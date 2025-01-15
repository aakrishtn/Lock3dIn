#include <iostream>
#include <filesystem>
#include "./src/app/processes/ProcessManagement.hpp"
#include "./src/app/processes/Task.hpp"

using namespace std;

namespace fs = filesystem; //only use fs wherever filesystem is to be used

int main(int argc, char *argv){
    string directory;
    string action;

    cout<<"Enter directory path: "<<endl;
    getline(cin,directory); //getline cz we want to read an entire line of input

    cout<<"Enter the action (encrypt/decrypt): "<<endl;
    getline(cin,action);

    try{
        if(fs::exists(directory) && fs::is_directory(directory))
        //is_dir returns bool val; it checks whether given path refers to a dir or not
        {
            ProcessManagement processManagement; // the constr of this class is anyways empty
            for(const auto &entry:fs::recursive_directory_iterator(directory))
            /*entry represents a single file in the iteration on directory; recursive directory iterator
            is iterating over all files in the directory including subdirectories recursively*/
            {
                if(entry.is_regular_file()){ //checking if current entry is only normal file and not another directory 
                    string filePath=entry.path().string(); //retrieving the full path of file as a str so that later it can be opened and operations can be done
                    IO io(filePath);
                    fstream f_stream = move(io.getFileStream());
                    if(f_stream.is_open()){
                        Action taskAction = (action=="encrypt")?Action::ENCRYPT:Action::DECRYPT;
                        auto task = make_unique<Task>(move(f_stream), taskAction, filePath); //creating a unique ptr to a task obj
                        processManagement.submitTaskToQueue(move(task));                     
                    }else{
                            cout<<"Unable to open the file: "<<filePath<<endl;
                    }
                }
            } 
            // now our files hv been read
            processManagement.executeTasks();
        }else{
            cout<<"Invalid directory path: "<<endl;
        }

    }catch(const fs::filesystem_error &ex){
        cout<<"Filesystem error: "<<ex.what()<<endl;
    }
    return 0;
}

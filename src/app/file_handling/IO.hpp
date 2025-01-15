using namespace std;
#ifndef IO_hpp
#define IO_hpp
// the IO_hpp which will be included in multiple classes will be compiled only once

#include <fstream>
#include <string>


class IO{
    //this class will take a file path, open and return; basically return the fstream
    public:
    IO(const string &file_path); //constructor of IO class; const cz file_path won't change ever 
    ~IO(); //destructor
    
    fstream getFileStream();

    private:
    fstream file_stream; //to store the file that has been read
};


#endif
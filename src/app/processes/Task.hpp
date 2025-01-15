using namespace std;
#ifndef TASK_HPP
#define TASK_HPP
#include <string>
#include<fstream>
#include <iostream>
#include "../file_handling/IO.hpp"
#include <sstream> 

enum class Action{
    ENCRYPT,
    DECRYPT
};

struct Task{
    string filePath;
    fstream f_stream;
    Action action;

    Task(fstream &&stream, Action act, string filePath):f_stream(move(stream)), action(act), filePath(filePath){}
    /* w/ &&, stream is a temporary object which will only pass an "fstream" further to assign it to f_stream; 
    here w/ move(stream) we hv passed the ownership of fstream obj, act has been put into action etc.
    here the parameters are being assigned to local variables; the tasks which have all these attributes are being passed on
    to process management and will be called to run child process; can be passed ot child process using serialisation and deserialisation */

    //serialising
    string toString() const {
        ostringstream oss;
        oss<<filePath<<","<<(action==Action::ENCRYPT? "ENCRYPT":"DECRYPT"); 
        // w/ what's above we'll get: test.txt ENCRYPT f_stream
        // we r using oss for string construction

        return oss.str(); 
        // "test.txt ENCRYPT"
    }

    //deserialising
    static Task fromString(const string &taskData){
        // taskData is a serialised string
        istringstream iss(taskData);
        string filePath;
        string actionStr;

        if(getline(iss, filePath, ',') && getline(iss, actionStr)){
            // whatevz in iss till ',' gets stored in filePath and remaining gets stored in actionStr
            Action action = (actionStr=="encrypt")?Action::ENCRYPT:Action::DECRYPT; //converting back into the Action enum
            IO io(filePath);
            fstream f_stream=move(io.getFileStream()); //we r not referencing but rather moving it to f_stream; to the Task constructor        
            // using filePath we r opening the filestream 
            if (f_stream.is_open()){
                return Task(move(f_stream), action, filePath);
            }

            else{
                throw runtime_error("Failed to open file: " + filePath);
            }
        }

        else{
            throw runtime_error("Invalid task data format");
        }
    }

};

#endif
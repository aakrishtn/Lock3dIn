#include<iostream>
using namespace std;
#include "IO.hpp"

// implementing contructor IO of the class IO
IO::IO(const string &file_path){
    file_stream.open(file_path, ios::in | ios::out | ios::binary); 
    /* private var file_stream has been opened and its content has been stored;
    everything else is flags specifying mode in which file shld open */
    if(!file_stream.is_open()){
        cout<<"Unable to open file: "<<file_path<<endl;
    }
}

fstream IO::getFileStream(){
    return move(file_stream); 
}

IO::~IO(){
    if(file_stream.is_open()){
        file_stream.close();
    }
}
 
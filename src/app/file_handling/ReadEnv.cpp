// in this "read environment" file we need a key to do the cryption

#include<iostream>
#include<fstream>
using namespace std;
#include "IO.hpp" //no need to call cpp file as it'll be redirected to there; passed by ref 
#include<string>
#include <sstream>

class ReadEnv{ //reading env file
public:
    string getEnv(){
        string env_path=".env"; //this is not in any directory but in the main working space only wjhere encrypt_decrypt is running
        IO io(env_path); 
        fstream f_stream = io.getFileStream();   
        stringstream buffer;
        buffer<<f_stream.rdbuf(); //w/ rdbuf() we r accessing the "stream buffer" of f_stream
        string content=buffer.str();
        return content;
    }
};
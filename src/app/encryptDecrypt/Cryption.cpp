#include<bits/stdc++.h>
#include "Cryption.hpp"
#include "../processes/Task.hpp" //Task will first be deserialised so that filepath can be extracted & then it'll be enc/dec
#include "../file_handling/ReadEnv.cpp"

int executeCryption(const string &taskData){
    Task task= Task::fromString(taskData);  ///deserialising
    ReadEnv env; //an obj of the class ReadEnv
    string envKey = env.getEnv(); //w/ getEnv() we r returning the str part of the ".env" file; our key is being read as a str
    int key = stoi(envKey);

    if(task.action==Action::ENCRYPT){
        char ch;
        while(task.f_stream.get(ch)){ // we can read the file content using the filestream that's in the Task 
            ch=(ch+key)%256; //by taking remainder w/ 256 our ans will always be within 0-255 and that way we can refer the ascii table
            task.f_stream.seekp(-1,ios::cur);
            task.f_stream.put(ch);
            /*once we get(ch) our ptr pts to the next ch so then .seekp(-1,ios::cur) we make
            ptr move one space back and then make it the current ptr and at that posn we put(ch
            which is now encrypted)*/
        }
        task.f_stream.close();
    }else{
        char ch;
        while(task.f_stream.get(ch)){
            ch=(ch-key+256)%256;
            task.f_stream.seekp(-1,ios::cur);
            task.f_stream.put(ch);
        }
        task.f_stream.close();
    }
    return 0;     
}
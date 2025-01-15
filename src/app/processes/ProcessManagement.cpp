using namespace std;
#include "ProcessManagement.hpp"
#include<iostream>
#include<cstring>
#include<sys/wait.h>
#include "../encryptDecrypt/Cryption.hpp"
#include<unistd.h>

ProcessManagement::ProcessManagement(){}

bool ProcessManagement::submitTaskToQueue(unique_ptr<Task> task){
    taskQueue.push(move(task));
    return true;
}

void ProcessManagement::executeTasks()
// executeTasks() is to consume tasks from th queue and make a child process of each task; in this project we r not making child process but directly encrppting and decrypting
{
    while(!taskQueue.empty()){
        unique_ptr<Task> taskToExecute = move(taskQueue.front()); //moving ownership to local variable of this file
        taskQueue.pop();
        cout<<"Executing task: "<<taskToExecute->toString()<<endl; //taskToExecute is u_ptr pting to tasks in taskQueue; here w r printing the toString of task
        executeCryption(taskToExecute->toString());
    }
}
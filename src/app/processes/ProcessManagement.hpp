using namespace std;

#ifndef PROCESS_MANAGEMENT_HPP
#define PROCESS_MANAGEMENT_HPP
#include "Task.hpp"
#include <queue>
#include <memory>

class ProcessManagement{
public:
    ProcessManagement();
    bool submitTaskToQueue(unique_ptr<Task> task);
    void executeTasks();
private:
    queue<unique_ptr<Task>> taskQueue; //a queue where each elemt is a unique_ptr pointing to diff tasks
};

#endif
 


//JUST FOR TESTING THE CRYPTION ALGORITHM
#include<iostream>
#include "Cryption.hpp"

int main(int argc, char* argv[]){
    if(argc!=2){
        cerr<<"Usage: ./cryption <task_data>"<<endl;
        return 1;
    }
    executeCryption(argv[1]);
    return 0;
}
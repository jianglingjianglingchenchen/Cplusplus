#include "../include/thread.hpp"
#include <iostream>
using std::cerr;
using std::endl;
using std::cout;

Thread::Thread(const CallBack& cb)
:_cb(cb){

}

Thread::~Thread(){}

void Thread::start(){
    int err = pthread_create(&_tid,nullptr,threadFunc,this);
    if(err != 0){
        cerr << "pthread_create failed" << endl;
        exit(1);
    }
    cout << _tid << endl;
}

void Thread::join(){
    int err = pthread_join(_tid,nullptr);
    if(err != 0){
        cerr << "pthread_join failed" << endl;
        exit(1);
    }
}

void* Thread::threadFunc(void* arg){
    Thread* pth = (Thread*)arg;
    pth->_cb();
    return nullptr;
}





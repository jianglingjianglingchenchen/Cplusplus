#include "Thread.hpp"
#include <pthread.h>
#include <iostream>
using std::cerr;
using std::cout;

void Thread::start(){
    //这里与pthread_once类似
    //不能用bind绑定threadFunc然后作为第三个参数
    //因为bind返回的是一个函数对象，而第三个参数只能是一个函数指针
    //因此只能将threadFunc设置为static的，并将this作为参数传递给它
    if(!_isRunning){
        int err = pthread_create(&_tid,nullptr,threadFunc,this);
        if(err){
            cerr << "pthread_create" << "\n";
            return;
        }
        _isRunning = true;
    }
    else{
        cout << "thread is exist" << "\n";
    }
}

void Thread::join(){
    if(_isRunning){
        int err = pthread_join(_tid,nullptr);
        if(err){
            cerr << "pthread_create" << "\n";
            return;
        }
    }
}

void* Thread::threadFunc(void* arg){
    Thread* pthis = (Thread*)arg;
    pthis->run();
    /* return nullptr; */
    pthread_exit(nullptr);
}

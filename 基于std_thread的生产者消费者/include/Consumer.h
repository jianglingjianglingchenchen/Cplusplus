#ifndef  __CM_H__
#define  __CM_H__

#include "TaskQueue.h"
#include <unistd.h>
#include <thread>
#include <iostream>
#include <functional>
#include <memory>
using std::thread;
using std::cout;
using std::endl;
using std::bind;
using std::unique_ptr;

class Consumer
{
public:
    Consumer(TaskQueue& que)
    :_tq(que),_tid(nullptr)
    {}

    ~Consumer() {}

    void consume(){
        /* thread th(bind(&Consumer::threadFunc,this)); */
        _tid.reset(new thread(bind(&Consumer::threadFunc,this)));
    }

    void join(){
        if(_tid){
            _tid->join();
        }
    }

private:
    void threadFunc(){
        while(1){
            cout << "consume:" << _tq.pop() << endl;
            /* sleep(1); */
        }
    }

private:
    TaskQueue& _tq;
    unique_ptr<std::thread> _tid;
};

#endif

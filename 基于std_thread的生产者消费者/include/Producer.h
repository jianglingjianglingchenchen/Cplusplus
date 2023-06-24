#ifndef __PD_H__
#define __PD_H__

#include <memory>
#include <unistd.h>
#include "TaskQueue.h"
#include <thread>
#include <stdlib.h>
#include <functional>
#include <iostream>
using std::thread;
using std::bind;
using std::cout;
using std::endl;
using std::unique_ptr;

class Producer
{
public:
    Producer(TaskQueue& que)
    :_tq(que),_tid(nullptr)
    {}

    ~Producer() {}

    void start(){
        cout << "befor thread create" << endl;
        //这里一定要创建堆对象，否则创建栈对象，并将栈对象的指针赋给_tid的话，_tid->join()将导致未定义的行为
        _tid.reset(new thread(bind(&Producer::threadFunc,this)));
        //pthread_create(&tid,nullptr,Func,this)
        //Func{
        //  this->threadFunc();
        //}
        cout << "end create thread" << endl;
        /* _tid = &th; *///这里就是错误情况，将栈对象的指针进行了托管
    }

    void join(){
        if(_tid.get()){
            _tid->join();
        }
    }

private:
    void threadFunc(){
        cout << "in threadFunc" << endl;
        srand(time(nullptr));
        while(1){
            int cargo = rand() % 77;
            _tq.push(cargo);
            sleep(1);
        }
    }

private:
    TaskQueue& _tq;
    unique_ptr<std::thread> _tid;//这里用智能指针管理可以省略delete的步骤
};
#endif


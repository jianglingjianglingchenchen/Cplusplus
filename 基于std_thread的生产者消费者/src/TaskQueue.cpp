#include "../include/TaskQueue.h"
#include <thread>
#include <iostream>
using std::unique_lock;
using std::cout;
using std::endl;

bool TaskQueue::empty(){
    return 0 == _que.size();
}
bool TaskQueue::full(){
    return _queSize == _que.size();
}
void TaskQueue::push(const int& value){
    //1、加锁
    unique_lock<mutex> lk(_mutex);
    //2、判断队列是否为空
    //3、空则wait
    while(full()){
        _notFull.wait(lk);//condition_variable的wait函数的参数只能是unique_lock，因为unique_lock可以自行解锁
        //而lock_guard是不允许自行解锁的。而wait在陷入等待之前会先把锁解开，所以只能用unique_lock
    }
    //4、非空则直接往队列中生产一个产品
    _que.push(value);
    //5、解锁并通知消费者
    _mutex.unlock();
    _notEmpty.notify_one();
}

int TaskQueue::pop(){
    unique_lock<mutex> lk(_mutex);
    while(empty()){
        _notEmpty.wait(lk);
    }
    int ret = _que.front();
    _que.pop();
    _mutex.unlock();
    _notFull.notify_one();
    return ret;
}

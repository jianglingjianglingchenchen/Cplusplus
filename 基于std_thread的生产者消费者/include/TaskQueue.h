#ifndef __TQ_H__
#define __TQ_H__
#include <iostream>
#include <queue>
#include <mutex>
#include <condition_variable>
using std::queue;
using std::mutex;
using std::condition_variable;

class TaskQueue
{
public:
    TaskQueue(size_t queSize)
    :_queSize(queSize),_que(),_mutex(),_notEmpty(),_notFull()
    {}

    ~TaskQueue() {}

    bool empty();
    bool full();
    void push(const int& value);
    int pop();

private:
    size_t _queSize;
    queue<int> _que;
    mutex _mutex;
    condition_variable _notEmpty;
    condition_variable _notFull;
};

#endif


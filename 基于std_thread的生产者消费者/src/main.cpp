#include <iostream>
#include "../include/TaskQueue.h"
#include "../include/Producer.h"
#include "../include/Consumer.h"
#include "../include/thread.hpp"

void test(){
    TaskQueue task_queue(10);
    auto tmp = bind(&TaskQueue::push,&task_queue,77);
    thread tid(tmp);
    /* thread tid(threadFunc,task_queue); */
    tid.join();
    cout << task_queue.empty() << endl;
    /* task_queue.push(23); */
    cout << task_queue.pop() << endl;
    cout << task_queue.empty() << endl;
}

void test1(){
    TaskQueue tq(10);
    Producer pd1(tq);
    Producer pd2(tq);
    Consumer cm(tq);
    pd1.start();
    pd2.start();
    cm.consume();
    pd1.join();
    pd2.join();
    cm.join();
}

int main()
{
    test1();
    return 0;
}


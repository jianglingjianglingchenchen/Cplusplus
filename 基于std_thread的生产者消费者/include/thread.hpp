#ifndef __THREAD_H__
#define __THREAD_H__
#include <functional>
#include <pthread.h>
using std::function;

using CallBack = function<void(void)>;

class Thread
{
public:
    Thread(const CallBack&); 
    ~Thread();
    void start();
    void join();

private:
    static void* threadFunc(void* arg);

private:
    const CallBack& _cb;
    pthread_t _tid;
};
#endif

#ifndef __TH_H__
#define __TH_H__

#include <functional>
#include <pthread.h>
#include <utility>

/* using std::function; */
/* using CallBcak = function<void(void)>; */

//抽象基类
class Thread
{
public:
    Thread() 
    :_tid(),_isRunning(false){}

    //抽象类记得将析构函数设置为虚函数
    virtual ~Thread() {}

    void start();
    void join();

private:
    static void* threadFunc(void* arg);
    virtual void run() = 0;
private:
    pthread_t _tid;
    bool _isRunning;
};

#endif


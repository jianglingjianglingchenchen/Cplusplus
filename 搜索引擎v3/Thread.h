#ifndef __THREAD_H__
#define __THREAD_H__

#include <pthread.h>
#include <functional>

using std::function;
using std::bind;

namespace current_thread_id{
    extern __thread int tNum;
}

class Thread
{
    using ThreadCallback = function<void()>;
public:
    Thread(ThreadCallback &&cb,const int&);
    ~Thread();

    //线程运行与停止的函数
    void start();
    void join();

private:
    //线程入口函数
    static void *threadFunc(void *arg);

private:
    pthread_t _thid;//线程id
    int _tNum;
    bool _isRunning;//标识线程是否在运行
    ThreadCallback _cb;//就是需要执行的任务
};

#endif

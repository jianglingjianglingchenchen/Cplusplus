#include <iostream>
#include "logger.hpp"
using namespace std;

//void test0()
//{
//    //第一步，完成单例模式的写法
//    Mylogger *log = Mylogger::getInstance();
//
//    log->info("The log is info message");
//    log->error("The log is error message");
//    log->fatal("The log is fatal message");
//    log->crit("The log is crit message");
//}
//
//void test1() 
//{
//    printf("hello,world\n");
//    //第二步，像使用printf一样
//    //只要求能输出纯字符串信息即可，不需要做到格式化输出
//    LogInfo("The log is info message");
//    LogError("The log is error message");
//    LogWarn("The log is warn message");
//    LogDebug("The log is debug message");
//}

void test23(){
    Mylogger* logg = Mylogger::getInstance();
    LogWarn("this is warn");
    LogError("this is jordan number:%d",23);
    LogDebug("this is %s","hello");
    LogInfo("this is chenyi %f",23.77);
}

int main()
{
    test23();
    return 0;
}


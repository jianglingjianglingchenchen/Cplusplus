#ifndef __WD_Mylogger_HPP__ 
#define __WD_Mylogger_HPP__
//预处理操作是针对于一个*.cc文件的，
//当头文件在一个*.cc文件中出现多次时
//只会有一份Mylogger的源码出现

//keep your code clean
#include <log4cpp/Category.hh>
#include <iostream>
#include <sstream>
using namespace std;

namespace wd
{

class Mylogger
{
public:
    static Mylogger * getInstance();
    static void destroy();

    void error(const char* msg){
        _mycat.error(msg);
    }

    template <class T,class... Args>
    void error(const char * msg,T t,Args... args){
            string tmp(msg);
            for(int i = 0;i < tmp.size();++i){
                if(tmp[i] == '%'){
                    tmp.erase(i,2);
                    ostringstream ostr;
                    ostr << t;
                    tmp.insert(i,ostr.str());
                    break;
                }
            }
            error(tmp.c_str(),args...);
    }
    void warn(const char * msg);
    void info(const char * msg);
    void debug(const char * msg);

private:
    Mylogger();
    ~Mylogger();

private:
    log4cpp::Category & _mycat;//引用成员
    //log4cpp::OstreamAppender * _pos;
    static Mylogger * _pInstance;
};

#define LogError(msg,...) wd::Mylogger::getInstance()->error(addprefix(msg),##__VA_ARGS__)
#define LogWarn(msg) wd::Mylogger::getInstance()->warn(addprefix(msg))
#define LogInfo(msg) wd::Mylogger::getInstance()->info(addprefix(msg))
#define LogDebug(msg) wd::Mylogger::getInstance()->debug(addprefix(msg))

#define addprefix(msg) string("[")\
    .append(__FILE__).append(":")\
    .append(__FUNCTION__).append(":")\
    .append(std::to_string(__LINE__)).append("] ")\
    .append(msg).c_str()



}//end of namespace wd

#endif



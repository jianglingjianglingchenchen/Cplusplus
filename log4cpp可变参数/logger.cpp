#include "logger.hpp"
#include <log4cpp/Priority.hh>
#include <log4cpp/PatternLayout.hh>
#include <log4cpp/FileAppender.hh>
#include <log4cpp/RollingFileAppender.hh>
#include <log4cpp/OstreamAppender.hh>
using namespace std;

Mylogger::Mylogger()
:_myloger(log4cpp::Category::getInstance("mylogger")){
    _myloger.setPriority(log4cpp::Priority::DEBUG);
    log4cpp::OstreamAppender* os_appender = new log4cpp::OstreamAppender("console",&cout);
    log4cpp::PatternLayout* os_layout = new log4cpp::PatternLayout();
    os_layout->setConversionPattern("%d %c [%p] %m%n");
    os_appender->setLayout(os_layout);
    log4cpp::FileAppender* file_appender = new log4cpp::FileAppender("fileLog","mylog.log");
    log4cpp::PatternLayout* file_layout = new log4cpp::PatternLayout();
    file_layout->setConversionPattern("%d %c [%p] %m%n");
    file_appender->setLayout(file_layout);
    log4cpp::RollingFileAppender* rl_appender = new log4cpp::RollingFileAppender("rlLog","rl.log",2*128*128,1);
    log4cpp::PatternLayout* rl_layout = new log4cpp::PatternLayout();
    rl_layout->setConversionPattern("%d %c [%p] %m%n");
    rl_appender->setLayout(rl_layout);
    _myloger.setAppender(os_appender);
    _myloger.setAppender(file_appender);
    _myloger.setAppender(rl_appender);
}

Mylogger::~Mylogger(){
    _myloger.shutdown();
}

Mylogger* Mylogger::getInstance(){
    if(!_pInstance){
        _pInstance = new Mylogger();
    }
    return _pInstance;
}

void Mylogger::destory(){
    if(_pInstance){
        delete _pInstance;
        _pInstance = nullptr;
    }
}

/* void Mylogger::warn(const char* msg){ */
/*     _myloger.warn(msg); */
/* } */

/* void Mylogger::error(const char* msg){ */
/*     _myloger.error(msg); */
/* } */

/* void Mylogger::debug(const char* msg){ */
/*     _myloger.debug(msg); */
/* } */

/* void Mylogger::info(const char* msg){ */
/*     _myloger.info(msg); */
/* } */

Mylogger* Mylogger::_pInstance = nullptr;


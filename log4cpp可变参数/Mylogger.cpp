#include "Mylogger.hpp"
#include <iostream>

#include <log4cpp/Priority.hh>
#include <log4cpp/PatternLayout.hh>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/FileAppender.hh>

using std::cout;
using std::endl;
using namespace log4cpp;

namespace wd
{

Mylogger * Mylogger::_pInstance = nullptr;

Mylogger * Mylogger::getInstance()
{
    if(nullptr == _pInstance) {
        _pInstance = new Mylogger();
    }
    return _pInstance;
}
    
void Mylogger::destroy()
{
    if(_pInstance) {
        delete _pInstance;
        _pInstance = nullptr;
    }
}

Mylogger::Mylogger()
: _mycat(Category::getRoot().getInstance("mycat"))
{
    //C++11新特性, auto会自动推断类型
    auto ptnLayout1 = new PatternLayout();
    ptnLayout1->setConversionPattern("%d %c [%p] %m%n");
    auto ptnLayout2 = new PatternLayout();
    ptnLayout2->setConversionPattern("%d %c [%p] %m%n");
    auto posApp = new OstreamAppender("console", &cout);
    posApp->setLayout(ptnLayout1);
    auto pfileApp = new FileAppender("pfileApp", "wd.log");
    pfileApp->setLayout(ptnLayout2);

    _mycat.setPriority(Priority::DEBUG);
    _mycat.addAppender(posApp);
    _mycat.addAppender(pfileApp);
    cout << "Mylogger()" << endl;
}

Mylogger::~Mylogger()
{
    Category::shutdown();
    cout << "~Mylogger()" << endl;
}

//template <class T,class... Args>
//void Mylogger::error(const char * msg,T t,Args... args)
//{   
//}

void Mylogger::warn(const char * msg)
{   _mycat.warn(msg);   }

void Mylogger::info(const char * msg)
{   _mycat.info(msg);   }

void Mylogger::debug(const char * msg)
{   _mycat.debug(msg);  }

}//end of namespace wd


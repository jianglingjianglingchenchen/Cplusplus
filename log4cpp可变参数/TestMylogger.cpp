#include "Mylogger.hpp"
#include <iostream>
using std::cout;
using std::endl;
using std::string;

void test0()
{
    /* wd::Mylogger::getInstance()->error("this is an error msg"); */
    wd::Mylogger::getInstance()->warn("this is a warn msg");
    wd::Mylogger::getInstance()->info("this is an info msg");
    wd::Mylogger::getInstance()->debug("this is a debug msg");
}

void test1()
{
    cout << __FILE__ << endl;
    cout << __LINE__ << endl;
    cout << __FUNCTION__ << endl;
    cout << __func__ << endl;
}


void test2()
{
    cout << addprefix("this is a test msg") << endl;
    cout << addprefix("this is a test2 msg") << endl;
}

void test3()
{
    //wd::Mylogger::getInstance()->error(addprefix("this is an error msg"));
    wd::Mylogger::getInstance()->warn(addprefix("this is a warn msg"));
    wd::Mylogger::getInstance()->info(addprefix("this is an info msg"));
    wd::Mylogger::getInstance()->debug(addprefix("this is a debug msg"));
}

void test4()
{
    int number = 10;
    double dnumber = 3.14;
    string name = "chenyi";
    LogError("this is an error message, %d, %lf ,%s", number, dnumber,name);
    LogWarn("this is a warn message");
    LogInfo("this is an info message");
    LogDebug("this is a debug message");
}

int main()
{
    /* test0(); */
    /* test1(); */
    /* test2(); */
    /* test3(); */
    test4();
    wd::Mylogger::destroy();
    return 0;
}



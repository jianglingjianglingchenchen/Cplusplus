#include <log4cpp/Category.hh>
#include <string>
using std::string;

class Mylogger
{
public:
    static Mylogger* getInstance();
    static void destory();
    template <class... Args>
    void warn(const char *msg,Args... args){
        _myloger.warn(msg,args...);
    }
    template <class... Args>
    void error(const char *msg,Args... args){
        _myloger.error(msg,args...);
    }
    template <class... Args>
    void debug(const char *msg,Args... args){
        _myloger.debug(msg,args...);
    }
    template <class... Args>
	void info(const char *msg,Args... args){
        _myloger.info(msg,args...);
    }
private:
	Mylogger();
	~Mylogger();
    
private:
  //......
    log4cpp::Category& _myloger;
    static Mylogger* _pInstance;
};

//38行的末尾必须要加分号，否则调用处会一直报缺失分号的错误
#define LogWarn(msg,...) { \
    Mylogger::getInstance()->warn(LOG(msg),##__VA_ARGS__); \
}

#define LogError(msg,...) { \
    Mylogger::getInstance()->error(LOG(msg),##__VA_ARGS__); \
}

#define LogDebug(msg,...) { \
    Mylogger::getInstance()->debug(LOG(msg),##__VA_ARGS__); \
}

#define LogInfo(msg,...) { \
    Mylogger::getInstance()->info(LOG(msg),##__VA_ARGS__); \
}

#define LOG(msg){ \
    string(msg).append("\n").append("filename:").append(__FILE__).append("  ") \
    .append("function:").append(__FUNCTION__).append("  ")   \
    .append("line:").append(to_string(__LINE__)).c_str()    \
}

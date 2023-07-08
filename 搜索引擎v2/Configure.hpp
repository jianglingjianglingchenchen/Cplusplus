#ifndef __CONFIGURE_HPP__
#define __CONFIGURE_HPP__
#include <iostream>
using std::string;
class Configure
{
public:
#if 0
    static Configure * getInstance(const string & path){
        if(_pInstance == nullptr){
            atexit(destroy);
            _pInstance = new Configure(path);
        }
        return _pInstance;
    }
    static void init(){
        _pInstance = new Configure();
        atexit(destroy);
    }
    static void destroy(){
        if(_pInstance){
            delete _pInstance;
            _pInstance = nullptr;
        }
    }
    static Configure * getPtr(){
        return _pInstance;
    }
#endif
    string handlePath(const string & line);
    void readPath();
    string getZnDict(){
        return _znDict;
    }
    string getZnIndex(){
        return _znIndex;
    }
    string getEngDict(){
        return _engDict;
    }
    string getEngIndex(){
        return _engIndex;
    }
    string getPage(){
        return _pageStoreHouse;
    }
    string getOffset(){
        return _offsetStoreHouse;
    }
    string getIndex(){
        return _invertStoreHouse;
    }
/* private: */
    Configure(const string & path);
    ~Configure();
private:
    string _path;//加载配置文件的路径
    string _znDict;//中文词典库路径名
    string _znIndex;//中文索引库路径名
    string _engDict;//英文词典库路径名
    string _engIndex;//英文索引库路径名
    string _pageStoreHouse;//网页库路径名
    string _offsetStoreHouse;//网页偏移库路径名
    string _invertStoreHouse;//倒排索引库路径名
    /* static Configure * _pInstance; */
};
#endif


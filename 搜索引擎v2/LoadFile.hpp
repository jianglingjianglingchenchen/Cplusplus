#ifndef __LOADFILE_HPP__
#define __LOADFILE_HPP__
#include "webPage.hpp"
#include "Configure.hpp"
#include <vector>
#include <unordered_map>
#include <set>
#include <iostream>
#include <functional>
#include <stdlib.h>
#include <pthread.h>
#include <mutex>
using std::vector;
using std::unordered_map;
using std::set;
using std::pair;
using std::make_pair;
using std::endl;
using std::cout;
class LoadFile
{
public:
    /* static LoadFile * getInstance(Configure * pconf){ */
    static LoadFile * getInstance(){
        /* auto init_func = [pconf](){ */
        /*     init(pconf); */
        /* }; */
        /* std::function<void()> init_r = init_func; */
        /* std::function<void(void)> tmp = std::bind(init,pconf); */
        pthread_once(&once,init);
        return _pInstance;
        
        /* call_once(flag,tmp); */
    }
    static void init(){
        _pInstance = new LoadFile();
        atexit(destroy);
    }
    static void destroy(){
        if(_pInstance){
            delete _pInstance;
            _pInstance = nullptr;
        }
    }
    void loadFile(Configure * _pconf);
    vector<pair<int,webPage>> & getPage(){
        return _pageLib;
    }
    unordered_map<int,pair<int,int>> & getOffset(){
        return _offsetLib;
    }
    unordered_map<string,set<pair<int,double>>> & getIndex(){
        return _invertIndexTable;
    }
private:
    LoadFile();
    ~LoadFile();
private:
    //网页库
    vector<pair<int,webPage>> _pageLib;
    //网页偏移库
    unordered_map<int,pair<int,int>>  _offsetLib;
    //倒排索引库
    unordered_map<string,set<pair<int,double>>>  _invertIndexTable;
    //配置文件类
    /* Configure * _pconf; */
    static LoadFile * _pInstance;
    static pthread_once_t once;
    /* static std::once_flag flag; */
};
/* pthread_once_t LoadFile::once = PTHREAD_ONCE_INIT; */
/* LoadFile * LoadFile::_pInstance = nullptr; */
#endif


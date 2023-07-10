#include "CacheManager.h"
#include <algorithm>
#include <iterator>


CacheManager& CacheManager::getInstance(const int& arrSize){
    static CacheManager cacheManager(arrSize); 
    return cacheManager;
}

LRUcache& CacheManager::getLRUcache(int index){
    return *(_cacheArr[index]);
}

CacheManager::CacheManager(const int& arrSize){
    //一个线程对应一个cache的话,需要知道有几个线程
    //在这里初始化所有的LRUcache
    //缓存大小的选择
    for(int i = 0;i < arrSize;++i){
        unique_ptr<LRUcache> tmp(new LRUcache(10));
        tmp->readFile();
        _cacheArr.push_back(std::move(tmp));
    }
    /* for(auto& x : _cacheArr){ */
    /*     x.readFile();//将持久化到磁盘中的数据重新加载回cache */
    /* } */
}

struct TupleComparator{
    bool operator()(const tuple<key,mode,string>& a,
                    const tuple<key,mode,string>& b) const{
        return std::get<0>(a) < std::get<0>(b);
    }
};

struct TupleEqual {
    bool operator()(const std::tuple<std::string, int, std::string>& a,
                    const std::tuple<std::string, int, std::string>& b) const {
        return std::get<0>(a) == std::get<0>(b) &&
               std::get<1>(a) == std::get<1>(b) &&
               std::get<2>(a) == std::get<2>(b);
    }
};

void CacheManager::update(){//将各个缓存进行同步
    /* for(auto& x : _cacheArr){//x = unique_ptr<LRUcache> */
    /*     list<tuple<key,mode,string>> tmp; */
    /* } */
    list<tuple<key,mode,string>> tmp(_cacheArr[0]->_pendingUpdate.begin(),_cacheArr[0]->_pendingUpdate.end());
    tmp.sort(TupleComparator{});

    list<tuple<key,mode,string>> emp;
    for(int i = 1;i < (int)_cacheArr.size();++i){
        _cacheArr[i]->_pendingUpdate.sort(TupleComparator{});
        std::merge(tmp.begin(),tmp.end(),
                   _cacheArr[i]->_pendingUpdate.begin(),
                   _cacheArr[i]->_pendingUpdate.end(),
                   std::back_inserter(emp));
        //更新完之后要清除原来的待更新队列
        _cacheArr[i]->_pendingUpdate.clear();

        emp.unique(TupleEqual{});
        tmp.assign(emp.begin(),emp.end());
        emp.clear();
    }

    for(int i = 0;i < _cacheArr[0]->_cacheSize;++i){
        //tmp目前存放着所有全部地最新数据
        //将tmp中的所有数据放到主cache中的_cache
        _cacheArr[0]->addData(std::get<0>(tmp.front()),
                              std::get<1>(tmp.front()),
                              std::get<2>(tmp.front()));

        tmp.pop_front();

        if(tmp.size() == 0)
            break;
    }

    LRUcache& mainC = getLRUcache(0);
    for(int i = 1;i < (int)_cacheArr.size();++i){
        _cacheArr[i]->updateLRUcache(mainC);
    }

}

CacheManager::~CacheManager(){

}

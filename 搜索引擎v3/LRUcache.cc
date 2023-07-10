#include "LRUcache.h"
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <tuple>
#include <iostream>
#include <fstream>
#include <sstream>
using std::tuple;
using std::cout;
using std::endl;
using std::ifstream;
using std::istringstream;



void LRUcache::addData(const key& keys,const mode& modes,const string& results){
    //如果缓存满了就淘汰最久未访问的数据
    if((int)_cache.size() >= _cacheSize){
        std::tuple<key,mode,string> toDrop = _cache.front();
        _cache.pop_front();//才链表中删除节点
        key keyword = std::get<0>(toDrop);
        mode dropNode_mode = std::get<1>(toDrop);
        auto dropingNode = _mapping.find(std::make_pair(keyword,dropNode_mode)); 
        if(dropingNode != _mapping.end()){
            _mapping.erase(dropingNode);
        }
    }
    //将数据插入到cache中，并且更新哈希表
    _cache.emplace_back(keys,modes,results);
    auto it = _cache.end();
    pair<key,mode> ele(keys,modes);
    _mapping.emplace(ele,--it);

    //同时也要将数据插入到待更新的链表中，以便进行同步
    /* tuple<key,mode,string> data(keys,modes,results); */
    _pendingUpdate.emplace_back(keys,modes,results);
}

string LRUcache::getData(const key& keys,const mode& modes){
    pair<key,mode> toSearch(keys,modes);
    auto res = _mapping.find(toSearch);
    if(res != _mapping.end()){//说明数据在缓存中
        //将本次访问的数据放到队尾，表示新访问
        _cache.splice(_cache.end(),_cache,res->second);
        return std::get<2>(*(res->second));
    }
    else{
        return {""};
    }
}

void LRUcache::updateLRUcache(const LRUcache& cache){
    _cache.assign(cache._cache.begin(),cache._cache.end());
    updateMapping();
}

void LRUcache::updateMapping(){
    _mapping.clear();
    auto itt = _cache.begin();
    while(itt != _cache.end()){
        _mapping.emplace(std::make_pair(std::get<0>(*itt),std::get<1>(*itt)),itt);

        ++itt;
    }
    cout << "list_size:" << _cache.size() << endl;
    cout << "mapping_size:" << _mapping.size() << endl;
}

void LRUcache::printResultList(){
    for(const auto& x : _cache){
        string keys = std::get<0>(x);
        int num = std::get<1>(x);
        string res = std::get<2>(x);
        cout << keys << " " << num << " "
            << res << endl;
    }
    cout << endl;
    for(const auto& x : _mapping){
        string str = std::get<2>(*(x.second));
        cout << str << endl;
    }
}

void LRUcache::readFile(){
    ifstream file("cacheList.txt");
    if(!file.is_open()) {
        cout << "目前无缓存文件" << endl;
        return;
    }
    string line;
    while (std::getline(file, line)) {
        istringstream lines(line);
        key keyWord;
        lines >> keyWord;
        string num;
        lines >> num;
        mode modes = std::stoi(num);
        string json_str;
        lines >> json_str;
        _cache.emplace_back(keyWord,modes,json_str);
        auto itt = _cache.end();
        _mapping.emplace(std::make_pair(keyWord,modes),--itt);
    }
    file.close();
}

void LRUcache::writeFile(){
    int fd2 = ::open("cacheList.txt",O_RDWR|O_CREAT|O_TRUNC,0666);
    if(fd2 == -1){
        perror("::open");
        exit(-1);
    }

    for(const auto& x : _cache){
        key keyWord = std::get<0>(x);
        mode modes = std::get<1>(x);
        string json_str = std::get<2>(x);
        string toWrite = keyWord + " " + std::to_string(modes)
                         + " " + json_str + "\n";
        ssize_t sret = ::write(fd2,toWrite.c_str(),toWrite.size());
        if(sret == -1){
            perror("::write");
            exit(-1);
        }
    }

    ::close(fd2);
} 

LRUcache::LRUcache(const int& size)
:_cacheSize(size){

}

LRUcache::~LRUcache(){

}

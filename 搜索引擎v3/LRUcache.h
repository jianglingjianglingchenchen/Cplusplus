#ifndef __LRUCACHE_H__
#define __LRUCACHE_H__

#include "NonCopyable.h"
#include <unordered_map>
#include <list>
#include <string>
#include <tuple>
using std::string;
using std::unordered_map;
using std::list;
using std::pair;
using std::tuple;

struct PairHash {
    template <class T1, class T2>
    std::size_t operator() (const std::pair<T1, T2>& p) const {
        auto h1 = std::hash<T1>{}(p.first);
        auto h2 = std::hash<T2>{}(p.second);
        return h1 ^ h2;
    }
};

struct PairEqual {
    template <class T1, class T2>
    bool operator() (const std::pair<T1, T2>& lhs, const std::pair<T1, T2>& rhs) const {
        return lhs.first == rhs.first && lhs.second == rhs.second;
    }
};



using key = string;
using mode = int;
using it = list<tuple<key,mode,string>>::iterator;
class LRUcache
:public NonCopyable 
{
public:
    friend class CacheManager;
    void addData(const key&,const mode&,const string&);
    string getData(const key&,const mode&);
    void updateLRUcache(const LRUcache&);
    void printResultList();
    void readFile();
    void writeFile();
    LRUcache(const int&);
    ~LRUcache();
private:
    void updateMapping();
private:
    int _cacheSize;
    list<tuple<key,mode,string>> _cache;
    unordered_map<pair<key,mode>,it,PairHash,PairEqual> _mapping;
    //在待更新的链表中,要存储查询的词,是关键字查询还是网页查询,以及查询的结果
    list<std::tuple<key,mode,string>> _pendingUpdate;
};

#endif

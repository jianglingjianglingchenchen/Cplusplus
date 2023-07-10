#ifndef __CACHEMANAGER_H__
#define __CACHEMANAGER_H__

#include "LRUcache.h"
#include <vector>
#include <memory>
using std::vector;
using std::unique_ptr;

class CacheManager
{
public:
    static CacheManager& getInstance(const int&);
    LRUcache& getLRUcache(int index);
    void update();//将各个缓存进行同步


    CacheManager(const CacheManager&) = delete;
    CacheManager(CacheManager&&) = delete;
    CacheManager& operator=(const CacheManager&) = delete;
    CacheManager& operator=(CacheManager&&) = delete;
private:
    CacheManager(const int&);
    ~CacheManager();
private:
    vector<unique_ptr<LRUcache>> _cacheArr;
};



#endif

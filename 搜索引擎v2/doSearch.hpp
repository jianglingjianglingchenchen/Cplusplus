#ifndef __DOSEARCH_HPP__
#define __DOSEARCH_HPP__
#include "LoadFile.hpp"
#include "Configure.hpp"
using std::string;

struct Result;

class doSearch
{
public:
    doSearch(const string & sought);
    ~doSearch();
    vector<Result> run(LoadFile * load);

private:
    string _sought;
    /* LoadFile * _load; */
};
#endif


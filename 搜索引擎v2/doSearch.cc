#include "doSearch.hpp"
#include "webQuery.hpp"
doSearch::doSearch(const string & sought)
: _sought(sought)
/* , _load(load) */
{

}

doSearch::~doSearch(){

}

vector<Result> doSearch::run(LoadFile * load){
    webQuery query(_sought,load);   
    query.returnQuery();
    return query.response();
    /* query.print(); */
}

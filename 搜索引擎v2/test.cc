#include <iostream>
#include "webQuery.hpp"
#include "LoadFile.hpp"
#include "Configure.hpp"
#include "Cos.hpp"
#include "doSearch.hpp"
using std::cout;
using std::endl;
#if 1
void test0(){
    Configure conf("configure.conf");
    conf.readPath();
    LoadFile * load = LoadFile::getInstance();
    load->loadFile(&conf);
    string str("坚决捍卫国家领土");
    doSearch search(str);
    search.run(load);
    /* webQuery query(str,load); */
    /* load->loadFile(&conf); */
    /* query.returnQuery(); */
    /* query.print(); */
}
#endif
#if 0
void test1(){
    vector<double> vec1 = {1.1,2.2,3.3,4.4,5.5};
    vector<double> vec2 = {2.2,3.3,4.4,5.5,6.6};
    Cos cos(vec1,vec2);
    cout << cos.countCos() << endl;
}
/* #endif */
void test2(){
    Configure conf("configure.conf");
    conf.readPath();
    LoadFile * load = LoadFile::getInstance(&conf);
    load->loadFile();
}
#endif
int main()
{
    test0();
    /* test1(); */
    /* test2(); */
    return 0;
}


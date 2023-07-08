#ifndef __WEBPAGE_HPP__
#define __WEBPAGE_HPP__
#include "tinyxml2.hpp"
#include <iostream>
using namespace tinyxml2;
using std::string;
class webPage
{
public:
    webPage();//需要知道存放磁盘文件的路径名
    ~webPage();
    //获取文章信息
    void getDoc(const string & file);
    //获取文章id
    int getID(){
        return _docid;
    }
    //获取文章标题
    string getTitle(){
        return _docTitle;
    }
    string getLink(){
        return _docUrl;
    }
    //获取文章摘要
    /* string getDescription(){ */
    /*     return _docDescription; */
    /* } */
    //获取文章内容
    string getContent(){
        return  _docContent;
    }
private:
    /* string _file; */
    int _docid;//文档id
    string _docTitle;//文档标题
    string _docUrl;//文档Url
    /* string _docDescription;//文档摘要 */
    string _docContent;//文档内容
};
#endif


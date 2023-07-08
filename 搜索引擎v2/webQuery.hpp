#ifndef __WEBQUERY_HPP__
#define __WEBQUERY_HPP__

#include "wordSegmentation.hpp"
#include "TF_IDF.hpp"
#include "Cos.hpp"
#include "webPage.hpp"
#include "LoadFile.hpp"
#include <unordered_map>
#include <vector>
#include <set>
using std::unordered_map;
using std::vector;
using std::string;
using std::pair;
using std::set;

struct Result{
    string title;
    string link;
    string abstract;
};

class webQuery
{
public:
    webQuery(const string & sought,LoadFile * pload);
    ~webQuery();
    //计算查询词的权重值
    vector<double>& getQueryWordsWeightVector(); 
    //读取库文件
    void loadFile();
    //执行查询
    bool executeQuery(map<int,vector<double>> & resultMap);
    //vector<string> ---> string
    string getString(vector<string>::iterator it1,vector<string>::iterator it2){
        string str;
        while(it1 != it2){
            str += *it1;
            str += " ";
            ++it1;
        }
        return str;
    }
    //动态摘要和标题
    void dynamicAbstract(vector<pair<int,double>> & id);
    //返回查询结果
    void returnQuery();
    //测试
    /* void print(){ */
    /*     for(auto & elem : _ret){ */
    /*         cout << "title: " << elem.title << endl; */
    /*         cout << "link: " << elem.link << endl; */ 
    /*         cout << "abstract: " << elem.abstract; */
    /*     } */
    /* } */
    vector<Result> response(){
        return _ret;
    }
private:
    //需要查询的词
    string _sought;
    //结巴分词对象
    wordSegmentation _jieba;
    //查询词的权重值
    TF_IDF _weights;
    //加载库文件对象
    LoadFile * _pload;
    //网页库
    vector<pair<int,webPage>> & _pageLib;
    //网页偏移库
    unordered_map<int,pair<int,int>>  & _offsetLib;
    //倒排索引库
    unordered_map<string,set<pair<int,double>>>  &_invertIndexTable;
    //存放标题和动态摘要
    vector<Result> _ret;
};
#endif

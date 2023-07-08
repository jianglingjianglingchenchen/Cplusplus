#include "webQuery.hpp"
#include <utility>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <queue>
using std::make_pair;
using std::set_intersection;
using std::ifstream;
using std::istringstream;
using std::ofstream;
using std::getline;
using std::string;
/* string pageLibPath("ripepage.dat"); */
/* string offsetLibPath("offset.dat"); */
/* string invertIndexLibPath("invert.dat"); */
webQuery::webQuery(const string & sought,LoadFile  *pload)
: _sought(sought)
, _jieba()
, _weights(_jieba(_sought))
, _pload(pload)
, _pageLib(_pload->getPage())
, _offsetLib(_pload->getOffset())
, _invertIndexTable(_pload->getIndex())
{

}
webQuery::~webQuery(){

}
//计算查询词的权重值
vector<double>& webQuery::getQueryWordsWeightVector(){
    _weights.wordWeights();
    return _weights.getVec();
} 
//读取库文件
#if 0
void webQuery::loadFile(){
    //读取偏移库
    {
        ifstream ifs(offsetLibPath);
        string line;
        while(getline(ifs,line)){
            istringstream iss(line);
            string id,startPos,offset;
            iss >> id >> startPos >> offset;
            pair<int,int> tmp = make_pair(atoi(startPos.c_str()),atoi(offset.c_str()));
            pair<int,pair<int,int>> _offset = make_pair(atoi(id.c_str()),tmp);
            _offsetLib.insert(_offset);
        }
    }
    /* cout << "pianyiku: " << _offsetLib.size() << endl; */
    //读取网页库
    {
        ofstream ofs("wangyeku.dat");
        ifstream ifs(pageLibPath);
        /* for(auto & elem : _offsetLib){ */
        for(size_t i = 0;i < _offsetLib.size();++i){
            auto elem = _offsetLib[i+1];
            ifs.seekg(elem.first);
            char * buffer = new char[elem.second+1];
            ifs.read(buffer,elem.second);
            string str1(buffer,elem.second);
            ofs << str1;
            /* cout << str1 << endl; */
            webPage web;
            web.getDoc(str1);
            pair<int,webPage> tmp = make_pair(elem.first,web);
            _pageLib.push_back(tmp);
            delete []buffer;
        }
    }
    /* cout << "wangyeku: " << _pageLib.size() << endl; */
    //读取倒排索引库
    {
        ifstream ifs(invertIndexLibPath);
        string line;
        while(getline(ifs,line)){
            istringstream iss(line);
            string word;
            iss >> word;
            set<pair<int,double>> startAndWeight;
            string start,weight;
            while(iss >> start >> weight){
                pair<int,double> sw = make_pair(atoi(start.c_str()),std::stod(weight.c_str()));
                startAndWeight.insert(sw);
                start.clear();
                weight.clear();
            }
            pair<string,set<pair<int,double>>> tmp = make_pair(word,startAndWeight);
            _invertIndexTable.insert(tmp);
        }
        /* cout << "suoyinku: " << _invertIndexTable.size() << endl; */
    }
}
#endif
//执行查询
bool webQuery::executeQuery( map<int,vector<double>> & resultMap)
{
    //存放每个需要查询的词以及所对应的文章id
    vector<pair<string,vector<int>>> soughtAndID;
    for(auto & elem : _jieba.getVec()){
        /* cout << elem << " "; */
        vector<int> id;//用来存放每个string对应的id
        if(_invertIndexTable.find(elem) == _invertIndexTable.end()){
            return false;
        }else{
            //把每一个string对应的文章id取出来
            for(auto & elem1 : _invertIndexTable[elem]){
                id.push_back(elem1.first);
            }
        }
        pair<string,vector<int>> tmp_pair = make_pair(elem,id);
        soughtAndID.push_back(tmp_pair);
    }
    //取交集之前先对文章id进行排序
    for(auto & elem : soughtAndID){
        sort(elem.second.begin(),elem.second.end());
    }
    //对文章id取交集，intersection存放最后含有所有查询词的文章id
    vector<int> intersection = soughtAndID[0].second;//用第一个向量初始化intersection
    //循环取交集
    for(size_t idx = 1;idx < _jieba.getVec().size();++idx){
        vector<int> tmpIntersection;//临时向量
        set_intersection(intersection.begin(),intersection.end(),
                         soughtAndID[idx].second.begin(),soughtAndID[idx].second.end(),
                         std::back_inserter(tmpIntersection));
        //更新交集为临时交集
        intersection = tmpIntersection;
    }
    /* map<int,vector<double>> id_weight; */
    //记录不同文章中出现的string所对应的权重值
    for(auto & str : _jieba.getVec()){
        for(auto & elem : _invertIndexTable[str]){
            for(size_t i = 0;i < intersection.size();++i){
                if(elem.first == intersection[i]){
                    resultMap[elem.first].push_back(elem.second);
                }
            }
        }
    }
    return true;
}
//获取动态摘要和标题
void webQuery::dynamicAbstract(vector<pair<int,double>> & Id){
    
    string abstract;
    vector<string> sentences;
    for(int i = 0,articleCount = 5;articleCount != 0 && i < (int)Id.size();--articleCount,++i){
        Result ret;
        abstract.clear();
        sentences.clear();
        auto elem = _pageLib[Id[i].first - 1];
        string text = elem.second.getContent();
        //获取标题
        ret.title = elem.second.getTitle();
        //获取链接
        ret.link = elem.second.getLink();
        istringstream iss(text);
        string sentence;
        size_t pos = 0,nextPos = 0;
        while(nextPos != string::npos){
            nextPos = text.find_first_of("。", pos);
            sentence = text.substr(pos, nextPos - pos + 1);
            pos = nextPos + 1;
            sentences.push_back(sentence);
        }
        /* cout << "sentences.size: " << sentences.size() << endl; */
        //获取摘要
        for(auto & str : _jieba.getVec()){
            for(auto & elem : sentences){
                if(elem.find(str) != string::npos){
                    abstract += elem;
                    abstract += "\n";
                    break;
                }
            }
        }
        ret.abstract = abstract;
        _ret.push_back(ret);
    }
}
//返回查询结果
void webQuery::returnQuery(){
    //x向量组
    vector<double> x = getQueryWordsWeightVector(); 
    vector<pair<int,double>> id;//记录文章的id以及cos值
    map<int,vector<double>> id_map;
    if(executeQuery(id_map)){
        for(auto & elem : id_map){
            Cos cos(x,elem.second);
            /* cos.print(); */
            pair<int,double> tmp = make_pair(elem.first,cos.countCos());
            id.push_back(tmp);
        }
    }else{
        return;
    }
    sort(id.begin(),id.end(),[](const pair<int,double> & a,const pair<int,double> & b){
         return a.second > b.second;
         });
    dynamicAbstract(id);
}

/*************************************************************************
*File Name: Dictionary.cc
*Author: hongyabo
*mail: 1113445675@qq.com
*Created Time: 2023年07月05日 星期三 21时49分22秒
*Copyright (c) 2023 Yb H. All rights reserved
 ************************************************************************/
#include "Dictionary.h"

#include <fstream>
#include <sstream>

#include <iostream>

using std::ifstream;
using std::istringstream;

using std::cout;
using std::endl;

Dictionary *Dictionary::getInstance() {
    if(_instance == nullptr) {
        atexit(destroy);
        _instance = new Dictionary();
        _instance->initEnglish("dict.txt","index.txt");
        _instance->initChinese("dict_zh.txt", "index_zh.txt");
    }
    return _instance;
}

void Dictionary::destroy() {
    if(_instance)
    {
        delete _instance;
        _instance = nullptr;
    }
    
}

Dictionary *Dictionary::_instance = getInstance();

//加载文件初始化
//中文or英文？ 放在一起？
void Dictionary::initEnglish(const string &dictPath, const string &indexPath) {
    //打开文件
    ifstream ifsdict(dictPath);
    ifstream ifsindex(indexPath);

    string word;
    int frequence;
    int lineno;

    //读入词频文件
    int cnt = 0;
    while(ifsdict) {
        string line;
        getline(ifsdict, line);
        istringstream iss(line);
        iss >> word >> frequence;
        _dict.push_back(make_pair(word, frequence));
        /* cout << word << "," << frequence << endl; */
        ++cnt;
    }
    _off = cnt;

    
    //读入索引文件
    while(ifsindex) {
        string line;
        getline(ifsindex, line);
        istringstream iss(line);
        iss >> word;
        while(iss) {
            iss >> lineno;
            _indexTable[word].insert(lineno);
        }
        /* cout << word << ":"; */
        /* for (auto &x : _indexTable[word]) */
            /* cout << x << ","; */
        /* cout << endl; */
    }
    
    //关闭文件
    ifsdict.close();
    ifsindex.close();
}

void Dictionary::initChinese(const string &dictPath, const string &indexPath) {
    //打开文件
    ifstream ifsdict(dictPath);
    ifstream ifsindex(indexPath);

    string word;
    int frequence;
    int lineno;

    //读入词频文件
    while(ifsdict) {
        string line;
        getline(ifsdict, line);
        istringstream iss(line);
        iss >> word >> frequence;
        _dict.push_back(make_pair(word, frequence));
        /* cout << word << "," << frequence << endl; */
    }

    
    //读入索引文件
    while(ifsindex) {
        string line;
        getline(ifsindex, line);
        istringstream iss(line);
        iss >> word;
        while(iss) {
            iss >> lineno;
            _indexTable[word].insert(lineno);
        }
        /* cout << word << ":"; */
        /* for (auto &x : _indexTable[word]) */
        /*     cout << x << ","; */
        /* cout << endl; */
    }
    
    //关闭文件
    ifsdict.close();
    ifsindex.close();
}


set<int> Dictionary::queryIndex(const string &word) {
    return _indexTable[word];
}

//根据行号查
pair<string, int> Dictionary::queryEnglishWord(int idx) {
    return _dict[idx];    
}

pair<string, int> Dictionary::queryChineseWord(int idx) {
    /* cout << idx << endl; */
    /* cout << "off:" << _off << endl; */
    
    return _dict[idx + _off];    
}

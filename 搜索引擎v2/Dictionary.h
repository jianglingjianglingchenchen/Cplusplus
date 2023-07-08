/*************************************************************************
*File Name: Dictionary.h
*Author: hongyabo
*mail: 1113445675@qq.com
*Created Time: 2023年07月05日 星期三 21时44分01秒
*Copyright (c) 2023 Yb H. All rights reserved
 ************************************************************************/
#ifndef _DICTIONARY_H_
#define _DICTIONARY_H_

#include <vector>
#include <map>
#include <set>
#include <string>

using std::vector;
using std::map;
using std::pair;
using std::string;
using std::set;

//单例词典类
class Dictionary
{
public:
    //实例化函数
    static Dictionary *getInstance();

    static void destroy();


    //根据行号给出词的词频
    pair<string, int> queryEnglishWord(int);
    pair<string, int> queryChineseWord(int);

    //获取词的行号
    set<int> queryIndex(const string&);
private:
    //存词和词频
    vector<pair<string, int>> _dict;
    //存词和行号
    map<string, set<int>> _indexTable;
    //指向自己的静态指针
    static Dictionary *_instance;

    //中英文词典间偏移量
    int _off = 0;

    //构造析构私有化
    Dictionary(){}
    ~Dictionary(){}

    //禁止复制
    Dictionary(const Dictionary &) = delete;
    Dictionary &operator=(const Dictionary &) = delete;

    //读取文件构造词典
    void initEnglish(const string &, const string &);
    void initChinese(const string &, const string &);
};



#endif


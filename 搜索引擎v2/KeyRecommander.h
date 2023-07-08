/*************************************************************************
*File Name: KeyRecommander.h
*Author: hongyabo
*mail: 1113445675@qq.com
*Created Time: 2023年07月05日 星期三 21时04分06秒
*Copyright (c) 2023 Yb H. All rights reserved
 ************************************************************************/
#ifndef _KEY_RECOMMANDER_H_
#define _KEY_RECOMMANDER_H_

#include "CandidateResult.h"
#include "Dictionary.h"

#include <queue>
#include <string>
#include <map>
#include <set>

using std::string;
using std::pair;
using std::map;
using std::set;

//模板特化优先队列比较函数
//编辑距离 > 词频 > 字典序
namespace std{
template<>
struct greater<CandidateResult> {
    bool operator() (const CandidateResult &lhs, const CandidateResult &rhs) {
        int ld = lhs.getDistance();
        int rd = rhs.getDistance();
        if (ld > rd) { 
            return true;
        } else if (ld == rd) { // 编辑距离相等
            int lf = lhs.getFrequence();
            int rf = rhs.getFrequence();
            if (lf > rf) {
                return false;
            } else if (lf == rf) { // 词频相等
                return false;
            } else {
                return true;
            }
        } else {
            return false;
        }
        
    }
};
}


class KeyRecommander
{
public:
    KeyRecommander(const string&, Dictionary *); 
    ~KeyRecommander();

    //推荐函数(启动函数)
    //1.拆分词查询行号
    //2.行号取交集
    //3.根据行号取词:词和词频
    //4.放入队列
    void recommand();

    //返回最终结果（调用tcp）
    vector<string> response();
    

private:
    //待查询关键字
    string _sought;

    //存放候选关键字//设置比较函数
    std::priority_queue<CandidateResult, vector<CandidateResult>, std::greater<CandidateResult>> _queue;

    //候选词数量
    int _num = 5;

    //字典指针/引用
    Dictionary * _dict;

    //计算最短编辑距离
    int distanceEnglish(const string &);
    int distanceChinese(const string &);
    
    //最短编辑算法的状态矩阵
    int f[100][100];

    //根据行号查词频
    pair<string, int> queryEnglishWord(int);
    pair<string, int> queryChineseWord(int);

    //查行号
    set<int> queryIndex(const string &);
    

    //拆分单词放入vector
    vector<string> splitEnglish(const string &);
    vector<string> splitChinese(const string &);

    //判断中文
    bool isChinese(const string &);

};

#endif


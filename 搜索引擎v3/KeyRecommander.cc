/*************************************************************************
 *File Name: KeyRecommander.cc
 *Author: hongyabo
 *mail: 1113445675@qq.com
 *Created Time: 2023年07月06日 星期四 11时07分31秒
 *Copyright (c) 2023 Yb H. All rights reserved
 ************************************************************************/
#include "KeyRecommander.h"

#include <cstring>

#include <algorithm>
#include <iterator>

using std::min;

KeyRecommander::KeyRecommander (const string &word, Dictionary *dict) 
    : _sought(word)
    , _dict(dict) {

}
KeyRecommander::~KeyRecommander () {

}

//推荐函数(启动函数)
//1.拆分词查询行号
//2.行号取交集
//3.根据行号取词:词和词频
//4.放入队列
//5.返回结果
void KeyRecommander::recommand () {
    //  拆分单词放入vector
    vector<string> split;
    if (isChinese(_sought)) {
        split = splitChinese(_sought);
    } else {
        split = splitEnglish(_sought);
    }   
    
    /* for (auto &x : split) */
        /* cout << x << endl; */

    // 2. 查询行号
    vector<set<int>> lineno;
    for (auto &x : split) {
        lineno.push_back(queryIndex(x));
    }

    /* for (auto &x : lineno) */
    /* { */
    /*     for (auto &y : x) */
    /*     { */
    /*         cout << y << ","; */
    /*     } */
    /*     cout << endl; */
    /* } */


    // 3. 取行号交集
    set<int> intersection = lineno[0];
    if (!isChinese(_sought)) {
        for (int i = 1; i < lineno.size(); ++i) {
            set<int> tmp;
            std::set_intersection(intersection.begin(), intersection.end()
                                  , lineno[i].begin(), lineno[i].end()
                                  , std::inserter(tmp, tmp.begin()));
            intersection = tmp;
        }
    } else { // 中文取并集
        for (int i = 1; i < lineno.size(); ++i) {
            set<int> tmp;
            std::set_union(intersection.begin(), intersection.end()
                                  , lineno[i].begin(), lineno[i].end()
                                  , std::inserter(tmp, tmp.begin()));
            intersection = tmp;
        }

    }



    // 4. 根据行号取词（区分中英，中文要加数）放入队列
    if (isChinese(_sought)) {
        for (auto &x : intersection) {
            pair<string, int> word = queryChineseWord(x - 1);
            int dist = distanceChinese(word.first);
            CandidateResult can(word.first, word.second, dist);
            _queue.push(can);
        }

    } else {
        for (auto &x : intersection) {
            pair<string, int> word = queryEnglishWord(x - 1);
            int dist = distanceEnglish(word.first);
            CandidateResult can(word.first, word.second, dist);
            _queue.push(can);
        }
    }
}

//计算最短编辑距离
//英文和英文比，中文和中文比
//需要判断中英文
int KeyRecommander::distanceEnglish (const string &word) {
    //清空状态矩阵
    memset(f, 0, sizeof(f));     

    int n = word.size();
    int m = _sought.size();

    const char *psought = _sought.c_str();
    const char *pword = word.c_str();

    //初始化状态矩阵
    for (int i = 0; i <= n; ++i)
        f[i][0] = i;
    for (int i = 0; i <= m; ++i)
        f[0][i] = i;

    //计算最短编辑距离
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            f[i][j] = min(f[i][j - 1] + 1, f[i - 1][j] + 1);
            if (pword[i - 1] == psought[j - 1])
                f[i][j] = min(f[i][j], f[i - 1][j - 1]);
            else
                f[i][j] = min(f[i][j], f[i - 1][j - 1] + 1);
        }
    }
    /* cout << f[n][m] << endl; */
    return f[n][m];
}
int KeyRecommander::distanceChinese (const string &word) {
    //
    memset(f, 0, sizeof(f));     

    int n = word.size() / 3;
    int m = _sought.size() / 3;

    const char *psought = _sought.c_str();
    const char *pword = word.c_str();

    for (int i = 0; i <= n; ++i)
        f[i][0] = i;
    for (int i = 0; i <= m; ++i)
        f[0][i] = i;

    for (int i = 1; i <= n; ++i) {
            int p = (i - 1) * 3;
        for (int j = 1; j <= m; ++j) {
            int q = (j - 1) * 3;
            f[i][j] = min(f[i][j - 1] + 1, f[i - 1][j] + 1);
            if (pword[p] == psought[q] && pword[p + 1] == psought[q + 1] && pword[p + 2] == psought[q + 2])
                f[i][j] = min(f[i][j], f[i - 1][j - 1]);
            else
                f[i][j] = min(f[i][j], f[i - 1][j - 1] + 1);
        }
    }
    /* cout << f[n][m] << endl; */
    return f[n][m];
}

//查词频
pair<string, int> KeyRecommander::queryEnglishWord (int idx) {
    return _dict->queryEnglishWord(idx);
}
pair<string, int> KeyRecommander::queryChineseWord (int idx) {
    return _dict->queryChineseWord(idx);
}
//查行号
set<int> KeyRecommander::queryIndex (const string &word) {
    return _dict->queryIndex(word);
}

//返回最终结果（调用tcp）
vector<string> KeyRecommander::response () {
    vector<string> result;
    int size;
    if (_queue.size() >= _num) {
        size = _num;
    } else {
        size = _queue.size();
    }

    while (size--) {
        string word = _queue.top().getWord();
        _queue.pop();
        result.push_back(word);
    }
    return result;
}

bool KeyRecommander::isChinese(const string &word) {
    const char *p = word.c_str();
    if((unsigned char)*p > 0x7f)
        return true;
    else
        return false;
}

vector<string> KeyRecommander::splitChinese (const string &word) {
    vector<string> result;
    for (int i = 0; i < word.size() / 3; ++i)
    {
        string character = word.substr(i * 3, 3); 
        result.push_back(character);
    }
    return result;
}

vector<string> KeyRecommander::splitEnglish (const string &word) {
    vector<string> result;
    for (int i = 0; i < word.size(); ++i)
    {
        string character = word.substr(i, 1); 
        result.push_back(character);
    }
    return result;
}

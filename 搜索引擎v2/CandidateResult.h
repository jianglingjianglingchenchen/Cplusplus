/*************************************************************************
*File Name: CandidateResult.h
*Author: hongyabo
*mail: 1113445675@qq.com
*Created Time: 2023年07月05日 星期三 21时18分04秒
*Copyright (c) 2023 Yb H. All rights reserved
 ************************************************************************/
#ifndef _CANDIDATE_RESULT_H_
#define _CANDIDATE_RESULT_H_

#include <string>
#include <iostream>

using std::string;
using std::cout;
using std::endl;

class CandidateResult
{
public:
    CandidateResult(string, int, int);
    ~CandidateResult();

    int getDistance () const;
    int getFrequence () const;
    string getWord () const;

private:
    string _word;
    int _frequence;
    int _distance;

};

#endif


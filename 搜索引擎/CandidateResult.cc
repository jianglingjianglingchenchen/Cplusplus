/*************************************************************************
*File Name: CandidateResult.cc
*Author: hongyabo
*mail: 1113445675@qq.com
*Created Time: 2023年07月05日 星期三 21时21分34秒
*Copyright (c) 2023 Yb H. All rights reserved
 ************************************************************************/
#include "CandidateResult.h"

CandidateResult::CandidateResult(string word, int frequence, int distance) 
    : _word(word)
    , _frequence(frequence)
    , _distance(distance){

}
CandidateResult::~CandidateResult() {

}

int CandidateResult::getDistance () const {
    return _distance;
}

int CandidateResult::getFrequence() const {
    return _frequence;
}

string CandidateResult::getWord() const {
    return _word;
}

#ifndef __WORDSEGMENTATION_HPP__
#define __WORDSEGMENTATION_HPP__

#include "cppjieba/Jieba.hpp"
#include <iostream>
#include <string>
#include <vector>
using std::endl;
using std::cout;
using std::string;
using std::vector;

const char* const DICT_PATH = "./cppjieba/dict/jieba.dict.utf8";
const char* const HMM_PATH = "./cppjieba/dict/hmm_model.utf8";
const char* const USER_DICT_PATH = "./cppjieba/dict/user.dict.utf8";
const char* const IDF_PATH = "./cppjieba/dict/idf.utf8";
const char* const STOP_WORD_PATH = "./cppjieba/dict/stop_words.utf8";

class wordSegmentation
{
public:
    wordSegmentation()
    : _jieba(DICT_PATH,HMM_PATH,USER_DICT_PATH,IDF_PATH,STOP_WORD_PATH)
    {

    }
    ~wordSegmentation(){

    }
    vector<string> & operator()(const string str){
        _jieba.Cut(str,_result,true);
        return _result;
    }
    vector<string> & getVec(){
        return _result;
    }
private:
    cppjieba::Jieba _jieba;
    vector<string> _result;
};
#endif


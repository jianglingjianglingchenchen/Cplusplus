#ifndef __TF_IDF_HPP__
#define __TF_IDF_HPP__
#include <map>
#include <vector>
#include <iostream>
using std::map;
using std::string;
using std::vector;
class TF_IDF
{
public:
    TF_IDF(const vector<string> & file);
    ~TF_IDF();
    void wordWeights();
    void print();
    vector<double> & getVec(){
        return _weight;
    }
private:
    void wordSum();
private:
    vector<string> _file;
    map<string,int> _dict;
    vector<double> _weight;
};
#endif


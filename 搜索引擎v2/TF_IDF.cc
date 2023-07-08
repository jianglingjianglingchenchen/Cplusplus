#include "TF_IDF.hpp"
#include <math.h>
TF_IDF::TF_IDF(const vector<string> & file)
: _file(file)
{

}
TF_IDF::~TF_IDF(){

}
void TF_IDF::wordSum(){
    for(auto & elem : _file){
        ++_dict[elem];
    }
}
void TF_IDF::wordWeights(){
    double sum = 0;
    wordSum();
    for(auto & elem : _dict){
        sum += pow(elem.second,2);
    }
    sum = sqrt(sum);
    for(auto & elem : _dict){
        _weight.push_back((double)(elem.second/sum));
    }
}

void TF_IDF::print(){
    for(auto & elem : _dict){
        std::cout << elem.first << ":" << elem.second << " ";
    }
    std::cout << std::endl;
    for(auto & elem : _weight){
        std::cout << elem << " ";
    }
    std::cout << std::endl;
}


#include "Cos.hpp"
#include <math.h>
Cos::Cos(const vector<double> & vec1,const vector<double> & vec2)
: _vec1(vec1)
, _vec2(vec2)
{

}
Cos::~Cos(){

}
double Cos::countCos(){
    double magnitude1 = magnitude(_vec1);
    double magnitude2 = magnitude(_vec2);
    return multiply() / (magnitude1 * magnitude2);
}
double Cos::magnitude(const vector<double> & vec){
    double sum = 0;
    for(auto & data : vec){
        sum += pow(data,2);
    }
    return sqrt(sum);
}
double Cos::multiply(){
    double sum = 0;
    for(size_t i = 0;i < _vec1.size();++i){
        sum += _vec1[i] * _vec2[i];
    }
    return sum;
}

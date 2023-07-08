#ifndef __COS_HPP__
#define __COS_HPP__
#include <vector>
#include <iostream>
#include <algorithm>
using std::vector;
class Cos
{
public:
    Cos(const vector<double> & vec1,const vector<double> & vec2);
    ~Cos();
    double countCos();
    double magnitude(const vector<double> & vec);
    double multiply();
    /* void print(){ */
    /*     for_each(_vec2.begin(),_vec2.end(),[](double a){ */
    /*              std::cout << a << " "; */
    /*              }); */
    /* } */
private:
    vector<double> _vec1;
    vector<double> _vec2;
};
#endif


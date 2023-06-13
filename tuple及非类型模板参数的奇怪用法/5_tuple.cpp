#include <iostream>
#include <tuple>
using namespace std;

tuple<int,string,double> retTest(){
    return tuple<int,string,double>(77,"luka",23.77);
}

int main()
{
    tuple<int,string,double> x = retTest();
    cout << get<0>(x) << endl;
    cout << get<1>(x) << endl;
    cout << get<2>(x) << endl;
    return 0;
}


#include "pimpl.hpp"
#include <iostream>
using std::cout;
using std::endl;

class Pimpl::PimplImpl{
public:
    PimplImpl(const int data = 0):_data(data){}
    void display(){ cout << "data:" << _data << endl; }

private:
    int _data;
};

Pimpl::Pimpl(int x):_p(new PimplImpl(x)){
    cout << "Pimpl()" << endl;
}

Pimpl::~Pimpl(){
    if(_p){
        delete _p;
        _p = nullptr;
    }
}

void Pimpl::display(){
    _p->display();
}

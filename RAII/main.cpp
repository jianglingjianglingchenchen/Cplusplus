#include "mystring.hpp"
#include <vector>
#include <stdio.h>

template <class Type>
struct Default{
    void operator()(Type* p) const{
        delete p;
    }
};

class CloseFile{
public:
    void operator()(FILE* p){
        fclose(p);
    }
};

template <class T = int,class DefalultDel = Default<T>>
class RAII{
public:
    RAII(T* p):p(p){}
    ~RAII(){
        if(p){
            del(p);
            p = nullptr;
        }
    }

    T* operator->(){ return p; }
    T& operator*(){ return *p; }
    T* get(){ return p; }
private:
    T* p;
    DefalultDel del;;
};

String test(){
    /* String tmp("asd"); */
    /* return tmp; */
    return String("asd");
}

void test0(){
    RAII<String> tmp(new String("hello\n"));
    cout << *(tmp.get()) << endl;
    cout << *tmp << endl;
}

void test1(){
    RAII<FILE,CloseFile> tmp(fopen("test.txt","a+"));
    fwrite("hello\n",1,6,tmp.get());
}

void test2(){
    RAII<> tmp(new int(77)); 
    cout << *tmp << endl;
}

int main(void){
    test2();
    return 0;
}

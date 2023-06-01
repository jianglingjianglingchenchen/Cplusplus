#include <iostream>
#include <string.h>
using std::cout;
using std::endl;

class String{
public:
    String()
    :_pstr(new char[5]() + 4){
        *_pstr = '\0';
        initRefCount();
    }
    explicit
    String(const char* str)
    :_pstr(new char[strlen(str)+5]() + 4){
        memcpy(_pstr,str,strlen(str)+1);
        initRefCount();
    }
    String(const String& str)
    :_pstr(str._pstr){
        increaseRefCount();
    }
    ~String(){
        release();
    }
    String& operator=(const String& str){
        release();
        this->_pstr = str._pstr;
        increaseRefCount();
        return *this;
    }
    String& operator=(const char* str){
        release();
        _pstr = new char[strlen(str)+5]() + 4;
        memcpy(_pstr,str,strlen(str)+1);
        initRefCount();
        return *this;
    }
private:
    class CharProxy{
    public:
        CharProxy(int index,String& self)
        :_index(index),_self(self){}

        char& operator=(char x);
        friend std::ostream& operator<<(std::ostream&,const CharProxy&);//这里设为友元是为了让'<<'函数可以拿到CharProxy的数据成员

        //另外一种读操作的另外一种方式
        //operator char(){
        //    return _self._pstr[_index];
        //}

    private:
        int _index;
        String& _self;
    };
public:
    friend std::ostream& operator<<(std::ostream&,const CharProxy&);//这里设为友元是因为CharProxy的私有类
    //重载下标运算符时，返回一个代理类，让代理类通过重载'='和'<<'运算符的时候去区分读写行为
    CharProxy operator[](const int index){
        return CharProxy(index,*this);
    }

    friend std::ostream& operator<<(std::ostream& ost,const String& str);

    char* returnP(){return _pstr;}
    void printString(){
        cout << _pstr << endl;
    }
    void displayRefCount(){
        int* tmp = (int*)(_pstr-4);
        cout << "refCount = " << *tmp << endl;
    }
private:
    void release(){
        decreaseRefCount();
        int* tmp = (int*)(_pstr-4);
        if(*tmp <= 0){
            char* p = _pstr - 4;
            delete []p;
            _pstr = nullptr;
        }
    }
    void initRefCount(){
        int* tmp = (int*)(_pstr-4);
        *tmp = 1;
    }
    void increaseRefCount(){
        int* tmp = (int*)(_pstr-4);
        ++*tmp;
    }
    void decreaseRefCount(){
        int* tmp = (int*)(_pstr-4);
        --*tmp;
    }
private:
    char* _pstr;

};




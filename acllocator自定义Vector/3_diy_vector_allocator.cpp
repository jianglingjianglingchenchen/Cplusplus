#include <iostream>
#include <string.h>
#include <memory>
#include <algorithm>
using namespace std;

template<typename T>
class Vector
{
public:
    using iiterator = T*;
    iiterator begin();
    iiterator end();
    Vector();
    ~Vector();
    void push_back(const T &);
    void pop_back();
    int size();
    int capacity();
private:
    void reallocate();//重新分配内存,动态扩容要用的
private:
    static std::allocator<T> _alloc;
    T *_start;                 //指向数组中的第一个元素
    T *_finish;                //指向最后一个实际元素之后的那个元素
    T *_end_of_storage;        //指向数组本身之后的位置
};

template <class T>
void Vector<T>::pop_back(){
    if(size()){
        _alloc.destroy(--_finish);
    }
}

template <class T>
T* Vector<T>::begin(){
    return _start;
}

template <class T>
T* Vector<T>::end(){
    return _finish;
}

template <class T>
int Vector<T>::capacity(){
    return (int)(_end_of_storage - _start);
}

template <class T>
Vector<T>::~Vector(){
    cout << "~Vector()" << endl;
    if(_start){
        for(int i = 0;i < size();++i){
            _alloc.destroy(_start+i);
        }
        _alloc.deallocate(_start,capacity());
    }
}

template <class T>
int Vector<T>::size(){
    return (int)(_finish - _start);
}

template <class T>
allocator<T> Vector<T>::_alloc;

template <class T>
Vector<T>::Vector()
:_start(nullptr),_finish(nullptr),_end_of_storage(nullptr){}

template <class T>
void Vector<T>::reallocate(){//只负责扩容
    //直接扩容，或者是最开始的第一个元素
    int size_to_get = (_start == nullptr)? 1 : 2 * capacity();
    int sizex = size();
    T* pArr = _alloc.allocate(size_to_get);
    if(pArr == nullptr){
        cerr << "allocate failed!" << endl;
        return ;
    }
    memset(pArr,0,size_to_get);
    if(size_to_get != 1){
        //注意memcpy的最后一个参数是总共要复制的字节数，capacity()要乘以sizeof(T)
        memcpy(pArr,_start,capacity() * sizeof(T));//是可以使用memcpy的，数据的底层都是01形式的二进制码
        /* uninitialized_copy(_start,_finish,pArr); */
        /* copy(_start,_finish,pArr); */
        while(_finish != _start){
            _alloc.destroy(--_finish);
        }
        _alloc.deallocate(_start,capacity());
    }
    _start = pArr;
    _finish = pArr + sizex;
    _end_of_storage = pArr + size_to_get;
}

template <class T>
void Vector<T>::push_back(const T& val){
    //如果是放入第一个元素，则只申请一个元素大小的空间
    //如果是满了需要扩容，则直接申请现在元素个数的两倍的空间
    if(size() == capacity()){
        cout << "kuorongzhiqian:" << "\n"
            << "size:" << size() <<"\n"
            << "capacity:" << capacity() << endl;
        reallocate();//只是进行了扩容，没有进行对象的压栈
    }
    if(size() < capacity()){//扩容成功才进行压栈
        _alloc.construct(_finish++,val);
    }
}

int main(void)
{
    Vector<int> t;
    t.push_back(11);
    cout << "size:" << t.size() << endl;
    cout << "capacity:" << t.capacity() << endl;
    t.push_back(23);
    cout << "size:" << t.size() << endl;
    cout << "capacity:" << t.capacity() << endl;
    t.push_back(23);
    cout << "size:" << t.size() << endl;
    cout << "capacity:" << t.capacity() << endl;
    t.push_back(23);
    cout << "size:" << t.size() << endl;
    cout << "capacity:" << t.capacity() << endl;
    t.push_back(23);
    cout << "size:" << t.size() << endl;
    cout << "capacity:" << t.capacity() << endl;

    for(auto& x : t)
        cout << x << " ";
    cout << endl;
    t.pop_back();
    for(auto& x : t)
        cout << x << " ";
    cout << endl;

    return 0;
}


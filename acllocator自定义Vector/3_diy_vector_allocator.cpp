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
    iiterator begin() const;
    iiterator end() const;
    Vector();
    ~Vector();
    void push_back(const T &);
    void pop_back();
    int size() const;
    int capacity() const;
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
T* Vector<T>::begin() const{
    return _start;
}

template <class T>
T* Vector<T>::end() const{//要优先提供const版本，否则如果容器被const修饰，就无法使用迭代器就行遍历
    return _finish;
}

template <class T>
int Vector<T>::capacity() const{
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
int Vector<T>::size() const{
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
        reallocate();//只是进行了扩容，没有进行对象的压栈
    }
    if(size() < capacity()){//扩容成功才进行压栈
        _alloc.construct(_finish++,val);
    }
}

class Point{
public:
    Point(const int& x,const int& y):_x(x),_y(y){}
    friend ostream& operator<<(ostream& os,const Point& rhs);
private:
    int _x,_y;
};

ostream& operator<<(ostream& os,const Point& rhs){
    os << rhs._x << "," << rhs._y;
    return os;
}

template <class Container>
void printCon(const Container& con){//这里加上const会报错
    for(auto& x : con)
        cout << x << " ";
    cout << endl;
}

template <class Container>
void printCapacity(const Container& con){
    cout << "con.size:" << con.size() << endl;
    cout << "con.capacity:" << con.capacity() << endl;
}

int main(void)
{
    Vector<Point> vec;
    vec.push_back({1,2});
    printCapacity(vec);
    vec.push_back({1,7});
    printCapacity(vec);
    vec.push_back({1,90});
    printCapacity(vec);
    vec.push_back({23,2});
    printCapacity(vec);
    vec.push_back({1,77});
    printCapacity(vec);
    vec.push_back({1,2});
    printCapacity(vec);
    vec.push_back({100,2});
    printCapacity(vec);
    
    printCon(vec);
    return 0;
}


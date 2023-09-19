#include <iostream>
#include <mutex>
using namespace std;

template <class T>
class SharedPtr{
public:
    SharedPtr(T* ptr = nullptr)
    :_ptr(ptr)
    ,_prefCount(new int(1))
    ,_pmutex(new mutex)
    {}

    ~SharedPtr(){
        release();
    }

    SharedPtr(const SharedPtr<T>& tmp)
    :_ptr(tmp._ptr)
    ,_prefCount(tmp._prefCount)
    ,_pmutex(tmp._pmutex){
        addRefCount();
    }

    SharedPtr<T>& operator=(const SharedPtr<T>& tmp){
        //防止自赋值的发生
        if(_ptr != tmp._ptr){
            release();//释放旧的托管资源
            _ptr = tmp._ptr;
            _prefCount = tmp._prefCount;
            _pmutex = tmp._pmutex;
            addRefCount();//这里记住要增加一次引用计数
        }
        return *this;
    } 

    int useCount(){
        return *_prefCount;
    }

    T* get(){
        return _ptr;
    }

    T& operator*(){
        return *_ptr;
    }

    T* operator->(){
        return _ptr;
    }
private:
    void addRefCount(){
        _pmutex->lock();
        ++*_prefCount;
        _pmutex->unlock();
    }
    void release(){
        bool deleFlag = false;//用于控制mutex的释放
        _pmutex->lock();
        if(--*_prefCount == 0){
            delete _prefCount;
            delete _ptr;
            deleFlag = true;
        }
        _pmutex->unlock();//mutex只是为了让多线程环境下，各线程互斥访问refCount，当需要释放时，mutex需要最后释放
        if(deleFlag){
            delete _pmutex;
        }
    }
private:
    T* _ptr;
    int* _prefCount;//必须放在堆空间，否则不可能让各个智能指针对象都拿到同一个引用计数
    mutex* _pmutex;
};

class Test{
public:
    Test(const string& info)
    :_info(info){

    }

    void printInfo(){
        cout << _info << endl;
    }
private:
    string _info;
};

template <class T>
void testRefCount(SharedPtr<T> tmp){
    cout << tmp.useCount() << endl;
    (*tmp).printInfo();
}

int main()
{
    SharedPtr<Test> pTest(new Test("jordan"));
    cout << pTest.useCount() << endl;
    pTest->printInfo();
    testRefCount(pTest);
    cout << pTest.useCount() << endl;
    return 0;
}


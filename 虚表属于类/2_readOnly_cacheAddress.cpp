#include <iostream>
using namespace std;

class Base{
    virtual void display(){
        cout << "display" << endl;
    }
};

void ttest(){
    cout << "tt" << endl;
}

int main()
{
    Base b1;
    Base b2;
    long* p = (long*)(&b1);
    long* o = (long*)(&b2);
    long* a1 = (long*)(p[0]);
    long* a2 = (long*)(o[0]);
    //虚表是属于类的，一个类的所有对象共享一张虚表,每个对象的vfptr指向同一个地址
    cout << "以下是虚表的地址" << endl;
    printf("%p\n%p\n",a1,a2);
    long* pFunc = (long*)(&ttest);
    cout << "以下是代码段的地址" << endl;
    printf("%p\n",pFunc);
    static int xx = 23;
    cout << "以下是文字常量区的地址" << endl;
    printf("%p\n",&xx);
    return 0;
}


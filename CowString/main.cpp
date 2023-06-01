#include <iostream>
#include <string.h>
#include "COWstring.hpp"
using std::cout;
using std::endl;

int main()
{
    String s1("hello");
    cout << s1[0] << endl;
    String s2 = s1;
    s1.printString();
    s2.printString();
    s1.displayRefCount();
    s2.displayRefCount();
    s2[0] = 'H';
    s1.printString();
    s2.printString();
    s1.displayRefCount();
    s2.displayRefCount();
    s1[0] = 'A';
    s1.printString();
    s2.printString();
    cout << s1 << "\n" << s2 << endl;

    return 0;
}


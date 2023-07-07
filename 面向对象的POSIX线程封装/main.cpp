#include "Thread.hpp"
#include <iostream>
#include <unistd.h>
using namespace std;

class MyThread
:public Thread{
private:
    void run() override{
        cout << "hello world" << endl;
        sleep(2);
    }
};

void test(){
    MyThread tid;
    tid.start();
    tid.start();
    tid.join();
}

int main(void){
    test();
    return 0;
}

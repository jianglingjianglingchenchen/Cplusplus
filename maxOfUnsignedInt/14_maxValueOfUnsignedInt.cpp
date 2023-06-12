#include <iostream>
using namespace std;

int main()
{
    unsigned int x = -1;//此时x的取值是unsigned int所能取的最大值
    for(size_t i = 9;i > 0;i -= 2){//这样就无法退出这个循环了，因为size_t是无符号类型
        cout << i << " " ;
    }
    cout << endl;
    return 0;
}


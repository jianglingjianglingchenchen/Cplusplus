#include <iostream>
using namespace std;

template<int N>
int getArraySize(int (&arr)[N]) {
    return N;
}

template <int x = 10>
int retX(){
    /* x = 100; */
    return x;
}

int main()
{
    int arr[] = {1,2,3,4,5,6};
    cout << getArraySize(arr) << endl;

    cout << retX<77>() << endl;
    return 0;
}


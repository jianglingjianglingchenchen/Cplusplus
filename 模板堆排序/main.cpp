#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

template <typename T, typename Compare = std::less<T>>
class HeapSort
{
public:
    HeapSort(T* arr, size_t size, Compare com);
    void heapAdjust(size_t, size_t, Compare& com);
    void sort(Compare& com);
    void print();
private:
    vector<T> _vec;
};
template <class T, class Compare>
void HeapSort<T, Compare>::print() {
    for (auto& x : _vec) {
        cout << x << " ";
    }
    cout << endl;
}

template <class T, class Compare>
HeapSort<T, Compare>::HeapSort(T* arr, size_t size, Compare com)
    :_vec(arr, arr + size) {
}

//调整堆的函数
template <class T, class Compare>
void HeapSort<T, Compare>::heapAdjust(size_t index, size_t size, Compare& com) {
    if ((index * 2) + 1 >= size) return;
    size_t lchild = (index * 2) + 1;
    size_t rchild = (index * 2) + 2;
    while (true) {
        int largerChildIndex = index;
        //有左孩子且左孩子的值比当前节点的值大
        if ((index * 2) + 1 < size && com(_vec[(index * 2) + 1], _vec[largerChildIndex]))
            largerChildIndex = (index * 2) + 1;
        if ((index * 2) + 2 < size && com(_vec[(index * 2) + 2], _vec[largerChildIndex]))
            largerChildIndex = (index * 2) + 2;
        if (largerChildIndex != index) {
            swap(_vec[largerChildIndex], _vec[index]);
            index = largerChildIndex;
        }
        else
            break;
    }
    heapAdjust(lchild, size, com);
    heapAdjust(rchild, size, com);
}

template <class T, class Compare>
void HeapSort<T, Compare>::sort(Compare& com) {
    for (int i = 0; i < log2(_vec.size()+1); ++i)
        heapAdjust(0, _vec.size(), com);
    for (int i = 0,tail = _vec.size() - 1; i < tail; --tail) {
        swap(_vec[tail], _vec[i]);
        heapAdjust(i, tail, com);
    }
}

int main()
{
    vector<int> t = { 1,23,34,56,76,77,79,81,23,90,235,325,1022 };
    //vector<int> t = { 1,2,3,5,79 };
    HeapSort<int, greater<int>> test(t.data(), t.size(), greater<int>());
    greater<int> com;
    test.sort(com);
    test.print();
    return 0;
}


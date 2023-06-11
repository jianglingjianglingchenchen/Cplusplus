/* program3 */
#include <iostream>
using std::cout;
using std::endl;

template <typename T>
class ManyFriend
{
private:
    T item;
public:
    ManyFriend(const T & i):item(i){}
    //unbound template friend declation
    template <typename C,typename D> friend void show(C &,D &);
};

class Test{
public:
    Test(const double x):item(x){}
    template <typename C,typename D> friend void show(C &,D &);
private:
    double item;
};

template <typename C,typename D> void show(C & c,D & d)
{
    cout<<c.item<<", "<<d.item<<endl;
}

int main()
{
    ManyFriend<int> hfi1(10);
    ManyFriend<int> hfi2(20);
    ManyFriend<double> hfdb(15.5);
    Test t1(23.77);
    cout<<"hfi1, hfi2: ";
    show(hfi1,hfi2);//generate show<ManyFriend<int> &,ManyFriend<int> &>(ManyFriend<int> & c,ManyFriend<int> & d)
    cout<<"hfdb, hfi2: ";
    show(hfdb,hfi2);//generate show<MantyFriend<double> &,ManyFriend<int> &>(ManyFriend<double> & c,ManyFriend<int> & d)
    cout<<"t1, hfi2: ";
    show(t1,hfi2);//generate show<MantyFriend<double> &,ManyFriend<int> &>(ManyFriend<double> & c,ManyFriend<int> & d)

    return 0;
}


/* program2 */
#include <iostream>
using std::cout;
using std::endl;

//template prototypes
template <typename T> void counts();
template <typename T> void report(T &);

//template class
template <typename TT>
class HasFriendTem
{
private:
    TT item;
    static int cnts;
public:
    HasFriendTem(const TT & i):item(i){cnts++;}
    ~HasFriendTem(){cnts--;}
    friend void counts<TT>();
    friend void report<>(HasFriendTem<TT> &);
};

template <typename TT>
int HasFriendTem<TT>::cnts=0;

//template friend functions definitions
template <typename T>
void counts()
{
    cout<<"template size:"<<sizeof(HasFriendTem<T>)<<";";
    cout<<"template counts():"<<HasFriendTem<T>::cnts<<endl;
}

template <typename T>
void report(T& hf)
{
    cout<<hf.item<<endl;
}

int main()
{
    counts<int>();
    HasFriendTem<int> hfi1(10);
    HasFriendTem<int> hfi2(20);
    HasFriendTem<double> hfdb(15.5);
    report(hfi1);//generate report(HasFriendTem<int> &)
    report(hfi2);
    report(hfdb);//generate report(HasFriendTem<double> &)
    cout<<"counts<int>() output:\n";
    counts<int>();
    cout<<"counts<double() output:\n";
    counts<double>();

    return 0;
}


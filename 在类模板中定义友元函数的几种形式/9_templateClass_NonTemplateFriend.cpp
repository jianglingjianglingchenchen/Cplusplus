/* program1 */
#include <iostream>
using std::cout;
using std::endl;

template <typename T>
class HasFriend
{
private:
    T item;
    static int cnts;
public:
    HasFriend(const T& i):item(i){cnts++;}
    ~HasFriend(){cnts--;}
    friend void counts();
    friend void report(HasFriend<T>&);//template class parameter
};

//each specialization has its own static data number
template <typename T>
int HasFriend<T>::cnts=0;

//non-template friend to all HasFriend<T> classes
void counts()
{
    cout<<"int count"<<HasFriend<int>::cnts<<";";
    cout<<"double count"<<HasFriend<double>::cnts<<endl;
}

//non-template friend to the HasFriend<int> class
void report(HasFriend<int> & hf)
{
    cout<<"HasFriend<int>:"<<hf.item<<endl;
}

//non-template friend to the HasFriend<double> class
void report(HasFriend<double> & hf)
{
    cout<<"HasFriend<double>:"<<hf.item<<endl;
}

int main()
{
    cout<<"No objects declared:";
    counts();
    HasFriend<int> hfi1(10);
    cout<<"After hfi1 declared:";
    counts();
    HasFriend<int> hfi2(20);
    cout<<"After hfi2 declared:";
    counts();
    HasFriend<double> hfdb(15.5);
    cout<<"After hfdb declared:";
    counts();
    report(hfi1);
    report(hfi2);
    report(hfdb);

    return 0;
}

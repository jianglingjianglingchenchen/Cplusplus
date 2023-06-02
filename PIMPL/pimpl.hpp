
class Pimpl{
public:
    Pimpl(int);
    ~Pimpl();
    void display();
private:
    class PimplImpl;
    PimplImpl* _p;
};

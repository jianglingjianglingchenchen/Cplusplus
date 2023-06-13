#include <iostream>
using namespace std;

class String
{
public:
	String();
	String(const char* pstr);
	String(const String& rhs);
    String(String&& rhs);
	String& operator=(const String& rhs);
    String& operator=(String&& rhs);
	~String();
	void print();
	size_t length() const;
	const char* c_str() const;
	void printAddr() const;
    friend ostream& operator<<(ostream&,const String&);
private:
	char* _pstr;
};




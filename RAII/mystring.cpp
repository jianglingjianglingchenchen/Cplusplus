#include "mystring.hpp"
#include <string.h>

String::String()
:_pstr(nullptr){
	
}

String::String(const char* pstr)
	: _pstr(new char[strlen(pstr) + 1]()) {
	memcpy(_pstr, pstr, strlen(pstr) + 1);
}

String::String(const String& rhs)
:_pstr(new char[strlen(rhs._pstr) + 1]()){
	cout << "String(const String&)" << endl;
	memcpy(_pstr, rhs._pstr, strlen(rhs._pstr) + 1);
}

String::~String() {
	if (_pstr) {
		delete[]_pstr;
		_pstr = nullptr;
	}
}

String& String::operator=(const String& rhs) {
	if (this != &rhs) {
		if (_pstr) {
			delete[]_pstr;
		}
		_pstr = new char[strlen(rhs._pstr) + 1]();
		memcpy(_pstr, rhs._pstr, strlen(rhs._pstr) + 1);
	}
	return *this;
}

void String::print() {
	if (_pstr) {
		cout << "pstr:" << _pstr << "\n";
	}
}

size_t String::length() const{
	if (!_pstr)
		return 0;
	else
		return strlen(_pstr);
}

const char* String::c_str() const {
	if (_pstr)
		return _pstr;
	else
		return nullptr;
}

void String::printAddr() const {
	printf("%p\n", _pstr);//_pstr是new出来
	cout << "&pstr:" << &_pstr << "\n";
}

//这是移动构造函数
String::String(String&& rhs)
:_pstr(rhs._pstr){
    rhs._pstr = nullptr;
    cout << "String(String&&)" << endl;
}

String& String::operator=(String&& rhs){
    if(this == &rhs)
        return *this;
    /* if(_pstr != rhs._pstr && _pstr){ */
    delete []_pstr;
     _pstr = rhs._pstr;
    rhs._pstr = nullptr;
    /* } */
    cout << "operator=(String&&)" << endl;
    return *this;
}

ostream& operator<<(ostream& os,const String& str){
    os << str._pstr;
    return os;
}

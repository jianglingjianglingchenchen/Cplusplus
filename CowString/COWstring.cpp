#include "COWstring.hpp"

std::ostream& operator<<(std::ostream& ost,const String& str){
    ost << str._pstr;
    return ost;
}

std::ostream& operator<<(std::ostream& ost,const String::CharProxy& str){
    ost << str._self._pstr[str._index];
    return ost;
}


char& String::CharProxy::operator=(char x){
    int* tmp = (int*)(_self._pstr-4);
    if(_index > strlen(_self._pstr) || _index < 0){
        static char nullchar = '\0'; 
        return nullchar;
    }
    else{
        if(*tmp > 1){
            _self.decreaseRefCount();
            char* buf = new char[strlen(_self._pstr)+5]() + 4;
            strcpy(buf,_self._pstr);
            _self._pstr = buf;
            _self.initRefCount();
        }
    }
    _self._pstr[_index] = x;
    return _self._pstr[_index]; 
}

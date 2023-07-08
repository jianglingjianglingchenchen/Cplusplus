#include "Configure.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
using std::ifstream;
using std::istringstream;
using std::cout;
using std::endl;
/* Configure * Configure::_pInstance = Configure::getInstance("configure.conf"); */

Configure::Configure(const string & path)
: _path(path)
{

}
Configure::~Configure(){

}
string Configure::handlePath(const string & line){
    istringstream iss(line);
    string word;
    iss >> word;
    iss >> word;
    /* cout << word << endl; */
    /* string str1 = iss.str(); */
    /* cout << "str: " << str1 << endl; */
    return word;
}
void Configure::readPath(){
    ifstream ifs(_path);
    string line;
    while(getline(ifs,line)){
        if(line[0] == '#'){
            continue;
        }
        if(line.find("znDict") != string::npos){
            _znDict = handlePath(line);
        }else if(line.find("znIndex") != string::npos){
            _znIndex = handlePath(line);
        }else if(line.find("engDict") != string::npos){
            _engDict = handlePath(line);
        }else if(line.find("engIndex") != string::npos){
            _engIndex = handlePath(line);
        }else if(line.find("pageStoreHouse") != string::npos){
            _pageStoreHouse = handlePath(line);
        }else if(line.find("offsetStoreHouse") != string::npos){
            _offsetStoreHouse = handlePath(line);
        }else if(line.find("invertStoreHouse") != string::npos){
            _invertStoreHouse = handlePath(line);
        }else{
            continue;
        }
    }
}

#include "LoadFile.hpp"
#include <fstream>
#include <sstream>
using std::ifstream;
using std::istringstream;
/* Configure * p; */
pthread_once_t LoadFile::once = PTHREAD_ONCE_INIT;
/* std::once_flag LoadFile::flag ; */
LoadFile * LoadFile::_pInstance = nullptr;
LoadFile::LoadFile()
/* : _pconf(pconf) */
{

}
LoadFile::~LoadFile(){

}
void LoadFile::loadFile(Configure * _pconf){
    //读取偏移库
    {
        ifstream ifs(_pconf->getOffset());
        string line;
        while(getline(ifs,line)){
            istringstream iss(line);
            string id,startPos,offset;
            iss >> id >> startPos >> offset;
            pair<int,int> tmp = make_pair(atoi(startPos.c_str()),atoi(offset.c_str()));
            pair<int,pair<int,int>> _offset = make_pair(atoi(id.c_str()),tmp);
            _offsetLib.insert(_offset);
        }
        /* cout << _offsetLib.size() << endl; */
    }
    //读取网页库
    {
        ifstream ifs(_pconf->getPage());
        /* for(auto & elem : _offsetLib){ */
        for(size_t i = 0;i < _offsetLib.size();++i){
            auto elem = _offsetLib[i+1];
            ifs.seekg(elem.first);
            char * buffer = new char[elem.second+1];
            ifs.read(buffer,elem.second);
            string str1(buffer,elem.second);
            webPage web;
            web.getDoc(str1);
            pair<int,webPage> tmp = make_pair(elem.first,web);
            _pageLib.push_back(tmp);
            delete []buffer;
        }
        /* cout << _pageLib.size() << endl; */
    }
    //读取倒排索引库
    {
        ifstream ifs(_pconf->getIndex());
        string line;
        while(getline(ifs,line)){
            istringstream iss(line);
            string word;
            iss >> word;
            set<pair<int,double>> startAndWeight;
            string start,weight;
            while(iss >> start >> weight){
                pair<int,double> sw = make_pair(atoi(start.c_str()),std::stod(weight.c_str()));
                startAndWeight.insert(sw);
                start.clear();
                weight.clear();
            }
            pair<string,set<pair<int,double>>> tmp = make_pair(word,startAndWeight);
            _invertIndexTable.insert(tmp);
        }
        /* cout << _invertIndexTable.size() << endl; */
    }
}

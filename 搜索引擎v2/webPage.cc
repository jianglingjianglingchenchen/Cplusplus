#include "webPage.hpp"
#include <sstream>
using std::istringstream;
webPage::webPage()
{

}
webPage::~webPage(){

}
void webPage::getDoc(const string & file){
    /* istringstream iss(file); */
    /* string word,file1; */
    /* while(iss >> word){ */
    /*     file1 += word; */
    /* } */
    XMLDocument * doc = new XMLDocument();
    doc->Parse(file.c_str());
    if(doc->Error()){
        return;
    }
    XMLElement * root = doc->FirstChildElement("doc");
    XMLElement * id = root->FirstChildElement("docid");
    _docid = atoi(id->GetText());
    XMLElement * title = root->FirstChildElement("title");
    _docTitle = title->GetText();
    XMLElement * link = root->FirstChildElement("link");
    _docUrl = link->GetText();
    XMLElement * content = root->FirstChildElement("content");
    if(content->GetText()){
        _docContent = content->GetText();
    }
    /* std::cout << _docContent << std::endl; */
}

#include "ThreadPool.h"
#include "TcpServer.h"
#include "TcpConnection.h"
#include "KeyRecommander.h"
#include "webQuery.hpp"
#include "LoadFile.hpp"
#include "doSearch.hpp"
#include "Configure.hpp"
#include <string.h>
#include <nlohmann/json.hpp>
#include <iostream>

using std::cout;
using std::endl;
using json = nlohmann::json;

ThreadPool *gPool = nullptr;

struct Train{
    int length_of_msg;
    int flag;
    char msg[10000];
};

class MyTask
{
public:
    MyTask(const string &msg, const TcpConnectionPtr &con)
    : _msg(msg)
    , _con(con)
    {

    }
    void process()
    {
        //业务逻辑的处理
        //对msg调用相对应的函数得到返回值
        //用返回值初始化一个json对象，然后序列化
        Dictionary* dict = Dictionary::getInstance();
        KeyRecommander recm(_msg,dict);
        recm.recommand();
        vector<string> res = recm.response();

        cout << "after recommand" << endl;
        cout << "vector.size:" << res.size() << endl;
        for(auto& x:res){
            cout << x << endl;
        }

        /* json toSend{_msg}; */
        json toSend{res}; 
        string strSend(toSend.dump());
        Train train;
        train.length_of_msg = strSend.size();
        train.flag = 100;
        bzero(&train.msg,sizeof(train.msg));
        memcpy(&train.msg,strSend.c_str(),train.length_of_msg);
        _con->sendInLoop(&train,4+4+train.length_of_msg);
    }
private:
    string _msg;//这是客户端发来的字符串
    TcpConnectionPtr _con;
    /* &;// */
};

class WebSearchTask{
public:
    WebSearchTask(const string& msg,const TcpConnectionPtr& con)
    :_msg(msg),_con(con){

    }

    void process(){
        Configure conf("configure.conf");
        conf.readPath();
        LoadFile* load = LoadFile::getInstance();
        load->loadFile(&conf);
        doSearch search(_msg);
        vector<Result> webRes = search.run(load);
        //业务逻辑
        json json_arr;
        for(const auto& p:webRes){
            json tmp;
            tmp["title"] = p.title;
            tmp["link"] = p.link;
            tmp["abstract"] = p.abstract;
            json_arr.push_back(tmp);
        }
        string strSend(json_arr.dump());
        Train train;
        train.length_of_msg = strSend.size();
        train.flag = 100;
        bzero(&train.msg,sizeof(train.msg));
        memcpy(&train.msg,strSend.c_str(),train.length_of_msg);
        _con->sendInLoop(&train,4+4+train.length_of_msg);
    }
private:
    string _msg;
    TcpConnectionPtr _con;
};

//1、连接建立做的事件
void onNewConnection(const TcpConnectionPtr &con)
{
    cout << con->toString() << " has connected!" << endl;
}

//2、消息到达做的事件
void onMessage(const TcpConnectionPtr &con)
{
    //string msg = con->receive();//接收客户端的数据
    //cout << ">>recv msg from client " << msg << endl;
    Train train;
    char* p = (char*)con->recvn(4); 
    train.length_of_msg = *((int*)p);
    delete []p;
    p = (char*)con->recvn(4);
    train.flag = *((int*)p);
    delete []p;
    p = (char*)con->recvn(train.length_of_msg);
    bzero(train.msg,sizeof(train.msg));
    memcpy(train.msg,p,train.length_of_msg);
    delete []p;
    string setup(train.msg);
    json toQuery = json::parse(setup);
    string query = toQuery["message"];
    //从json字符串还原成json对象，再还原成原始字符串？
    
    cout << "length:" << query.size() << endl;
    cout << "flag:" << train.flag << endl;
    cout << "msg:" << query << endl;
    //这里的train.msg其实就是客户端发送过来的需要查询的字符串

    //接收到客户端的msg之后，是可以进行业务逻辑的处理
    
    if(train.flag == 1){//向池中添加查询关键字的任务
        MyTask task(query, con);
        gPool->addTask(std::bind(&MyTask::process, task));
    }
    else if(train.flag == 2){
        WebSearchTask task(query,con);
        gPool->addTask(std::bind(&WebSearchTask::process,task));
    }
    //创建对象
    //添加了Task，添加到了线程池里面去了,执行了_taskQue
    //中的push

    /* con->send(msg);//没有必要 */
}

//3、连接断开做的事件
void onClose(const TcpConnectionPtr &con)
{
    cout << con->toString() << " has closed!" << endl;
}

void test()
{
    ThreadPool pool(4, 10);
    pool.start();//工作线程会阻塞在_taskQue中pop函数，没有任务
    gPool = &pool;

    TcpServer server("127.0.0.1", 8888);
    server.setAllCallback(std::move(onNewConnection)
                          , std::move(onMessage)//此处
                          , std::move(onClose));
    server.start();
}

int main(int argc, char **argv)
{
    test();
    return 0;
}


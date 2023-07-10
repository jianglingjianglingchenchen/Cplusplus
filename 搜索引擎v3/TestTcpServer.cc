#include "ThreadPool.h"
#include "TcpServer.h"
#include "TcpConnection.h"
#include "KeyRecommander.h"
#include "Thread.h"
#include "CacheManager.h"
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
        cout << "tNum:" << current_thread_id::tNum << endl;        
        LRUcache& mycache = CacheManager::getInstance(4).getLRUcache(current_thread_id::tNum);
        /* string str_in_cache = mycache.find_json_str(_msg); */
        string str_in_cache = mycache.getData(_msg,1);
        if(str_in_cache.size() == 0){
            //所需要的查询结果不在缓存中，需要执行一遍查询获得结果
            //将查询获得的新结果放在一个存储待更新数据的链表中
            //设置一个定时器，当定时器到时，将所有缓存中待更新的结果写入主cache
            //然后再从主cache中拷贝到其他的cache
            //另外还需要另一个定时器事件来将cache中的内容持久化到磁盘中，每次系统开机也需要先从磁盘中将之前的cache还原
            Dictionary* dict = Dictionary::getInstance();
            KeyRecommander keyRec(_msg,dict);
            keyRec.recommand();
            vector<string> res = keyRec.response();
            json toSend;
            toSend["data"] = res;
            str_in_cache = toSend.dump();
            mycache.addData(_msg,1,str_in_cache);//将新的查询结果放到cache中
        }
        Train train;
        train.length_of_msg = str_in_cache.size();
        train.flag = 100;
        bzero(&train.msg,sizeof(train.msg));
        memcpy(&train.msg,str_in_cache.c_str(),train.length_of_msg);
        _con->sendInLoop(&train,4+4+train.length_of_msg);
    }
private:
    string _msg;//这是客户端发来的字符串
    TcpConnectionPtr _con;
};

class WebSearchTask{
public:
    WebSearchTask(const string& msg,const TcpConnectionPtr& con)
    :_msg(msg),_con(con){

    }

    void process(){
        //业务逻辑
        json toSend{_msg};
        string strSend(toSend.dump());
        Train train;
        train.length_of_msg = strSend.size();
        train.flag = 200;
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


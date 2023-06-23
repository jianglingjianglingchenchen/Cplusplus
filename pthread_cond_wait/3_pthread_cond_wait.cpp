#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <tuple>
using namespace std;

struct pass{
    pthread_cond_t* c;
    pthread_mutex_t* m;
};

pthread_cond_t cv = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mt;

void* threadFunc(void* arg){
    pass* pPass = (pass*)arg;
    /* pthread_mutex_lock(pPass->m); */
    /* cout << "after lock, befor wait" << endl; */
    pthread_cond_wait(pPass->c,pPass->m);//Why this is wrong?
    cout << "threadFunc" << endl;
    pthread_mutex_unlock(pPass->m);
    return nullptr;
}

int main()
{
    int err = pthread_mutex_init(&mt,nullptr);
    if(err){
        cerr << "pthread_mutex_init" << endl;
    }
    err = pthread_cond_init(&cv,nullptr);
    if(err){
        cerr << "pthread_cond_init" << endl;
    }

    /* tuple<pthread_mutex_t*,pthread_cond_t*> tp(&mt,&cv); */
    pass args;
    args.m = &mt;
    args.c = &cv;

    pthread_t tid;
    /* pthread_create(&tid,nullptr,threadFunc,nullptr); */
    pthread_create(&tid,nullptr,threadFunc,&args);
    
    pthread_mutex_lock(&mt);
    cout << "main thread" << endl;
    /* pthread_mutex_unlock(&mt); */
    /* pthread_mutex_lock(&mt); */
    sleep(2);

    pthread_mutex_lock(&mt);

    pthread_cond_signal(&cv);
    /* pthread_mutex_lock(&mt); */
    cout << "after signal, befor unlock" << endl;
    sleep(2);
    pthread_mutex_unlock(&mt);

    pthread_join(tid,nullptr);

    return 0;
}


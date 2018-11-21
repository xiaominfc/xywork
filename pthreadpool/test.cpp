/*
 * test.c
 * Copyright (C) 2018 xiaominfc(武汉鸣鸾信息科技有限公司) <xiaominfc@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#include "FCThreadPool.h"
#include <unistd.h>
//#include "FCTask.h"

class TestTask:public FCTask{
public:
    TestTask(){}
    virtual ~TestTask(){}
    void execute(){
        sleep(1);
        printf("test\n");
    }
};

void test1() {
   FCWorkThread* work = new FCWorkThread();
   work->start();
   FCTask *task = new TestTask();
   FCTask *task1 = new TestTask();
   FCTask *task2 = new TestTask();
   work->addTask(task);
   work->addTask(task1);
   work->addTask(task2);
   work->stop();// wait all task finish
   delete work;
   //sleep(3);
}

void test2() {
    FCThreadPool* pool = new FCThreadPool();
    pool->initPool(10);
    for(int i = 0 ; i < 100 ;i ++) {
        FCTask *task = new TestTask();
        pool->addTask(task);
    }
    pool->release();// wait all thread stop
    delete pool;
   //sleep(3);
}

void test3(){
    FCTask *task = new TestTask();
    FCSingleTaskThread *thread = new FCSingleTaskThread(task);
    thread->start();
    thread->stop();
    delete thread;// delete task also
}


int main(){
    //test1();
    //test2();
    test3();
    return 0;
}


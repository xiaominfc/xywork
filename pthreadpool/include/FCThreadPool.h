/*
 * FCThreadPool.h
 * Copyright (C) 2018 xiaominfc(武汉鸣鸾信息科技有限公司)
 * Email: xiaominfc@gmail.com
 * Distributed under terms of the MIT license.
 */

#ifndef FCTHREADPOOL_H
#define FCTHREADPOOL_H
#include "FCThread.h"
#include "FCTask.h"
#include <list>

using namespace std;



class FCSingleTaskThread:public FCThread
{
public:
    FCSingleTaskThread(FCTask* task);
    ~FCSingleTaskThread();
    virtual void run();
    virtual void stop();
private:
    FCTask *m_task;
};



class FCWorkThread:public FCThread
{
public:
    FCWorkThread();
    virtual ~FCWorkThread();
    virtual void start();
    virtual void stop();
    virtual void run();
    virtual void addTask(FCTask *task);
protected:
    list<FCTask*>    m_task_list;
    FCThreadNotify   m_notify;
    bool m_running;
};





class FCExpandThread:public FCWorkThread
{
public:
    FCExpandThread();
    virtual ~FCExpandThread();
    virtual void run();
};

class FCThreadPool
{
public:
    FCThreadPool();
    ~FCThreadPool(){};

    // init pool by size(number of thread)
    int initPool(unsigned int size);

    // wait all thread finish task;
    void release();
    virtual void addTask(FCTask *task);
protected:
    unsigned int m_size;
    unsigned int m_task_count;

private:
    FCWorkThread* m_workers;
};




#endif /* !FCTHREADPOOL_H */

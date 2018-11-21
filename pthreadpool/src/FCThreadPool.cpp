/*
 * FCThreadPool.cpp
 * Copyright (C) 2018 xiaominfc(武汉鸣鸾信息科技有限公司) <xiaominfc@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#include "FCThreadPool.h"


FCSingleTaskThread::FCSingleTaskThread(FCTask *task):FCThread()
{
    m_task = task;
}

FCSingleTaskThread::~FCSingleTaskThread(){
    if(m_task) {
        delete m_task;
    }
}

void FCSingleTaskThread::run(){
    if(m_task) {
        m_task->execute();
    }
}

void FCSingleTaskThread::stop(){
    pthread_join(m_thread_id,NULL);
}




FCWorkThread::FCWorkThread(){
    m_running = false;
}

void FCWorkThread::start(){
    m_running = true;
    FCThread::start();
}

void FCWorkThread::stop(){
    m_running = false;
    m_notify.signal();
    printf("stop:%d\n",m_thread_id);
    pthread_join(m_thread_id,NULL);
}

FCWorkThread::~FCWorkThread(){

}

void FCWorkThread::run(){
    while(true){
        m_notify.lock();
        while(m_task_list.empty()){
            if(!m_running) {
                m_notify.unlock();
                return;
            }
            m_notify.wait();
        }
        FCTask *task = m_task_list.front();
        m_task_list.pop_front();
        m_notify.unlock();
        task->execute();
        delete task;    
    }
}

void FCWorkThread::addTask(FCTask* task){
    m_notify.lock();
    m_task_list.push_back(task);
    m_notify.signal();
    m_notify.unlock();
}



FCThreadPool::FCThreadPool()
{
    m_size = 0;
    m_task_count = 0;
    m_workers = NULL;
}


int FCThreadPool::initPool(unsigned int size){
    m_size = size;
    m_workers = new FCWorkThread[m_size];
    for(int i = 0;i < m_size; i++){
        m_workers[i].start();
    }
    return 0;
}

void FCThreadPool::addTask(FCTask *task) {
    m_workers[m_task_count++ % m_size].addTask(task);
}

void FCThreadPool::release(){

    if(m_workers) {
        for(int i = 0; i < m_size ; i++){
            m_workers[i].stop();
        }
        delete []m_workers;
    }
   
}



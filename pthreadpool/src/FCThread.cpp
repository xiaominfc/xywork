/*
 * FCThread.cpp
 * Copyright (C) 2018 xiaominfc(武汉鸣鸾信息科技有限公司) <xiaominfc@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#include "FCThread.h"


static void* StartThread(void *arg){
    FCThread *thread = (FCThread*)arg;
    thread->run();
}


FCThread::FCThread(){
    m_thread_id=0;
}


FCThread::~FCThread(){
    m_thread_id=0;
}

void FCThread::start(){
    // pthread_attr_t a;
    // pthread_attr_init(&a);
    // pthread_attr_setdetachstate(&a, PTHREAD_CREATE_DETACHED);
    //(void)pthread_create(&m_thread_id, &a, StartThread, this);
    (void)pthread_create(&m_thread_id, NULL, StartThread, this);
}

FCEventThread::FCEventThread(){
    m_running = false;
}


void FCEventThread::start(){
    m_running = true;
    FCEventThread::start();
}

void FCEventThread::stop(){
    m_running = false;
}

void FCEventThread::run(){
   while(this->m_running){
       onEventTick();
   }
}

FCThreadNotify::FCThreadNotify()
{
	pthread_mutexattr_init(&m_mutexattr);
	pthread_mutexattr_settype(&m_mutexattr, PTHREAD_MUTEX_RECURSIVE);
	pthread_mutex_init(&m_mutex, &m_mutexattr);
	pthread_cond_init(&m_cond, NULL);
}

FCThreadNotify::~FCThreadNotify()
{
	pthread_mutexattr_destroy(&m_mutexattr);
	pthread_mutex_destroy(&m_mutex);
    
	pthread_cond_destroy(&m_cond);
}


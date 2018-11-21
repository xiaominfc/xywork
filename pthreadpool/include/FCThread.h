/*
 * FCThread.h
 * Copyright (C) 2018 xiaominfc(武汉鸣鸾信息科技有限公司)
 * Email: xiaominfc@gmail.com
 * Distributed under terms of the MIT license.
 */

#ifndef FCTHREAD_H
#define FCTHREAD_H


#include <pthread.h>


class FCThread
{
public:
    FCThread();
    virtual ~FCThread();
    virtual void start();
    virtual void run()=0;
protected:
    pthread_t m_thread_id;
};


class FCEventThread:FCThread 
{
public:
    FCEventThread();
    virtual ~FCEventThread()=0;
    virtual void start();
    virtual void stop();
    virtual void run();
    virtual void onEventTick() = 0;
private:
    bool m_running;

};


class FCThreadNotify
{
public:
    FCThreadNotify();
    ~FCThreadNotify();
    void lock() { pthread_mutex_lock(&m_mutex); }
    void unlock() { pthread_mutex_unlock(&m_mutex); }
    void wait() {pthread_cond_wait(&m_cond, &m_mutex); }
    void signal() { pthread_cond_signal(&m_cond); }

private:
    pthread_mutex_t 	m_mutex;
    pthread_mutexattr_t	m_mutexattr;
    pthread_cond_t 		m_cond;

};


#endif /* !FCTHREAD_H */

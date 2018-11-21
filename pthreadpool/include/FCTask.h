/*
 * FCTask.h
 * Copyright (C) 2018 xiaominfc(武汉鸣鸾信息科技有限公司)
 * Email: xiaominfc@gmail.com
 * Distributed under terms of the MIT license.
 */

#ifndef FCTASK_H
#define FCTASK_H

class FCTask
{
public:
    FCTask(){}
    virtual ~FCTask(){};

    // over write for youself task
    virtual void execute()=0;
};

class FCEventTask:FCTask
{
public:
    FCEventTask(){};
    ~FCEventTask(){};
    virtual void onPrepare(void *data);
    virtual void onEnd(void *data);
    //virtual onProgress(void *data);
    virtual void execute();
};

#endif /* !FCTASK_H */

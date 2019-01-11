#ifndef __USERAGENTCORETHREAD_H__
#define __USERAGENTCORETHREAD_H__

#include "rutil/ThreadIf.hxx"

namespace resip
{ 
class BasicClientUserAgent;

class CUserAgentCoreThread : public ThreadIf
{
public:
    CUserAgentCoreThread(BasicClientUserAgent *userAgent);


    virtual void thread();

private:
    BasicClientUserAgent *m_UserAgent;
};

}

#endif
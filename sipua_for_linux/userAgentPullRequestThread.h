#ifndef __USERAGENT_PULL_REQUEST_THREAD_H__
#define __USERAGENT_PULL_REQUEST_THREAD_H__

#include "rutil/ThreadIf.hxx"

namespace resip
{
    class BasicClientUserAgent;

    class CUserAgentPullRequestThread : public ThreadIf
    {
    public:
        CUserAgentPullRequestThread(BasicClientUserAgent *userAgent);


        virtual void thread();

    private:
        BasicClientUserAgent *m_UserAgent;
    };

}

#endif //__USERAGENT_PULL_REQUEST_THREAD_H__
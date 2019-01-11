#include "userAgentPullRequestThread.h"
#include "basicClientUserAgent.hxx"

using namespace resip;

CUserAgentPullRequestThread::CUserAgentPullRequestThread(BasicClientUserAgent* userAgent)
    :m_UserAgent(userAgent)
{

}

void CUserAgentPullRequestThread::thread()
{
    while (!mShutdown)
    {
        //get messget
    }
}
#include "userAgentCoreThread.h"
#include "basicClientUserAgent.hxx"

using namespace resip;

CUserAgentCoreThread::CUserAgentCoreThread(BasicClientUserAgent* userAgent)
    :m_UserAgent(userAgent)
{
    
}

void CUserAgentCoreThread::thread()
{
    if (NULL != m_UserAgent)
    { 
        while (m_UserAgent->process(1000))
        {
        
        }

        m_UserAgent->shutdown();
    }
}
#ifndef __GB28181_USER_AGENT_H__
#define __GB28181_USER_AGENT_H__
#include "basicClientUserAgent.hxx"

using namespace resip;

class GB28181UserAgent : public BasicClientUserAgent
{
public:
    GB28181UserAgent();
    ~GB28181UserAgent();

public:
    virtual void onRegisterSuccess();
    virtual void onRegisterFailure_401();
    virtual void onRegisterFailure();

    //int doInit(char* SipServerId, char* SipServerIp, int SipServerPort, 
    //    char* GB28181UserAgentId, int GB28181UserAgentPort);

    /**
    *   function:
    *       get Directiory info from sipsvr
    *   功能：
    *       获取目录信息
    */
    int doGetDirectory(char* SipDeviceId);

private:
};

#endif

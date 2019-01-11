#include "taskDispatcher.h"
#include "basicClientUserAgent.hxx"

using namespace resip;

CTaskDispatcher::CTaskDispatcher()
{

}

CTaskDispatcher::~CTaskDispatcher()
{
}

int CTaskDispatcher::getDirectoryInfo(char* target_dev_id, char* target_realm, char* directory_info_buf_out)
{
    return 0;
}
int CTaskDispatcher::ptzControl(char* target_dev_id, char* target_realm, int ptz, int ptz_speed)
{
    return 0;
}

int CTaskDispatcher::startRealPlay(char* call_id, char* target_dev_id, char* target_realm,
    char* media_recv_ip, int media_recv_port)
{
    char sip_starget[100] = { 0 };

    //BasicClientUserAgent* pUserAgent = BasicClientUserAgent::getInstance();
    if (
         strlen(call_id) > 0
        || strlen(target_dev_id) > 0
        || strlen(target_realm) > 0
        || strlen(media_recv_ip) > 0
        )
    {
        sprintf(sip_starget, "sip:%s@%s", target_dev_id, target_realm);
        BasicClientUserAgent::getInstance()->doInvite(call_id, sip_starget, media_recv_ip, media_recv_port);
    }
    return 0;
}
int CTaskDispatcher::stopRealPlay(char* call_id, char* target_dev_id, char* target_realm, char* media_recv_ip, int media_recv_port)
{
    char sip_starget[100] = { 0 };
    BasicClientUserAgent* pUserAgent = BasicClientUserAgent::getInstance();
    if ( strlen(call_id) > 0
        || strlen(target_dev_id) > 0
        || strlen(target_realm) > 0
        || strlen(media_recv_ip) > 0
        )
    {
        sprintf(sip_starget, "sip:%s@%s", target_dev_id, target_realm);
        BasicClientUserAgent::getInstance()->doBye(call_id);
    }
    return 0;
}
int CTaskDispatcher::startPlayBack(char* call_id, char* target_dev_id, char* target_realm, char* start_time, char* end_time)
{
    return 0;
}
int CTaskDispatcher::stopPlayBack(char* call_id, char* target_dev_id, char* target_realm)
{
    return 0;
}
int CTaskDispatcher::pausePlayBack(char* call_id, char* target_dev_id, char* target_realm)
{
    return 0;
}

int CTaskDispatcher::addTask(char* call_id, char* media_recv_ip, int media_recv_port, char* target_dev_id, char* target_realm)
{
    return 0;
}
int CTaskDispatcher::dealTask()
{
    return 0;
}
#ifndef __TASKDISPATCHER_H__
#define __TASKDISPATCHER_H__

#include <map>
#include <vector>

typedef struct ctrl_status
{
    typedef enum media_status
    {
        normal = 1,
        palying,
        stoped,
        paused

    } media_status_e;

    char call_id[24];
    char media_recv_ip[16];
    int media_recv_port;

    char target_dev_id[24];
    char target_realm[24];

    bool is_status_changed;

}ctrl_status_t;

class CTaskDispatcher
{
public:
    static CTaskDispatcher* getInstance()
    {
        if (NULL != mInstance)
        {
            return mInstance;
        }
        else
        { 
            return new CTaskDispatcher();
        }
    }

    //不需要建立会话
    int getDirectoryInfo(char* target_dev_id, char* target_realm, char* directory_info_buf_out);
    int ptzControl(char* target_dev_id, char* target_realm, int ptz, int ptz_speed);

    //需要建立会话
    int startRealPlay(char* call_id, char* target_dev_id, char* target_realm, char* media_recv_ip, int media_recv_port);
    int stopRealPlay(char* call_id, char* target_dev_id, char* target_realm, char* media_recv_ip, int media_recv_port);

    int startPlayBack(char* call_id, char* target_dev_id, char* target_realm, char* start_time, char* end_time);
    int stopPlayBack(char* call_id, char* target_dev_id, char* target_realm);
    int pausePlayBack(char* call_id, char* target_dev_id, char* target_realm);

    //inner
    int addTask(char* call_id, char* media_recv_ip, int media_recv_port, char* target_dev_id, char* target_realm);
    int dealTask();

private:
    CTaskDispatcher();
    virtual ~CTaskDispatcher();
    static CTaskDispatcher* mInstance;

    std::map<std::string, ctrl_status_t*> mSessionMap;
    std::vector<char*> mDirectoryInfoRepository;
};

#endif
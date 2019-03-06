#include <memory>
#include "gb28181UserAgent.h"

using namespace std;

GB28181UserAgent::GB28181UserAgent()
{
}

GB28181UserAgent::~GB28181UserAgent()
{
}

void GB28181UserAgent::onRegisterSuccess()
{}

void GB28181UserAgent::onRegisterFailure_401()
{}

void GB28181UserAgent::onRegisterFailure()
{}

//int GB28181UserAgent::doInit(char* SipServerId, char* SipServerIp, int SipServerPort,
//    char* GB28181UserAgentId, int GB28181UserAgentPort)
//{
//    if( SipServerId && SipServerIp && GB28181UserAgentId)
//    {
//
//    }
//    return 0;
//}


int GB28181UserAgent::doGetDirectory(char* SipDeviceId)
{
    ClientPagerMessageHandle cpmh = mDum->makePagerMessage(NameAddr(mAor), mProfile);

    Data getCatalogReq =
        "<?xml version=\"1.0\"?>\r\n"
        "<Query>\r\n"
        "<CmdType>Catalog</CmdType>\r\n"
        "<SN>SN_PlaceHolder</SN>\r\n"
        "<DeviceID>DeviceID_PlaceHolder</DeviceID>\r\n"
        "</Query>\r\n"
        ;

    if (SipDeviceId)
    {
        getCatalogReq.replace("DeviceID_PlaceHolder", SipDeviceId);
    }

    doMessage(getCatalogReq);

    return 0;
}

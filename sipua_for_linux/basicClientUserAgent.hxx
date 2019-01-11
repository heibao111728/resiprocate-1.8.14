#if !defined(basicClientUserAgent_hxx)
#define basicClientUserAgent_hxx

#include <set>
#include <map>

#include "resip/stack/InterruptableStackThread.hxx"
#include "rutil/SelectInterruptor.hxx"
#include "resip/dum/MasterProfile.hxx"
#include "resip/dum/RegistrationHandler.hxx"
#include "resip/dum/SubscriptionHandler.hxx"
#include "resip/dum/RedirectHandler.hxx"
#include "resip/dum/DialogSetHandler.hxx"
#include "resip/dum/DumShutdownHandler.hxx"
#include "resip/dum/OutOfDialogHandler.hxx"
#include "resip/dum/InviteSessionHandler.hxx"
#include "resip/dum/DialogUsageManager.hxx"
#include "resip/dum/Postable.hxx"
#include "resip/dum/PagerMessageHandler.hxx"
#include "resip/dum/ClientPagerMessage.hxx"
#include "resip/dum/ServerPagerMessage.hxx"

#include "userAgentCoreThread.h"


namespace resip
{
    class BasicClientCall;

    class BasicClientUserAgent :
        public Postable,
        public DialogSetHandler,
        public ClientRegistrationHandler,
        public ClientSubscriptionHandler,
        public ServerSubscriptionHandler,
        public OutOfDialogHandler,
        public InviteSessionHandler,
        public DumShutdownHandler,
        public RedirectHandler,
        public ClientPagerMessageHandler,  /*used for message request*/
        public ServerPagerMessageHandler   /*used for message request*/
    {
    private:
        BasicClientUserAgent();
        

    public:
        static BasicClientUserAgent* getInstance()
        {
            if (NULL != mInstance)
            {
                return mInstance;
            }
            else
            {
                mInstance = new BasicClientUserAgent();
                return mInstance;
            }
        }

        //静态成员变量需要先初始化
        static BasicClientUserAgent* mInstance;
        

    public:
        virtual ~BasicClientUserAgent();
        virtual void startup();
        virtual void shutdown();
        bool process(int timeoutMs); // returns false when shutdown is complete and process should no longer be called

        DialogUsageManager &getDialogUsageManager() { return *mDum; }
        SharedPtr<UserProfile> getIncomingUserProfile(const SipMessage &msg) { return mProfile; } // This test program only uses the one global Master Profile - just return it

    protected:
        // Postable Handler ////////////////////////////////////////////////////////////
        virtual void post(Message *); // Used to receive Connection Terminated messages

        // Shutdown Handler ////////////////////////////////////////////////////////////
        void onDumCanBeDeleted();

        // Registration Handler ////////////////////////////////////////////////////////
        virtual void onSuccess(resip::ClientRegistrationHandle h, const resip::SipMessage &response);
        virtual void onFailure(resip::ClientRegistrationHandle h, const resip::SipMessage &response);
        virtual void onRemoved(resip::ClientRegistrationHandle h, const resip::SipMessage &response);
        virtual int onRequestRetry(resip::ClientRegistrationHandle h, int retryMinimum, const resip::SipMessage &msg);

        // ClientSubscriptionHandler ///////////////////////////////////////////////////
        virtual void onUpdatePending(resip::ClientSubscriptionHandle h, const resip::SipMessage &notify, bool outOfOrder);
        virtual void onUpdateActive(resip::ClientSubscriptionHandle h, const resip::SipMessage &notify, bool outOfOrder);
        virtual void onUpdateExtension(resip::ClientSubscriptionHandle, const resip::SipMessage &notify, bool outOfOrder);
        virtual void onNotifyNotReceived(ClientSubscriptionHandle h);
        virtual void onTerminated(resip::ClientSubscriptionHandle h, const resip::SipMessage *notify);
        virtual void onNewSubscription(resip::ClientSubscriptionHandle h, const resip::SipMessage &notify);
        virtual int onRequestRetry(resip::ClientSubscriptionHandle h, int retrySeconds, const resip::SipMessage &notify);

        // Invite Session Handler /////////////////////////////////////////////////////
        virtual void onNewSession(resip::ClientInviteSessionHandle h, resip::InviteSession::OfferAnswerType oat, const resip::SipMessage &msg);
        virtual void onNewSession(resip::ServerInviteSessionHandle h, resip::InviteSession::OfferAnswerType oat, const resip::SipMessage &msg);
        virtual void onFailure(resip::ClientInviteSessionHandle h, const resip::SipMessage &msg);
        virtual void onEarlyMedia(resip::ClientInviteSessionHandle, const resip::SipMessage &, const resip::SdpContents &);
        virtual void onProvisional(resip::ClientInviteSessionHandle, const resip::SipMessage &msg);
        virtual void onConnected(resip::ClientInviteSessionHandle h, const resip::SipMessage &msg);
        virtual void onConnected(resip::InviteSessionHandle, const resip::SipMessage &msg);
        virtual void onStaleCallTimeout(resip::ClientInviteSessionHandle);
        virtual void onTerminated(resip::InviteSessionHandle h, resip::InviteSessionHandler::TerminatedReason reason, const resip::SipMessage *msg);
        virtual void onRedirected(resip::ClientInviteSessionHandle, const resip::SipMessage &msg);
        virtual void onAnswer(resip::InviteSessionHandle, const resip::SipMessage &msg, const resip::SdpContents &);
        virtual void onOffer(resip::InviteSessionHandle handle, const resip::SipMessage &msg, const resip::SdpContents &offer);
        virtual void onOfferRequired(resip::InviteSessionHandle, const resip::SipMessage &msg);
        virtual void onOfferRejected(resip::InviteSessionHandle, const resip::SipMessage *msg);
        virtual void onOfferRequestRejected(resip::InviteSessionHandle, const resip::SipMessage &msg);
        virtual void onRemoteSdpChanged(resip::InviteSessionHandle, const resip::SipMessage &msg, const resip::SdpContents &sdp);
        virtual void onInfo(resip::InviteSessionHandle, const resip::SipMessage &msg);
        virtual void onInfoSuccess(resip::InviteSessionHandle, const resip::SipMessage &msg);
        virtual void onInfoFailure(resip::InviteSessionHandle, const resip::SipMessage &msg);
        virtual void onRefer(resip::InviteSessionHandle, resip::ServerSubscriptionHandle, const resip::SipMessage &msg);
        virtual void onReferAccepted(resip::InviteSessionHandle, resip::ClientSubscriptionHandle, const resip::SipMessage &msg);
        virtual void onReferRejected(resip::InviteSessionHandle, const resip::SipMessage &msg);
        virtual void onReferNoSub(resip::InviteSessionHandle, const resip::SipMessage &msg);
        virtual void onMessage(resip::InviteSessionHandle, const resip::SipMessage &msg);
        virtual void onMessageSuccess(resip::InviteSessionHandle, const resip::SipMessage &msg);
        virtual void onMessageFailure(resip::InviteSessionHandle, const resip::SipMessage &msg);
        virtual void onForkDestroyed(resip::ClientInviteSessionHandle);
        virtual void onReadyToSend(InviteSessionHandle, SipMessage &msg);
        virtual void onFlowTerminated(InviteSessionHandle);

        // DialogSetHandler  //////////////////////////////////////////////
        virtual void onTrying(resip::AppDialogSetHandle, const resip::SipMessage &msg);
        virtual void onNonDialogCreatingProvisional(resip::AppDialogSetHandle, const resip::SipMessage &msg);

        // ServerSubscriptionHandler ///////////////////////////////////////////////////
        virtual void onNewSubscription(resip::ServerSubscriptionHandle, const resip::SipMessage &sub);
        virtual void onNewSubscriptionFromRefer(resip::ServerSubscriptionHandle, const resip::SipMessage &sub);
        virtual void onRefresh(resip::ServerSubscriptionHandle, const resip::SipMessage &sub);
        virtual void onTerminated(resip::ServerSubscriptionHandle);
        virtual void onReadyToSend(resip::ServerSubscriptionHandle, resip::SipMessage &);
        virtual void onNotifyRejected(resip::ServerSubscriptionHandle, const resip::SipMessage &msg);
        virtual void onError(resip::ServerSubscriptionHandle, const resip::SipMessage &msg);
        virtual void onExpiredByClient(resip::ServerSubscriptionHandle, const resip::SipMessage &sub, resip::SipMessage &notify);
        virtual void onExpired(resip::ServerSubscriptionHandle, resip::SipMessage &notify);
        virtual bool hasDefaultExpires() const;
        virtual UInt32 getDefaultExpires() const;

        // OutOfDialogHandler //////////////////////////////////////////////////////////
        virtual void onSuccess(resip::ClientOutOfDialogReqHandle, const resip::SipMessage &response);
        virtual void onFailure(resip::ClientOutOfDialogReqHandle, const resip::SipMessage &response);
        virtual void onReceivedRequest(resip::ServerOutOfDialogReqHandle, const resip::SipMessage &request);

        // RedirectHandler /////////////////////////////////////////////////////////////
        virtual void onRedirectReceived(resip::AppDialogSetHandle, const resip::SipMessage &response);
        virtual bool onTryingNextTarget(resip::AppDialogSetHandle, const resip::SipMessage &request);

        // ClientPagerMessageHandle 
        virtual void onSuccess(ClientPagerMessageHandle, const SipMessage& status);
        virtual void onFailure(ClientPagerMessageHandle, const SipMessage& status, std::auto_ptr<Contents> contents);

        //ServerPagerMessageHandle
        virtual void onMessageArrived(ServerPagerMessageHandle, const SipMessage& message);
    public:
        /**
        *   function:
        *       register to sipSvr
        *   param:
        *       expire          [in]:
        *                               0:  unRegister
        *                               >0: timeout
        *   return:
        *       0:  success
        *       -1: failure
        *   功能：
        *       注册到sip服务器
        */
        int doRegister(int expire);

        /**
        *   function:
        *       invite a peer join dialog
        *   param:
        *       target          [in]: target sip URI
        *       mediaRecvIp     [in]: specify host, which recv media stream
        *       mediaRecvPort   [in]: specify port, which revc media stream
        *   功能：
        *       
        *       
        *       
        */
        int doInvite(char* callid, char* deviceId, char* realm, char* mediaRecvIp, int mediaRecvPort, bool securityFlag = false);

        /**
        *   function:
        *       terminate dialog
        *   功能：
        *       结束当前对话, 这里只明显显示bye指令，对于还未彻底建立会话时应当使用cancel指令，
        *       对此应用层不做判断分析，交给协议栈做处理，如果对话还未彻底建立，协议栈会自动发送
        *       cancel消息指令而不是bye指令。
        */
        int doBye(char* callid);

        /**
        *   function:
        *       get Directiory info from sipsvr
        *   功能：
        *       获取目录信息
        */
        int doGetDirectory();

        /**
        *   function:
        *       review
        *   功能：
        *       历史视频预览
        */
        int doPlayBack();

        /**
        *   function:
        *       Subscribe
        *   功能：
        *       订阅
        */
        int doSubscribe();

        /**
        *   function:
        *       UnSubscribe
        *   功能：
        *       取消订阅
        */
        int doUnSubscribe();

        void printfConfigureInfo();

    protected:
        void addTransport(TransportType type, int port);
        friend class NotifyTimer;
        void onNotifyTimeout(unsigned int timerId);
        void sendNotify();
        friend class CallTimer;
        void onCallTimeout(BasicClientCall *call);

        SharedPtr<MasterProfile> mProfile;
        // Using pointers for the following classes so that we can control object descruction order
        Security *mSecurity;
        SelectInterruptor *mSelectInterruptor;
        SipStack *mStack;
        InterruptableStackThread *mStackThread;
        DialogUsageManager *mDum;
        volatile bool mDumShutdownRequested;
        bool mDumShutdown;
        ClientRegistrationHandle mRegHandle;
        ClientSubscriptionHandle mClientSubscriptionHandle;
        ServerSubscriptionHandle mServerSubscriptionHandle;
        unsigned int mRegistrationRetryDelayTime;
        unsigned int mCurrentNotifyTimerId;

        friend class BasicClientCall;

        std::set<BasicClientCall *> mCallList;
        std::map<std::string, BasicClientCall *> mCallMap;

        void registerCall(BasicClientCall *call);
        void unregisterCall(BasicClientCall *call);
        bool isValidCall(BasicClientCall *call);

        //modified by yangdong
        CUserAgentCoreThread *mUserAgentThread;

    private:
        Data mLogType;
        Data mLogLevel;
        char *m_LogFileName;
        Data mTlsDomain;
        Data mCertPath;

        int mUdpPort;
        int mTcpPort;
        int mTlsPort;
        int mDtlsPort;

        int mRegisterDuration;
        bool mNoV4;
        bool mEnableV6;
        bool mHostFileLookupOnlyDnsMode;

        Uri mAor;				//sip server info
        Data mPassword;			//sip server pwd, when register use.

        Uri mOutboundProxy;
        Uri mContact;
        bool mOutboundEnabled;

        Uri mSubscribeTarget;
        Uri mCallTarget;
    };

} // namespace resip

#endif

/* ====================================================================

 Copyright (c) 2011, SIP Spectrum, Inc.
 All rights reserved.

 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are
 met:

 1. Redistributions of source code must retain the above copyright
 notice, this list of conditions and the following disclaimer.

 2. Redistributions in binary form must reproduce the above copyright
 notice, this list of conditions and the following disclaimer in the
 documentation and/or other materials provided with the distribution.

 3. Neither the name of SIP Spectrum nor the names of its contributors
 may be used to endorse or promote products derived from this
 software without specific prior written permission.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

 ==================================================================== */

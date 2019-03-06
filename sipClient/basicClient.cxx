#if defined(HAVE_CONFIG_HXX)
#include "resip/stack/config.hxx"
#endif

#include <cstring>
#include <cassert>

#ifndef __APPLE__
bool TRUE=true;
bool FALSE=false;
#endif

//#include "basicClientUserAgent.hxx"
#include "gb28181UserAgent.h"
#include <resip/stack/SipStack.hxx>
#include <resip/stack/Uri.hxx>
#include <rutil/Logger.hxx>

#ifdef USE_SSL
#include <resip/stack/ssl/Security.hxx>
#endif

#include <signal.h>

using namespace resip;
using namespace std;

#define RESIPROCATE_SUBSYSTEM Subsystem::TEST

static bool exitSignalDetected = false;

static void
signalHandler(int signo)
{
   std::cerr << "Shutting down" << endl;
   exitSignalDetected = true;
}

int
main(int argc, char* argv[])
{
#ifndef _WIN32
   if ( signal( SIGPIPE, SIG_IGN) == SIG_ERR)
   {
      cerr << "Couldn't install signal handler for SIGPIPE" << endl;
      exit(-1);
   }
#endif

   if ( signal( SIGINT, signalHandler ) == SIG_ERR )
   {
      cerr << "Couldn't install signal handler for SIGINT" << endl;
      exit( -1 );
   }

   if ( signal( SIGTERM, signalHandler ) == SIG_ERR )
   {
      cerr << "Couldn't install signal handler for SIGTERM" << endl;
      exit( -1 );
   }

   // Initialize network
   initNetwork();

   try
   {
       //BasicClientUserAgent* pUa = BasicClientUserAgent::getInstance();
      // BasicClientUserAgent* pUa = new BasicClientUserAgent();
      // pUa->startup();
      //
      //InfoLog(<< argv[0] << " starting");

      //Sleep(5 * 1000);

      //pUa->doInvite("test1", "34020000001320000202", "3402000000", "192.168.2.102", 9000);
      ////Sleep(2 * 1000);
      ////BasicClientUserAgent::getInstance()->doInvite("test2", "34020000001320000201", "3402000000", "192.168.2.102", 20000);

      ////Sleep(6 * 1000);

      ////BasicClientUserAgent::getInstance()->doBye("test2");
      ////pUa->doBye("test1");

      //Sleep(120 * 1000);
      //pUa->doBye("test1");
       char* SipServerId = "34020000002000000001";
       char* SipServerIp = "192.168.2.128";
       int SipServerPort = 5060;
       char* AuthPwd = "12345678a";

       char* SipClientId = "34020000004000000001";
       int SipClientPort = 5060;

       GB28181UserAgent gb28181ua;

       gb28181ua.doInit(SipServerId, SipServerIp, SipServerPort, AuthPwd, SipClientId, SipClientPort);

       gb28181ua.startup();

       gb28181ua.doRegister(3600);

       InfoLog(<< argv[0] << " starting");

       gb28181ua.doInvite("test1", "34020000001320000202", "3402000000", "192.168.2.102", 9000);





      //while(ua.process(1000))  // Look for exit key every 1 second
      //{
      //   if(exitSignalDetected)
      //   {
      //      ua.shutdown();
      //      exitSignalDetected = false;
      //   }
      //}
   }
#ifdef USE_SSL
   catch (BaseSecurity::Exception& e)
   {
      WarningLog (<< "Couldn't set up security object: " << e);
      exit(-1);
   }
#endif
   catch (BaseException& e)
   {
      ErrLog (<< "Caught: " << e);
      exit(-1);
   }
   catch( ... )
   {
      ErrLog( << "Caught non-resip exception" );
      exit(-1);
   }

   return 0;
}

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


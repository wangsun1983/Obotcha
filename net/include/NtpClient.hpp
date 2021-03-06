#ifndef __OBOTCHA_NTP_CLIENT_HPP__
#define __OBOTCHA_NTP_CLIENT_HPP__

#include <sys/stat.h>
#include <unistd.h>    
#include <sys/types.h>
#include <netinet/in.h>
#include <mqueue.h>
#include <fstream>
#include <sys/un.h>


#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "SocketListener.hpp"
#include "Condition.hpp"
#include "Mutex.hpp"
#include "SocketMonitor.hpp"

namespace obotcha {

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <unistd.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <errno.h>
#include <endian.h>

#define NTP_DATA_SIZE 48

#define  JAN_1970   0x83aa7e80      //3600s*24h*(365days*70years+17days)

//x*10^(-6)*2^32 us NtpTime'sfraction
#define  NTPFRAC(x) (4294 * (x) + ((1981 * (x)) >> 11))  

#define  USEC(x) (((x) >> 12) - 759 * ((((x) >> 10) + 32768) >> 16))

//#define DEF_NTP_SERVER "stdtime.gov.hk" //HK server

//#define DEF_NTP_SERVER "pool.ntp.org"   //ntp server

struct NtpTime{
    unsigned   int  integer;
    unsigned   int  fraction;
};

DECLARE_SIMPLE_CLASS(NtpListener) {
public:
    virtual void onAccept(long int millseconds);
    virtual void onClose();
};

DECLARE_SIMPLE_CLASS(NtpSocketClientListener) IMPLEMENTS(SocketListener) {
public:
    _NtpSocketClientListener(Condition,Mutex);

    void onSocketMessage(int,Socket,ByteArray);
    
    void setTimeCallback(NtpListener);

    long int getTimeMillis();

    ~_NtpSocketClientListener();

private:
    void onDataReceived(Socket,ByteArray);

    Condition mCondition;
    Mutex mMutex;
    long int milliseconds;
    NtpListener mListener;

    double get_rrt(const struct NtpPacket *ntp, const struct timeval *recvtv);

    double get_offset(const struct NtpPacket *ntp, const struct timeval *recvtv);
};
    
DECLARE_SIMPLE_CLASS(NtpClient) {
public:
    _NtpClient();

    int bind(String url,int port);

    long getCurrentTimeSync();

    void getCurrentTimeAsync(NtpListener);

    void release();

    ~_NtpClient();

private:

    String mServerIp;

    //UdpClient mClient;
    Socket mSock;
    SocketMonitor mSockMonitor;

    int mPort;

    NtpSocketClientListener mListener;

    Mutex mMutex;

    Condition mCondition;

    NtpListener mNtpListener;

    void generateNtpPacket(char *);
};

}

#endif

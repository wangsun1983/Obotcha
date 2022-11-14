#ifndef __OBOTCHA_NTP_CLIENT_HPP__
#define __OBOTCHA_NTP_CLIENT_HPP__

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

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "SocketListener.hpp"
#include "Condition.hpp"
#include "Mutex.hpp"
#include "SocketMonitor.hpp"

namespace obotcha {

#define NTP_DATA_SIZE 48

#define  JAN_1970   0x83aa7e80      //3600s*24h*(365days*70years+17days)

//x*10^(-6)*2^32 us NtpTime'sfraction
#define  NTPFRAC(x) (4294 * (x) + ((1981 * (x)) >> 11))  

#define  USEC(x) (((x) >> 12) - 759 * ((((x) >> 10) + 32768) >> 16))

//#define DEF_NTP_SERVER "stdtime.gov.hk" //HK server

//#define DEF_NTP_SERVER "pool.ntp.org"   //ntp server

struct NtpTime{
    unsigned int  integer;
    unsigned int  fraction;
};

DECLARE_CLASS(NtpClient) {
public:
    _NtpClient();

    int bind(String url,int port = 123,long duration = 1000*5);

    long get();

    void close();

    ~_NtpClient();

private:
    
    String mServerIp;

    Socket mSock;

    int mPort;

    void generateNtpPacket(char *);
    
    double get_rrt(const struct NtpPacket *ntp, const struct timeval *recvtv);

    double get_offset(const struct NtpPacket *ntp, const struct timeval *recvtv);

};

}

#endif

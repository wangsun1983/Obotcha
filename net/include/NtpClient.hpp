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


#define  NTPFRAC(x) (4294 * (x) + ((1981 * (x)) >> 11))  

#define  USEC(x) (((x) >> 12) - 759 * ((((x) >> 10) + 32768) >> 16))

struct NtpTime{
    uint64_t  integer;
    uint64_t  fraction;
};

DECLARE_CLASS(NtpClient) {
public:
    _NtpClient() = default;

    int bind(String url,in_port_t port = 123,int duration = 1000*5);

    long get();

    void close();

    ~_NtpClient() override;

private:
    static const uint64_t kJan1970;
    static const int kNtpDataSize;

    String mServerIp;

    Socket mSock;

    int mPort;

    void generateNtpPacket(char *) const;
    
    double get_rrt(const struct NtpPacket *ntp, const struct timeval *recvtv);

    double get_offset(const struct NtpPacket *ntp, const struct timeval *recvtv);

};

}

#endif

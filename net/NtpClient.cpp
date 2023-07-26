#include <chrono>
#include <sys/time.h>

#include "Error.hpp"
#include "InetAddress.hpp"
#include "NtpClient.hpp"
#include "SocketBuilder.hpp"
#include "System.hpp"
#include "TimeZone.hpp"
#include "HttpUrl.hpp"

namespace obotcha {

const uint64_t st(NtpClient)::kJan1970 = 0x83aa7e80; //3600s*24h*(365days*70years+17days)
const int st(NtpClient)::kNtpDataSize = 48;
/*
 * Convert time to unix standard time NTP is number of seconds since 0000
 * UT on 1 January 1900 unix time is seconds since 0000 UT on 1 January
 * 1970 There has been a trend to add a 2 leap seconds every 3 years.
 * Leap seconds are only an issue the last second of the month in June and
 * December if you don't try to set the clock then it can be ignored but
 * this is importaint to people who coordinate times with GPS clock sources.
 */
//#define NTP_TIMESTAMP_DELTA 2208988800ull

int _NtpClient::bind(String url, int port, long duration) {
    ArrayList<InetAddress> servers = createHttpUrl(url)->getInetAddress();
    if (servers->size() == 0) {
        return -1;
    }
    InetAddress address = servers->get(0);
    address->setPort(port);

    SocketOption option = createSocketOption();
    option->setRcvTimeout(duration);
    mSock = createSocketBuilder()
                ->setAddress(address)
                ->setOption(option)
                ->newDatagramSocket();
    return mSock->connect();
}

long _NtpClient::get() {
    ByteArray packet = createByteArray(kNtpDataSize);
    generateNtpPacket((char *)packet->toValue());

    mSock->getOutputStream()->write(packet);

    ByteArray pack = createByteArray(1024 * 4);
    if(mSock->getInputStream()->read(pack) < 0) {
        return -1;
    }

    unsigned int *data = (unsigned int *)pack->toValue();

    NtpTime oritime, rectime, tratime, destime;
    struct timeval offtime, dlytime;
    struct timeval now;

    gettimeofday(&now, nullptr);
    destime.integer = now.tv_sec + kJan1970;
    destime.fraction = NTPFRAC(now.tv_usec);

#define DATA(i) ntohl(((unsigned int *)data)[i])

    oritime.integer = DATA(6);
    oritime.fraction = DATA(7);
    rectime.integer = DATA(8);
    rectime.fraction = DATA(9);
    tratime.integer = DATA(10);
    tratime.fraction = DATA(11);

#undef DATA

    // Originate Timestamp       T1        client send time
    // Receive Timestamp         T2        server receive time
    // Transmit Timestamp        T3        server response time
    // Destination Timestamp     T4        client receive time
    // net delay(d)
    // d = (T2 - T1) + (T4 - T3); t = [(T2 - T1) + (T3 - T4)] / 2;

#define MKSEC(ntpt) ((ntpt).integer - kJan1970)

#define MKUSEC(ntpt) (USEC((ntpt).fraction))

#define TTLUSEC(sec, usec) ((long long)(sec)*1000000 + (usec))

#define GETSEC(us) ((us) / 1000000)

#define GETUSEC(us) ((us) % 1000000)
    long long orius, recus, traus, desus, offus, dlyus;
    orius = TTLUSEC(MKSEC(oritime), MKUSEC(oritime));
    recus = TTLUSEC(MKSEC(rectime), MKUSEC(rectime));
    traus = TTLUSEC(MKSEC(tratime), MKUSEC(tratime));
    desus = TTLUSEC(now.tv_sec, now.tv_usec);

    offus = ((recus - orius) + (traus - desus)) / 2;
    dlyus = (recus - orius) + (desus - traus);

    offtime.tv_sec = GETSEC(offus);
    offtime.tv_usec = GETUSEC(offus);
    dlytime.tv_sec = GETSEC(dlyus);
    dlytime.tv_usec = GETUSEC(dlyus);

    struct timeval newTime;
    // corse time
    // new.tv_sec = tratime.integer - kJan1970;
    // new.tv_usec = USEC(tratime.fraction);

    // fine time
    newTime.tv_sec = destime.integer - kJan1970 + offtime.tv_sec;
    newTime.tv_usec = USEC(destime.fraction) + offtime.tv_usec;

    return newTime.tv_sec * 1000 + newTime.tv_usec / 1000;
}

void _NtpClient::generateNtpPacket(char *v) {
    //int ret;
    struct timeval now;

    static const int LI = 0;       // head
    static const int VN = 3;       // version
    static const int MODE = 3;     // mode: client request
    static const int STRATUM = 0;
    static const int POLL = 4;     // max interval
    static const int PREC = -6;

    unsigned int *data = (unsigned int *)v;

    data[0] = htonl((LI << 30) | (VN << 27) | (MODE << 24) | (STRATUM << 16) |
                    (POLL << 8) | (PREC & 0xff));
    data[1] = htonl(1 << 16);
    data[2] = htonl(1 << 16);

    gettimeofday(&now, nullptr);

    data[10] = htonl(now.tv_sec + kJan1970);
    data[11] = htonl(NTPFRAC(now.tv_usec));
}

void _NtpClient::close() { 
    mSock->close(); 
}

_NtpClient::~_NtpClient() { 
    mSock->close(); 
}

} // namespace obotcha

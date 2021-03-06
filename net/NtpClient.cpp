#include <sys/time.h>
#include <chrono>

#include "NtpClient.hpp"
#include "InetAddress.hpp"
#include "System.hpp"
#include "TimeZone.hpp"
#include "Error.hpp"
#include "SocketBuilder.hpp"
#include "URL.hpp"

namespace obotcha {

/*
   * Convert time to unix standard time NTP is number of seconds since 0000
   * UT on 1 January 1900 unix time is seconds since 0000 UT on 1 January
   * 1970 There has been a trend to add a 2 leap seconds every 3 years.
   * Leap seconds are only an issue the last second of the month in June and
   * December if you don't try to set the clock then it can be ignored but
   * this is importaint to people who coordinate times with GPS clock sources.
   */
#define NTP_TIMESTAMP_DELTA 2208988800ull

_NtpSocketClientListener::_NtpSocketClientListener(Condition c,Mutex m) {
    mCondition = c;
    mMutex = m;
}

_NtpSocketClientListener::~_NtpSocketClientListener() {
    if(mListener != nullptr) {
        mListener->onClose();
    }
    milliseconds = -1;
    mCondition->notify();
}

void _NtpSocketClientListener::onSocketMessage(int event,Socket s,ByteArray data) {
    switch(event) {
        case st(Socket)::Message:
        return onDataReceived(s,data);

        case st(Socket)::Connect:
        case st(Socket)::Disconnect:
        default:
        return;
    }
}

void _NtpSocketClientListener::onDataReceived(Socket r,ByteArray pack) {
    //int  ret;
    unsigned int *data = (unsigned int *)pack->toValue(); 

    NtpTime oritime, rectime, tratime, destime;
    struct  timeval offtime, dlytime;
    struct  timeval now;

    gettimeofday(&now, NULL);
    destime.integer  = now.tv_sec + JAN_1970;
    destime.fraction = NTPFRAC (now.tv_usec);

#define  DATA(i) ntohl((( unsigned   int  *)data)[i])

    oritime.integer  = DATA(6);
    oritime.fraction = DATA(7);
    rectime.integer  = DATA(8);
    rectime.fraction = DATA(9);
    tratime.integer  = DATA(10);
    tratime.fraction = DATA(11);
    
#undef  DATA

    //Originate Timestamp       T1        client send time 
    //Receive Timestamp         T2        server receive time
    //Transmit Timestamp        T3        server response time
    //Destination Timestamp     T4        client receive time
    //net delay(d)
    //d = (T2 - T1) + (T4 - T3); t = [(T2 - T1) + (T3 - T4)] / 2;

#define  MKSEC(ntpt)   ((ntpt).integer - JAN_1970)

#define  MKUSEC(ntpt)  (USEC((ntpt).fraction))

#define  TTLUSEC(sec,usec)   (( long   long )(sec)*1000000 + (usec))

#define  GETSEC(us)    ((us)/1000000) 

#define  GETUSEC(us)   ((us)%1000000) 
    long   long  orius, recus, traus, desus, offus, dlyus;
    orius = TTLUSEC(MKSEC(oritime), MKUSEC(oritime));
    recus = TTLUSEC(MKSEC(rectime), MKUSEC(rectime));
    traus = TTLUSEC(MKSEC(tratime), MKUSEC(tratime));
    desus = TTLUSEC(now.tv_sec, now.tv_usec);

    offus = ((recus - orius) + (traus - desus))/2;
    dlyus = (recus - orius) + (desus - traus);

    offtime.tv_sec  = GETSEC(offus);
    offtime.tv_usec = GETUSEC(offus);
    dlytime.tv_sec  = GETSEC(dlyus);
    dlytime.tv_usec = GETUSEC(dlyus);

    struct  timeval  newTime ;
    //corse time
    //new.tv_sec = tratime.integer - JAN_1970;
    //new.tv_usec = USEC(tratime.fraction);
    
    //fine time
    newTime.tv_sec = destime.integer - JAN_1970 + offtime.tv_sec;
    newTime.tv_usec = USEC(destime.fraction) + offtime.tv_usec;

    milliseconds = newTime.tv_sec*1000 + newTime.tv_usec/1000;
    mCondition->notify();
    
    if(mListener != nullptr) {
        mListener->onAccept(milliseconds);
    }
}


void _NtpSocketClientListener::setTimeCallback(NtpListener l) {
    mListener = l;
}

long int _NtpSocketClientListener::getTimeMillis() {
    return milliseconds; 
}

_NtpClient::_NtpClient() {
    mMutex = createMutex();
    mCondition = createCondition();
    mListener = createNtpSocketClientListener(mCondition,mMutex);
}

int _NtpClient::bind(String url,int port = 123) {
    ArrayList<InetAddress> servers = createURL(url)->getInetAddress();
    if(servers->size() == 0) {
        return -NetConnectFail;
    }

    InetAddress address = servers->get(0);
    address->setPort(port);

    mSock = createSocketBuilder()
            ->setAddress(address)
            ->newDatagramSocket();
            
    mSockMonitor = createSocketMonitor();
    mSockMonitor->bind(mSock,AutoClone(this));
    //mClient = createUdpClient(mServerIp,port,mListener);
    //mClient->start();
}

long _NtpClient::getCurrentTimeSync() {
    char mNtpPacket[NTP_DATA_SIZE];
    memset(mNtpPacket,0,sizeof(mNtpPacket));
    generateNtpPacket(mNtpPacket);
    //unsigned int *v = (unsigned int *)mNtpPacket;

    ByteArray packet = createByteArray((byte *)mNtpPacket,NTP_DATA_SIZE);
    //mClient->send(packet);
    mSock->getOutputStream()->write(packet);
    {
        AutoLock l(mMutex);
        mCondition->wait(mMutex);
    }

    return mListener->getTimeMillis();
}

void _NtpClient::getCurrentTimeAsync(NtpListener l) {
    mListener->setTimeCallback(l);
    char mNtpPacket[NTP_DATA_SIZE];
    memset(mNtpPacket,0,sizeof(mNtpPacket));
    generateNtpPacket(mNtpPacket);

    ByteArray packet = createByteArray((byte *)mNtpPacket,NTP_DATA_SIZE);
    //mClient->send(packet);
    mSock->getOutputStream()->write(packet);
}

void _NtpClient::generateNtpPacket(char *v) {
    int  ret;
    struct  timeval now;

#define  LI 0             //head
#define  VN 3             //version
#define  MODE 3           //mode: client request
#define  STRATUM 0
#define  POLL 4           //max interval
#define  PREC -6          
    unsigned int *data = (unsigned int *)v;

    data[0] = htonl((LI << 30) | (VN << 27) | (MODE << 24) 
        | (STRATUM << 16) | (POLL << 8) | (PREC & 0xff));
    data[1] = htonl(1 << 16);
    data[2] = htonl(1 << 16);

    gettimeofday(&now, NULL);

    data[10] = htonl(now.tv_sec + JAN_1970);
    data[11] = htonl(NTPFRAC(now.tv_usec));
}

void _NtpClient::release() {
    mSock->close();
}

_NtpClient::~_NtpClient() {
    mSock->close();
}


}

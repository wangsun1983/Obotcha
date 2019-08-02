#include <sys/time.h>
#include <chrono>

#include "NtpClient.hpp"
#include "InetAddress.hpp"
#include "System.hpp"
#include "TimeZone.hpp"

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


void _NtpSocketClientListener::onAccept(int fd,String ip,int port,ByteArray pack) {
    struct tm t;

    NtpPacket *p = (NtpPacket *)pack->toValue();
    long int txTm_s = ntohl(p->txTm_s) - NTP_TIMESTAMP_DELTA;
    long int txTm_f = ntohl(p->txTm_f);
    printf("txTm_f is %ld \n",txTm_f);

    localtime_r((const time_t*)&txTm_s,&t);
    milliseconds = mktime(&t) *1000;
    printf("milliseconds is %ld \n",milliseconds);
    printf("current time is %ld \n",st(System)::currentTimeMillis());
    mCondition->notify();
    
    if(mListener != nullptr) {
        mListener->onAccept(milliseconds);
    }
}

void _NtpSocketClientListener::setTimeCallback(NtpListener l) {
    mListener = l;
}
    
void _NtpSocketClientListener::onDisconnect(int fd) {

}
    
void _NtpSocketClientListener::onConnect(int fd,String ip,int port) {

}

void _NtpSocketClientListener::onConnect(int fd,String domain) {

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
    ArrayList<String> servers = st(InetAddress)::getHostByName(url);
    if(servers->size() == 0) {
        return -NtpFailConnectFail;
    }

    mServerIp = servers->get(0);

    mClient = createUdpClient(mServerIp,port,mListener);
    
    mClient->start();
}

long _NtpClient::getCurrentTimeSync() {
    memset(&mNtpPacket,0,sizeof(NtpPacket));

    // Set the first byte's bits to 00,011,011 for li = 0, vn = 3, and mode = 3. The rest will be left set to zero.
   *((char*) &mNtpPacket + 0) = 0x1b; // Represents 27 in base 10 or 00011011 in base 2.
    
    ByteArray packet = createByteArray((char *)&mNtpPacket,sizeof(NtpPacket));
    mClient->send(packet);
    {
        AutoMutex l(mMutex);
        mCondition->wait(mMutex);
    }

    return mListener->getTimeMillis();
}

void _NtpClient::getCurrentTimeAsync(NtpListener l) {
    mListener->setTimeCallback(l);
    memset(&mNtpPacket,0,sizeof(NtpPacket));

    // Set the first byte's bits to 00,011,011 for li = 0, vn = 3, and mode = 3. The rest will be left set to zero.
    *((char*) &mNtpPacket + 0) = 0x1b; // Represents 27 in base 10 or 00011011 in base 2.
    
    ByteArray packet = createByteArray((char *)&mNtpPacket,sizeof(NtpPacket));
    mClient->send(packet);
}

void _NtpClient::release() {
    mClient->release();
}

_NtpClient::~_NtpClient() {
    mClient->release();
}


}

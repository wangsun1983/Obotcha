#ifndef __OBOTCHA_SOCKET_OPTION_HPP__
#define __OBOTCHA_SOCKET_OPTION_HPP__

#include <sys/stat.h>
#include <unistd.h>    
#include <sys/types.h>
#include <netinet/in.h>
#include <net/if.h>
#include <linux/filter.h>
#include <fstream>
#include <sys/un.h>

#include "Object.hpp"
#include "String.hpp"
#include "InetAddress.hpp"
#include "FileDescriptor.hpp"

namespace obotcha {

DECLARE_CLASS(SocketOption) {
public:
    static const int DefaultBuffSize;
    static const int DefaultWaitAcceptQueueSize;

    _SocketOption() = default;
    ~_SocketOption() override;

    void update(FileDescriptor);
    static int get(FileDescriptor,
                  int level, 
                  int optname, 
                  void *optval,
                  socklen_t *oplen);
    
    _SocketOption* setReUseAddr(int);
    _SocketOption* setDnotRoute(int);
    _SocketOption* setBroadcast(int);
    _SocketOption* setSndBuffSize(int);
    _SocketOption* setRcvBuffSize(int);
    _SocketOption* setSndBuffForce(int);
    _SocketOption* setRcvBuffForce(int);
    _SocketOption* setKeepAlive(int);
    _SocketOption* setOobInline(int);
    _SocketOption* setNoCheck(int);
    _SocketOption* setLinger(int,int);
    _SocketOption* setReUsePort(int);
    _SocketOption* setPassCred(int);
    _SocketOption* setPeerCred(int);
    _SocketOption* setRcvLoWat(int);
    _SocketOption* setSndLoWat(int);
    _SocketOption* setRcvTimeout(int);
    _SocketOption* setSndTimeout(int);
    _SocketOption* setConnectTimeout(int); //use mSendTimeout
    _SocketOption* setBindToDevice(struct ifreq *);
    _SocketOption* setAttachFilter(struct sock_fprog *);
    _SocketOption* setDetachFilter(int);
    _SocketOption* setTimeStamp(int);
    _SocketOption* setTimeStampNs(int);
    _SocketOption* setTimeStampIng(int);
    _SocketOption* setBusyPoll(int);
    _SocketOption* setMaxPacingRate(unsigned int);
    _SocketOption* setReusePortCbpf(struct sock_fprog*);
    _SocketOption* setReusePortEbpf(int);
    _SocketOption* setZeroCopy(int);
    _SocketOption* setWaitAcceptQueueSize(int);

    //support for SSL Socket
    _SocketOption* setSSLCertificatePath(String);
    _SocketOption* setSSLKeyPath(String);

    int getReUseAddr() const;
    int getDnotRoute() const;
    int getBroadcast() const;
    int getSndBuffSize() const;
    int getRcvBuffSize() const;
    int getSndBuffForce() const;
    int getRcvBuffForce() const;
    int getKeepAlive() const;
    int getOobInline() const;
    int getNoCheck() const;
    int getLingerOnOFF() const;
    int getLingerValue() const;
    int getReUsePort() const;
    int getPassCred() const;
    int getPeerCred() const;
    int getRcvLoWat() const;
    int getSndLoWat() const;
    int getRcvTimeout() const;
    int getSndTimeout() const;
    void getBindToDevice(struct ifreq *) const;
    void getAttachFilter(struct sock_fprog *) const;
    int getDetachFilter() const;
    int getTimeStamp() const;
    int getTimeStampNs() const;
    int getTimeStampIng() const;
    int getBusyPoll() const;
    unsigned int getMaxPacingRate() const;
    void getReusePortCbpf(struct sock_fprog*) const;
    int getReusePortEbpf() const;
    int getZeroCopy() const;
    int getRecvTimeout() const;
    int getSendTimeout() const;
    int getConnectTimeout() const;
    int getWaitAcceptQueueSize() const;

    //support SSL Socket
    String getSSLCertificatePath() const;
    String getSSLKeyPath() const;

    enum Switcher {
        Off = 0,
        On = 1,
    };

private:
    int mReUseAddr = -1;         //SO_REUSEADDR(on/off)
    int mDontRoute = -1;         //SO_DONTROUTE(on/off)
    int mBroadCast = -1;         //SO_BROADCAST(on/off)
    int mSendBuf = DefaultBuffSize;           //SO_SNDBUF
    int mRcvBuff = DefaultBuffSize;           //SO_RCVBUF
    int mSendBuffForce = -1;     //SO_SNDBUFFORCE
    int mRcvBuffForce = -1;      //SO_RCVBUFFORCE
    int mKeepAlive = -1;         //SO_KEEPALIVE(on/off)
    int mOobInline = -1;         //SO_OOBINLINE
    int mNoCheck = -1;           //SO_NO_CHECK
    int mPriority = -1;          //SO_PRIORITY(0~6)
    int mLingerOnOff = -1;       //SO_LINGER
    int mLingerValue = -1;       //SO_LINGER
    int mReUsePort = -1;         //SO_REUSEPORT(on/off)
    int mPassCred = -1;          //SO_PASSCRED(on/off)
    int mPeerCred = -1;          //SO_PEERCRED
    int mRcvLoWat = -1;          //SO_RCVLOWAT
    int mSndLoWat = -1;          //SO_SNDLOWAT
    int mRcvTimeout = -1;        //SO_RCVTIMEO 
    int mSendTimeout = -1;       //SO_SNDTIMEO
    int mConnTimeout  = -1;

    struct ifreq *mBindToDevice = nullptr;            //SO_BINDTODEVICE(struct ifreq ifr)
    struct sock_fprog *mAttachFilter = nullptr;       //SO_ATTACH_FILTER
    int mDetachFilter = -1;                      //SO_DETACH_FILTER
                                            //SO_GET_FILTER(no use)
                                            //SO_PEERNAME(no use)
    int mTimeStamp = -1;                         //SO_TIMESTAMP
                                            //SO_ACCEPTCONN(no use)
                                            //SO_PEERSEC(no use)
                                            //SO_PASSSEC(no use)
    int mTimeStampNs = -1;                       //SO_TIMESTAMPNS
    int mTimeStampIng = -1;                      //SO_TIMESTAMPING
                                            //SO_PROTOCOL(no use)
                                            //SO_DOMAIN(no use)
                                            //SO_RXQ_OVFL(no use)
                                            //SO_WIFI_STATUS(no use)
                                            //SO_PEEK_OFF(no use)
                                            //SO_NOFCS(no use)
                                            //SO_LOCK_FILTER(no use)
                                            //SO_SELECT_ERR_QUEUE(no use)
    int mBusyPoll = -1;                          //SO_BUSY_POLL                                                                                       
    long int mMaxPacingRate = -1;                //SO_MAX_PACING_RATE
                                            //SO_INCOMING_CPU(no use)
                                            //SO_ATTACH_BPF(no use)
                                            //SO_DETACH_BPF(no use)
    struct sock_fprog *mReusePortCbpf = nullptr;      //SO_ATTACH_REUSEPORT_CBPF
    int mReusePortEbpf = -1;                     //SO_ATTACH_REUSEPORT_EBPF
                                            //SO_CNX_ADVICE(no use)
                                            //SCM_TIMESTAMPING_OPT_STATS(no use)
                                            //SO_MEMINFO(no use)
                                            //SO_INCOMING_NAPI_ID(no use)
                                            //SO_COOKIE(no use)
                                            //SCM_TIMESTAMPING_PKTINFO(no use)
                                            //SO_PEERGROUPS(no use)
    int mZeroCopy = -1;                          //SO_ZEROCOPY

    int mWaitAcceptQueueSize = DefaultWaitAcceptQueueSize;
    //support SSL Socket
    String mSSLCertificatePath;
    String mSSLKeyPath;
};

}
#endif

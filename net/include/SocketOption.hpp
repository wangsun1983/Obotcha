#ifndef __OBOTCHA_SOCKET_OPTION_HPP__
#define __OBOTCHA_SOCKET_OPTION_HPP__

#include <sys/stat.h>
#include <unistd.h>    
#include <sys/types.h>
#include <netinet/in.h>
#include <net/if.h>
#include <linux/filter.h>
#include <mqueue.h>
#include <fstream>
#include <sys/un.h>

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "InetAddress.hpp"


namespace obotcha {

DECLARE_SIMPLE_CLASS(SocketOption) {
public:
    friend class _SocketImpl;
    friend class _HttpOption;

    static const int DefaultBuffSize;

    _SocketOption();
    ~_SocketOption();
    
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
    _SocketOption* setRecvTimeout(int);
    _SocketOption* setSendTimeout(int);
    _SocketOption* setConnectionNum(int);
    _SocketOption* setBuffSize(int);

    int getReUseAddr();
    int getDnotRoute();
    int getBroadcast();
    int getSndBuffSize();
    int getRcvBuffSize();
    int getSndBuffForce();
    int getRcvBuffForce();
    int getKeepAlive();
    int getOobInline();
    int getNoCheck();
    int getLingerOnOFF();
    int getLingerValue();
    int getReUsePort();
    int getPassCred();
    int getPeerCred();
    int getRcvLoWat();
    int getSndLoWat();
    int getRcvTimeout();
    int getSndTimeout();
    void getBindToDevice(struct ifreq *);
    void getAttachFilter(struct sock_fprog *);
    int getDetachFilter();
    int getTimeStamp();
    int getTimeStampNs();
    int getTimeStampIng();
    int getBusyPoll();
    unsigned int getMaxPacingRate();
    void getReusePortCbpf(struct sock_fprog*);
    int getReusePortEbpf();
    int getZeroCopy();
    int getRecvTimeout();
    int getSendTimeout();
    int getBuffSize();
    int getConnectionNum();

    enum Switcher {
        Off = 0,
        On = 1,
    };

private:
    int mReUseAddr;         //SO_REUSEADDR(on/off)
    int mDontRoute;         //SO_DONTROUTE(on/off)
    int mBroadCast;         //SO_BROADCAST(on/off)
    int mSendBuf;           //SO_SNDBUF
    int mRcvBuff;           //SO_RCVBUF
    int mSendBuffForce;     //SO_SNDBUFFORCE
    int mRcvBuffForce;      //SO_RCVBUFFORCE
    int mKeepAlive;         //SO_KEEPALIVE(on/off)
    int mOobInline;         //SO_OOBINLINE
    int mNoCheck;           //SO_NO_CHECK
    int mPriority;          //SO_PRIORITY(0~6)
    int mLingerOnOff;       //SO_LINGER
    int mLingerValue;       //SO_LINGER
                            //SO_BSDCOMPAT(no use)
    int mReUsePort;         //SO_REUSEPORT(on/off)
    int mPassCred;          //SO_PASSCRED(on/off)
    int mPeerCred;          //SO_PEERCRED
    int mRcvLoWat;          //SO_RCVLOWAT
    int mSndLoWat;          //SO_SNDLOWAT
    int mRcvTimeout;        //SO_RCVTIMEO 
    int mSendTimeout;       //SO_SNDTIMEO
                            //SO_SECURITY_AUTHENTICATION(no use)
                            //SO_SECURITY_ENCRYPTION_TRANSPORT(no use)
                            //SO_SECURITY_ENCRYPTION_NETWORK(no use)

    struct ifreq *mBindToDevice;            //SO_BINDTODEVICE(struct ifreq ifr)
    struct sock_fprog *mAttachFilter;       //SO_ATTACH_FILTER
    int mDetachFilter;                      //SO_DETACH_FILTER
                                            //SO_GET_FILTER(no use)
                                            //SO_PEERNAME(no use)
    int mTimeStamp;                         //SO_TIMESTAMP
                                            //SO_ACCEPTCONN(no use)
                                            //SO_PEERSEC(no use)
                                            //SO_PASSSEC(no use)
    int mTimeStampNs;                       //SO_TIMESTAMPNS
    int mTimeStampIng;                      //SO_TIMESTAMPING
                                            //SO_PROTOCOL(no use)
                                            //SO_DOMAIN(no use)
                                            //SO_RXQ_OVFL(no use)
                                            //SO_WIFI_STATUS(no use)
                                            //SO_PEEK_OFF(no use)
                                            //SO_NOFCS(no use)
                                            //SO_LOCK_FILTER(no use)
                                            //SO_SELECT_ERR_QUEUE(no use)
    int mBusyPoll;                          //SO_BUSY_POLL                                                                                       
    long int mMaxPacingRate;                //SO_MAX_PACING_RATE
                                            //SO_INCOMING_CPU(no use)
                                            //SO_ATTACH_BPF(no use)
                                            //SO_DETACH_BPF(no use)
    struct sock_fprog *mReusePortCbpf;      //SO_ATTACH_REUSEPORT_CBPF
    int mReusePortEbpf;                     //SO_ATTACH_REUSEPORT_EBPF
                                            //SO_CNX_ADVICE(no use)
                                            //SCM_TIMESTAMPING_OPT_STATS(no use)
                                            //SO_MEMINFO(no use)
                                            //SO_INCOMING_NAPI_ID(no use)
                                            //SO_COOKIE(no use)
                                            //SCM_TIMESTAMPING_PKTINFO(no use)
                                            //SO_PEERGROUPS(no use)
    int mZeroCopy;                          //SO_ZEROCOPY




    int mConnectNum;
    int mBuffSize;
};

}
#endif

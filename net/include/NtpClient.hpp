#ifndef __NTP_CLIENT_HPP__
#define __NTP_CLIENT_HPP__

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
#include "UdpClient.hpp"
#include "SocketListener.hpp"
#include "Condition.hpp"
#include "Mutex.hpp"


namespace obotcha {

enum NtpFailReason {
    NtpFailConnectFail = 200,
};

struct NtpPacket{

    uint8_t li_vn_mode;      // Eight bits. li, vn, and mode.
                             // li.   Two bits.   Leap indicator.
                             // vn.   Three bits. Version number of the protocol.
                             // mode. Three bits. Client will pick mode 3 for client.

    uint8_t stratum;         // Eight bits. Stratum level of the local clock.
    uint8_t poll;            // Eight bits. Maximum interval between successive messages.
    uint8_t precision;       // Eight bits. Precision of the local clock.

    uint32_t rootDelay;      // 32 bits. Total round trip delay time.
    uint32_t rootDispersion; // 32 bits. Max error aloud from primary clock source.
    uint32_t refId;          // 32 bits. Reference clock identifier.

    uint32_t refTm_s;        // 32 bits. Reference time-stamp seconds.
    uint32_t refTm_f;        // 32 bits. Reference time-stamp fraction of a second.

    uint32_t origTm_s;       // 32 bits. Originate time-stamp seconds.
    uint32_t origTm_f;       // 32 bits. Originate time-stamp fraction of a second.

    uint32_t rxTm_s;         // 32 bits. Received time-stamp seconds.
    uint32_t rxTm_f;         // 32 bits. Received time-stamp fraction of a second.

    uint32_t txTm_s;         // 32 bits and the most important field the client cares about. Transmit time-stamp seconds.
    uint32_t txTm_f;         // 32 bits. Transmit time-stamp fraction of a second.

};              // Total: 384 bits or 48 bytes.

DECLARE_SIMPLE_CLASS(NtpListener) {
public:
    virtual void onAccept(long int millseconds);
    virtual void onClose();
};

DECLARE_SIMPLE_CLASS(NtpSocketClientListener) IMPLEMENTS(SocketListener) {
public:
    _NtpSocketClientListener(Condition,Mutex);

    void onAccept(int fd,String ip,int port,ByteArray pack);
    
    void onDisconnect(int fd);
    
    void onConnect(int fd,String ip,int port);

    void onConnect(int fd,String domain);

    void setTimeCallback(NtpListener);

    long int getTimeMillis();

    ~_NtpSocketClientListener();

private:
    Condition mCondition;
    Mutex mMutex;
    long int milliseconds;
    NtpListener mListener;
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

    UdpClient mClient;

    int mPort;

    NtpSocketClientListener mListener;

    Mutex mMutex;

    Condition mCondition;

    NtpPacket mNtpPacket;

    NtpListener mNtpListener;
};

}

#endif

#ifndef __OBOTCHA_HTTP_OPTION_HPP__
#define __OBOTCHA_HTTP_OPTION_HPP__

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
#include "InetAddress.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(HttpOption) {
public:
    _HttpOption();
    _HttpOption* setRecvTimeout(int);
    _HttpOption* setSendTimeout(int);
    _HttpOption* setConnectionNum(int);
    _HttpOption* setCertificate(String);
    _HttpOption* setKey(String);
    
    int getRcvTimeout();
    int getSendTimeout();
    int getConnectionNum();
    String getCertificate();
    String getKey();
    
private:
    int mRcvTimeout;
    int mSendTimeout;
    int mConnectNum;
    String mCretificate;
    String mKey;
};

}
#endif

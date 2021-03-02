#ifndef __OBOTCHA_SSL_INFO_HPP_
#define __OBOTCHA_SSL_INFO_HPP_

#include <sys/stat.h>
#include <unistd.h>    
#include <sys/types.h>
#include <netinet/in.h>
#include <mqueue.h>
#include <fstream>
#include <sys/un.h>

extern "C" {
#include "openssl/ssl.h"
#include "openssl/err.h"
}


#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "InetAddress.hpp"
#include "SocketListener.hpp"
#include "Mutex.hpp"
#include "Pipe.hpp"
#include "Thread.hpp"
#include "SocketListener.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(SSLInfo) {
public:
    _SSLInfo(String certificate,String key);

    _SSLInfo();

    SSL *getSSL();
    
    int bindSocket(int sock);

    int getSocket();

    int read(ByteArray);

    int write(ByteArray);

    int write(ByteArray,int);

    ~_SSLInfo();

private:
    SSL *mSSL;
    SSL_CTX *mCtx;

    String mCertificate;
    String mKey;

    int mSock;
};

}
#endif

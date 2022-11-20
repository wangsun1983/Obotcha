#ifndef __OBOTCHA_SSL_SERVER_SOCKET_CONTEXT_HPP__
#define __OBOTCHA_SSL_SERVER_SOCKET_CONTEXT_HPP__

extern "C" {
    #include "openssl/ssl.h"
    #include "openssl/err.h"
}

#include "Object.hpp"

namespace obotcha {

DECLARE_CLASS(SSLSocketContext) {
public:
    _SSLSocketContext(int);
    void initSSL();
    
    SSL *getSSL();
    SSL_CTX *getCtx();
    ~_SSLSocketContext();
    enum Type {
        SERVER,
        CLIENT
    };

private:
    SSL *mSSL;
    SSL_CTX *mCtx;

    int type;
};

}

#endif
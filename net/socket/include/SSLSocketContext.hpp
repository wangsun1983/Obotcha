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
    enum class Type {
        Server,
        Client
    };

    explicit _SSLSocketContext(_SSLSocketContext::Type);
    void initSSL();
    
    SSL *getSSL();
    SSL_CTX *getCtx();
    ~_SSLSocketContext() override;

private:
    SSL *mSSL = nullptr;
    SSL_CTX *mCtx = nullptr;
};

}

#endif
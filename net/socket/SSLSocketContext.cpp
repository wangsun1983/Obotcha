#include "SSLSocketContext.hpp"
#include "InitializeException.hpp"

namespace obotcha {

_SSLSocketContext::_SSLSocketContext(int type) {
    mSSL = nullptr;
    mCtx = nullptr;

    /* int ssl  */
    SSL_library_init();
    /* load SSL algorithms */
    OpenSSL_add_all_algorithms();
    /* load SSL error strings */
    SSL_load_error_strings();

    /*can use SSLv2_server_method() or SSLv3_server_method()*/
    switch(type) {
        case CLIENT:
        mCtx = SSL_CTX_new(SSLv23_client_method());
        break;

        case SERVER:
        mCtx = SSL_CTX_new(SSLv23_server_method());
        break;
    }

    if (mCtx == nullptr) {
        Trigger(InitializeException,"SSL Create error");
    }
}

void _SSLSocketContext::initSSL() {
    mSSL = SSL_new(mCtx);
}

SSL *_SSLSocketContext::getSSL() {
    return mSSL;
}

SSL_CTX *_SSLSocketContext::getCtx() {
    return mCtx;
}

_SSLSocketContext::~_SSLSocketContext() {
    if(mSSL != nullptr) {
        SSL_shutdown (mSSL);
        SSL_free (mSSL);
        mSSL = nullptr;
    }

    if (mCtx != nullptr) {
        SSL_CTX_free(mCtx);
        mCtx = nullptr;
    }
}

}

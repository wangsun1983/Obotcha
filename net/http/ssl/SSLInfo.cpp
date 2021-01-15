#include "SSLInfo.hpp"
#include "Enviroment.hpp"
#include "Error.hpp"

namespace obotcha {


_SSLInfo::_SSLInfo(String certificate,String key) {
    mCertificate = certificate;
    mKey = key;

    if(certificate == nullptr) {
        mCertificate = st(Enviroment)::getInstance()->get(st(Enviroment)::gHttpSslCertificatePath);
    }
    
    if(mKey == nullptr) {
        mKey = st(Enviroment)::getInstance()->get(st(Enviroment)::gHttpSslKeyPath);
    }

    mSock = -1;

    /* int ssl  */
    SSL_library_init();
    /* load SSL algorithms */
    OpenSSL_add_all_algorithms();
    /* load SSL error strings */
    SSL_load_error_strings();

    /*can use SSLv2_server_method() or SSLv3_server_method()*/
    mCtx = SSL_CTX_new(SSLv23_server_method());
    if (mCtx == NULL) {
        throw InitializeException("SSL Create error");
    }
    /* load user certificate,this certificati is used to send to client,certificate contains public key */
    if (SSL_CTX_use_certificate_file(mCtx, mCertificate->toChars(), SSL_FILETYPE_PEM) <= 0) {
	    throw InitializeException("SSL certificate use error");
    }
    /* load private key */
    if (SSL_CTX_use_PrivateKey_file(mCtx, mKey->toChars(), SSL_FILETYPE_PEM) <= 0) {
        throw InitializeException("SSL private key use error");
    }
    /* check whether private is ok */
    if (!SSL_CTX_check_private_key(mCtx)) {
        throw InitializeException("SSL private key check error");
    }

    mSSL = SSL_new(mCtx);
}

_SSLInfo::_SSLInfo():_SSLInfo(nullptr,nullptr) {

}

int _SSLInfo::bindSocket(int sock) {
    if(!SSL_set_fd(mSSL, sock)) {
        return -NetBindFail;
    }

    if(!SSL_accept(mSSL)) {
        return -NetBindFail;
    }
    
    mSock = sock;

    return 0;
}
    
int _SSLInfo::getSocket() {
    return mSock;
}

int _SSLInfo::read(ByteArray buff) {
    if(mSSL != nullptr) {
        return SSL_read(mSSL, buff->toValue(), buff->size());
    }

    return -1;
}

int _SSLInfo::write(ByteArray b) {
    if(mSSL != nullptr) {
        return SSL_write(mSSL,b->toValue(),b->size());
    }

    return  -1;
}

int _SSLInfo::write(ByteArray b,int size) {
    if(mSSL != nullptr) {
        return SSL_write(mSSL,b->toValue(),size);
    }

    return  -1;
}

SSL *_SSLInfo::getSSL() {
    return mSSL;
}

_SSLInfo::~_SSLInfo() {
    if(mCtx != nullptr) {
        SSL_CTX_free(mCtx);
        mCtx = nullptr;
    }

    if(mSSL != nullptr) {
        SSL_shutdown(mSSL);
        SSL_free(mSSL);
        mSSL = nullptr;
    }
}

}

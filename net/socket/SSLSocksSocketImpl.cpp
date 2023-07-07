#include "SSLSocksSocketImpl.hpp"
#include "SocksSocketImpl.hpp"
#include "InitializeException.hpp"

namespace obotcha {

//this is used for creating new socket in server
_SSLSocksSocketImpl::_SSLSocksSocketImpl(SocketImpl s,SocketOption option) {
    mSocket = s;
    init(option->getSSLCertificatePath(),option->getSSLKeyPath());
}

_SSLSocksSocketImpl::_SSLSocksSocketImpl(InetAddress address,SocketOption option) {
    mSocket = createSocksSocketImpl(address,option);
    if(option != nullptr) {
        init(option->getSSLCertificatePath(),option->getSSLKeyPath());
    } else {
        init(nullptr,nullptr);
    }
}

_SSLSocksSocketImpl::_SSLSocksSocketImpl(SocketImpl impl) {
    mSocket = impl;
    init(nullptr,nullptr);
}

void _SSLSocksSocketImpl::init(String certificatePath,String keyPath) {
    if(certificatePath != nullptr) {
        mContext = createSSLSocketContext(st(SSLSocketContext)::SERVER);
        if (SSL_CTX_use_certificate_file(mContext->getCtx(), certificatePath->toChars(),
                                     SSL_FILETYPE_PEM) <= 0) {
            Trigger(InitializeException,"SSL certificate use error");
        }
        /* load private key */
        if (SSL_CTX_use_PrivateKey_file(mContext->getCtx(), keyPath->toChars(), SSL_FILETYPE_PEM) <=
            0) {
            Trigger(InitializeException,"SSL private key use error");
        }
        /* check whether private is ok */
        if (!SSL_CTX_check_private_key(mContext->getCtx())) {
            Trigger(InitializeException,"SSL private key check error");
        }
        mContext->initSSL();
    } else {
        mContext = createSSLSocketContext(st(SSLSocketContext)::CLIENT);
        mContext->initSSL();
    }

    if(!SSL_set_fd(mContext->getSSL(),mSocket->getFileDescriptor()->getFd())) {
        ERR_print_errors_fp (stderr);
    }
}

int _SSLSocksSocketImpl::connect() {
    mSocket->getFileDescriptor()->setAsync(false);

    if(mSocket->connect()) {
        return -1;
    }

    if(SSL_connect(mContext->getSSL()) < 0) {
        ERR_print_errors_fp (stderr);
    }
    return 0;
}

int _SSLSocksSocketImpl::close() {
    //do not set null,because if this socket is server
    //socket monitor will call getFileDescriptor to remove
    //socket 
    return mSocket->close();
}

int _SSLSocksSocketImpl::write(ByteArray buff,int start,int length) {
    int size = computeSutiableSize(buff,start,length);
    return SSL_write(mContext->getSSL(), buff->toValue() + start, size);
}

int _SSLSocksSocketImpl::read(ByteArray buff,int start,int length) {
    int size = computeSutiableSize(buff,start,length);
    return SSL_read(mContext->getSSL(),buff->toValue() + start,size);
}

ByteArray _SSLSocksSocketImpl::read() {
    ByteArray buff = createByteArray(1024*16);
    int size = SSL_read(mContext->getSSL(), buff->toValue(), 1024*16);
    buff->quickShrink(size);
    return buff;
}

FileDescriptor _SSLSocksSocketImpl::getFileDescriptor() {
    return mSocket->getFileDescriptor();
}

SSLSocketContext _SSLSocksSocketImpl::getSSLContext() {
    return this->mContext;
}

}

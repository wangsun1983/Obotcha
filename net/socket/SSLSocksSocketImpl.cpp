#include "SSLSocksSocketImpl.hpp"
#include "SocksSocketImpl.hpp"
#include "InitializeException.hpp"

namespace obotcha {

//this is used for creating new socket in server
_SSLSocksSocketImpl::_SSLSocksSocketImpl(SocketImpl impl,SocketOption option):mSocket(impl) {
    init(option->getSSLCertificatePath(),option->getSSLKeyPath());
}

_SSLSocksSocketImpl::_SSLSocksSocketImpl(InetAddress address,SocketOption option) {
    mSocket = SocksSocketImpl::New(address,option);
    if(option != nullptr) {
        init(option->getSSLCertificatePath(),option->getSSLKeyPath());
    } else {
        init(nullptr,nullptr);
    }
}

_SSLSocksSocketImpl::_SSLSocksSocketImpl(SocketImpl impl):mSocket(impl) {
    init(nullptr,nullptr);
}

void _SSLSocksSocketImpl::init(String certificatePath,String keyPath) {
    if(certificatePath != nullptr) {
        mContext = SSLSocketContext::New(st(SSLSocketContext)::Type::Server);
        if (SSL_CTX_use_certificate_file(mContext->getCtx(), certificatePath->toChars(),
                                     SSL_FILETYPE_PEM) <= 0) {
            Trigger(InitializeException,"SSL certificate use error")
        }
        /* load private key */
        if (SSL_CTX_use_PrivateKey_file(mContext->getCtx(), keyPath->toChars(), 
                SSL_FILETYPE_PEM) <= 0) {
            Trigger(InitializeException,"SSL private key use error")
        }
        /* check whether private is ok */
        if (!SSL_CTX_check_private_key(mContext->getCtx())) {
            Trigger(InitializeException,"SSL private key check error")
        }
        mContext->initSSL();
    } else {
        mContext = SSLSocketContext::New(st(SSLSocketContext)::Type::Client);
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

    bool isAsync = mSocket->getFileDescriptor()->isAsync();
    if(isAsync) {
        mSocket->getFileDescriptor()->setAsync(false);
    }

    //start shakehande with client
    if(SSL_connect(mContext->getSSL()) < 0) {
        ERR_print_errors_fp (stderr);
    }

    if(isAsync) {
        mSocket->getFileDescriptor()->setAsync(true);
    }
    return 0;
}

int _SSLSocksSocketImpl::close() {
    //do not set null,because if this socket is server
    //socket monitor will call getFileDescriptor to remove
    //socket 
    return mSocket->close();
}

ssize_t _SSLSocksSocketImpl::write(ByteArray buff,uint64_t start,uint64_t length) {
    auto size = computeSutiableSize(buff,start,length);
    return SSL_write(mContext->getSSL(), buff->toValue() + start, size);
}

ssize_t _SSLSocksSocketImpl::read(ByteArray buff,uint64_t start,uint64_t length) {
    auto size = computeSutiableSize(buff,start,length);
    return SSL_read(mContext->getSSL(),buff->toValue() + start,size);
}

ByteArray _SSLSocksSocketImpl::read() {
    ByteArray buff = ByteArray::New(1024*16);
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

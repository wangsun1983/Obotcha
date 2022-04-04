#include "SSLSocksSocketImpl.hpp"
#include "InitializeException.hpp"

namespace obotcha {

//this is used for creating new socket in server
_SSLSocksSocketImpl::_SSLSocksSocketImpl(String certificatePath,String keyPath,SocketImpl s) {
    mSocket = s;
    init(certificatePath,keyPath);
}

_SSLSocksSocketImpl::_SSLSocksSocketImpl(String certificatePath,String keyPath,InetAddress address,SocketOption option) {
    mSocket = createSocksSocketImpl(address,option);
    init(certificatePath,keyPath);
}
    
_SSLSocksSocketImpl::_SSLSocksSocketImpl(SocketImpl s) {
    mSocket = s;
    init(nullptr,nullptr);
}

_SSLSocksSocketImpl::_SSLSocksSocketImpl(InetAddress address,SocketOption option) {
    mSocket = createSocksSocketImpl(address,option);
    init(nullptr,nullptr);
}

void _SSLSocksSocketImpl::init(String certificatePath,String keyPath) {
    if(certificatePath != nullptr) {
        mContext = createSSLSocketContext(st(SSLSocketContext)::SERVER);
        if (SSL_CTX_use_certificate_file(mContext->getCtx(), certificatePath->toChars(),
                                     SSL_FILETYPE_PEM) <= 0) {
            throw InitializeException("SSL certificate use error");
        }
        /* load private key */
        if (SSL_CTX_use_PrivateKey_file(mContext->getCtx(), keyPath->toChars(), SSL_FILETYPE_PEM) <=
            0) {
            throw InitializeException("SSL private key use error");
        }
        /* check whether private is ok */
        if (!SSL_CTX_check_private_key(mContext->getCtx())) {
            throw InitializeException("SSL private key check error");
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

    int ret = mSocket->connect();
    
    ret = SSL_connect(mContext->getSSL());
    if(ret < 0) {
        ERR_print_errors_fp (stderr);
    }
    return ret;
}

int _SSLSocksSocketImpl::close() {
    if(mSocket != nullptr) {
        mSocket->close();
        mSocket = nullptr;
    }

    return 0;
}

int _SSLSocksSocketImpl::write(ByteArray buff,int start,int length) {
    int size = (length == -1?buff->size() - start:length);
    
    if(start + length > buff->size()) {
        //TODO
        return -1;
    }

    
    return SSL_write(mContext->getSSL(), buff->toValue() + start, size);
}

int _SSLSocksSocketImpl::read(ByteArray buff,int start,int length) {
    int size = (length == -1?buff->size() - start:length);
    
    if(start + size > buff->size()) {
        //TODO
        return -1;
    }
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

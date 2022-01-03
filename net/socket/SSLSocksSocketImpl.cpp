#include "SSLSocksSocketImpl.hpp"
#include "InitializeException.hpp"

namespace obotcha {

_SSLSocksSocketImpl::_SSLSocksSocketImpl(String certificatePath,String keyPath,SocketImpl s,bool isServer) {
    init(certificatePath,keyPath,isServer);
    mSocket = s;
}

_SSLSocksSocketImpl::_SSLSocksSocketImpl(String certificatePath,String keyPath,InetAddress address,SocketOption option,bool isServer) {
    init(certificatePath,keyPath,isServer);
    mSocket = createSocksSocketImpl(address,option);
}

void _SSLSocksSocketImpl::init(String certificatePath,String keyPath,bool isServer) {
    mCertificate = certificatePath;
    mKey = keyPath;
    /* int ssl  */
    SSL_library_init();
    /* load SSL algorithms */
    OpenSSL_add_all_algorithms();
    /* load SSL error strings */
    SSL_load_error_strings();

    /*can use SSLv2_server_method() or SSLv3_server_method()*/
    if(isServer) {
        mCtx = SSL_CTX_new(SSLv23_server_method());
    } else {
        mCtx = SSL_CTX_new(SSLv23_client_method());
    }
    if (mCtx == NULL) {
        throw InitializeException("SSL Create error");
    }
    /* load user certificate,this certificati is used to send to
     * client,certificate contains public key */
    if (SSL_CTX_use_certificate_file(mCtx, mCertificate->toChars(),
                                     SSL_FILETYPE_PEM) <= 0) {
        throw InitializeException("SSL certificate use error");
    }
    /* load private key */
    if (SSL_CTX_use_PrivateKey_file(mCtx, mKey->toChars(), SSL_FILETYPE_PEM) <=
        0) {
        throw InitializeException("SSL private key use error");
    }
    /* check whether private is ok */
    if (!SSL_CTX_check_private_key(mCtx)) {
        throw InitializeException("SSL private key check error");
    }

    mSSL = SSL_new(mCtx);
}

int _SSLSocksSocketImpl::connect() {
    return mSocket->connect();
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

    
    return SSL_write(mSSL, buff->toValue() + start, size);
}

int _SSLSocksSocketImpl::read(ByteArray buff,int start,int length) {
    int size = (length == -1?buff->size() - start:length);
    
    if(start + size > buff->size()) {
        //TODO
        return -1;
    }

    return SSL_read(mSSL,buff->toValue() + start,size);
}

ByteArray _SSLSocksSocketImpl::read() {
    ByteArray buff = createByteArray(1024*16);
    int size = SSL_write(mSSL, buff->toValue(), 1024*16);
    buff->quickShrink(size);
    return buff;
}

FileDescriptor _SSLSocksSocketImpl::getFileDescriptor() {
    return mSocket->getFileDescriptor();
}


}

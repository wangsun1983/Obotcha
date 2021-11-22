#include "SSLServerSocketImpl.hpp"
#include "SSLSocksSocketImpl.hpp"
#include "InitializeException.hpp"

namespace obotcha {

_SSLServerSocketImpl::_SSLServerSocketImpl(String certificatePath,
                                           String keyPath,
                                           InetAddress address,
                                           SocketOption option){
    mCertificate = certificatePath;
    mKey = keyPath;

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

    mSocket = createServerSocketImpl(address,option);

}

int _SSLServerSocketImpl::bind() {
    return mSocket->bind();
}

Socket _SSLServerSocketImpl::accept() {
    Socket s = mSocket->accept();
    if(s->getFileDescriptor() == nullptr) {
        printf("s fd is nullptr \n");
    }
    auto client = createSSLSocksSocketImpl(mCertificate,mKey,s->getSockImpl(),true);
    s->getFileDescriptor()->setAsync(false);
    printf("ssl accept trace1,fd is %d \n",s->getFileDescriptor()->getFd());
    int ret = SSL_set_fd(client->mSSL, s->getFileDescriptor()->getFd());

    printf("ssl accept trace2,ret is %d \n",ret);
    ret = SSL_accept(client->mSSL);
    printf("ssl accept ret2 is %d \n",ret);

    s->getFileDescriptor()->setAsync(true);
    
    printf("ssl accept trace3,fd is %d \n",s->getFileDescriptor()->getFd());
    Socket result = createSocket();
    result->setSockImpl(client);
    result->setType(st(Socket)::SSL);

    return result;
}

FileDescriptor _SSLServerSocketImpl::getFileDescriptor() {
    return mSocket->getFileDescriptor();
}

int _SSLServerSocketImpl::close() {
    if(mSocket != nullptr) {
        return mSocket->close();
        mSocket = nullptr;
    }

    return 0;
}

_SSLServerSocketImpl::~_SSLServerSocketImpl() {
    if (mCtx != nullptr) {
        SSL_CTX_free(mCtx);
        mCtx = nullptr;
    }

    if (mSSL != nullptr) {
        SSL_shutdown(mSSL);
        SSL_free(mSSL);
        mSSL = nullptr;
    }
}


}

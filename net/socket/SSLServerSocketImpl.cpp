#include "SSLServerSocketImpl.hpp"
#include "SSLSocksSocketImpl.hpp"
#include "InitializeException.hpp"
#include "Log.hpp"

namespace obotcha {

_SSLServerSocketImpl::_SSLServerSocketImpl(String certificatePath,
                                           String keyPath,
                                           InetAddress address,
                                           SocketOption option){
    mCertificate = certificatePath;
    mKey = keyPath;

    mSSLContext = createSSLSocketContext(st(SSLSocketContext)::SERVER);
    /* load user certificate,this certificati is used to send to
     * client,certificate contains public key */
    if (SSL_CTX_use_certificate_file(mSSLContext->getCtx(), mCertificate->toChars(),
                                     SSL_FILETYPE_PEM) <= 0) {
        Trigger(InitializeException,"SSL certificate use error");
    }
    /* load private key */
    if (SSL_CTX_use_PrivateKey_file(mSSLContext->getCtx(), mKey->toChars(), SSL_FILETYPE_PEM) <= 0) {
        Trigger(InitializeException,"SSL private key use error");
    }
    /* check whether private is ok */
    if (!SSL_CTX_check_private_key(mSSLContext->getCtx())) {
        Trigger(InitializeException,"SSL private key check error");
    }

    mSSLContext->initSSL();
    mSocket = createServerSocketImpl(address,option);
}

int _SSLServerSocketImpl::bind() {
    return mSocket->bind();
}

Socket _SSLServerSocketImpl::accept() {
    Socket s = mSocket->accept();
    
    auto client = createSSLSocksSocketImpl(mCertificate,mKey,s->getSockImpl());
    s->getFileDescriptor()->setAsync(false);
    int ret = SSL_accept(client->getSSLContext()->getSSL());
    if(ret < 0) {
        LOG(ERROR)<<"SSLServerSocketImpl SSL_accept failed";
        ERR_print_errors_fp (stderr);
    }

    s->getFileDescriptor()->setAsync(true);
    
    Socket result = createSocket();
    result->setSockImpl(client);
    result->setProtocol(st(Socket)::SSL);

    return result;
}

FileDescriptor _SSLServerSocketImpl::getFileDescriptor() {
    return mSocket->getFileDescriptor();
}

int _SSLServerSocketImpl::close() {
    if(mSocket != nullptr) {
        int ret = mSocket->close();
        mSocket = nullptr;
        return ret;
    }

    return 0;
}

_SSLServerSocketImpl::~_SSLServerSocketImpl() {

}


}

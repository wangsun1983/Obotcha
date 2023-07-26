#include "SSLServerSocketImpl.hpp"
#include "SSLSocksSocketImpl.hpp"
#include "InitializeException.hpp"
#include "Log.hpp"

namespace obotcha {

_SSLServerSocketImpl::_SSLServerSocketImpl(InetAddress address,
                                           SocketOption option) {                                            
    String certificate = option->getSSLCertificatePath();
    String key = option->getSSLKeyPath();
    mOption = option;
    
    if(certificate == nullptr || key == nullptr) {
        Trigger(InitializeException,"SSL no certificate/key")
    }
    mSSLContext = createSSLSocketContext(st(SSLSocketContext)::SERVER);
    /* load user certificate,this certificati is used to send to
     * client,certificate contains public key */
    if (SSL_CTX_use_certificate_file(mSSLContext->getCtx(), certificate->toChars(),
                                     SSL_FILETYPE_PEM) <= 0) {
        Trigger(InitializeException,"SSL certificate use error")
    }
    /* load private key */
    if (SSL_CTX_use_PrivateKey_file(mSSLContext->getCtx(), key->toChars(), SSL_FILETYPE_PEM) <= 0) {
        Trigger(InitializeException,"SSL private key use error")
    }
    /* check whether private is ok */
    if (!SSL_CTX_check_private_key(mSSLContext->getCtx())) {
        Trigger(InitializeException,"SSL private key check error")
    }
    mSSLContext->initSSL();
    mSocket = createServerSocketImpl(address,option);
}

int _SSLServerSocketImpl::bind() {
    return mSocket->bind();
}

Socket _SSLServerSocketImpl::accept() {
    Socket s = mSocket->accept();
    SocketOption option = createSocketOption();
    auto client = createSSLSocksSocketImpl(s->mSockImpl,mOption);

    bool isAsync = s->getFileDescriptor()->isAsync();
    if(isAsync) {
        s->getFileDescriptor()->setAsync(false);
    }
    //start shakehande with client
    if(SSL_accept(client->getSSLContext()->getSSL()) < 0) {
        LOG(ERROR)<<"SSLServerSocketImpl SSL_accept failed";
        ERR_print_errors_fp (stderr);
    }
    if(isAsync) {
        s->getFileDescriptor()->setAsync(true);
    }
    return createSocket(client);
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

}

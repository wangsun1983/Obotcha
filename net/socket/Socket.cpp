#include "Socket.hpp"
#include "DatagramSocketImpl.hpp"
#include "InitializeException.hpp"
#include "SocketInputStream.hpp"
#include "SocketOutputStream.hpp"
#include "SocksSocketImpl.hpp"
#include "SSLSocksSocketImpl.hpp"
#include "System.hpp"
#include "OStdInstanceOf.hpp"

namespace obotcha {

_Socket::_Socket() {
    mProtocol = UnKnown;
    mClosed = false;
    mSockImpl = nullptr;
    mIsAsync = false;
    mPool = nullptr;
}

_Socket::_Socket(int protocol, 
                 InetAddress addr, 
                 SocketOption option,
                 bool isAsync,
                 AsyncOutputChannelPool pool):_Socket() {
    mProtocol = protocol;
    mPool = pool;
    mIsAsync = isAsync;

    switch (protocol) {
        case Tcp:
            mSockImpl = createSocksSocketImpl(addr, option);
            return;

        case Udp:
            mSockImpl = createDatagramSocketImpl(addr, option);
            return;

        case Ssl:
            mSockImpl = createSSLSocksSocketImpl(addr,option);
            return;
    }

    Trigger(InitializeException, "invalid protocol");
}

_Socket::_Socket(SocketImpl impl,AsyncOutputChannelPool pool):_Socket() {
    mPool = pool;
    if(IsInstance(SocksSocketImpl,impl)) {
        mProtocol = Tcp;
    } else if(IsInstance(DatagramSocketImpl,impl)) {
        mProtocol = Udp;
    } else if(IsInstance(SSLSocksSocketImpl,impl)) {
        mProtocol = Ssl;
    }
    mSockImpl = impl;
    updateStream();
}

void _Socket::setAsync(bool async,AsyncOutputChannelPool pool) {
    bool formerAsync = mIsAsync;
    if(formerAsync != async) {
        mSockImpl->getFileDescriptor()->setAsync(async);
        //firstly,remove ouputstream from async pool!!!!;
        if(mOutputStream != nullptr) {
            mOutputStream->setAsync(false);
        }

        if(pool != nullptr) {
            mPool = pool;
        }

        mIsAsync = async;
        
        if(mOutputStream != nullptr) {
            mOutputStream->setAsync(async,mPool);
        }
    }
}

bool _Socket::isAsync() {
    return mSockImpl->getFileDescriptor()->isAsync();
}

InetAddress _Socket::getInetAddress() {
    return mSockImpl->getInetAddress();
}

int _Socket::connect() {
    if(mSockImpl->connect() == 0) {
        mSockImpl->getFileDescriptor()->setAsync(mIsAsync);
        setAsync(mIsAsync,mPool);
        updateStream();
        return 0;
    }
    return -1;
}

int _Socket::bind() {
    int ret = mSockImpl->bind();
    updateStream();

    return ret;
}

void _Socket::close() {
    if(!mClosed) {
        mClosed = true;
        if(mInputStream != nullptr) {
            mInputStream->close();
        }

        if(mOutputStream != nullptr) {
            mOutputStream->close();
        }

        if (mSockImpl != nullptr) {
            mSockImpl->close();
        }
    }
}

bool _Socket::isClosed() {
    return mClosed;
}

InputStream _Socket::getInputStream() {
    return mInputStream;
}

OutputStream _Socket::getOutputStream() {
    return mOutputStream;
}

FileDescriptor _Socket::getFileDescriptor() {
    return mSockImpl->getFileDescriptor();
}

int _Socket::getProtocol() {
    return mProtocol;
}

void _Socket::updateStream() {
    mOutputStream = createSocketOutputStream(mSockImpl,mPool);
    mInputStream = createSocketInputStream(mSockImpl);
}

} // namespace obotcha

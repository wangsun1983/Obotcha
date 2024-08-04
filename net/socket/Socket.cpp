#include "Socket.hpp"
#include "DatagramSocketImpl.hpp"
#include "InitializeException.hpp"
#include "SocksSocketImpl.hpp"
#include "SSLSocksSocketImpl.hpp"
#include "Log.hpp"

namespace obotcha {

_Socket::_Socket(st(Net)::Protocol protocol, 
                 InetAddress addr, 
                 SocketOption option,
                 bool isAsync,
                 AsyncOutputChannelPool pool):
                 mProtocol(protocol),mPool(pool),mIsAsync(isAsync) {
    switch (protocol) {
        case st(Net)::Protocol::Tcp:
            mSockImpl = SocksSocketImpl::New(addr, option);
            return;

        case st(Net)::Protocol::Udp:
            mSockImpl = DatagramSocketImpl::New(addr, option);
            return;

        case st(Net)::Protocol::Ssl:
            mSockImpl = SSLSocksSocketImpl::New(addr,option);
            return;
        
        default:
            Trigger(InitializeException, "invalid protocol")
    }    
}

_Socket::_Socket(SocketImpl impl,InetAddress addr,AsyncOutputChannelPool pool):mPool(pool),mSockImpl(impl) {
    if(IsInstance(SocksSocketImpl,impl)) {
        mProtocol = st(Net)::Protocol::Tcp;
    } else if(IsInstance(DatagramSocketImpl,impl)) {
        mProtocol = st(Net)::Protocol::Udp;
    } else if(IsInstance(SSLSocksSocketImpl,impl)) {
        mProtocol = st(Net)::Protocol::Ssl;
    }
    
    if(addr != nullptr) {
        mSockImpl->setInetAddress(addr);
    }

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

bool _Socket::isAsync() const {
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
            mInputStream = nullptr;
        }

        if(mOutputStream != nullptr) {
            mOutputStream->close();
            mOutputStream = nullptr;
        }

        if (mSockImpl != nullptr) {
            mSockImpl->close();
            mSockImpl = nullptr;
        }
    }
}

bool _Socket::isClosed() const {
    return mClosed;
}

InputStream _Socket::getInputStream() {
    if(mClosed) {
        LOG(ERROR)<<"getInputStream after closed.";
        return nullptr;
    }
    return mInputStream;
}

OutputStream _Socket::getOutputStream() {
    if(mClosed) {
        LOG(ERROR)<<"getOutputStream after closed.";
        return nullptr;
    }
    return mOutputStream;
}

FileDescriptor _Socket::getFileDescriptor() {
    return mSockImpl->getFileDescriptor();
}

st(Net)::Protocol _Socket::getProtocol() const {
    return mProtocol;
}

void _Socket::updateStream() {
    mOutputStream = SocketOutputStream::New(mSockImpl,mPool);
    mInputStream = SocketInputStream::New(mSockImpl);
}

} // namespace obotcha

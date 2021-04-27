#include "Object.hpp"
#include "StrongPointer.hpp"

#include "SocketMonitor.hpp"
#include "ExecutorBuilder.hpp"
#include "HttpAsyncConnectionPool.hpp"
#include "HttpAsyncConnection.hpp"
#include "Handler.hpp"

namespace obotcha {

_HttpAsyncConnectionPool::_HttpAsyncConnectionPool() {
    mMutex = createMutex();
    mSocketMonitor = createSocketMonitor();
    mConnections = createHashMap<Socket,HttpAsyncConnection>();
    mExecutor = createExecutorBuilder()->newThreadPool();
}

HttpAsyncConnection _HttpAsyncConnectionPool::createConnection(HttpUrl url,HttpConnectionListener l,HttpOption o ) {
    HttpAsyncConnection connection = createHttpAsyncConnection(url,l,o);
    mExecutor->execute([](HttpAsyncConnectionPool pool,HttpAsyncConnection c) {
        int ret = c->connect();
        if(c->mListener != nullptr) {
            c->mListener->onConnect(ret);
        }

        {
            AutoLock l(pool->mMutex);
            pool->mConnections->put(c->mSocket,c);
            pool->mSocketMonitor->bind(c->mSocket,pool);
        }
    },AutoClone(this),connection);
    return connection;
}

void _HttpAsyncConnectionPool::onSocketMessage(int event,Socket s,ByteArray data) {
    AutoLock l(mMutex);
    HttpAsyncConnection url = mConnections->get(s);
    if(url != nullptr) {
        url->onResponse(event,data);
    }
}

void _HttpAsyncConnectionPool::close() {
    mSocketMonitor->close();
    {
        AutoLock l(mMutex);
        auto iterator = mConnections->getIterator();
        while(iterator->hasValue()) {
            auto c = iterator->getValue();
            c->close();
            iterator->next();
        }
        mConnections->clear();
    }

    mExecutor->shutdown();
}

void _HttpAsyncConnectionPool::recyleConnection(HttpAsyncConnection c) {
    {
        AutoLock l(mMutex);
        mConnections->remove(c->mSocket);
        mSocketMonitor->remove(c->mSocket);
    }
}
}

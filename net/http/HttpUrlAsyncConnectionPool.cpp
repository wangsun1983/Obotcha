#include "Object.hpp"
#include "StrongPointer.hpp"

#include "SocketMonitor.hpp"
#include "ExecutorBuilder.hpp"
#include "HttpUrlAsyncConnectionPool.hpp"
#include "Handler.hpp"

namespace obotcha {

_HttpUrlAsyncConnectionPool::_HttpUrlAsyncConnectionPool() {
    mMutex = createMutex();
    mSocketMonitor = createSocketMonitor();
    mExecutor = createExecutorBuilder()->newThreadPool();
    mConnections = createHashMap<Socket,HttpUrlConnection>();
}

HttpUrlConnection _HttpUrlAsyncConnectionPool::createConnection(HttpUrl url) {
    HttpUrlConnection connection = createHttpUrlConnection(url,createHandler());
    
    mExecutor->execute([](HttpUrlAsyncConnectionPool pool,HttpUrlConnection c) {
        //HttpUrlConnection c,Mutex mutex,HashMap<Socket,HttpUrlConnection> map,SocketMonitor monitor
        c->_connect();
        {
            if(c->mSocket == nullptr) {
                printf("socket is nullptr \n");
            }
            AutoLock l(pool->mMutex);
            pool->mConnections->put(c->mSocket,c);
            pool->mSocketMonitor->bind(c->mSocket,pool);
        }
    },AutoClone(this),connection);

    return connection;
}

void _HttpUrlAsyncConnectionPool::recyleConnection(HttpUrlConnection c) {
    {
        AutoLock l(mMutex);
        mConnections->remove(c->mSocket);
    }
}

void _HttpUrlAsyncConnectionPool::onSocketMessage(int event,Socket s,ByteArray data) {
    AutoLock l(mMutex);
    printf("onData size is %d \n",data->size());
    HttpUrlConnection url = mConnections->get(s);
    if(url != nullptr) {
        url->onResponse(event,data);
    }
}

}

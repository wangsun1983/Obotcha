#include "HttpSessionManager.hpp"
#include "ExecutorBuilder.hpp"
#include "System.hpp"

namespace obotcha {

sp<_HttpSessionManager> _HttpSessionManager::mInstance = nullptr;

HttpSessionManager _HttpSessionManager::getInstance() {
    static std::once_flag flag;
    std::call_once(flag, []() {
        mInstance = AutoClone(new _HttpSessionManager());
    });
    
    return mInstance;
}

HttpSession _HttpSessionManager::createSession(int interval) {
    HttpSession session = HttpSession::New(interval);
    add(session);
    return session;
}

HttpSession _HttpSessionManager::get(String id) {
    return mSessions->get(id);
}

void _HttpSessionManager::remove(HttpSession session) {
    if(session != nullptr) {
        mSessions->remove(session->getId());
    }
    
    auto future = mFutures->remove(session->getId());
    if(future != nullptr) {
        future->cancel();
    }
}

void _HttpSessionManager::add(HttpSession session) {
    mSessions->put(session->getId(),session);
    if(session->getMaxInactiveInterval() > 0) {
        monitor(session->getId());
    }
}

_HttpSessionManager::_HttpSessionManager() {
    mExecutor = ExecutorBuilder::New()->newScheduledThreadPool();
    mSessions = ConcurrentHashMap<String,HttpSession>::New();
    mFutures = ConcurrentHashMap<String,Future>::New();
}

void _HttpSessionManager::monitor(String id) {
    auto session = mSessions->get(id);
    if(auto future = mFutures->get(id);future != nullptr) {
        future->cancel();
    }

    long interval = 0;
    if(session->getMaxInactiveInterval() > 0) {
        interval = session->getLastAccessedTime() 
                    + session->getMaxInactiveInterval() *1000 
                    - st(System)::CurrentTimeMillis();
    
        auto future = mExecutor->schedule(interval,[session,this] {
            long next = session->getLastAccessedTime() + session->getMaxInactiveInterval()*1000;
            if(next <= st(System)::CurrentTimeMillis()) {
                session->invalidate();
            } else {
                add(session);
            }
        });
        mFutures->put(session->getId(),future);
    }
}

} // namespace obotcha

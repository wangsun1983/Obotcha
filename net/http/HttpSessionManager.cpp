#include "HttpSessionManager.hpp"
#include "ExecutorBuilder.hpp"
#include "System.hpp"

namespace obotcha {

sp<_HttpSessionManager> _HttpSessionManager::mInstance = nullptr;

HttpSessionManager _HttpSessionManager::getInstance() {
    static std::once_flag flag;
    std::call_once(flag, []() {
        _HttpSessionManager *mgr = new _HttpSessionManager();
        mInstance = AutoClone(mgr);
    });
    
    return mInstance;
}

HttpSession _HttpSessionManager::createSession() {
    HttpSession session = createHttpSession();
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
}

void _HttpSessionManager::add(HttpSession session) {
    mSessions->put(session->getId(),session);
    int interval = session->getLastAccessedTime() 
                + session->getMaxInactiveInterval() *1000 
                - st(System)::currentTimeMillis();

    if(interval > 0) {
        mExecutor->schedule(interval,[session,this] {
            long next = session->getLastAccessedTime() + session->getMaxInactiveInterval()*1000;
            if(next <= st(System)::currentTimeMillis()) {
                session->invalidate();
                mSessions->remove(session->getId());
            } else {
                add(session);
            }
        });
    }
}

_HttpSessionManager::_HttpSessionManager() {
    mExecutor = createExecutorBuilder()->newScheduledThreadPool();
    mSessions = createConcurrentHashMap<String,HttpSession>();
}

} // namespace obotcha

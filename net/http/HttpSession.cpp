#include "HttpSession.hpp"
#include "HttpSessionManager.hpp"
#include "System.hpp"
#include "UUID.hpp"

namespace obotcha {

int _HttpSession::kInfiniteDuration = -1;

_HttpSession::_HttpSession(int maxInactiveInterval) { 
    sessions = createConcurrentHashMap<String, Object>();
    mCreationTime = st(System)::currentTimeMillis();
    mLastAccessTime = mCreationTime;
    mMaxInactiveInterval = maxInactiveInterval;
    mIsValid = true;
    UUID uid = createUUID();
    mId = createString(mCreationTime)->append(uid->generate());
}

long _HttpSession::getCreationTime() {
    return mCreationTime;
}

String _HttpSession::getId() {
    return mId;
}

long _HttpSession::getLastAccessedTime() {
    return mLastAccessTime;
}

void _HttpSession::setMaxInactiveInterval(int interval) {
    mMaxInactiveInterval = interval;
    st(HttpSessionManager)::getInstance()->monitor(getId());
}

int _HttpSession::getMaxInactiveInterval() {
    return mMaxInactiveInterval;
}

void _HttpSession::setAttribute(String name, Object value) {
    sessions->put(name,value);
    mLastAccessTime = st(System)::currentTimeMillis();
}

void _HttpSession::removeAttribute(String name) {
    sessions->remove(name);
    mLastAccessTime = st(System)::currentTimeMillis();
}

void _HttpSession::invalidate() {
    mIsValid = false;
    sessions->clear();
    st(HttpSessionManager)::getInstance()->remove(AutoClone(this));
}

ArrayList<String> _HttpSession::getAttributeNames() {
    mLastAccessTime = st(System)::currentTimeMillis();
    return sessions->keySet();
}

int _HttpSession::size() {
    return sessions->size();
}

bool _HttpSession::isValid() {
    return mIsValid;
}

} // namespace obotcha
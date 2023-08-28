#include "HttpSession.hpp"
#include "HttpSessionManager.hpp"
#include "System.hpp"
#include "UUID.hpp"

namespace obotcha {

int _HttpSession::kInfiniteDuration = -1;

_HttpSession::_HttpSession(int maxInactiveInterval):
                            mMaxInactiveInterval(maxInactiveInterval) { 
    mCreationTime = st(System)::CurrentTimeMillis();
    mLastAccessTime = mCreationTime;
    UUID uid = createUUID();
    mId = createString(mCreationTime)->append(uid->generate());
}

long _HttpSession::getCreationTime() const {
    return mCreationTime;
}

String _HttpSession::getId() const {
    return mId;
}

long _HttpSession::getLastAccessedTime() const {
    return mLastAccessTime;
}

void _HttpSession::setMaxInactiveInterval(int interval) {
    mMaxInactiveInterval = interval;
    st(HttpSessionManager)::getInstance()->monitor(getId());
}

int _HttpSession::getMaxInactiveInterval() const {
    return mMaxInactiveInterval;
}

void _HttpSession::setAttribute(String name, Object value) {
    sessions->put(name,value);
    mLastAccessTime = st(System)::CurrentTimeMillis();
}

void _HttpSession::removeAttribute(String name) {
    sessions->remove(name);
    mLastAccessTime = st(System)::CurrentTimeMillis();
}

void _HttpSession::invalidate() {
    mIsValid = false;
    sessions->clear();
    st(HttpSessionManager)::getInstance()->remove(AutoClone(this));
}

ArrayList<String> _HttpSession::getAttributeNames() {
    mLastAccessTime = st(System)::CurrentTimeMillis();
    return sessions->keySet();
}

size_t _HttpSession::size() const {
    return sessions->size();
}

bool _HttpSession::isValid() const {
    return mIsValid;
}

} // namespace obotcha
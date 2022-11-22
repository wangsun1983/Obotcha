#include "HttpSession.hpp"
#include "System.hpp"
#include "UUID.hpp"

namespace obotcha {

_HttpSession::_HttpSession(int maxInactiveInterval) { 
    sessions = createConcurrentHashMap<String, Object>();
    mCreationTime = st(System)::currentTimeMillis();
    mLastAccessTime = mCreationTime;
    UUID uid = createUUID();
    mId = createString(mCreationTime)->append(uid->generate());
    mMaxInactiveInterval = maxInactiveInterval;
    mIsValid = true;
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
}

int _HttpSession::getMaxInactiveInterval() {
    return mMaxInactiveInterval;
}

void _HttpSession::setAttribute(String name, Object value) {
    sessions->put(name,value);
}

void _HttpSession::removeAttribute(String name) {
    sessions->remove(name);
}

void _HttpSession::invalidate() {
    mIsValid = false;
    sessions->clear();
}

ArrayList<String> _HttpSession::getAttributeNames() {
    return sessions->keySet();
}

int _HttpSession::size() {
    return sessions->size();
}

bool _HttpSession::isValid() {
    return mIsValid;
}

} // namespace obotcha
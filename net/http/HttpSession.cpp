#include "HttpSession.hpp"

namespace obotcha {

_HttpSession::_HttpSession() { 
    sessions = createConcurrentHashMap<String, Object>(); 
}

void _HttpSession::setAttribute(String name, Object value) {
    sessions->put(name,value);
}

Object _HttpSession::getAttribute(String name) {
    return sessions->get(name);
}

void _HttpSession::invalidate() {
    sessions->clear();
}

void _HttpSession::removeAttribute(String name) {
    sessions->remove(name);
}

ArrayList<String> _HttpSession::getAttributeNames() {
    return sessions->entrySet();
}

} // namespace obotcha
#include "HttpSession.hpp"

namespace obotcha {

_HttpSession::_HttpSession() { 
    sessions = createConcurrentHashMap<String, Object>(); 
}

void _HttpSession::setAttribute(String name, Object value) {
    sessions->put(name,value);
}

void _HttpSession::invalidate() {
    sessions->clear();
}

void _HttpSession::removeAttribute(String name) {
    sessions->remove(name);
}

ArrayList<String> _HttpSession::getAttributeNames() {
    return sessions->keySet();
}

int _HttpSession::size() {
    return sessions->size();
}

} // namespace obotcha
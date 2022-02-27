#ifndef __OBOTCHA_HTTP_SESSION_HPP__
#define __OBOTCHA_HTTP_SESSION_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ConcurrentHashMap.hpp"
#include "ArrayList.hpp"

namespace obotcha {

DECLARE_CLASS(HttpSession) {

public:
    _HttpSession();
    void setAttribute(String name, Object value);
    Object getAttribute(String name);
    void invalidate();

    void removeAttribute(String);
    ArrayList<String> getAttributeNames();

    Object operator[] (String key) {
        return sessions->get(key);
    }
private:
    ConcurrentHashMap<String,Object> sessions;
};

}
#endif

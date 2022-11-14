#ifndef __OBOTCHA_HTTP_SESSION_HPP__
#define __OBOTCHA_HTTP_SESSION_HPP__

#include "Object.hpp"
#include "String.hpp"
#include "ConcurrentHashMap.hpp"
#include "ArrayList.hpp"

namespace obotcha {

DECLARE_CLASS(HttpSession) {

public:
    _HttpSession();
    void setAttribute(String name, Object value);
    
    template <typename T>
    T getAttribute(String name) {
        Object o = sessions->get(name);
        return Cast<T>(o);
    }

    void invalidate();

    void removeAttribute(String);
    ArrayList<String> getAttributeNames();

    int size();
private:
    ConcurrentHashMap<String,Object> sessions;
};

}
#endif

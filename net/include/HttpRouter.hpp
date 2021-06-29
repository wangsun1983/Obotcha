#ifndef __OBOTCHA_HTTP_ROUTER_HPP__
#define __OBOTCHA_HTTP_ROUTER_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "HashMap.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(RouterListener) {
public:
    virtual Object onInvoke(HashMap<String,String>) = 0;
};

DECLARE_SIMPLE_CLASS(HttpRouter) {
public:
    _HttpRouter(String p,RouterListener l);
    
    String getPath();
    RouterListener getListener();

private:
    String mPath;
    RouterListener mListener;
    
};

}

#endif

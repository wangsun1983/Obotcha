#include <stdio.h>
#include <unistd.h>

#include "HttpRouter.hpp"

namespace obotcha {

_HttpRouter::_HttpRouter(String p, RouterListener l) {
    mPath = p;
    mListener = l;
}

String _HttpRouter::getPath() { 
    return mPath; 
}

RouterListener _HttpRouter::getListener() { 
    return mListener; 
}

}
#ifndef __OBOTCHA_HANDLER_TARGET_HPP__
#define __OBOTCHA_HANDLER_TARGET_HPP__

#include "Object.hpp"

namespace obotcha {

class _Message;

DECLARE_CLASS(HandlerTarget) {
public:
    virtual void handleMessage(sp<_Message>) {
        //Intentionally unimplemented...
    };    
};

} // namespace obotcha
#endif
#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "Message.hpp"

namespace obotcha {

_Message::_Message() {
    mDrop = 0;
}

_Message::_Message(int w) {
    what = w;
    mDrop = 0;
}

}

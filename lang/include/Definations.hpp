#ifndef __OBOTCHA_DEFINATIONS_HPP__
#define __OBOTCHA_DEFINATIONS_HPP__

#include "Object.hpp"

namespace obotcha {

DECLARE_CLASS(Defination) {
public:
    enum Id {
        Sync = 0,
        ASync,
        Break,
        Continue,
        //BigEndian,
        //LittleEndian,
        NoContentRead,
        ContinueRead,
    };
};

}

#endif
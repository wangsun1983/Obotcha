#ifndef __OBOTCHA_FILA_HPP__
#define __OBOTCHA_FILA_HPP__

#include "co_routine.h"

#include "Object.hpp"

namespace obotcha {

DECLARE_CLASS(Fila) {
public:
    static int sleep(long interval = 0);
};


} // namespace obotcha
#endif
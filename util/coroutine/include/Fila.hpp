#ifndef __OBOTCHA_FILA_HPP__
#define __OBOTCHA_FILA_HPP__

#include "Object.hpp"
#include "co_routine.h"

namespace obotcha {

DECLARE_CLASS(Fila) {
public:
    static int sleep(long interval = 0);
};


} // namespace obotcha
#endif
#ifndef __OBOTCHA_ERROR_HPP__
#define __OBOTCHA_ERROR_HPP__

#include "errno.h"

#define CurrentError strerror(errno)

#endif

#ifndef __OBOTCHA_TIME_ZONE_HPP__
#define __OBOTCHA_TIME_ZONE_HPP__

#include "Object.hpp"

namespace obotcha {

DECLARE_CLASS(TimeZone) {
public:
    static int GetZone();
    static void SetZone(int z);

private:
    static int kZone;
};

} // namespace obotcha
#endif
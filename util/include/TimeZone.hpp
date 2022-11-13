#ifndef __OBOTCHA_TIME_ZONE_HPP__
#define __OBOTCHA_TIME_ZONE_HPP__

#include "Object.hpp"

namespace obotcha {

DECLARE_CLASS(TimeZone) {

  public:
    static int getZone();
    static void setZone(int z);

  private:
    static int zone;
};

} // namespace obotcha
#endif
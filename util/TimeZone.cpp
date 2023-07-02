#include <time.h>

#include "TimeZone.hpp"

namespace obotcha {

int _TimeZone::zone = -1;

int _TimeZone::getZone() {
    if (zone == -1) {
        time_t time_utc = 0;
        // struct tm *p_tm_time;

        struct tm p_tm_time;
        localtime_r(&time_utc, &p_tm_time); // change to local time
        zone = (p_tm_time.tm_hour > 12) ? (p_tm_time.tm_hour -= 24)
                                        : p_tm_time.tm_hour;
    }

    return zone;
}

void _TimeZone::setZone(int z) { 
    zone = z; 
}

} // namespace obotcha
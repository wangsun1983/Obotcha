#include <time.h>

#include "TimeZone.hpp"

namespace obotcha {

int _TimeZone::kZone = -1;

int _TimeZone::GetZone() {
    if (kZone == -1) {
        time_t time_utc = 0;

        struct tm p_tm_time;
        localtime_r(&time_utc, &p_tm_time); // change to local time
        kZone = (p_tm_time.tm_hour > 12) ? (p_tm_time.tm_hour -= 24)
                                        : p_tm_time.tm_hour;
    }

    return kZone;
}

void _TimeZone::SetZone(int z) { 
    kZone = z; 
}

} // namespace obotcha
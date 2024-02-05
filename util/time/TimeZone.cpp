/**
 * @file TimeZone.cpp
 * @brief  The TimeZone class is an class that provides methods
 * to get timezone.
 * @details none
 * @mainpage none
 * @author sunli.wang
 * @email wang_sun_1983@yahoo.co.jp
 * @version 0.0.1
 * @date 2024-01-15
 * @license none
 */
#include <time.h>

#include "TimeZone.hpp"

namespace obotcha {

int _TimeZone::GetZone() {
    time_t time_utc = 0; //0:00:0

    struct tm p_tm_time;
    localtime_r(&time_utc, &p_tm_time); // change to local time
    auto kZone = (p_tm_time.tm_hour > 12) ? (p_tm_time.tm_hour -= 24)
                                    : p_tm_time.tm_hour;

    return kZone;
}

} // namespace obotcha
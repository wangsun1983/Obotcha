#ifndef __TIME_ZONE_HPP__
#define __TIME_ZONE_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

DECLARE_SIMPLE_CLASS(TimeZone) {

public:
    static int getZone();
    static void setZone(int z);

private:
    static int zone;

};

#endif
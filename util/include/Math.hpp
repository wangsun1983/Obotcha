#ifndef __OBOTCHA_MATH_HPP__
#define __OBOTCHA_MATH_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"

namespace obotcha {

DECLARE_CLASS(Math) {

public:
    enum CompareResult {
        AlmostEqual = 0,
        Param1Greater,
        Param2Greater,
    };  

    static const double E;
    static const double PI;

    static long abs(long);
    static double abs(double);
    static int abs(int);
    static float abs(float);

    static double cos(double);
    static double sin(double);
    static double tan(double);

    static double acos(double);
    static double asin(double);
    static double atan(double);

    static long max(long,long);
    static double max(double,double);
    static float max(float,float);

    static long min(long,long);
    static double min(double,double);
    static float min(float,float);

    static double pow(double,double);
    static long pow(long,long);

    static double sqrt(double);

    static int ceil(double);
    static int floor(double);

    static int compareDouble(double,double);
    static int compareFloat(float,float);

};
}
#endif
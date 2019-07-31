#ifndef __MATH_HPP__
#define __MATH_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(Math) {

public:
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
    static int max(int,double);
    static float max(float,double);

    static long min(long,long);
    static double min(double,double);
    static int min(int,double);
    static float min(float,double);

    static double pow(double,double);
    static double sqrt(double);

    static int ceil(double);
    static int floor(double);

};
}
#endif
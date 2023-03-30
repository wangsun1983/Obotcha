#ifndef __OBOTCHA_MATH_HPP__
#define __OBOTCHA_MATH_HPP__

#include "Object.hpp"

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

    static int compareDouble(double, double);
    static int compareFloat(float, float);
};
} // namespace obotcha
#endif
/**
 * @file Math.cpp
 * @brief  A class for arithmetic
 * @details none
 * @mainpage none
 * @author sunli.wang
 * @email wang_sun_1983@yahoo.co.jp
 * @version 0.0.1
 * @date 2019-07-12
 * @license none
 */

#include <cmath>
#include <limits>

#include "Double.hpp"
#include "Float.hpp"
#include "Math.hpp"

namespace obotcha {

const double _Math::E = 2.718281828459045;

const double _Math::PI = 3.141592653589793;

int _Math::compareDouble(double v1, double v2) {
    if (st(Double)::IsEqual(v1, v2)) {
        return CompareResult::AlmostEqual;
    }

    if (std::isgreater(v1, v2)) {
        return CompareResult::Param1Greater;
    }

    return CompareResult::Param2Greater;
}

int _Math::compareFloat(float v1, float v2) {
    if (st(Float)::IsEqual(v1, v2)) {
        return CompareResult::AlmostEqual;
    }

    if (std::isgreater(v1, v2)) {
        return CompareResult::Param1Greater;
    }

    return CompareResult::Param2Greater;
}

} // namespace obotcha
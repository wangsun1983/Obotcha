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

long _Math::abs(long v) { 
    return std::labs(v); 
}

double _Math::abs(double v) { 
    return std::fabs(v); 
}

int _Math::abs(int v) { 
    return std::abs(v); 
}

float _Math::abs(float v) { 
    return std::fabs(v); 
}

double _Math::cos(double v) { 
    return std::cos(v * PI / 180.0f); 
}

double _Math::sin(double v) { 
    return std::sin(v * PI / 180.0f); 
}

double _Math::tan(double v) { 
    return std::tan(v * PI / 180.0f); 
}

double _Math::acos(double v) { 
    return std::acos(v) * 180 / PI; 
}

double _Math::asin(double v) { 
    return std::asin(v) * 180 / PI; 
}

double _Math::atan(double v) { 
    return std::atan(v) * 180 / PI;
}

long _Math::max(long v1, long v2) { 
    return std::fmaxl(v1, v2); 
}

double _Math::max(double v1, double v2) { 
    return std::fmax(v1, v2); 
}

float _Math::max(float v1, float v2) { 
    return std::fmax(v1, v2); 
}

long _Math::min(long v1, long v2) { 
    return std::fminl(v1, v2); 
}

double _Math::min(double v1, double v2) { 
    return std::fmin(v1, v2); 
}

float _Math::min(float v1, float v2) { 
    return std::fminf(v1, v2); 
}

double _Math::pow(double v1, double v2) { 
    return std::pow(v1, v2); 
}

long _Math::pow(long v1, long v2) { 
    return std::pow(v1, v2); 
}

double _Math::sqrt(double v1) { 
    return std::sqrt(v1); 
}

int _Math::ceil(double v1) { 
    return std::ceil(v1); 
}

int _Math::floor(double v1) { 
    return std::floor(v1); 
}

int _Math::compareDouble(double v1, double v2) {
    if (st(Double)::isEqual(v1, v2)) {
        return CompareResult::AlmostEqual;
    }

    if (std::isgreater(v1, v2)) {
        return CompareResult::Param1Greater;
    }

    return CompareResult::Param2Greater;
}

int _Math::compareFloat(float v1, float v2) {
    if (st(Float)::isEqual(v1, v2)) {
        return CompareResult::AlmostEqual;
    }

    if (std::isgreater(v1, v2)) {
        return CompareResult::Param1Greater;
    }

    return CompareResult::Param2Greater;
}

} // namespace obotcha
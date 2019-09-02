#include <cmath>

#include "Math.hpp"
#include "Float.hpp"
#include "Double.hpp"

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
    return std::cos(v*PI/180.0f);
}

double _Math::sin(double v) {
    return std::sin(v*PI/180.0f);
}

double _Math::tan(double v) {
    return std::tan(v*PI/180.0f);
}

double _Math::acos(double v) {
    return std::acos(v)*180/PI;
}

double _Math::asin(double v) {
    return std::asin(v)*180/PI;
}

double _Math::atan(double v) {
    return std::atan(v)*180/PI;
}

long _Math::max(long v1,long v2) {
    return std::fmaxl(v1,v2);
}
    
double _Math::max(double v1,double v2) {
    return std::fmax(v1,v2);
}
    
float _Math::max(float v1,float v2) {
    return std::fmax(v1,v2);
}

long _Math::min(long v1,long v2) {
    return std::fminl(v1,v2);
}
    
double _Math::min(double v1,double v2) {
    return std::fmin(v1,v2);
}
    
float _Math::min(float v1,float v2) {
    return std::fminf(v1,v2);
}

double _Math::pow(double v1,double v2) {
    return std::pow(v1,v2);
}

long _Math::pow(long v1,long v2) {
    return std::pow(v1,v2);
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

int _Math::compare(double v1,double v2) {
    double v = std::fabs(v1 - v2);

    if(v <= st(Double)::EPS) {
        return CompareParamEqual;
    } else if(v1 -v2 > st(Double)::EPS){
        return CompareParam1Larger;
    } else {
        return CompareParam2Larger;
    }
}

int _Math::compare(float v1,float v2) {
    float v = std::fabs(v1 - v2);
    if(v  <= st(Float)::EPS) {
        return CompareParamEqual;
    } else if(v1 -v2 > st(Float)::EPS){
        return CompareParam1Larger;
    } else {
        return CompareParam2Larger;
    }
}

}
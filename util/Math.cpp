#include <cmath>

#include "Math.hpp"

namespace obotcha {

long _Math::abs(long v) {
    return std::abs(v);
}

double _Math::abs(double v) {
    return std::abs(v);
}

int _Math::abs(int v) {
    return std::abs(v);
}

float _Math::abs(float v) {
    return std::abs(v);
}

double _Math::cos(double v) {
    return std::cos(v);
}

double _Math::sin(double v) {
    return std::sin(v);
}

double _Math::tan(double v) {
    return std::tan(v);
}

double _Math::acos(double v) {
    return std::acos(v);
}

double _Math::asin(double v) {
    return std::asin(v);
}

double _Math::atan(double v) {
    return std::atan(v);
}

long _Math::max(long v1,long v2) {
    return std::fmax(v1,v2);
}
    
double _Math::max(double v1,double v2) {
    return std::fmax(v1,v2);
}
    
int _Math::max(int v1,double v2) {
    return std::fmax(v1,v2);
}

float _Math::max(float v1,double v2) {
    return std::fmax(v1,v2);
}

long _Math::min(long v1,long v2) {
    return std::fmin(v1,v2);
}
    
double _Math::min(double v1,double v2) {
    return std::fmin(v1,v2);
}
    
int _Math::min(int v1,double v2) {
    return std::fmin(v1,v2);
}

float _Math::min(float v1,double v2) {
    return std::fmin(v1,v2);
}

double _Math::pow(double v1,double v2) {
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

}
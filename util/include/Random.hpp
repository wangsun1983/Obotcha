#ifndef __OBOTCHA_RANDOM_HPP__
#define __OBOTCHA_RANDOM_HPP__

#include <cmath>
#include <random>
#include <time.h>

#include "Object.hpp"
#include "ByteArray.hpp"

namespace obotcha {

DECLARE_CLASS(Random) {
public:
    _Random();

    template<typename T>
    T next() {
        std::uniform_int_distribution<T> dis;
        int value = dis(gen);
        return value;
    }

    template<typename T>
    T next(T min,T max) {
        std::uniform_int_distribution<T> dis(min, max);
        int value = dis(gen);
        return value;
    }

    void nextBytes(ByteArray);
private:
    std::random_device rd;
    std::mt19937_64 gen;
};

template<>
double _Random::next();

template<>
double _Random::next(double min,double max);

template<>
float _Random::next();

template<>
float _Random::next(float min,float max);

} // namespace obotcha

#endif
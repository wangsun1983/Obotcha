#include <cfloat>
#include <fcntl.h>
#include <random>
#include <stdio.h>
#include <unistd.h>

#include "Integer.hpp"
#include "Math.hpp"
#include "Random.hpp"

//#define random_int_1(a, b) (std::abs((nextInt() % (b - a))) + a) // exclued b
//#define random_int_2(a, b) (std::abs((nextInt() % (b - a + 1))) + a) // include
                                                                     // b

namespace obotcha {

_Random::_Random() {
    gen = std::mt19937_64(rd()); // may be support different random strategy
}

template<>
double _Random::next() {
    std::uniform_real_distribution<double> dis;
    double value = dis(gen);
    return value;
}

template<>
double _Random::next(double min,double max) {
    std::uniform_real_distribution<double> dis(min, max);
    double value = dis(gen);
    return value;
}

template<>
float _Random::next() {
    std::uniform_real_distribution<float> dis;
    double value = dis(gen);
    return value;
}

template<>
float _Random::next(float min,float max) {
    std::uniform_real_distribution<float> dis(min, max);
    double value = dis(gen);
    return value;
}

void _Random::nextBytes(ByteArray bytes) {
    //std::srand((int)time(nullptr));
    int size = bytes->size();
    for (int i = 0, len = size; i < len;) {
        bytes[i++] = next<byte>(0,255);
    }
}

} // namespace obotcha
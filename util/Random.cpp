#include <cfloat>
#include <fcntl.h>
#include <random>
#include <stdio.h>
#include <unistd.h>

#include "Integer.hpp"
#include "Math.hpp"
#include "Random.hpp"

namespace obotcha {

_Random::_Random() {
    gen = std::mt19937_64(rd()); // may be support different random strategy
}

template<>
double _Random::next() {
    std::uniform_real_distribution<double> dis;
    return dis(gen);
}

template<>
double _Random::next(double min,double max) {
    std::uniform_real_distribution dis(min, max);
    return dis(gen);
}

template<>
float _Random::next() {
    std::uniform_real_distribution<float> dis;
    return dis(gen);
}

template<>
float _Random::next(float min,float max) {
    std::uniform_real_distribution dis(min, max);
    return dis(gen);
}

void _Random::nextBytes(ByteArray bytes) {
    auto size = bytes->size();
    for (auto i = 0; i < size;i++) {
        bytes[i] = next<byte>(0,255);
    }
}

} // namespace obotcha
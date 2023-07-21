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

uint32_t _Random::nextUint32() {
    std::uniform_int_distribution<> dis;
    uint32_t value = dis(gen);
    return value;
}

int _Random::nextInt() {
    std::uniform_int_distribution<> dis;
    int value = dis(gen);
    return value;
}

int _Random::nextInt(int min, int max) {
    std::uniform_int_distribution<> dis(min, max);
    int value = dis(gen);
    return value;
}

int _Random::nextInt(int min) { 
    return nextInt(min, st(Integer)::MAX_VALUE); 
}

double _Random::nextDouble() {
    std::uniform_real_distribution<> dis;
    double value = dis(gen);
    return value;
}

double _Random::nextDouble(double min, double max) {
    std::uniform_real_distribution<double> dis(min, max);
    double value = dis(gen);
    return value;
}

double _Random::nextDouble(double min) { 
    return nextDouble(min, DBL_MAX); 
}

void _Random::nextBytes(ByteArray bytes) {
    //std::srand((int)time(nullptr));
    int size = bytes->size();
    for (int i = 0, len = size; i < len;) {
        bytes[i++] = nextInt(0,255);
    }
}

} // namespace obotcha
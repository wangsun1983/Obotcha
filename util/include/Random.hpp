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

    uint32_t nextUint32();

    int nextInt();

    int nextInt(int min, int max);

    int nextInt(int min);

    double nextDouble();

    double nextDouble(double min, double max);

    double nextDouble(double min);

    void nextBytes(ByteArray);

private:
    std::random_device rd;
    std::mt19937_64 gen;
};

} // namespace obotcha

#endif
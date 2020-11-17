#ifndef __OBOTCHA_RANDOM_HPP__
#define __OBOTCHA_RANDOM_HPP__

#include <cmath>
#include <time.h>
#include <random>


#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ByteArray.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(Random) {

public:
    _Random();

    uint32_t nextUint32();

    int nextInt();

    int nextInt(int min,int max);

    int nextInt(int min);

    double nextDouble();

    double nextDouble(double min,double max);

    double nextDouble(double min);

    void nextBytes(ByteArray);

private:
    std::random_device rd;
    std::mt19937_64 gen;

};

}

#endif
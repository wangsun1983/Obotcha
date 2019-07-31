#ifndef __RANDOM_HPP__
#define __RANDOM_HPP__

#include <time.h>

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ByteArray.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(Random) {

public:
    static int nextInt();

    static int nextInt(int min,int max);

    static int nextInt(int min);

    static double nextDouble();

    static void nextBytes(ByteArray);
};

}

#endif
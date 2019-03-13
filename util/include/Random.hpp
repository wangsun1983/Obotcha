#ifndef __RANDOM_HPP__
#define __RANDOM_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"

DECLARE_SIMPLE_CLASS(Random) {

public:
    _Random();

    int nextInt();

};

#endif
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <random>
#include <cfloat>

#include "Random.hpp"
#include "Math.hpp"
#include "Integer.hpp"

#define random_int_1(a,b) (std::abs((nextInt()%(b-a)))+a)    //exclued b
#define random_int_2(a,b) (std::abs((nextInt()%(b-a+1)))+a)  //include b

namespace obotcha {

_Random::_Random() {
    gen = std::mt19937_64(rd()); //may be support different random strategy
}

int _Random::nextInt() {
    /*
    int fd = open("/dev/urandom",O_RDONLY);
    if(-1 == fd) {
        fd = open("/dev/random",O_RDONLY);
    }
    int randNum = 0;
    read(fd,(char *)&randNum,sizeof(int));
    close(fd);
    return randNum;//rand();
    */
    std::uniform_int_distribution<> dis;
    int value = dis(gen);
    return value;
}

int _Random::nextInt(int min,int max) {
    //srand((int)time(NULL));
    std::uniform_int_distribution<> dis(min,max);
    int value = dis(gen);
    return value;
}

int _Random::nextInt(int min) {
    //return random_int_2(min,RAND_MAX);
    return nextInt(min,st(Integer)::MAX_VALUE);
}

double _Random::nextDouble() {
    //return (double)(RAND_MAX+1.0)/(nextInt() + 1.0);
    std::uniform_real_distribution<> dis;
    double value = dis(gen);
    return value;
}

double _Random::nextDouble(double min,double max) {
    std::uniform_real_distribution<double> dis(min,max);
    double value = dis(gen);
    return value;
}

double _Random::nextDouble(double min){
    //return nextDouble(min,RAND_MAX);
    return nextDouble(min,DBL_MAX);
}

void _Random::nextBytes(ByteArray bytes) {
    srand((int)time(NULL));
    int size = bytes->size();
    for (int i = 0, len = size; i < len; ) {
        for (int rnd = nextInt(),
             //n = Math.min(len - i, sizeof(int)/sizeof(byte));
             n = st(Math)::min(len - i, (long)(sizeof(int)/sizeof(byte)));
             n-- > 0; rnd >>= 8) {
                //bytes[i++] = (byte)rnd;
                //printf("rnd is %d \n",(byte)rnd);
                bytes->fill(i++,(byte)rnd);
        }
    }
}

}
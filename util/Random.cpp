#include "Random.hpp"

#define random_int_1(a,b) ((rand()%(b-a))+a)    //exclued b
#define random_int_2(a,b) ((rand()%(b-a+1))+a)  //include b

namespace obotcha {

static void randomInit() {
    srand((int)time(NULL));
}

int _Random::nextInt() {
    return rand();
}

int _Random::nextInt(int min,int max) {
    return random_int_2(min,max);
}

int _Random::nextInt(int min) {
    return random_int_2(min,RAND_MAX);
}

double _Random::nextDouble() {
    return (RAND_MAX+1.0)/(rand() + 1.0);
}

}
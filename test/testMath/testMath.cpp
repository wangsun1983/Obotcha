#include <stdio.h>

#include "Math.hpp"


using namespace obotcha;

int main() {
    double v = st(Math)::sqrt(100);
    printf("v is %lf \n",v);

    double v2 = st(Math)::pow(2,3);
    printf("v2 is %lf \n",v2);
}

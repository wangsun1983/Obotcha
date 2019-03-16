#include <stdio.h>
#include <unistd.h>

#include "Random.hpp"

int main() {
    int i = st(Random)::nextInt();
    printf("i is %d \n",i);

    int j = st(Random)::nextInt(1,10);
    printf("j is %d \n",j);
}

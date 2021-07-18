#include <iostream>
#include <stdio.h>
#include <unistd.h>

#include "Thread.hpp"
#include "ArrayList.hpp"
#include "Integer.hpp"
#include "String.hpp"

using namespace obotcha;

int testArrayListForEach() {
  ArrayList<int> list = createArrayList<int>();
  list->add(1);
  list->add(2);
  list->add(3);

  list->foreach([](int value) {
    printf("value is %d \n",value);
    value = 100;
    return 1;
  });

  list->foreach([](int value) {
    printf("again value is %d \n",value);
    return 1;
  });
}

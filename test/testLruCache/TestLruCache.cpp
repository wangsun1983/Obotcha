#include <iostream>
#include <stdio.h>
#include <unistd.h>

#include "Thread.hpp"
#include "ArrayList.hpp"
#include "Integer.hpp"
#include "String.hpp"
#include "LruCache.hpp"

using namespace obotcha;

DECLARE_SIMPLE_CLASS(MyData) {
public:
  int i;

  ~_MyData() {
    printf("release mydata : %d \n",i);
  }
};

int main() {

    LruCache<String,MyData> lru = createLruCache<String,MyData>(3);
    for(int i = 0;i < 15;i++) {
      MyData d = createMyData();
      d->i = i;
      lru->put(createString(i),d);
    }

    printf("size is %d \n",lru->size());


}

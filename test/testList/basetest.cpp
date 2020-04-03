#include <stdio.h>
#include <unistd.h>
#include <vector>
//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "Uint8.hpp"
#include "StrongPointer.hpp"
#include "Uint8.hpp"
#include "List.hpp"

using namespace std;
using namespace obotcha;

class MyArray {

public:
  MyArray() {
    value.push_back(12);
    value.push_back(23);
    value.push_back(14);
  }

  int& operator[] (int i) {  
     int &v = value[i];
     return v;
  }

private:
  std::vector<int> value;
  int vv;
};
    

int value[] = {1,2,3,4,5};

int basetest() {

    //MyArray *t = new MyArray(&value[0]);
    //MyArray *t = new MyArray();
    //printf("v is %d \n",(*t)[0]);

    List<int> t = createList<int>(&value[0],5);

    printf("t[1] is %d \n",t[1]);

    t[1] = 100;
    printf("t[1] is %d \n",t[1]);
    //printf("t[2] is %d \n",t[2]);
    //printf("t[3] is %d \n",t[3]);
    //printf("t[4] is %d \n",t[4]);

    //t[1] = 100;

    //printf("value[1] is %d \n",value[1]);
    //printf("t[1] is %d \n",t[1]);

}

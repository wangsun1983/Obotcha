#include <stdio.h>
#include <unistd.h>

//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "Integer.hpp"
#include "StrongPointer.hpp"
#include "Long.hpp"
#include "SqlData.hpp"

using namespace obotcha;


DECLARE_SIMPLE_CLASS(Student) {
  DECLARE_TABLE(Student,Age);
  DECLARE_INT_DATA_MEMBER(Student,Age);
};

PUBLISH_TABLE(Student);

int main() {
  
  printf("---[TimeWatcher Test Start]--- \n");
  Student t = createStudent();
  sql_data_set m = t->getSqlAssignment(0,"Age");
  m(t.get_pointer(),"123");
  printf("t is %d \n",t->getAge());

  while(1){}

}

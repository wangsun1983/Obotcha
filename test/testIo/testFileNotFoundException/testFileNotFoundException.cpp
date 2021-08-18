#include <stdio.h>
#include <unistd.h>

#include "Handler.hpp"
#include "Message.hpp"
#include "System.hpp"

#include "FileNotFoundException.hpp"

using namespace obotcha;

DECLARE_CLASS(MyFileException) EXTENDS(FileNotFoundException) {
public:
  void doTest(int v) {
    switch(v) {
      case 0:
        printf("it is zero \n");
      break;

      case 1:
        throw createFileNotFoundException("i am error!!!!!");
      break;
    }
  }
};

int main() {
  MyFileException m = MyFileException();
  m->doTest(0);

  try {
    m->doTest(1);
  }catch(FileNotFoundException e) {
    printf("error is %s \n",e->getErrInfo()->toChars());
    e->printStack();
  }
}

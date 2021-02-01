#include <stdio.h>
#include <unistd.h>

#include "HttpContentType.hpp"
#include "HttpContentTypeTool.hpp"

using namespace obotcha;

int testContentSuffixParse() {
  //case1
  HttpContentTypeTool tool = st(HttpContentTypeTool)::getInstance();

  int type = tool->suffixToInt(createString("mml"));
  printf("type is %d \n",type);
}

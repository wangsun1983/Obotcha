#include <iostream>
#include <stdio.h>
#include <unistd.h>

#include "Thread.hpp"
#include "ArrayList.hpp"
#include "Integer.hpp"
#include "String.hpp"
#include "Base64.hpp"
#include "Log.hpp"

using namespace obotcha;

int main() {
  String abc = "hello worldhello worldhello worldhello worldhello worldhello worldhello worldhello worldhello worldhello worldhello worldhello worldhello worldhello worldhello worldhello worldhello worldhello worldhello worldhello worldhello worldhello worldhello worldhello worldhello worldhello worldhello worldhello worldhello worldhello worldhello worldhello worldhello worldhello worldhello worldhello world";
  Base64 base64 = createBase64();
  String r1 = base64->encode(abc);
  LOGD("r1 is ",r1,"r1 size is ",r1->size());

  String r2 = base64->decode(r1);
  LOGD("r2 is ",r2);
}

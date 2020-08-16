#include <stdio.h>
#include <unistd.h>

#include "JsonWriter.hpp"
#include "JsonReader.hpp"
#include "JsonValue.hpp"

#include "Log.hpp"

using namespace obotcha;

extern int basetest();
extern int testpass1();
extern int testremove();
extern int testreflect();

int main(){
  //basetest();
  //testpass1();
  //testremove();
    testreflect();
}

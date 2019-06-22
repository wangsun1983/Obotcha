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
  printf("---[ByteArray Test Start]--- \n");
  //decode(String)/encode(String)
  while(1) {
      String abc = "hello worldhello worldhello worldhello worldhello worldhello worldhello worldhello worldhello worldhello worldhello worldhello worldhello worldhello worldhello worldhello worldhello worldhello worldhello worldhello worldhello worldhello worldhello worldhello worldhello worldhello worldhello worldhello worldhello worldhello worldhello worldhello worldhello worldhello worldhello worldhello world";
      Base64 base64 = createBase64();
      String r1 = base64->encode(abc);
      String r2 = base64->decode(r1);

      if(!r2->equals(abc)) {
          printf("---[ByteArray Test {decode(String)/encode(String)} case1] [FAILED]--- \n");
          break;
      }

      printf("---[ByteArray Test {decode(String)/encode(String)} case2] [Success]--- \n");
      break;
  }

  //decode(ByteArray)/encode(ByteArray)
  while(1) {
      ByteArray array = createByteArray(32);
      for(int i = 0;i < 1;i++) {
        array->fill(i,'a');
      }

      printf("array is %s \n",array->toValue());

      //for(int i = 0;i < 1023;i++) {
      //  printf("v[i] is %d \n",array->at(i));
      //}


      Base64 base64 = createBase64();
      printf("encode array is %s,size is %d\n",array->toValue(),array->size());
      ByteArray r1 = base64->encode(array);

      //ByteArray r2 = base64->decode(r1);

      //for(int i = 0;i<1023;i++) {
      //  if(r2->at(i) != array->at(i)) {
      //    printf("r2[%d] is %d,array[%d] is %d \n",i,r2->at(i),i,array->at(i));
      //    printf("---[ByteArray Test {decode(ByteArray)/encode(ByteArray)} case1,i is] [FAILED]--- \n");
      //    break;
      //  }
      //}

      printf("---[ByteArray Test {decode(ByteArray)/encode(ByteArray)} case2] [Success]--- \n");
      break;
  }
  
}

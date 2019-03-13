#include <stdio.h>
#include <unistd.h>

#include "Thread.hpp"
#include "Log.hpp"


int main() {

    //Log::d("hello world");
    //Log::d("hello world2");
    //Log::d("hello world3");

    //Log::d({"aa is ","bb","dd"});
    //Log::d({"aa1 is ","bb1","cc1"});

    //LOGD(1,23,4);
    String abc = "aaaa";
    LOGD("string is ",2," i need ", "an apple");

}

#include <stdio.h>
#include <unistd.h>

//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "Aes.hpp"
#include "String.hpp"
#include "ByteArray.hpp"
#include "NumberFormatter.hpp"

using namespace obotcha;

int main() {
    //static String format(const int value);
    printf("---[NumberFormatter Test Start]--- \n");
	while(1) {
        String v = st(NumberFormatter)::format(12);
        
        if(v == nullptr || !v->equals("12")) {
            printf("---[NumberFormatter Test {format(const int)} case1] [FAILED]--- \n");
            break;
        }

        printf("---[NumberFormatter Test {format(const int)} case2] [Success]--- \n");
        break;
    }

    //String format(const int value, const int width);
    while(1) {
        String v = st(NumberFormatter)::format(12,5);
        if(v == nullptr || !v->equals("   12")) {
            printf("---[NumberFormatter Test {format(const int,const int)} case1] [FAILED]--- \n");
            break;
        }

        printf("---[NumberFormatter Test {format(const int,const int)} case2] [Success]--- \n");
        break;
    }

	//String format0(const int value, const int width);
    while(1) {
        String v = st(NumberFormatter)::format0(12,5);
        if(v == nullptr || !v->equals("00012")) {
            printf("---[NumberFormatter Test {format0(const int,const int)} case1] [FAILED]--- \n");
            break;
        }

        printf("---[NumberFormatter Test {format0(const int,const int)} case2] [Success]--- \n");
        break;
    }

}

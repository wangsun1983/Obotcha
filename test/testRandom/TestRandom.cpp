#include <stdio.h>
#include <unistd.h>
#include "Math.hpp"
#include "Random.hpp"

using namespace obotcha;

int main() {

    printf("---[Random Test Start]--- \n");

    //int nextInt()
    while(1) {
        int array[1000];
        bool isOk = true;
        Random rand = createRandom();
        for(int index = 0;index < 1000;index++) {
            int v1 = rand->nextInt();
            for(int ckindex = 0;ckindex < index;ckindex++) {
                if(v1 == array[ckindex]) {
                    std::cout<<"v1 is "<<v1<<";array["<<ckindex<<"] = "<<array[ckindex]<<std::endl;
                    isOk = false;
                    break;
                }
            }

            array[index] = v1;

            if(!isOk) {
                printf("---[TestRandom Test {nextInt(int)} case1] [FAILED]--- \n");
                break;
            }
        }

        if(isOk) {
            printf("---[TestRandom Test {nextInt(int)} case2] [Success]--- \n");
            break;
        }

        break;
    }

    //static int nextInt(int min,int max);
    while(1) {
        int max = 100;
        int min = 10;
        Random rand = createRandom();
        for(int index = 0;index < 100000;index++) {
            int v = rand->nextInt(min,max);
            if(v > max || v < min) {
                printf("---[TestRandom Test {nextInt(int,int)} case1] [FAIL]--- \n");
                break;
            }
        }

        printf("---[TestRandom Test {nextInt(int,int)} case2] [Success]--- \n");
        break;
    }

    //static int nextInt(int min);
    while(1) {
        int min = 10;
        Random rand = createRandom();
        for(int index = 0;index < 100000;index++) {
            int v = rand->nextInt(min);
            if(v < min) {
                printf("---[TestRandom Test {nextInt(int)} case1] [FAIL]--- \n");
                break;
            }
        }

        printf("---[TestRandom Test {nextInt(int)} case2] [Success]--- \n");
        break;
    }

    //static double nextDouble();
    while(1) {
        double array[1000];
        bool isOk = true;
        Random rand = createRandom();
        for(int index = 0;index < 1000;index++) {
            double v1 = rand->nextDouble();
            //std::cout<<"v1 is "<<v1;
            for(int ckindex = 0;ckindex < index;ckindex++) {
                //if(v1 == array[ckindex]) {
                if(st(Math)::compare(v1,array[ckindex]) == CompareParamEqual) {
                    std::cout<<"v1 is "<<v1<<";array["<<ckindex<<"] = "<<array[ckindex]<<std::endl;
                    isOk = false;
                    break;
                }
            }

            array[index] = v1;

            if(!isOk) {
                printf("---[TestRandom Test {nextDouble()} case1] [FAILED]--- \n");
                break;
            }
        }

        if(isOk) {
            printf("---[TestRandom Test {nextDouble()} case2] [Success]--- \n");
            break;
        }

        break;
    }



    //static double nextDouble(double min,double max);
    while(1) {
        Random rand = createRandom();
        for(int index = 0;index < 1000;index++) {
            double min = 10.0001;
            double max = 15.00001;
            double t = rand->nextDouble(min,max);
            if(st(Math)::compare(t,min) == CompareParam2Larger || st(Math)::compare(t,max) == CompareParam1Larger) {
                printf("---[TestRandom Test {nextDouble(double,double)} case1] [FAILED]--- \n");
                break;
            }
        }

        printf("---[TestRandom Test {nextDouble(double,double)} case2] [Success]--- \n");
        break;
    }

    //static double nextDouble(double min);
    while(1) {
        Random rand = createRandom();
        for(int index = 0;index < 1000;index++) {
            double min = 10.0001;
            double t = rand->nextDouble(min);
            if(st(Math)::compare(t,min) == CompareParam2Larger) {
                printf("---[TestRandom Test {nextDouble(double)} case1] [FAILED]--- \n");
                break;
            }
        }

        printf("---[TestRandom Test {nextDouble(double)} case2] [Success]--- \n");
        break;
    }

    //static void nextBytes(ByteArray);
}

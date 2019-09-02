#include <stdio.h>
#include <iostream>
#include <cmath>

#include "Math.hpp"


using namespace obotcha;

int main() {
    printf("---[Math Test Start]--- \n");

    //static long abs(long);
    while(1) {
      long v1 = st(Math)::abs(1);
      if(v1 != 1) {
        printf("---[Math Test {abs(long)} case1] [FAIL]--- \n");
        break;
      }

      long v2 = st(Math)::abs(-1);
      if(v2 != 1) {
        printf("---[Math Test {abs(long)} case2] [FAIL]--- \n");
        break;
      }

      printf("---[Math Test {abs(long)} case3] [Success]--- \n");
      break;
    }

    //static double abs(double);
    while(1) {
      double v1 = st(Math)::abs(1.1);
      if(st(Math)::compare(v1,1.1) != CompareParamEqual) {
        printf("---[Math Test {abs(double)} case1] [FAIL]--- \n");
        break;
      }

      double v2 = st(Math)::abs(-1.1);
      if(st(Math)::compare(v2,1.1) != CompareParamEqual) {
        printf("---[Math Test {abs(double)} case2] [FAIL]--- \n");
        break;
      }

      printf("---[Math Test {abs(double)} case3] [Success]--- \n");
      break;
    }

    //static int abs(int);
    while(1) {
      long v1 = st(Math)::abs(1);
      if(v1 != 1) {
        printf("---[Math Test {abs(int)} case1] [FAIL]--- \n");
        break;
      }

      long v2 = st(Math)::abs(-1);
      if(v2 != 1) {
        printf("---[Math Test {abs(int)} case2] [FAIL]--- \n");
        break;
      }

      printf("---[Math Test {abs(int)} case3] [Success]--- \n");
      break;
    }

    //static float abs(float);
    while(1) {
      float v1 = st(Math)::abs(1.1f);
      if(v1 != 1.1f) {
        printf("---[Math Test {abs(float)} case1] [FAIL]--- \n");
        break;
      }

      float v2 = st(Math)::abs(-1.1f);
      if(v2 != 1.1f) {
        printf("---[Math Test {abs(float)} case2] [FAIL]--- \n");
        break;
      }

      printf("---[Math Test {abs(float)} case3] [Success]--- \n");
      break;
    }

    //static double cos(double);
    while(1) {
      double v1 = st(Math)::cos(60);
      //std::cout<<"v1 is "<<v1;
      //std::cout<<"std::cos is  "<<std::cos(60);
      
      if(st(Math)::compare(v1,0.5) != CompareParamEqual) {
        printf("---[Math Test {cos(float)} case1] [FAIL]--- \n");
        break;
      }

      double v2 = st(Math)::cos(0);
      if(st(Math)::compare(v2,1) != CompareParamEqual) {
        printf("---[Math Test {cos(float)} case2] [FAIL]--- \n");
        break;
      }
      
      printf("---[Math Test {cos(float)} case3] [Success]--- \n");
      break;
    }

    //static double sin(double);
    while(1) {
      double v1 = st(Math)::sin(30);
      if(st(Math)::compare(v1,0.5) != CompareParamEqual) {
        printf("---[Math Test {sin(float)} case1] [FAIL]--- \n");
        break;
      }

      double v2 = st(Math)::sin(90);
      if(st(Math)::compare(v2,1) != CompareParamEqual) {
        printf("---[Math Test {sin(float)} case2] [FAIL]--- \n");
        break;
      }

      break;
    }

    //static double tan(double);
    while(1) {
        double v1 = st(Math)::tan(45);
        if(st(Math)::compare(v1,1) != CompareParamEqual) {
            printf("---[Math Test {tan(float)} case1] [FAIL]--- \n");
            break;
        }

        /*
        double v2 = st(Math)::tan(90);
        if(v2 != 1) {
            printf("---[Math Test {sin(float)} case1] [FAIL]--- \n");
            break;
        }
        */

        break;
    }

    
    //static double acos(double);
    while(1) {
        double v1 = st(Math)::acos(0.5);
        if(st(Math)::compare(v1,60) != CompareParamEqual) {
            printf("---[Math Test {acos(double)} case1] [FAIL]--- \n");
            break;
        }

        double v2 = st(Math)::acos(0);
        if(st(Math)::compare(v2,90) != CompareParamEqual) {
            printf("---[Math Test {acos(double)} case2] [FAIL]--- \n");
            break;
        }

        double v3 = st(Math)::acos(1);
        if(st(Math)::compare(v3,0) != CompareParamEqual) {
            printf("---[Math Test {acos(double)} case3] [FAIL]--- \n");
            break;
        }

        printf("---[Math Test {acos(double)} case4] [Success]--- \n");
        break;
    }

    
    //static double asin(double);
    while(1) {
        double v1 = st(Math)::asin(0.5);
        if(st(Math)::compare(v1,30) != CompareParamEqual) {
            printf("---[Math Test {asin(double)} case1] [FAIL]--- \n");
            break;
        }

        double v2 = st(Math)::asin(0);
        if(st(Math)::compare(v2,0) != CompareParamEqual) {
            printf("---[Math Test {asin(double)} case2] [FAIL]--- \n");
            break;
        }

        double v3 = st(Math)::asin(1);
        if(st(Math)::compare(v3,90) != CompareParamEqual) {
            printf("---[Math Test {asin(double)} case3] [FAIL]--- \n");
            break;
        }

        printf("---[Math Test {asin(double)} case4] [Success]--- \n");
        break;
    }

    
    //static double atan(double);
    while(1) {
        double v1 = st(Math)::atan(1);
        if(st(Math)::compare(v1,45) != CompareParamEqual) {
            printf("---[Math Test {atan(double)} case1] [FAIL]--- \n");
            break;
        }

        double v2 = st(Math)::atan(0);
        if(st(Math)::compare(v2,0) != CompareParamEqual) {
            printf("---[Math Test {atan(double)} case2] [FAIL]--- \n");
            break;
        }

        printf("---[Math Test {atan(double)} case4] [Success]--- \n");
        break;
    }

    
    //static long max(long,long);
    while(1) {
        long value1 = 100;
        long value2 = 200;
        if(st(Math)::max(value1,value2) != value2) {
            printf("---[Math Test {max(long,long)} case1] [FAIL]--- \n");
            break;
        }

        printf("---[Math Test {max(long,long)} case2] [Success]--- \n");
        break;
    }

    //static double max(double,double);
    while(1) {
        double value1 = 2.000001;
        double value2 = 2.0000001;
        double max = st(Math)::max(value1,value2);
        if(st(Math)::compare(max,value1) != CompareParamEqual) {
            printf("---[Math Test {max(double,double)} case1] [FAIL]--- \n");
            break;
        }

        printf("---[Math Test {max(double,double)} case2] [Success]--- \n");
        break;
    }

    //static float max(float,float);
    while(1) {
        float value1 = 2.000001;
        float value2 = 2.0000001;
        float max = st(Math)::max(value1,value2);
        if(st(Math)::compare(max,value1) != CompareParamEqual) {
            printf("---[Math Test {max(float,float)} case1] [FAIL]--- \n");
            break;
        }

        printf("---[Math Test {max(float,float)} case2] [Success]--- \n");
        break;
    }

    //static long min(long,long);
    while(1) {
        long value1 = 100;
        long value2 = 200;
        if(st(Math)::min(value1,value2) != value1) {
            printf("---[Math Test {min(long,long)} case1] [FAIL]--- \n");
            break;
        }

        printf("---[Math Test {min(long,long)} case2] [Success]--- \n");
        break;
    }

    //static double min(double,double);
    while(1) {
        double value1 = 2.000001;
        double value2 = 2.0000001;
        double min = st(Math)::min(value1,value2);
        if(st(Math)::compare(min,value2) != CompareParamEqual) {
            //std::cout<<"value2 is "<<value1<<";min is "<<min<<std::endl;
            printf("---[Math Test {min(double,double)} case1] [FAIL]--- \n");
            break;
        }

        printf("---[Math Test {min(double,double)} case2] [Success]--- \n");
        break;
    }

    //static float min(float,float);
    while(1) {
        float value1 = 2.000001;
        float value2 = 2.0000001;
        float min = st(Math)::min(value1,value2);
        if(st(Math)::compare(min,value2) != CompareParamEqual) {
            printf("---[Math Test {min(float,double)} case1] [FAIL]--- \n");
            break;
        }

        printf("---[Math Test {min(float,double)} case2] [Success]--- \n");
        break;
    }


    //static double pow(double,double);
    while(1) {
        double t1 = 2.1;
        double t2 = st(Math)::pow(t1,3);
        if(st(Math)::compare(t2,9.261) != CompareParamEqual) {
            printf("---[Math Test {pow(double,double)} case1] [FAIL]--- \n");
            break;
        }

        double t3 = st(Math)::pow(t1,0);
        if(st(Math)::compare(t3,1) != CompareParamEqual) {
            printf("---[Math Test {pow(double,double)} case2] [FAIL]--- \n");
            break;
        }

        printf("---[Math Test {pow(double,double)} case3] [Success]--- \n");
        break;
    }

    //static long pow(long,long);
    while(1) {
        long t1 = 2;
        long t2 = st(Math)::pow(t1,3);
        if(t2 != 8) {
            printf("---[Math Test {pow(long,long)} case1] [FAIL]--- \n");
            break;
        }

        long t3 = st(Math)::pow(t1,0);
        if(t3 != 1) {
            printf("---[Math Test {pow(long,long)} case2] [FAIL]--- \n");
            break;
        }

        printf("---[Math Test {pow(long,long)} case3] [Success]--- \n");
        break;
    }

    //static double sqrt(double);
    while(1) {
        double v1 = 1.4142135623730950488016887242097;
        double v2 = st(Math)::sqrt(2);
        if(st(Math)::compare(v1,v2) != CompareParamEqual) {
            printf("---[Math Test {sqrt(double)} case1] [FAIL]--- \n");
            break;
        }

        double v3 = st(Math)::sqrt(4);
        if(st(Math)::compare(v3,2) != CompareParamEqual) {
            printf("---[Math Test {sqrt(double)} case2] [FAIL]--- \n");
            break;
        }

        printf("---[Math Test {sqrt(double)} case3] [Success]--- \n");
        break;
    }

    //static int ceil(double);
    while(1) {
        double v1 = 1.01;
        double v2 = st(Math)::ceil(v1);
        if(st(Math)::compare(v2,2) != CompareParamEqual) {
            printf("---[Math Test {ceil(double)} case1] [FAIL]--- \n");
            break;
        }

        double v3 = st(Math)::ceil(4.99);
        if(st(Math)::compare(v3,5) != CompareParamEqual) {
            printf("---[Math Test {ceil(double)} case2] [FAIL]--- \n");
            break;
        }

        printf("---[Math Test {ceil(double)} case3] [Success]--- \n");
        break;
    }

    //static int floor(double);
    while(1) {
        double v1 = 1.99;
        double v2 = st(Math)::floor(v1);
        if(st(Math)::compare(v2,1) != CompareParamEqual) {
            printf("---[Math Test {floor(double)} case1] [FAIL]--- \n");
            break;
        }

        double v3 = st(Math)::floor(4.01);
        if(st(Math)::compare(v3,4) != CompareParamEqual) {
            printf("---[Math Test {floor(double)} case2] [FAIL]--- \n");
            break;
        }

        printf("---[Math Test {floor(double)} case3] [Success]--- \n");
        break;
    }
    
}

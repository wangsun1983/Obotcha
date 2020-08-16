#include <stdio.h>
#include <unistd.h>
#include <iostream>

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "Reflect.hpp"
#include "String.hpp"

using namespace obotcha;

DECLARE_SIMPLE_CLASS(MyReflectData) {
public:
    int data1;
    int data2;
    double data3;

    DECLARE_REFLECT_FIELD(_MyReflectData,data1,data2,data3)
};

int main() {
    MyReflectData data = createMyReflectData();
    data->setFieldValue(createString("data1"),"1");
    data->setFieldValue(createString("data2"),"123");
    data->setFieldValue(createString("data3"),"1.2");

    std::cout<<"data1 is "<<data->data1<<std::endl;
    std::cout<<"data2 is "<<data->data2<<std::endl;
    std::cout<<"data3 is "<<data->data3<<std::endl;
}

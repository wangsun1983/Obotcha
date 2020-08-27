#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <type_traits>

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "Reflect.hpp"
#include "String.hpp"

using namespace obotcha;

DECLARE_SIMPLE_CLASS(MyInnerData) {
public:
    int innerData;
    DECLARE_REFLECT_FIELD(MyInnerData,innerData)
};

DECLARE_SIMPLE_CLASS(MyReflectData) {
public:
    int data1;
    double data2;
    MyInnerData data3;

    DECLARE_REFLECT_FIELD(MyReflectData,data1,data2,data3)
};

int main() {
    MyReflectData data = createMyReflectData();
    //data->data3 = createMyInnerData();

    data->setFieldIntValue("data1",1);
    data->setFieldDoubleValue("data2",1.125);
    
    int v1 = data->getFieldIntValue("data1");
    double v2 = data->getFieldDoubleValue("data2");

    printf("i create \n");
    data->createFieldValue("data3");
    auto v4 = data->getFieldObjectValue("data3");
    printf("i create1 \n");
    v4->setFieldIntValue("innerData",167);
    printf("i create2 \n");

    //data->setFieldObjectValue("data3",v4);

    std::cout<<"data1 is "<<v1<<std::endl;
    std::cout<<"data2 is "<<v2<<std::endl;
    std::cout<<"data3 is "<<data->data3->innerData<<std::endl;
    //std::cout<<"data2 is "<<data->data3->innerData<<std::endl;
}

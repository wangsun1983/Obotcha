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
    Field f = data->getField("data1");
    f->setValue(123);

    Field f2 = data->getField("data2");
    f2->setValue(1.234);

    Field f3 = data->getField("data1");
    Field f4 = data->getField("data2");
    printf("create start \n");
    Field f5 = data->getField("data3");
    f5->createObject();

    //Field f6 = data->getField("data3");
    auto innerData1 = f5->getObjectValue();

    Field f7 = innerData1->getField("innerData");
    f7->setValue(99);

#if 0
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
#endif
    //data->setFieldObjectValue("data3",v4);

    std::cout<<"data1 is "<<data->data1<<std::endl;
    std::cout<<"data2 is "<<data->data2<<std::endl;

    std::cout<<"field data1 is "<<f3->getIntValue()<<std::endl;
    std::cout<<"field data1 is "<<f4->getDoubleValue()<<std::endl;

    std::cout<<"inner data is "<<data->data3->innerData<<std::endl;
    //std::cout<<"data3 is "<<data->data3->innerData<<std::endl;
    //std::cout<<"data2 is "<<data->data3->innerData<<std::endl;
}

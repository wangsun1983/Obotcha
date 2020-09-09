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
    //DECLARE_REFLECT_FIELD(MyInnerData,innerData)
};

DECLARE_SIMPLE_CLASS(MyReflectData) {
public:
    int data1;
    double data2;
    ArrayList<MyInnerData> data3;

    //DECLARE_REFLECT_FIELD(MyReflectData,data1,data2,data3)
};

template<typename T>
void sayhello(T t) {
    printf("hello \n");
}

template<typename T>
void sayhello(ArrayList<T> t) {
    printf("hello2 \n");
}

int main() {
    ArrayList<String> list = createArrayList<String>();
    sayhello(list);

#if 0    
    MyReflectData data = createMyReflectData();
    Field f = data->getField("data3");
    f->createObject();
    auto value = f->createListItemObject();
    if(value != nullptr) {
        printf("value is not nullptr \n");
        Field f2 = value->getField("innerData");
        f2->setValue(123);
    } else {
        printf("value is nullptr \n");
    }
    //Field f2 = value->getField("innerData");
    //f2->setValue("123");

    if(data->data3 != nullptr) {
        MyInnerData innerData = data->data3->get(0);
        if(innerData != nullptr) {
            printf("innderdata is %d \n",innerData->innerData);
        }
    }
#endif
}

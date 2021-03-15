#ifndef __OBOTCHA_LIST_HPP__
#define __OBOTCHA_LIST_HPP__

#include <vector>
#include <algorithm>

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "Boolean.hpp"
#include "Double.hpp"
#include "Float.hpp"
#include "Integer.hpp"
#include "Long.hpp"
#include "String.hpp"
#include "MethodNotSupportException.hpp"
#include "ArrayIndexOutOfBoundsException.hpp"

namespace obotcha {

//----------------- ArrayList ---------------------
DECLARE_CLASS(List,1) {
public:
    _List(int length) {
        mSize = length;
        elements = new T[length];
    }

    _List(T *data,int nums) {
        mSize = nums;
        elements = new T[nums];
        for(int i = 0;i<nums;i++) {
            elements[i] = data[i];
        }
    }
    
    int size() {
        return mSize;
    }

    T& operator[] (int i) {
        T &v = elements[i];   
        return v;
    }

    ~_List() {
        if(elements != nullptr) {
            delete []elements;
            elements = nullptr;
        }
    }

private:
    int mSize;
    T *elements;
};

}
#endif

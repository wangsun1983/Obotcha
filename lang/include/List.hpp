#ifndef __LIST_HPP__
#define __LIST_HPP__

#include <vector>
#include <algorithm>

#include "ListObject.hpp"
#include "ListPointer.hpp"
#include "Boolean.hpp"
#include "Double.hpp"
#include "Float.hpp"
#include "Integer.hpp"
#include "Long.hpp"
#include "String.hpp"
#include "MethodNotSupportException.hpp"
#include "ArrayIndexOutOfBoundsException.hpp"

#include "Collection.hpp"

using namespace std;

namespace obotcha {
    
//----------------- ArrayList ---------------------
DECLARE_LIST(List,1) {
public:
    _List(int length) {
        elements.reserve(length);
    }

    _List(T *data,int nums) {
        elements.reserve(nums);
        for(int i = 0;i<nums;i++) {
            elements.push_back(data[i]);
        }
    }
    
    int size() {
        return elements.capacity();
    }

    T& operator[] (int i) {
        T &v = elements[i];   
        return v;
    }

private:
    std::vector<T> elements;
};

}
#endif

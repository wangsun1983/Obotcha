#ifndef __OBOTCHA_HASH_KEY_HPP__
#define __OBOTCHA_HASH_KEY_HPP__

#include <algorithm>
#include <unordered_map>
#include <string>

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "ArrayList.hpp"
#include "NullPointerException.hpp"

namespace obotcha {

//hash function of map
template<typename T>
class KeyHash{
public:    
    size_t operator()(const T &A)const{
        if(A == nullptr) {
            return std::hash<int>{}(0);
        }
        return A->hashcode();
    }
};

#define KeyHashSimpleDataTypeFunc(X) template<> \
class KeyHash<X> { \
public: \
    size_t operator()(const X &A)const{ \
        return std::hash<X>{}(A); \
    } \
}\

KeyHashSimpleDataTypeFunc(bool);
KeyHashSimpleDataTypeFunc(double);
KeyHashSimpleDataTypeFunc(float);
KeyHashSimpleDataTypeFunc(int);
KeyHashSimpleDataTypeFunc(long);
KeyHashSimpleDataTypeFunc(uint8_t);
KeyHashSimpleDataTypeFunc(uint16_t);
KeyHashSimpleDataTypeFunc(uint32_t);
KeyHashSimpleDataTypeFunc(uint64_t);
KeyHashSimpleDataTypeFunc(std::string);

//compare function of map
template<typename T>
class KeyComapre
{
public:
    bool operator()(const T &k1, const T &k2) const {
        if(k1 != nullptr && k2 != nullptr) {
            return k1->hashcode() == k2->hashcode();
        } else if(k1 == nullptr && k2 == nullptr) {
            return true;
        }

        return false;
    }
};

#define KeyCompareSimpleDataTypeFunc(X) template<> \
class KeyComapre<X> {\
public:\
    bool operator()(const X &k1, const X &k2) const {\
        return k1 == k2;\
    }\
};\

KeyCompareSimpleDataTypeFunc(bool);
KeyCompareSimpleDataTypeFunc(double);
KeyCompareSimpleDataTypeFunc(float);
KeyCompareSimpleDataTypeFunc(int);
KeyCompareSimpleDataTypeFunc(long);
KeyCompareSimpleDataTypeFunc(uint8_t);
KeyCompareSimpleDataTypeFunc(uint16_t);
KeyCompareSimpleDataTypeFunc(uint32_t);
KeyCompareSimpleDataTypeFunc(uint64_t);
KeyCompareSimpleDataTypeFunc(std::string);

}
#endif
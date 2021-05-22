#ifndef __OBOTCHA_HASHMAP_HPP__
#define __OBOTCHA_HASHMAP_HPP__

#include <algorithm>
#include <unordered_map>
#include <string>

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "ArrayList.hpp"
#include "NullPointerException.hpp"

namespace obotcha {

template<typename T,typename U>
class _MapIterator;

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

//----------------------- HashMap<T,U> -----------------------
DECLARE_CLASS(HashMap,2) {
public:
    friend class _MapIterator<T,U>;

    void put(const T &t,const U &u) {
        hashmap[t] = u;
    }

    U get(const T &t) {
        auto ite = hashmap.find(t);
        if(ite != hashmap.end()) {  
            return ite->second;
        }

        return nullptr;
    }

    void remove(const T &t) {
        auto ite = hashmap.find(t);
        if(ite == hashmap.end()) {   
            return;
        }
        hashmap.erase(ite);
    }

    bool isEmpty() {
        return hashmap.size() == 0;
    }

    void clear() {
        hashmap.clear();
    }

    int size() {
        return hashmap.size();
    }

    //template<typename V>
    ArrayList<T> keySet() {
        ArrayList<T> keyset = createArrayList<T>();
        for (auto it= hashmap.begin();it != hashmap.end();it++) {
            keyset->add(it->first);
        }

        return keyset;
    }
    
    //template<typename V>
    ArrayList<U> entrySet() {
        ArrayList<U> keyset = createArrayList<U>();
        for (auto it= hashmap.begin();it != hashmap.end();it++) {
            keyset->add(it->second);
        }

        return keyset;
    }

    //add foreach lambda
    using foreachCallback = std::function<int(T,U)>;
    inline void foreach(foreachCallback callback) {
        for (auto it= hashmap.begin();it != hashmap.end();it++) {
            if(callback(it->first,it->second) < 0) {
                break;
            }
        }
    }

    U &operator[](const T &k) {
        return hashmap[k];
    }
    
    sp<_MapIterator<T,U>> getIterator() {
        return new _MapIterator<T,U>(this);
    }

private:
    std::unordered_map<T,U,KeyHash<T>,KeyComapre<T>> hashmap;

    typename std::unordered_map<T,U,KeyHash<T>,KeyComapre<T>>::iterator begin() {
        return hashmap.begin();
    }

    typename std::unordered_map<T,U,KeyHash<T>,KeyComapre<T>>::iterator end() {
        return hashmap.end();
    }
};

//----------------- MapIterator ---------------------
DECLARE_CLASS(MapIterator,2) {

public:
    _MapIterator(_HashMap<T,U> *map) {
        mHashMap.set_pointer(map);
        //map->incStrong(0);

        iterator = map->begin();
    }

    _MapIterator(HashMap<T,U> map) {
        mHashMap = map;
        iterator = mHashMap->begin();
    }

    T getKey() {
        return iterator->first;
    }

    U getValue() {
        return iterator->second;
    }

    bool hasValue() {
        return iterator != mHashMap->end();
    }

    bool next() {
        if(iterator ==  mHashMap->end()) {
            return false;
        }

        iterator++;
        return true;
    }

    void remove() {
        if(iterator ==  mHashMap->end()) {
            return;
        }

        mHashMap->hashmap.erase(iterator++);
    }
    
private:
    HashMap<T,U> mHashMap;    
    typename std::unordered_map<T,U,KeyHash<T>,KeyComapre<T>>::iterator iterator;
};

}
#endif
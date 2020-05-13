#ifndef __OBOTCHA_HASHMAP_HPP__
#define __OBOTCHA_HASHMAP_HPP__

#include <map>
#include <algorithm>
#include <hash_map>

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "Boolean.hpp"
#include "Double.hpp"
#include "Float.hpp"
#include "Integer.hpp"
#include "Long.hpp"
#include "String.hpp"

#include "Collection.hpp"
#include "ArrayList.hpp"
#include "NullPointerException.hpp"

using namespace std;

namespace obotcha {

template<typename T,typename U>
class _MapIterator;

//compare function of map
template<typename T>
class KeyComapre
{
public:
    bool operator()(const T k1, const T k2)const {
        return k1 == k2;
    }
};

//hash function of map
template<typename T>
class KeyHash{
public:    
    size_t operator()(T A)const{
        if(A == nullptr) { 
            return std::hash<int>{}(0);
        }
        return std::hash<std::uint64_t>{}((std::uint64_t)A.get_pointer()); 
    }
};

#define KeyHashSimpleDataTypeFunc(X) template<> \
class KeyHash<X> { \
public: \
    size_t operator()(const X A)const{ \
        return std::hash<X>{}(A); \
    } \
}\

KeyHashSimpleDataTypeFunc(bool);
//KeyHashSimpleDataTypeFunc(byte);=>eaquls uint8
KeyHashSimpleDataTypeFunc(double);
KeyHashSimpleDataTypeFunc(float);
KeyHashSimpleDataTypeFunc(int);
KeyHashSimpleDataTypeFunc(long);
KeyHashSimpleDataTypeFunc(std::uint8_t);
KeyHashSimpleDataTypeFunc(std::uint16_t);
KeyHashSimpleDataTypeFunc(std::uint32_t);
KeyHashSimpleDataTypeFunc(std::uint64_t);

#define KeyHashDataTypeFunc(X,Y) template<> \
class KeyHash<X> { \
public: \
    size_t operator()(const X A)const{ \
        if(A == nullptr) { \
            return std::hash<int>{}(0); \
        } \
        return std::hash<Y>{}(A->toValue()); \
    } \
}\

KeyHashDataTypeFunc(Boolean,bool);
KeyHashDataTypeFunc(Byte,byte);
KeyHashDataTypeFunc(Double,double);
KeyHashDataTypeFunc(Float,float);
KeyHashDataTypeFunc(Integer,int);
KeyHashDataTypeFunc(Long,long);
KeyHashDataTypeFunc(Uint8,std::uint8_t);
KeyHashDataTypeFunc(Uint16,std::uint16_t);
KeyHashDataTypeFunc(Uint32,std::uint32_t);
KeyHashDataTypeFunc(Uint64,std::uint64_t);

template<>
class KeyHash<String> { 
public:
    size_t operator()(String A)const{
        if(A == nullptr) {
            return std::hash<int>{}(0);
        }
        return std::hash<std::string>{}(A->getStdString()); 
    } 
};

//----------------------- HashMap<T,U> -----------------------
DECLARE_CLASS(HashMap,2) {
public:
    friend class _MapIterator<T,U>;

    void put(T t,U u) {
        hashmap[t] = u;
    }

    U get(T t) {
        auto ite = hashmap.find(t);
        if(ite != hashmap.end()) {  
            return ite->second;
        }

        return nullptr;
    }

    void remove(T t) {
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
    
    sp<_MapIterator<T,U>> getIterator() {
        return new _MapIterator<T,U>(this);
    }

private:
    __gnu_cxx::hash_map<T,U,KeyHash<T>,KeyComapre<T>> hashmap;

    typename __gnu_cxx::hash_map<T,U,KeyHash<T>,KeyComapre<T>>::iterator begin() {
        return hashmap.begin();
    }

    typename __gnu_cxx::hash_map<T,U,KeyHash<T>,KeyComapre<T>>::iterator end() {
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

        iterator = mHashMap->hashmap.erase(iterator);
    }
    
private:
    HashMap<T,U> mHashMap;    
    typename __gnu_cxx::hash_map<T,U,KeyHash<T>,KeyComapre<T>>::iterator iterator;
};

}
#endif
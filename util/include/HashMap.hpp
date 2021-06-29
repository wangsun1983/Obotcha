#ifndef __OBOTCHA_HASHMAP_HPP__
#define __OBOTCHA_HASHMAP_HPP__

#include <algorithm>
#include <unordered_map>
#include <string>

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "NullPointerException.hpp"
#include "HashKey.hpp"

namespace obotcha {

template<typename T,typename U>
class _MapIterator;

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
        return AutoClone(new _MapIterator<T,U>(this));
    }

    void merge(sp<_HashMap<T,U>> m) {
        auto iterator = m->getIterator();
        while(iterator->hasValue()) {
            T key = iterator->getKey();
            U value = iterator->getValue();
            hashmap[key] = value;

            iterator->next();
        }
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
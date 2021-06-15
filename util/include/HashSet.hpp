#ifndef __OBOTCHA_HASHSET_HPP__
#define __OBOTCHA_HASHSET_HPP__

#include <unordered_set>
#include <algorithm>

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "Long.hpp"
#include "String.hpp"
#include "HashKey.hpp"

#include<set>

namespace obotcha {

template<typename T>
class _HashSetIterator;

DECLARE_CLASS(HashSet,1) {

public:
    friend class _HashSetIterator<T>;

    _HashSet() {
        
    }

    void add(T val) {
        hashset.insert(val);
    }

    bool contains(T val) {
        if(hashset.find(val) == hashset.end()) {
            return false;
        }

        return true;
    }

    void add(HashSet<T> list) {
        hashset.insert(hashset.end(),list->hashset.begin(),list->hashset.end());
    }

    inline void clear() {
        hashset.clear();
    }

    inline int remove(T val) {
        return hashset.erase(val);
    }

    inline T get(int index) {
        return hashset[index];
    }

    inline int size() {
        return hashset.size();
    }

    sp<_HashSetIterator<T>> getIterator() {
        return AutoClone(new _HashSetIterator<T>(this));
    }

private:
    std::unordered_set<T,KeyHash<T>,KeyComapre<T>> hashset;

    typename std::unordered_set<T,KeyHash<T>,KeyComapre<T>>::iterator begin() {
        return hashset.begin();
    }

    typename std::unordered_set<T,KeyHash<T>,KeyComapre<T>>::iterator end() {
        return hashset.end();
    }
};

DECLARE_CLASS(HashSetIterator,1) {
public:
    _HashSetIterator(_HashSet<T> *list) {
        mList.set_pointer(list);
        iterator = list->begin();
    }

    _HashSetIterator(HashSet<T> list) {
        mList = list;
        iterator = mList->begin();
    }

    T getValue() {
        return *iterator;
    }

    bool hasValue() {
        return iterator != mList->end();
    }

    bool next() {
        if(iterator ==  mList->end()) {
            return false;
        }
        iterator++;
        return (iterator != mList->end());
    }

    bool remove() {
        if(iterator == mList->end()) {
            return false;
        }

        mList->hashset.erase(iterator);
        iterator++;
        return true;
    }
    
private:
    HashSet<T> mList;    
    typename std::unordered_set<T,KeyHash<T>,KeyComapre<T>>::iterator iterator;
};

}
#endif
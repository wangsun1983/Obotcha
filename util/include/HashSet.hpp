#ifndef __HASHSET_HPP__
#define __HASHSET_HPP__

#include <map>
#include <algorithm>

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "Boolean.hpp"
#include "Double.hpp"
#include "Float.hpp"
#include "Integer.hpp"
#include "Long.hpp"
#include "String.hpp"

#include "Collection.hpp"
#include "HashMap.hpp"

template<typename T>
class _SetIterator;

DECLARE_CLASS(HashSet,1) {

public:
    friend class _SetIterator<T>;

    _HashSet() {
        map = createHashMap<T,Integer>();
        v = createInteger(0);
    }

    void put(T val) {
        map->put(val,v);
    }

    sp<_SetIterator<T>> getIterator();

private:
    HashMap<T,Integer> map;
    Integer v;
};

DECLARE_CLASS(SetIterator,1) {
public:
    _SetIterator(_HashSet<T> *set) {
        mSets.set_pointer(set);
        iterator = set->map->getIterator();
    }

    _SetIterator(_HashSet<T> sets) {
        mSets = sets;
        iterator = mSets->map->getIterator();
    }

    T getValue() {
        //return iterator->second;
        return iterator->getKey();
    }

    bool hasValue() {
        return iterator->hasValue();
    }

    bool next() {
        return iterator->next();
    }
    
private:
    HashSet<T> mSets;
    MapIterator<T,Integer> iterator;
};

template<typename T>
SetIterator<T> _HashSet<T>::getIterator() {
    return new _SetIterator<T>(this);
}

#endif
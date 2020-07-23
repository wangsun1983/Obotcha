#ifndef __OBOTCHA_HASHSET_HPP__
#define __OBOTCHA_HASHSET_HPP__

#include <hash_set>
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

    void add(HashSet<T> list) {
        if(list == nullptr || list->size() == 0) {
            return;
        }

        hashset.insert(hashset.end(),list->hashset.begin(),list->hashset.end());
    }

    inline void clear() {
        hashset.clear();
    }

    inline int remove(T val) {
        /*
        typename vector<T>::iterator result = find(hashset.begin(), hashset.end(),val);
        if(result != hashset.end()) {
            hashset.erase(result);
            //return result - hashset.begin();
            return 0;
        }

        return -1;
        */
       hashset.erase(val);
    }

    inline T get(int index) {
         if(index >= hashset.size() || index < 0) {
            throw ArrayIndexOutOfBoundsException("HashSet get fail",hashset.size(),index);
        }

        return hashset[index];
    }

    inline int size() {
        return hashset.size();
    }

    sp<_HashSetIterator<T>> getIterator() {
        return new _HashSetIterator<T>(this);
    }

private:
    __gnu_cxx::hash_set<T,KeyHash<T>,KeyComapre<T>> hashset;

    typename __gnu_cxx::hash_set<T,KeyHash<T>,KeyComapre<T>>::iterator begin() {
        return hashset.begin();
    }

    typename __gnu_cxx::hash_set<T,KeyHash<T>,KeyComapre<T>>::iterator end() {
        return hashset.end();
    }
};

DECLARE_CLASS(HashSetIterator,1) {
public:
    _HashSetIterator(_HashSet<T> *list) {
        mList.set_pointer(list);
        //list->incStrong(0);
        iterator = list->begin();
    }

    _HashSetIterator(HashSet<T> list) {
        mList = list;
        iterator = mList->begin();
    }

    T getValue() {
        //return iterator->second;
        if(iterator == mList->end()) {
            //return nullptr;
            throw ArrayIndexOutOfBoundsException("iterator error");
        }

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

    //bool remove() {
    //    if(iterator == mList->end()) {
    //        return false;
    //    }

    //    iterator = mList->hashset.erase(iterator);
    //    return true;
    //}
    
private:
    HashSet<T> mList;    
    typename __gnu_cxx::hash_set<T,KeyHash<T>,KeyComapre<T>>::iterator iterator;
};

}
#endif
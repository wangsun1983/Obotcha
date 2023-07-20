#ifndef __OBOTCHA_HASHSET_HPP__
#define __OBOTCHA_HASHSET_HPP__

#include <algorithm>
#include <unordered_set>
#include <set>

#include "Object.hpp"
#include "HashKey.hpp"
#include "Inspect.hpp"

namespace obotcha {

template <typename T> class _HashSetIterator;

DECLARE_TEMPLATE_CLASS(HashSet, T) {
public:
    friend class _HashSetIterator<T>;

    _HashSet() {}

    void add(T val) { 
        hashset.insert(val); 
    }

    bool contains(T val) {
        return hashset.find(val) != hashset.end();
    }

    void add(HashSet<T> &list) {
        hashset.insert(list->hashset.begin(),list->hashset.end());
    }

    inline void clear() { 
        hashset.clear(); 
    }

    inline int remove(T val) { 
        return hashset.erase(val); 
    }

    inline T get(int index) { 
        auto iterator = hashset.begin();
        for(int i = 0;i < index;i++) {
            iterator++;
        }
        return *iterator;
    }

    inline int size() { 
        return hashset.size(); 
    }

    sp<_HashSetIterator<T>> getIterator() {
        return AutoClone(new _HashSetIterator<T>(this));
    }

private:
    std::unordered_set<T, HashKey<T>, KeyComapre<T>> hashset;

    typename std::unordered_set<T, HashKey<T>, KeyComapre<T>>::iterator
    begin() {
        return hashset.begin();
    }

    typename std::unordered_set<T, HashKey<T>, KeyComapre<T>>::iterator end() {
        return hashset.end();
    }
};

DECLARE_TEMPLATE_CLASS(HashSetIterator, T) {
public:
    explicit _HashSetIterator(_HashSet<T> * list) {
        mList.set_pointer(list);
        iterator = list->begin();
    }

    explicit _HashSetIterator(HashSet<T> list) {
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
        Inspect(iterator == mList->end(),false);
        iterator++;
        return (iterator != mList->end());
    }

    bool remove() {
        Inspect(iterator == mList->end(),false);
        iterator = mList->hashset.erase(iterator);
        return true;
    }

    T getItem() { 
        return *iterator; 
    }


private:
    HashSet<T> mList;
    typename std::unordered_set<T, HashKey<T>, KeyComapre<T>>::iterator
        iterator;
};

} // namespace obotcha
#endif
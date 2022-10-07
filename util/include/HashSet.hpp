#ifndef __OBOTCHA_HASHSET_HPP__
#define __OBOTCHA_HASHSET_HPP__

#include <algorithm>
#include <unordered_set>

#include "HashKey.hpp"
#include "Long.hpp"
#include "Object.hpp"
#include "String.hpp"
#include "StrongPointer.hpp"

#include <set>

namespace obotcha {

template <typename T> class _HashSetIterator;

DECLARE_TEMPLATE_CLASS(HashSet, T) {
public:
    friend class _HashSetIterator<T>;

    _HashSet() {}

    void add(T val) { hashset.insert(val); }

    bool contains(T val) {
        if (hashset.find(val) == hashset.end()) {
            return false;
        }

        return true;
    }

    void add(HashSet<T> list) {
        hashset.insert(hashset.end(), list->hashset.begin(),
                       list->hashset.end());
    }

    inline void clear() { hashset.clear(); }

    inline int remove(T val) { return hashset.erase(val); }

    inline T get(int index) { return hashset[index]; }

    inline int size() { return hashset.size(); }

    sp<_HashSetIterator<T>> getIterator() {
        return AutoClone(new _HashSetIterator<T>(this));
    }

private:
    std::unordered_set<T, KeyHash<T>, KeyComapre<T>> hashset;

    typename std::unordered_set<T, KeyHash<T>, KeyComapre<T>>::iterator
    begin() {
        return hashset.begin();
    }

    typename std::unordered_set<T, KeyHash<T>, KeyComapre<T>>::iterator end() {
        return hashset.end();
    }
};

DECLARE_TEMPLATE_CLASS(HashSetIterator, T) {
public:
    _HashSetIterator(_HashSet<T> * list) {
        mList.set_pointer(list);
        iterator = list->begin();
    }

    _HashSetIterator(HashSet<T> list) {
        mList = list;
        iterator = mList->begin();
    }

    T getValue() { return *iterator; }

    bool hasValue() { return iterator != mList->end(); }

    bool next() {
        if (iterator == mList->end()) {
            return false;
        }
        iterator++;
        return (iterator != mList->end());
    }

    bool remove() {
        if (iterator == mList->end()) {
            return false;
        }

        iterator = mList->hashset.erase(iterator);
        return true;
    }

    T getItem() { return *iterator; }


private:
    HashSet<T> mList;
    typename std::unordered_set<T, KeyHash<T>, KeyComapre<T>>::iterator
        iterator;
};

} // namespace obotcha
#endif
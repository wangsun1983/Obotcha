#ifndef __OBOTCHA_LIST_HPP__
#define __OBOTCHA_LIST_HPP__

#include <algorithm>
#include <vector>

#include "ArrayIndexOutOfBoundsException.hpp"
#include "Boolean.hpp"
#include "Double.hpp"
#include "Float.hpp"
#include "Integer.hpp"
#include "Long.hpp"
#include "MethodNotSupportException.hpp"
#include "Object.hpp"
#include "String.hpp"

namespace obotcha {

template <typename T> class _ListIterator;

//----------------- List ---------------------
DECLARE_TEMPLATE_CLASS(List, T) {
public:
    friend class _ListIterator<T>;

    explicit _List(int length) {
        mSize = length;
        elements = new T[length];
    }

    _List(T * data, int nums) {
        mSize = nums;
        elements = new T[nums];
        for (int i = 0; i < nums; i++) {
            elements[i] = data[i];
        }
    }

    _List(sp<_List<T>> ll) {
        mSize = ll->size();
        elements = new T[mSize];
        for (int i = 0; i < mSize; i++) {
            elements[i] = ll[i];
        }
    }

    int size() {
      return mSize;
    }

    T &operator[](int index) {
        Panic(index >= mSize,
            ArrayIndexOutOfBoundsException, "out of array");
        T &v = elements[index];
        return v;
    }

    sp<_ListIterator<T>> getIterator() {
        return AutoClone(new _ListIterator<T>(this));
    }

    ~_List() {
        if (elements != nullptr) {
            delete[] elements;
            elements = nullptr;
        }
    }

private:
    int mSize;
    T *elements;
};

//----------------- ListIterator ---------------------
DECLARE_TEMPLATE_CLASS(ListIterator, T) {
public:
    explicit _ListIterator(_List<T> * list):_ListIterator(AutoClone(list)) {
    }

    explicit _ListIterator(List<T> list) {
        mList = list;
        index = 0;
    }

    T getValue() {
        Panic(index == mList->mSize,
            ArrayIndexOutOfBoundsException, "no data");
        return mList[index];
    }

    bool hasValue() {
        return index < mList->mSize;
    }

    bool next() {
        if (index == mList->mSize) {
            return false;
        }

        index++;
        return true;
    }

    bool remove() {
        Trigger(MethodNotSupportException,"cannot remove");
        return true;
    }

    void insert(T value) {
        Trigger(MethodNotSupportException,"cannot insert");
    }

    T getItem() {
        return getValue();
    }

private:
    List<T> mList;
    int index;
};


} // namespace obotcha
#endif

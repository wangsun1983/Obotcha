#ifndef __OBOTCHA_LIST_HPP__
#define __OBOTCHA_LIST_HPP__

#include "Object.hpp"
#include "ArrayIndexOutOfBoundsException.hpp"
#include "MethodNotSupportException.hpp"

namespace obotcha {

template <typename T> class _ListIterator;

//----------------- List ---------------------
DECLARE_TEMPLATE_CLASS(List, T) {
public:
    friend class _ListIterator<T>;

    explicit _List(size_t length):mSize(length),
                               elements(new T[length]) {
    }

    _List(T * data, size_t nums):mSize(nums),
                              elements(new T[nums]) {
        for (size_t i = 0; i < nums; i++) {
            elements[i] = data[i];
        }
    }

    explicit _List(sp<_List<T>> ll):mSize(ll->size()) {
        elements = new T[mSize];
        for (size_t i = 0; i < mSize; i++) {
            elements[i] = ll[i];
        }
    }

    size_t size() const {
      return mSize;
    }

    T &operator[](size_t index) {
        Panic(index >= mSize,
            ArrayIndexOutOfBoundsException, "out of array")
        T &v = elements[index];
        return v;
    }

    sp<_ListIterator<T>> getIterator() {
        return AutoClone(new _ListIterator<T>(this));
    }

    ~_List() override {
        if (elements != nullptr) {
            delete[] elements;
            elements = nullptr;
        }
    }

private:
    size_t mSize;
    T *elements;
};

//----------------- ListIterator ---------------------
DECLARE_TEMPLATE_CLASS(ListIterator, T) {
public:
    explicit _ListIterator(_List<T> * list):_ListIterator(AutoClone(list)) {
    }

    explicit _ListIterator(List<T> list):mList(list) {
    }

    T getValue() {
        Panic(index == mList->mSize,
            ArrayIndexOutOfBoundsException, "no data")
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
        mList[index] = nullptr;
        return true;
    }

    void insert([[maybe_unused]] T value) const {
        Trigger(MethodNotSupportException,"cannot insert")
    }

    T getItem() {
        return getValue();
    }

private:
    List<T> mList;
    size_t index = 0;
};


} // namespace obotcha
#endif

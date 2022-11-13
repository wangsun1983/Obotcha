#ifndef __OBOTCHA_STACK_HPP__
#define __OBOTCHA_STACK_HPP__

#include <vector>
#include <stack>

#include "Object.hpp"
#include "ArrayIndexOutOfBoundsException.hpp"
#include "ContainerValue.hpp"

namespace obotcha {

template <typename T> class _StackIterator;

DECLARE_TEMPLATE_CLASS(Stack, T) {
public:
    friend class _StackIterator<T>;

    _Stack() {}

    void push(T val) { element.push_back(val); }

    T pop() {
        if (element.size() == 0) {
            return ContainerValue<T>(nullptr).get();
        }

        T result = element.back();
        element.pop_back();
        return result;
    }

    T top() {
        if (element.size() == 0) {
            return ContainerValue<T>(nullptr).get();
        }

        T result = element.back();
        return result;    
    }

    inline int size() { return element.size(); }

    sp<_StackIterator<T>> getIterator() { return new _StackIterator<T>(this); }

private:
    std::vector<T> element;
    typename std::vector<T>::iterator begin() { return element.begin(); }
    typename std::vector<T>::iterator end() { return element.end(); }
};

DECLARE_TEMPLATE_CLASS(StackIterator, T) {
public:
    _StackIterator(_Stack<T> * list) {
        mStack.set_pointer(list);
        iterator = list->begin();
    }

    _StackIterator(Stack<T> list) {
        mStack = list;
        iterator = mStack->begin();
    }

    T getValue() {
        if (iterator == mStack->end()) {
            Trigger(ArrayIndexOutOfBoundsException, "iterator error");
        }

        return *iterator;
    }

    bool hasValue() { return iterator != mStack->end(); }

    bool next() {
        if (iterator == mStack->end()) {
            return false;
        }
        iterator++;
        return (iterator != mStack->end());
    }

    bool remove() {
        if (iterator == mStack->end()) {
            return false;
        }

        iterator = mStack->element.erase(iterator);
        return true;
    }

    T getItem() {
        if (iterator == mStack->end()) {
            Trigger(ArrayIndexOutOfBoundsException, "iterator error");
        }

        return *iterator;
    }

private:
    Stack<T> mStack;
    typename std::vector<T>::iterator iterator;
};

} // namespace obotcha
#endif
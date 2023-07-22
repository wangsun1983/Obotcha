#ifndef __OBOTCHA_STACK_HPP__
#define __OBOTCHA_STACK_HPP__

#include <vector>

#include "Object.hpp"
#include "ArrayIndexOutOfBoundsException.hpp"
#include "ContainerValue.hpp"
#include "Inspect.hpp"

namespace obotcha {

template <typename T> class _StackIterator;

DECLARE_TEMPLATE_CLASS(Stack, T) {
public:
    friend class _StackIterator<T>;

    _Stack() = default;

    void push(T val) { 
        element.push_back(val); 
    }

    T pop() {
        Inspect(element.size() == 0,ContainerValue<T>(nullptr).get())
        T result = element.back();
        element.pop_back();
        return result;
    }

    T top() {
        Inspect(element.size() == 0,ContainerValue<T>(nullptr).get())
        return element.back();    
    }

    void clear() {
        element.clear();
    }

    inline int size() { 
        return element.size(); 
    }

    sp<_StackIterator<T>> getIterator() { 
        return AutoClone(new _StackIterator<T>(this)); 
    }

private:
    std::vector<T> element;
    typename std::vector<T>::iterator begin() { 
        return element.begin(); 
    }

    typename std::vector<T>::iterator end() { 
        return element.end(); 
    }
};

DECLARE_TEMPLATE_CLASS(StackIterator, T) {
public:
    explicit _StackIterator(_Stack<T> * list) {
        mStack.set_pointer(list);
        iterator = list->begin();
    }

    explicit _StackIterator(Stack<T> list) {
        mStack = list;
        iterator = mStack->begin();
    }

    T getValue() {
        Panic(iterator == mStack->end(),
            ArrayIndexOutOfBoundsException, "iterator error");
        return *iterator;
    }

    bool hasValue() { 
        return iterator != mStack->end(); 
    }

    bool next() {
        Inspect(iterator == mStack->end(),false)
        iterator++;
        return (iterator != mStack->end());
    }

    bool remove() {
        Inspect(iterator == mStack->end(),false)
        iterator = mStack->element.erase(iterator);
        return true;
    }

    T getItem() {
        Panic(iterator == mStack->end(),
            ArrayIndexOutOfBoundsException, "iterator error");
        return *iterator;
    }

private:
    Stack<T> mStack;
    typename std::vector<T>::iterator iterator;
};

} // namespace obotcha
#endif
#ifndef __OBOTCHA_ARRAYLIST_HPP__
#define __OBOTCHA_ARRAYLIST_HPP__

#include <vector>
#include <algorithm>

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "Boolean.hpp"
#include "Double.hpp"
#include "Float.hpp"
#include "Integer.hpp"
#include "Long.hpp"
#include "String.hpp"
#include "MethodNotSupportException.hpp"
#include "ArrayIndexOutOfBoundsException.hpp"

namespace obotcha {
    
template<typename T>
class _ListIterator;

template<typename T>
class _ArrayList;

#define ARRAYLIST_NOT_SUPPORT(V) template<> \
class _ArrayList<V>:virtual public Object{ \
public:    \
    _ArrayList() { \
        throwMethodNotSupportException("ArrayList not support int"); \
    } \
};\

//----------------- ArrayList ---------------------
DECLARE_CLASS(ArrayList,1) {
public:

    friend class _ListIterator<T>;

    _ArrayList(){
        //TODO Nothing
    }

    _ArrayList(int size) {
        elements.reserve(size);
    }

    inline void add(T val) {
        elements.insert(elements.end(),val); 
    }

    inline void add(ArrayList<T> list) {
        if(list == nullptr || list->size() == 0) {
            return;
        }

        elements.insert(elements.end(),list->elements.begin(),list->elements.end());
    }

    inline void clear() {
        elements.clear();
    }

    inline T removeAt(int index) {
        if(index >= elements.capacity() || index < 0) {
            String exception = createString("Arraylist remove fail")
                            ->append("capacity is",
                                    createString(elements.capacity()),
                                    "index is ",
                                    createString(index));

            throwArrayIndexOutOfBoundsException(exception);
        }

        T val = elements.at(index);
        elements.erase(elements.begin() + index);
        return val;
    }

    inline int remove(T val) {
        typename std::vector<T>::iterator result = find(elements.begin( ), elements.end( ),val);
        if(result != elements.end()) {
            elements.erase(result);
            return result - elements.begin();
        }

        return -1;
    }

    inline int indexOf(T val) {
        typename std::vector<T>::iterator result = find( elements.begin( ), elements.end( ),val);
        if(result == elements.end()) {
            return -1;
        }

        return(result - elements.begin());
    }

    inline int set(int index,T val) {
        if(index >= elements.capacity() || index < 0) {
            String exception = createString("Arraylist set fail")
                            ->append("capacity is",
                                    createString(elements.capacity()),
                                    "index is ",
                                    createString(index));

            throwArrayIndexOutOfBoundsException(exception);
        }

        elements[index] = val;
        return 0;
    }

    inline T get(int index) {
         if(index >= elements.capacity() || index < 0) {
            String exception = createString("Arraylist get fail")
                            ->append("capacity is",
                                    createString(elements.capacity()),
                                    "index is ",
                                    createString(index));

            throwArrayIndexOutOfBoundsException(exception);
        }

        return elements[index];
    }

    inline int insert(int index,T val) {
        if(index > elements.capacity() || index < 0) {
            String exception = createString("Arraylist insert fail")
                            ->append("capacity is",
                                    createString(elements.capacity()),
                                    "index is ",
                                    createString(index));

            throwArrayIndexOutOfBoundsException(exception);
        }


        elements.insert(elements.begin() + index,val);
        return 0;
    }

    inline int insert(int index,ArrayList<T> list) {
        if(index > elements.capacity() || index < 0) {
            String exception = createString("Arraylist insert fail")
                            ->append("capacity is",
                                    createString(elements.capacity()),
                                    "index is ",
                                    createString(index));

            throwArrayIndexOutOfBoundsException(exception);
        }

        if(list != nullptr) {
            elements.insert(elements.begin() + index,list->begin(),list->end());
        }
        return 0;
    }

    inline int insert(int index,ArrayList<T> list,int length) {
        if(index > elements.capacity() || length <= 0 || index < 0) {
            String exception = createString("Arraylist insert fail")
                            ->append("capacity is",
                                    createString(elements.capacity()),
                                    "index is ",
                                    createString(index));

            throwArrayIndexOutOfBoundsException(exception);
        }

        if(list != nullptr) {
            int size = list->elements.capacity(); 
            size = length > size?size:length;

            elements.insert(elements.begin() + index,list->begin(),list->begin() + size);
        }
        return 0;
    }

    inline void insertFirst(T val) {
        elements.insert(elements.begin(),val); 
    }


    inline void insertFirst(ArrayList<T> list) {
        if(list == nullptr || list->size() == 0) {
            return;
        }

        elements.insert(elements.begin(),list->elements.begin(),list->elements.end());
    }
    
    inline void insertLast(T v) {
        elements.insert(elements.end(),v);
    }

    inline void insertLast(ArrayList<T> list) {
        if(list == nullptr || list->size() == 0) {
            return;
        }

        elements.insert(elements.end(),list->begin(),list->end());
    }

    inline int size() {
        return elements.size();
    }

    inline int capacity() {
        return elements.capacity();
    }

    sp<_ListIterator<T>> getIterator() {
        return new _ListIterator<T>(this);
    }

private:
    std::vector<T> elements;

    typename std::vector<T>::iterator begin() {
        return elements.begin();
    }

    typename std::vector<T>::iterator end() {
        return elements.end();
    }
};

//----------------- ArrayListIterator ---------------------
DECLARE_CLASS(ListIterator,1) {
public:
    _ListIterator(_ArrayList<T> *list) {
        mList.set_pointer(list);
        //list->incStrong(0);
        iterator = list->begin();
    }

    _ListIterator(ArrayList<T> list) {
        mList = list;
        iterator = mList->begin();
    }

    T getValue() {
        //return iterator->second;
        if(iterator == mList->end()) {
            //return nullptr;
            throwArrayIndexOutOfBoundsException("iterator error");
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

    bool remove() {
        if(iterator == mList->end()) {
            return false;
        }

        iterator = mList->elements.erase(iterator);
        return true;
    }
    
private:
    ArrayList<T> mList;    
    typename std::vector<T>::iterator iterator;
};

/*
ARRAYLIST_NOT_SUPPORT(bool);
ARRAYLIST_NOT_SUPPORT(byte);
ARRAYLIST_NOT_SUPPORT(double);
ARRAYLIST_NOT_SUPPORT(float);
ARRAYLIST_NOT_SUPPORT(int);
ARRAYLIST_NOT_SUPPORT(long);
ARRAYLIST_NOT_SUPPORT(std::uint8_t);
ARRAYLIST_NOT_SUPPORT(std::uint16_t);
ARRAYLIST_NOT_SUPPORT(std::uint32_t);
ARRAYLIST_NOT_SUPPORT(std::uint64_t);
*/

}
#endif

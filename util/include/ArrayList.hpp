#ifndef __ARRAYLIST_HPP__
#define __ARRAYLIST_HPP__

#include <vector>
#include <algorithm>

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "Boolean.hpp"
#include "Double.hpp"
#include "Float.hpp"
#include "Integer.hpp"

#include "Collection.hpp"

using namespace std;

#define arraylist_iterator(X) typename vector<sp<X>>::iterator

DECLARE_CLASS(ArrayList,1) {
public:
    inline void add(T val) {
        elements.insert(elements.end(),val); 
    }

    inline void add(ArrayList<T> list);

    inline void add(int val) {
        Integer v = createInteger(val);
        add(v);
    }

    inline void add(bool val) {
        Boolean v = createBoolean(val);
        add(v);
    }

    inline void add(double val) {
        Double v = createDouble(val);
        add(v);
    }

    inline void add(float val) {
        Float v = createFloat(val);
        add(v);
    }

    inline void clear() {
        elements.clear();
    }

    inline T remove(int index) {
        T val = elements.at(index);
        elements.erase(elements.begin() + index);
        return val;
    }

    inline int remove(T val) {
        typename vector<T>::iterator result = find(elements.begin( ), elements.end( ),val);
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
        elements[index] = val;
    }

    inline T get(int index) {
        return elements[index];
    }

    inline void insert(int index,T val) {
        elements.insert(elements.begin() + index,val);
    }

    inline void insert(int index,ArrayList<T> list);

    inline void insert(int index,ArrayList<T> list,int length);

    inline void insertFirst(T val) {
        elements.insert(elements.begin(),val); 
    }

    inline void insertFirst(ArrayList<T> list);

    inline void insertFirst(int val) {
        Integer v = createInteger(val);
        elements.insert(elements.begin(),v);
    }

    inline void insertFirst(bool val) {
        Boolean v = createInteger(val);
        elements.insert(elements.begin(),v);
    }

    inline void insertFirst(double val) {
        Double v = createDouble(val);
        elements.insert(elements.begin(),v);
    }

    inline void insertFirst(float val) {
        Float v = createFloat(val);
        elements.insert(elements.begin(),v);
    }

    inline void insertLast(T v) {
        elements.insert(elements.end(),v);
    }

    inline void insertLast(ArrayList<T> list);

    inline void insertLast(int val) {
        Integer v = createInteger(val);
        elements.insert(elements.end(),v);
    }

    inline void insertLast(bool val) {
        Boolean v = createBoolean(val);
        elements.insert(elements.end(),v);
    }

    inline void insertLast(double val) {
        Double v = createDouble(val);
        elements.insert(elements.end(),v);
    }

    inline void insertLast(float val) {
        Float v = createFloat(val);
        elements.insert(elements.end(),v);
    }

    inline int size() {
        return elements.size();
    }

    inline container_iterator(T) begin() {
        return elements.begin();
    }

    inline container_iterator(T) end() {
        return elements.end();
    }

private:
    std::vector<T> elements;
};

template<typename T>
void _ArrayList<T>::insert(int index,ArrayList<T> list){
    elements.insert(elements.begin() + index,list.begin(),list.end());
}

template<typename T>
void _ArrayList<T>::insert(int index,ArrayList<T> list,int length) {
    elements.insert(elements.begin() + index,list.begin(),list.begin() + length);
}

template<typename T>
void _ArrayList<T>::add(ArrayList<T> list) {
    elements.insert(elements.end(),list->elements.begin(),list->elements.end());
}

template<typename T>
void _ArrayList<T>::insertFirst(ArrayList<T> list) {
    elements.insert(elements.begin(),list->elements.begin(),list->elements.end());
}

template<typename T>
void _ArrayList<T>::insertLast(ArrayList<T> list) {
    elements.insert(elements.end(),list->begin(),list->end());
}

#endif
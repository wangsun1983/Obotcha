#ifndef __OBOTCHA_ARRAYLIST_HPP__
#define __OBOTCHA_ARRAYLIST_HPP__

#include <vector>
#include <algorithm>
#include <functional>

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "ArrayIndexOutOfBoundsException.hpp"

namespace obotcha {
    
template<typename T>
class _ListIterator;

//----------------- ArrayList ---------------------
DECLARE_CLASS(ArrayList,1) {
public:

    friend class _ListIterator<T>;

    _ArrayList(){
        //TODO Nothing
    }

    _ArrayList(sp<_ArrayList> l) {
        elements.push_back(l->elements);
    }

    _ArrayList(int size) {
        elements.reserve(size);
    }

    inline void add(const T val) {
        elements.push_back(val);
    }

    inline void add(const ArrayList<T> &list) {
        elements.insert(elements.end(),list->elements.begin(),list->elements.end());
    }

    inline void clear() {
        elements.clear();
    }

    inline T removeAt(int index) {
        T val = elements.at(index);
        elements.erase(elements.begin() + index);
        return val;
    }

    inline int remove(const T &val) {
        typename std::vector<T>::iterator result = find(elements.begin( ), elements.end( ),val);
        if(result != elements.end()) {
            elements.erase(result);
            return result - elements.begin();
        }

        return -1;
    }

    //add foreach lambda
    using foreachCallback = std::function<int(T &)>;
    inline void foreach(foreachCallback callback) {
        for (T &value:elements) {
            if(callback(value) < 0) {
                break;
            }
        }
    }

    inline int indexOf(const T &val) {
        typename std::vector<T>::iterator result = find( elements.begin( ), elements.end( ),val);
        if(result == elements.end()) {
            return -1;
        }

        return(result - elements.begin());
    }

    inline int set(int index,const T val) {
        elements[index] = val;
        return 0;
    }

    inline T get(int index) {
        return elements[index];
    }

    inline int insert(int index,const T val) {
        elements.insert(elements.begin() + index,val);
        return 0;
    }

    inline int insert(int index,const ArrayList<T> &list) {
        elements.insert(elements.begin() + index,list->begin(),list->end());
        return 0;
    }

    inline int insert(int index,const ArrayList<T> &list,int length) {
        elements.insert(elements.begin() + index,list->begin(),list->begin() + length);
        return 0;
    }

    inline void insertFirst(const T val) {
        elements.emplace(elements.begin(),val); 
    }


    inline void insertFirst(const ArrayList<T> &list) {
        elements.insert(elements.begin(),list->elements.begin(),list->elements.end());
    }
    
    inline void insertLast(const T v) {
        elements.emplace(elements.end(),v);
    }

    inline void insertLast(const ArrayList<T> &list) {
        elements.insert(elements.end(),list->begin(),list->end());
    }

    inline int size() {
        return elements.size();
    }

    inline int capacity() {
        return elements.capacity();
    }

    sp<_ListIterator<T>> getIterator() {
        return AutoClone(new _ListIterator<T>(this));
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
        iterator = list->begin();
    }

    _ListIterator(ArrayList<T> list) {
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

}
#endif

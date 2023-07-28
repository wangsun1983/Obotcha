/**
 * @file ArrayList.hpp
 * @brief Resizable-array
 * @details none
 * @mainpage none
 * @author sunli.wang
 * @email wang_sun_1983@yahoo.co.jp
 * @version 0.0.1
 * @date 2019-07-12
 * @license none
 */

#ifndef __OBOTCHA_ARRAYLIST_HPP__
#define __OBOTCHA_ARRAYLIST_HPP__

#include <algorithm>
#include <functional>
#include <vector>

#include "ArrayIndexOutOfBoundsException.hpp"
#include "Object.hpp"
#include "String.hpp"

namespace obotcha {

template <typename T> class _ArrayListIterator;

#define DUMMY_REFLECT_ARRAY_FUNCTION(X)                                        \
    template <> class __reflectArrayListItemFunc<X> {                          \
      public:                                                                  \
        __reflectArrayListItemFunc(_ArrayList<X> *p) {}                        \
        sp<_Object> create(std::string name) { return nullptr; }               \
        sp<_Object> get(std::string name, int index) { return nullptr; }       \
        void add(std::string name, sp<_Object> data) {}                        \
    };

template <typename D> class __reflectArrayListItemFunc {
  public:
    explicit __reflectArrayListItemFunc(_ArrayList<D> *p):ptr(p) {
    }

    sp<_Object> create(std::string name) {
        D value;
        AutoCreator<D, D::isReflect()> keyCreator;
        return keyCreator.get();
    }

    sp<_Object> get(std::string name, int index) {
        return ptr->elements[index];
    }

    void add(std::string name, sp<_Object> data) {
        ptr->elements.push_back(Cast<D>(data));
    }

  private:
    _ArrayList<D> *ptr;
};

DUMMY_REFLECT_ARRAY_FUNCTION(int)
DUMMY_REFLECT_ARRAY_FUNCTION(bool)
DUMMY_REFLECT_ARRAY_FUNCTION(double)
DUMMY_REFLECT_ARRAY_FUNCTION(float)
DUMMY_REFLECT_ARRAY_FUNCTION(long int)
DUMMY_REFLECT_ARRAY_FUNCTION(uint8_t)
DUMMY_REFLECT_ARRAY_FUNCTION(uint16_t)
DUMMY_REFLECT_ARRAY_FUNCTION(uint32_t)
DUMMY_REFLECT_ARRAY_FUNCTION(uint64_t)
DUMMY_REFLECT_ARRAY_FUNCTION(std::string)

//----------------- ArrayList ---------------------
DECLARE_TEMPLATE_CLASS(ArrayList, T)
{
public:
    friend class __reflectArrayListItemFunc<T>;
    friend class _ArrayListIterator<T>;

    _ArrayList() = default;

    explicit _ArrayList(sp<_ArrayList<T>> l) : elements(l->elements) {}

    explicit _ArrayList(int size) {
        elements.reserve(size);
    }

    inline void add(const T val) {
        elements.push_back(val);
    }

    inline void add(sp<_ArrayList<T>> list) {
        elements.insert(elements.end(), list->elements.begin(),
                        list->elements.end());
    }

    inline void clear() {
        elements.clear();
    }

    inline T removeAt(int index) {
        if (index < 0 || index >= elements.size() || elements.size() == 0) {
            Trigger(ArrayIndexOutOfBoundsException, "incorrect index[%d]",index)
        }

        T val = elements.at(index);
        elements.erase(elements.begin() + index);
        return val;
    }

    inline bool contains(T t) {
        for (T &value : elements) {
            if(value->equals(t)) {
                return true;
            }
        }

        return false;
    }

    inline int remove(const T &val) {
        auto result = find(elements.begin(), elements.end(), val);
        if (result != elements.end()) {
            elements.erase(result);
            return result - elements.begin();
        }

        return -1;
    }

    inline int removeAll(const sp<_ArrayList<T>> &val) {
        int valsize = val->size();
        int count = 0;
        for(int i = 0; i < valsize; i++) {
            count += (remove(val->get(i)) == -1)?0:1;
        }
        
        return count;
    }

    inline int indexOf(const T &val) {
        auto result = find(elements.begin(), elements.end(), val);
        return (result == elements.end())? -1 : (result - elements.begin());
    }

    inline int set(int index, const T val) {
        Panic(index >= elements.size(),
                ArrayIndexOutOfBoundsException, "incorrect index")
        elements[index] = val;
        return 0;
    }

    inline T get(int index) {
        Panic(index < 0 || index >= elements.size(),ArrayIndexOutOfBoundsException, 
                "incorrect index,index is %d,size is %ld",index,elements.size())
        return elements[index];
    }

    inline int insert(int index, const T val) {
        Panic(index < 0 || index > elements.size(),ArrayIndexOutOfBoundsException, 
                "incorrect index")
        elements.emplace(elements.begin() + index, val);
        return 0;
    }

    inline int insert(int index, const ArrayList<T> &list) {
        Panic(index < 0 || index > elements.size(),ArrayIndexOutOfBoundsException,
            "incorrect index")
        
        elements.insert(elements.begin() + index, list->begin(), list->end());
        return 0;
    }

    inline int insert(int index, const ArrayList<T> &list, int length) {
        Panic(index < 0 || index > elements.size() || length > list->size(),
                ArrayIndexOutOfBoundsException, "incorrect index")

        elements.insert(elements.begin() + index, list->begin(),
                        list->begin() + length);
        return 0;
    }

    inline void insertFirst(const T val) {
        elements.emplace(elements.begin(), val);
    }

    inline void insertFirst(const ArrayList<T> &list) {
        elements.insert(elements.begin(), list->elements.begin(),
                        list->elements.end());
    }

    inline void insertFirst(const ArrayList<T> &list, int length) {
        insert(0, list, length);
    }

    inline void insertLast(const T v) { 
        elements.emplace(elements.end(), v); 
    }

    inline void insertLast(const ArrayList<T> &list) {
        elements.insert(elements.end(), list->begin(), list->end());
    }

    inline void insertLast(const ArrayList<T> &list, int length) {
        insert(elements.size(), list, length);
    }

    inline int size() { 
        return elements.size(); 
    }

    inline int capacity() { 
        return elements.capacity(); 
    }

    sp<_ArrayListIterator<T>> getIterator() {
        return AutoClone(new _ArrayListIterator<T>(this));
    }

    inline int __getContainerSize(const std::string &name) { 
        return elements.size(); 
    }

    inline sp<_Object> __createListItemObject(const std::string &name) {
        return __reflectArrayListItemFunc<T>(this).create(name);
    }

    inline sp<_Object> __getListItemObject(const std::string &name, int index) {
        return __reflectArrayListItemFunc<T>(this).get(name, index);
    }

    inline void __addListItemObject(const std::string &name, sp<_Object> data) {
        __reflectArrayListItemFunc<T>(this).add(name, data);
    }

    inline sp<_String> __ReflectClassName() {
        return createString("_ArrayList");
    }

    static const int __isReflected = 1;

private:
    std::vector<T> elements;

    typename std::vector<T>::iterator begin() { return elements.begin(); }

    typename std::vector<T>::iterator end() { return elements.end(); }
};

//----------------- ArrayArrayListIterator ---------------------
DECLARE_TEMPLATE_CLASS(ArrayListIterator, T) {
public:
    explicit _ArrayListIterator(_ArrayList<T> * list):_ArrayListIterator(AutoClone(list)) {
    }

    explicit _ArrayListIterator(ArrayList<T> list) {
        mList = list;
        iterator = list->begin();
    }

    T getValue() {
        Panic(iterator == mList->end(),
            ArrayIndexOutOfBoundsException, "no data")
        return *iterator;
    }

    bool hasValue() {
        return iterator != mList->end();
    }

    bool next() {
        if (iterator != mList->end()) {
            iterator++;
        }

        return iterator != mList->end();
    }

    bool remove() {
        Inspect(iterator == mList->end(),false)
        iterator = mList->elements.erase(iterator);
        return true;
    }

    void insert(T value) {
        iterator = mList->elements.insert(iterator, value);
    }

    T getItem() {
        return getValue();
    }

private:
    ArrayList<T> mList;
    typename std::vector<T>::iterator iterator;
};

} // namespace obotcha
#endif

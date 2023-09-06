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
        sp<_Object> create([[maybe_unused]]const std::string & name) { return nullptr; }               \
        sp<_Object> get([[maybe_unused]]const std::string &name, size_t index) { return nullptr; }       \
        void add([[maybe_unused]]const std::string &name, sp<_Object> data) {}                        \
    };

template <typename D> class __reflectArrayListItemFunc {
  public:
    explicit __reflectArrayListItemFunc(_ArrayList<D> *p):ptr(p) {
    }

    sp<_Object> create([[maybe_unused]]const std::string &name) {
        D value;
        AutoCreator<D, D::isReflect()> keyCreator;
        return keyCreator.get();
    }

    sp<_Object> get([[maybe_unused]]const std::string &name, size_t index) {
        return ptr->elements[index];
    }

    void add([[maybe_unused]]const std::string &name, sp<_Object> data) {
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

    explicit _ArrayList(sp<_ArrayList<T>> &l) : elements(l->elements) {}

    explicit _ArrayList(size_t size) {
        elements.reserve(size);
    }

    inline void add(const T val) {
        elements.push_back(val);
    }

    inline void add(sp<_ArrayList<T>> &list) {
        elements.insert(elements.end(), list->elements.begin(),
                        list->elements.end());
    }

    inline void clear() {
        elements.clear();
    }

    inline T removeAt(size_t index) {
        Panic (index >= elements.size(),
               ArrayIndexOutOfBoundsException, "incorrect index[%d]",index)

        T val = elements.at(index);
        elements.erase(elements.begin() + index);
        return val;
    }

    inline bool contains(T t) {
        return indexOf(t) != -1;
    }

    inline size_t remove(const T &val) {
        if (auto result = find(elements.begin(), elements.end(), val);
            result != elements.end()) {
            elements.erase(result);
            return result - elements.begin();
        }
        return -1;
    }

    inline size_t removeAll(const sp<_ArrayList<T>> &val) {
        size_t valsize = val->size();
        size_t count = 0;
        for(size_t i = 0; i < valsize; i++) {
            count += (remove(val->get(i)) == -1)?0:1;
        }
        
        return count;
    }

    inline size_t indexOf(const T &val) {
        auto result = find(elements.begin(), elements.end(), val);
        return (result == elements.end())? -1 : (result - elements.begin());
    }

    inline int set(size_t index, const T val) {
        Panic(index >= elements.size(),
                ArrayIndexOutOfBoundsException, "incorrect index")
        elements[index] = val;
        return 0;
    }

    inline T get(size_t index) {
        Panic(index >= elements.size(),ArrayIndexOutOfBoundsException, 
                "incorrect index,index is %d,size is %ld",index,elements.size())
        return elements[index];
    }

    inline int insert(size_t index, const T val) {
        Panic(index > elements.size(),ArrayIndexOutOfBoundsException,"incorrect index")
        elements.emplace(elements.begin() + index, val);
        return 0;
    }

    inline int insert(size_t index, const ArrayList<T> &list) {
        Panic(index > elements.size(),ArrayIndexOutOfBoundsException,
            "incorrect index")
        
        elements.insert(elements.begin() + index, list->begin(), list->end());
        return 0;
    }

    inline int insert(size_t index, const ArrayList<T> &list, size_t length) {
        Panic(index > elements.size() || length > list->size(),
                ArrayIndexOutOfBoundsException, "incorrect length")

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

    inline void insertFirst(const ArrayList<T> &list, size_t length) {
        insert(0, list, length);
    }

    inline void insertLast(const T v) { 
        elements.emplace(elements.end(), v); 
    }

    inline void insertLast(const ArrayList<T> &list) {
        elements.insert(elements.end(), list->begin(), list->end());
    }

    inline void insertLast(const ArrayList<T> &list, size_t length) {
        insert(elements.size(), list, length);
    }

    inline size_t size() const { 
        return elements.size(); 
    }

    inline size_t capacity() const { 
        return elements.capacity(); 
    }

    sp<_ArrayListIterator<T>> getIterator() {
        return AutoClone(new _ArrayListIterator<T>(this));
    }

    inline size_t __getContainerSize(const std::string &name) override { 
        return elements.size(); 
    }

    inline sp<_Object> __createListItemObject(const std::string &name) override {
        return __reflectArrayListItemFunc<T>(this).create(name);
    }

    inline sp<_Object> __getListItemObject(const std::string &name, size_t index) override {
        return __reflectArrayListItemFunc<T>(this).get(name, index);
    }

    inline void __addListItemObject(const std::string &name, sp<_Object> data) override {
        __reflectArrayListItemFunc<T>(this).add(name, data);
    }

    inline sp<_String> __ReflectClassName() override {
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

    explicit _ArrayListIterator(ArrayList<T> list):mList(list),iterator(list->begin()) {        
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

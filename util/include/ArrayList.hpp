#ifndef __OBOTCHA_ARRAYLIST_HPP__
#define __OBOTCHA_ARRAYLIST_HPP__

#include <algorithm>
#include <functional>
#include <vector>

#include "ArrayIndexOutOfBoundsException.hpp"
#include "Object.hpp"
#include "StrongPointer.hpp"

namespace obotcha {

template <typename T> class _ListIterator;

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
    __reflectArrayListItemFunc(_ArrayList<D> *p) { ptr = p; }

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
DECLARE_TEMPLATE_CLASS(ArrayList, 1) {
public:
    friend class __reflectArrayListItemFunc<T>;
    friend class _ListIterator<T>;

    _ArrayList() {
        // TODO Nothing
    }

    _ArrayList(sp<_ArrayList<T>> l) : elements(l->elements) {}

    _ArrayList(int size) { elements.reserve(size); }

    inline void add(const T val) { elements.push_back(val); }

    inline void add(sp<_ArrayList<T>> list) {
        elements.insert(elements.end(), list->elements.begin(),
                        list->elements.end());
    }

    inline void clear() { elements.clear(); }

    inline T removeAt(int index) {
        if (index < 0 || index >= elements.size() || elements.size() == 0) {
            Trigger(ArrayIndexOutOfBoundsException, "incorrect index");
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
        typename std::vector<T>::iterator result =
            find(elements.begin(), elements.end(), val);
        if (result != elements.end()) {
            elements.erase(result);
            return result - elements.begin();
        }

        return -1;
    }

    // add foreach lambda
    using foreachCallback = std::function<int(T &)>;
    inline void foreach (foreachCallback callback) {
        for (T &value : elements) {
            if (callback(value) == Global::Break) {
                break;
            }
        }
    }

    inline int indexOf(const T &val) {
        typename std::vector<T>::iterator result =
            find(elements.begin(), elements.end(), val);
        if (result == elements.end()) {
            return -1;
        }

        return (result - elements.begin());
    }

    inline int set(int index, const T val) {
        if (index >= elements.size()) {
            Trigger(ArrayIndexOutOfBoundsException, "incorrect index");
        }
        elements[index] = val;
        return 0;
    }

    inline T get(int index) {
        if (index < 0 || index >= elements.size()) {
            Trigger(ArrayIndexOutOfBoundsException, "incorrect index");
        }
        return elements[index];
    }

    inline int insert(int index, const T val) {
        if (index < 0 || index > elements.size()) {
            Trigger(ArrayIndexOutOfBoundsException, "incorrect index");
        }
        elements.insert(elements.begin() + index, val);
        return 0;
    }

    // insert before index....
    inline int insert(int index, const ArrayList<T> &list) {
        if (index < 0 || index > elements.size()) {
            Trigger(ArrayIndexOutOfBoundsException, "incorrect index");
        }
        elements.insert(elements.begin() + index, list->begin(), list->end());
        return 0;
    }

    // insert before index....
    inline int insert(int index, const ArrayList<T> &list, int length) {
        if (index < 0 || index > elements.size() || length > list->size()) {
            Trigger(ArrayIndexOutOfBoundsException, "incorrect index");
        }
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

    inline void insertLast(const T v) { elements.emplace(elements.end(), v); }

    inline void insertLast(const ArrayList<T> &list) {
        elements.insert(elements.end(), list->begin(), list->end());
    }

    inline void insertLast(const ArrayList<T> &list, int length) {
        insert(elements.size(), list, length);
    }

    inline int size() { return elements.size(); }

    inline int capacity() { return elements.capacity(); }

    sp<_ListIterator<T>> getIterator() {
        return AutoClone(new _ListIterator<T>(this));
    }

    inline int __getContainerSize(std::string name) { return elements.size(); }

    inline sp<_Object> __createListItemObject(std::string name) {
        return __reflectArrayListItemFunc<T>(this).create(name);
    }

    inline sp<_Object> __getListItemObject(std::string name, int index) {
        return __reflectArrayListItemFunc<T>(this).get(name, index);
    }

    inline void __addListItemObject(std::string name, sp<_Object> data) {
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

//----------------- ArrayListIterator ---------------------
DECLARE_TEMPLATE_CLASS(ListIterator, 1) {
public:
    _ListIterator(_ArrayList<T> * list) {
        mList.set_pointer(list);
        iterator = list->begin();
    }

    _ListIterator(ArrayList<T> list) {
        mList = list;
        iterator = mList->begin();
    }

    T getValue() {
        if (iterator == mList->end()) {
            Trigger(ArrayIndexOutOfBoundsException, "no data");
        }
        return *iterator;
    }

    bool hasValue() { return iterator != mList->end(); }

    bool next() {
        if (iterator != mList->end()) {
            iterator++;
        }

        return iterator != mList->end();
    }

    bool remove() {
        if (iterator == mList->end()) {
            return false;
        }

        iterator = mList->elements.erase(iterator);
        return true;
    }

    void insert(T value) { iterator = mList->elements.insert(iterator, value); }

private:
    ArrayList<T> mList;
    typename std::vector<T>::iterator iterator;
};

} // namespace obotcha
#endif

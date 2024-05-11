/**
 * @file HashMap.hpp
 * @brief Hash table based implementation of the std::unordered_map.  This
 *        implementation provides all of the optional map operations, and permits
 *        Object values and the int/uint32_t.... key. 
 * @details none
 * @mainpage none
 * @author sunli.wang
 * @email wang_sun_1983@yahoo.co.jp
 * @version 0.0.1
 * @date 2019-07-12
 * @license none
 * @Notice:Do not support HashMap's value as primitive value(int/long...)
 */

#ifndef __OBOTCHA_HASHMAP_HPP__
#define __OBOTCHA_HASHMAP_HPP__

#include <string>
#include <unordered_map>

#include "Object.hpp"
#include "ArrayList.hpp"
#include "OStdReturnValue.hpp"
#include "HashKey.hpp"
#include "Pair.hpp"
#include "ValueNotFoundException.hpp"

namespace obotcha {

template <typename T, typename U> class _MapIterator;

#define DUMMY_REFLECT_HASHMAP_FUNCTION(X)                                                     \
template <typename E>                                                                         \
class reflectItemFunc<X, E>                                                                   \
{                                                                                             \
public:                                                                                       \
    reflectItemFunc(_HashMap<X, E> *p) {}                                                     \
    sp<_ArrayList<sp<_Pair<sp<_Object>, sp<_Object>>>>>                                       \
    get([[maybe_unused]] const std::string &name) {                                           \
        return nullptr;                                                                       \
    }                                                                                         \
    void add([[maybe_unused]] const std::string &name, sp<_Object> key, sp<_Object> value) {} \
    sp<_Pair<sp<_Object>, sp<_Object>>> create([[maybe_unused]] const std::string &name) {    \
        return nullptr;                                                                       \
    }                                                                                         \
};

//----------------------- HashMap<T,U> -----------------------
DECLARE_TEMPLATE_CLASS(HashMap,T,U) {
  public:
    friend class _MapIterator<T, U>;

    static const int __isReflected = 1;

    void put(const T t, const U &u) { 
        hashmap[t] = u; 
    }

    U get(const T t) {
        if (auto ite = hashmap.find(t);ite != hashmap.end()) {
            return ite->second;
        }

        return nullptr;
    }

    U remove(const T t) {
        auto ite = hashmap.find(t);
        if (ite == hashmap.end()) {
            return nullptr;
        }

        auto result = ite->second;
        hashmap.erase(ite);
        return result;
    }

    bool isEmpty() { 
        return hashmap.size() == 0; 
    }

    void clear() { 
        hashmap.clear(); 
    }

    size_t size() { 
        return hashmap.size(); 
    }

    ArrayList<T> keySet() {
        ArrayList<T> keyset = ArrayList<T>::New();
        for (auto it = hashmap.begin(); it != hashmap.end(); it++) {
            keyset->add(it->first);
        }

        return keyset;
    }

    ArrayList<U> entrySet() {
        ArrayList<U> entrySet = ArrayList<U>::New();
        for (auto it = hashmap.begin(); it != hashmap.end(); it++) {
            entrySet->add(it->second);
        }

        return entrySet;
    }

    U &operator[](const T &k) { 
        return hashmap[k]; 
    }

    sp<_MapIterator<T, U>> getIterator() {
        return AutoClone(new _MapIterator<T, U>(this));
    }

    void append(sp<_HashMap<T, U>> m) {
        hashmap.insert(m->hashmap.begin(),m->hashmap.end());
    }

    inline size_t __getContainerSize(const std::string &name) override { 
        return hashmap.size(); 
    }

    template <typename D, typename E> class reflectItemFunc {
      public:
        explicit reflectItemFunc(_HashMap<D, E> *p):ptr(p) {}

        sp<_ArrayList<sp<_Pair<sp<_Object>, sp<_Object>>>>>
        get([[maybe_unused]]const std::string &name) {
            auto iterator = ptr->hashmap.begin();
            ArrayList<Pair<Object, Object>> values = ArrayList<Pair<Object, Object>>::New();
            while (iterator != ptr->hashmap.end()) {
                values->add(Pair<sp<_Object>, sp<_Object>>::New(iterator->first, iterator->second));
                iterator++;
            }

            return values;
        }

        void add([[maybe_unused]]const std::string &name, 
                sp<_Object> key, sp<_Object> value) {
            ptr->hashmap[Cast<T>(key)] = Cast<U>(value);
        }

        sp<_Pair<sp<_Object>, sp<_Object>>> create([[maybe_unused]]const std::string &name) {
            AutoCreator<D, D::isReflect()> keyCreator;
            AutoCreator<E, E::isReflect()> valueCreator;
            return Pair<Object, Object>::New(keyCreator.get(),valueCreator.get());
        }

      private:
        _HashMap<D, E> *ptr;
    };

    DUMMY_REFLECT_HASHMAP_FUNCTION(int)
    DUMMY_REFLECT_HASHMAP_FUNCTION(bool)
    DUMMY_REFLECT_HASHMAP_FUNCTION(double)
    DUMMY_REFLECT_HASHMAP_FUNCTION(float)
    DUMMY_REFLECT_HASHMAP_FUNCTION(long)
    DUMMY_REFLECT_HASHMAP_FUNCTION(uint8_t)
    DUMMY_REFLECT_HASHMAP_FUNCTION(uint16_t)
    DUMMY_REFLECT_HASHMAP_FUNCTION(uint32_t)
    DUMMY_REFLECT_HASHMAP_FUNCTION(uint64_t)
    DUMMY_REFLECT_HASHMAP_FUNCTION(std::string)

    inline sp<_ArrayList<sp<_Pair<sp<_Object>, sp<_Object>>>>>
    __getMapItemObjects(const std::string &name) override {
        return reflectItemFunc<T, U>(this).get(name);
    }

    inline void __addMapItemObject(const std::string &name, sp<_Object> key,
                                   sp<_Object> value) override {
        return reflectItemFunc<T, U>(this).add(name, key, value);
    }

    inline sp<_Pair<sp<_Object>, sp<_Object>>> __createMapItemObject(const std::string &name) override {
        return reflectItemFunc<T, U>(this).create(name);
    }

    inline sp<_String> __ReflectClassName() override { 
        return String::New("_HashMap"); 
    }

  private:
    std::unordered_map<T, U, HashKey<T>, KeyComapre<T>> hashmap;

    typename std::unordered_map<T, U, HashKey<T>, KeyComapre<T>>::iterator
    begin() {
        return hashmap.begin();
    }

    typename std::unordered_map<T, U, HashKey<T>, KeyComapre<T>>::iterator
    end() {
        return hashmap.end();
    }
};

//----------------- MapIterator ---------------------
DECLARE_TEMPLATE_CLASS(MapIterator, T,U) {
public:
    explicit _MapIterator(_HashMap<T, U> * map):iterator(map->begin()) {
        mHashMap.set_pointer(map);
    }

    explicit _MapIterator(HashMap<T, U> map):iterator(mHashMap->begin()) {
        mHashMap = map;
    }

    T getKey() {
        Panic(iterator == mHashMap->end(),
            ArrayIndexOutOfBoundsException, "no data")
        return iterator->first;
    }

    U getValue() {
        Panic(iterator == mHashMap->end(),
            ArrayIndexOutOfBoundsException, "no data")
        return iterator->second;
    }

    bool hasValue() { 
        return iterator != mHashMap->end(); 
    }

    bool next() {
        if (iterator != mHashMap->end()) {
            iterator++;
        }

        return iterator != mHashMap->end();
    }

    void remove() {
        if (iterator != mHashMap->end()) {
            iterator = mHashMap->hashmap.erase(iterator);
        }
    }

    Pair<T,U> getItem() {
        return Pair<T,U>::New(iterator->first,iterator->second);
    }

private:
    HashMap<T, U> mHashMap;
    typename std::unordered_map<T, U, HashKey<T>, KeyComapre<T>>::iterator
        iterator;
};

} // namespace obotcha
#endif
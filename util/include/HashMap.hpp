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
 */

#ifndef __OBOTCHA_HASHMAP_HPP__
#define __OBOTCHA_HASHMAP_HPP__

#include <algorithm>
#include <string>
#include <unordered_map>

#include "Object.hpp"
#include "ArrayList.hpp"
#include "ValueNotFoundException.hpp"
#include "OStdReturnValue.hpp"
#include "HashKey.hpp"
#include "Pair.hpp"

namespace obotcha {

template <typename T, typename U> class _MapIterator;

#define DUMMY_REFLECT_HASHMAP_FUNCTION(X)                                      \
    template <typename E> class reflectItemFunc<X, E> {                        \
      public:                                                                  \
        reflectItemFunc(_HashMap<X, E> *p) {}                                  \
        sp<_ArrayList<sp<_Pair<sp<_Object>, sp<_Object>>>>>            \
        get(std::string name) {                                                \
            return nullptr;                                                    \
        }                                                                      \
        void add(std::string name, sp<_Object> key, sp<_Object> value) {}      \
        sp<_Pair<sp<_Object>, sp<_Object>>> create(std::string name) { \
            return nullptr;                                                    \
        }                                                                      \
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
        auto ite = hashmap.find(t);
        if (ite != hashmap.end()) {
            return ite->second;
        }

        __NotFoundValue<U> v;
        return v.getValue();
    }

    //wangsl
    DefRet(bool,U) getPrimitive(T t) {
        auto ite = hashmap.find(t);
        if (ite != hashmap.end()) {
            return MakeRet(true,ite->second);
        }
        return MakeRet(false,std::ignore);
    }
    //wangsl

    U remove(const T t) {
        auto ite = hashmap.find(t);
        if (ite == hashmap.end()) {
            __NotFoundValue<U> v;
            return v.getValue();;
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

    int size() { 
        return hashmap.size(); 
    }

    ArrayList<T> keySet() {
        ArrayList<T> keyset = createArrayList<T>();
        for (auto it = hashmap.begin(); it != hashmap.end(); it++) {
            keyset->add(it->first);
        }

        return keyset;
    }

    ArrayList<U> entrySet() {
        ArrayList<U> entrySet = createArrayList<U>();
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

    inline int __getContainerSize(std::string name) { return hashmap.size(); }

    template <typename D, typename E> class reflectItemFunc {
      public:
        reflectItemFunc(_HashMap<D, E> *p) { ptr = p; }

        sp<_ArrayList<sp<_Pair<sp<_Object>, sp<_Object>>>>>
        get(std::string name) {
            auto iterator = ptr->hashmap.begin();
            ArrayList<Pair<Object, Object>> values =
                createArrayList<Pair<Object, Object>>();
            while (iterator != ptr->hashmap.end()) {
                values->add(createPair<sp<_Object>, sp<_Object>>(
                    iterator->first, iterator->second));
                iterator++;
            }

            return values;
        }

        void add(std::string name, sp<_Object> key, sp<_Object> value) {
            ptr->hashmap[Cast<T>(key)] = Cast<U>(value);
        }

        sp<_Pair<sp<_Object>, sp<_Object>>> create(std::string name) {
            AutoCreator<D, D::isReflect()> keyCreator;
            AutoCreator<E, E::isReflect()> valueCreator;
            return createPair<Object, Object>(keyCreator.get(),
                                                      valueCreator.get());
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
    __getMapItemObjects(std::string name) {
        return reflectItemFunc<T, U>(this).get(name);
    }

    inline void __addMapItemObject(std::string name, sp<_Object> key,
                                   sp<_Object> value) {
        return reflectItemFunc<T, U>(this).add(name, key, value);
    }

    inline sp<_Pair<sp<_Object>, sp<_Object>>> __createMapItemObject(
        std::string name) {
        return reflectItemFunc<T, U>(this).create(name);
    }

    inline sp<_String> __ReflectClassName() { return createString("_HashMap"); }

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
    _MapIterator(_HashMap<T, U> * map) {
        mHashMap.set_pointer(map);
        iterator = map->begin();
    }

    _MapIterator(HashMap<T, U> map) {
        mHashMap = map;
        iterator = mHashMap->begin();
    }

    T getKey() {
        Panic(iterator == mHashMap->end(),
            ArrayIndexOutOfBoundsException, "no data");
        return iterator->first;
    }

    U getValue() {
        Panic(iterator == mHashMap->end(),
            ArrayIndexOutOfBoundsException, "no data");
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
        if (iterator == mHashMap->end()) {
            return;
        }

        iterator = mHashMap->hashmap.erase(iterator);
    }

    Pair<T,U> getItem() {
        return createPair<T,U>(iterator->first,iterator->second);
    }

  private:
    HashMap<T, U> mHashMap;
    typename std::unordered_map<T, U, HashKey<T>, KeyComapre<T>>::iterator
        iterator;
};

} // namespace obotcha
#endif
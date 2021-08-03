#ifndef __OBOTCHA_HASHMAP_HPP__
#define __OBOTCHA_HASHMAP_HPP__

#include <algorithm>
#include <unordered_map>
#include <string>

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "NullPointerException.hpp"
#include "ValueNotFoundException.hpp"
#include "HashKey.hpp"
#include "KeyValuePair.hpp"

namespace obotcha {

template<typename T,typename U>
class _MapIterator;

#define DUMMY_REFLECT_HASHMAP_FUNCTION(X) \
template<typename E>\
class reflectItemFunc<X,E>\
{\
    public:\
    reflectItemFunc(_HashMap<X,E> *p) {\
    }\
    sp<_ArrayList<sp<_KeyValuePair<sp<_Object>,sp<_Object>>>>> get(std::string name)\
    {\
        return nullptr;\
    }\
    void add(std::string name,sp<_Object> key,sp<_Object> value) {\
    }\
    sp<_KeyValuePair<sp<_Object>,sp<_Object>>> create(std::string name) {\
        return nullptr;\
    }\
};\

//----------------------- HashMap<T,U> -----------------------
DECLARE_CLASS(HashMap,2) {
public:
    friend class _MapIterator<T,U>;
    
    static const int __isReflected = 1;

    void put(const T &t,const U &u) {
        hashmap[t] = u;
    }

    U get(const T &t) {
        auto ite = hashmap.find(t);
        if(ite != hashmap.end()) {  
            return ite->second;
        }

        __NotFoundValue<U> v;
        return v.getValue();
    }

    void remove(const T &t) {
        auto ite = hashmap.find(t);
        if(ite == hashmap.end()) {   
            return;
        }
        hashmap.erase(ite);
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

    //template<typename V>
    ArrayList<T> keySet() {
        ArrayList<T> keyset = createArrayList<T>();
        for (auto it= hashmap.begin();it != hashmap.end();it++) {
            keyset->add(it->first);
        }

        return keyset;
    }
    
    //template<typename V>
    ArrayList<U> entrySet() {
        ArrayList<U> keyset = createArrayList<U>();
        for (auto it= hashmap.begin();it != hashmap.end();it++) {
            keyset->add(it->second);
        }

        return keyset;
    }

    //add foreach lambda
    using foreachCallback = std::function<int(T,U)>;
    inline void foreach(foreachCallback callback) {
        for (auto it= hashmap.begin();it != hashmap.end();it++) {
            if(callback(it->first,it->second) == Global::Break) {
                break;
            }
        }
    }

    U &operator[](const T &k) {
        return hashmap[k];
    }
    
    sp<_MapIterator<T,U>> getIterator() {
        return AutoClone(new _MapIterator<T,U>(this));
    }

    void merge(sp<_HashMap<T,U>> m) {
        auto iterator = m->getIterator();
        while(iterator->hasValue()) {
            T key = iterator->getKey();
            U value = iterator->getValue();
            hashmap[key] = value;

            iterator->next();
        }
    }

    inline int __getContainerSize(std::string name) {
        return hashmap.size();
    }

    
    template<typename D,typename E>
    class reflectItemFunc {
        public:
        reflectItemFunc(_HashMap<D,E> *p) {
            ptr = p;
        }

        sp<_ArrayList<sp<_KeyValuePair<sp<_Object>,sp<_Object>>>>> get(std::string name)
        {
            auto iterator = ptr->hashmap.begin();
            ArrayList<KeyValuePair<Object,Object>> values = createArrayList<KeyValuePair<Object,Object>>();
            while(iterator != ptr->hashmap.end()) {
                values->add(createKeyValuePair<sp<_Object>,sp<_Object>>(iterator->first,iterator->second));
                iterator++;
            }

            return values;
        }

        void add(std::string name,sp<_Object> key,sp<_Object> value) {
            ptr->hashmap[Cast<T>(key)] = Cast<U>(value);
        }

        sp<_KeyValuePair<sp<_Object>,sp<_Object>>> create(std::string name) {
            AutoCreator<D,D::isReflect()> keyCreator;
            AutoCreator<E,E::isReflect()> valueCreator;
            return createKeyValuePair<Object,Object>(keyCreator.get(),valueCreator.get());
        }

        private:
        _HashMap<D,E> *ptr;
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

    inline sp<_ArrayList<sp<_KeyValuePair<sp<_Object>,sp<_Object>>>>> __getMapItemObjects(std::string name){
       return reflectItemFunc<T,U>(this).get(name);
    }

    inline void __addMapItemObject(std::string name,sp<_Object> key,sp<_Object> value){
        return reflectItemFunc<T,U>(this).add(name,key,value);
    }

    inline sp<_KeyValuePair<sp<_Object>,sp<_Object>>> __createMapItemObject(std::string name){
        return reflectItemFunc<T,U>(this).create(name);
    }

    inline sp<_String> __ReflectClassName(){return createString("_HashMap");}

private:
    std::unordered_map<T,U,KeyHash<T>,KeyComapre<T>> hashmap;

    typename std::unordered_map<T,U,KeyHash<T>,KeyComapre<T>>::iterator begin() {
        return hashmap.begin();
    }

    typename std::unordered_map<T,U,KeyHash<T>,KeyComapre<T>>::iterator end() {
        return hashmap.end();
    }
};

//----------------- MapIterator ---------------------
DECLARE_CLASS(MapIterator,2) {

public:
    _MapIterator(_HashMap<T,U> *map) {
        mHashMap.set_pointer(map);
        iterator = map->begin();
    }

    _MapIterator(HashMap<T,U> map) {
        mHashMap = map;
        iterator = mHashMap->begin();
    }

    T getKey() {
        if(iterator == mHashMap->end()) {
            Trigger(ArrayIndexOutOfBoundsException,"no data");
        }

        return iterator->first;
    }

    U getValue() {
        if(iterator == mHashMap->end()) {
            Trigger(ArrayIndexOutOfBoundsException,"no data");
        }

        return iterator->second;
    }

    bool hasValue() {
        return iterator != mHashMap->end();
    }

    bool next() {
        if(iterator != mHashMap->end()) {
            iterator++;
        }

        return iterator != mHashMap->end();
    }

    void remove() {
        if(iterator ==  mHashMap->end()) {
            return;
        }

        iterator = mHashMap->hashmap.erase(iterator);
    }
    
private:
    HashMap<T,U> mHashMap;    
    typename std::unordered_map<T,U,KeyHash<T>,KeyComapre<T>>::iterator iterator;
};

}
#endif
#ifndef __HASHMAP_HPP__
#define __HASHMAP_HPP__

#include <map>
#include <algorithm>

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "Boolean.hpp"
#include "Double.hpp"
#include "Float.hpp"
#include "Integer.hpp"
#include "Long.hpp"
#include "String.hpp"

#include "Collection.hpp"
#include "ArrayList.hpp"

using namespace std;

namespace obotcha {

template<typename T,typename U>
class _MapIterator;

//----------------------- HashMap<T,U> -----------------------
DECLARE_CLASS(HashMap,2) {
public:
    friend class _MapIterator<T,U>;

    void put(T t,U u) {
        hashmap.insert(std::pair<T, U>(t, u));
    }

    U get(T t) {
        auto value = hashmap.find(t);
        if(value == hashmap.end()) {
            return nullptr;
        }

        return value->second;
    }

    void remove(T t) {
        //hashmap.erase(t);
        typename std::map<T,U>::iterator ite = hashmap.find(t);
        if(ite == hashmap.end()) {
            printf("hashmap can not find \n");
            return;
        }
        hashmap.erase(ite++);
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

    template<typename V>
    ArrayList<V> keySet() {
        ArrayList<V> keyset = createArrayList<V>();
        for (auto it= hashmap.begin();it != hashmap.end();it++) {
            keyset->add(it->first);
        }

        return keyset;
    }
    
    template<typename V>
    ArrayList<V> entrySet() {
        ArrayList<V> keyset = createArrayList<V>();
        for (auto it= hashmap.begin();it != hashmap.end();it++) {
            keyset->add(it->second);
        }

        return keyset;
    }
    
    sp<_MapIterator<T,U>> getIterator() {
        return new _MapIterator<T,U>(this);
    }

private:
    std::map<T,U> hashmap;

    typename std::map<T,U>::iterator begin() {
        return hashmap.begin();
    }

    typename std::map<T,U>::iterator end() {
        return hashmap.end();
    }
};

//----------------------- HashMap<String,U> -----------------------
template<typename U>  
class _HashMap<String,U>:virtual public Object{
public:
    friend class _MapIterator<String,U>;

    void put(String t,U u) {
        std::string str(t->getStdString());
        hashmap.insert(std::pair<std::string, U>(str,u));
    }

    U get(String t) {
        auto value = hashmap.find(t->getStdString());
        if(value == hashmap.end()) {
            return nullptr;
        }

        return value->second;
    }

    void remove(String t) {
        //remember free
        hashmap->remove(t->getStdString());
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

    ArrayList<String> keySet() {
        ArrayList<String> keyset = createArrayList<String>();
        for (auto it= hashmap.begin();it != hashmap.end();it++) {
            keyset->add(createString(it->first));
        }

        return keyset;
    }
    
    template<typename V>
    ArrayList<V> entrySet() {
        ArrayList<V> keyset = createArrayList<V>();
        for (auto it= hashmap.begin();it != hashmap.end();it++) {
            keyset->add(it->second);
        }

        return keyset;
    }

    sp<_MapIterator<String,U>> getIterator() {
        return new _MapIterator<String,U>(this);
    }

private:
    std::map<std::string,U> hashmap;

    typename std::map<std::string,U>::iterator begin() {
        return hashmap.begin();
    }

    typename std::map<std::string,U>::iterator end() {
        return hashmap.end();
    }
};

//----------------------- HashMap<Integer,U> -----------------------
template<typename U>  
class _HashMap<Integer,U>:virtual public Object{
public:
    void put(Integer t,U u) {
        hashmap.insert(std::pair<int, U>(t->toValue(),u));
    }

    U get(Integer t) {
        auto value = hashmap.find(t->toValue());
        if(value == hashmap.end()) {
            return nullptr;
        }

        return value->second;
    }

    void remove(Integer t) {
        hashmap->remove(t->toValue());
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

    ArrayList<Integer> keySet() {
        ArrayList<Integer> keyset = createArrayList<Integer>();
        for (auto it= hashmap.begin();it != hashmap.end();it++) {
            keyset->add(createInteger(it->first));
        }

        return keyset;
    }
    
    template<typename V>
    ArrayList<V> entrySet() {
        ArrayList<V> keyset = createArrayList<V>();
        for (auto it= hashmap.begin();it != hashmap.end();it++) {
            keyset->add(it->second);
        }

        return keyset;
    }

    sp<_MapIterator<String,U>> getIterator() {
        return new _MapIterator<Integer,U>(this);
    }

private:
    std::map<int,U> hashmap;

    typename std::map<int,U>::iterator begin() {
        return hashmap.begin();
    }

    typename std::map<int,U>::iterator end() {
        return hashmap.end();
    }
};

//----------------------- HashMap<Double,U> -----------------------
template<typename U>  
class _HashMap<Double,U>:virtual public Object{
public:
    inline void put(Double t,U u) {
        hashmap.insert(std::pair<double, U>(t->toValue(),u));
    }

    U get(Double t) {
        auto value = hashmap.find(t->toValue());
        if(value == hashmap.end()) {
            return nullptr;
        }

        return value->second;
    }

    void remove(Double t) {
        hashmap->remove(t->toValue());
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

    ArrayList<Double> keySet() {
        ArrayList<Double> keyset = createArrayList<Double>();
        for (auto it= hashmap.begin();it != hashmap.end();it++) {
            keyset->add(createDouble(it->first));
        }

        return keyset;
    }
    
    template<typename V>
    ArrayList<V> entrySet() {
        ArrayList<V> keyset = createArrayList<V>();
        for (auto it= hashmap.begin();it != hashmap.end();it++) {
            keyset->add(it->second);
        }

        return keyset;
    }

private:
    std::map<double,U> hashmap;

    typename std::map<double,U>::iterator begin() {
        return hashmap.begin();
    }

    typename std::map<double,U>::iterator end() {
        return hashmap.end();
    }
};


//----------------------- HashMap<Float,U> -----------------------
template<typename U>  
class _HashMap<Float,U>:virtual public Object{

public:
    inline void put(Float t,U u) {
        hashmap.insert(std::pair<float, U>(t->toValue(),u));
    }

    U get(Float t) {
        auto value = hashmap.find(t->toValue());
        if(value == hashmap.end()) {
            return nullptr;
        }

        return value->second;
    }

    void remove(Float t) {
        hashmap->remove(t->toValue());
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

    ArrayList<Float> keySet() {
        ArrayList<Float> keyset = createArrayList<Float>();
        for (auto it= hashmap.begin();it != hashmap.end();it++) {
            keyset->add(createFloat(it->first));
        }

        return keyset;
    }
    
    template<typename V>
    ArrayList<V> entrySet() {
        ArrayList<V> keyset = createArrayList<V>();
        for (auto it= hashmap.begin();it != hashmap.end();it++) {
            keyset->add(it->second);
        }

        return keyset;
    }

private:
    std::map<float,U> hashmap;

    typename std::map<float,U>::iterator begin() {
        return hashmap.begin();
    }

    typename std::map<float,U>::iterator end() {
        return hashmap.end();
    }
};

//----------------------- HashMap<Boolean,U> -----------------------
template<typename U>  
class _HashMap<Boolean,U>:virtual public Object{
public:
    inline void put(Boolean t,U u) {
        hashmap.insert(std::pair<bool, U>(t->toValue(),u));
    }

    U get(Boolean t) {
        auto value = hashmap.find(t->toValue());
        if(value == hashmap.end()) {
            return nullptr;
        }

        return value->second;
    }

    void remove(Boolean t) {
        hashmap->remove(t->toValue());
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

    ArrayList<Boolean> keySet() {
        ArrayList<Boolean> keyset = createArrayList<Boolean>();
        for (auto it= hashmap.begin();it != hashmap.end();it++) {
            keyset->add(createFloat(it->first));
        }

        return keyset;
    }
    
    template<typename V>
    ArrayList<V> entrySet() {
        ArrayList<V> keyset = createArrayList<V>();
        for (auto it= hashmap.begin();it != hashmap.end();it++) {
            keyset->add(it->second);
        }

        return keyset;
    }

private:
    std::map<bool,U> hashmap;

    typename std::map<bool,U>::iterator begin() {
        return hashmap.begin();
    }

    typename std::map<bool,U>::iterator end() {
        return hashmap.end();
    }

};

//----------------------- HashMap<Long,U> -----------------------
template<typename U>  
class _HashMap<Long,U>:virtual public Object{
public:
    inline void put(Long t,U u) {
        hashmap.insert(std::pair<long, U>(t->toValue(),u));
    }

    U get(Long t) {
        auto value = hashmap.find(t->toValue());
        if(value == hashmap.end()) {
            return nullptr;
        }

        return value->second;
    }

    void remove(Long t) {
        hashmap->remove(t->toValue());
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

    ArrayList<Long> keySet() {
        ArrayList<Long> keyset = createArrayList<Long>();
        for (auto it= hashmap.begin();it != hashmap.end();it++) {
            keyset->add(createFloat(it->first));
        }

        return keyset;
    }
    
    template<typename V>
    ArrayList<V> entrySet() {
        ArrayList<V> keyset = createArrayList<V>();
        for (auto it= hashmap.begin();it != hashmap.end();it++) {
            keyset->add(it->second);
        }

        return keyset;
    }

private:
    std::map<long,U> hashmap;

    typename std::map<long,U>::iterator begin() {
        return hashmap.begin();
    }

    typename std::map<long,U>::iterator end() {
        return hashmap.end();
    }

};


//----------------- MapIterator ---------------------
DECLARE_CLASS(MapIterator,2) {

public:
    _MapIterator(_HashMap<T,U> *map) {
        mHashMap.set_pointer(map);
        //map->incStrong(0);

        iterator = map->begin();
    }

    _MapIterator(HashMap<T,U> map) {
        mHashMap = map;
        iterator = mHashMap->begin();
    }

    T getKey() {
        return iterator->first;
    }

    U getValue() {
        return iterator->second;
    }

    bool hasValue() {
        return iterator != mHashMap->end();
    }

    bool next() {
        iterator++;
        if(iterator ==  mHashMap->end()) {
            return false;
        }

        return true;
    }
    
private:
    HashMap<T,U> mHashMap;    
    typename std::map<T,U>::iterator iterator;
};

//----------------- MapIterator<String,U> ---------------------
template<typename U>  
class _MapIterator<String,U>:virtual public Object{
public:
    _MapIterator(_HashMap<String,U> *map) {
        mHashMap.set_pointer(map);
        //map->incStrong(0);

        iterator = map->begin();
    }

    _MapIterator(HashMap<String,U> map) {
        mHashMap = map;
        iterator = mHashMap->begin();
    }

    String getKey() {
        return createString(iterator->first);
    }

    U getValue() {
        return iterator->second;
    }

    bool hasValue() {
        return iterator != mHashMap->end();
    }

    bool next() {
        iterator++;
        if(iterator ==  mHashMap->end()) {
            return false;
        }

        return true;
    }

private:
    HashMap<String,U> mHashMap;    
    typename std::map<std::string,U>::iterator iterator;
};

//----------------- MapIterator<Integer,U> ---------------------
template<typename U>  
class _MapIterator<Integer,U>:virtual public Object{
public:    
    _MapIterator(_HashMap<Integer,U> *map) {
        mHashMap.set_pointer(map);
        //map->incStrong(0);

        iterator = map->begin();
    }

    _MapIterator(HashMap<Integer,U> map) {
        mHashMap = map;
        iterator = mHashMap->begin();
    }

    Integer getKey() {
        return createInteger(iterator->first);
    }

    U getValue() {
        return iterator->second;
    }

    bool hasValue() {
        return iterator != mHashMap->end();
    }

    bool next() {
        iterator++;
        if(iterator ==  mHashMap->end()) {
            return false;
        }

        return true;
    }

private:
    HashMap<Integer,U> mHashMap;    
    typename std::map<int,U>::iterator iterator;
};

//----------------- MapIterator<Double,U> ---------------------
template<typename U>  
class _MapIterator<Double,U>:virtual public Object{
public:
    _MapIterator(_HashMap<Double,U> *map) {
        mHashMap.set_pointer(map);
        //map->incStrong(0);

        iterator = map->begin();
    }

    _MapIterator(HashMap<Double,U> map) {
        mHashMap = map;
        iterator = mHashMap->begin();
    }

    Double getKey() {
        return createDouble(iterator->first);
    }

    U getValue() {
        return iterator->second;
    }

    bool hasValue() {
        return iterator != mHashMap->end();
    }

    bool next() {
        iterator++;
        if(iterator ==  mHashMap->end()) {
            return false;
        }

        return true;
    }

private:
    HashMap<Double,U> mHashMap;    
    typename std::map<double,U>::iterator iterator;
};

//----------------- MapIterator<Double,U> ---------------------
template<typename U>  
class _MapIterator<Float,U>:virtual public Object{
public:
    _MapIterator(_HashMap<Float,U> *map) {
        mHashMap.set_pointer(map);
        //map->incStrong(0);

        iterator = map->begin();
    }

    _MapIterator(HashMap<Float,U> map) {
        mHashMap = map;
        iterator = mHashMap->begin();
    }

    Float getKey() {
        return createFloat(iterator->first);
    }

    U getValue() {
        return iterator->second;
    }

    bool hasValue() {
        return iterator != mHashMap->end();
    }

    bool next() {
        iterator++;
        if(iterator ==  mHashMap->end()) {
            return false;
        }

        return true;
    }

private:
    HashMap<Float,U> mHashMap;    
    typename std::map<float,U>::iterator iterator;
};

//----------------- MapIterator<Boolean,U> ---------------------
template<typename U>  
class _MapIterator<Boolean,U>:virtual public Object{
public:
    _MapIterator(_HashMap<Boolean,U> *map) {
        mHashMap.set_pointer(map);
        //map->incStrong(0);

        iterator = map->begin();
    }

    _MapIterator(HashMap<Boolean,U> map) {
        mHashMap = map;
        iterator = mHashMap->begin();
    }

    Boolean getKey() {
        return createBoolean(iterator->first);
    }

    U getValue() {
        return iterator->second;
    }

    bool hasValue() {
        return iterator != mHashMap->end();
    }

    bool next() {
        iterator++;
        if(iterator ==  mHashMap->end()) {
            return false;
        }

        return true;
    }

    private:
    HashMap<Boolean,U> mHashMap;    
    typename std::map<bool,U>::iterator iterator;
};

//----------------- MapIterator<Long,U> ---------------------
template<typename U>  
class _MapIterator<Long,U>:virtual public Object{
public:
    _MapIterator(_HashMap<Long,U> *map) {
        mHashMap.set_pointer(map);
        //map->incStrong(0);

        iterator = map->begin();
    }

    _MapIterator(HashMap<Long,U> map) {
        mHashMap = map;
        iterator = mHashMap->begin();
    }

    Long getKey() {
        return createLong(iterator->first);
    }

    U getValue() {
        return iterator->second;
    }

    bool hasValue() {
        return iterator != mHashMap->end();
    }

    bool next() {
        iterator++;
        if(iterator ==  mHashMap->end()) {
            return false;
        }

        return true;
    }

private:
    HashMap<Long,U> mHashMap;    
    typename std::map<long,U>::iterator iterator;
};

}
#endif
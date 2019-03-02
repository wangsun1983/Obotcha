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
#include "String.hpp"

#include "Collection.hpp"
#include "ArrayList.hpp"

using namespace std;


DECLARE_CLASS(HashMap,2) {
public:
    void put(T t,U u) {
        hashmap.insert(std::pair<T, U>(t, u));
    }

    U get(T t);

    void remove(T t);

    bool isEmpty();

    void clear();

    int size();

    template<typename V>
    ArrayList<V> keySet();
    
    template<typename V>
    ArrayList<V> entrySet();

    auto begin();

    auto end();

private:
    std::map<T,U> hashmap;
};

template<typename T,typename U>
void _HashMap<T,U>::remove(T t) {
    hashmap.earse(t);
}

template<typename T,typename U>
U _HashMap<T,U>::get(T t) {
    auto value = hashmap.find(t);
    if(value == hashmap.end()) {
        return nullptr;
    }

    return value->second;
}

template<typename T,typename U>
bool _HashMap<T,U>::isEmpty() {
    return hashmap.size() == 0;
}

template<typename T,typename U>
void _HashMap<T,U>::clear() {
    hashmap.clear();
}

template<typename T,typename U>
int _HashMap<T,U>::size() {
    return hashmap.size();
}

template<typename T,typename U> template<typename V>
ArrayList<V> _HashMap<T,U>::keySet(){
    ArrayList<V> keyset = createArrayList<V>();
    for (auto it= hashmap.begin();it != hashmap.end();it++) {
        keyset.add(it->first);
    }

    return keyset;
}

template<typename T,typename U> template<typename V>
ArrayList<V> _HashMap<T,U>::entrySet(){
    ArrayList<V> keyset = createArrayList<V>();
    for (auto it= hashmap.begin();it != hashmap.end();it++) {
        keyset.add(it->second);
    }

    return keyset;
}

template<typename T,typename U>
auto _HashMap<T,U>::begin() {
    return hashmap.begin();
}

template<typename T,typename U>
auto _HashMap<T,U>::end() {
    return hashmap.end();
}


template<typename U>  
class _HashMap<String,U>:virtual public obo::Object{

public:
    inline void put(String t,U u) {
        hashmap.insert(std::pair<std::string, U>(t->getStdSring(),u));
    }

    U get(String t) {
        auto value = hashmap.find(t->getStdSring());
        if(value == hashmap.end()) {
            return nullptr;
        }

        return value->second;
    }

private:
    std::map<std::string,U> hashmap;
};

template<typename U>  
class _HashMap<Integer,U>:virtual public obo::Object{

public:
    inline void put(Integer t,U u) {
        hashmap.insert(std::pair<int, U>(t->toValue(),u));
    }

    U get(Integer t) {
        auto value = hashmap.find(t->toValue());
        if(value == hashmap.end()) {
            return nullptr;
        }

        return value->second;
    }

private:
    std::map<int,U> hashmap;
};

template<typename U>  
class _HashMap<Double,U>:virtual public obo::Object{

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

private:
    std::map<double,U> hashmap;
};

template<typename U>  
class _HashMap<Float,U>:virtual public obo::Object{

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

private:
    std::map<float,U> hashmap;
};

template<typename U>  
class _HashMap<Boolean,U>:virtual public obo::Object{

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

private:
    std::map<bool,U> hashmap;
};

#endif
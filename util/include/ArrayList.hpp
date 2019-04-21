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
#include "Long.hpp"
#include "String.hpp"

#include "Collection.hpp"

using namespace std;

namespace obotcha {
    
template<typename T>
class _ListIterator;

class _ListIterator<String>;

class _ListIterator<Integer>;

class _ListIterator<Boolean>;

class _ListIterator<Float>;

class _ListIterator<Double>;

class _ListIterator<Long>;

template<typename T>
class _ArrayList;

class _ArrayList<String>;

class _ArrayList<Integer>;

class _ArrayList<Boolean>;

class _ArrayList<Float>;

class _ArrayList<Double>;

class _ArrayList<Long>;

//----------------- ArrayList ---------------------
DECLARE_CLASS(ArrayList,1) {
public:

    friend class _ListIterator<T>;

    inline void add(T val) {
        elements.insert(elements.end(),val); 
    }

    inline void add(ArrayList<T> list) {
        elements.insert(elements.end(),list->elements.begin(),list->elements.end());
    }

    inline void clear() {
        elements.clear();
    }

    inline T remove(int index) {
        if(index >= elements.size() || index < 0) {
            return nullptr;
        }

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
        if(index >= elements.size() || index < 0) {
            return -1;
        }

        elements[index] = val;
    }

    inline T get(int index) {
        return elements[index];
    }

    inline int insert(int index,T val) {
        //printf("insert index is %d,elements.size() is %d \n",index,elements.size());
        if(index >= elements.size() || index < 0) {
            if(index != 0) {
                return -1;    
            }
        }

        printf("insert trace \n");

        elements.insert(elements.begin() + index,val);
        return 0;
    }

    inline int insert(int index,ArrayList<T> list) {
        if(index >= elements.size() || index < 0) {
            if(index != 0) {
                return -1;
            }
        }

        if(list != nullptr) {
            elements.insert(elements.begin() + index,list->begin(),list->end());
        }
        return 0;
    }

    inline int insert(int index,ArrayList<T> list,int length) {
        if(index >= elements.size() || length <= 0 || index < 0) {
            if(index != 0) {
                return -1;
            }
        }

        if(list != nullptr) {
            int size = list->elements.size(); 
            size = length > (size - 1)?(size -1):length;

            elements.insert(elements.begin() + index,list->begin(),list->begin() + size);
        }
        return 0;
    }

    inline void insertFirst(T val) {
        elements.insert(elements.begin(),val); 
    }


    inline void insertFirst(ArrayList<T> list) {
        elements.insert(elements.begin(),list->elements.begin(),list->elements.end());
    }
    
    inline void insertLast(T v) {
        elements.insert(elements.end(),v);
    }

    inline void insertLast(ArrayList<T> list) {
        elements.insert(elements.end(),list->begin(),list->end());
    }

    inline int size() {
        return elements.size();
    }

    sp<_ListIterator<T>> getIterator() {
        return new _ListIterator<T>(this);
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
        //list->incStrong(0);
        iterator = list->begin();
    }

    _ListIterator(ArrayList<T> list) {
        mList = list;
        iterator = mList->begin();
    }

    T getValue() {
        //return iterator->second;
        if(iterator == mList->end()) {
            return nullptr;
        }

        return *iterator;
    }

    bool hasValue() {
        return iterator != mList->end();
    }

    bool next() {
        iterator++;
        if(iterator ==  mList->end()) {
            return false;
        }

        return true;
    }
    
private:
    ArrayList<T> mList;    
    typename std::vector<T>::iterator iterator;
};



//----------------- ArrayList<String> ---------------------
template<>
class _ArrayList<String>:virtual public Object{

public:
    friend class _ListIterator<String>;

    void add(const char *s);

    void add(const std::string s);

    void add(String val);

    void add(ArrayList<String> list);

    void clear();

    String remove(int index);

    int remove(String v);

    int indexOf(String v);

    int set(int index,String val);

    String get(int index);

    int insert(int index,String val);

    int insert(int index,const char *s);

    int insert(int index,const std::string s);

    int insert(int index,ArrayList<String> list);

    int insert(int index,ArrayList<String> list,int length);

    void insertFirst(String val);

    void insertFirst(const char *s);

    void insertFirst(ArrayList<String> list);
    
    void insertLast(String v);

    void insertLast(const char *s);

    void insertLast(ArrayList<String> list);

    int size();

    sp<_ListIterator<String>> getIterator();

private:
    std::vector<std::string> elements;

    std::vector<std::string>::iterator begin();

    std::vector<std::string>::iterator end();
};

//----------------- ArrayListIterator ---------------------
template<>
class _ListIterator<String>:virtual public Object {
public:
    _ListIterator(_ArrayList<String> *list);

    _ListIterator(ArrayList<String> list);

    String getValue();

    bool hasValue();

    bool next();
    
private:
    ArrayList<String> mList;    
    std::vector<std::string>::iterator iterator;
};


//----------------- ArrayList<Integer> ---------------------
template<>
class _ArrayList<Integer>:virtual public Object{
public:
    friend class _ListIterator<Integer>;
    
    void add(Integer val);

    void add(int val);

    void add(ArrayList<Integer> list);

    void clear();

    Integer remove(int index);

    int remove(Integer v);

    int indexOf(Integer v);

    int set(int index,Integer val);

    int set(int index,int val);

    Integer get(int index);

    int insert(int index,Integer val);

    int insert(int index,int val);

    int insert(int index,ArrayList<Integer> list);

    int insert(int index,ArrayList<Integer> list,int length);

    void insertFirst(Integer val);

    void insertFirst(int val);

    void insertFirst(ArrayList<Integer> list);
    
    void insertLast(Integer v);

    void insertLast(int v);
 
    void insertLast(ArrayList<Integer> list);

    int size();

    sp<_ListIterator<Integer>> getIterator();


private:
    std::vector<int> elements;

    std::vector<int>::iterator begin();

    std::vector<int>::iterator end();
};

//----------------- ArrayListIterator<Integer> ---------------------
template<>
class _ListIterator<Integer>:virtual public Object {
public:
    _ListIterator(_ArrayList<Integer> *list);

    _ListIterator(ArrayList<Integer> list);

    Integer getValue();

    bool hasValue();

    bool next();
    
private:
    ArrayList<Integer> mList;    
    std::vector<int>::iterator iterator;
};


//----------------- ArrayList<Boolean> ---------------------
template<>
class _ArrayList<Boolean>:virtual public Object{

public:
    friend class _ListIterator<Boolean>;

    void add(Boolean val);

    void add(bool val);

    void add(ArrayList<Boolean> list);

    void clear();

    Boolean remove(int index);

    int remove(Boolean v);

    int indexOf(Boolean v);

    int set(int index,Boolean val);

    int set(int index,bool val);

    Boolean get(int index);

    int insert(int index,Boolean val);

    int insert(int index,bool val);

    int insert(int index,ArrayList<Boolean> list);

    int insert(int index,ArrayList<Boolean> list,int length);

    void insertFirst(Boolean val);

    void insertFirst(bool val);

    void insertFirst(ArrayList<Boolean> list);
    
    void insertLast(Boolean v);

    void insertLast(bool v);

    void insertLast(ArrayList<Boolean> list);

    int size();

    sp<_ListIterator<Boolean>> getIterator();


private:
    std::vector<bool> elements;

    std::vector<bool>::iterator begin();

    std::vector<bool>::iterator end();
};

//----------------- ArrayListIterator ---------------------
template<>
class _ListIterator<Boolean>:virtual public Object {
public:
    _ListIterator(_ArrayList<Boolean> *list);

    _ListIterator(ArrayList<Boolean> list);

    Boolean getValue();

    bool hasValue();

    bool next();
    
private:
    ArrayList<Boolean> mList;    
    std::vector<bool>::iterator iterator;
};

//----------------- ArrayList<Float> ---------------------
template<>
class _ArrayList<Float>:virtual public Object{

public:
    friend class _ListIterator<Float>;

    void add(Float val);

    void add(float val);

    void add(ArrayList<Float> list);

    void clear();

    Float remove(int index);

    int remove(Float v);

    int indexOf(Float v);

    int set(int index,Float val);

    int set(int index,float val);

    Float get(int index);

    int insert(int index,Float val);

    int insert(int index,float val);

    int insert(int index,ArrayList<Float> list);

    int insert(int index,ArrayList<Float> list,int length);

    void insertFirst(Float val);

    void insertFirst(float val);

    void insertFirst(ArrayList<Float> list);
    
    void insertLast(Float v);

    void insertLast(float v);

    void insertLast(ArrayList<Float> list);

    int size();

    sp<_ListIterator<Float>> getIterator();

private:
    std::vector<float> elements;

    std::vector<float>::iterator begin();

    std::vector<float>::iterator end();
};

//----------------- ArrayListIterator <Float>---------------------
template<>
class _ListIterator<Float>:virtual public Object {
public:
    _ListIterator(_ArrayList<Float> *list);

    _ListIterator(ArrayList<Float> list);

    Float getValue();

    bool hasValue();

    bool next();
    
private:
    ArrayList<Float> mList;    
    std::vector<float>::iterator iterator;
};

//----------------- ArrayList<Double> ---------------------
template<>
class _ArrayList<Double>:virtual public Object{

public:
    friend class _ListIterator<Double>;

    void add(Double val);

    void add(double val);

    void add(ArrayList<Double> list);

    void clear();

    Double remove(int index);

    int remove(Double v);

    int indexOf(Double v);

    int set(int index,Double val);

    int set(int index,double val);

    Double get(int index);

    int insert(int index,Double val);

    int insert(int index,double val);

    int insert(int index,ArrayList<Double> list);

    int insert(int index,ArrayList<Double> list,int length);

    void insertFirst(Double val);

    void insertFirst(double val);

    void insertFirst(ArrayList<Double> list);
    
    void insertLast(Double v);

    void insertLast(double v);

    void insertLast(ArrayList<Double> list);

    int size();

    sp<_ListIterator<Double>> getIterator();

private:
    std::vector<double> elements;

    std::vector<double>::iterator begin();

    std::vector<double>::iterator end();
};

//----------------- ArrayListIterator <Double>---------------------
template<>
class _ListIterator<Double>:virtual public Object {
public:
    _ListIterator(_ArrayList<Double> *list);

    _ListIterator(ArrayList<Double> list);

    Double getValue();

    bool hasValue();

    bool next();
    
private:
    ArrayList<Double> mList;    
    std::vector<double>::iterator iterator;
};

//----------------- ArrayList<Long> ---------------------
template<>
class _ArrayList<Long>:virtual public Object{
public:
    friend class _ListIterator<Long>;

    void add(Long val);

    void add(long val);

    void add(ArrayList<Long> list);

    void clear();

    Long remove(int index);

    int remove(Long v);

    int indexOf(Long v);

    int set(int index,Long val);

    int set(int index,long val);

    Long get(int index);

    int insert(int index,Long val);

    int insert(int index,long val);

    int insert(int index,ArrayList<Long> list);

    int insert(int index,ArrayList<Long> list,int length);

    void insertFirst(Long val);

    void insertFirst(long val);

    void insertFirst(ArrayList<Long> list);
    
    void insertLast(Long v);

    void insertLast(long v);

    void insertLast(ArrayList<Long> list);

    int size();

    sp<_ListIterator<Long>> getIterator();

private:
    std::vector<long> elements;

    std::vector<long>::iterator begin();

    std::vector<long>::iterator end();
};

//----------------- ArrayListIterator <Long>---------------------
template<>
class _ListIterator<Long>:virtual public Object {
public:
    _ListIterator(_ArrayList<Long> *list);

    _ListIterator(ArrayList<Long> list);

    Long getValue();

    bool hasValue();

    bool next();
    
private:
    ArrayList<Long> mList;    
    std::vector<long>::iterator iterator;
};
}
#endif

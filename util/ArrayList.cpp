#include <iostream>
#include "ArrayList.hpp"

namespace obotcha {

//----------------- ArrayList<String> ---------------------
void _ArrayList<String>::add(const char *s) {
    if(s != nullptr) {
        std::string str(s);
        elements.insert(elements.end(),str); 
    }
}

void _ArrayList<String>::add(std::string s) {
    //if(s != nullptr) {
    std::string str(s);
    elements.insert(elements.end(),str); 
    //}
}

void _ArrayList<String>::add(String val) {
    if(val == nullptr) {
        return;
    }

    std::string str(val->getStdString());
    elements.insert(elements.end(),str); 
}

void _ArrayList<String>::add(ArrayList<String> list) {
    if(list != nullptr) {
        int size = list->elements.size(); 
        for(int i = 0;i < size;i++) {
            std::string str(list->elements.at(i));
            elements.insert(elements.end(),str);
        }
    }
}

void _ArrayList<String>::clear() {
    elements.clear();
}

String _ArrayList<String>::remove(int index) {
    if(index >= elements.size() || index < 0) {
        return nullptr;
    }

    std::string val = elements.at(index);
    elements.erase(elements.begin() + index);
    return createString(val);
}

int _ArrayList<String>::remove(String v) {
    if(v == nullptr) {
        return -1;
    }

    std::string val = v->getStdString();
    vector<std::string>::iterator result = find(elements.begin( ), elements.end( ),val);
    if(result != elements.end()) {
        elements.erase(result);
        return result - elements.begin();
    }

    return -1;
}

int _ArrayList<String>::indexOf(String v) {
    if(v == nullptr) {
        return -1;
    }

    std::string val = v->getStdString();
    std::vector<std::string>::iterator result = find( elements.begin( ), elements.end( ),val);
    if(result == elements.end()) {
        return -1;
    }

    return(result - elements.begin());
}

int _ArrayList<String>::set(int index,String val) {
    if(index >= elements.size() || index < 0 || val == nullptr) {
        return -1;
    }

    std::string v(val->getStdString());
    elements[index] = v;

    return 0;
}

String _ArrayList<String>::get(int index) {
    if(index >= elements.size() || index < 0) {
        return nullptr;
    }
    return createString(elements[index]);
}

int _ArrayList<String>::insert(int index,String val) {
    if(index >= elements.size() || index < 0) {
        if(index != 0) {
            return -1;
        }
    }
    
    std::string str(val->getStdString());
    elements.insert(elements.begin() + index,str);
}

int _ArrayList<String>::insert(int index,const char *s) {
    if(index >= elements.size() || index < 0) {
        if(index != 0) {
            return -1;
        }
    }
    
    
    std::string str(s);
    elements.insert(elements.begin() + index,str);
    return 0;
}

int _ArrayList<String>::insert(int index,const std::string s) {
    if(index >= elements.size() || index < 0) {
        if(index != 0) {
            return -1;
        }
    }
    
    std::string str(s);
    elements.insert(elements.begin() + index,str);
    return 0;
}

int _ArrayList<String>::insert(int index,ArrayList<String> list) {
    if(index >= elements.size() || index < 0) {
        if(index != 0) {
            return -1;
        }
    }
    

    if(list != nullptr) {
        int size = list->elements.size(); 
        for(int i = 0;i < size;i++) {
            std::string str(list->elements.at(i));
            elements.insert(elements.begin() + index + i,str);
        }
    }

    return 0;
}

int _ArrayList<String>::insert(int index,ArrayList<String> list,int length) {
    if(index >= elements.size() || index < 0) {
        if(index != 0) {
            return -1;
        }
    }

    if(list != nullptr) {
        if(length > list->size()) {
            length = list->size();
        }

        for(int i = 0;i < length;i++) {
            std::string str(list->elements.at(i));
            elements.insert(elements.begin() + index + i,str);
        }
    }

    return 0;
}

void _ArrayList<String>::insertFirst(String val) {
    if(val == nullptr) {
        return;
    }

    std::string v(val->getStdString());
    elements.insert(elements.begin(),v); 
}

void _ArrayList<String>::insertFirst(const char *s) {
    if(s == nullptr) {
        return;
    }

    std::string v(s);
    elements.insert(elements.begin(),v); 
}

void _ArrayList<String>::insertFirst(ArrayList<String> list) {
    insert(0,list);
}
    
void _ArrayList<String>::insertLast(String v) {
    add(v);
}

void _ArrayList<String>::insertLast(const char * v) {
    add(v);
}

void _ArrayList<String>::insertLast(ArrayList<String> list) {
    add(list);
}

int _ArrayList<String>::size() {
    return elements.size();
}

sp<_ListIterator<String>> _ArrayList<String>::getIterator() {
    return new _ListIterator<String>(this);
}

std::vector<std::string>::iterator _ArrayList<String>::begin() {
    return elements.begin();
}

std::vector<std::string>::iterator _ArrayList<String>::end() {
    return elements.end();
}

//----------------- ArrayListIterator<String> ---------------------
_ListIterator<String>::_ListIterator(_ArrayList<String> *list) {
    mList.set_pointer(list);
    iterator = list->begin();
}

_ListIterator<String>::_ListIterator(ArrayList<String> list) {
    mList = list;
    iterator = mList->begin();
}

String _ListIterator<String>::getValue() {
    if(iterator == mList->end()) {
        return nullptr;
    }
    std::string str = *iterator;
    return createString(str);
}

bool _ListIterator<String>::hasValue() {
    return iterator != mList->end();
}

bool _ListIterator<String>::next() {
    if(iterator ==  mList->end()) {
        return false;
    }
    
    iterator++;
    return (iterator != mList->end());
}

bool _ListIterator<String>::remove() {
    if(iterator == mList->end()) {
        return false;
    }

    iterator = mList->elements.erase(iterator);
    return true;
}


//----------------- ArrayList<Integer> ---------------------
void _ArrayList<Integer>::add(Integer val) {
    if(val == nullptr) {
        return;
    }

    elements.insert(elements.end(),val->toValue()); 
}

void _ArrayList<Integer>::add(int val) {
    elements.insert(elements.end(),val); 
}

void _ArrayList<Integer>::add(ArrayList<Integer> list) {
    if(list != nullptr) {
        int size = list->elements.size(); 
        for(int i = 0;i < size;i++) {
            elements.insert(elements.end(),list->elements.at(i));
        }
    }
}

void _ArrayList<Integer>::clear() {
    elements.clear();
}

Integer _ArrayList<Integer>::remove(int index) {
    if(index >= elements.size() || index < 0) {
        return nullptr;
    }

    int val = elements.at(index);
    elements.erase(elements.begin() + index);
    return createInteger(val);
}

int _ArrayList<Integer>::remove(Integer v) {
    if(v == nullptr) {
        return -1;
    }

    vector<int>::iterator result = find(elements.begin( ), elements.end( ),v->toValue());
    if(result != elements.end()) {
        elements.erase(result);
        return result - elements.begin();
    }

    return -1;
}

int _ArrayList<Integer>::indexOf(Integer v) {
    if(v == nullptr) {
        return -1;
    }

    int val = v->toValue();
    std::vector<int>::iterator result = find( elements.begin( ), elements.end( ),val);
    if(result == elements.end()) {
        return -1;
    }

    return(result - elements.begin());
}

int _ArrayList<Integer>::set(int index,Integer val) {
    if(index >= elements.size() || index < 0 || val == nullptr) {
        return -1;
    }
    
    elements[index] = val->toValue();
    return 0;
}

int _ArrayList<Integer>::set(int index,int val) {
    if(index >= elements.size() || index < 0) {
        return -1;
    }
    
    elements[index] = val;
    return 0;
}

Integer _ArrayList<Integer>::get(int index) {
    if(index >= elements.size()) {
        return nullptr;
    }

    return createInteger(elements[index]);
}

int _ArrayList<Integer>::insert(int index,Integer val) {
    if(index >= elements.size() || index < 0 || val == nullptr) {
        if(index != 0) {
            return -1;
        }
    }
    
    elements.insert(elements.begin() + index,val->toValue());
    return 0;
}

int _ArrayList<Integer>::insert(int index,int val) {
    if(index >= elements.size() || index < 0) {
        if(index != 0) {
            return -1;
        }
    }
    
    elements.insert(elements.begin() + index,val);
    return 0;
}

int _ArrayList<Integer>::insert(int index,ArrayList<Integer> list) {
    if(index >= elements.size() || index < 0) {
        if(index != 0) {
            return -1;
        }
    }
    
    if(list != nullptr) {
        int size = list->size();
        for(int i = 0;i < size;i++) {
            elements.insert(elements.begin() + index + i,list->elements.at(i));
        }
    }

    return 0;
}

int _ArrayList<Integer>::insert(int index,ArrayList<Integer> list,int length) {
    if(index >= elements.size() || index < 0) {
        if(index != 0) {
            return -1;
        }
    }
    
    if(list != nullptr) {
        if(length > list->size()) {
            length = list->size();
        }

        for(int i = 0;i < length;i++) {
            elements.insert(elements.begin() + index + i,list->elements[i]);
        }
    }

    return 0;
}

void _ArrayList<Integer>::insertFirst(Integer val) {
    if(val == nullptr) {
        return;
    }

    elements.insert(elements.begin(),val->toValue()); 
}

void _ArrayList<Integer>::insertFirst(int val) {
    elements.insert(elements.begin(),val); 
}


void _ArrayList<Integer>::insertFirst(ArrayList<Integer> list) {
    insert(0,list);
}
    
void _ArrayList<Integer>::insertLast(Integer v) {
    //insert(elements.end() - elements.begin(),v);
    add(v);
}

void _ArrayList<Integer>::insertLast(ArrayList<Integer> list) {
    //insert(elements.end() - elements.begin(),list);
    add(list);
}

void _ArrayList<Integer>::insertLast(int v) {
    //elements.insert(elements.end(),v);
    add(v);
}

int _ArrayList<Integer>::size() {
    return elements.size();
}

sp<_ListIterator<Integer>> _ArrayList<Integer>::getIterator() {
    return new _ListIterator<Integer>(this);
}

std::vector<int>::iterator _ArrayList<Integer>::begin() {
    return elements.begin();
}

std::vector<int>::iterator _ArrayList<Integer>::end() {
    return elements.end();
}


//----------------- ArrayListIterator<Integer> ---------------------
_ListIterator<Integer>::_ListIterator(_ArrayList<Integer> *list) {
    mList.set_pointer(list);
    
    iterator = list->begin();
}

_ListIterator<Integer>::_ListIterator(ArrayList<Integer> list) {
    mList = list;
    iterator = mList->begin();
}

Integer _ListIterator<Integer>::getValue() {
    if(iterator == mList->end()) {
        return nullptr;
    }
    return createInteger(*iterator);
}

bool _ListIterator<Integer>::hasValue() {
    return iterator != mList->end();
}

bool _ListIterator<Integer>::next() {
    if(iterator ==  mList->end()) {
        return false;
    }

    iterator++;

    return (iterator != mList->end());
}

bool _ListIterator<Integer>::remove() {
    if(iterator == mList->end()) {
        return false;
    }

    iterator = mList->elements.erase(iterator);
    return true;
}


//----------------- ArrayList<Boolean> ---------------------

void _ArrayList<Boolean>::add(Boolean val) {
    if(val == nullptr) {
        return;
    }

    elements.insert(elements.end(),val->toValue()); 
}

void _ArrayList<Boolean>::add(bool val) {
    elements.insert(elements.end(),val); 
}

void _ArrayList<Boolean>::add(ArrayList<Boolean> list) {
    if(list != nullptr) {
        int size = list->elements.size(); 
        for(int i = 0;i < size;i++) {
            elements.insert(elements.end(),list->elements.at(i));
        }
    }
}

void _ArrayList<Boolean>::clear() {
    elements.clear();
}

Boolean _ArrayList<Boolean>::remove(int index) {
    if(index >= elements.size() || index < 0) {
        return nullptr;
    }

    bool val = elements.at(index);
    elements.erase(elements.begin() + index);
    return createBoolean(val);
}

int _ArrayList<Boolean>::remove(Boolean v) {
    if(v == nullptr) {
        return -1;
    }

    vector<bool>::iterator result = find(elements.begin( ), elements.end( ),v->toValue());
    if(result != elements.end()) {
        elements.erase(result);
        return result - elements.begin();
    }

    return -1;
}

int _ArrayList<Boolean>::indexOf(Boolean v) {
    if(v == nullptr) {
        return -1;
    }

    bool val = v->toValue();
    std::vector<bool>::iterator result = find( elements.begin( ), elements.end( ),val);
    if(result == elements.end()) {
        return -1;
    }

    return(result - elements.begin());
}

int _ArrayList<Boolean>::set(int index,Boolean val) {
    if(index >= elements.size() || index < 0 || val == nullptr) {
        return -1;
    }

    elements[index] = val->toValue();
    return 0;
}

int _ArrayList<Boolean>::set(int index,bool val) {
    if(index >= elements.size() || index < 0) {
        return -1;
    }
    
    elements[index] = val;
    return 0;
}

Boolean _ArrayList<Boolean>::get(int index) {
    if(index >= elements.size()) {
        return nullptr;
    }

    return createBoolean(elements[index]);
}

int _ArrayList<Boolean>::insert(int index,Boolean val) {
    if(index >= elements.size() || index < 0) {
        if(index != 0) {
            return -1;
        }
    }

    elements.insert(elements.begin() + index,val->toValue());
    return 0;
}

int _ArrayList<Boolean>::insert(int index,bool val) {
    if(index >= elements.size() || index < 0) {
        if(index != 0) {
            return -1;
        }
    }

    elements.insert(elements.begin() + index,val);
    return 0;
}

int _ArrayList<Boolean>::insert(int index,ArrayList<Boolean> list) {
    if(index >= elements.size()|| index < 0) {
        if(index != 0) {
            return -1;
        }
    }

    if(list != nullptr) {
        //int size = list->elements.size(); 
        //for(int i = 0;i < size;i++) {
        //    elements.insert(elements.begin() + index + i,list->elements[i]);
        //}
        elements.insert(elements.begin() + index,list->begin(),list->end());
    }

    return 0;
}

int _ArrayList<Boolean>::insert(int index,ArrayList<Boolean> list,int length) {
    if(index >= elements.size()|| index < 0) {
        if(index != 0) {
            return -1;
        }
    }

    if(list != nullptr) {
        int size = list->elements.size(); 
        size = length > size?size:length;

        elements.insert(elements.begin() + index,list->begin(),list->begin() + size);
    }

    return 0;
}

void _ArrayList<Boolean>::insertFirst(Boolean val) {
    if(val == nullptr) {
        return;
    }

    elements.insert(elements.begin(),val->toValue()); 
}

void _ArrayList<Boolean>::insertFirst(bool val) {
    elements.insert(elements.begin(),val); 
}

void _ArrayList<Boolean>::insertFirst(ArrayList<Boolean> list) {
    insert(0,list);
}
    
void _ArrayList<Boolean>::insertLast(Boolean v) {
    //insert(elements.end() - elements.begin(),v);
    add(v);
}

void _ArrayList<Boolean>::insertLast(bool v) {
    //elements.insert(elements.end(),v);
    add(v);
}

void _ArrayList<Boolean>::insertLast(ArrayList<Boolean> list) {
    //insert(elements.end() - elements.begin(),list);
    add(list);
}

int _ArrayList<Boolean>::size() {
    return elements.size();
}

sp<_ListIterator<Boolean>> _ArrayList<Boolean>::getIterator() {
    return new _ListIterator<Boolean>(this);
}

std::vector<bool>::iterator _ArrayList<Boolean>::begin() {
    return elements.begin();
}

std::vector<bool>::iterator _ArrayList<Boolean>::end() {
    return elements.end();
}

//----------------- ArrayListIterator<Boolean> ---------------------
_ListIterator<Boolean>::_ListIterator(_ArrayList<Boolean> *list) {
    mList.set_pointer(list);
    iterator = list->begin();
}

_ListIterator<Boolean>::_ListIterator(ArrayList<Boolean> list) {
    mList = list;
    iterator = mList->begin();
}

Boolean _ListIterator<Boolean>::getValue() {
    if(iterator == mList->end()) {
        return nullptr;
    }

    return createBoolean(*iterator);
}

bool _ListIterator<Boolean>::hasValue() {
    return iterator != mList->end();
}

bool _ListIterator<Boolean>::next() {
    if(iterator ==  mList->end()) {
        return false;
    }
    iterator++;
    return (iterator != mList->end());
}

bool _ListIterator<Boolean>::remove() {
    if(iterator == mList->end()) {
        return false;
    }

    iterator = mList->elements.erase(iterator);
    return true;
}

//----------------- ArrayList<Float> ---------------------
void _ArrayList<Float>::add(Float val) {
    if(val == nullptr) {
        return;
    }

    elements.insert(elements.end(),val->toValue()); 
}

void _ArrayList<Float>::add(float val) {
    elements.insert(elements.end(),val); 
}

void _ArrayList<Float>::add(ArrayList<Float> list) {
    if(list != nullptr) {
        int size = list->elements.size(); 
        for(int i = 0;i < size;i++) {
            elements.insert(elements.end(),list->elements.at(i));
        }
    }
}

void _ArrayList<Float>::clear() {
    elements.clear();
}

Float _ArrayList<Float>::remove(int index) {
    if(index >= elements.size() || index < 0) {
        return nullptr;
    }

    float val = elements.at(index);
    elements.erase(elements.begin() + index);
    return createFloat(val);
}

int _ArrayList<Float>::remove(Float v) {
    if(v == nullptr) {
        return -1;
    }

    vector<float>::iterator result = find(elements.begin( ), elements.end( ),v->toValue());
    if(result != elements.end()) {
        elements.erase(result);
        return result - elements.begin();
    }

    return -1;
}

int _ArrayList<Float>::indexOf(Float v) {
    if(v == nullptr) {
        return -1;
    }

    float val = v->toValue();
    std::vector<float>::iterator result = find( elements.begin( ), elements.end( ),val);
    if(result == elements.end()) {
        return -1;
    }

    return(result - elements.begin());
}

int _ArrayList<Float>::set(int index,Float val) {
    if(index >= elements.size() || index < 0 || val == nullptr) {
        return -1;
    }

    elements[index] = val->toValue();
    return 0;
}

int _ArrayList<Float>::set(int index,float val) {
    if(index >= elements.size() || index < 0) {
        return -1;
    }

    elements[index] = val;
    return 0;
}

Float _ArrayList<Float>::get(int index) {
    if(index >= elements.size()) {
        return nullptr;
    }

    return createFloat(elements[index]);
}

int _ArrayList<Float>::insert(int index,Float val) {
    if(index >= elements.size() || index < 0) {
        if(index != 0) {
            return -1;
        }
    }

    elements.insert(elements.begin() + index,val->toValue());
    return 0;
}

int _ArrayList<Float>::insert(int index,float val) {
    if(index >= elements.size() || index < 0) {
        if(index != 0) {
            return -1;
        }
    }

    elements.insert(elements.begin() + index,val);
    return 0;
}

int _ArrayList<Float>::insert(int index,ArrayList<Float> list) {
    if(index >= elements.size() || index < 0) {
        if(index != 0) {
            return -1;
        }
    }

    if(list != nullptr) {
        int size = list->elements.size(); 
        for(int i = 0;i < size;i++) {
            elements.insert(elements.begin() + index + i,list->elements[i]);
        }
    }

    return 0;
}

int _ArrayList<Float>::insert(int index,ArrayList<Float> list,int length) {
    if(index >= elements.size() || index < 0) {
        if(index != 0) {
            return -1;
        }
    }

    if(list != nullptr) {
        //int size = list->elements.size(); 
        //size = length > (size - 1)?(size -1):length;

        //for(int i = 0;i < size;i++) {
        //    elements.insert(elements.begin() + index + i,list->elements[i]);
        //}
        int size = list->elements.size(); 
        size = length > size?size:length;

        elements.insert(elements.begin() + index,list->begin(),list->begin() + size);
    }

    return 0;
}

void _ArrayList<Float>::insertFirst(Float val) {
    if(val == nullptr) {
        return;
    }

    elements.insert(elements.begin(),val->toValue()); 
}

void _ArrayList<Float>::insertFirst(float val) {
    elements.insert(elements.begin(),val); 
}

void _ArrayList<Float>::insertFirst(ArrayList<Float> list) {
    insert(0,list);
}
    
void _ArrayList<Float>::insertLast(Float v) {
    //insert(elements.end() - elements.begin(),v);
    add(v);
}

void _ArrayList<Float>::insertLast(float v) {
    //insert(elements.end() - elements.begin(),createFloat(v));
    add(v);
}

void _ArrayList<Float>::insertLast(ArrayList<Float> list) {
    //insert(elements.end() - elements.begin(),list);
    add(list);
}

int _ArrayList<Float>::size() {
    return elements.size();
}

sp<_ListIterator<Float>> _ArrayList<Float>::getIterator() {
    return new _ListIterator<Float>(this);
}

std::vector<float>::iterator _ArrayList<Float>::begin() {
    return elements.begin();
}

std::vector<float>::iterator _ArrayList<Float>::end() {
    return elements.end();
}

//----------------- ArrayListIterator <Float>---------------------
_ListIterator<Float>::_ListIterator(_ArrayList<Float> *list) {
    mList.set_pointer(list);
    iterator = list->begin();
}

_ListIterator<Float>::_ListIterator(ArrayList<Float> list) {
    mList = list;
    iterator = mList->begin();
}

Float _ListIterator<Float>::getValue() {
    if(iterator == mList->end()) {
        return nullptr;
    }
    return createFloat(*iterator);
}

bool _ListIterator<Float>::hasValue() {
    return iterator != mList->end();
}

bool _ListIterator<Float>::next() {
    if(iterator ==  mList->end()) {
        return false;
    }
    iterator++;
    return (iterator != mList->end());
}

bool _ListIterator<Float>::remove() {
    if(iterator == mList->end()) {
        return false;
    }

    iterator = mList->elements.erase(iterator);
    return true;
}

//----------------- ArrayList<Double> ---------------------
void _ArrayList<Double>::add(Double val) {
    if(val == nullptr) {
        return;
    }

    elements.insert(elements.end(),val->toValue()); 
}

void _ArrayList<Double>::add(double val) {
    elements.insert(elements.end(),val); 
}

void _ArrayList<Double>::add(ArrayList<Double> list) {
    if(list != nullptr) {
        int size = list->elements.size(); 
        for(int i = 0;i < size;i++) {
            elements.insert(elements.end(),list->elements.at(i));
        }
    }
}

void _ArrayList<Double>::clear() {
    elements.clear();
}

Double _ArrayList<Double>::remove(int index) {
    if(index >= elements.size() || index < 0) {
        return nullptr;
    }

    double val = elements.at(index);
    elements.erase(elements.begin() + index);
    return createDouble(val);
}

int _ArrayList<Double>::remove(Double v) {
    if(v == nullptr) {
        return -1;
    }

    vector<double>::iterator result = find(elements.begin( ), elements.end( ),v->toValue());
    if(result != elements.end()) {
        elements.erase(result);
        return result - elements.begin();
    }

    return -1;
}

int _ArrayList<Double>::indexOf(Double v) {
    if(v == nullptr) {
        return -1;
    }

    double val = v->toValue();
    std::vector<double>::iterator result = find( elements.begin( ), elements.end( ),val);
    if(result == elements.end()) {
        return -1;
    }

    return(result - elements.begin());
}

int _ArrayList<Double>::set(int index,Double val) {
    if(index >= elements.size() || index < 0 || val == nullptr) {
        return -1;
    }

    elements[index] = val->toValue();
    return  0;
}

int _ArrayList<Double>::set(int index,double val) {
    if(index >= elements.size() || index < 0) {
        return -1;
    }

    elements[index] = val;
    return 0;
}

Double _ArrayList<Double>::get(int index) {
    if(index >= elements.size()) {
        return nullptr;
    }

    return createDouble(elements[index]);
}

int _ArrayList<Double>::insert(int index,Double val) {
    if(index >= elements.size() || index < 0) {
        if(index != 0) {
            return -1;
        }
    }

    elements.insert(elements.begin() + index,val->toValue());
    return 0;
}

int _ArrayList<Double>::insert(int index,double val) {
    if(index >= elements.size() || index < 0) {
        if(index != 0) {
            return -1;
        }
    }

    elements.insert(elements.begin() + index,val);
    return 0;
}

int _ArrayList<Double>::insert(int index,ArrayList<Double> list) {
    if(index >= elements.size() || index < 0) {
        if(index != 0) {
            return -1;
        }
    }

    if(list != nullptr) {
        int size = list->elements.size(); 
        for(int i = 0;i < size;i++) {
            elements.insert(elements.begin() + index + i,list->elements[i]);
        }
    }

    return 0;
}

int _ArrayList<Double>::insert(int index,ArrayList<Double> list,int length) {
    if(index >= elements.size() || index < 0) {
        if(index != 0) {
            return -1;
        }
    }

    if(list != nullptr) {
        //int size = list->elements.size(); 
        //size = length > (size - 1)?(size -1):length;

        //for(int i = 0;i < size;i++) {
        //    elements.insert(elements.begin() + index + i,list->elements[i]);
        //}
        int size = list->elements.size(); 
        size = length > size?size:length;

        elements.insert(elements.begin() + index,list->begin(),list->begin() + size);
    }

    return 0;
}

void _ArrayList<Double>::insertFirst(Double val) {
    if(val == nullptr) {
        return;
    }

    elements.insert(elements.begin(),val->toValue()); 
}

void _ArrayList<Double>::insertFirst(double val) {
    elements.insert(elements.begin(),val); 
}

void _ArrayList<Double>::insertFirst(ArrayList<Double> list) {
    insert(0,list);
}
    
void _ArrayList<Double>::insertLast(Double v) {
    //insert(elements.end() - elements.begin(),v);
    add(v);
}

void _ArrayList<Double>::insertLast(double v) {
    //elements.insert(elements.end(),v);
    add(v); 
}

void _ArrayList<Double>::insertLast(ArrayList<Double> list) {
    //insert(elements.end() - elements.begin(),list);
    add(list);
}

int _ArrayList<Double>::size() {
    return elements.size();
}

sp<_ListIterator<Double>> _ArrayList<Double>::getIterator() {
    return new _ListIterator<Double>(this);
}

std::vector<double>::iterator _ArrayList<Double>::begin() {
    return elements.begin();
}

std::vector<double>::iterator _ArrayList<Double>::end() {
    return elements.end();
}

//----------------- ArrayListIterator <Double>---------------------
_ListIterator<Double>::_ListIterator(_ArrayList<Double> *list) {
    mList.set_pointer(list);

    iterator = list->begin();
}

_ListIterator<Double>::_ListIterator(ArrayList<Double> list) {
    mList = list;
    iterator = mList->begin();
}

Double _ListIterator<Double>::getValue() {
    if(iterator == mList->end()) {
        return nullptr;
    }
    return createDouble(*iterator);
}

bool _ListIterator<Double>::hasValue() {
    return iterator != mList->end();
}

bool _ListIterator<Double>::next() {
    if(iterator ==  mList->end()) {
        return false;
    }
    iterator++;
    return (iterator != mList->end());
}

bool _ListIterator<Double>::remove() {
    if(iterator == mList->end()) {
        return false;
    }

    iterator = mList->elements.erase(iterator);
    return true;
}

//----------------- ArrayList<Long> ---------------------
void _ArrayList<Long>::add(Long val) {
    if(val == nullptr) {
        return;
    }
    
    elements.insert(elements.end(),val->toValue()); 
}

void _ArrayList<Long>::add(long val) {
    elements.insert(elements.end(),val); 
}

void _ArrayList<Long>::add(ArrayList<Long> list) {
    if(list != nullptr) {
        int size = list->elements.size(); 
        for(int i = 0;i < size;i++) {
            elements.insert(elements.end(),list->elements.at(i));
        }
    }
}

void _ArrayList<Long>::clear() {
    elements.clear();
}

Long _ArrayList<Long>::remove(int index) {
    if(index >= elements.size() || index < 0) {
        return nullptr;
    }

    long val = elements.at(index);
    elements.erase(elements.begin() + index);
    return createLong(val);
}

int _ArrayList<Long>::remove(Long v) {
    if(v == nullptr) {
        return -1;
    }

    vector<long>::iterator result = find(elements.begin( ), elements.end( ),v->toValue());
    if(result != elements.end()) {
        elements.erase(result);
        return result - elements.begin();
    }

    return -1;
}

int _ArrayList<Long>::indexOf(Long v) {
    if(v == nullptr) {
        return -1;
    }

    long val = v->toValue();
    std::vector<long>::iterator result = find( elements.begin( ), elements.end( ),val);
    if(result == elements.end()) {
        return -1;
    }

    return(result - elements.begin());
}

int _ArrayList<Long>::set(int index,Long val) {
    if(index >= elements.size() || index < 0 || val == nullptr) {
        return -1;
    }

    elements[index] = val->toValue();
    return 0;
}

int  _ArrayList<Long>::set(int index,long val) {
    if(index >= elements.size() || index < 0) {
        return -1;
    }

    elements[index] = val;
    return 0;
}

Long _ArrayList<Long>::get(int index) {
    if(index >= elements.size()) {
        return nullptr;
    }

    return createLong(elements[index]);
}

int _ArrayList<Long>::insert(int index,Long val) {
    if(index >= elements.size() || index < 0) {
        if(index != 0) {
            return -1;
        }
    }

    elements.insert(elements.begin() + index,val->toValue());
    return 0;
}

int _ArrayList<Long>::insert(int index,long val) {
    if(index >= elements.size() || index < 0) {
        if(index != 0) {
            return -1;
        }
    }

    elements.insert(elements.begin() + index,val);
    return 0;
}

int _ArrayList<Long>::insert(int index,ArrayList<Long> list) {
    if(index >= elements.size() || index < 0) {
        if(index != 0) {
            return -1;
        }
    }

    if(list != nullptr) {
        int size = list->elements.size(); 
        for(int i = 0;i < size;i++) {
            elements.insert(elements.begin() + index + i,list->elements[i]);
        }
    }

    return 0;
}

int _ArrayList<Long>::insert(int index,ArrayList<Long> list,int length) {
    if(index >= elements.size() || index < 0) {
        if(index != 0) {
            return -1;
        }
    }

    if(list != nullptr) {
        //int size = list->elements.size(); 
        //size = length > (size - 1)?(size -1):length;
        //for(int i = 0;i < size;i++) {
        //    elements.insert(elements.begin() + index + i,list->elements[i]);
        //}
        int size = list->elements.size(); 
        size = length > size?size:length;

        elements.insert(elements.begin() + index,list->begin(),list->begin() + size);
    }

    return 0;
}

void _ArrayList<Long>::insertFirst(Long val) {
    if(val == nullptr) {
        return;
    }

    elements.insert(elements.begin(),val->toValue()); 
}

void _ArrayList<Long>::insertFirst(long val) {
    elements.insert(elements.begin(),val); 
}

void _ArrayList<Long>::insertFirst(ArrayList<Long> list) {
    insert(0,list);
}
    
void _ArrayList<Long>::insertLast(Long v) {
    //insert(elements.end() - elements.begin(),v);
    add(v);
}

void _ArrayList<Long>::insertLast(long v) {
    //elements.insert(elements.end(),v);
    add(v);
}

void _ArrayList<Long>::insertLast(ArrayList<Long> list) {
    //insert(elements.end() - elements.begin(),list);
    add(list);
}

int _ArrayList<Long>::size() {
    return elements.size();
}

sp<_ListIterator<Long>> _ArrayList<Long>::getIterator() {
    return new _ListIterator<Long>(this);
}

std::vector<long>::iterator _ArrayList<Long>::begin() {
    return elements.begin();
}

std::vector<long>::iterator _ArrayList<Long>::end() {
    return elements.end();
}

//----------------- ArrayListIterator <Long>---------------------
_ListIterator<Long>::_ListIterator(_ArrayList<Long> *list) {
    mList.set_pointer(list);
    iterator = list->begin();
}

_ListIterator<Long>::_ListIterator(ArrayList<Long> list) {
    mList = list;
    iterator = mList->begin();
}

Long _ListIterator<Long>::getValue() {
    if(iterator == mList->end()) {
        return nullptr;
    }
    return createLong(*iterator);
}

bool _ListIterator<Long>::hasValue() {
    return iterator != mList->end();
}

bool _ListIterator<Long>::next() {
    if(iterator ==  mList->end()) {
        return false;
    }

    iterator++;
    return (iterator != mList->end());
}

bool _ListIterator<Long>::remove() {
    if(iterator == mList->end()) {
        return false;
    }

    iterator = mList->elements.erase(iterator);
    return true;
}


}
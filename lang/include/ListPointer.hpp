#ifndef __LIST_POINTER_HPP__
#define __LIST_POINTER_HPP__

#include <stdio.h>
#include <stdlib.h>
#include <type_traits>

#include "ListObject.hpp"
#include "Object.hpp"
#include "StrongPointer.hpp"

namespace obotcha {

template <typename T>
class __lst :public sp<T>{
public:
    __lst():sp<T>{} {

    }

    __lst(T* other) :sp<T>{other}{
    }

    __lst(const sp<T>& other):sp<T>{other} {

    }

    template<typename U> __lst(U* other):sp<T>{other} {

    }

    template<typename U> __lst(const sp<U>& other):sp<T>{other} {

    }

    __lst& operator = (T* other) {
        if (other) other->incStrong(this);
            if (this->m_ptr) {
                if(this->m_ptr->decStrong(this) == OBJ_DEC_FREE) {
                    delete static_cast<const T*>(this->m_ptr);
            }   
        }
        this->m_ptr = other;

        return *this;
    }


    __lst& operator = (const sp<T>& other) {
        T* otherPtr(other.m_ptr);
        if (otherPtr) otherPtr->incStrong(this);
        if (this->m_ptr) {
            if(this->m_ptr->decStrong(this) == OBJ_DEC_FREE) {
                delete static_cast<const T*>(this->m_ptr);
            }
        }

        this->m_ptr = otherPtr;
        return *this;
    }

    //add for list
    auto operator[] (int i) ->decltype((*this->m_ptr)[0])
    { 
        return (*this->m_ptr)[i];
    }
};

template <typename T>
class __btarr :public sp<T>{
public:
    __btarr():sp<T>{} {

    }

    __btarr(T* other) :sp<T>{other}{
    }

    __btarr(const sp<T>& other):sp<T>{other} {

    }

    template<typename U> __btarr(U* other):sp<T>{other} {

    }

    template<typename U> __btarr(const sp<U>& other):sp<T>{other} {

    }

    __btarr& operator = (T* other) {
        if (other) other->incStrong(this);
            if (this->m_ptr) {
                if(this->m_ptr->decStrong(this) == OBJ_DEC_FREE) {
                    delete static_cast<const T*>(this->m_ptr);
            }   
        }
        this->m_ptr = other;

        return *this;
    }


    __btarr& operator = (const sp<T>& other) {
        T* otherPtr(other.m_ptr);
        if (otherPtr) otherPtr->incStrong(this);
        if (this->m_ptr) {
            if(this->m_ptr->decStrong(this) == OBJ_DEC_FREE) {
                delete static_cast<const T*>(this->m_ptr);
            }
        }

        this->m_ptr = otherPtr;
        return *this;
    }

    //add for list
    unsigned char &operator[] (int i)
    { 
        return (unsigned char &)(*this->m_ptr)[i];
    }
};

}
#endif
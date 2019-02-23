#ifndef __STRONG_POINTER_HPP__
#define __STRONG_POINTER_HPP__

#include <stdio.h>
#include <stdlib.h>

#include "Object.hpp"

// ---------------------------------------------------------------------------
#define COMPARE(_op_)                                           \
inline bool operator _op_ (const sp<T>& o) const {              \
    return m_ptr _op_ o.m_ptr;                                  \
}                                                               \
inline bool operator _op_ (const T* o) const {                  \
    return m_ptr _op_ o;                                        \
}                                                               \
template<typename U>                                            \
inline bool operator _op_ (const sp<U>& o) const {              \
    return m_ptr _op_ o.m_ptr;                                  \
}                                                               \
template<typename U>                                            \
inline bool operator _op_ (const U* o) const {                  \
    return m_ptr _op_ o;                                        \
}                                                               \
// ---------------------------------------------------------------------------

template <typename T>
class sp {

public:
    inline sp() : m_ptr(0) { }

    sp(T* other);
    sp(const sp<T>& other);
    template<typename U> sp(U* other);
    template<typename U> sp(const sp<U>& other);

    ~sp();

    // Assignment

    sp& operator = (T* other);
    sp& operator = (const sp<T>& other);

    template<typename U> sp& operator = (const sp<U>& other);
    template<typename U> sp& operator = (U* other);

    //! Special optimization for use by ProcessState (and nobody else).
    void force_set(T* other);

    // Reset

    void clear();

    // Accessors

    inline  T&      operator* () const  { return *m_ptr; }
    inline  T*      operator-> () const { return m_ptr;  }
    inline  T*      get() const         { return m_ptr; }

    // Operators(==)
    inline bool operator == (const sp<T>& o) const { 
        return m_ptr->equals(o.m_ptr);
    }
    inline bool operator == (const T* o) const {
        return m_ptr->equals(o);
    }

    template<typename U>                                            
    inline bool operator == (const sp<U>& o) const {
        return m_ptr->equals(o.m_ptr);
    }

    template<typename U>
    inline bool operator == (const U* o) const {
        return m_ptr->euqals(o);
    }

    // Operators(!=)
    inline bool operator != (const sp<T>& o) const { 
        return !m_ptr->equals(o.m_ptr);
    }

    inline bool operator != (const T* o) const {
        return !m_ptr->equals(o);
    }

    template<typename U>                                            
    inline bool operator != (const sp<U>& o) const {
        return !m_ptr->equals(o.m_ptr);
    }

    template<typename U>
    inline bool operator != (const U* o) const {
        return !m_ptr->euqals(o);
    }

    //COMPARE(==)
    //COMPARE(!=)
    COMPARE(>)
    COMPARE(<)
    COMPARE(<=)
    COMPARE(>=)

    void set_pointer(T* ptr);
    
    T* get_pointer();

    T* m_ptr;
};



template<typename T>
sp<T>::sp(T* other)
: m_ptr(other)
  {
    if (other) other->incStrong(this);
  }

template<typename T>
sp<T>::sp(const sp<T>& other)
: m_ptr(other.m_ptr)
  {
    if (m_ptr) m_ptr->incStrong(this);
  }

template<typename T> template<typename U>
sp<T>::sp(U* other) : m_ptr(other)
{
    if (other) ((T*)other)->incStrong(this);
}

template<typename T> template<typename U>
sp<T>::sp(const sp<U>& other)
: m_ptr(other.m_ptr)
  {
    if (m_ptr) m_ptr->incStrong(this);
  }

template<typename T>
sp<T>::~sp()
{
    if (m_ptr) {
        if(m_ptr->decStrong(this) == OBJ_DEC_FREE) {
            delete m_ptr;
        }
    }
}

template<typename T>
sp<T>& sp<T>::operator = (const sp<T>& other) {
    T* otherPtr(other.m_ptr);
    if (otherPtr) otherPtr->incStrong(this);
    
    if (m_ptr) {
    	if(m_ptr->decStrong(this) == OBJ_DEC_FREE) {
            delete static_cast<const T*>(m_ptr);
        }
    }

    m_ptr = otherPtr;
    return *this;
}

template<typename T>
sp<T>& sp<T>::operator = (T* other)
{
    if (other) other->incStrong(this);
    if (m_ptr) {
        if(m_ptr->decStrong(this) == OBJ_DEC_FREE) {
            delete static_cast<const T*>(m_ptr);
        }	
    }
    m_ptr = other;
    return *this;
}

template<typename T> template<typename U>
sp<T>& sp<T>::operator = (const sp<U>& other)
{
    T* otherPtr(other.m_ptr);
    if (otherPtr) otherPtr->incStrong(this);
    if (m_ptr) {
    	if(m_ptr->decStrong(this) == OBJ_DEC_FREE) {
            delete static_cast<const T*>(m_ptr);
        }
    }
    m_ptr = otherPtr;
    return *this;
}

template<typename T> template<typename U>
sp<T>& sp<T>::operator = (U* other)
{
    if (other) ((T*)other)->incStrong(this);
    if (m_ptr) {
        if(m_ptr->decStrong(this) == OBJ_DEC_FREE) {
            delete static_cast<const T*>(m_ptr);
        }
    }
    m_ptr = other;
    return *this;
}

template<typename T>
void sp<T>::force_set(T* other)
{
    other->forceIncStrong(this);
    m_ptr = other;
}

template<typename T>
void sp<T>::clear()
{
    if (m_ptr) {
        //m_ptr->decStrong(this);
        if(m_ptr->decStrong(this) == OBJ_DEC_FREE) {
            delete static_cast<const T*>(m_ptr);
        }
        
        m_ptr = 0;
    }
}

template<typename T>
void sp<T>::set_pointer(T* ptr) {
    m_ptr = ptr;
}

template<typename T>
T* sp<T>::get_pointer(){
    return m_ptr;
}

//template <typename T>
//inline TextOutput& operator<<(TextOutput& to, const sp<T>& val)
//{
//    return printStrongPointer(to, val.get());
//}
#endif
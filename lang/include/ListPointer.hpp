#ifndef __LIST_POINTER_HPP__
#define __LIST_POINTER_HPP__

#include <stdio.h>
#include <stdlib.h>
#include <type_traits>

#include "ListObject.hpp"

namespace obotcha {
//template
template<bool C, typename T, typename U>
class ListPointerChanger;

template<typename T, typename U>
class ListPointerChanger<true, T, U>{
public:
     static T *convert(U *u) {
       if (u) ((T*)u)->incStrong(0);
       return (T*)u;
     }
 };

template<typename T, typename U>
class ListPointerChanger<false, T, U>{
public:
   static T *convert(U *u) {
     T* t = new T(u);
     t->incStrong(0);
     return t;
   }
 };

// ---------------------------------------------------------------------------
#define LIST_COMPARE(_op_)                                           \
inline bool operator _op_ (const lst<T>& o) const {              \
    return m_ptr _op_ o.m_ptr;                                  \
}                                                               \
inline bool operator _op_ (const T* o) const {                  \
    return m_ptr _op_ o;                                        \
}                                                               \
template<typename U>                                            \
inline bool operator _op_ (const lst<U>& o) const {              \
    return m_ptr _op_ o.m_ptr;                                  \
}                                                               \
template<typename U>                                            \
inline bool operator _op_ (const U* o) const {                  \
    return m_ptr _op_ o;                                        \
}                                                               \
// ---------------------------------------------------------------------------

template <typename T>
class lst {

public:
    inline lst() : m_ptr(0) { }

    lst(T* other);
    lst(const lst<T>& other);
    template<typename U> lst(U* other);
    template<typename U> lst(const lst<U>& other);

    ~lst();

    // Assignment

    lst& operator = (T* other);
    lst& operator = (const lst<T>& other);

    template<typename U> lst& operator = (const lst<U>& other);
    template<typename U> lst& operator = (U* other);

    //! lstecial optimization for use by ProcessState (and nobody else).
    void force_set(T* other);

    // Reset

    void clear();

    // Accessors

    inline  T&      operator* () const  { return *m_ptr; }
    inline  T*      operator-> () const { return m_ptr;  }
    inline  T*      get() const         { return m_ptr; }

    // Operators(==)
    inline bool operator == (const lst<T>& o) const {
        if(o.m_ptr == nullptr) {
            if(m_ptr == nullptr) {
                return true;
            }
            return false;
        }

        if(m_ptr == nullptr) {
            if(o.m_ptr == nullptr) {
                return true;
            }

            return false;
        }

        return m_ptr->equals(o.m_ptr);
    }
    
    inline bool operator == (const T* o) const {
        if(o == nullptr) {
            if(m_ptr == nullptr) {
                return true;
            }
            return false;
        }

        if(m_ptr == nullptr) {
            if(o == nullptr) {
                return true;
            }

            return false;
        }

        return m_ptr->equals(o);
    }

    template<typename U>                                            
    inline bool operator == (const lst<U>& o) const {
        if(o.m_ptr == nullptr) {
            if(m_ptr == nullptr) {
                return true;
            }
            return false;
        }

        if(m_ptr == nullptr) {
            if(o.m_ptr == nullptr) {
                return true;
            }

            return false;
        }

        return m_ptr->equals(o.m_ptr);
    }

    template<typename U>
    inline bool operator == (const U* o) const {
        if(o->m_ptr == nullptr) {
            if(o->m_ptr == nullptr) {
                return true;
            }
            return false;
        }

        if(m_ptr == nullptr) {
            if(o == nullptr) {
                return true;
            }

            return false;
        }


        return m_ptr->euqals(o);
    }

    // Operators(!=)
    inline bool operator != (const lst<T>& o) const { 
        if(o.m_ptr == nullptr) {
            if(m_ptr == nullptr) {
                return false;
            }
            return true;
        }

        if(m_ptr == nullptr) {
            if(o.m_ptr == nullptr) {
                return false;
            }

            return true;
        }
        return !m_ptr->equals(o.m_ptr);
    }

    inline bool operator != (const T* o) const {
        if(o == nullptr) {
            if(m_ptr == nullptr) {
                return false;
            }
            return true;
        }

        if(m_ptr == nullptr) {
            if(o == nullptr) {
                return false;
            }

            return true;
        }
        return !m_ptr->equals(o);
    }

    template<typename U>                                            
    inline bool operator != (const lst<U>& o) const {
        if(o.m_ptr == nullptr) {
            if(m_ptr == nullptr) {
                return false;
            }
            return true;
        }

        if(m_ptr == nullptr) {
            if(o.m_ptr == nullptr) {
                return false;
            }

            return true;
        }
        return !m_ptr->equals(o.m_ptr);
    }

    template<typename U>
    inline bool operator != (const U* o) const {
        if(o->m_ptr == nullptr) {
            if(m_ptr == nullptr) {
                return false;
            }
            return true;
        }

        if(m_ptr == nullptr) {
            if(o == nullptr) {
                return false;
            }

            return true;
        }
        return !m_ptr->euqals(o);
    }

    //LIST_COMPARE(==)
    //LIST_COMPARE(!=)
    LIST_COMPARE(>)
    LIST_COMPARE(<)
    LIST_COMPARE(<=)
    LIST_COMPARE(>=)

    void set_pointer(T* ptr);

    void remove_pointer();
    
    T* get_pointer();

    T* m_ptr;

public:
    //add for list
    auto operator[] (int i) ->decltype((*m_ptr)[0])
    { 
        return (*m_ptr)[i];
    }
};


template<typename T>
lst<T>::lst(T* other)
: m_ptr(other)
  {
    if (other) other->incStrong(this);
  }

template<typename T>
lst<T>::lst(const lst<T>& other)
: m_ptr(other.m_ptr)
  {
    if (m_ptr) m_ptr->incStrong(this);
  }

template<typename T> template<typename U>
lst<T>::lst(U* other) 
{
    //m_ptr = other;
    //if (other) ((T*)other)->incStrong(this);
    m_ptr = ListPointerChanger<std::is_base_of<T,U>::value == 1,T,U>::convert(other);
}

template<typename T> template<typename U>
lst<T>::lst(const lst<U>& other)
//: m_ptr(dynamic_cast<T*>(other.m_ptr))
: m_ptr(other.m_ptr)
{
    if (m_ptr) m_ptr->incStrong(this);
}

template<typename T>
lst<T>::~lst()
{
    if (m_ptr) {
        if(m_ptr->decStrong(this) == OBJ_DEC_FREE) {
            delete m_ptr;
        }
    }
}

template<typename T>
lst<T>& lst<T>::operator = (const lst<T>& other) {
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
lst<T>& lst<T>::operator = (T* other)
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
lst<T>& lst<T>::operator = (const lst<U>& other)
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
lst<T>& lst<T>::operator = (U* other)
{
    if (m_ptr) {
        if(m_ptr->decStrong(this) == OBJ_DEC_FREE) {
            delete static_cast<const T*>(m_ptr);
        }
    }    
    m_ptr = ListPointerChanger<std::is_base_of<T,U>::value == 1,T,U>::convert(other);
    return *this;
}

template<typename T>
void lst<T>::force_set(T* other)
{
    other->forceIncStrong(this);
    m_ptr = other;
}

template<typename T>
void lst<T>::clear()
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
void lst<T>::set_pointer(T* ptr) {
    if(m_ptr) {
        if(m_ptr->decStrong(this) == OBJ_DEC_FREE) {
            delete static_cast<const T*>(m_ptr);
        }
    }
    
    m_ptr = ptr;
    if(m_ptr != nullptr) {
        m_ptr->incStrong(0);
    }
}

template<typename T>
void lst<T>::remove_pointer() {
    if(m_ptr) {
        if(m_ptr->decStrong(this) == OBJ_DEC_FREE) {
            delete static_cast<const T*>(m_ptr);
        }
    }
    
    m_ptr = nullptr;
}

template<typename T>
T* lst<T>::get_pointer(){
    return m_ptr;
}

#define tp(X) _##X
template<typename X,typename V>
lst<X> transform_cast(lst<V> t) {
    lst<X> value;
    
    value.set_pointer(dynamic_cast<X *>(t.m_ptr));
    return value;
}

}
#endif
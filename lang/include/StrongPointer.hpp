#ifndef __OBOTCHA_STRONG_POINTER_HPP__
#define __OBOTCHA_STRONG_POINTER_HPP__

#include <stdio.h>
#include <stdlib.h>
#include <type_traits>

namespace obotcha {

#define POINTER_DEC_FREE 0  //same as Object::OBJ_DEC_FREE
#define POINTER_DEC_NO_FREE 1//same as Object::OBJ_DEC_NO_FREE

//template
template<bool C, typename T, typename U>
class PointerChanger;

template<typename T, typename U>
class PointerChanger<true, T, U>{
public:
     static T *convert(U *u) {
       if (u) ((T*)u)->incStrong(0);
       return (T*)u;
     }
 };

template<typename T, typename U>
class PointerChanger<false, T, U>{
public:
   static T *convert(U *u) {
     T* t = new T(u);
     t->incStrong(0);
     return t;
   }
 };

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
    inline bool operator == (const sp<U>& o) const {
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
            if(m_ptr == nullptr) {
                return true;
            }
            return false;
        }

        if(m_ptr == nullptr) {
            if(o->m_ptr == nullptr) {
                return true;
            }

            return false;
        }


        return m_ptr->euqals(o);
    }


    // Operators(!=)
    inline bool operator != (const sp<T>& o) const { 
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
    inline bool operator != (const sp<U>& o) const {
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
            if(o->m_ptr == nullptr) {
                return false;
            }

            return true;
        }
        return !m_ptr->euqals(o);
    }

    auto &operator[] (int index) { 
        return (*this->m_ptr)[index];
    }

    template<typename Q>
    auto &operator[] (Q key) {
        return (*this->m_ptr)[key];
    }

    //COMPARE(==)
    //COMPARE(!=)
    COMPARE(>)
    COMPARE(<)
    COMPARE(<=)
    COMPARE(>=)

    void set_pointer(T* ptr);
    void remove_pointer(){};
    
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
sp<T>::sp(U* other) 
{
    //m_ptr = other;
    //if (other) ((T*)other)->incStrong(this);
    m_ptr = PointerChanger<std::is_base_of<T,U>::value == 1,T,U>::convert(other);
}

template<typename T> template<typename U>
sp<T>::sp(const sp<U>& other)
//: m_ptr(dynamic_cast<T*>(other.m_ptr))
: m_ptr(other.m_ptr)
{
    if (m_ptr) m_ptr->incStrong(this);
}

template<typename T>
sp<T>::~sp()
{
    if (m_ptr) {
        if(m_ptr->decStrong(this) == POINTER_DEC_FREE) {
            delete m_ptr;
        }
    }
}

template<typename T>
sp<T>& sp<T>::operator = (const sp<T>& other) {
    T* otherPtr(other.m_ptr);
    if (otherPtr) otherPtr->incStrong(this);
    if (m_ptr) {
        if(m_ptr->decStrong(this) == POINTER_DEC_FREE) {
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
        if(m_ptr->decStrong(this) == POINTER_DEC_FREE) {
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
        if(m_ptr->decStrong(this) == POINTER_DEC_FREE) {
            delete static_cast<const T*>(m_ptr);
        }
    }
    m_ptr = otherPtr;
    return *this;
}

template<typename T> template<typename U>
sp<T>& sp<T>::operator = (U* other)
{
    if (m_ptr) {
        if(m_ptr->decStrong(this) == POINTER_DEC_FREE) {
            delete static_cast<const T*>(m_ptr);
        }
    }
    m_ptr = PointerChanger<std::is_base_of<T,U>::value == 1,T,U>::convert(other);
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
        if(m_ptr->decStrong(this) == POINTER_DEC_FREE) {
            delete static_cast<const T*>(m_ptr);
        }
        
        m_ptr = 0;
    }
}

template<typename T>
void sp<T>::set_pointer(T* ptr) {
    if(m_ptr) {
        if(m_ptr->decStrong(this) == POINTER_DEC_FREE) {
            delete static_cast<const T*>(m_ptr);
        }
    }
    
    m_ptr = ptr;
    if(m_ptr != nullptr) {
        m_ptr->incStrong(0);
    }
}

template<typename T>
T* sp<T>::get_pointer(){
    return m_ptr;
}

}
#endif
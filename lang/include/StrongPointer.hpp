#ifndef __OBOTCHA_STRONG_POINTER_HPP__
#define __OBOTCHA_STRONG_POINTER_HPP__

#include <stdio.h>
#include <stdlib.h>
#include <type_traits>

namespace obotcha {

#define POINTER_DEC_FREE 0  
#define POINTER_DEC_NO_FREE 1

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

#if 0
template<typename T, typename U>
class PointerChanger<false, T, U>{
public:
   static T *convert(U *u) {
     //TODO
     T* t = new T(u);
     t->incStrong(0);
     return t;
   }
};
#endif

template <typename T>
class sp {

public:
    inline sp() : m_ptr(0) { }

    sp(T* other): m_ptr(other) {
        if (other) {
            other->incStrong(this);
        }
    }

    sp(const sp<T>& other): sp<T>(other.m_ptr){
        //do nothing
    }

    template<typename U> 
    sp(U* other) {
        m_ptr = PointerChanger<std::is_base_of<T,U>::value == 1,T,U>::convert(other);
    }

    template<typename U> sp(const sp<U>& other):sp<T>(other.m_ptr) {
        //do nothing
    }

    static constexpr int isReflect() {
        return T::__isReflected;
    }

    ~sp() {
        if (m_ptr) {
            if(m_ptr->decStrong(this) == POINTER_DEC_FREE) {
                delete m_ptr;
            }
        }
    }

    sp& operator = (T* other) {
        if (other) other->incStrong(this);
        if (m_ptr) {
            if(m_ptr->decStrong(this) == POINTER_DEC_FREE) {
                delete static_cast<const T*>(m_ptr);
            }   
        }
        m_ptr = other;

        return *this;
    }

    sp& operator = (const sp<T>& other) {
        *this = other.m_ptr;
        return *this;
    }

    template<typename U> sp& operator = (U* other) {
        if (m_ptr) {
            if(m_ptr->decStrong(this) == POINTER_DEC_FREE) {
                delete static_cast<const T*>(m_ptr);
            }
        }
        m_ptr = PointerChanger<std::is_base_of<T,U>::value == 1,T,U>::convert(other);
        return *this;
    }

    template<typename U> 
    sp& operator = (const sp<U>& other) {
        *this = other.m_ptr;
        return *this;
    }

    void clear() {
        if (m_ptr) {
            if(m_ptr->decStrong(this) == POINTER_DEC_FREE) {
                delete static_cast<const T*>(m_ptr);
            }
            
            m_ptr = nullptr;
        }
    }

    // Accessors

    inline  T&      operator* () const  { return *m_ptr; }
    inline  T*      operator-> () const { return m_ptr;  }

    // Operators(==)
    inline bool operator == (const sp<T>& o) const {
        if((void *)m_ptr == (void *)o.m_ptr) {
            return true;
        }

        if(m_ptr != nullptr && o.m_ptr!= nullptr) {
            return m_ptr->equals(o.m_ptr);
        }

        return false;
    }
    
    inline bool operator == (const T* o) const {
        if((void *)m_ptr == (void *)o) {
            return true;
        }

        if(m_ptr != nullptr && o != nullptr) {
            return m_ptr->equals(o);
        }

        return false;
    }

    template<typename U>                                            
    inline bool operator == (const sp<U>& o) const {
        if((void *)m_ptr == (void *)o.m_ptr) {
            return true;
        }
        
        if(m_ptr != nullptr && o.m_ptr != nullptr) {
            return m_ptr->equals(o.m_ptr);
        }

        return false;
    }


    template<typename U>
    inline bool operator == (const U* o) const {
        if((void *)m_ptr == (void *)o) {
            return true;
        }

        if(m_ptr != nullptr && o != nullptr) {
            return m_ptr->equals(o);
        }

        return false;
    }

    // Operators(!=)
    inline bool operator != (const sp<T>& o) const {
        return !(*this == o);
    }

    inline bool operator != (const T* o) const {
        return !(*this == o);
    }

    template<typename U>                                            
    inline bool operator != (const sp<U>& o) const {
        return !(*this == o);
    }

    template<typename U>
    inline bool operator != (const U* o) const {
        return !(*this == o);
    }

    auto &operator[] (int index) { 
        return (*this->m_ptr)[index];
    }

    template<typename Q>
    auto &operator[] (Q key) {
        return (*this->m_ptr)[key];
    }

    void set_pointer(T* ptr) {
        if(m_ptr) {
            if(m_ptr->decStrong(this) == POINTER_DEC_FREE) {
                delete static_cast<const T*>(m_ptr);
            }
        }

        if(ptr != nullptr) {
            ptr->incStrong(0);
        }
        m_ptr = ptr;
    }

    T* get_pointer() const{
        return m_ptr;
    }

    T* m_ptr;
};

}
#endif
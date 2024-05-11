#ifndef __OBOTCHA_STRONG_POINTER_HPP__
#define __OBOTCHA_STRONG_POINTER_HPP__

#include <stdio.h>
#include <stdlib.h>
#include <type_traits>
#include <utility>

namespace obotcha {

// template
template <bool C, typename T, typename U> class PointerChanger;

template <typename T, typename U> class PointerChanger<true, T, U> {
public:
    static T *convert(U *u) {
        if (u) ((T *)u)->incStrong(nullptr);
        return (T *)u;
    }
};

template <typename T, typename U> class PointerChanger<false, T, U> {
public:
    static T *convert(U *u) {
        T *t = new T(u);
        t->incStrong(nullptr);
        return t;
    }
};

template <typename T> class sp {

public:
    template <typename... Args>              
        static sp<T> New(Args &&... args) {
        T *p = new T(std::forward<Args>(args)...);
        p->__ReflectInit();
        return sp<T>(p);
    }

    inline sp() : m_ptr(nullptr) {}

    sp(T *other) : m_ptr(other) {
        if (other) other->incStrong(this);
    }

    sp(const sp<T> &other) : sp<T>(other.m_ptr) {
        // do nothing
    }

    template <typename U> 
    sp(U *other) {
        m_ptr = PointerChanger<std::is_base_of<T, U>::value == 1, T, U>
                ::convert(other);
    }

    template <typename U> sp(const sp<U> &other) : sp<T>(other.m_ptr) {
        // do nothing
    }

    static constexpr int isReflect() { 
        return T::__isReflected; 
    }

    ~sp() {
        if (m_ptr) m_ptr->decStrong(this);
    }

    sp &operator=(T *other) {
        if (other) other->incStrong(this);
        if (m_ptr) m_ptr->decStrong(this);
        m_ptr = other;
        return *this;
    }

    sp &operator=(const sp<T> &other) {
        *this = other.m_ptr;
        return *this;
    }

    template <typename U> sp &operator=(U *other) {
        if (m_ptr) m_ptr->decStrong(this);
        m_ptr = PointerChanger<std::is_base_of<T, U>::value == 1, T, U>
                ::convert(other);
        return *this;
    }

    template <typename U> sp &operator=(const sp<U> &other) {
        *this = other.m_ptr;
        return *this;
    }

    void clear() {
        T* oldPtr(*const_cast<T* volatile*>(&m_ptr));
        if (oldPtr) {
            oldPtr->decStrong(this);
            m_ptr = nullptr;
        }
    }

    // Accessors
    inline T &operator*() const { return *m_ptr; }
    inline T *operator->() const { return m_ptr; }

    inline bool operator==(const sp<T> &o) const {
        if ((void *)m_ptr == (void *)o.m_ptr) {       
            return true;                          
        }

        if(m_ptr != nullptr) {
            return o.m_ptr == nullptr? false:m_ptr->equals(o);
        }

        return false;
    }

    template <typename U> bool operator==(const sp<U> &other) {
        if((void *)m_ptr == (void *)other.m_ptr) {
            return true;
        }

        if(m_ptr != nullptr) {
            T* t = dynamic_cast<T*>(other.m_ptr);
            return m_ptr == t || m_ptr->equals(t);
        }
        return false;
    }


    // Operators(!=)
    inline bool operator!=(const sp<T> &o) const { 
        return !(*this == o); 
    }

    template <typename U> bool operator!=(const sp<U> &other) {
        if((void *)m_ptr == (void *)other.m_ptr) {
            return false;
        }

        if(m_ptr == nullptr && other.m_ptr != nullptr) {
            return true;
        }

        T* t = dynamic_cast<T*>(other.m_ptr);
        return m_ptr != t && !m_ptr->equals(t);
    }

    auto &operator[](size_t index) { 
        return (*this->m_ptr)[index];
    }

    template <typename Q> auto &operator[](Q key) {
        return (*this->m_ptr)[key];
    }

    void set_pointer(T *ptr) {
        if (m_ptr) m_ptr->decStrong(this);
        if (ptr != nullptr) ptr->incStrong(nullptr);
        m_ptr = ptr;
    }

    T *get_pointer() const { 
        return m_ptr; 
    }

    T *m_ptr = nullptr;
};

} // namespace obotcha
#endif
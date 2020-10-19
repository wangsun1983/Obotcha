#ifndef __OBOTCHA_ATOMIC_HPP__
#define __OBOTCHA_ATOMIC_HPP__

#include <stdio.h>
#include <atomic>

#include "Log.hpp"

namespace obotcha {

template<typename T>
class Atomic {
public:
    Atomic():value(0) {
        //TODO
    }

    Atomic(T v):value(v) {

    }

    Atomic(const Atomic<T>&v):value(0) {
        LOG(ERROR)<<"Atomic not support";
    }

    void operator++(T) {
        value++;
    }

    void operator--(T) {
        value--;
    }

    Atomic<T> operator+=(T v) {
        value += v;
        return *this;
    }

    Atomic<T> operator-=(T v) {
        value -= v;
        return *this;
    }

    Atomic<T> operator|=(T v) {
        value |= v;
        return *this;
    }

    Atomic<T> operator&=(T v) {
        value &= v;
        return *this;
    }

    Atomic<T> operator-(T v) {
        Atomic<T> vv(0);
        vv = (value - v);
        return vv;
    }

    Atomic<T> operator+(T v) {
        Atomic<T> vv(0);
        vv = (value + v);
        return vv;
    }

    Atomic<T> operator|(T v) {
        Atomic<T> vv(0);
        vv = (value|v);
        return vv;
    }

    Atomic<T> operator&(T v) {
        Atomic<T> vv(0);
        vv = (value&v);
        return vv;
    }

    void operator=(T v) {
        value = v;
    }

    Atomic<T>* operator->() {
        return this;
    }

    void operator=(Atomic<T> v) {
        value.store(v.value);
    }

    bool operator==(int v) {
        return value == v;
    }

    bool operator !=(int v) {
        return value != v;
    }

    T get() {
        return value.load(memory_order_relaxed);
    }

private:
    std::atomic<T> value;
};

}
#endif
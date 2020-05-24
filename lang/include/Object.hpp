#ifndef __OBOTCHA_OBJECT_H__
#define __OBOTCHA_OBJECT_H__

#include <stdint.h>
#include <sys/types.h>
#include <stdlib.h>
#include <utility>
#include <stdio.h>
#include <typeinfo>

#define OBJ_DEC_FREE 0
#define OBJ_DEC_NO_FREE 1

namespace obotcha {

class Object
{
public:
    Object() : mCount(0) { }

    inline void incStrong(__attribute__((unused)) const void* id) {
        __sync_fetch_and_add(&mCount, 1);
        return;
    }

    inline int decStrong(__attribute__((unused)) const void* id) {
        if (__sync_fetch_and_sub(&mCount, 1) == 1) {
            //delete static_cast<const T*>(this);
            return OBJ_DEC_FREE;
        }
        return OBJ_DEC_NO_FREE;
    }

    //! DEBUGGING ONLY: Get current strong ref count.
    inline int32_t getStrongCount() {
        return mCount;
    }

    inline virtual bool equals(const Object *m) {
        return this == m;
    }

    inline virtual bool equals(Object &m) {
        return this == &m;
    }

    

protected:
    inline virtual ~Object() {
    }

private:
    mutable volatile int32_t mCount;

};

}

#define MAKE_FUNCTION_0(Y) \
template<typename... Args>\
sp<_##Y> create##Y(Args&&... args)\
{\
    sp<_##Y> ret = new _##Y(std::forward<Args>(args)...);\
    return ret;\
}\

#define MAKE_FUNCTION_1(Y) \
template<typename T,typename... Args>\
sp<_##Y<T>> create##Y(Args&&... args)\
{\
    sp<_##Y<T>> ret = new _##Y<T>(std::forward<Args>(args)...);\
    return ret;\
}\

#define MAKE_FUNCTION_2(Y) \
template<typename T,typename U,typename... Args>\
sp<_##Y<T,U>> create##Y(Args&&... args)\
{\
    sp<_##Y<T,U>> ret = new _##Y<T,U>(std::forward<Args>(args)...);\
    return ret;\
}\


#define CLASS_PRE_DEF_0(YY) class _##YY
#define CLASS_PRE_DEF_1(YY) template<typename X>class _##YY
#define CLASS_PRE_DEF_2(YY) template<typename X,typename Z>class _##YY

#define TYPE_DEF_0(YY) typedef sp<_##YY> YY
#define TYPE_DEF_1(YY) \
template<typename UU> \
using YY = sp<_##YY<UU>>; \

#define TYPE_DEF_2(YY) \
template<typename UU,typename VV> \
using YY = sp<_##YY<UU,VV>>; \


#define TEPMLATE_DECLARE_0
#define TEPMLATE_DECLARE_1 template<typename T>
#define TEPMLATE_DECLARE_2 template<typename T,typename U>


#define DECLARE_CLASS(Y,U) \
CLASS_PRE_DEF_##U(Y); \
TYPE_DEF_##U(Y); \
MAKE_FUNCTION_##U(Y) \
TEPMLATE_DECLARE_##U \
class _##Y: virtual public Object\

#define DECLARE_SIMPLE_CLASS(Y) DECLARE_CLASS(Y,0)

#define CONSTRUCT(X) _##X

#define DESTRUCT(X) ~_##X

#define EXTENDS(X) ,virtual public _##X

#define IMPLEMENTS(X) ,virtual public _##X

#define CLASS(X) _##X

#define CONSTRUCT_IMPLEMENT(X) CLASS(##X)::CONSTRUCT(##X)

#define DESTRUCT_IMPLEMENT(X) CLASS(##X)::DESTRUCT(##X)

#define st(Y) _##Y

#define InstanceOf(X,Y) typeid(*X.get_pointer()) == typeid(_##Y)


#endif

#ifndef __LIST_LIST_OBJECT_H__
#define __LIST_LIST_OBJECT_H__

#include <stdint.h>
#include <sys/types.h>
#include <stdlib.h>
#include <utility>
#include <stdio.h>
#include <typeinfo>

#define LIST_OBJ_DEC_FREE 0
#define LIST_OBJ_DEC_NO_FREE 1

namespace obotcha {

class ListObject
{
public:
    ListObject() : mCount(0) { }

    inline void incStrong(__attribute__((unused)) const void* id) {
        __sync_fetch_and_add(&mCount, 1);
    }

    inline int decStrong(__attribute__((unused)) const void* id) {
        if (__sync_fetch_and_sub(&mCount, 1) == 1) {
            //delete static_cast<const T*>(this);
            return LIST_OBJ_DEC_FREE;
        }
        return LIST_OBJ_DEC_NO_FREE;
    }

    //! DEBUGGING ONLY: Get current strong ref count.
    inline int32_t getStrongCount() {
        return mCount;
    }

    inline virtual bool equals(const ListObject *m) {
        return this == m;
    }

    inline virtual bool equals(ListObject &m) {
        return this == &m;
    }

protected:
    inline virtual ~ListObject() {
    }

private:
    mutable volatile int32_t mCount;

};

}

#define MAKE_LIST_FUNCTION_0(Y) \
template<typename... Args>\
lst<_##Y> create##Y(Args&&... args)\
{\
    lst<_##Y> ret = new _##Y(std::forward<Args>(args)...);\
    return ret;\
}\

#define MAKE_LIST_FUNCTION_1(Y) \
template<typename T,typename... Args>\
lst<_##Y<T>> create##Y(Args&&... args)\
{\
    lst<_##Y<T>> ret = new _##Y<T>(std::forward<Args>(args)...);\
    return ret;\
}\

#define MAKE_LIST_FUNCTION_2(Y) \
template<typename T,typename U,typename... Args>\
lst<_##Y<T,U>> create##Y(Args&&... args)\
{\
    lst<_##Y<T,U>> ret = new _##Y<T,U>(std::forward<Args>(args)...);\
    return ret;\
}\


#define LIST_CLASS_FUNCTION_DEF_0(YY) class _##YY
#define LIST_CLASS_FUNCTION_DEF_1(YY) template<typename X>class _##YY
#define LIST_CLASS_FUNCTION_DEF_2(YY) template<typename X,typename Z>class _##YY

#define LIST_TYPE_DEF_0(YY) typedef lst<_##YY> YY
#define LIST_TYPE_DEF_1(YY) \
template<typename UU> \
using YY = lst<_##YY<UU>>; \

#define LIST_TYPE_DEF_2(YY) \
template<typename UU,typename VV> \
using YY = lst<_##YY<UU,VV>>; \


#define LIST_TEPMLATE_DECLARE_0
#define LIST_TEPMLATE_DECLARE_1 template<typename T>
#define LIST_TEPMLATE_DECLARE_2 template<typename T,typename U>


#define DECLARE_LIST(Y,U) \
LIST_CLASS_FUNCTION_DEF_##U(Y); \
LIST_TYPE_DEF_##U(Y); \
MAKE_LIST_FUNCTION_##U(Y) \
LIST_TEPMLATE_DECLARE_##U \
class _##Y: virtual public ListObject\


#endif

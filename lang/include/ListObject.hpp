#ifndef __OBOTCHA_LIST_LIST_OBJECT_H__
#define __OBOTCHA_LIST_LIST_OBJECT_H__

#include <stdint.h>
#include <sys/types.h>
#include <stdlib.h>
#include <utility>
#include <stdio.h>
#include <typeinfo>

#define LIST_OBJ_DEC_FREE 0
#define LIST_OBJ_DEC_NO_FREE 1

namespace obotcha {

#define MAKE_LIST_FUNCTION_0(Y) \
template<typename... Args>\
__lst<_##Y> create##Y(Args&&... args)\
{\
    __lst<_##Y> ret = new _##Y(std::forward<Args>(args)...);\
    return ret;\
}\

#define MAKE_LIST_FUNCTION_BYTEARRAY(Y) \
template<typename... Args>\
__btarr<_##Y> create##Y(Args&&... args)\
{\
    __btarr<_##Y> ret = new _##Y(std::forward<Args>(args)...);\
    return ret;\
}\

#define MAKE_LIST_FUNCTION_1(Y) \
template<typename T,typename... Args>\
__lst<_##Y<T>> create##Y(Args&&... args)\
{\
    __lst<_##Y<T>> ret = new _##Y<T>(std::forward<Args>(args)...);\
    return ret;\
}\

#define MAKE_LIST_FUNCTION_2(Y) \
template<typename T,typename U,typename... Args>\
__lst<_##Y<T,U>> create##Y(Args&&... args)\
{\
    __lst<_##Y<T,U>> ret = new _##Y<T,U>(std::forward<Args>(args)...);\
    return ret;\
}\

#define LIST_CLASS_FUNCTION_DEF_0(YY) class _##YY
#define LIST_CLASS_FUNCTION_DEF_1(YY) template<typename X>class _##YY
#define LIST_CLASS_FUNCTION_DEF_2(YY) template<typename X,typename Z>class _##YY

#define LIST_TYPE_DEF_0(YY) typedef __lst<_##YY> YY
#define LIST_TYPE_DEF_1(YY) \
template<typename UU> \
using YY = __lst<_##YY<UU>>; \

#define LIST_TYPE_DEF_BYTEARRY(YY) typedef __btarr<_##YY> YY

#define LIST_TYPE_DEF_2(YY) \
template<typename UU,typename VV> \
using YY = __lst<_##YY<UU,VV>>; \


#define LIST_TEPMLATE_DECLARE_0
#define LIST_TEPMLATE_DECLARE_1 template<typename T>
#define LIST_TEPMLATE_DECLARE_2 template<typename T,typename U>

#define DECLARE_LIST(Y,U) \
LIST_CLASS_FUNCTION_DEF_##U(Y); \
LIST_TYPE_DEF_##U(Y); \
MAKE_LIST_FUNCTION_##U(Y) \
LIST_TEPMLATE_DECLARE_##U \
class _##Y: virtual public Object\

#define DECLARE_BYTE_ARRAY(Y) \
LIST_CLASS_FUNCTION_DEF_0(Y); \
LIST_TYPE_DEF_BYTEARRY(Y); \
MAKE_LIST_FUNCTION_BYTEARRAY(Y) \
LIST_TEPMLATE_DECLARE_0 \
class _##Y: virtual public Object\

}
#endif

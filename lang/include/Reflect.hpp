#ifndef __OBOTCHA_REFLECT_HPP__
#define __OBOTCHA_REFLECT_HPP__

#include <map>
#include <functional>
#include <sstream>  
#include <iostream>

#include "Field.hpp"
#include "HashMap.hpp"
#include "StrongPointer.hpp"
#include "ArrayList.hpp"
#include "ReflectUtil.hpp"

#define ARG_0(\
        N, ...) N

#define ARG_1(\
         _1,N, ...) N

#define ARG_2(\
         _1,_2,N, ...) N

#define ARG_3(\
         _1,_2,_3,N, ...) N

#define ARG_4(\
         _1,_2,_3,_4,N, ...) N

#define ARG_5(\
         _1,_2,_3,_4,_5,N, ...) N                  

#define ARG_6(\
         _1,_2,_3,_4,_5,_6,N, ...) N  

#define ARG_7(\
         _1,_2,_3,_4,_5,_6,_7,N, ...) N  

#define ARG_8(\
         _1,_2,_3,_4,_5,_6,_7,_8,N, ...) N  

#define ARG_9(\
         _1,_2,_3,_4,_5,_6,_7,_8,_9,N, ...) N  

#define ARG_10(\
         _1,_2,_3,_4,_5,_6,_7,_8,_9,_10,N, ...) N  

#define ARG_11(\
         _1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,N, ...) N  

#define ARG_12(\
         _1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,N, ...) N  

#define ARG_13(\
         _1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,N, ...) N 

#define ARG_14(\
         _1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,N, ...) N 

#define ARG_15(\
         _1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,N, ...) N 

#define RSEQ_N() \
         119,118,117,116,115,114,113,112,111,110,\
         109,108,107,106,105,104,103,102,101,100,\
         99,98,97,96,95,94,93,92,91,90, \
         89,88,87,86,85,84,83,82,81,80, \
         79,78,77,76,75,74,73,72,71,70, \
         69,68,67,66,65,64,63,62,61,60, \
         59,58,57,56,55,54,53,52,51,50, \
         49,48,47,46,45,44,43,42,41,40, \
         39,38,37,36,35,34,33,32,31,30, \
         29,28,27,26,25,24,23,22,21,20, \
         19,18,17,16,15,14,13,12,11,10, \
         9,8,7,6,5,4,3,2,1,0

#define ARG_N(\
         _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, \
         _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, \
         _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, \
         _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, \
         _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, \
         _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, \
         _61, _62, _63, _64, _65, _66, _67, _68, _69, _70, \
         _71, _72, _73, _74, _75, _76, _77, _78, _79, _80, \
         _81, _82, _83, _84, _85, _86, _87, _88, _89, _90, \
         _91, _92, _93, _94, _95, _96, _97, _98, _99, _100, \
         _101, _102, _103, _104, _105, _106, _107, _108, _109, _110, \
         _111, _112, _113, _114, _115, _116, _117, _118, _119, N, ...) N

#define MARCO_EXPAND(...)                 __VA_ARGS__
#define GET_ARG_COUNT_INNER(...)    MARCO_EXPAND(ARG_N(__VA_ARGS__))
#define GET_ARG_COUNT(...)          GET_ARG_COUNT_INNER(__VA_ARGS__, RSEQ_N())

#define DO_IMPLE_SET_VALUE(CLASS, ...) \
    IMPLE_SET_VALUE_INTERFACE(CLASS,GET_ARG_COUNT(__VA_ARGS__),__VA_ARGS__)

#define IMPLE_SET_VALUE_INTERFACE_1(CLASS,COUNT,...) IMPLE_SET_VALUE_1_INTERFACE_INTER(CLASS,COUNT,__VA_ARGS__)
#define IMPLE_SET_VALUE_1_INTERFACE_INTER(CLASS,COUNT, ...) 

#define IMPLE_SET_VALUE_INTERFACE_2(CLASS,COUNT,MEMBER, ...) IMPLE_SET_VALUE_2_INTERFACE_INTER(CLASS,COUNT,MEMBER,__VA_ARGS__)
#define IMPLE_SET_VALUE_2_INTERFACE_INTER(CLASS,COUNT,MEMBER, ...) IMPLE_SET_VALUE_2_INTERFACE_INTER2(CLASS,COUNT,MEMBER,__VA_ARGS__)
#define IMPLE_SET_VALUE_2_INTERFACE_INTER2(CLASS,COUNT,MEMBER, ...) IMPLE_SET_VALUE(CLASS,COUNT,MEMBER,__VA_ARGS__)

#define IMPLE_SET_VALUE_INTERFACE(CLASS,COUNT,MEMBER, ...) IMPLE_SET_VALUE_INTERFACE_INTER(CLASS,COUNT,MEMBER,__VA_ARGS__)
#define IMPLE_SET_VALUE_INTERFACE_INTER(CLASS,COUNT,MEMBER, ...) IMPLE_SET_VALUE_INTERFACE_INTER2(CLASS,COUNT,MEMBER,__VA_ARGS__)
#define IMPLE_SET_VALUE_INTERFACE_INTER2(CLASS,COUNT,MEMBER, ...) IMPLE_SET_VALUE(CLASS,COUNT,MEMBER,__VA_ARGS__)

//function
#define IMPLE_SET_VALUE_1(CLASS,MEMBER) \
    void __ReflectSet##MEMBER(decltype(MEMBER) v) { \
        MEMBER = v;\
    }\
    decltype(MEMBER) __ReflectGet##MEMBER() {\
        return MEMBER;\
    }\
    void __ReflectCreate##MEMBER() {\
        st(ReflectUtil)::createObject(MEMBER);\
    }\
    sp<_Object> __ReflectCreateListMember##MEMBER() {\
        return genArrayListData(MEMBER);\
    }\
    sp<_Object> __ReflectGetListItem##MEMBER(int index) {\
        return getArrayListItem(MEMBER,index);\
    }\
    int __ReflectGetListSize##MEMBER() {\
        return __getListSize(MEMBER);\
    }\

#define IMPLE_SET_VALUE_2(CLASS,M1,M2) \
    IMPLE_SET_VALUE_1(CLASS,M1) \
    IMPLE_SET_VALUE_1(CLASS,M2)

#define IMPLE_SET_VALUE_3(CLASS,M1,M2,M3) \
    IMPLE_SET_VALUE_2(CLASS,M1,M2) \
    IMPLE_SET_VALUE_1(CLASS,M3)

#define IMPLE_SET_VALUE_4(CLASS,M1,M2,M3,M4) \
    IMPLE_SET_VALUE_3(CLASS,M1,M2,M3) \
    IMPLE_SET_VALUE_1(CLASS,M4)

#define IMPLE_SET_VALUE_5(CLASS,M1,M2,M3,M4,M5) \
    IMPLE_SET_VALUE_4(CLASS,M1,M2,M3,M4) \
    IMPLE_SET_VALUE_1(CLASS,M5)    

#define IMPLE_SET_VALUE_6(CLASS,M1,M2,M3,M4,M5,M6) \
    IMPLE_SET_VALUE_5(CLASS,M1,M2,M3,M4,M5) \
    IMPLE_SET_VALUE_1(CLASS,M6) 

#define IMPLE_SET_VALUE_7(CLASS,M1,M2,M3,M4,M5,M6,M7) \
    IMPLE_SET_VALUE_6(CLASS,M1,M2,M3,M4,M5,M6) \
    IMPLE_SET_VALUE_1(CLASS,M7)

#define IMPLE_SET_VALUE_8(CLASS,M1,M2,M3,M4,M5,M6,M7,M8) \
    IMPLE_SET_VALUE_7(CLASS,M1,M2,M3,M4,M5,M6,M7) \
    IMPLE_SET_VALUE_1(CLASS,M8)

#define IMPLE_SET_VALUE_9(CLASS,M1,M2,M3,M4,M5,M6,M7,M8,M9) \
    IMPLE_SET_VALUE_8(CLASS,M1,M2,M3,M4,M5,M6,M7,M8) \
    IMPLE_SET_VALUE_1(CLASS,M9)

#define IMPLE_SET_VALUE_10(CLASS,M1,M2,M3,M4,M5,M6,M7,M8,M9,M10) \
    IMPLE_SET_VALUE_9(CLASS,M1,M2,M3,M4,M5,M6,M7,M8,M9) \
    IMPLE_SET_VALUE_1(CLASS,M10)

#define IMPLE_SET_VALUE_11(CLASS,M1,M2,M3,M4,M5,M6,M7,M8,M9,M10,M11) \
    IMPLE_SET_VALUE_10(CLASS,M1,M2,M3,M4,M5,M6,M7,M8,M9,M10) \
    IMPLE_SET_VALUE_1(CLASS,M11)

#define IMPLE_SET_VALUE_12(CLASS,M1,M2,M3,M4,M5,M6,M7,M8,M9,M10,M11,M12) \
    IMPLE_SET_VALUE_11(CLASS,M1,M2,M3,M4,M5,M6,M7,M8,M9,M10,M11) \
    IMPLE_SET_VALUE_1(CLASS,M12)

#define IMPLE_SET_VALUE_13(CLASS,M1,M2,M3,M4,M5,M6,M7,M8,M9,M10,M11,M12,M13) \
    IMPLE_SET_VALUE_12(CLASS,M1,M2,M3,M4,M5,M6,M7,M8,M9,M10,M11,M12) \
    IMPLE_SET_VALUE_1(CLASS,M13)

#define IMPLE_SET_VALUE_14(CLASS,M1,M2,M3,M4,M5,M6,M7,M8,M9,M10,M11,M12,M13,M14) \
    IMPLE_SET_VALUE_13(CLASS,M1,M2,M3,M4,M5,M6,M7,M8,M9,M10,M11,M12,M13) \
    IMPLE_SET_VALUE_1(CLASS,M14)

#define IMPLE_SET_VALUE_15(CLASS,M1,M2,M3,M4,M5,M6,M7,M8,M9,M10,M11,M12,M13,M14,M15) \
    IMPLE_SET_VALUE_14(CLASS,M1,M2,M3,M4,M5,M6,M7,M8,M9,M10,M11,M12,M13,M14) \
    IMPLE_SET_VALUE_1(CLASS,M15)
        
//init
#define IMPLE_INIT_FUNCTION_1(CLASS,MEMBER) \
    {\
        std::function<void(decltype(MEMBER))> setobj = std::bind(&CLASS::__ReflectSet##MEMBER,this,std::placeholders::_1);\
        std::function<void()> createobj = std::bind(&CLASS::__ReflectCreate##MEMBER,this);\
        FieldContent<decltype(MEMBER)> content = createFieldContent<decltype(MEMBER)>(setobj);\
        content->setReflectObject(this);\
        content->setName(createString(#MEMBER));\
        content->setType(content->TypeOf(this->MEMBER));\
        content->setId(index);\
        maps->put(content->getName(),content);\
        index++;\
    }
    
#define IMPLE_INIT_FUNCTION_2(CLASS,M1,M2) \
    IMPLE_INIT_FUNCTION_1(CLASS,M1) \
    IMPLE_INIT_FUNCTION_1(CLASS,M2) 

#define IMPLE_INIT_FUNCTION_3(CLASS,M1,M2,M3) \
    IMPLE_INIT_FUNCTION_2(CLASS,M1,M2) \
    IMPLE_INIT_FUNCTION_1(CLASS,M3)

#define IMPLE_INIT_FUNCTION_4(CLASS,M1,M2,M3,M4) \
    IMPLE_INIT_FUNCTION_3(CLASS,M1,M2,M3) \
    IMPLE_INIT_FUNCTION_1(CLASS,M4)

#define IMPLE_INIT_FUNCTION_5(CLASS,M1,M2,M3,M4,M5) \
    IMPLE_INIT_FUNCTION_4(CLASS,M1,M2,M3,M4) \
    IMPLE_INIT_FUNCTION_1(CLASS,M5)

#define IMPLE_INIT_FUNCTION_6(CLASS,M1,M2,M3,M4,M5,M6) \
    IMPLE_INIT_FUNCTION_5(CLASS,M1,M2,M3,M4,M5) \
    IMPLE_INIT_FUNCTION_1(CLASS,M6)

#define IMPLE_INIT_FUNCTION_7(CLASS,M1,M2,M3,M4,M5,M6,M7) \
    IMPLE_INIT_FUNCTION_6(CLASS,M1,M2,M3,M4,M5,M6) \
    IMPLE_INIT_FUNCTION_1(CLASS,M7)

#define IMPLE_INIT_FUNCTION_8(CLASS,M1,M2,M3,M4,M5,M6,M7,M8) \
    IMPLE_INIT_FUNCTION_7(CLASS,M1,M2,M3,M4,M5,M6,M7) \
    IMPLE_INIT_FUNCTION_1(CLASS,M8)

#define IMPLE_INIT_FUNCTION_9(CLASS,M1,M2,M3,M4,M5,M6,M7,M8,M9) \
    IMPLE_INIT_FUNCTION_8(CLASS,M1,M2,M3,M4,M5,M6,M7,M8) \
    IMPLE_INIT_FUNCTION_1(CLASS,M9)

#define IMPLE_INIT_FUNCTION_10(CLASS,M1,M2,M3,M4,M5,M6,M7,M8,M9,M10) \
    IMPLE_INIT_FUNCTION_9(CLASS,M1,M2,M3,M4,M5,M6,M7,M8,M9) \
    IMPLE_INIT_FUNCTION_1(CLASS,M10)

#define IMPLE_INIT_FUNCTION_11(CLASS,M1,M2,M3,M4,M5,M6,M7,M8,M9,M10,M11) \
    IMPLE_INIT_FUNCTION_10(CLASS,M1,M2,M3,M4,M5,M6,M7,M8,M9,M10) \
    IMPLE_INIT_FUNCTION_1(CLASS,M11)

#define IMPLE_INIT_FUNCTION_12(CLASS,M1,M2,M3,M4,M5,M6,M7,M8,M9,M10,M11,M12) \
    IMPLE_INIT_FUNCTION_11(CLASS,M1,M2,M3,M4,M5,M6,M7,M8,M9,M10,M11) \
    IMPLE_INIT_FUNCTION_1(CLASS,M12)

#define IMPLE_INIT_FUNCTION_13(CLASS,M1,M2,M3,M4,M5,M6,M7,M8,M9,M10,M11,M12,M13) \
    IMPLE_INIT_FUNCTION_12(CLASS,M1,M2,M3,M4,M5,M6,M7,M8,M9,M10,M11,M12) \
    IMPLE_INIT_FUNCTION_1(CLASS,M13)

#define IMPLE_INIT_FUNCTION_14(CLASS,M1,M2,M3,M4,M5,M6,M7,M8,M9,M10,M11,M12,M13,M14) \
    IMPLE_INIT_FUNCTION_13(CLASS,M1,M2,M3,M4,M5,M6,M7,M8,M9,M10,M11,M12,M13) \
    IMPLE_INIT_FUNCTION_1(CLASS,M14)

#define IMPLE_INIT_FUNCTION_15(CLASS,M1,M2,M3,M4,M5,M6,M7,M8,M9,M10,M11,M12,M13,M14,M15) \
    IMPLE_INIT_FUNCTION_14(CLASS,M1,M2,M3,M4,M5,M6,M7,M8,M9,M10,M11,M12,M13,M14) \
    IMPLE_INIT_FUNCTION_1(CLASS,M15)

#define IMPLE_INIT_FUNCTION_16(CLASS,M1,M2,M3,M4,M5,M6,M7,M8,M9,M10,M11,M12,M13,M14,M15,M16) \
    IMPLE_INIT_FUNCTION_15(CLASS,M1,M2,M3,M4,M5,M6,M7,M8,M9,M10,M11,M12,M13,M14,M15) \
    IMPLE_INIT_FUNCTION_1(CLASS,M16)

#define IMPLE_INIT_FUNCTION_DETECT(CLASS,COUNT, ...) IMPLE_INIT_FUNCTION_DETECT_TRACE(CLASS,COUNT, __VA_ARGS__)
#define IMPLE_INIT_FUNCTION_DETECT_TRACE(CLASS,COUNT, ...) IMPLE_INIT_FUNCTION_DETECT_TRACE1(CLASS,COUNT, __VA_ARGS__)
#define IMPLE_INIT_FUNCTION_DETECT_TRACE1(CLASS,COUNT, ...) IMPLE_INIT_FUNCTION_##COUNT(CLASS,__VA_ARGS__)


#define IMPLE_SET_FUNCTION_DETECT(CLASS,COUNT, ...) IMPLE_SET_FUNCTION_DETECT_TRACE(CLASS,COUNT, __VA_ARGS__)
#define IMPLE_SET_FUNCTION_DETECT_TRACE(CLASS,COUNT, ...) IMPLE_SET_FUNCTION_DETECT_TRACE1(CLASS,COUNT, __VA_ARGS__)
#define IMPLE_SET_FUNCTION_DETECT_TRACE1(CLASS,COUNT, ...) IMPLE_SET_VALUE_##COUNT(CLASS,__VA_ARGS__)

#define DECLARE_INIT_TUPLE_DETECT(CLASS,COUNT, ...) DECLARE_INIT_TUPLE_DETECT_TRACE(CLASS,COUNT, __VA_ARGS__)
#define DECLARE_INIT_TUPLE_DETECT_TRACE(CLASS,COUNT, ...) DECLARE_INIT_TUPLE_DETECT_TRACE1(CLASS,COUNT, __VA_ARGS__)
#define DECLARE_INIT_TUPLE_DETECT_TRACE1(CLASS,COUNT, ...) DECLARE_INIT_TUPLE_##COUNT(__VA_ARGS__)

//Set,Get,Create
#define __S(MEMBER) std::function<void(decltype(MEMBER))>
#define __G(MEMBER) std::function<decltype(MEMBER)()>
#define __C(MEMBER) std::function<void()>
#define __L(MEMBER) std::function<sp<_Object>()>
#define __D() std::function<int()>//dummy function
#define __LD() std::function<sp<_Object>()> //list dummy function 
#define __LIG(MEMBER) std::function<sp<_Object>(int)> //list item get function
#define __OBJSIZE(MEMBER) std::function<int()> //list item get function

#define DECLARE_INIT_TUPLE_1(M1) \
    std::tuple<__S(M1),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D()> setFuncTuple;\
    std::tuple<__G(M1),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D()> getFuncTuple;\
    std::tuple<__C(M1),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D()> createFuncTuple;\
    std::tuple<__L(M1),__LD(),__LD(),__LD(),__LD(),\
                __LD(),__LD(),__LD(),__LD(),__LD(),\
                __LD(),__LD(),__LD(),__LD(),__LD(),\
                __LD(),__LD(),__LD(),__LD(),__LD(),\
                __LD(),__LD(),__LD(),__LD(),__LD(),\
                __LD(),__LD(),__LD(),__LD(),__LD(),\
                __LD(),__LD()> createListItemFuncTuple;\
    std::tuple<__LIG(M1),__LIG(),__LIG(),__LIG(),__LIG(),\
                __LIG(),__LIG(),__LIG(),__LIG(),__LIG(),\
                __LIG(),__LIG(),__LIG(),__LIG(),__LIG(),\
                __LIG(),__LIG(),__LIG(),__LIG(),__LIG(),\
                __LIG(),__LIG(),__LIG(),__LIG(),__LIG(),\
                __LIG(),__LIG(),__LIG(),__LIG(),__LIG(),\
                __LIG(),__LIG()> getListItemFuncTuple;\
    std::tuple<__OBJSIZE(M1),__OBJSIZE(),__OBJSIZE(),__OBJSIZE(),__OBJSIZE(),\
                __OBJSIZE(),__OBJSIZE(),__OBJSIZE(),__OBJSIZE(),__OBJSIZE(),\
                __OBJSIZE(),__OBJSIZE(),__OBJSIZE(),__OBJSIZE(),__OBJSIZE(),\
                __OBJSIZE(),__OBJSIZE(),__OBJSIZE(),__OBJSIZE(),__OBJSIZE(),\
                __OBJSIZE(),__OBJSIZE(),__OBJSIZE(),__OBJSIZE(),__OBJSIZE(),\
                __OBJSIZE(),__OBJSIZE(),__OBJSIZE(),__OBJSIZE(),__OBJSIZE(),\
                __OBJSIZE(),__OBJSIZE()> getListSizeFuncTuple;

#define DECLARE_INIT_TUPLE_2(M1,M2) \
    std::tuple<__S(M1),__S(M2),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D()> setFuncTuple;\
    std::tuple<__G(M1),__G(M2),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D()> getFuncTuple;\
    std::tuple<__C(M1),__C(M2),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D()> createFuncTuple;\
    std::tuple<__L(M1),__L(M2),__LD(),__LD(),__LD(),\
                __LD(),__LD(),__LD(),__LD(),__LD(),\
                __LD(),__LD(),__LD(),__LD(),__LD(),\
                __LD(),__LD(),__LD(),__LD(),__LD(),\
                __LD(),__LD(),__LD(),__LD(),__LD(),\
                __LD(),__LD(),__LD(),__LD(),__LD(),\
                __LD(),__LD()> createListItemFuncTuple;\
    std::tuple<__LIG(M1),__LIG(M2),__LIG(),__LIG(),__LIG(),\
                __LIG(),__LIG(),__LIG(),__LIG(),__LIG(),\
                __LIG(),__LIG(),__LIG(),__LIG(),__LIG(),\
                __LIG(),__LIG(),__LIG(),__LIG(),__LIG(),\
                __LIG(),__LIG(),__LIG(),__LIG(),__LIG(),\
                __LIG(),__LIG(),__LIG(),__LIG(),__LIG(),\
                __LIG(),__LIG()> getListItemFuncTuple;\
    std::tuple<__OBJSIZE(M1),__OBJSIZE(M2),__OBJSIZE(),__OBJSIZE(),__OBJSIZE(),\
            __OBJSIZE(),__OBJSIZE(),__OBJSIZE(),__OBJSIZE(),__OBJSIZE(),\
            __OBJSIZE(),__OBJSIZE(),__OBJSIZE(),__OBJSIZE(),__OBJSIZE(),\
            __OBJSIZE(),__OBJSIZE(),__OBJSIZE(),__OBJSIZE(),__OBJSIZE(),\
            __OBJSIZE(),__OBJSIZE(),__OBJSIZE(),__OBJSIZE(),__OBJSIZE(),\
            __OBJSIZE(),__OBJSIZE(),__OBJSIZE(),__OBJSIZE(),__OBJSIZE(),\
            __OBJSIZE(),__OBJSIZE()> getListSizeFuncTuple;


#define DECLARE_INIT_TUPLE_3(M1,M2,M3) \
    std::tuple<__S(M1),__S(M2),__S(M3),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D()> setFuncTuple;\
    std::tuple<__G(M1),__G(M2),__G(M3),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D()> getFuncTuple;\
    std::tuple<__C(M1),__C(M2),__C(M3),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D()> createFuncTuple;\
    std::tuple<__L(M1),__L(M2),__L(M3),__LD(),__LD(),\
                __LD(),__LD(),__LD(),__LD(),__LD(),\
                __LD(),__LD(),__LD(),__LD(),__LD(),\
                __LD(),__LD(),__LD(),__LD(),__LD(),\
                __LD(),__LD(),__LD(),__LD(),__LD(),\
                __LD(),__LD(),__LD(),__LD(),__LD(),\
                __LD(),__LD()> createListItemFuncTuple;\
    std::tuple<__LIG(M1),__LIG(M2),__LIG(M3),__LIG(),__LIG(),\
                __LIG(),__LIG(),__LIG(),__LIG(),__LIG(),\
                __LIG(),__LIG(),__LIG(),__LIG(),__LIG(),\
                __LIG(),__LIG(),__LIG(),__LIG(),__LIG(),\
                __LIG(),__LIG(),__LIG(),__LIG(),__LIG(),\
                __LIG(),__LIG(),__LIG(),__LIG(),__LIG(),\
                __LIG(),__LIG()> getListItemFuncTuple;\
    std::tuple<__OBJSIZE(M1),__OBJSIZE(M2),__OBJSIZE(M3),__OBJSIZE(),__OBJSIZE(),\
            __OBJSIZE(),__OBJSIZE(),__OBJSIZE(),__OBJSIZE(),__OBJSIZE(),\
            __OBJSIZE(),__OBJSIZE(),__OBJSIZE(),__OBJSIZE(),__OBJSIZE(),\
            __OBJSIZE(),__OBJSIZE(),__OBJSIZE(),__OBJSIZE(),__OBJSIZE(),\
            __OBJSIZE(),__OBJSIZE(),__OBJSIZE(),__OBJSIZE(),__OBJSIZE(),\
            __OBJSIZE(),__OBJSIZE(),__OBJSIZE(),__OBJSIZE(),__OBJSIZE(),\
            __OBJSIZE(),__OBJSIZE()> getListSizeFuncTuple;

#define DECLARE_INIT_TUPLE_4(M1,M2,M3,M4) \
    std::tuple<__S(M1),__S(M2),__S(M3),__S(M4),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D()> setFuncTuple;\
    std::tuple<__G(M1),__G(M2),__G(M3),__G(M4),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D()> getFuncTuple;\
    std::tuple<__C(M1),__C(M2),__C(M3),__C(M4),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D()> createFuncTuple;\
    std::tuple<__L(M1),__L(M2),__L(M3),__L(M4),__LD(),\
                __LD(),__LD(),__LD(),__LD(),__LD(),\
                __LD(),__LD(),__LD(),__LD(),__LD(),\
                __LD(),__LD(),__LD(),__LD(),__LD(),\
                __LD(),__LD(),__LD(),__LD(),__LD(),\
                __LD(),__LD(),__LD(),__LD(),__LD(),\
                __LD(),__LD()> createListItemFuncTuple;\
    std::tuple<__LIG(M1),__LIG(M2),__LIG(M3),__LIG(M4),__LIG(),\
                __LIG(),__LIG(),__LIG(),__LIG(),__LIG(),\
                __LIG(),__LIG(),__LIG(),__LIG(),__LIG(),\
                __LIG(),__LIG(),__LIG(),__LIG(),__LIG(),\
                __LIG(),__LIG(),__LIG(),__LIG(),__LIG(),\
                __LIG(),__LIG(),__LIG(),__LIG(),__LIG(),\
                __LIG(),__LIG()> getListItemFuncTuple;\
    std::tuple<__OBJSIZE(M1),__OBJSIZE(M2),__OBJSIZE(M3),__OBJSIZE(M4),__OBJSIZE(),\
                __OBJSIZE(),__OBJSIZE(),__OBJSIZE(),__OBJSIZE(),__OBJSIZE(),\
                __OBJSIZE(),__OBJSIZE(),__OBJSIZE(),__OBJSIZE(),__OBJSIZE(),\
                __OBJSIZE(),__OBJSIZE(),__OBJSIZE(),__OBJSIZE(),__OBJSIZE(),\
                __OBJSIZE(),__OBJSIZE(),__OBJSIZE(),__OBJSIZE(),__OBJSIZE(),\
                __OBJSIZE(),__OBJSIZE(),__OBJSIZE(),__OBJSIZE(),__OBJSIZE(),\
                __OBJSIZE(),__OBJSIZE()> getListSizeFuncTuple;

#define DECLARE_INIT_TUPLE_5(M1,M2,M3,M4,M5) \
    std::tuple<__S(M1),__S(M2),__S(M3),__S(M4),__S(M5),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D()> setFuncTuple;\
    std::tuple<__G(M1),__G(M2),__G(M3),__G(M4),__G(M5),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D()> getFuncTuple;\
    std::tuple<__C(M1),__C(M2),__C(M3),__C(M4),__C(M5),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D()> createFuncTuple;\
    std::tuple<__L(M1),__L(M2),__L(M3),__L(M4),__L(M5),\
                __LD(),__LD(),__LD(),__LD(),__LD(),\
                __LD(),__LD(),__LD(),__LD(),__LD(),\
                __LD(),__LD(),__LD(),__LD(),__LD(),\
                __LD(),__LD(),__LD(),__LD(),__LD(),\
                __LD(),__LD(),__LD(),__LD(),__LD(),\
                __LD(),__LD()> createListItemFuncTuple;\
    std::tuple<__LIG(M1),__LIG(M2),__LIG(M3),__LIG(M4),__LIG(M5),\
                __LIG(),__LIG(),__LIG(),__LIG(),__LIG(),\
                __LIG(),__LIG(),__LIG(),__LIG(),__LIG(),\
                __LIG(),__LIG(),__LIG(),__LIG(),__LIG(),\
                __LIG(),__LIG(),__LIG(),__LIG(),__LIG(),\
                __LIG(),__LIG(),__LIG(),__LIG(),__LIG(),\
                __LIG(),__LIG()> getListItemFuncTuple;\
    std::tuple<__OBJSIZE(M1),__OBJSIZE(M2),__OBJSIZE(M3),__OBJSIZE(M4),__OBJSIZE(M5),\
                __OBJSIZE(),__OBJSIZE(),__OBJSIZE(),__OBJSIZE(),__OBJSIZE(),\
                __OBJSIZE(),__OBJSIZE(),__OBJSIZE(),__OBJSIZE(),__OBJSIZE(),\
                __OBJSIZE(),__OBJSIZE(),__OBJSIZE(),__OBJSIZE(),__OBJSIZE(),\
                __OBJSIZE(),__OBJSIZE(),__OBJSIZE(),__OBJSIZE(),__OBJSIZE(),\
                __OBJSIZE(),__OBJSIZE(),__OBJSIZE(),__OBJSIZE(),__OBJSIZE(),\
                __OBJSIZE(),__OBJSIZE()> getListSizeFuncTuple;

#define DECLARE_INIT_TUPLE_6(M1,M2,M3,M4,M5,M6) \
    std::tuple<__S(M1),__S(M2),__S(M3),__S(M4),__S(M5),\
                __S(M6),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D()> setFuncTuple;\
    std::tuple<__G(M1),__G(M2),__G(M3),__G(M4),__G(M5),\
                __G(M6),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D()> getFuncTuple;\
    std::tuple<__C(M1),__C(M2),__C(M3),__C(M4),__C(M5),\
                __C(M6),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D()> createFuncTuple;\
    std::tuple<__L(M1),__L(M2),__L(M3),__L(M4),__L(M5),\
                __L(M6),__LD(),__LD(),__LD(),__LD(),\
                __LD(),__LD(),__LD(),__LD(),__LD(),\
                __LD(),__LD(),__LD(),__LD(),__LD(),\
                __LD(),__LD(),__LD(),__LD(),__LD(),\
                __LD(),__LD(),__LD(),__LD(),__LD(),\
                __LD(),__LD()> createListItemFuncTuple;\
    std::tuple<__LIG(M1),__LIG(M2),__LIG(M3),__LIG(M4),__LIG(M5),\
                __LIG(M6),__LIG(),__LIG(),__LIG(),__LIG(),\
                __LIG(),__LIG(),__LIG(),__LIG(),__LIG(),\
                __LIG(),__LIG(),__LIG(),__LIG(),__LIG(),\
                __LIG(),__LIG(),__LIG(),__LIG(),__LIG(),\
                __LIG(),__LIG(),__LIG(),__LIG(),__LIG(),\
                __LIG(),__LIG()> getListItemFuncTuple;\
    std::tuple<__OBJSIZE(M1),__OBJSIZE(M2),__OBJSIZE(M3),__OBJSIZE(M4),__OBJSIZE(M5),\
                __OBJSIZE(M6),__OBJSIZE(),__OBJSIZE(),__OBJSIZE(),__OBJSIZE(),\
                __OBJSIZE(),__OBJSIZE(),__OBJSIZE(),__OBJSIZE(),__OBJSIZE(),\
                __OBJSIZE(),__OBJSIZE(),__OBJSIZE(),__OBJSIZE(),__OBJSIZE(),\
                __OBJSIZE(),__OBJSIZE(),__OBJSIZE(),__OBJSIZE(),__OBJSIZE(),\
                __OBJSIZE(),__OBJSIZE(),__OBJSIZE(),__OBJSIZE(),__OBJSIZE(),\
                __OBJSIZE(),__OBJSIZE()> getListSizeFuncTuple;


#define DECLARE_INIT_TUPLE_7(M1,M2,M3,M4,M5,M6,M7) \
    std::tuple<__S(M1),__S(M2),__S(M3),__S(M4),__S(M5),\
                __S(M6),__S(M7),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D()> setFuncTuple;\
    std::tuple<__G(M1),__G(M2),__G(M3),__G(M4),__G(M5),\
                __G(M6),__G(M7),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D()> getFuncTuple;\
    std::tuple<__C(M1),__C(M2),__C(M3),__C(M4),__C(M5),\
                __C(M6),__C(M7),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D()> createFuncTuple;\
    std::tuple<__L(M1),__L(M2),__L(M3),__L(M4),__L(M5),\
                __L(M6),__L(M7),__LD(),__LD(),__LD(),\
                __LD(),__LD(),__LD(),__LD(),__LD(),\
                __LD(),__LD(),__LD(),__LD(),__LD(),\
                __LD(),__LD(),__LD(),__LD(),__LD(),\
                __LD(),__LD(),__LD(),__LD(),__LD(),\
                __LD(),__LD()> createListItemFuncTuple;\
    std::tuple<__LIG(M1),__LIG(M2),__LIG(M3),__LIG(M4),__LIG(M5),\
                __LIG(M6),__LIG(M7),__LIG(),__LIG(),__LIG(),\
                __LIG(),__LIG(),__LIG(),__LIG(),__LIG(),\
                __LIG(),__LIG(),__LIG(),__LIG(),__LIG(),\
                __LIG(),__LIG(),__LIG(),__LIG(),__LIG(),\
                __LIG(),__LIG(),__LIG(),__LIG(),__LIG(),\
                __LIG(),__LIG()> getListItemFuncTuple;\
    std::tuple<__OBJSIZE(M1),__OBJSIZE(M2),__OBJSIZE(M3),__OBJSIZE(M4),__OBJSIZE(M5),\
                __OBJSIZE(M6),__OBJSIZE(M7),__OBJSIZE(),__OBJSIZE(),__OBJSIZE(),\
                __OBJSIZE(),__OBJSIZE(),__OBJSIZE(),__OBJSIZE(),__OBJSIZE(),\
                __OBJSIZE(),__OBJSIZE(),__OBJSIZE(),__OBJSIZE(),__OBJSIZE(),\
                __OBJSIZE(),__OBJSIZE(),__OBJSIZE(),__OBJSIZE(),__OBJSIZE(),\
                __OBJSIZE(),__OBJSIZE(),__OBJSIZE(),__OBJSIZE(),__OBJSIZE(),\
                __OBJSIZE(),__OBJSIZE()> getListSizeFuncTuple;    


#define DECLARE_INIT_TUPLE_8(M1,M2,M3,M4,M5,M6,M7,M8) \
    std::tuple<__S(M1),__S(M2),__S(M3),__S(M4),__S(M5),\
                __S(M6),__S(M7),__S(M8),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D()> setFuncTuple;\
    std::tuple<__G(M1),__G(M2),__G(M3),__G(M4),__G(M5),\
                __G(M6),__G(M7),__G(M8),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D()> getFuncTuple;\
    std::tuple<__C(M1),__C(M2),__C(M3),__C(M4),__C(M5),\
                __C(M6),__C(M7),__C(M8),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D()> createFuncTuple;\
    std::tuple<__L(M1),__L(M2),__L(M3),__L(M4),__L(M5),\
                __L(M6),__L(M7),__L(M8),__LD(),__LD(),\
                __LD(),__LD(),__LD(),__LD(),__LD(),\
                __LD(),__LD(),__LD(),__LD(),__LD(),\
                __LD(),__LD(),__LD(),__LD(),__LD(),\
                __LD(),__LD(),__LD(),__LD(),__LD(),\
                __LD(),__LD()> createListItemFuncTuple;\
    std::tuple<__LIG(M1),__LIG(M2),__LIG(M3),__LIG(M4),__LIG(M5),\
                __LIG(M6),__LIG(M7),__LIG(M8),__LIG(),__LIG(),\
                __LIG(),__LIG(),__LIG(),__LIG(),__LIG(),\
                __LIG(),__LIG(),__LIG(),__LIG(),__LIG(),\
                __LIG(),__LIG(),__LIG(),__LIG(),__LIG(),\
                __LIG(),__LIG(),__LIG(),__LIG(),__LIG(),\
                __LIG(),__LIG()> getListItemFuncTuple;\
    std::tuple<__OBJSIZE(M1),__OBJSIZE(M2),__OBJSIZE(M3),__OBJSIZE(M4),__OBJSIZE(M5),\
                __OBJSIZE(M6),__OBJSIZE(M7),__OBJSIZE(M8),__OBJSIZE(),__OBJSIZE(),\
                __OBJSIZE(),__OBJSIZE(),__OBJSIZE(),__OBJSIZE(),__OBJSIZE(),\
                __OBJSIZE(),__OBJSIZE(),__OBJSIZE(),__OBJSIZE(),__OBJSIZE(),\
                __OBJSIZE(),__OBJSIZE(),__OBJSIZE(),__OBJSIZE(),__OBJSIZE(),\
                __OBJSIZE(),__OBJSIZE(),__OBJSIZE(),__OBJSIZE(),__OBJSIZE(),\
                __OBJSIZE(),__OBJSIZE()> getListSizeFuncTuple;    

#define DECLARE_INIT_TUPLE_9(M1,M2,M3,M4,M5,M6,M7,M8,M9) \
    std::tuple<__S(M1),__S(M2),__S(M3),__S(M4),__S(M5),\
                __S(M6),__S(M7),__S(M8),__S(M9),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D()> setFuncTuple;\
    std::tuple<__G(M1),__G(M2),__G(M3),__G(M4),__G(M5),\
                __G(M6),__G(M7),__G(M8),__G(M9),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D()> getFuncTuple;\
    std::tuple<__C(M1),__C(M2),__C(M3),__C(M4),__C(M5),\
                __C(M6),__C(M7),__C(M8),__C(M9),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D()> createFuncTuple;\
    std::tuple<__L(M1),__L(M2),__L(M3),__L(M4),__L(M5),\
                __L(M6),__L(M7),__L(M8),__L(M9),__LD(),\
                __LD(),__LD(),__LD(),__LD(),__LD(),\
                __LD(),__LD(),__LD(),__LD(),__LD(),\
                __LD(),__LD(),__LD(),__LD(),__LD(),\
                __LD(),__LD(),__LD(),__LD(),__LD(),\
                __LD(),__LD()> createListItemFuncTuple;\
    std::tuple<__LIG(M1),__LIG(M2),__LIG(M3),__LIG(M4),__LIG(M5),\
                __LIG(M6),__LIG(M7),__LIG(M8),__LIG(M9),__LIG(),\
                __LIG(),__LIG(),__LIG(),__LIG(),__LIG(),\
                __LIG(),__LIG(),__LIG(),__LIG(),__LIG(),\
                __LIG(),__LIG(),__LIG(),__LIG(),__LIG(),\
                __LIG(),__LIG(),__LIG(),__LIG(),__LIG(),\
                __LIG(),__LIG()> getListItemFuncTuple;\
    std::tuple<__OBJSIZE(M1),__OBJSIZE(M2),__OBJSIZE(M3),__OBJSIZE(M4),__OBJSIZE(M5),\
                __OBJSIZE(M6),__OBJSIZE(M7),__OBJSIZE(M8),__OBJSIZE(M9),__OBJSIZE(),\
                __OBJSIZE(),__OBJSIZE(),__OBJSIZE(),__OBJSIZE(),__OBJSIZE(),\
                __OBJSIZE(),__OBJSIZE(),__OBJSIZE(),__OBJSIZE(),__OBJSIZE(),\
                __OBJSIZE(),__OBJSIZE(),__OBJSIZE(),__OBJSIZE(),__OBJSIZE(),\
                __OBJSIZE(),__OBJSIZE(),__OBJSIZE(),__OBJSIZE(),__OBJSIZE(),\
                __OBJSIZE(),__OBJSIZE()> getListSizeFuncTuple;   

#define DECLARE_INIT_TUPLE_10(M1,M2,M3,M4,M5,M6,M7,M8,M9,M10) \
    std::tuple<__S(M1),__S(M2),__S(M3),__S(M4),__S(M5),\
                __S(M6),__S(M7),__S(M8),__S(M9),__S(M10),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D()> setFuncTuple;\
    std::tuple<__G(M1),__G(M2),__G(M3),__G(M4),__G(M5),\
                __G(M6),__G(M7),__G(M8),__G(M9),__G(M10),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D()> getFuncTuple;\
    std::tuple<__C(M1),__C(M2),__C(M3),__C(M4),__C(M5),\
                __C(M6),__C(M7),__C(M8),__C(M9),__C(M10),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D()> createFuncTuple;\
    std::tuple<__L(M1),__L(M2),__L(M3),__L(M4),__L(M5),\
                __L(M6),__L(M7),__L(M8),__L(M9),__L(M10),\
                __LD(),__LD(),__LD(),__LD(),__LD(),\
                __LD(),__LD(),__LD(),__LD(),__LD(),\
                __LD(),__LD(),__LD(),__LD(),__LD(),\
                __LD(),__LD(),__LD(),__LD(),__LD(),\
                __LD(),__LD()> createListItemFuncTuple;\
    std::tuple<__LIG(M1),__LIG(M2),__LIG(M3),__LIG(M4),__LIG(M5),\
                __LIG(M6),__LIG(M7),__LIG(M8),__LIG(M9),__LIG(M10),\
                __LIG(),__LIG(),__LIG(),__LIG(),__LIG(),\
                __LIG(),__LIG(),__LIG(),__LIG(),__LIG(),\
                __LIG(),__LIG(),__LIG(),__LIG(),__LIG(),\
                __LIG(),__LIG(),__LIG(),__LIG(),__LIG(),\
                __LIG(),__LIG()> getListItemFuncTuple;\
    std::tuple<__OBJSIZE(M1),__OBJSIZE(M2),__OBJSIZE(M3),__OBJSIZE(M4),__OBJSIZE(M5),\
                __OBJSIZE(M6),__OBJSIZE(M7),__OBJSIZE(M8),__OBJSIZE(M9),__OBJSIZE(M10),\
                __OBJSIZE(),__OBJSIZE(),__OBJSIZE(),__OBJSIZE(),__OBJSIZE(),\
                __OBJSIZE(),__OBJSIZE(),__OBJSIZE(),__OBJSIZE(),__OBJSIZE(),\
                __OBJSIZE(),__OBJSIZE(),__OBJSIZE(),__OBJSIZE(),__OBJSIZE(),\
                __OBJSIZE(),__OBJSIZE(),__OBJSIZE(),__OBJSIZE(),__OBJSIZE(),\
                __OBJSIZE(),__OBJSIZE()> getListSizeFuncTuple;   

#define DECLARE_INIT_TUPLE_11(M1,M2,M3,M4,M5,M6,M7,M8,M9,M10,M11) \
    std::tuple<__S(M1),__S(M2),__S(M3),__S(M4),__S(M5),\
                __S(M6),__S(M7),__S(M8),__S(M9),__S(M10),\
                __S(M11),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D()> setFuncTuple;\
    std::tuple<__G(M1),__G(M2),__G(M3),__G(M4),__G(M5),\
                __G(M6),__G(M7),__G(M8),__G(M9),__G(M10),\
                __G(M11),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D()> getFuncTuple;\
    std::tuple<__C(M1),__C(M2),__C(M3),__C(M4),__C(M5),\
                __C(M6),__C(M7),__C(M8),__C(M9),__C(M10),\
                __C(M11),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D()> createFuncTuple;\
    std::tuple<__L(M1),__L(M2),__L(M3),__L(M4),__L(M5),\
                __L(M6),__L(M7),__L(M8),__L(M9),__L(M10),\
                __L(M11),__LD(),__LD(),__LD(),__LD(),\
                __LD(),__LD(),__LD(),__LD(),__LD(),\
                __LD(),__LD(),__LD(),__LD(),__LD(),\
                __LD(),__LD(),__LD(),__LD(),__LD(),\
                __LD(),__LD()> createListItemFuncTuple;\
    std::tuple<__LIG(M1),__LIG(M2),__LIG(M3),__LIG(M4),__LIG(M5),\
                __LIG(M6),__LIG(M7),__LIG(M8),__LIG(M9),__LIG(M10),\
                __LIG(M11),__LIG(),__LIG(),__LIG(),__LIG(),\
                __LIG(),__LIG(),__LIG(),__LIG(),__LIG(),\
                __LIG(),__LIG(),__LIG(),__LIG(),__LIG(),\
                __LIG(),__LIG(),__LIG(),__LIG(),__LIG(),\
                __LIG(),__LIG()> getListItemFuncTuple;\
    std::tuple<__OBJSIZE(M1),__OBJSIZE(M2),__OBJSIZE(M3),__OBJSIZE(M4),__OBJSIZE(M5),\
                __OBJSIZE(M6),__OBJSIZE(M7),__OBJSIZE(M8),__OBJSIZE(M9),__OBJSIZE(M10),\
                __OBJSIZE(M11),__OBJSIZE(),__OBJSIZE(),__OBJSIZE(),__OBJSIZE(),\
                __OBJSIZE(),__OBJSIZE(),__OBJSIZE(),__OBJSIZE(),__OBJSIZE(),\
                __OBJSIZE(),__OBJSIZE(),__OBJSIZE(),__OBJSIZE(),__OBJSIZE(),\
                __OBJSIZE(),__OBJSIZE(),__OBJSIZE(),__OBJSIZE(),__OBJSIZE(),\
                __OBJSIZE(),__OBJSIZE()> getListSizeFuncTuple; 


#define DECLARE_INIT_TUPLE_12(M1,M2,M3,M4,M5,M6,M7,M8,M9,M10,M11,M12) \
    std::tuple<__S(M1),__S(M2),__S(M3),__S(M4),__S(M5),\
                __S(M6),__S(M7),__S(M8),__S(M9),__S(M10),\
                __S(M11),__S(M12),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D()> setFuncTuple;\
    std::tuple<__G(M1),__G(M2),__G(M3),__G(M4),__G(M5),\
                __G(M6),__G(M7),__G(M8),__G(M9),__G(M10),\
                __G(M11),__G(M12),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D()> getFuncTuple;\
    std::tuple<__C(M1),__C(M2),__C(M3),__C(M4),__C(M5),\
                __C(M6),__C(M7),__C(M8),__C(M9),__C(M10),\
                __C(M11),__C(M12),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D()> createFuncTuple;\
    std::tuple<__L(M1),__L(M2),__L(M3),__L(M4),__L(M5),\
                __L(M6),__L(M7),__L(M8),__L(M9),__L(M10),\
                __L(M11),__L(M12),__LD(),__LD(),__LD(),\
                __LD(),__LD(),__LD(),__LD(),__LD(),\
                __LD(),__LD(),__LD(),__LD(),__LD(),\
                __LD(),__LD(),__LD(),__LD(),__LD(),\
                __LD(),__LD()> createListItemFuncTuple;\
    std::tuple<__LIG(M1),__LIG(M2),__LIG(M3),__LIG(M4),__LIG(M5),\
                __LIG(M6),__LIG(M7),__LIG(M8),__LIG(M9),__LIG(M10),\
                __LIG(M11),__LIG(M12),__LIG(),__LIG(),__LIG(),\
                __LIG(),__LIG(),__LIG(),__LIG(),__LIG(),\
                __LIG(),__LIG(),__LIG(),__LIG(),__LIG(),\
                __LIG(),__LIG(),__LIG(),__LIG(),__LIG(),\
                __LIG(),__LIG()> getListItemFuncTuple;\
    std::tuple<__OBJSIZE(M1),__OBJSIZE(M2),__OBJSIZE(M3),__OBJSIZE(M4),__OBJSIZE(M5),\
                __OBJSIZE(M6),__OBJSIZE(M7),__OBJSIZE(M8),__OBJSIZE(M9),__OBJSIZE(M10),\
                __OBJSIZE(M11),__OBJSIZE(M12),__OBJSIZE(),__OBJSIZE(),__OBJSIZE(),\
                __OBJSIZE(),__OBJSIZE(),__OBJSIZE(),__OBJSIZE(),__OBJSIZE(),\
                __OBJSIZE(),__OBJSIZE(),__OBJSIZE(),__OBJSIZE(),__OBJSIZE(),\
                __OBJSIZE(),__OBJSIZE(),__OBJSIZE(),__OBJSIZE(),__OBJSIZE(),\
                __OBJSIZE(),__OBJSIZE()> getListSizeFuncTuple; 

#define DECLARE_INIT_TUPLE_13(M1,M2,M3,M4,M5,M6,M7,M8,M9,M10,M11,M12,M13) \
    std::tuple<__S(M1),__S(M2),__S(M3),__S(M4),__S(M5),\
                __S(M6),__S(M7),__S(M8),__S(M9),__S(M10),\
                __S(M11),__S(M12),__S(M13),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D()> setFuncTuple;\
    std::tuple<__G(M1),__G(M2),__G(M3),__G(M4),__G(M5),\
                __G(M6),__G(M7),__G(M8),__G(M9),__G(M10),\
                __G(M11),__G(M12),__G(M13),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D()> getFuncTuple;\
    std::tuple<__C(M1),__C(M2),__C(M3),__C(M4),__C(M5),\
                __C(M6),__C(M7),__C(M8),__C(M9),__C(M10),\
                __C(M11),__C(M12),__C(M13),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D()> createFuncTuple;\
    std::tuple<__L(M1),__L(M2),__L(M3),__L(M4),__L(M5),\
                __L(M6),__L(M7),__L(M8),__L(M9),__L(M10),\
                __L(M11),__L(M12),__L(M13),__LD(),__LD(),\
                __LD(),__LD(),__LD(),__LD(),__LD(),\
                __LD(),__LD(),__LD(),__LD(),__LD(),\
                __LD(),__LD(),__LD(),__LD(),__LD(),\
                __LD(),__LD()> createListItemFuncTuple;\
    std::tuple<__LIG(M1),__LIG(M2),__LIG(M3),__LIG(M4),__LIG(M5),\
                __LIG(M6),__LIG(M7),__LIG(M8),__LIG(M9),__LIG(M10),\
                __LIG(M11),__LIG(M12),__LIG(M13),__LIG(),__LIG(),\
                __LIG(),__LIG(),__LIG(),__LIG(),__LIG(),\
                __LIG(),__LIG(),__LIG(),__LIG(),__LIG(),\
                __LIG(),__LIG(),__LIG(),__LIG(),__LIG(),\
                __LIG(),__LIG()> getListItemFuncTuple;\
    std::tuple<__OBJSIZE(M1),__OBJSIZE(M2),__OBJSIZE(M3),__OBJSIZE(M4),__OBJSIZE(M5),\
                __OBJSIZE(M6),__OBJSIZE(M7),__OBJSIZE(M8),__OBJSIZE(M9),__OBJSIZE(M10),\
                __OBJSIZE(M11),__OBJSIZE(M12),__OBJSIZE(M13),__OBJSIZE(),__OBJSIZE(),\
                __OBJSIZE(),__OBJSIZE(),__OBJSIZE(),__OBJSIZE(),__OBJSIZE(),\
                __OBJSIZE(),__OBJSIZE(),__OBJSIZE(),__OBJSIZE(),__OBJSIZE(),\
                __OBJSIZE(),__OBJSIZE(),__OBJSIZE(),__OBJSIZE(),__OBJSIZE(),\
                __OBJSIZE(),__OBJSIZE()> getListSizeFuncTuple;

#define DECLARE_INIT_TUPLE_14(M1,M2,M3,M4,M5,M6,M7,M8,M9,M10,M11,M12,M13,M14) \
    std::tuple<__S(M1),__S(M2),__S(M3),__S(M4),__S(M5),\
                __S(M6),__S(M7),__S(M8),__S(M9),__S(M10),\
                __S(M11),__S(M12),__S(M13),__S(M14),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D()> setFuncTuple;\
    std::tuple<__G(M1),__G(M2),__G(M3),__G(M4),__G(M5),\
                __G(M6),__G(M7),__G(M8),__G(M9),__G(M10),\
                __G(M11),__G(M12),__G(M13),__G(M14),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D()> getFuncTuple;\
    std::tuple<__C(M1),__C(M2),__C(M3),__C(M4),__C(M5),\
                __C(M6),__C(M7),__C(M8),__C(M9),__C(M10),\
                __C(M11),__C(M12),__C(M13),__C(M14),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D()> createFuncTuple;\
    std::tuple<__L(M1),__L(M2),__L(M3),__L(M4),__L(M5),\
                __L(M6),__L(M7),__L(M8),__L(M9),__L(M10),\
                __L(M11),__L(M12),__L(M13),__L(M14),__LD(),\
                __LD(),__LD(),__LD(),__LD(),__LD(),\
                __LD(),__LD(),__LD(),__LD(),__LD(),\
                __LD(),__LD(),__LD(),__LD(),__LD(),\
                __LD(),__LD()> createListItemFuncTuple;\
    std::tuple<__LIG(M1),__LIG(M2),__LIG(M3),__LIG(M4),__LIG(M5),\
                __LIG(M6),__LIG(M7),__LIG(M8),__LIG(M9),__LIG(M10),\
                __LIG(M11),__LIG(M12),__LIG(M13),__LIG(M14),__LIG(),\
                __LIG(),__LIG(),__LIG(),__LIG(),__LIG(),\
                __LIG(),__LIG(),__LIG(),__LIG(),__LIG(),\
                __LIG(),__LIG(),__LIG(),__LIG(),__LIG(),\
                __LIG(),__LIG()> getListItemFuncTuple;\
    std::tuple<__OBJSIZE(M1),__OBJSIZE(M2),__OBJSIZE(M3),__OBJSIZE(M4),__OBJSIZE(M5),\
                __OBJSIZE(M6),__OBJSIZE(M7),__OBJSIZE(M8),__OBJSIZE(M9),__OBJSIZE(M10),\
                __OBJSIZE(M11),__OBJSIZE(M12),__OBJSIZE(M13),__OBJSIZE(M14),__OBJSIZE(),\
                __OBJSIZE(),__OBJSIZE(),__OBJSIZE(),__OBJSIZE(),__OBJSIZE(),\
                __OBJSIZE(),__OBJSIZE(),__OBJSIZE(),__OBJSIZE(),__OBJSIZE(),\
                __OBJSIZE(),__OBJSIZE(),__OBJSIZE(),__OBJSIZE(),__OBJSIZE(),\
                __OBJSIZE(),__OBJSIZE()> getListSizeFuncTuple;

#define DECLARE_INIT_TUPLE_15(M1,M2,M3,M4,M5,M6,M7,M8,M9,M10,M11,M12,M13,M14,M15) \
    std::tuple<__S(M1),__S(M2),__S(M3),__S(M4),__S(M5),\
                __S(M6),__S(M7),__S(M8),__S(M9),__S(M10),\
                __S(M11),__S(M12),__S(M13),__S(M14),__S(M15),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D()> setFuncTuple;\
    std::tuple<__G(M1),__G(M2),__G(M3),__G(M4),__G(M5),\
                __G(M6),__G(M7),__G(M8),__G(M9),__G(M10),\
                __G(M11),__G(M12),__G(M13),__G(M14),__G(M15),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D()> getFuncTuple;\
    std::tuple<__C(M1),__C(M2),__C(M3),__C(M4),__C(M5),\
                __C(M6),__C(M7),__C(M8),__C(M9),__C(M10),\
                __C(M11),__C(M12),__C(M13),__C(M14),__C(M15),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D()> createFuncTuple;\
    std::tuple<__L(M1),__L(M2),__L(M3),__L(M4),__L(M5),\
                __L(M6),__L(M7),__L(M8),__L(M9),__L(M10),\
                __L(M11),__L(M12),__L(M13),__L(M14),__L(M15),\
                __LD(),__LD(),__LD(),__LD(),__LD(),\
                __LD(),__LD(),__LD(),__LD(),__LD(),\
                __LD(),__LD(),__LD(),__LD(),__LD(),\
                __LD(),__LD()> createListItemFuncTuple;\
    std::tuple<__LIG(M1),__LIG(M2),__LIG(M3),__LIG(M4),__LIG(M5),\
                __LIG(M6),__LIG(M7),__LIG(M8),__LIG(M9),__LIG(M10),\
                __LIG(M11),__LIG(M12),__LIG(M13),__LIG(M14),__LIG(M15),\
                __LIG(),__LIG(),__LIG(),__LIG(),__LIG(),\
                __LIG(),__LIG(),__LIG(),__LIG(),__LIG(),\
                __LIG(),__LIG(),__LIG(),__LIG(),__LIG(),\
                __LIG(),__LIG()> getListItemFuncTuple;\
    std::tuple<__OBJSIZE(M1),__OBJSIZE(M2),__OBJSIZE(M3),__OBJSIZE(M4),__OBJSIZE(M5),\
                __OBJSIZE(M6),__OBJSIZE(M7),__OBJSIZE(M8),__OBJSIZE(M9),__OBJSIZE(M10),\
                __OBJSIZE(M11),__OBJSIZE(M12),__OBJSIZE(M13),__OBJSIZE(M14),__OBJSIZE(M15),\
                __OBJSIZE(),__OBJSIZE(),__OBJSIZE(),__OBJSIZE(),__OBJSIZE(),\
                __OBJSIZE(),__OBJSIZE(),__OBJSIZE(),__OBJSIZE(),__OBJSIZE(),\
                __OBJSIZE(),__OBJSIZE(),__OBJSIZE(),__OBJSIZE(),__OBJSIZE(),\
                __OBJSIZE(),__OBJSIZE()> getListSizeFuncTuple;


#define DECLARE_INIT_TUPLE_16(M1,M2,M3,M4,M5,M6,M7,M8,M9,M10,M11,M12,M13,M14,M15,M16) \
    std::tuple<__S(M1),__S(M2),__S(M3),__S(M4),__S(M5),\
                __S(M6),__S(M7),__S(M8),__S(M9),__S(M10),\
                __S(M11),__S(M12),__S(M13),__S(M14),__S(M15),\
                __S(M16),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D()> setFuncTuple;\
    std::tuple<__G(M1),__G(M2),__G(M3),__G(M4),__G(M5),\
                __G(M6),__G(M7),__G(M8),__G(M9),__G(M10),\
                __G(M11),__G(M12),__G(M13),__G(M14),__G(M15),\
                __G(M16),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D()> getFuncTuple;\
    std::tuple<__C(M1),__C(M2),__C(M3),__C(M4),__C(M5),\
                __C(M6),__C(M7),__C(M8),__C(M9),__C(M10),\
                __C(M11),__C(M12),__C(M13),__C(M14),__C(M15),\
                __C(M16),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D(),__D(),__D(),__D(),\
                __D(),__D()> createFuncTuple;\
    std::tuple<__L(M1),__L(M2),__L(M3),__L(M4),__L(M5),\
                __L(M6),__L(M7),__L(M8),__L(M9),__L(M10),\
                __L(M11),__L(M12),__L(M13),__L(M14),__L(M15),\
                __L(M16),__LD(),__LD(),__LD(),__LD(),\
                __LD(),__LD(),__LD(),__LD(),__LD(),\
                __LD(),__LD(),__LD(),__LD(),__LD(),\
                __LD(),__LD()> createListItemFuncTuple;\
    std::tuple<__LIG(M1),__LIG(M2),__LIG(M3),__LIG(M4),__LIG(M5),\
                __LIG(M6),__LIG(M7),__LIG(M8),__LIG(M9),__LIG(M10),\
                __LIG(M11),__LIG(M12),__LIG(M13),__LIG(M14),__LIG(M15),\
                __LIG(M16),__LIG(),__LIG(),__LIG(),__LIG(),\
                __LIG(),__LIG(),__LIG(),__LIG(),__LIG(),\
                __LIG(),__LIG(),__LIG(),__LIG(),__LIG(),\
                __LIG(),__LIG()> getListItemFuncTuple;\
    std::tuple<__OBJSIZE(M1),__OBJSIZE(M2),__OBJSIZE(M3),__OBJSIZE(M4),__OBJSIZE(M5),\
                __OBJSIZE(M6),__OBJSIZE(M7),__OBJSIZE(M8),__OBJSIZE(M9),__OBJSIZE(M10),\
                __OBJSIZE(M11),__OBJSIZE(M12),__OBJSIZE(M13),__OBJSIZE(M14),__OBJSIZE(M15),\
                __OBJSIZE(M16),__OBJSIZE(),__OBJSIZE(),__OBJSIZE(),__OBJSIZE(),\
                __OBJSIZE(),__OBJSIZE(),__OBJSIZE(),__OBJSIZE(),__OBJSIZE(),\
                __OBJSIZE(),__OBJSIZE(),__OBJSIZE(),__OBJSIZE(),__OBJSIZE(),\
                __OBJSIZE(),__OBJSIZE()> getListSizeFuncTuple;


#define IMPLE_INIT_TUPLE_DETECT(CLASS,COUNT, ...) IMPLE_INIT_TUPLE_DETECT_TRACE(CLASS,COUNT, __VA_ARGS__)
#define IMPLE_INIT_TUPLE_DETECT_TRACE(CLASS,COUNT, ...) IMPLE_INIT_TUPLE_DETECT_TRACE1(CLASS,COUNT, __VA_ARGS__)
#define IMPLE_INIT_TUPLE_DETECT_TRACE1(CLASS,COUNT, ...) IMPLE_INIT_TUPLE_##COUNT(CLASS,__VA_ARGS__)

#define IMPLE_INIT_TUPLE_1(CLASS,M1) \
    std::function<decltype(M1)()> getobj = std::bind(&CLASS::__ReflectGet##M1,this);\
    std::function<void()> createobj = std::bind(&CLASS::__ReflectCreate##M1,this);\
    std::function<sp<_Object>()>genItemObj = std::bind(&CLASS::__ReflectCreateListMember##M1,this);\
    std::function<sp<_Object>(int)>getItemObj = std::bind(&CLASS::__ReflectGetListItem##M1,this,std::placeholders::_1);\
    std::function<int()>getListSize = std::bind(&CLASS::__ReflectGetListSize##M1,this);\
    getFuncTuple = std::make_tuple(getobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj);\
    createFuncTuple = std::make_tuple(createobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj);\
    createListItemFuncTuple = std::make_tuple(genItemObj,dummycreateobj,dummycreateobj,dummycreateobj,dummycreateobj,\
                                   dummycreateobj,dummycreateobj,dummycreateobj,dummycreateobj,dummycreateobj,\
                                   dummycreateobj,dummycreateobj,dummycreateobj,dummycreateobj,dummycreateobj,\
                                   dummycreateobj,dummycreateobj,dummycreateobj,dummycreateobj,dummycreateobj,\
                                   dummycreateobj,dummycreateobj,dummycreateobj,dummycreateobj,dummycreateobj,\
                                   dummycreateobj,dummycreateobj,dummycreateobj,dummycreateobj,dummycreateobj,\
                                   dummycreateobj,dummycreateobj);\
    getListItemFuncTuple = std::make_tuple(getItemObj,dummyligobj,dummyligobj,dummyligobj,dummyligobj,\
                                   dummyligobj,dummyligobj,dummyligobj,dummyligobj,dummyligobj,\
                                   dummyligobj,dummyligobj,dummyligobj,dummyligobj,dummyligobj,\
                                   dummyligobj,dummyligobj,dummyligobj,dummyligobj,dummyligobj,\
                                   dummyligobj,dummyligobj,dummyligobj,dummyligobj,dummyligobj,\
                                   dummyligobj,dummyligobj,dummyligobj,dummyligobj,dummyligobj,\
                                   dummyligobj,dummyligobj);\
    getListSizeFuncTuple = std::make_tuple(getListSize,dummyobj,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj);

#define IMPLE_INIT_TUPLE_2(CLASS,M1,M2) \
    std::function<decltype(M1)()> getobj1 = std::bind(&CLASS::__ReflectGet##M1,this);\
    std::function<decltype(M2)()> getobj2 = std::bind(&CLASS::__ReflectGet##M2,this);\
    std::function<void()> createobj1 = std::bind(&CLASS::__ReflectCreate##M1,this);\
    std::function<void()> createobj2 = std::bind(&CLASS::__ReflectCreate##M2,this);\
    std::function<sp<_Object>()>genItemObj1 = std::bind(&CLASS::__ReflectCreateListMember##M1,this);\
    std::function<sp<_Object>()>genItemObj2 = std::bind(&CLASS::__ReflectCreateListMember##M2,this);\
    std::function<sp<_Object>(int)>getItemObj1 = std::bind(&CLASS::__ReflectGetListItem##M1,this,std::placeholders::_1);\
    std::function<sp<_Object>(int)>getItemObj2 = std::bind(&CLASS::__ReflectGetListItem##M2,this,std::placeholders::_1);\
    std::function<int()>getListSize1 = std::bind(&CLASS::__ReflectGetListSize##M1,this);\
    std::function<int()>getListSize2 = std::bind(&CLASS::__ReflectGetListSize##M2,this);\
    getFuncTuple = std::make_tuple(getobj1,getobj2,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj);\
    createFuncTuple = std::make_tuple(createobj1,createobj2,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj);\
    createListItemFuncTuple = std::make_tuple(genItemObj1,genItemObj2,dummycreateobj,dummycreateobj,dummycreateobj,\
                                   dummycreateobj,dummycreateobj,dummycreateobj,dummycreateobj,dummycreateobj,\
                                   dummycreateobj,dummycreateobj,dummycreateobj,dummycreateobj,dummycreateobj,\
                                   dummycreateobj,dummycreateobj,dummycreateobj,dummycreateobj,dummycreateobj,\
                                   dummycreateobj,dummycreateobj,dummycreateobj,dummycreateobj,dummycreateobj,\
                                   dummycreateobj,dummycreateobj,dummycreateobj,dummycreateobj,dummycreateobj,\
                                   dummycreateobj,dummycreateobj);\
    getListItemFuncTuple = std::make_tuple(getItemObj1,getItemObj2,dummyligobj,dummyligobj,dummyligobj,\
                                   dummyligobj,dummyligobj,dummyligobj,dummyligobj,dummyligobj,\
                                   dummyligobj,dummyligobj,dummyligobj,dummyligobj,dummyligobj,\
                                   dummyligobj,dummyligobj,dummyligobj,dummyligobj,dummyligobj,\
                                   dummyligobj,dummyligobj,dummyligobj,dummyligobj,dummyligobj,\
                                   dummyligobj,dummyligobj,dummyligobj,dummyligobj,dummyligobj,\
                                   dummyligobj,dummyligobj);\
    getListSizeFuncTuple = std::make_tuple(getListSize1,getListSize2,dummyobj,dummyobj,dummyobj,\
                                dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                dummyobj,dummyobj);

#define IMPLE_INIT_TUPLE_3(CLASS,M1,M2,M3) \
    std::function<decltype(M1)()> getobj1 = std::bind(&CLASS::__ReflectGet##M1,this);\
    std::function<decltype(M2)()> getobj2 = std::bind(&CLASS::__ReflectGet##M2,this);\
    std::function<decltype(M3)()> getobj3 = std::bind(&CLASS::__ReflectGet##M3,this);\
    std::function<void()> createobj1 = std::bind(&CLASS::__ReflectCreate##M1,this);\
    std::function<void()> createobj2 = std::bind(&CLASS::__ReflectCreate##M2,this);\
    std::function<void()> createobj3 = std::bind(&CLASS::__ReflectCreate##M3,this);\
    std::function<sp<_Object>()>genItemObj1 = std::bind(&CLASS::__ReflectCreateListMember##M1,this);\
    std::function<sp<_Object>()>genItemObj2 = std::bind(&CLASS::__ReflectCreateListMember##M2,this);\
    std::function<sp<_Object>()>genItemObj3 = std::bind(&CLASS::__ReflectCreateListMember##M3,this);\
    std::function<sp<_Object>(int)>getItemObj1 = std::bind(&CLASS::__ReflectGetListItem##M1,this,std::placeholders::_1);\
    std::function<sp<_Object>(int)>getItemObj2 = std::bind(&CLASS::__ReflectGetListItem##M2,this,std::placeholders::_1);\
    std::function<sp<_Object>(int)>getItemObj3 = std::bind(&CLASS::__ReflectGetListItem##M3,this,std::placeholders::_1);\
    std::function<int()>getListSize1 = std::bind(&CLASS::__ReflectGetListSize##M1,this);\
    std::function<int()>getListSize2 = std::bind(&CLASS::__ReflectGetListSize##M2,this);\
    std::function<int()>getListSize3 = std::bind(&CLASS::__ReflectGetListSize##M3,this);\
    getFuncTuple = std::make_tuple(getobj1,getobj2,getobj3,dummyobj,dummyobj,\
                                   dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj);\
    createFuncTuple = std::make_tuple(createobj1,createobj2,createobj3,dummyobj,dummyobj,\
                                   dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj);\
    createListItemFuncTuple = std::make_tuple(genItemObj1,genItemObj2,genItemObj3,dummycreateobj,dummycreateobj,\
                                   dummycreateobj,dummycreateobj,dummycreateobj,dummycreateobj,dummycreateobj,\
                                   dummycreateobj,dummycreateobj,dummycreateobj,dummycreateobj,dummycreateobj,\
                                   dummycreateobj,dummycreateobj,dummycreateobj,dummycreateobj,dummycreateobj,\
                                   dummycreateobj,dummycreateobj,dummycreateobj,dummycreateobj,dummycreateobj,\
                                   dummycreateobj,dummycreateobj,dummycreateobj,dummycreateobj,dummycreateobj,\
                                   dummycreateobj,dummycreateobj);\
    getListItemFuncTuple = std::make_tuple(getItemObj1,getItemObj2,getItemObj3,dummyligobj,dummyligobj,\
                                   dummyligobj,dummyligobj,dummyligobj,dummyligobj,dummyligobj,\
                                   dummyligobj,dummyligobj,dummyligobj,dummyligobj,dummyligobj,\
                                   dummyligobj,dummyligobj,dummyligobj,dummyligobj,dummyligobj,\
                                   dummyligobj,dummyligobj,dummyligobj,dummyligobj,dummyligobj,\
                                   dummyligobj,dummyligobj,dummyligobj,dummyligobj,dummyligobj,\
                                   dummyligobj,dummyligobj);\
    getListSizeFuncTuple = std::make_tuple(getListSize1,getListSize2,getListSize3,dummyobj,dummyobj,\
                                dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                dummyobj,dummyobj);

#define IMPLE_INIT_TUPLE_4(CLASS,M1,M2,M3,M4) \
    std::function<decltype(M1)()> getobj1 = std::bind(&CLASS::__ReflectGet##M1,this);\
    std::function<decltype(M2)()> getobj2 = std::bind(&CLASS::__ReflectGet##M2,this);\
    std::function<decltype(M3)()> getobj3 = std::bind(&CLASS::__ReflectGet##M3,this);\
    std::function<decltype(M4)()> getobj4 = std::bind(&CLASS::__ReflectGet##M4,this);\
    std::function<void()> createobj1 = std::bind(&CLASS::__ReflectCreate##M1,this);\
    std::function<void()> createobj2 = std::bind(&CLASS::__ReflectCreate##M2,this);\
    std::function<void()> createobj3 = std::bind(&CLASS::__ReflectCreate##M3,this);\
    std::function<void()> createobj4 = std::bind(&CLASS::__ReflectCreate##M4,this);\
    std::function<sp<_Object>()>genItemObj1 = std::bind(&CLASS::__ReflectCreateListMember##M1,this);\
    std::function<sp<_Object>()>genItemObj2 = std::bind(&CLASS::__ReflectCreateListMember##M2,this);\
    std::function<sp<_Object>()>genItemObj3 = std::bind(&CLASS::__ReflectCreateListMember##M3,this);\
    std::function<sp<_Object>()>genItemObj4 = std::bind(&CLASS::__ReflectCreateListMember##M4,this);\
    std::function<sp<_Object>(int)>getItemObj1 = std::bind(&CLASS::__ReflectGetListItem##M1,this,std::placeholders::_1);\
    std::function<sp<_Object>(int)>getItemObj2 = std::bind(&CLASS::__ReflectGetListItem##M2,this,std::placeholders::_1);\
    std::function<sp<_Object>(int)>getItemObj3 = std::bind(&CLASS::__ReflectGetListItem##M3,this,std::placeholders::_1);\
    std::function<sp<_Object>(int)>getItemObj4 = std::bind(&CLASS::__ReflectGetListItem##M4,this,std::placeholders::_1);\
    std::function<int()>getListSize1 = std::bind(&CLASS::__ReflectGetListSize##M1,this);\
    std::function<int()>getListSize2 = std::bind(&CLASS::__ReflectGetListSize##M2,this);\
    std::function<int()>getListSize3 = std::bind(&CLASS::__ReflectGetListSize##M3,this);\
    std::function<int()>getListSize4 = std::bind(&CLASS::__ReflectGetListSize##M4,this);\
    getFuncTuple = std::make_tuple(getobj1,getobj2,getobj3,getobj4,dummyobj,\
                                   dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj);\
    createFuncTuple = std::make_tuple(createobj1,createobj2,createobj3,createobj4,dummyobj,\
                                   dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj);\
    createListItemFuncTuple = std::make_tuple(genItemObj1,genItemObj2,genItemObj3,genItemObj4,dummycreateobj,\
                                   dummycreateobj,dummycreateobj,dummycreateobj,dummycreateobj,dummycreateobj,\
                                   dummycreateobj,dummycreateobj,dummycreateobj,dummycreateobj,dummycreateobj,\
                                   dummycreateobj,dummycreateobj,dummycreateobj,dummycreateobj,dummycreateobj,\
                                   dummycreateobj,dummycreateobj,dummycreateobj,dummycreateobj,dummycreateobj,\
                                   dummycreateobj,dummycreateobj,dummycreateobj,dummycreateobj,dummycreateobj,\
                                   dummycreateobj,dummycreateobj);\
    getListItemFuncTuple = std::make_tuple(getItemObj1,getItemObj2,getItemObj3,getItemObj4,dummyligobj,\
                                   dummyligobj,dummyligobj,dummyligobj,dummyligobj,dummyligobj,\
                                   dummyligobj,dummyligobj,dummyligobj,dummyligobj,dummyligobj,\
                                   dummyligobj,dummyligobj,dummyligobj,dummyligobj,dummyligobj,\
                                   dummyligobj,dummyligobj,dummyligobj,dummyligobj,dummyligobj,\
                                   dummyligobj,dummyligobj,dummyligobj,dummyligobj,dummyligobj,\
                                   dummyligobj,dummyligobj);\
    getListSizeFuncTuple = std::make_tuple(getListSize1,getListSize2,getListSize3,getListSize4,dummyobj,\
                                dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                dummyobj,dummyobj);

#define IMPLE_INIT_TUPLE_5(CLASS,M1,M2,M3,M4,M5) \
    std::function<decltype(M1)()> getobj1 = std::bind(&CLASS::__ReflectGet##M1,this);\
    std::function<decltype(M2)()> getobj2 = std::bind(&CLASS::__ReflectGet##M2,this);\
    std::function<decltype(M3)()> getobj3 = std::bind(&CLASS::__ReflectGet##M3,this);\
    std::function<decltype(M4)()> getobj4 = std::bind(&CLASS::__ReflectGet##M4,this);\
    std::function<decltype(M5)()> getobj5 = std::bind(&CLASS::__ReflectGet##M5,this);\
    std::function<void()> createobj1 = std::bind(&CLASS::__ReflectCreate##M1,this);\
    std::function<void()> createobj2 = std::bind(&CLASS::__ReflectCreate##M2,this);\
    std::function<void()> createobj3 = std::bind(&CLASS::__ReflectCreate##M3,this);\
    std::function<void()> createobj4 = std::bind(&CLASS::__ReflectCreate##M4,this);\
    std::function<void()> createobj5 = std::bind(&CLASS::__ReflectCreate##M5,this);\
    std::function<sp<_Object>()>genItemObj1 = std::bind(&CLASS::__ReflectCreateListMember##M1,this);\
    std::function<sp<_Object>()>genItemObj2 = std::bind(&CLASS::__ReflectCreateListMember##M2,this);\
    std::function<sp<_Object>()>genItemObj3 = std::bind(&CLASS::__ReflectCreateListMember##M3,this);\
    std::function<sp<_Object>()>genItemObj4 = std::bind(&CLASS::__ReflectCreateListMember##M4,this);\
    std::function<sp<_Object>()>genItemObj5 = std::bind(&CLASS::__ReflectCreateListMember##M5,this);\
    std::function<sp<_Object>(int)>getItemObj1 = std::bind(&CLASS::__ReflectGetListItem##M1,this,std::placeholders::_1);\
    std::function<sp<_Object>(int)>getItemObj2 = std::bind(&CLASS::__ReflectGetListItem##M2,this,std::placeholders::_1);\
    std::function<sp<_Object>(int)>getItemObj3 = std::bind(&CLASS::__ReflectGetListItem##M3,this,std::placeholders::_1);\
    std::function<sp<_Object>(int)>getItemObj4 = std::bind(&CLASS::__ReflectGetListItem##M4,this,std::placeholders::_1);\
    std::function<sp<_Object>(int)>getItemObj5 = std::bind(&CLASS::__ReflectGetListItem##M5,this,std::placeholders::_1);\
    std::function<int()>getListSize1 = std::bind(&CLASS::__ReflectGetListSize##M1,this);\
    std::function<int()>getListSize2 = std::bind(&CLASS::__ReflectGetListSize##M2,this);\
    std::function<int()>getListSize3 = std::bind(&CLASS::__ReflectGetListSize##M3,this);\
    std::function<int()>getListSize4 = std::bind(&CLASS::__ReflectGetListSize##M4,this);\
    std::function<int()>getListSize5 = std::bind(&CLASS::__ReflectGetListSize##M5,this);\
    getFuncTuple = std::make_tuple(getobj1,getobj2,getobj3,getobj4,getobj5,\
                                   dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj);\
    createFuncTuple = std::make_tuple(createobj1,createobj2,createobj3,createobj4,createobj5,\
                                   dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj);\
    createListItemFuncTuple = std::make_tuple(genItemObj1,genItemObj2,genItemObj3,genItemObj4,genItemObj5,\
                                   dummycreateobj,dummycreateobj,dummycreateobj,dummycreateobj,dummycreateobj,\
                                   dummycreateobj,dummycreateobj,dummycreateobj,dummycreateobj,dummycreateobj,\
                                   dummycreateobj,dummycreateobj,dummycreateobj,dummycreateobj,dummycreateobj,\
                                   dummycreateobj,dummycreateobj,dummycreateobj,dummycreateobj,dummycreateobj,\
                                   dummycreateobj,dummycreateobj,dummycreateobj,dummycreateobj,dummycreateobj,\
                                   dummycreateobj,dummycreateobj);\
    getListItemFuncTuple = std::make_tuple(getItemObj1,getItemObj2,getItemObj3,getItemObj4,getItemObj5,\
                                   dummyligobj,dummyligobj,dummyligobj,dummyligobj,dummyligobj,\
                                   dummyligobj,dummyligobj,dummyligobj,dummyligobj,dummyligobj,\
                                   dummyligobj,dummyligobj,dummyligobj,dummyligobj,dummyligobj,\
                                   dummyligobj,dummyligobj,dummyligobj,dummyligobj,dummyligobj,\
                                   dummyligobj,dummyligobj,dummyligobj,dummyligobj,dummyligobj,\
                                   dummyligobj,dummyligobj);\
    getListSizeFuncTuple = std::make_tuple(getListSize1,getListSize2,getListSize3,getListSize4,getListSize5,\
                                dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                dummyobj,dummyobj);                                   

#define IMPLE_INIT_TUPLE_6(CLASS,M1,M2,M3,M4,M5,M6) \
    std::function<decltype(M1)()> getobj1 = std::bind(&CLASS::__ReflectGet##M1,this);\
    std::function<decltype(M2)()> getobj2 = std::bind(&CLASS::__ReflectGet##M2,this);\
    std::function<decltype(M3)()> getobj3 = std::bind(&CLASS::__ReflectGet##M3,this);\
    std::function<decltype(M4)()> getobj4 = std::bind(&CLASS::__ReflectGet##M4,this);\
    std::function<decltype(M5)()> getobj5 = std::bind(&CLASS::__ReflectGet##M5,this);\
    std::function<decltype(M6)()> getobj6 = std::bind(&CLASS::__ReflectGet##M6,this);\
    std::function<void()> createobj1 = std::bind(&CLASS::__ReflectCreate##M1,this);\
    std::function<void()> createobj2 = std::bind(&CLASS::__ReflectCreate##M2,this);\
    std::function<void()> createobj3 = std::bind(&CLASS::__ReflectCreate##M3,this);\
    std::function<void()> createobj4 = std::bind(&CLASS::__ReflectCreate##M4,this);\
    std::function<void()> createobj5 = std::bind(&CLASS::__ReflectCreate##M5,this);\
    std::function<void()> createobj6 = std::bind(&CLASS::__ReflectCreate##M6,this);\
    std::function<sp<_Object>()>genItemObj1 = std::bind(&CLASS::__ReflectCreateListMember##M1,this);\
    std::function<sp<_Object>()>genItemObj2 = std::bind(&CLASS::__ReflectCreateListMember##M2,this);\
    std::function<sp<_Object>()>genItemObj3 = std::bind(&CLASS::__ReflectCreateListMember##M3,this);\
    std::function<sp<_Object>()>genItemObj4 = std::bind(&CLASS::__ReflectCreateListMember##M4,this);\
    std::function<sp<_Object>()>genItemObj5 = std::bind(&CLASS::__ReflectCreateListMember##M5,this);\
    std::function<sp<_Object>()>genItemObj6 = std::bind(&CLASS::__ReflectCreateListMember##M6,this);\
    std::function<sp<_Object>(int)>getItemObj1 = std::bind(&CLASS::__ReflectGetListItem##M1,this,std::placeholders::_1);\
    std::function<sp<_Object>(int)>getItemObj2 = std::bind(&CLASS::__ReflectGetListItem##M2,this,std::placeholders::_1);\
    std::function<sp<_Object>(int)>getItemObj3 = std::bind(&CLASS::__ReflectGetListItem##M3,this,std::placeholders::_1);\
    std::function<sp<_Object>(int)>getItemObj4 = std::bind(&CLASS::__ReflectGetListItem##M4,this,std::placeholders::_1);\
    std::function<sp<_Object>(int)>getItemObj5 = std::bind(&CLASS::__ReflectGetListItem##M5,this,std::placeholders::_1);\
    std::function<sp<_Object>(int)>getItemObj6 = std::bind(&CLASS::__ReflectGetListItem##M6,this,std::placeholders::_1);\
    std::function<int()>getListSize1 = std::bind(&CLASS::__ReflectGetListSize##M1,this);\
    std::function<int()>getListSize2 = std::bind(&CLASS::__ReflectGetListSize##M2,this);\
    std::function<int()>getListSize3 = std::bind(&CLASS::__ReflectGetListSize##M3,this);\
    std::function<int()>getListSize4 = std::bind(&CLASS::__ReflectGetListSize##M4,this);\
    std::function<int()>getListSize5 = std::bind(&CLASS::__ReflectGetListSize##M5,this);\
    std::function<int()>getListSize6 = std::bind(&CLASS::__ReflectGetListSize##M6,this);\
    getFuncTuple = std::make_tuple(getobj1,getobj2,getobj3,getobj4,getobj5,\
                                   getobj6,dummyobj,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj);\
    createFuncTuple = std::make_tuple(createobj1,createobj2,createobj3,createobj4,createobj5,\
                                   createobj6,dummyobj,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj);\
    createListItemFuncTuple = std::make_tuple(genItemObj1,genItemObj2,genItemObj3,genItemObj4,genItemObj5,\
                                   genItemObj6,dummycreateobj,dummycreateobj,dummycreateobj,dummycreateobj,\
                                   dummycreateobj,dummycreateobj,dummycreateobj,dummycreateobj,dummycreateobj,\
                                   dummycreateobj,dummycreateobj,dummycreateobj,dummycreateobj,dummycreateobj,\
                                   dummycreateobj,dummycreateobj,dummycreateobj,dummycreateobj,dummycreateobj,\
                                   dummycreateobj,dummycreateobj,dummycreateobj,dummycreateobj,dummycreateobj,\
                                   dummycreateobj,dummycreateobj);\
    getListItemFuncTuple = std::make_tuple(getItemObj1,getItemObj2,getItemObj3,getItemObj4,getItemObj5,\
                                   getItemObj6,dummyligobj,dummyligobj,dummyligobj,dummyligobj,\
                                   dummyligobj,dummyligobj,dummyligobj,dummyligobj,dummyligobj,\
                                   dummyligobj,dummyligobj,dummyligobj,dummyligobj,dummyligobj,\
                                   dummyligobj,dummyligobj,dummyligobj,dummyligobj,dummyligobj,\
                                   dummyligobj,dummyligobj,dummyligobj,dummyligobj,dummyligobj,\
                                   dummyligobj,dummyligobj);\
    getListSizeFuncTuple = std::make_tuple(getListSize1,getListSize2,getListSize3,getListSize4,getListSize5,\
                            getListSize6,dummyobj,dummyobj,dummyobj,dummyobj,\
                            dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                            dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                            dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                            dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                            dummyobj,dummyobj);     

#define IMPLE_INIT_TUPLE_7(CLASS,M1,M2,M3,M4,M5,M6,M7) \
    std::function<decltype(M1)()> getobj1 = std::bind(&CLASS::__ReflectGet##M1,this);\
    std::function<decltype(M2)()> getobj2 = std::bind(&CLASS::__ReflectGet##M2,this);\
    std::function<decltype(M3)()> getobj3 = std::bind(&CLASS::__ReflectGet##M3,this);\
    std::function<decltype(M4)()> getobj4 = std::bind(&CLASS::__ReflectGet##M4,this);\
    std::function<decltype(M5)()> getobj5 = std::bind(&CLASS::__ReflectGet##M5,this);\
    std::function<decltype(M6)()> getobj6 = std::bind(&CLASS::__ReflectGet##M6,this);\
    std::function<decltype(M7)()> getobj7 = std::bind(&CLASS::__ReflectGet##M7,this);\
    std::function<void()> createobj1 = std::bind(&CLASS::__ReflectCreate##M1,this);\
    std::function<void()> createobj2 = std::bind(&CLASS::__ReflectCreate##M2,this);\
    std::function<void()> createobj3 = std::bind(&CLASS::__ReflectCreate##M3,this);\
    std::function<void()> createobj4 = std::bind(&CLASS::__ReflectCreate##M4,this);\
    std::function<void()> createobj5 = std::bind(&CLASS::__ReflectCreate##M5,this);\
    std::function<void()> createobj6 = std::bind(&CLASS::__ReflectCreate##M6,this);\
    std::function<void()> createobj7 = std::bind(&CLASS::__ReflectCreate##M7,this);\
    std::function<sp<_Object>()>genItemObj1 = std::bind(&CLASS::__ReflectCreateListMember##M1,this);\
    std::function<sp<_Object>()>genItemObj2 = std::bind(&CLASS::__ReflectCreateListMember##M2,this);\
    std::function<sp<_Object>()>genItemObj3 = std::bind(&CLASS::__ReflectCreateListMember##M3,this);\
    std::function<sp<_Object>()>genItemObj4 = std::bind(&CLASS::__ReflectCreateListMember##M4,this);\
    std::function<sp<_Object>()>genItemObj5 = std::bind(&CLASS::__ReflectCreateListMember##M5,this);\
    std::function<sp<_Object>()>genItemObj6 = std::bind(&CLASS::__ReflectCreateListMember##M6,this);\
    std::function<sp<_Object>()>genItemObj7 = std::bind(&CLASS::__ReflectCreateListMember##M7,this);\
    std::function<sp<_Object>(int)>getItemObj1 = std::bind(&CLASS::__ReflectGetListItem##M1,this,std::placeholders::_1);\
    std::function<sp<_Object>(int)>getItemObj2 = std::bind(&CLASS::__ReflectGetListItem##M2,this,std::placeholders::_1);\
    std::function<sp<_Object>(int)>getItemObj3 = std::bind(&CLASS::__ReflectGetListItem##M3,this,std::placeholders::_1);\
    std::function<sp<_Object>(int)>getItemObj4 = std::bind(&CLASS::__ReflectGetListItem##M4,this,std::placeholders::_1);\
    std::function<sp<_Object>(int)>getItemObj5 = std::bind(&CLASS::__ReflectGetListItem##M5,this,std::placeholders::_1);\
    std::function<sp<_Object>(int)>getItemObj6 = std::bind(&CLASS::__ReflectGetListItem##M6,this,std::placeholders::_1);\
    std::function<sp<_Object>(int)>getItemObj7 = std::bind(&CLASS::__ReflectGetListItem##M7,this,std::placeholders::_1);\
    std::function<int()>getListSize1 = std::bind(&CLASS::__ReflectGetListSize##M1,this);\
    std::function<int()>getListSize2 = std::bind(&CLASS::__ReflectGetListSize##M2,this);\
    std::function<int()>getListSize3 = std::bind(&CLASS::__ReflectGetListSize##M3,this);\
    std::function<int()>getListSize4 = std::bind(&CLASS::__ReflectGetListSize##M4,this);\
    std::function<int()>getListSize5 = std::bind(&CLASS::__ReflectGetListSize##M5,this);\
    std::function<int()>getListSize6 = std::bind(&CLASS::__ReflectGetListSize##M6,this);\
    std::function<int()>getListSize7 = std::bind(&CLASS::__ReflectGetListSize##M7,this);\
    getFuncTuple = std::make_tuple(getobj1,getobj2,getobj3,getobj4,getobj5,\
                                   getobj6,getobj7,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj);\
    createFuncTuple = std::make_tuple(createobj1,createobj2,createobj3,createobj4,createobj5,\
                                   createobj6,createobj7,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj);\
    createListItemFuncTuple = std::make_tuple(genItemObj1,genItemObj2,genItemObj3,genItemObj4,genItemObj5,\
                                   genItemObj6,genItemObj7,dummycreateobj,dummycreateobj,dummycreateobj,\
                                   dummycreateobj,dummycreateobj,dummycreateobj,dummycreateobj,dummycreateobj,\
                                   dummycreateobj,dummycreateobj,dummycreateobj,dummycreateobj,dummycreateobj,\
                                   dummycreateobj,dummycreateobj,dummycreateobj,dummycreateobj,dummycreateobj,\
                                   dummycreateobj,dummycreateobj,dummycreateobj,dummycreateobj,dummycreateobj,\
                                   dummycreateobj,dummycreateobj);\
    getListItemFuncTuple = std::make_tuple(getItemObj1,getItemObj2,getItemObj3,getItemObj4,getItemObj5,\
                                   getItemObj6,getItemObj7,dummyligobj,dummyligobj,dummyligobj,\
                                   dummyligobj,dummyligobj,dummyligobj,dummyligobj,dummyligobj,\
                                   dummyligobj,dummyligobj,dummyligobj,dummyligobj,dummyligobj,\
                                   dummyligobj,dummyligobj,dummyligobj,dummyligobj,dummyligobj,\
                                   dummyligobj,dummyligobj,dummyligobj,dummyligobj,dummyligobj,\
                                   dummyligobj,dummyligobj);\
    getListSizeFuncTuple = std::make_tuple(getListSize1,getListSize2,getListSize3,getListSize4,getListSize5,\
                        getListSize6,getListSize7,dummyobj,dummyobj,dummyobj,\
                        dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                        dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                        dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                        dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                        dummyobj,dummyobj); 

#define IMPLE_INIT_TUPLE_8(CLASS,M1,M2,M3,M4,M5,M6,M7,M8) \
    std::function<decltype(M1)()> getobj1 = std::bind(&CLASS::__ReflectGet##M1,this);\
    std::function<decltype(M2)()> getobj2 = std::bind(&CLASS::__ReflectGet##M2,this);\
    std::function<decltype(M3)()> getobj3 = std::bind(&CLASS::__ReflectGet##M3,this);\
    std::function<decltype(M4)()> getobj4 = std::bind(&CLASS::__ReflectGet##M4,this);\
    std::function<decltype(M5)()> getobj5 = std::bind(&CLASS::__ReflectGet##M5,this);\
    std::function<decltype(M6)()> getobj6 = std::bind(&CLASS::__ReflectGet##M6,this);\
    std::function<decltype(M7)()> getobj7 = std::bind(&CLASS::__ReflectGet##M7,this);\
    std::function<decltype(M8)()> getobj8 = std::bind(&CLASS::__ReflectGet##M8,this);\
    std::function<void()> createobj1 = std::bind(&CLASS::__ReflectCreate##M1,this);\
    std::function<void()> createobj2 = std::bind(&CLASS::__ReflectCreate##M2,this);\
    std::function<void()> createobj3 = std::bind(&CLASS::__ReflectCreate##M3,this);\
    std::function<void()> createobj4 = std::bind(&CLASS::__ReflectCreate##M4,this);\
    std::function<void()> createobj5 = std::bind(&CLASS::__ReflectCreate##M5,this);\
    std::function<void()> createobj6 = std::bind(&CLASS::__ReflectCreate##M6,this);\
    std::function<void()> createobj7 = std::bind(&CLASS::__ReflectCreate##M7,this);\
    std::function<void()> createobj8 = std::bind(&CLASS::__ReflectCreate##M8,this);\
    std::function<sp<_Object>()>genItemObj1 = std::bind(&CLASS::__ReflectCreateListMember##M1,this);\
    std::function<sp<_Object>()>genItemObj2 = std::bind(&CLASS::__ReflectCreateListMember##M2,this);\
    std::function<sp<_Object>()>genItemObj3 = std::bind(&CLASS::__ReflectCreateListMember##M3,this);\
    std::function<sp<_Object>()>genItemObj4 = std::bind(&CLASS::__ReflectCreateListMember##M4,this);\
    std::function<sp<_Object>()>genItemObj5 = std::bind(&CLASS::__ReflectCreateListMember##M5,this);\
    std::function<sp<_Object>()>genItemObj6 = std::bind(&CLASS::__ReflectCreateListMember##M6,this);\
    std::function<sp<_Object>()>genItemObj7 = std::bind(&CLASS::__ReflectCreateListMember##M7,this);\
    std::function<sp<_Object>()>genItemObj8 = std::bind(&CLASS::__ReflectCreateListMember##M8,this);\
    std::function<sp<_Object>(int)>getItemObj1 = std::bind(&CLASS::__ReflectGetListItem##M1,this,std::placeholders::_1);\
    std::function<sp<_Object>(int)>getItemObj2 = std::bind(&CLASS::__ReflectGetListItem##M2,this,std::placeholders::_1);\
    std::function<sp<_Object>(int)>getItemObj3 = std::bind(&CLASS::__ReflectGetListItem##M3,this,std::placeholders::_1);\
    std::function<sp<_Object>(int)>getItemObj4 = std::bind(&CLASS::__ReflectGetListItem##M4,this,std::placeholders::_1);\
    std::function<sp<_Object>(int)>getItemObj5 = std::bind(&CLASS::__ReflectGetListItem##M5,this,std::placeholders::_1);\
    std::function<sp<_Object>(int)>getItemObj6 = std::bind(&CLASS::__ReflectGetListItem##M6,this,std::placeholders::_1);\
    std::function<sp<_Object>(int)>getItemObj7 = std::bind(&CLASS::__ReflectGetListItem##M7,this,std::placeholders::_1);\
    std::function<sp<_Object>(int)>getItemObj8 = std::bind(&CLASS::__ReflectGetListItem##M8,this,std::placeholders::_1);\
    std::function<int()>getListSize1 = std::bind(&CLASS::__ReflectGetListSize##M1,this);\
    std::function<int()>getListSize2 = std::bind(&CLASS::__ReflectGetListSize##M2,this);\
    std::function<int()>getListSize3 = std::bind(&CLASS::__ReflectGetListSize##M3,this);\
    std::function<int()>getListSize4 = std::bind(&CLASS::__ReflectGetListSize##M4,this);\
    std::function<int()>getListSize5 = std::bind(&CLASS::__ReflectGetListSize##M5,this);\
    std::function<int()>getListSize6 = std::bind(&CLASS::__ReflectGetListSize##M6,this);\
    std::function<int()>getListSize7 = std::bind(&CLASS::__ReflectGetListSize##M7,this);\
    std::function<int()>getListSize8 = std::bind(&CLASS::__ReflectGetListSize##M8,this);\
    getFuncTuple = std::make_tuple(getobj1,getobj2,getobj3,getobj4,getobj5,\
                                   getobj6,getobj7,getobj8,dummyobj,dummyobj,\
                                   dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj);\
    createFuncTuple = std::make_tuple(createobj1,createobj2,createobj3,createobj4,createobj5,\
                                   createobj6,createobj7,createobj8,dummyobj,dummyobj,\
                                   dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj);\
    createListItemFuncTuple = std::make_tuple(genItemObj1,genItemObj2,genItemObj3,genItemObj4,genItemObj5,\
                                   genItemObj6,genItemObj7,genItemObj8,dummycreateobj,dummycreateobj,\
                                   dummycreateobj,dummycreateobj,dummycreateobj,dummycreateobj,dummycreateobj,\
                                   dummycreateobj,dummycreateobj,dummycreateobj,dummycreateobj,dummycreateobj,\
                                   dummycreateobj,dummycreateobj,dummycreateobj,dummycreateobj,dummycreateobj,\
                                   dummycreateobj,dummycreateobj,dummycreateobj,dummycreateobj,dummycreateobj,\
                                   dummycreateobj,dummycreateobj);\
    getListItemFuncTuple = std::make_tuple(getItemObj1,getItemObj2,getItemObj3,getItemObj4,getItemObj5,\
                                   getItemObj6,getItemObj7,getItemObj8,dummyligobj,dummyligobj,\
                                   dummyligobj,dummyligobj,dummyligobj,dummyligobj,dummyligobj,\
                                   dummyligobj,dummyligobj,dummyligobj,dummyligobj,dummyligobj,\
                                   dummyligobj,dummyligobj,dummyligobj,dummyligobj,dummyligobj,\
                                   dummyligobj,dummyligobj,dummyligobj,dummyligobj,dummyligobj,\
                                   dummyligobj,dummyligobj);\
    getListSizeFuncTuple = std::make_tuple(getListSize1,getListSize2,getListSize3,getListSize4,getListSize5,\
                    getListSize6,getListSize7,getListSize8,dummyobj,dummyobj,\
                    dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                    dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                    dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                    dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                    dummyobj,dummyobj); 

#define IMPLE_INIT_TUPLE_9(CLASS,M1,M2,M3,M4,M5,M6,M7,M8,M9) \
    std::function<decltype(M1)()> getobj1 = std::bind(&CLASS::__ReflectGet##M1,this);\
    std::function<decltype(M2)()> getobj2 = std::bind(&CLASS::__ReflectGet##M2,this);\
    std::function<decltype(M3)()> getobj3 = std::bind(&CLASS::__ReflectGet##M3,this);\
    std::function<decltype(M4)()> getobj4 = std::bind(&CLASS::__ReflectGet##M4,this);\
    std::function<decltype(M5)()> getobj5 = std::bind(&CLASS::__ReflectGet##M5,this);\
    std::function<decltype(M6)()> getobj6 = std::bind(&CLASS::__ReflectGet##M6,this);\
    std::function<decltype(M7)()> getobj7 = std::bind(&CLASS::__ReflectGet##M7,this);\
    std::function<decltype(M8)()> getobj8 = std::bind(&CLASS::__ReflectGet##M8,this);\
    std::function<decltype(M9)()> getobj9 = std::bind(&CLASS::__ReflectGet##M9,this);\
    std::function<void()> createobj1 = std::bind(&CLASS::__ReflectCreate##M1,this);\
    std::function<void()> createobj2 = std::bind(&CLASS::__ReflectCreate##M2,this);\
    std::function<void()> createobj3 = std::bind(&CLASS::__ReflectCreate##M3,this);\
    std::function<void()> createobj4 = std::bind(&CLASS::__ReflectCreate##M4,this);\
    std::function<void()> createobj5 = std::bind(&CLASS::__ReflectCreate##M5,this);\
    std::function<void()> createobj6 = std::bind(&CLASS::__ReflectCreate##M6,this);\
    std::function<void()> createobj7 = std::bind(&CLASS::__ReflectCreate##M7,this);\
    std::function<void()> createobj8 = std::bind(&CLASS::__ReflectCreate##M8,this);\
    std::function<void()> createobj9 = std::bind(&CLASS::__ReflectCreate##M9,this);\
    std::function<sp<_Object>()>genItemObj1 = std::bind(&CLASS::__ReflectCreateListMember##M1,this);\
    std::function<sp<_Object>()>genItemObj2 = std::bind(&CLASS::__ReflectCreateListMember##M2,this);\
    std::function<sp<_Object>()>genItemObj3 = std::bind(&CLASS::__ReflectCreateListMember##M3,this);\
    std::function<sp<_Object>()>genItemObj4 = std::bind(&CLASS::__ReflectCreateListMember##M4,this);\
    std::function<sp<_Object>()>genItemObj5 = std::bind(&CLASS::__ReflectCreateListMember##M5,this);\
    std::function<sp<_Object>()>genItemObj6 = std::bind(&CLASS::__ReflectCreateListMember##M6,this);\
    std::function<sp<_Object>()>genItemObj7 = std::bind(&CLASS::__ReflectCreateListMember##M7,this);\
    std::function<sp<_Object>()>genItemObj8 = std::bind(&CLASS::__ReflectCreateListMember##M8,this);\
    std::function<sp<_Object>()>genItemObj9 = std::bind(&CLASS::__ReflectCreateListMember##M9,this);\
    std::function<sp<_Object>(int)>getItemObj1 = std::bind(&CLASS::__ReflectGetListItem##M1,this,std::placeholders::_1);\
    std::function<sp<_Object>(int)>getItemObj2 = std::bind(&CLASS::__ReflectGetListItem##M2,this,std::placeholders::_1);\
    std::function<sp<_Object>(int)>getItemObj3 = std::bind(&CLASS::__ReflectGetListItem##M3,this,std::placeholders::_1);\
    std::function<sp<_Object>(int)>getItemObj4 = std::bind(&CLASS::__ReflectGetListItem##M4,this,std::placeholders::_1);\
    std::function<sp<_Object>(int)>getItemObj5 = std::bind(&CLASS::__ReflectGetListItem##M5,this,std::placeholders::_1);\
    std::function<sp<_Object>(int)>getItemObj6 = std::bind(&CLASS::__ReflectGetListItem##M6,this,std::placeholders::_1);\
    std::function<sp<_Object>(int)>getItemObj7 = std::bind(&CLASS::__ReflectGetListItem##M7,this,std::placeholders::_1);\
    std::function<sp<_Object>(int)>getItemObj8 = std::bind(&CLASS::__ReflectGetListItem##M8,this,std::placeholders::_1);\
    std::function<sp<_Object>(int)>getItemObj9 = std::bind(&CLASS::__ReflectGetListItem##M9,this,std::placeholders::_1);\
    std::function<int()>getListSize1 = std::bind(&CLASS::__ReflectGetListSize##M1,this);\
    std::function<int()>getListSize2 = std::bind(&CLASS::__ReflectGetListSize##M2,this);\
    std::function<int()>getListSize3 = std::bind(&CLASS::__ReflectGetListSize##M3,this);\
    std::function<int()>getListSize4 = std::bind(&CLASS::__ReflectGetListSize##M4,this);\
    std::function<int()>getListSize5 = std::bind(&CLASS::__ReflectGetListSize##M5,this);\
    std::function<int()>getListSize6 = std::bind(&CLASS::__ReflectGetListSize##M6,this);\
    std::function<int()>getListSize7 = std::bind(&CLASS::__ReflectGetListSize##M7,this);\
    std::function<int()>getListSize8 = std::bind(&CLASS::__ReflectGetListSize##M8,this);\
    std::function<int()>getListSize9 = std::bind(&CLASS::__ReflectGetListSize##M9,this);\
    getFuncTuple = std::make_tuple(getobj1,getobj2,getobj3,getobj4,getobj5,\
                                   getobj6,getobj7,getobj8,getobj9,dummyobj,\
                                   dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj);\
    createFuncTuple = std::make_tuple(createobj1,createobj2,createobj3,createobj4,createobj5,\
                                   createobj6,createobj7,createobj8,createobj9,dummyobj,\
                                   dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj);\
    createListItemFuncTuple = std::make_tuple(genItemObj1,genItemObj2,genItemObj3,genItemObj4,genItemObj5,\
                                   genItemObj6,genItemObj7,genItemObj8,genItemObj9,dummycreateobj,\
                                   dummycreateobj,dummycreateobj,dummycreateobj,dummycreateobj,dummycreateobj,\
                                   dummycreateobj,dummycreateobj,dummycreateobj,dummycreateobj,dummycreateobj,\
                                   dummycreateobj,dummycreateobj,dummycreateobj,dummycreateobj,dummycreateobj,\
                                   dummycreateobj,dummycreateobj,dummycreateobj,dummycreateobj,dummycreateobj,\
                                   dummycreateobj,dummycreateobj);\
    getListItemFuncTuple = std::make_tuple(getItemObj1,getItemObj2,getItemObj3,getItemObj4,getItemObj5,\
                                   getItemObj6,getItemObj7,getItemObj8,getItemObj9,dummyligobj,\
                                   dummyligobj,dummyligobj,dummyligobj,dummyligobj,dummyligobj,\
                                   dummyligobj,dummyligobj,dummyligobj,dummyligobj,dummyligobj,\
                                   dummyligobj,dummyligobj,dummyligobj,dummyligobj,dummyligobj,\
                                   dummyligobj,dummyligobj,dummyligobj,dummyligobj,dummyligobj,\
                                   dummyligobj,dummyligobj);\
    getListSizeFuncTuple = std::make_tuple(getListSize1,getListSize2,getListSize3,getListSize4,getListSize5,\
                getListSize6,getListSize7,getListSize8,getListSize9,dummyobj,\
                dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                dummyobj,dummyobj); 

#define IMPLE_INIT_TUPLE_10(CLASS,M1,M2,M3,M4,M5,M6,M7,M8,M9,M10) \
    std::function<decltype(M1)()> getobj1 = std::bind(&CLASS::__ReflectGet##M1,this);\
    std::function<decltype(M2)()> getobj2 = std::bind(&CLASS::__ReflectGet##M2,this);\
    std::function<decltype(M3)()> getobj3 = std::bind(&CLASS::__ReflectGet##M3,this);\
    std::function<decltype(M4)()> getobj4 = std::bind(&CLASS::__ReflectGet##M4,this);\
    std::function<decltype(M5)()> getobj5 = std::bind(&CLASS::__ReflectGet##M5,this);\
    std::function<decltype(M6)()> getobj6 = std::bind(&CLASS::__ReflectGet##M6,this);\
    std::function<decltype(M7)()> getobj7 = std::bind(&CLASS::__ReflectGet##M7,this);\
    std::function<decltype(M8)()> getobj8 = std::bind(&CLASS::__ReflectGet##M8,this);\
    std::function<decltype(M9)()> getobj9 = std::bind(&CLASS::__ReflectGet##M9,this);\
    std::function<decltype(M10)()> getobj10 = std::bind(&CLASS::__ReflectGet##M10,this);\
    std::function<void()> createobj1 = std::bind(&CLASS::__ReflectCreate##M1,this);\
    std::function<void()> createobj2 = std::bind(&CLASS::__ReflectCreate##M2,this);\
    std::function<void()> createobj3 = std::bind(&CLASS::__ReflectCreate##M3,this);\
    std::function<void()> createobj4 = std::bind(&CLASS::__ReflectCreate##M4,this);\
    std::function<void()> createobj5 = std::bind(&CLASS::__ReflectCreate##M5,this);\
    std::function<void()> createobj6 = std::bind(&CLASS::__ReflectCreate##M6,this);\
    std::function<void()> createobj7 = std::bind(&CLASS::__ReflectCreate##M7,this);\
    std::function<void()> createobj8 = std::bind(&CLASS::__ReflectCreate##M8,this);\
    std::function<void()> createobj9 = std::bind(&CLASS::__ReflectCreate##M9,this);\
    std::function<void()> createobj10 = std::bind(&CLASS::__ReflectCreate##M10,this);\
    std::function<sp<_Object>()>genItemObj1 = std::bind(&CLASS::__ReflectCreateListMember##M1,this);\
    std::function<sp<_Object>()>genItemObj2 = std::bind(&CLASS::__ReflectCreateListMember##M2,this);\
    std::function<sp<_Object>()>genItemObj3 = std::bind(&CLASS::__ReflectCreateListMember##M3,this);\
    std::function<sp<_Object>()>genItemObj4 = std::bind(&CLASS::__ReflectCreateListMember##M4,this);\
    std::function<sp<_Object>()>genItemObj5 = std::bind(&CLASS::__ReflectCreateListMember##M5,this);\
    std::function<sp<_Object>()>genItemObj6 = std::bind(&CLASS::__ReflectCreateListMember##M6,this);\
    std::function<sp<_Object>()>genItemObj7 = std::bind(&CLASS::__ReflectCreateListMember##M7,this);\
    std::function<sp<_Object>()>genItemObj8 = std::bind(&CLASS::__ReflectCreateListMember##M8,this);\
    std::function<sp<_Object>()>genItemObj9 = std::bind(&CLASS::__ReflectCreateListMember##M9,this);\
    std::function<sp<_Object>()>genItemObj10 = std::bind(&CLASS::__ReflectCreateListMember##M10,this);\
    std::function<sp<_Object>(int)>getItemObj1 = std::bind(&CLASS::__ReflectGetListItem##M1,this,std::placeholders::_1);\
    std::function<sp<_Object>(int)>getItemObj2 = std::bind(&CLASS::__ReflectGetListItem##M2,this,std::placeholders::_1);\
    std::function<sp<_Object>(int)>getItemObj3 = std::bind(&CLASS::__ReflectGetListItem##M3,this,std::placeholders::_1);\
    std::function<sp<_Object>(int)>getItemObj4 = std::bind(&CLASS::__ReflectGetListItem##M4,this,std::placeholders::_1);\
    std::function<sp<_Object>(int)>getItemObj5 = std::bind(&CLASS::__ReflectGetListItem##M5,this,std::placeholders::_1);\
    std::function<sp<_Object>(int)>getItemObj6 = std::bind(&CLASS::__ReflectGetListItem##M6,this,std::placeholders::_1);\
    std::function<sp<_Object>(int)>getItemObj7 = std::bind(&CLASS::__ReflectGetListItem##M7,this,std::placeholders::_1);\
    std::function<sp<_Object>(int)>getItemObj8 = std::bind(&CLASS::__ReflectGetListItem##M8,this,std::placeholders::_1);\
    std::function<sp<_Object>(int)>getItemObj9 = std::bind(&CLASS::__ReflectGetListItem##M9,this,std::placeholders::_1);\
    std::function<sp<_Object>(int)>getItemObj10 = std::bind(&CLASS::__ReflectGetListItem##M10,this,std::placeholders::_1);\
    std::function<int()>getListSize1 = std::bind(&CLASS::__ReflectGetListSize##M1,this);\
    std::function<int()>getListSize2 = std::bind(&CLASS::__ReflectGetListSize##M2,this);\
    std::function<int()>getListSize3 = std::bind(&CLASS::__ReflectGetListSize##M3,this);\
    std::function<int()>getListSize4 = std::bind(&CLASS::__ReflectGetListSize##M4,this);\
    std::function<int()>getListSize5 = std::bind(&CLASS::__ReflectGetListSize##M5,this);\
    std::function<int()>getListSize6 = std::bind(&CLASS::__ReflectGetListSize##M6,this);\
    std::function<int()>getListSize7 = std::bind(&CLASS::__ReflectGetListSize##M7,this);\
    std::function<int()>getListSize8 = std::bind(&CLASS::__ReflectGetListSize##M8,this);\
    std::function<int()>getListSize9 = std::bind(&CLASS::__ReflectGetListSize##M9,this);\
    std::function<int()>getListSize10 = std::bind(&CLASS::__ReflectGetListSize##M10,this);\
    getFuncTuple = std::make_tuple(getobj1,getobj2,getobj3,getobj4,getobj5,\
                                   getobj6,getobj7,getobj8,getobj9,getobj10,\
                                   dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj);\
    createFuncTuple = std::make_tuple(createobj1,createobj2,createobj3,createobj4,createobj5,\
                                   createobj6,createobj7,createobj8,createobj9,createobj10,\
                                   dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj);\
    createListItemFuncTuple = std::make_tuple(genItemObj1,genItemObj2,genItemObj3,genItemObj4,genItemObj5,\
                                   genItemObj6,genItemObj7,genItemObj8,genItemObj9,genItemObj10,\
                                   dummycreateobj,dummycreateobj,dummycreateobj,dummycreateobj,dummycreateobj,\
                                   dummycreateobj,dummycreateobj,dummycreateobj,dummycreateobj,dummycreateobj,\
                                   dummycreateobj,dummycreateobj,dummycreateobj,dummycreateobj,dummycreateobj,\
                                   dummycreateobj,dummycreateobj,dummycreateobj,dummycreateobj,dummycreateobj,\
                                   dummycreateobj,dummycreateobj);\
    getListItemFuncTuple = std::make_tuple(getItemObj1,getItemObj2,getItemObj3,getItemObj4,getItemObj5,\
                                   getItemObj6,getItemObj7,getItemObj8,getItemObj9,getItemObj10,\
                                   dummyligobj,dummyligobj,dummyligobj,dummyligobj,dummyligobj,\
                                   dummyligobj,dummyligobj,dummyligobj,dummyligobj,dummyligobj,\
                                   dummyligobj,dummyligobj,dummyligobj,dummyligobj,dummyligobj,\
                                   dummyligobj,dummyligobj,dummyligobj,dummyligobj,dummyligobj,\
                                   dummyligobj,dummyligobj);\
    getListSizeFuncTuple = std::make_tuple(getListSize1,getListSize2,getListSize3,getListSize4,getListSize5,\
                getListSize6,getListSize7,getListSize8,getListSize9,getListSize10,\
                dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                dummyobj,dummyobj); 

#define IMPLE_INIT_TUPLE_11(CLASS,M1,M2,M3,M4,M5,M6,M7,M8,M9,M10,M11) \
    std::function<decltype(M1)()> getobj1 = std::bind(&CLASS::__ReflectGet##M1,this);\
    std::function<decltype(M2)()> getobj2 = std::bind(&CLASS::__ReflectGet##M2,this);\
    std::function<decltype(M3)()> getobj3 = std::bind(&CLASS::__ReflectGet##M3,this);\
    std::function<decltype(M4)()> getobj4 = std::bind(&CLASS::__ReflectGet##M4,this);\
    std::function<decltype(M5)()> getobj5 = std::bind(&CLASS::__ReflectGet##M5,this);\
    std::function<decltype(M6)()> getobj6 = std::bind(&CLASS::__ReflectGet##M6,this);\
    std::function<decltype(M7)()> getobj7 = std::bind(&CLASS::__ReflectGet##M7,this);\
    std::function<decltype(M8)()> getobj8 = std::bind(&CLASS::__ReflectGet##M8,this);\
    std::function<decltype(M9)()> getobj9 = std::bind(&CLASS::__ReflectGet##M9,this);\
    std::function<decltype(M10)()> getobj10 = std::bind(&CLASS::__ReflectGet##M10,this);\
    std::function<decltype(M11)()> getobj11 = std::bind(&CLASS::__ReflectGet##M11,this);\
    std::function<void()> createobj1 = std::bind(&CLASS::__ReflectCreate##M1,this);\
    std::function<void()> createobj2 = std::bind(&CLASS::__ReflectCreate##M2,this);\
    std::function<void()> createobj3 = std::bind(&CLASS::__ReflectCreate##M3,this);\
    std::function<void()> createobj4 = std::bind(&CLASS::__ReflectCreate##M4,this);\
    std::function<void()> createobj5 = std::bind(&CLASS::__ReflectCreate##M5,this);\
    std::function<void()> createobj6 = std::bind(&CLASS::__ReflectCreate##M6,this);\
    std::function<void()> createobj7 = std::bind(&CLASS::__ReflectCreate##M7,this);\
    std::function<void()> createobj8 = std::bind(&CLASS::__ReflectCreate##M8,this);\
    std::function<void()> createobj9 = std::bind(&CLASS::__ReflectCreate##M9,this);\
    std::function<void()> createobj10 = std::bind(&CLASS::__ReflectCreate##M10,this);\
    std::function<void()> createobj11 = std::bind(&CLASS::__ReflectCreate##M11,this);\
    std::function<sp<_Object>()>genItemObj1 = std::bind(&CLASS::__ReflectCreateListMember##M1,this);\
    std::function<sp<_Object>()>genItemObj2 = std::bind(&CLASS::__ReflectCreateListMember##M2,this);\
    std::function<sp<_Object>()>genItemObj3 = std::bind(&CLASS::__ReflectCreateListMember##M3,this);\
    std::function<sp<_Object>()>genItemObj4 = std::bind(&CLASS::__ReflectCreateListMember##M4,this);\
    std::function<sp<_Object>()>genItemObj5 = std::bind(&CLASS::__ReflectCreateListMember##M5,this);\
    std::function<sp<_Object>()>genItemObj6 = std::bind(&CLASS::__ReflectCreateListMember##M6,this);\
    std::function<sp<_Object>()>genItemObj7 = std::bind(&CLASS::__ReflectCreateListMember##M7,this);\
    std::function<sp<_Object>()>genItemObj8 = std::bind(&CLASS::__ReflectCreateListMember##M8,this);\
    std::function<sp<_Object>()>genItemObj9 = std::bind(&CLASS::__ReflectCreateListMember##M9,this);\
    std::function<sp<_Object>()>genItemObj10 = std::bind(&CLASS::__ReflectCreateListMember##M10,this);\
    std::function<sp<_Object>()>genItemObj11 = std::bind(&CLASS::__ReflectCreateListMember##M11,this);\
    std::function<sp<_Object>(int)>getItemObj1 = std::bind(&CLASS::__ReflectGetListItem##M1,this,std::placeholders::_1);\
    std::function<sp<_Object>(int)>getItemObj2 = std::bind(&CLASS::__ReflectGetListItem##M2,this,std::placeholders::_1);\
    std::function<sp<_Object>(int)>getItemObj3 = std::bind(&CLASS::__ReflectGetListItem##M3,this,std::placeholders::_1);\
    std::function<sp<_Object>(int)>getItemObj4 = std::bind(&CLASS::__ReflectGetListItem##M4,this,std::placeholders::_1);\
    std::function<sp<_Object>(int)>getItemObj5 = std::bind(&CLASS::__ReflectGetListItem##M5,this,std::placeholders::_1);\
    std::function<sp<_Object>(int)>getItemObj6 = std::bind(&CLASS::__ReflectGetListItem##M6,this,std::placeholders::_1);\
    std::function<sp<_Object>(int)>getItemObj7 = std::bind(&CLASS::__ReflectGetListItem##M7,this,std::placeholders::_1);\
    std::function<sp<_Object>(int)>getItemObj8 = std::bind(&CLASS::__ReflectGetListItem##M8,this,std::placeholders::_1);\
    std::function<sp<_Object>(int)>getItemObj9 = std::bind(&CLASS::__ReflectGetListItem##M9,this,std::placeholders::_1);\
    std::function<sp<_Object>(int)>getItemObj10 = std::bind(&CLASS::__ReflectGetListItem##M10,this,std::placeholders::_1);\
    std::function<sp<_Object>(int)>getItemObj11 = std::bind(&CLASS::__ReflectGetListItem##M11,this,std::placeholders::_1);\
    std::function<int()>getListSize1 = std::bind(&CLASS::__ReflectGetListSize##M1,this);\
    std::function<int()>getListSize2 = std::bind(&CLASS::__ReflectGetListSize##M2,this);\
    std::function<int()>getListSize3 = std::bind(&CLASS::__ReflectGetListSize##M3,this);\
    std::function<int()>getListSize4 = std::bind(&CLASS::__ReflectGetListSize##M4,this);\
    std::function<int()>getListSize5 = std::bind(&CLASS::__ReflectGetListSize##M5,this);\
    std::function<int()>getListSize6 = std::bind(&CLASS::__ReflectGetListSize##M6,this);\
    std::function<int()>getListSize7 = std::bind(&CLASS::__ReflectGetListSize##M7,this);\
    std::function<int()>getListSize8 = std::bind(&CLASS::__ReflectGetListSize##M8,this);\
    std::function<int()>getListSize9 = std::bind(&CLASS::__ReflectGetListSize##M9,this);\
    std::function<int()>getListSize10 = std::bind(&CLASS::__ReflectGetListSize##M10,this);\
    std::function<int()>getListSize11 = std::bind(&CLASS::__ReflectGetListSize##M11,this);\
    getFuncTuple = std::make_tuple(getobj1,getobj2,getobj3,getobj4,getobj5,\
                                   getobj6,getobj7,getobj8,getobj9,getobj10,\
                                   getobj11,dummyobj,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj);\
    createFuncTuple = std::make_tuple(createobj1,createobj2,createobj3,createobj4,createobj5,\
                                   createobj6,createobj7,createobj8,createobj9,createobj10,\
                                   createobj11,dummyobj,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj);\
    createListItemFuncTuple = std::make_tuple(genItemObj1,genItemObj2,genItemObj3,genItemObj4,genItemObj5,\
                                   genItemObj6,genItemObj7,genItemObj8,genItemObj9,genItemObj10,\
                                   genItemObj11,dummycreateobj,dummycreateobj,dummycreateobj,dummycreateobj,\
                                   dummycreateobj,dummycreateobj,dummycreateobj,dummycreateobj,dummycreateobj,\
                                   dummycreateobj,dummycreateobj,dummycreateobj,dummycreateobj,dummycreateobj,\
                                   dummycreateobj,dummycreateobj,dummycreateobj,dummycreateobj,dummycreateobj,\
                                   dummycreateobj,dummycreateobj);\
    getListItemFuncTuple = std::make_tuple(getItemObj1,getItemObj2,getItemObj3,getItemObj4,getItemObj5,\
                                   getItemObj6,getItemObj7,getItemObj8,getItemObj9,getItemObj10,\
                                   getItemObj11,dummyligobj,dummyligobj,dummyligobj,dummyligobj,\
                                   dummyligobj,dummyligobj,dummyligobj,dummyligobj,dummyligobj,\
                                   dummyligobj,dummyligobj,dummyligobj,dummyligobj,dummyligobj,\
                                   dummyligobj,dummyligobj,dummyligobj,dummyligobj,dummyligobj,\
                                   dummyligobj,dummyligobj);\
    getListSizeFuncTuple = std::make_tuple(getListSize1,getListSize2,getListSize3,getListSize4,getListSize5,\
                getListSize6,getListSize7,getListSize8,getListSize9,getListSize10,\
                getListSize11,dummyobj,dummyobj,dummyobj,dummyobj,\
                dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                dummyobj,dummyobj); 

#define IMPLE_INIT_TUPLE_12(CLASS,M1,M2,M3,M4,M5,M6,M7,M8,M9,M10,M11,M12) \
    std::function<decltype(M1)()> getobj1 = std::bind(&CLASS::__ReflectGet##M1,this);\
    std::function<decltype(M2)()> getobj2 = std::bind(&CLASS::__ReflectGet##M2,this);\
    std::function<decltype(M3)()> getobj3 = std::bind(&CLASS::__ReflectGet##M3,this);\
    std::function<decltype(M4)()> getobj4 = std::bind(&CLASS::__ReflectGet##M4,this);\
    std::function<decltype(M5)()> getobj5 = std::bind(&CLASS::__ReflectGet##M5,this);\
    std::function<decltype(M6)()> getobj6 = std::bind(&CLASS::__ReflectGet##M6,this);\
    std::function<decltype(M7)()> getobj7 = std::bind(&CLASS::__ReflectGet##M7,this);\
    std::function<decltype(M8)()> getobj8 = std::bind(&CLASS::__ReflectGet##M8,this);\
    std::function<decltype(M9)()> getobj9 = std::bind(&CLASS::__ReflectGet##M9,this);\
    std::function<decltype(M10)()> getobj10 = std::bind(&CLASS::__ReflectGet##M10,this);\
    std::function<decltype(M11)()> getobj11 = std::bind(&CLASS::__ReflectGet##M11,this);\
    std::function<decltype(M12)()> getobj12 = std::bind(&CLASS::__ReflectGet##M12,this);\
    std::function<void()> createobj1 = std::bind(&CLASS::__ReflectCreate##M1,this);\
    std::function<void()> createobj2 = std::bind(&CLASS::__ReflectCreate##M2,this);\
    std::function<void()> createobj3 = std::bind(&CLASS::__ReflectCreate##M3,this);\
    std::function<void()> createobj4 = std::bind(&CLASS::__ReflectCreate##M4,this);\
    std::function<void()> createobj5 = std::bind(&CLASS::__ReflectCreate##M5,this);\
    std::function<void()> createobj6 = std::bind(&CLASS::__ReflectCreate##M6,this);\
    std::function<void()> createobj7 = std::bind(&CLASS::__ReflectCreate##M7,this);\
    std::function<void()> createobj8 = std::bind(&CLASS::__ReflectCreate##M8,this);\
    std::function<void()> createobj9 = std::bind(&CLASS::__ReflectCreate##M9,this);\
    std::function<void()> createobj10 = std::bind(&CLASS::__ReflectCreate##M10,this);\
    std::function<void()> createobj11 = std::bind(&CLASS::__ReflectCreate##M11,this);\
    std::function<void()> createobj12 = std::bind(&CLASS::__ReflectCreate##M12,this);\
    std::function<sp<_Object>()>genItemObj1 = std::bind(&CLASS::__ReflectCreateListMember##M1,this);\
    std::function<sp<_Object>()>genItemObj2 = std::bind(&CLASS::__ReflectCreateListMember##M2,this);\
    std::function<sp<_Object>()>genItemObj3 = std::bind(&CLASS::__ReflectCreateListMember##M3,this);\
    std::function<sp<_Object>()>genItemObj4 = std::bind(&CLASS::__ReflectCreateListMember##M4,this);\
    std::function<sp<_Object>()>genItemObj5 = std::bind(&CLASS::__ReflectCreateListMember##M5,this);\
    std::function<sp<_Object>()>genItemObj6 = std::bind(&CLASS::__ReflectCreateListMember##M6,this);\
    std::function<sp<_Object>()>genItemObj7 = std::bind(&CLASS::__ReflectCreateListMember##M7,this);\
    std::function<sp<_Object>()>genItemObj8 = std::bind(&CLASS::__ReflectCreateListMember##M8,this);\
    std::function<sp<_Object>()>genItemObj9 = std::bind(&CLASS::__ReflectCreateListMember##M9,this);\
    std::function<sp<_Object>()>genItemObj10 = std::bind(&CLASS::__ReflectCreateListMember##M10,this);\
    std::function<sp<_Object>()>genItemObj11 = std::bind(&CLASS::__ReflectCreateListMember##M11,this);\
    std::function<sp<_Object>()>genItemObj12 = std::bind(&CLASS::__ReflectCreateListMember##M12,this);\
    std::function<sp<_Object>(int)>getItemObj1 = std::bind(&CLASS::__ReflectGetListItem##M1,this,std::placeholders::_1);\
    std::function<sp<_Object>(int)>getItemObj2 = std::bind(&CLASS::__ReflectGetListItem##M2,this,std::placeholders::_1);\
    std::function<sp<_Object>(int)>getItemObj3 = std::bind(&CLASS::__ReflectGetListItem##M3,this,std::placeholders::_1);\
    std::function<sp<_Object>(int)>getItemObj4 = std::bind(&CLASS::__ReflectGetListItem##M4,this,std::placeholders::_1);\
    std::function<sp<_Object>(int)>getItemObj5 = std::bind(&CLASS::__ReflectGetListItem##M5,this,std::placeholders::_1);\
    std::function<sp<_Object>(int)>getItemObj6 = std::bind(&CLASS::__ReflectGetListItem##M6,this,std::placeholders::_1);\
    std::function<sp<_Object>(int)>getItemObj7 = std::bind(&CLASS::__ReflectGetListItem##M7,this,std::placeholders::_1);\
    std::function<sp<_Object>(int)>getItemObj8 = std::bind(&CLASS::__ReflectGetListItem##M8,this,std::placeholders::_1);\
    std::function<sp<_Object>(int)>getItemObj9 = std::bind(&CLASS::__ReflectGetListItem##M9,this,std::placeholders::_1);\
    std::function<sp<_Object>(int)>getItemObj10 = std::bind(&CLASS::__ReflectGetListItem##M10,this,std::placeholders::_1);\
    std::function<sp<_Object>(int)>getItemObj11 = std::bind(&CLASS::__ReflectGetListItem##M11,this,std::placeholders::_1);\
    std::function<sp<_Object>(int)>getItemObj12 = std::bind(&CLASS::__ReflectGetListItem##M12,this,std::placeholders::_1);\
    std::function<int()>getListSize1 = std::bind(&CLASS::__ReflectGetListSize##M1,this);\
    std::function<int()>getListSize2 = std::bind(&CLASS::__ReflectGetListSize##M2,this);\
    std::function<int()>getListSize3 = std::bind(&CLASS::__ReflectGetListSize##M3,this);\
    std::function<int()>getListSize4 = std::bind(&CLASS::__ReflectGetListSize##M4,this);\
    std::function<int()>getListSize5 = std::bind(&CLASS::__ReflectGetListSize##M5,this);\
    std::function<int()>getListSize6 = std::bind(&CLASS::__ReflectGetListSize##M6,this);\
    std::function<int()>getListSize7 = std::bind(&CLASS::__ReflectGetListSize##M7,this);\
    std::function<int()>getListSize8 = std::bind(&CLASS::__ReflectGetListSize##M8,this);\
    std::function<int()>getListSize9 = std::bind(&CLASS::__ReflectGetListSize##M9,this);\
    std::function<int()>getListSize10 = std::bind(&CLASS::__ReflectGetListSize##M10,this);\
    std::function<int()>getListSize11 = std::bind(&CLASS::__ReflectGetListSize##M11,this);\
    std::function<int()>getListSize12 = std::bind(&CLASS::__ReflectGetListSize##M12,this);\
    getFuncTuple = std::make_tuple(getobj1,getobj2,getobj3,getobj4,getobj5,\
                                   getobj6,getobj7,getobj8,getobj9,getobj10,\
                                   getobj11,getobj12,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj);\
    createFuncTuple = std::make_tuple(createobj1,createobj2,createobj3,createobj4,createobj5,\
                                   createobj6,createobj7,createobj8,createobj9,createobj10,\
                                   createobj11,createobj12,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj);\
    createListItemFuncTuple = std::make_tuple(genItemObj1,genItemObj2,genItemObj3,genItemObj4,genItemObj5,\
                                   genItemObj6,genItemObj7,genItemObj8,genItemObj9,genItemObj10,\
                                   genItemObj11,genItemObj12,dummycreateobj,dummycreateobj,dummycreateobj,\
                                   dummycreateobj,dummycreateobj,dummycreateobj,dummycreateobj,dummycreateobj,\
                                   dummycreateobj,dummycreateobj,dummycreateobj,dummycreateobj,dummycreateobj,\
                                   dummycreateobj,dummycreateobj,dummycreateobj,dummycreateobj,dummycreateobj,\
                                   dummycreateobj,dummycreateobj);\
    getListItemFuncTuple = std::make_tuple(getItemObj1,getItemObj2,getItemObj3,getItemObj4,getItemObj5,\
                                   getItemObj6,getItemObj7,getItemObj8,getItemObj9,getItemObj10,\
                                   getItemObj11,getItemObj12,dummyligobj,dummyligobj,dummyligobj,\
                                   dummyligobj,dummyligobj,dummyligobj,dummyligobj,dummyligobj,\
                                   dummyligobj,dummyligobj,dummyligobj,dummyligobj,dummyligobj,\
                                   dummyligobj,dummyligobj,dummyligobj,dummyligobj,dummyligobj,\
                                   dummyligobj,dummyligobj);\
    getListSizeFuncTuple = std::make_tuple(getListSize1,getListSize2,getListSize3,getListSize4,getListSize5,\
            getListSize6,getListSize7,getListSize8,getListSize9,getListSize10,\
            getListSize11,getListSize12,dummyobj,dummyobj,dummyobj,\
            dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
            dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
            dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
            dummyobj,dummyobj); 

#define IMPLE_INIT_TUPLE_13(CLASS,M1,M2,M3,M4,M5,M6,M7,M8,M9,M10,M11,M12,M13) \
    std::function<decltype(M1)()> getobj1 = std::bind(&CLASS::__ReflectGet##M1,this);\
    std::function<decltype(M2)()> getobj2 = std::bind(&CLASS::__ReflectGet##M2,this);\
    std::function<decltype(M3)()> getobj3 = std::bind(&CLASS::__ReflectGet##M3,this);\
    std::function<decltype(M4)()> getobj4 = std::bind(&CLASS::__ReflectGet##M4,this);\
    std::function<decltype(M5)()> getobj5 = std::bind(&CLASS::__ReflectGet##M5,this);\
    std::function<decltype(M6)()> getobj6 = std::bind(&CLASS::__ReflectGet##M6,this);\
    std::function<decltype(M7)()> getobj7 = std::bind(&CLASS::__ReflectGet##M7,this);\
    std::function<decltype(M8)()> getobj8 = std::bind(&CLASS::__ReflectGet##M8,this);\
    std::function<decltype(M9)()> getobj9 = std::bind(&CLASS::__ReflectGet##M9,this);\
    std::function<decltype(M10)()> getobj10 = std::bind(&CLASS::__ReflectGet##M10,this);\
    std::function<decltype(M11)()> getobj11 = std::bind(&CLASS::__ReflectGet##M11,this);\
    std::function<decltype(M12)()> getobj12 = std::bind(&CLASS::__ReflectGet##M12,this);\
    std::function<decltype(M13)()> getobj13 = std::bind(&CLASS::__ReflectGet##M13,this);\
    std::function<void()> createobj1 = std::bind(&CLASS::__ReflectCreate##M1,this);\
    std::function<void()> createobj2 = std::bind(&CLASS::__ReflectCreate##M2,this);\
    std::function<void()> createobj3 = std::bind(&CLASS::__ReflectCreate##M3,this);\
    std::function<void()> createobj4 = std::bind(&CLASS::__ReflectCreate##M4,this);\
    std::function<void()> createobj5 = std::bind(&CLASS::__ReflectCreate##M5,this);\
    std::function<void()> createobj6 = std::bind(&CLASS::__ReflectCreate##M6,this);\
    std::function<void()> createobj7 = std::bind(&CLASS::__ReflectCreate##M7,this);\
    std::function<void()> createobj8 = std::bind(&CLASS::__ReflectCreate##M8,this);\
    std::function<void()> createobj9 = std::bind(&CLASS::__ReflectCreate##M9,this);\
    std::function<void()> createobj10 = std::bind(&CLASS::__ReflectCreate##M10,this);\
    std::function<void()> createobj11 = std::bind(&CLASS::__ReflectCreate##M11,this);\
    std::function<void()> createobj12 = std::bind(&CLASS::__ReflectCreate##M12,this);\
    std::function<void()> createobj13 = std::bind(&CLASS::__ReflectCreate##M13,this);\
    std::function<sp<_Object>()>genItemObj1 = std::bind(&CLASS::__ReflectCreateListMember##M1,this);\
    std::function<sp<_Object>()>genItemObj2 = std::bind(&CLASS::__ReflectCreateListMember##M2,this);\
    std::function<sp<_Object>()>genItemObj3 = std::bind(&CLASS::__ReflectCreateListMember##M3,this);\
    std::function<sp<_Object>()>genItemObj4 = std::bind(&CLASS::__ReflectCreateListMember##M4,this);\
    std::function<sp<_Object>()>genItemObj5 = std::bind(&CLASS::__ReflectCreateListMember##M5,this);\
    std::function<sp<_Object>()>genItemObj6 = std::bind(&CLASS::__ReflectCreateListMember##M6,this);\
    std::function<sp<_Object>()>genItemObj7 = std::bind(&CLASS::__ReflectCreateListMember##M7,this);\
    std::function<sp<_Object>()>genItemObj8 = std::bind(&CLASS::__ReflectCreateListMember##M8,this);\
    std::function<sp<_Object>()>genItemObj9 = std::bind(&CLASS::__ReflectCreateListMember##M9,this);\
    std::function<sp<_Object>()>genItemObj10 = std::bind(&CLASS::__ReflectCreateListMember##M10,this);\
    std::function<sp<_Object>()>genItemObj11 = std::bind(&CLASS::__ReflectCreateListMember##M11,this);\
    std::function<sp<_Object>()>genItemObj12 = std::bind(&CLASS::__ReflectCreateListMember##M12,this);\
    std::function<sp<_Object>()>genItemObj13 = std::bind(&CLASS::__ReflectCreateListMember##M13,this);\
    std::function<sp<_Object>(int)>getItemObj1 = std::bind(&CLASS::__ReflectGetListItem##M1,this,std::placeholders::_1);\
    std::function<sp<_Object>(int)>getItemObj2 = std::bind(&CLASS::__ReflectGetListItem##M2,this,std::placeholders::_1);\
    std::function<sp<_Object>(int)>getItemObj3 = std::bind(&CLASS::__ReflectGetListItem##M3,this,std::placeholders::_1);\
    std::function<sp<_Object>(int)>getItemObj4 = std::bind(&CLASS::__ReflectGetListItem##M4,this,std::placeholders::_1);\
    std::function<sp<_Object>(int)>getItemObj5 = std::bind(&CLASS::__ReflectGetListItem##M5,this,std::placeholders::_1);\
    std::function<sp<_Object>(int)>getItemObj6 = std::bind(&CLASS::__ReflectGetListItem##M6,this,std::placeholders::_1);\
    std::function<sp<_Object>(int)>getItemObj7 = std::bind(&CLASS::__ReflectGetListItem##M7,this,std::placeholders::_1);\
    std::function<sp<_Object>(int)>getItemObj8 = std::bind(&CLASS::__ReflectGetListItem##M8,this,std::placeholders::_1);\
    std::function<sp<_Object>(int)>getItemObj9 = std::bind(&CLASS::__ReflectGetListItem##M9,this,std::placeholders::_1);\
    std::function<sp<_Object>(int)>getItemObj10 = std::bind(&CLASS::__ReflectGetListItem##M10,this,std::placeholders::_1);\
    std::function<sp<_Object>(int)>getItemObj11 = std::bind(&CLASS::__ReflectGetListItem##M11,this,std::placeholders::_1);\
    std::function<sp<_Object>(int)>getItemObj12 = std::bind(&CLASS::__ReflectGetListItem##M12,this,std::placeholders::_1);\
    std::function<sp<_Object>(int)>getItemObj13 = std::bind(&CLASS::__ReflectGetListItem##M13,this,std::placeholders::_1);\
    std::function<int()>getListSize1 = std::bind(&CLASS::__ReflectGetListSize##M1,this);\
    std::function<int()>getListSize2 = std::bind(&CLASS::__ReflectGetListSize##M2,this);\
    std::function<int()>getListSize3 = std::bind(&CLASS::__ReflectGetListSize##M3,this);\
    std::function<int()>getListSize4 = std::bind(&CLASS::__ReflectGetListSize##M4,this);\
    std::function<int()>getListSize5 = std::bind(&CLASS::__ReflectGetListSize##M5,this);\
    std::function<int()>getListSize6 = std::bind(&CLASS::__ReflectGetListSize##M6,this);\
    std::function<int()>getListSize7 = std::bind(&CLASS::__ReflectGetListSize##M7,this);\
    std::function<int()>getListSize8 = std::bind(&CLASS::__ReflectGetListSize##M8,this);\
    std::function<int()>getListSize9 = std::bind(&CLASS::__ReflectGetListSize##M9,this);\
    std::function<int()>getListSize10 = std::bind(&CLASS::__ReflectGetListSize##M10,this);\
    std::function<int()>getListSize11 = std::bind(&CLASS::__ReflectGetListSize##M11,this);\
    std::function<int()>getListSize12 = std::bind(&CLASS::__ReflectGetListSize##M12,this);\
    std::function<int()>getListSize13 = std::bind(&CLASS::__ReflectGetListSize##M13,this);\
    getFuncTuple = std::make_tuple(getobj1,getobj2,getobj3,getobj4,getobj5,\
                                   getobj6,getobj7,getobj8,getobj9,getobj10,\
                                   getobj11,getobj12,getobj13,dummyobj,dummyobj,\
                                   dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj);\
    createFuncTuple = std::make_tuple(createobj1,createobj2,createobj3,createobj4,createobj5,\
                                   createobj6,createobj7,createobj8,createobj9,createobj10,\
                                   createobj11,createobj12,createobj13,dummyobj,dummyobj,\
                                   dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj);\
    createListItemFuncTuple = std::make_tuple(genItemObj1,genItemObj2,genItemObj3,genItemObj4,genItemObj5,\
                                   genItemObj6,genItemObj7,genItemObj8,genItemObj9,genItemObj10,\
                                   genItemObj11,genItemObj12,genItemObj13,dummycreateobj,dummycreateobj,\
                                   dummycreateobj,dummycreateobj,dummycreateobj,dummycreateobj,dummycreateobj,\
                                   dummycreateobj,dummycreateobj,dummycreateobj,dummycreateobj,dummycreateobj,\
                                   dummycreateobj,dummycreateobj,dummycreateobj,dummycreateobj,dummycreateobj,\
                                   dummycreateobj,dummycreateobj);\
    getListItemFuncTuple = std::make_tuple(getItemObj1,getItemObj2,getItemObj3,getItemObj4,getItemObj5,\
                                   getItemObj6,getItemObj7,getItemObj8,getItemObj9,getItemObj10,\
                                   getItemObj11,getItemObj12,getItemObj13,dummyligobj,dummyligobj,\
                                   dummyligobj,dummyligobj,dummyligobj,dummyligobj,dummyligobj,\
                                   dummyligobj,dummyligobj,dummyligobj,dummyligobj,dummyligobj,\
                                   dummyligobj,dummyligobj,dummyligobj,dummyligobj,dummyligobj,\
                                   dummyligobj,dummyligobj);\
    getListSizeFuncTuple = std::make_tuple(getListSize1,getListSize2,getListSize3,getListSize4,getListSize5,\
            getListSize6,getListSize7,getListSize8,getListSize9,getListSize10,\
            getListSize11,getListSize12,getListSize13,dummyobj,dummyobj,\
            dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
            dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
            dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
            dummyobj,dummyobj); 

#define IMPLE_INIT_TUPLE_14(CLASS,M1,M2,M3,M4,M5,M6,M7,M8,M9,M10,M11,M12,M13,M14) \
    std::function<decltype(M1)()> getobj1 = std::bind(&CLASS::__ReflectGet##M1,this);\
    std::function<decltype(M2)()> getobj2 = std::bind(&CLASS::__ReflectGet##M2,this);\
    std::function<decltype(M3)()> getobj3 = std::bind(&CLASS::__ReflectGet##M3,this);\
    std::function<decltype(M4)()> getobj4 = std::bind(&CLASS::__ReflectGet##M4,this);\
    std::function<decltype(M5)()> getobj5 = std::bind(&CLASS::__ReflectGet##M5,this);\
    std::function<decltype(M6)()> getobj6 = std::bind(&CLASS::__ReflectGet##M6,this);\
    std::function<decltype(M7)()> getobj7 = std::bind(&CLASS::__ReflectGet##M7,this);\
    std::function<decltype(M8)()> getobj8 = std::bind(&CLASS::__ReflectGet##M8,this);\
    std::function<decltype(M9)()> getobj9 = std::bind(&CLASS::__ReflectGet##M9,this);\
    std::function<decltype(M10)()> getobj10 = std::bind(&CLASS::__ReflectGet##M10,this);\
    std::function<decltype(M11)()> getobj11 = std::bind(&CLASS::__ReflectGet##M11,this);\
    std::function<decltype(M12)()> getobj12 = std::bind(&CLASS::__ReflectGet##M12,this);\
    std::function<decltype(M13)()> getobj13 = std::bind(&CLASS::__ReflectGet##M13,this);\
    std::function<decltype(M14)()> getobj14 = std::bind(&CLASS::__ReflectGet##M14,this);\
    std::function<void()> createobj1 = std::bind(&CLASS::__ReflectCreate##M1,this);\
    std::function<void()> createobj2 = std::bind(&CLASS::__ReflectCreate##M2,this);\
    std::function<void()> createobj3 = std::bind(&CLASS::__ReflectCreate##M3,this);\
    std::function<void()> createobj4 = std::bind(&CLASS::__ReflectCreate##M4,this);\
    std::function<void()> createobj5 = std::bind(&CLASS::__ReflectCreate##M5,this);\
    std::function<void()> createobj6 = std::bind(&CLASS::__ReflectCreate##M6,this);\
    std::function<void()> createobj7 = std::bind(&CLASS::__ReflectCreate##M7,this);\
    std::function<void()> createobj8 = std::bind(&CLASS::__ReflectCreate##M8,this);\
    std::function<void()> createobj9 = std::bind(&CLASS::__ReflectCreate##M9,this);\
    std::function<void()> createobj10 = std::bind(&CLASS::__ReflectCreate##M10,this);\
    std::function<void()> createobj11 = std::bind(&CLASS::__ReflectCreate##M11,this);\
    std::function<void()> createobj12 = std::bind(&CLASS::__ReflectCreate##M12,this);\
    std::function<void()> createobj13 = std::bind(&CLASS::__ReflectCreate##M13,this);\
    std::function<void()> createobj14 = std::bind(&CLASS::__ReflectCreate##M14,this);\
    std::function<sp<_Object>()>genItemObj1 = std::bind(&CLASS::__ReflectCreateListMember##M1,this);\
    std::function<sp<_Object>()>genItemObj2 = std::bind(&CLASS::__ReflectCreateListMember##M2,this);\
    std::function<sp<_Object>()>genItemObj3 = std::bind(&CLASS::__ReflectCreateListMember##M3,this);\
    std::function<sp<_Object>()>genItemObj4 = std::bind(&CLASS::__ReflectCreateListMember##M4,this);\
    std::function<sp<_Object>()>genItemObj5 = std::bind(&CLASS::__ReflectCreateListMember##M5,this);\
    std::function<sp<_Object>()>genItemObj6 = std::bind(&CLASS::__ReflectCreateListMember##M6,this);\
    std::function<sp<_Object>()>genItemObj7 = std::bind(&CLASS::__ReflectCreateListMember##M7,this);\
    std::function<sp<_Object>()>genItemObj8 = std::bind(&CLASS::__ReflectCreateListMember##M8,this);\
    std::function<sp<_Object>()>genItemObj9 = std::bind(&CLASS::__ReflectCreateListMember##M9,this);\
    std::function<sp<_Object>()>genItemObj10 = std::bind(&CLASS::__ReflectCreateListMember##M10,this);\
    std::function<sp<_Object>()>genItemObj11 = std::bind(&CLASS::__ReflectCreateListMember##M11,this);\
    std::function<sp<_Object>()>genItemObj12 = std::bind(&CLASS::__ReflectCreateListMember##M12,this);\
    std::function<sp<_Object>()>genItemObj13 = std::bind(&CLASS::__ReflectCreateListMember##M13,this);\
    std::function<sp<_Object>()>genItemObj14 = std::bind(&CLASS::__ReflectCreateListMember##M14,this);\
    std::function<sp<_Object>(int)>getItemObj1 = std::bind(&CLASS::__ReflectGetListItem##M1,this,std::placeholders::_1);\
    std::function<sp<_Object>(int)>getItemObj2 = std::bind(&CLASS::__ReflectGetListItem##M2,this,std::placeholders::_1);\
    std::function<sp<_Object>(int)>getItemObj3 = std::bind(&CLASS::__ReflectGetListItem##M3,this,std::placeholders::_1);\
    std::function<sp<_Object>(int)>getItemObj4 = std::bind(&CLASS::__ReflectGetListItem##M4,this,std::placeholders::_1);\
    std::function<sp<_Object>(int)>getItemObj5 = std::bind(&CLASS::__ReflectGetListItem##M5,this,std::placeholders::_1);\
    std::function<sp<_Object>(int)>getItemObj6 = std::bind(&CLASS::__ReflectGetListItem##M6,this,std::placeholders::_1);\
    std::function<sp<_Object>(int)>getItemObj7 = std::bind(&CLASS::__ReflectGetListItem##M7,this,std::placeholders::_1);\
    std::function<sp<_Object>(int)>getItemObj8 = std::bind(&CLASS::__ReflectGetListItem##M8,this,std::placeholders::_1);\
    std::function<sp<_Object>(int)>getItemObj9 = std::bind(&CLASS::__ReflectGetListItem##M9,this,std::placeholders::_1);\
    std::function<sp<_Object>(int)>getItemObj10 = std::bind(&CLASS::__ReflectGetListItem##M10,this,std::placeholders::_1);\
    std::function<sp<_Object>(int)>getItemObj11 = std::bind(&CLASS::__ReflectGetListItem##M11,this,std::placeholders::_1);\
    std::function<sp<_Object>(int)>getItemObj12 = std::bind(&CLASS::__ReflectGetListItem##M12,this,std::placeholders::_1);\
    std::function<sp<_Object>(int)>getItemObj13 = std::bind(&CLASS::__ReflectGetListItem##M13,this,std::placeholders::_1);\
    std::function<sp<_Object>(int)>getItemObj14 = std::bind(&CLASS::__ReflectGetListItem##M14,this,std::placeholders::_1);\
    std::function<int()>getListSize1 = std::bind(&CLASS::__ReflectGetListSize##M1,this);\
    std::function<int()>getListSize2 = std::bind(&CLASS::__ReflectGetListSize##M2,this);\
    std::function<int()>getListSize3 = std::bind(&CLASS::__ReflectGetListSize##M3,this);\
    std::function<int()>getListSize4 = std::bind(&CLASS::__ReflectGetListSize##M4,this);\
    std::function<int()>getListSize5 = std::bind(&CLASS::__ReflectGetListSize##M5,this);\
    std::function<int()>getListSize6 = std::bind(&CLASS::__ReflectGetListSize##M6,this);\
    std::function<int()>getListSize7 = std::bind(&CLASS::__ReflectGetListSize##M7,this);\
    std::function<int()>getListSize8 = std::bind(&CLASS::__ReflectGetListSize##M8,this);\
    std::function<int()>getListSize9 = std::bind(&CLASS::__ReflectGetListSize##M9,this);\
    std::function<int()>getListSize10 = std::bind(&CLASS::__ReflectGetListSize##M10,this);\
    std::function<int()>getListSize11 = std::bind(&CLASS::__ReflectGetListSize##M11,this);\
    std::function<int()>getListSize12 = std::bind(&CLASS::__ReflectGetListSize##M12,this);\
    std::function<int()>getListSize13 = std::bind(&CLASS::__ReflectGetListSize##M13,this);\
    std::function<int()>getListSize14 = std::bind(&CLASS::__ReflectGetListSize##M14,this);\
    getFuncTuple = std::make_tuple(getobj1,getobj2,getobj3,getobj4,getobj5,\
                                   getobj6,getobj7,getobj8,getobj9,getobj10,\
                                   getobj11,getobj12,getobj13,getobj14,dummyobj,\
                                   dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj);\
    createFuncTuple = std::make_tuple(createobj1,createobj2,createobj3,createobj4,createobj5,\
                                   createobj6,createobj7,createobj8,createobj9,createobj10,\
                                   createobj11,createobj12,createobj13,createobj14,dummyobj,\
                                   dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj);\
    createListItemFuncTuple = std::make_tuple(genItemObj1,genItemObj2,genItemObj3,genItemObj4,genItemObj5,\
                                   genItemObj6,genItemObj7,genItemObj8,genItemObj9,genItemObj10,\
                                   genItemObj11,genItemObj12,genItemObj13,genItemObj14,dummycreateobj,\
                                   dummycreateobj,dummycreateobj,dummycreateobj,dummycreateobj,dummycreateobj,\
                                   dummycreateobj,dummycreateobj,dummycreateobj,dummycreateobj,dummycreateobj,\
                                   dummycreateobj,dummycreateobj,dummycreateobj,dummycreateobj,dummycreateobj,\
                                   dummycreateobj,dummycreateobj);\
    getListItemFuncTuple = std::make_tuple(getItemObj1,getItemObj2,getItemObj3,getItemObj4,getItemObj5,\
                                   getItemObj6,getItemObj7,getItemObj8,getItemObj9,getItemObj10,\
                                   getItemObj11,getItemObj12,getItemObj13,getItemObj14,dummyligobj,\
                                   dummyligobj,dummyligobj,dummyligobj,dummyligobj,dummyligobj,\
                                   dummyligobj,dummyligobj,dummyligobj,dummyligobj,dummyligobj,\
                                   dummyligobj,dummyligobj,dummyligobj,dummyligobj,dummyligobj,\
                                   dummyligobj,dummyligobj);\
    getListSizeFuncTuple = std::make_tuple(getListSize1,getListSize2,getListSize3,getListSize4,getListSize5,\
            getListSize6,getListSize7,getListSize8,getListSize9,getListSize10,\
            getListSize11,getListSize12,getListSize13,getListSize14,dummyobj,\
            dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
            dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
            dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
            dummyobj,dummyobj); 

#define IMPLE_INIT_TUPLE_15(CLASS,M1,M2,M3,M4,M5,M6,M7,M8,M9,M10,M11,M12,M13,M14,M15) \
    std::function<decltype(M1)()> getobj1 = std::bind(&CLASS::__ReflectGet##M1,this);\
    std::function<decltype(M2)()> getobj2 = std::bind(&CLASS::__ReflectGet##M2,this);\
    std::function<decltype(M3)()> getobj3 = std::bind(&CLASS::__ReflectGet##M3,this);\
    std::function<decltype(M4)()> getobj4 = std::bind(&CLASS::__ReflectGet##M4,this);\
    std::function<decltype(M5)()> getobj5 = std::bind(&CLASS::__ReflectGet##M5,this);\
    std::function<decltype(M6)()> getobj6 = std::bind(&CLASS::__ReflectGet##M6,this);\
    std::function<decltype(M7)()> getobj7 = std::bind(&CLASS::__ReflectGet##M7,this);\
    std::function<decltype(M8)()> getobj8 = std::bind(&CLASS::__ReflectGet##M8,this);\
    std::function<decltype(M9)()> getobj9 = std::bind(&CLASS::__ReflectGet##M9,this);\
    std::function<decltype(M10)()> getobj10 = std::bind(&CLASS::__ReflectGet##M10,this);\
    std::function<decltype(M11)()> getobj11 = std::bind(&CLASS::__ReflectGet##M11,this);\
    std::function<decltype(M12)()> getobj12 = std::bind(&CLASS::__ReflectGet##M12,this);\
    std::function<decltype(M13)()> getobj13 = std::bind(&CLASS::__ReflectGet##M13,this);\
    std::function<decltype(M14)()> getobj14 = std::bind(&CLASS::__ReflectGet##M14,this);\
    std::function<decltype(M15)()> getobj15 = std::bind(&CLASS::__ReflectGet##M15,this);\
    std::function<void()> createobj1 = std::bind(&CLASS::__ReflectCreate##M1,this);\
    std::function<void()> createobj2 = std::bind(&CLASS::__ReflectCreate##M2,this);\
    std::function<void()> createobj3 = std::bind(&CLASS::__ReflectCreate##M3,this);\
    std::function<void()> createobj4 = std::bind(&CLASS::__ReflectCreate##M4,this);\
    std::function<void()> createobj5 = std::bind(&CLASS::__ReflectCreate##M5,this);\
    std::function<void()> createobj6 = std::bind(&CLASS::__ReflectCreate##M6,this);\
    std::function<void()> createobj7 = std::bind(&CLASS::__ReflectCreate##M7,this);\
    std::function<void()> createobj8 = std::bind(&CLASS::__ReflectCreate##M8,this);\
    std::function<void()> createobj9 = std::bind(&CLASS::__ReflectCreate##M9,this);\
    std::function<void()> createobj10 = std::bind(&CLASS::__ReflectCreate##M10,this);\
    std::function<void()> createobj11 = std::bind(&CLASS::__ReflectCreate##M11,this);\
    std::function<void()> createobj12 = std::bind(&CLASS::__ReflectCreate##M12,this);\
    std::function<void()> createobj13 = std::bind(&CLASS::__ReflectCreate##M13,this);\
    std::function<void()> createobj14 = std::bind(&CLASS::__ReflectCreate##M14,this);\
    std::function<void()> createobj15 = std::bind(&CLASS::__ReflectCreate##M15,this);\
    std::function<sp<_Object>()>genItemObj1 = std::bind(&CLASS::__ReflectCreateListMember##M1,this);\
    std::function<sp<_Object>()>genItemObj2 = std::bind(&CLASS::__ReflectCreateListMember##M2,this);\
    std::function<sp<_Object>()>genItemObj3 = std::bind(&CLASS::__ReflectCreateListMember##M3,this);\
    std::function<sp<_Object>()>genItemObj4 = std::bind(&CLASS::__ReflectCreateListMember##M4,this);\
    std::function<sp<_Object>()>genItemObj5 = std::bind(&CLASS::__ReflectCreateListMember##M5,this);\
    std::function<sp<_Object>()>genItemObj6 = std::bind(&CLASS::__ReflectCreateListMember##M6,this);\
    std::function<sp<_Object>()>genItemObj7 = std::bind(&CLASS::__ReflectCreateListMember##M7,this);\
    std::function<sp<_Object>()>genItemObj8 = std::bind(&CLASS::__ReflectCreateListMember##M8,this);\
    std::function<sp<_Object>()>genItemObj9 = std::bind(&CLASS::__ReflectCreateListMember##M9,this);\
    std::function<sp<_Object>()>genItemObj10 = std::bind(&CLASS::__ReflectCreateListMember##M10,this);\
    std::function<sp<_Object>()>genItemObj11 = std::bind(&CLASS::__ReflectCreateListMember##M11,this);\
    std::function<sp<_Object>()>genItemObj12 = std::bind(&CLASS::__ReflectCreateListMember##M12,this);\
    std::function<sp<_Object>()>genItemObj13 = std::bind(&CLASS::__ReflectCreateListMember##M13,this);\
    std::function<sp<_Object>()>genItemObj14 = std::bind(&CLASS::__ReflectCreateListMember##M14,this);\
    std::function<sp<_Object>()>genItemObj15 = std::bind(&CLASS::__ReflectCreateListMember##M15,this);\
    std::function<sp<_Object>(int)>getItemObj1 = std::bind(&CLASS::__ReflectGetListItem##M1,this,std::placeholders::_1);\
    std::function<sp<_Object>(int)>getItemObj2 = std::bind(&CLASS::__ReflectGetListItem##M2,this,std::placeholders::_1);\
    std::function<sp<_Object>(int)>getItemObj3 = std::bind(&CLASS::__ReflectGetListItem##M3,this,std::placeholders::_1);\
    std::function<sp<_Object>(int)>getItemObj4 = std::bind(&CLASS::__ReflectGetListItem##M4,this,std::placeholders::_1);\
    std::function<sp<_Object>(int)>getItemObj5 = std::bind(&CLASS::__ReflectGetListItem##M5,this,std::placeholders::_1);\
    std::function<sp<_Object>(int)>getItemObj6 = std::bind(&CLASS::__ReflectGetListItem##M6,this,std::placeholders::_1);\
    std::function<sp<_Object>(int)>getItemObj7 = std::bind(&CLASS::__ReflectGetListItem##M7,this,std::placeholders::_1);\
    std::function<sp<_Object>(int)>getItemObj8 = std::bind(&CLASS::__ReflectGetListItem##M8,this,std::placeholders::_1);\
    std::function<sp<_Object>(int)>getItemObj9 = std::bind(&CLASS::__ReflectGetListItem##M9,this,std::placeholders::_1);\
    std::function<sp<_Object>(int)>getItemObj10 = std::bind(&CLASS::__ReflectGetListItem##M10,this,std::placeholders::_1);\
    std::function<sp<_Object>(int)>getItemObj11 = std::bind(&CLASS::__ReflectGetListItem##M11,this,std::placeholders::_1);\
    std::function<sp<_Object>(int)>getItemObj12 = std::bind(&CLASS::__ReflectGetListItem##M12,this,std::placeholders::_1);\
    std::function<sp<_Object>(int)>getItemObj13 = std::bind(&CLASS::__ReflectGetListItem##M13,this,std::placeholders::_1);\
    std::function<sp<_Object>(int)>getItemObj14 = std::bind(&CLASS::__ReflectGetListItem##M14,this,std::placeholders::_1);\
    std::function<sp<_Object>(int)>getItemObj15 = std::bind(&CLASS::__ReflectGetListItem##M15,this,std::placeholders::_1);\
    std::function<int()>getListSize1 = std::bind(&CLASS::__ReflectGetListSize##M1,this);\
    std::function<int()>getListSize2 = std::bind(&CLASS::__ReflectGetListSize##M2,this);\
    std::function<int()>getListSize3 = std::bind(&CLASS::__ReflectGetListSize##M3,this);\
    std::function<int()>getListSize4 = std::bind(&CLASS::__ReflectGetListSize##M4,this);\
    std::function<int()>getListSize5 = std::bind(&CLASS::__ReflectGetListSize##M5,this);\
    std::function<int()>getListSize6 = std::bind(&CLASS::__ReflectGetListSize##M6,this);\
    std::function<int()>getListSize7 = std::bind(&CLASS::__ReflectGetListSize##M7,this);\
    std::function<int()>getListSize8 = std::bind(&CLASS::__ReflectGetListSize##M8,this);\
    std::function<int()>getListSize9 = std::bind(&CLASS::__ReflectGetListSize##M9,this);\
    std::function<int()>getListSize10 = std::bind(&CLASS::__ReflectGetListSize##M10,this);\
    std::function<int()>getListSize11 = std::bind(&CLASS::__ReflectGetListSize##M11,this);\
    std::function<int()>getListSize12 = std::bind(&CLASS::__ReflectGetListSize##M12,this);\
    std::function<int()>getListSize13 = std::bind(&CLASS::__ReflectGetListSize##M13,this);\
    std::function<int()>getListSize14 = std::bind(&CLASS::__ReflectGetListSize##M14,this);\
    std::function<int()>getListSize15 = std::bind(&CLASS::__ReflectGetListSize##M15,this);\
    getFuncTuple = std::make_tuple(getobj1,getobj2,getobj3,getobj4,getobj5,\
                                   getobj6,getobj7,getobj8,getobj9,getobj10,\
                                   getobj11,getobj12,getobj13,getobj14,getobj15,\
                                   dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj);\
    createFuncTuple = std::make_tuple(createobj1,createobj2,createobj3,createobj4,createobj5,\
                                   createobj6,createobj7,createobj8,createobj9,createobj10,\
                                   createobj11,createobj12,createobj13,createobj14,createobj15,\
                                   dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj);\
    createListItemFuncTuple = std::make_tuple(genItemObj1,genItemObj2,genItemObj3,genItemObj4,genItemObj5,\
                                   genItemObj6,genItemObj7,genItemObj8,genItemObj9,genItemObj10,\
                                   genItemObj11,genItemObj12,genItemObj13,genItemObj14,genItemObj15,\
                                   dummycreateobj,dummycreateobj,dummycreateobj,dummycreateobj,dummycreateobj,\
                                   dummycreateobj,dummycreateobj,dummycreateobj,dummycreateobj,dummycreateobj,\
                                   dummycreateobj,dummycreateobj,dummycreateobj,dummycreateobj,dummycreateobj,\
                                   dummycreateobj,dummycreateobj);\
    getListItemFuncTuple = std::make_tuple(getItemObj1,getItemObj2,getItemObj3,getItemObj4,getItemObj5,\
                                   getItemObj6,getItemObj7,getItemObj8,getItemObj9,getItemObj10,\
                                   getItemObj11,getItemObj12,getItemObj13,getItemObj14,getItemObj15,\
                                   dummyligobj,dummyligobj,dummyligobj,dummyligobj,dummyligobj,\
                                   dummyligobj,dummyligobj,dummyligobj,dummyligobj,dummyligobj,\
                                   dummyligobj,dummyligobj,dummyligobj,dummyligobj,dummyligobj,\
                                   dummyligobj,dummyligobj);\
    getListSizeFuncTuple = std::make_tuple(getListSize1,getListSize2,getListSize3,getListSize4,getListSize5,\
        getListSize6,getListSize7,getListSize8,getListSize9,getListSize10,\
        getListSize11,getListSize12,getListSize13,getListSize14,getListSize15,\
        dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
        dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
        dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
        dummyobj,dummyobj); 

#define IMPLE_INIT_TUPLE_16(CLASS,M1,M2,M3,M4,M5,M6,M7,M8,M9,M10,M11,M12,M13,M14,M15,M16) \
    std::function<decltype(M1)()> getobj1 = std::bind(&CLASS::__ReflectGet##M1,this);\
    std::function<decltype(M2)()> getobj2 = std::bind(&CLASS::__ReflectGet##M2,this);\
    std::function<decltype(M3)()> getobj3 = std::bind(&CLASS::__ReflectGet##M3,this);\
    std::function<decltype(M4)()> getobj4 = std::bind(&CLASS::__ReflectGet##M4,this);\
    std::function<decltype(M5)()> getobj5 = std::bind(&CLASS::__ReflectGet##M5,this);\
    std::function<decltype(M6)()> getobj6 = std::bind(&CLASS::__ReflectGet##M6,this);\
    std::function<decltype(M7)()> getobj7 = std::bind(&CLASS::__ReflectGet##M7,this);\
    std::function<decltype(M8)()> getobj8 = std::bind(&CLASS::__ReflectGet##M8,this);\
    std::function<decltype(M9)()> getobj9 = std::bind(&CLASS::__ReflectGet##M9,this);\
    std::function<decltype(M10)()> getobj10 = std::bind(&CLASS::__ReflectGet##M10,this);\
    std::function<decltype(M11)()> getobj11 = std::bind(&CLASS::__ReflectGet##M11,this);\
    std::function<decltype(M12)()> getobj12 = std::bind(&CLASS::__ReflectGet##M12,this);\
    std::function<decltype(M13)()> getobj13 = std::bind(&CLASS::__ReflectGet##M13,this);\
    std::function<decltype(M14)()> getobj14 = std::bind(&CLASS::__ReflectGet##M14,this);\
    std::function<decltype(M15)()> getobj15 = std::bind(&CLASS::__ReflectGet##M15,this);\
    std::function<decltype(M16)()> getobj16 = std::bind(&CLASS::__ReflectGet##M16,this);\
    std::function<void()> createobj1 = std::bind(&CLASS::__ReflectCreate##M1,this);\
    std::function<void()> createobj2 = std::bind(&CLASS::__ReflectCreate##M2,this);\
    std::function<void()> createobj3 = std::bind(&CLASS::__ReflectCreate##M3,this);\
    std::function<void()> createobj4 = std::bind(&CLASS::__ReflectCreate##M4,this);\
    std::function<void()> createobj5 = std::bind(&CLASS::__ReflectCreate##M5,this);\
    std::function<void()> createobj6 = std::bind(&CLASS::__ReflectCreate##M6,this);\
    std::function<void()> createobj7 = std::bind(&CLASS::__ReflectCreate##M7,this);\
    std::function<void()> createobj8 = std::bind(&CLASS::__ReflectCreate##M8,this);\
    std::function<void()> createobj9 = std::bind(&CLASS::__ReflectCreate##M9,this);\
    std::function<void()> createobj10 = std::bind(&CLASS::__ReflectCreate##M10,this);\
    std::function<void()> createobj11 = std::bind(&CLASS::__ReflectCreate##M11,this);\
    std::function<void()> createobj12 = std::bind(&CLASS::__ReflectCreate##M12,this);\
    std::function<void()> createobj13 = std::bind(&CLASS::__ReflectCreate##M13,this);\
    std::function<void()> createobj14 = std::bind(&CLASS::__ReflectCreate##M14,this);\
    std::function<void()> createobj15 = std::bind(&CLASS::__ReflectCreate##M15,this);\
    std::function<void()> createobj16 = std::bind(&CLASS::__ReflectCreate##M16,this);\
    std::function<sp<_Object>()>genItemObj1 = std::bind(&CLASS::__ReflectCreateListMember##M1,this);\
    std::function<sp<_Object>()>genItemObj2 = std::bind(&CLASS::__ReflectCreateListMember##M2,this);\
    std::function<sp<_Object>()>genItemObj3 = std::bind(&CLASS::__ReflectCreateListMember##M3,this);\
    std::function<sp<_Object>()>genItemObj4 = std::bind(&CLASS::__ReflectCreateListMember##M4,this);\
    std::function<sp<_Object>()>genItemObj5 = std::bind(&CLASS::__ReflectCreateListMember##M5,this);\
    std::function<sp<_Object>()>genItemObj6 = std::bind(&CLASS::__ReflectCreateListMember##M6,this);\
    std::function<sp<_Object>()>genItemObj7 = std::bind(&CLASS::__ReflectCreateListMember##M7,this);\
    std::function<sp<_Object>()>genItemObj8 = std::bind(&CLASS::__ReflectCreateListMember##M8,this);\
    std::function<sp<_Object>()>genItemObj9 = std::bind(&CLASS::__ReflectCreateListMember##M9,this);\
    std::function<sp<_Object>()>genItemObj10 = std::bind(&CLASS::__ReflectCreateListMember##M10,this);\
    std::function<sp<_Object>()>genItemObj11 = std::bind(&CLASS::__ReflectCreateListMember##M11,this);\
    std::function<sp<_Object>()>genItemObj12 = std::bind(&CLASS::__ReflectCreateListMember##M12,this);\
    std::function<sp<_Object>()>genItemObj13 = std::bind(&CLASS::__ReflectCreateListMember##M13,this);\
    std::function<sp<_Object>()>genItemObj14 = std::bind(&CLASS::__ReflectCreateListMember##M14,this);\
    std::function<sp<_Object>()>genItemObj15 = std::bind(&CLASS::__ReflectCreateListMember##M15,this);\
    std::function<sp<_Object>()>genItemObj16 = std::bind(&CLASS::__ReflectCreateListMember##M16,this);\
    std::function<sp<_Object>(int)>getItemObj1 = std::bind(&CLASS::__ReflectGetListItem##M1,this,std::placeholders::_1);\
    std::function<sp<_Object>(int)>getItemObj2 = std::bind(&CLASS::__ReflectGetListItem##M2,this,std::placeholders::_1);\
    std::function<sp<_Object>(int)>getItemObj3 = std::bind(&CLASS::__ReflectGetListItem##M3,this,std::placeholders::_1);\
    std::function<sp<_Object>(int)>getItemObj4 = std::bind(&CLASS::__ReflectGetListItem##M4,this,std::placeholders::_1);\
    std::function<sp<_Object>(int)>getItemObj5 = std::bind(&CLASS::__ReflectGetListItem##M5,this,std::placeholders::_1);\
    std::function<sp<_Object>(int)>getItemObj6 = std::bind(&CLASS::__ReflectGetListItem##M6,this,std::placeholders::_1);\
    std::function<sp<_Object>(int)>getItemObj7 = std::bind(&CLASS::__ReflectGetListItem##M7,this,std::placeholders::_1);\
    std::function<sp<_Object>(int)>getItemObj8 = std::bind(&CLASS::__ReflectGetListItem##M8,this,std::placeholders::_1);\
    std::function<sp<_Object>(int)>getItemObj9 = std::bind(&CLASS::__ReflectGetListItem##M9,this,std::placeholders::_1);\
    std::function<sp<_Object>(int)>getItemObj10 = std::bind(&CLASS::__ReflectGetListItem##M10,this,std::placeholders::_1);\
    std::function<sp<_Object>(int)>getItemObj11 = std::bind(&CLASS::__ReflectGetListItem##M11,this,std::placeholders::_1);\
    std::function<sp<_Object>(int)>getItemObj12 = std::bind(&CLASS::__ReflectGetListItem##M12,this,std::placeholders::_1);\
    std::function<sp<_Object>(int)>getItemObj13 = std::bind(&CLASS::__ReflectGetListItem##M13,this,std::placeholders::_1);\
    std::function<sp<_Object>(int)>getItemObj14 = std::bind(&CLASS::__ReflectGetListItem##M14,this,std::placeholders::_1);\
    std::function<sp<_Object>(int)>getItemObj15 = std::bind(&CLASS::__ReflectGetListItem##M15,this,std::placeholders::_1);\
    std::function<sp<_Object>(int)>getItemObj16 = std::bind(&CLASS::__ReflectGetListItem##M16,this,std::placeholders::_1);\
    std::function<int()>getListSize2 = std::bind(&CLASS::__ReflectGetListSize##M2,this);\
    std::function<int()>getListSize3 = std::bind(&CLASS::__ReflectGetListSize##M3,this);\
    std::function<int()>getListSize4 = std::bind(&CLASS::__ReflectGetListSize##M4,this);\
    std::function<int()>getListSize5 = std::bind(&CLASS::__ReflectGetListSize##M5,this);\
    std::function<int()>getListSize6 = std::bind(&CLASS::__ReflectGetListSize##M6,this);\
    std::function<int()>getListSize7 = std::bind(&CLASS::__ReflectGetListSize##M7,this);\
    std::function<int()>getListSize8 = std::bind(&CLASS::__ReflectGetListSize##M8,this);\
    std::function<int()>getListSize9 = std::bind(&CLASS::__ReflectGetListSize##M9,this);\
    std::function<int()>getListSize10 = std::bind(&CLASS::__ReflectGetListSize##M10,this);\
    std::function<int()>getListSize11 = std::bind(&CLASS::__ReflectGetListSize##M11,this);\
    std::function<int()>getListSize12 = std::bind(&CLASS::__ReflectGetListSize##M12,this);\
    std::function<int()>getListSize13 = std::bind(&CLASS::__ReflectGetListSize##M13,this);\
    std::function<int()>getListSize14 = std::bind(&CLASS::__ReflectGetListSize##M14,this);\
    std::function<int()>getListSize15 = std::bind(&CLASS::__ReflectGetListSize##M15,this);\
    std::function<int()>getListSize16 = std::bind(&CLASS::__ReflectGetListSize##M16,this);\
    getFuncTuple = std::make_tuple(getobj1,getobj2,getobj3,getobj4,getobj5,\
                                   getobj6,getobj7,getobj8,getobj9,getobj10,\
                                   getobj11,getobj12,getobj13,getobj14,getobj15,\
                                   getobj16,dummyobj,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj);\
    createFuncTuple = std::make_tuple(createobj1,createobj2,createobj3,createobj4,createobj5,\
                                   createobj6,createobj7,createobj8,createobj9,createobj10,\
                                   createobj11,createobj12,createobj13,createobj14,createobj15,\
                                   createobj16,dummyobj,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj);\
    createListItemFuncTuple = std::make_tuple(genItemObj1,genItemObj2,genItemObj3,genItemObj4,genItemObj5,\
                                   genItemObj6,genItemObj7,genItemObj8,genItemObj9,genItemObj10,\
                                   genItemObj11,genItemObj12,genItemObj13,genItemObj14,genItemObj15,\
                                   genItemObj16,dummycreateobj,dummycreateobj,dummycreateobj,dummycreateobj,\
                                   dummycreateobj,dummycreateobj,dummycreateobj,dummycreateobj,dummycreateobj,\
                                   dummycreateobj,dummycreateobj,dummycreateobj,dummycreateobj,dummycreateobj,\
                                   dummycreateobj,dummycreateobj);\
    getListItemFuncTuple = std::make_tuple(getItemObj1,getItemObj2,getItemObj3,getItemObj4,getItemObj5,\
                                   getItemObj6,getItemObj7,getItemObj8,getItemObj9,getItemObj10,\
                                   getItemObj11,getItemObj12,getItemObj13,getItemObj14,getItemObj15,\
                                   getItemObj16,dummyligobj,dummyligobj,dummyligobj,dummyligobj,\
                                   dummyligobj,dummyligobj,dummyligobj,dummyligobj,dummyligobj,\
                                   dummyligobj,dummyligobj,dummyligobj,dummyligobj,dummyligobj,\
                                   dummyligobj,dummyligobj);\
    getListSizeFuncTuple = std::make_tuple(getListSize1,getListSize2,getListSize3,getListSize4,getListSize5,\
        getListSize6,getListSize7,getListSize8,getListSize9,getListSize10,\
        getListSize11,getListSize12,getListSize13,getListSize14,getListSize15,\
        getListSize16,dummyobj,dummyobj,dummyobj,dummyobj,\
        dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
        dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
        dummyobj,dummyobj); 

#define DECLARE_REFLECT_FIELD(CLASS, ...) \
private:\
    HashMap<String,Field> maps; \
    IMPLE_SET_FUNCTION_DETECT(_##CLASS,GET_ARG_COUNT(__VA_ARGS__),__VA_ARGS__) \
    DECLARE_INIT_TUPLE_DETECT(_##CLASS,GET_ARG_COUNT(__VA_ARGS__),__VA_ARGS__) \
    int __ReflectDummy() {return 0;}\
    sp<_Object>__ReflectCreateDummy() {return nullptr;}\
    sp<_Object>__ReflectListItemGetDummy(int){return nullptr;}\
public:\
    sp<_String> __ReflectClassName(){\
        return createString(#CLASS);\
    }\
    void __ReflectInit() {\
        int index = 0;\
        std::function<int(void)> dummyobj = std::bind(&_##CLASS::__ReflectDummy,this);\
        std::function<sp<_Object>(void)> dummycreateobj = std::bind(&_##CLASS::__ReflectCreateDummy,this);\
        std::function<sp<_Object>(int)> dummyligobj = std::bind(&_##CLASS::__ReflectListItemGetDummy,this,std::placeholders::_1);\
        maps = createHashMap<String,Field>();\
        IMPLE_INIT_FUNCTION_DETECT(_##CLASS,GET_ARG_COUNT(__VA_ARGS__),__VA_ARGS__)\
        IMPLE_INIT_TUPLE_DETECT(_##CLASS,GET_ARG_COUNT(__VA_ARGS__),__VA_ARGS__)\
    }\
    Field getField(String name) {\
        return maps->get(name);\
    }\
    ArrayList<Field> getAllFields(){ \
        return maps->entrySet();\
    }\
private:\
    template<typename Q>\
    Q* genArrayListDataPoint(sp<Q> t) {\
        Q *data = new Q();\
        data->__ReflectInit();\
        return data;\
    }\
    template<typename Q>\
    sp<_Object> genArrayListData(ArrayList<Q> list) {\
        Q param;\
        auto pointer = genArrayListDataPoint(param);\
        param.set_pointer(pointer);\
        list->add(param);\
        return param;\
    }\
    template<typename Q>\
    sp<_Object>genArrayListData(Q t) {\
        return nullptr;\
    }\
    template<typename Q>\
    sp<_Object> getArrayListItem(ArrayList<Q> list,int index){\
        if(list == nullptr ||index == list->size()) {\
            return nullptr;\
        }\
        return list->get(index);\
    }\
    template<typename Q>\
    sp<_Object> getArrayListItem(Q t,int index) {\
        return nullptr;\
    }\
    template<typename Q>\
    int __getListSize(ArrayList<Q> list){\
        if(list == nullptr) {\
            return 0;\
        }\
        return list->size();\
    }\
    template<typename Q>\
    int __getListSize(Q t) {\
        return -1;\
    }\
    int __getFieldIntValue(std::string name){ \
       FieldContentValue v = __getFieldContentValue(name);\
       return v->intValue;\
    }\
    long __getFieldLongValue(std::string name){ \
       FieldContentValue v = __getFieldContentValue(name);\
       return v->longValue;\
    }\
    uint8_t __getFieldByteValue(std::string name){ \
        FieldContentValue v = __getFieldContentValue(name);\
        return v->uint8Value;\
    }\
    bool __getFieldBoolValue(std::string name){ \
        FieldContentValue v = __getFieldContentValue(name);\
        return v->boolValue;\
    }\
    double __getFieldDoubleValue(std::string name){ \
        FieldContentValue v = __getFieldContentValue(name);\
        return v->doubleValue;\
    }\
    float __getFieldFloatValue(std::string name){ \
        FieldContentValue v = __getFieldContentValue(name);\
        return v->floatValue;\
    }\
    uint8_t __getFieldUint8Value(std::string name){ \
        FieldContentValue v = __getFieldContentValue(name);\
        return v->uint8Value;\
    }\
    uint16_t __getFieldUint16Value(std::string name){ \
        FieldContentValue v = __getFieldContentValue(name);\
        return v->uint16Value;\
    }\
    uint32_t __getFieldUint32Value(std::string name){ \
        FieldContentValue v = __getFieldContentValue(name);\
        return v->uint32Value;\
    }\
    uint64_t __getFieldUint64Value(std::string name){ \
        FieldContentValue v = __getFieldContentValue(name);\
        return v->uint64Value;\
    }\
    sp<_Object> __getFieldObjectValue(std::string name){ \
        FieldContentValue v = __getFieldContentValue(name);\
        return v->objectValue;\
    }\
    String __getFieldStringValue(std::string name) {\
        FieldContentValue v = __getFieldContentValue(name);\
        return v->stringValue;\
    }\
    void __setFieldIntValue(std::string name,int value){__setFieldValue(name,value);}\
    void __setFieldByteValue(std::string name,uint8_t value){__setFieldValue(name,value);}\
    void __setFieldDoubleValue(std::string name,double value){__setFieldValue(name,value);}\
    void __setFieldFloatValue(std::string name,float value){__setFieldValue(name,value);}\
    void __setFieldLongValue(std::string name,long value){__setFieldValue(name,value);}\
    void __setFieldUint8Value(std::string name,uint8_t value){__setFieldValue(name,value);}\
    void __setFieldBoolValue(std::string name,bool value){__setFieldValue(name,value);}\
    void __setFieldUint16Value(std::string name ,uint16_t value){__setFieldValue(name,value);}\
    void __setFieldUint32Value(std::string name ,uint32_t value){__setFieldValue(name,value);}\
    void __setFieldUint64Value(std::string name,uint64_t value){__setFieldValue(name,value);}\
    void __setFieldStringValue(std::string name,std::string value){__setFieldValue(name,createString(value));}\
    void __setFieldObjectValue(std::string name,sp<_Object> value){__setFieldValue(name,value);}\
    template<typename Q>\
    void __setFieldValue(std::string name,Q value){\
        Field f = maps->get(createString(name));\
        _FieldContent<Q>  *content = dynamic_cast<_FieldContent<Q>  *>(f.get_pointer());\
        content->setfunc(value);\
    }\
    FieldContentValue __getFieldContentValue(std::string name){\
        Field f = maps->get(createString(name));\
        FieldContentValue val = createFieldContentValue();\
        switch(f->getId()) {\
            case 0:\
            val->set(std::get<0>(getFuncTuple)());\
            break;\
            case 1:\
            val->set(std::get<1>(getFuncTuple)());\
            break;\
            case 2:\
            val->set(std::get<2>(getFuncTuple)());\
            break;\
            case 3:\
            val->set(std::get<3>(getFuncTuple)());\
            break;\
            case 4:\
            val->set(std::get<4>(getFuncTuple)());\
            break;\
            case 5:\
            val->set(std::get<5>(getFuncTuple)());\
            break;\
            case 6:\
            val->set(std::get<6>(getFuncTuple)());\
            break;\
            case 7:\
            val->set(std::get<7>(getFuncTuple)());\
            break;\
            case 8:\
            val->set(std::get<8>(getFuncTuple)());\
            break;\
            case 9:\
            val->set(std::get<9>(getFuncTuple)());\
            break;\
            case 10:\
            val->set(std::get<10>(getFuncTuple)());\
            break;\
            case 11:\
            val->set(std::get<11>(getFuncTuple)());\
            break;\
            case 12:\
            val->set(std::get<12>(getFuncTuple)());\
            break;\
            case 13:\
            val->set(std::get<13>(getFuncTuple)());\
            break;\
            case 14:\
            val->set(std::get<14>(getFuncTuple)());\
            break;\
            case 15:\
            val->set(std::get<15>(getFuncTuple)());\
            break;\
        }\
        return val;\
    }\
    void __createFieldObject(std::string name) {\
        Field f = maps->get(createString(name));\
        switch(f->getId()) {\
            case 0:\
                std::get<0>(createFuncTuple)();\
            break;\
            case 1:\
                std::get<1>(createFuncTuple)();\
            break;\
            case 2:\
                std::get<2>(createFuncTuple)();\
            break;\
            case 3:\
                std::get<3>(createFuncTuple)();\
            break;\
            case 4:\
                std::get<4>(createFuncTuple)();\
            break;\
            case 5:\
                std::get<5>(createFuncTuple)();\
            break;\
            case 6:\
                std::get<6>(createFuncTuple)();\
            break;\
            case 7:\
                std::get<7>(createFuncTuple)();\
            break;\
            case 8:\
                std::get<8>(createFuncTuple)();\
            break;\
            case 9:\
                std::get<9>(createFuncTuple)();\
            break;\
            case 10:\
                std::get<10>(createFuncTuple)();\
            break;\
            case 11:\
                std::get<11>(createFuncTuple)();\
            break;\
            case 12:\
                std::get<12>(createFuncTuple)();\
            break;\
            case 13:\
                std::get<13>(createFuncTuple)();\
            break;\
            case 14:\
                std::get<14>(createFuncTuple)();\
            break;\
            case 15:\
                std::get<15>(createFuncTuple)();\
            break;\
        }\
    }\
    sp<_Object> __createListItemObject(std::string name) {\
        Field f = maps->get(createString(name));\
        switch(f->getId()) {\
            case 0:\
                return std::get<0>(createListItemFuncTuple)();\
            break;\
            case 1:\
                return std::get<1>(createListItemFuncTuple)();\
            break;\
            case 2:\
                return std::get<2>(createListItemFuncTuple)();\
            break;\
            case 3:\
                return std::get<3>(createListItemFuncTuple)();\
            break;\
            case 4:\
                return std::get<4>(createListItemFuncTuple)();\
            break;\
            case 5:\
                return std::get<5>(createListItemFuncTuple)();\
            break;\
            case 6:\
                return std::get<6>(createListItemFuncTuple)();\
            break;\
            case 7:\
                return std::get<7>(createListItemFuncTuple)();\
            break;\
            case 8:\
                return std::get<8>(createListItemFuncTuple)();\
            break;\
            case 9:\
                return std::get<9>(createListItemFuncTuple)();\
            break;\
            case 10:\
                return std::get<10>(createListItemFuncTuple)();\
            break;\
            case 11:\
                return std::get<11>(createListItemFuncTuple)();\
            break;\
            case 12:\
                return std::get<12>(createListItemFuncTuple)();\
            break;\
            case 13:\
                return std::get<13>(createListItemFuncTuple)();\
            break;\
            case 14:\
                return std::get<14>(createListItemFuncTuple)();\
            break;\
            case 15:\
                return std::get<15>(createListItemFuncTuple)();\
            break;\
        }\
    }\
    sp<_Object> __getListItemObject(std::string name,int index){\
        Field f = maps->get(createString(name));\
        switch(f->getId()) {\
            case 0:\
                return std::get<0>(getListItemFuncTuple)(index);\
            break;\
            case 1:\
                return std::get<1>(getListItemFuncTuple)(index);\
            break;\
            case 2:\
                return std::get<2>(getListItemFuncTuple)(index);\
            break;\
            case 3:\
                return std::get<3>(getListItemFuncTuple)(index);\
            break;\
            case 4:\
                return std::get<4>(getListItemFuncTuple)(index);\
            break;\
            case 5:\
                return std::get<5>(getListItemFuncTuple)(index);\
            break;\
            case 6:\
                return std::get<6>(getListItemFuncTuple)(index);\
            break;\
            case 7:\
                return std::get<7>(getListItemFuncTuple)(index);\
            break;\
            case 8:\
                return std::get<8>(getListItemFuncTuple)(index);\
            break;\
            case 9:\
                return std::get<9>(getListItemFuncTuple)(index);\
            break;\
            case 10:\
                return std::get<10>(getListItemFuncTuple)(index);\
            break;\
            case 11:\
                return std::get<11>(getListItemFuncTuple)(index);\
            break;\
            case 12:\
                return std::get<12>(getListItemFuncTuple)(index);\
            break;\
            case 13:\
                return std::get<13>(getListItemFuncTuple)(index);\
            break;\
            case 14:\
                return std::get<14>(getListItemFuncTuple)(index);\
            break;\
            case 15:\
                return std::get<15>(getListItemFuncTuple)(index);\
            break;\
        }\
    };\
    int __getListObjectSize(std::string name) {\
        Field f = maps->get(createString(name));\
        switch(f->getId()) {\
            case 0:\
                return std::get<0>(getListSizeFuncTuple)();\
            break;\
            case 1:\
                return std::get<1>(getListSizeFuncTuple)();\
            break;\
            case 2:\
                return std::get<2>(getListSizeFuncTuple)();\
            break;\
            case 3:\
                return std::get<3>(getListSizeFuncTuple)();\
            break;\
            case 4:\
                return std::get<4>(getListSizeFuncTuple)();\
            break;\
            case 5:\
                return std::get<5>(getListSizeFuncTuple)();\
            break;\
            case 6:\
                return std::get<6>(getListSizeFuncTuple)();\
            break;\
            case 7:\
                return std::get<7>(getListSizeFuncTuple)();\
            break;\
            case 8:\
                return std::get<8>(getListSizeFuncTuple)();\
            break;\
            case 9:\
                return std::get<9>(getListSizeFuncTuple)();\
            break;\
            case 10:\
                return std::get<10>(getListSizeFuncTuple)();\
            break;\
            case 11:\
                return std::get<11>(getListSizeFuncTuple)();\
            break;\
            case 12:\
                return std::get<12>(getListSizeFuncTuple)();\
            break;\
            case 13:\
                return std::get<13>(getListSizeFuncTuple)();\
            break;\
            case 14:\
                return std::get<14>(getListSizeFuncTuple)();\
            break;\
            case 15:\
                return std::get<15>(getListSizeFuncTuple)();\
            break;\
        }\
    }\
    
#endif
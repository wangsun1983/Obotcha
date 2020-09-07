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
        createReflectObject(MEMBER);\
    }\
    sp<Object> __ReflectCreateListMember##MEMBER() {\
        return genArrayListData<decltype(MEMBER)>(MEMBER);\
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
#define __D() std::function<int()>

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
                __D(),__D()> createFuncTuple;

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
                __D(),__D()> createFuncTuple; 

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
                __D(),__D()> createFuncTuple; 

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
                __D(),__D()> createFuncTuple; 

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
                __D(),__D()> createFuncTuple;

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
                __D(),__D()> createFuncTuple;

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
                __D(),__D()> createFuncTuple;


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
                __D(),__D()> createFuncTuple;

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
                __D(),__D()> createFuncTuple;

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
                __D(),__D()> createFuncTuple;

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
                __D(),__D()> createFuncTuple;


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
                __D(),__D()> createFuncTuple;

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
                __D(),__D()> createFuncTuple;

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
                __D(),__D()> createFuncTuple;

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
                __D(),__D()> createFuncTuple;


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
                __D(),__D()> createFuncTuple;


#define IMPLE_INIT_TUPLE_DETECT(CLASS,COUNT, ...) IMPLE_INIT_TUPLE_DETECT_TRACE(CLASS,COUNT, __VA_ARGS__)
#define IMPLE_INIT_TUPLE_DETECT_TRACE(CLASS,COUNT, ...) IMPLE_INIT_TUPLE_DETECT_TRACE1(CLASS,COUNT, __VA_ARGS__)
#define IMPLE_INIT_TUPLE_DETECT_TRACE1(CLASS,COUNT, ...) IMPLE_INIT_TUPLE_##COUNT(CLASS,__VA_ARGS__)

#define IMPLE_INIT_TUPLE_1(CLASS,M1) \
    std::function<decltype(M1)()> getobj = std::bind(&CLASS::__ReflectGet##M1,this);\
    std::function<void()> createobj = std::bind(&CLASS::__ReflectCreate##M1,this);\
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

#define IMPLE_INIT_TUPLE_2(CLASS,M1,M2) \
    std::function<decltype(M1)()> getobj1 = std::bind(&CLASS::__ReflectGet##M1,this);\
    std::function<decltype(M2)()> getobj2 = std::bind(&CLASS::__ReflectGet##M2,this);\
    std::function<void()> createobj1 = std::bind(&CLASS::__ReflectCreate##M1,this);\
    std::function<void()> createobj2 = std::bind(&CLASS::__ReflectCreate##M2,this);\
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

#define IMPLE_INIT_TUPLE_3(CLASS,M1,M2,M3) \
    std::function<decltype(M1)()> getobj1 = std::bind(&CLASS::__ReflectGet##M1,this);\
    std::function<decltype(M2)()> getobj2 = std::bind(&CLASS::__ReflectGet##M2,this);\
    std::function<decltype(M3)()> getobj3 = std::bind(&CLASS::__ReflectGet##M3,this);\
    std::function<void()> createobj1 = std::bind(&CLASS::__ReflectCreate##M1,this);\
    std::function<void()> createobj2 = std::bind(&CLASS::__ReflectCreate##M2,this);\
    std::function<void()> createobj3 = std::bind(&CLASS::__ReflectCreate##M3,this);\
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

#define IMPLE_INIT_TUPLE_4(CLASS,M1,M2,M3,M4) \
    std::function<decltype(M1)()> getobj1 = std::bind(&CLASS::__ReflectGet##M1,this);\
    std::function<decltype(M2)()> getobj2 = std::bind(&CLASS::__ReflectGet##M2,this);\
    std::function<decltype(M3)()> getobj3 = std::bind(&CLASS::__ReflectGet##M3,this);\
    std::function<decltype(M4)()> getobj4 = std::bind(&CLASS::__ReflectGet##M4,this);\
    std::function<void()> createobj1 = std::bind(&CLASS::__ReflectCreate##M1,this);\
    std::function<void()> createobj2 = std::bind(&CLASS::__ReflectCreate##M2,this);\
    std::function<void()> createobj3 = std::bind(&CLASS::__ReflectCreate##M3,this);\
    std::function<void()> createobj4 = std::bind(&CLASS::__ReflectCreate##M4,this);\
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
    getFuncTuple = std::make_tuple(getobj1,getobj2,getobj3,getobj4,getobj5,\
                                   getobj6,getobj7,getobj8,getobj9,getobj10,\
                                   getobj11,getobj12,getobj13,getobj14,getobj15,\
                                   dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj);\

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
    getFuncTuple = std::make_tuple(getobj1,getobj2,getobj3,getobj4,getobj5,\
                                   getobj6,getobj7,getobj8,getobj9,getobj10,\
                                   getobj11,getobj12,getobj13,getobj14,getobj15,\
                                   getobj16,dummyobj,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj,dummyobj,dummyobj,dummyobj,\
                                   dummyobj,dummyobj);\


#define DECLARE_REFLECT_FIELD(CLASS, ...) \
private:\
    HashMap<String,Field> maps; \
    void createReflectObject(int) {}\
    void createReflectObject(byte) {}\
    void createReflectObject(double) {}\
    void createReflectObject(float) {}\
    void createReflectObject(uint16_t) {}\
    void createReflectObject(uint32_t) {}\
    void createReflectObject(uint64_t) {}\
    template<typename V>\
    void createReflectObject(sp<V> &v) {\
        V *p = new V();\
        p->__ReflectInit();\
        v.set_pointer(p);\
    }\
    IMPLE_SET_FUNCTION_DETECT(_##CLASS,GET_ARG_COUNT(__VA_ARGS__),__VA_ARGS__) \
    DECLARE_INIT_TUPLE_DETECT(_##CLASS,GET_ARG_COUNT(__VA_ARGS__),__VA_ARGS__) \
    int __ReflectDummy() {return 0;}\
public:\
    void __ReflectInit() {\
        int index = 0;\
        std::function<int(void)> dummyobj = std::bind(&_##CLASS::__ReflectDummy,this);\
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
    template<typename T>\
    sp<Object> genArrayListData(ArrayList<T> t) {\
        sp<Object> result;\
        T *data = new T();\
        data->__ReflectInit();\
        result.set_pointer(data);\
        return result;\
    }\
    template<typename T>\
    sp<Object> genArrayListData(T t) {\
        return nullptr;\
    }\
    int getFieldIntValue(std::string name){ \
       FieldContentValue v = getFieldContentValue(name);\
       return v->intValue;\
    }\
    unsigned char getFieldByteValue(std::string name){ \
        FieldContentValue v = getFieldContentValue(name);\
        return v->byteValue;\
    }\
    bool getFieldBoolValue(std::string name){ \
        FieldContentValue v = getFieldContentValue(name);\
        return v->boolValue;\
    }\
    double getFieldDoubleValue(std::string name){ \
        FieldContentValue v = getFieldContentValue(name);\
        return v->doubleValue;\
    }\
    float getFieldFloatValue(std::string name){ \
        FieldContentValue v = getFieldContentValue(name);\
        return v->floatValue;\
    }\
    uint8_t getFieldUint8Value(std::string name){ \
        FieldContentValue v = getFieldContentValue(name);\
        return v->uint8Value;\
    }\
    uint16_t getFieldUint16Value(std::string name){ \
        FieldContentValue v = getFieldContentValue(name);\
        return v->uint16Value;\
    }\
    uint32_t getFieldUint32Value(std::string name){ \
        FieldContentValue v = getFieldContentValue(name);\
        return v->uint32Value;\
    }\
    uint64_t getFieldUint64Value(std::string name){ \
        FieldContentValue v = getFieldContentValue(name);\
        return v->uint64Value;\
    }\
    sp<Object> getFieldObjectValue(std::string name){ \
        FieldContentValue v = getFieldContentValue(name);\
        return v->objectValue;\
    }\
    String getFieldStringValue(std::string name) {\
        FieldContentValue v = getFieldContentValue(name);\
        return v->stringValue;\
    }\
    void setFieldIntValue(std::string name,int value){setFieldValue(name,value);}\
    void setFieldByteValue(std::string name,unsigned char value){setFieldValue(name,value);}\
    void setFieldDoubleValue(std::string name,double value){setFieldValue(name,value);}\
    void setFieldFloatValue(std::string name,float value){setFieldValue(name,value);}\
    void setFieldUint8Value(std::string name,uint8_t value){setFieldValue(name,value);}\
    void setFieldUint16Value(std::string name ,uint16_t value){setFieldValue(name,value);}\
    void setFieldUint32Value(std::string name ,uint32_t value){setFieldValue(name,value);}\
    void setFieldUint64Value(std::string name,uint64_t value){setFieldValue(name,value);}\
    void setFieldStringValue(std::string name,std::string value){setFieldValue(name,createString(value));}\
    void setFieldObjectValue(std::string name,sp<Object> value){}\
    template<typename T>\
    void setFieldValue(std::string name,T value){\
        Field f = maps->get(createString(name));\
        _FieldContent<T>  *content = dynamic_cast<_FieldContent<T>  *>(f.get_pointer());\
        if(content == nullptr) {\
            printf("setFieldValue null,name is %s \n",name.c_str());\
        }\
        content->setfunc(value);\
    }\
    FieldContentValue getFieldContentValue(std::string name){\
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
    void createFieldObject(std::string name) {\
        Field f = maps->get(createString(name));\
        printf("createFieldObject id is %d \n",f->getId());\
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

#endif
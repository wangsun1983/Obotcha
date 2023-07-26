#ifndef __OBOTCHA_REFLECT_HPP__
#define __OBOTCHA_REFLECT_HPP__

#include <functional>
#include <iostream>
#include <map>
#include <sstream>

#include "ArrayList.hpp"
#include "Field.hpp"
#include "HashMap.hpp"
#include "Pair.hpp"
#include "ReflectUtil.hpp"
#include "StrongPointer.hpp"

#define DO_IMPLE_SET_VALUE(CLASS, ...)                                         \
    IMPLE_SET_VALUE_INTERFACE(CLASS, GET_ARG_COUNT(__VA_ARGS__), __VA_ARGS__)

#define IMPLE_SET_VALUE_INTERFACE_1(CLASS, COUNT, ...)                         \
    IMPLE_SET_VALUE_1_INTERFACE_INTER(CLASS, COUNT, __VA_ARGS__)
#define IMPLE_SET_VALUE_1_INTERFACE_INTER(CLASS, COUNT, ...)

#define IMPLE_SET_VALUE_INTERFACE_2(CLASS, COUNT, MEMBER, ...)                 \
    IMPLE_SET_VALUE_2_INTERFACE_INTER(CLASS, COUNT, MEMBER, __VA_ARGS__)
#define IMPLE_SET_VALUE_2_INTERFACE_INTER(CLASS, COUNT, MEMBER, ...)           \
    IMPLE_SET_VALUE_2_INTERFACE_INTER2(CLASS, COUNT, MEMBER, __VA_ARGS__)
#define IMPLE_SET_VALUE_2_INTERFACE_INTER2(CLASS, COUNT, MEMBER, ...)          \
    IMPLE_SET_VALUE(CLASS, COUNT, MEMBER, __VA_ARGS__)

#define IMPLE_SET_VALUE_INTERFACE(CLASS, COUNT, MEMBER, ...)                   \
    IMPLE_SET_VALUE_INTERFACE_INTER(CLASS, COUNT, MEMBER, __VA_ARGS__)
#define IMPLE_SET_VALUE_INTERFACE_INTER(CLASS, COUNT, MEMBER, ...)             \
    IMPLE_SET_VALUE_INTERFACE_INTER2(CLASS, COUNT, MEMBER, __VA_ARGS__)
#define IMPLE_SET_VALUE_INTERFACE_INTER2(CLASS, COUNT, MEMBER, ...)            \
    IMPLE_SET_VALUE(CLASS, COUNT, MEMBER, __VA_ARGS__)

// function
#define IMPLE_SET_VALUE_1(CLASS, MEMBER)                                       \
    void __ReflectSet##MEMBER(decltype(MEMBER) v) { MEMBER = v; }              \
    decltype(MEMBER) __ReflectGet##MEMBER() { return MEMBER; }                 \
    void __ReflectCreate##MEMBER() { st(ReflectUtil)::createObject(MEMBER); }  \
    Object __ReflectCreateListMember##MEMBER() {                               \
        return genArrayListData(MEMBER);                                       \
    }                                                                          \
    Object __ReflectGetListItem##MEMBER(int index) {                           \
        return getArrayListItem(MEMBER, index);                                \
    }                                                                          \
    void __ReflectAddListItem##MEMBER(Object v) {                              \
        return addArrayListData(MEMBER, v);                                    \
    }                                                                          \
    Pair<Object, Object> __ReflectCreateMapMember##MEMBER() {          \
        return genHashMapData(MEMBER);                                         \
    }                                                                          \
    ArrayList<Pair<Object, Object>> __ReflectGetMapItems##MEMBER() {   \
        return getHashMapItems(MEMBER);                                        \
    }                                                                          \
    void __ReflectAddMapItem##MEMBER(Object k, Object v) {                     \
        return addHashMapItem(MEMBER, k, v);                                   \
    }                                                                          \
    int __ReflectGetContainerSize##MEMBER() {                                  \
        return __getContainerSize(MEMBER);                                     \
    }

#define IMPLE_SET_VALUE_2(CLASS, M1, M2)                                       \
    IMPLE_SET_VALUE_1(CLASS, M1)                                               \
    IMPLE_SET_VALUE_1(CLASS, M2)

#define IMPLE_SET_VALUE_3(CLASS, M1, M2, M3)                                   \
    IMPLE_SET_VALUE_2(CLASS, M1, M2)                                           \
    IMPLE_SET_VALUE_1(CLASS, M3)

#define IMPLE_SET_VALUE_4(CLASS, M1, M2, M3, M4)                               \
    IMPLE_SET_VALUE_3(CLASS, M1, M2, M3)                                       \
    IMPLE_SET_VALUE_1(CLASS, M4)

#define IMPLE_SET_VALUE_5(CLASS, M1, M2, M3, M4, M5)                           \
    IMPLE_SET_VALUE_4(CLASS, M1, M2, M3, M4)                                   \
    IMPLE_SET_VALUE_1(CLASS, M5)

#define IMPLE_SET_VALUE_6(CLASS, M1, M2, M3, M4, M5, M6)                       \
    IMPLE_SET_VALUE_5(CLASS, M1, M2, M3, M4, M5)                               \
    IMPLE_SET_VALUE_1(CLASS, M6)

#define IMPLE_SET_VALUE_7(CLASS, M1, M2, M3, M4, M5, M6, M7)                   \
    IMPLE_SET_VALUE_6(CLASS, M1, M2, M3, M4, M5, M6)                           \
    IMPLE_SET_VALUE_1(CLASS, M7)

#define IMPLE_SET_VALUE_8(CLASS, M1, M2, M3, M4, M5, M6, M7, M8)               \
    IMPLE_SET_VALUE_7(CLASS, M1, M2, M3, M4, M5, M6, M7)                       \
    IMPLE_SET_VALUE_1(CLASS, M8)

#define IMPLE_SET_VALUE_9(CLASS, M1, M2, M3, M4, M5, M6, M7, M8, M9)           \
    IMPLE_SET_VALUE_8(CLASS, M1, M2, M3, M4, M5, M6, M7, M8)                   \
    IMPLE_SET_VALUE_1(CLASS, M9)

#define IMPLE_SET_VALUE_10(CLASS, M1, M2, M3, M4, M5, M6, M7, M8, M9, M10)     \
    IMPLE_SET_VALUE_9(CLASS, M1, M2, M3, M4, M5, M6, M7, M8, M9)               \
    IMPLE_SET_VALUE_1(CLASS, M10)

#define IMPLE_SET_VALUE_11(CLASS, M1, M2, M3, M4, M5, M6, M7, M8, M9, M10,     \
                           M11)                                                \
    IMPLE_SET_VALUE_10(CLASS, M1, M2, M3, M4, M5, M6, M7, M8, M9, M10)         \
    IMPLE_SET_VALUE_1(CLASS, M11)

#define IMPLE_SET_VALUE_12(CLASS, M1, M2, M3, M4, M5, M6, M7, M8, M9, M10,     \
                           M11, M12)                                           \
    IMPLE_SET_VALUE_11(CLASS, M1, M2, M3, M4, M5, M6, M7, M8, M9, M10, M11)    \
    IMPLE_SET_VALUE_1(CLASS, M12)

#define IMPLE_SET_VALUE_13(CLASS, M1, M2, M3, M4, M5, M6, M7, M8, M9, M10,     \
                           M11, M12, M13)                                      \
    IMPLE_SET_VALUE_12(CLASS, M1, M2, M3, M4, M5, M6, M7, M8, M9, M10, M11,    \
                       M12)                                                    \
    IMPLE_SET_VALUE_1(CLASS, M13)

#define IMPLE_SET_VALUE_14(CLASS, M1, M2, M3, M4, M5, M6, M7, M8, M9, M10,     \
                           M11, M12, M13, M14)                                 \
    IMPLE_SET_VALUE_13(CLASS, M1, M2, M3, M4, M5, M6, M7, M8, M9, M10, M11,    \
                       M12, M13)                                               \
    IMPLE_SET_VALUE_1(CLASS, M14)

#define IMPLE_SET_VALUE_15(CLASS, M1, M2, M3, M4, M5, M6, M7, M8, M9, M10,     \
                           M11, M12, M13, M14, M15)                            \
    IMPLE_SET_VALUE_14(CLASS, M1, M2, M3, M4, M5, M6, M7, M8, M9, M10, M11,    \
                       M12, M13, M14)                                          \
    IMPLE_SET_VALUE_1(CLASS, M15)

// init
#define IMPLE_INIT_FUNCTION_1(CLASS, MEMBER)                                   \
    {                                                                          \
        std::function<void(decltype(MEMBER))> setobj = std::bind(              \
            &CLASS::__ReflectSet##MEMBER, this, std::placeholders::_1);        \
        std::function<void()> createobj =                                      \
            std::bind(&CLASS::__ReflectCreate##MEMBER, this);                  \
        FieldContent<decltype(MEMBER)> content =                               \
            createFieldContent<decltype(MEMBER)>(setobj);                      \
        content->setReflectObject(this);                                       \
        content->setName(createString(#MEMBER));                               \
        content->setType(content->TypeOf(this->MEMBER));                       \
        content->setId(index);                                                 \
        __maps->put(content->getName(), content);                              \
        index++;                                                               \
    }

#define IMPLE_INIT_FUNCTION_2(CLASS, M1, M2)                                   \
    IMPLE_INIT_FUNCTION_1(CLASS, M1)                                           \
    IMPLE_INIT_FUNCTION_1(CLASS, M2)

#define IMPLE_INIT_FUNCTION_3(CLASS, M1, M2, M3)                               \
    IMPLE_INIT_FUNCTION_2(CLASS, M1, M2)                                       \
    IMPLE_INIT_FUNCTION_1(CLASS, M3)

#define IMPLE_INIT_FUNCTION_4(CLASS, M1, M2, M3, M4)                           \
    IMPLE_INIT_FUNCTION_3(CLASS, M1, M2, M3)                                   \
    IMPLE_INIT_FUNCTION_1(CLASS, M4)

#define IMPLE_INIT_FUNCTION_5(CLASS, M1, M2, M3, M4, M5)                       \
    IMPLE_INIT_FUNCTION_4(CLASS, M1, M2, M3, M4)                               \
    IMPLE_INIT_FUNCTION_1(CLASS, M5)

#define IMPLE_INIT_FUNCTION_6(CLASS, M1, M2, M3, M4, M5, M6)                   \
    IMPLE_INIT_FUNCTION_5(CLASS, M1, M2, M3, M4, M5)                           \
    IMPLE_INIT_FUNCTION_1(CLASS, M6)

#define IMPLE_INIT_FUNCTION_7(CLASS, M1, M2, M3, M4, M5, M6, M7)               \
    IMPLE_INIT_FUNCTION_6(CLASS, M1, M2, M3, M4, M5, M6)                       \
    IMPLE_INIT_FUNCTION_1(CLASS, M7)

#define IMPLE_INIT_FUNCTION_8(CLASS, M1, M2, M3, M4, M5, M6, M7, M8)           \
    IMPLE_INIT_FUNCTION_7(CLASS, M1, M2, M3, M4, M5, M6, M7)                   \
    IMPLE_INIT_FUNCTION_1(CLASS, M8)

#define IMPLE_INIT_FUNCTION_9(CLASS, M1, M2, M3, M4, M5, M6, M7, M8, M9)       \
    IMPLE_INIT_FUNCTION_8(CLASS, M1, M2, M3, M4, M5, M6, M7, M8)               \
    IMPLE_INIT_FUNCTION_1(CLASS, M9)

#define IMPLE_INIT_FUNCTION_10(CLASS, M1, M2, M3, M4, M5, M6, M7, M8, M9, M10) \
    IMPLE_INIT_FUNCTION_9(CLASS, M1, M2, M3, M4, M5, M6, M7, M8, M9)           \
    IMPLE_INIT_FUNCTION_1(CLASS, M10)

#define IMPLE_INIT_FUNCTION_11(CLASS, M1, M2, M3, M4, M5, M6, M7, M8, M9, M10, \
                               M11)                                            \
    IMPLE_INIT_FUNCTION_10(CLASS, M1, M2, M3, M4, M5, M6, M7, M8, M9, M10)     \
    IMPLE_INIT_FUNCTION_1(CLASS, M11)

#define IMPLE_INIT_FUNCTION_12(CLASS, M1, M2, M3, M4, M5, M6, M7, M8, M9, M10, \
                               M11, M12)                                       \
    IMPLE_INIT_FUNCTION_11(CLASS, M1, M2, M3, M4, M5, M6, M7, M8, M9, M10,     \
                           M11)                                                \
    IMPLE_INIT_FUNCTION_1(CLASS, M12)

#define IMPLE_INIT_FUNCTION_13(CLASS, M1, M2, M3, M4, M5, M6, M7, M8, M9, M10, \
                               M11, M12, M13)                                  \
    IMPLE_INIT_FUNCTION_12(CLASS, M1, M2, M3, M4, M5, M6, M7, M8, M9, M10,     \
                           M11, M12)                                           \
    IMPLE_INIT_FUNCTION_1(CLASS, M13)

#define IMPLE_INIT_FUNCTION_14(CLASS, M1, M2, M3, M4, M5, M6, M7, M8, M9, M10, \
                               M11, M12, M13, M14)                             \
    IMPLE_INIT_FUNCTION_13(CLASS, M1, M2, M3, M4, M5, M6, M7, M8, M9, M10,     \
                           M11, M12, M13)                                      \
    IMPLE_INIT_FUNCTION_1(CLASS, M14)

#define IMPLE_INIT_FUNCTION_15(CLASS, M1, M2, M3, M4, M5, M6, M7, M8, M9, M10, \
                               M11, M12, M13, M14, M15)                        \
    IMPLE_INIT_FUNCTION_14(CLASS, M1, M2, M3, M4, M5, M6, M7, M8, M9, M10,     \
                           M11, M12, M13, M14)                                 \
    IMPLE_INIT_FUNCTION_1(CLASS, M15)

#define IMPLE_INIT_FUNCTION_16(CLASS, M1, M2, M3, M4, M5, M6, M7, M8, M9, M10, \
                               M11, M12, M13, M14, M15, M16)                   \
    IMPLE_INIT_FUNCTION_15(CLASS, M1, M2, M3, M4, M5, M6, M7, M8, M9, M10,     \
                           M11, M12, M13, M14, M15)                            \
    IMPLE_INIT_FUNCTION_1(CLASS, M16)

#define IMPLE_INIT_FUNCTION_DETECT(CLASS, COUNT, ...)                          \
    IMPLE_INIT_FUNCTION_DETECT_TRACE(CLASS, COUNT, __VA_ARGS__)
#define IMPLE_INIT_FUNCTION_DETECT_TRACE(CLASS, COUNT, ...)                    \
    IMPLE_INIT_FUNCTION_DETECT_TRACE1(CLASS, COUNT, __VA_ARGS__)
#define IMPLE_INIT_FUNCTION_DETECT_TRACE1(CLASS, COUNT, ...)                   \
    IMPLE_INIT_FUNCTION_##COUNT(CLASS, __VA_ARGS__)

#define IMPLE_SET_FUNCTION_DETECT(CLASS, COUNT, ...)                           \
    IMPLE_SET_FUNCTION_DETECT_TRACE(CLASS, COUNT, __VA_ARGS__)
#define IMPLE_SET_FUNCTION_DETECT_TRACE(CLASS, COUNT, ...)                     \
    IMPLE_SET_FUNCTION_DETECT_TRACE1(CLASS, COUNT, __VA_ARGS__)
#define IMPLE_SET_FUNCTION_DETECT_TRACE1(CLASS, COUNT, ...)                    \
    IMPLE_SET_VALUE_##COUNT(CLASS, __VA_ARGS__)

#define DECLARE_INIT_TUPLE_DETECT(CLASS, COUNT, ...)                           \
    DECLARE_INIT_TUPLE_DETECT_TRACE(CLASS, COUNT, __VA_ARGS__)
#define DECLARE_INIT_TUPLE_DETECT_TRACE(CLASS, COUNT, ...)                     \
    DECLARE_INIT_TUPLE_DETECT_TRACE1(CLASS, COUNT, __VA_ARGS__)
#define DECLARE_INIT_TUPLE_DETECT_TRACE1(CLASS, COUNT, ...)                    \
    DECLARE_INIT_TUPLE_##COUNT(__VA_ARGS__)

// Set,Get,Create
#define __S(MEMBER) std::function<void(decltype(MEMBER))>
#define __G(MEMBER) std::function<decltype(MEMBER)()>
#define __C(MEMBER) std::function<void()>
#define __L(MEMBER) std::function<Object()>
#define __D() std::function<int()>                // dummy function
#define __LD() std::function<Object()>            // list dummy function
#define __LIG(MEMBER) std::function<Object(int)>  // list item get function
#define __LIA(MEMBER) std::function<void(Object)> // list add function

#define __MI(MEMBER)                                                           \
    std::function<Pair<Object, Object>()> // create map item(key,value)
#define __MIG(MEMBER)                                                          \
    std::function<ArrayList<Pair<Object, Object>>()> // get map items
#define __MIA(MEMBER) std::function<void(Object, Object)>    // add map item

#define __OBJSIZE(MEMBER) std::function<int()> // list size function

#define DECLARE_INIT_TUPLE_1(M1)                                               \
    std::tuple<__S(M1), __D(), __D(), __D(), __D(), __D(), __D(), __D(),       \
               __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(),  \
               __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(),  \
               __D(), __D(), __D(), __D(), __D(), __D()>                       \
        setFuncTuple;                                                          \
    std::tuple<__G(M1), __D(), __D(), __D(), __D(), __D(), __D(), __D(),       \
               __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(),  \
               __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(),  \
               __D(), __D(), __D(), __D(), __D(), __D()>                       \
        getFuncTuple;                                                          \
    std::tuple<__C(M1), __D(), __D(), __D(), __D(), __D(), __D(), __D(),       \
               __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(),  \
               __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(),  \
               __D(), __D(), __D(), __D(), __D(), __D()>                       \
        createFuncTuple;                                                       \
    std::tuple<__L(M1), __LD(), __LD(), __LD(), __LD(), __LD(), __LD(),        \
               __LD(), __LD(), __LD(), __LD(), __LD(), __LD(), __LD(), __LD(), \
               __LD(), __LD(), __LD(), __LD(), __LD(), __LD(), __LD(), __LD(), \
               __LD(), __LD(), __LD(), __LD(), __LD(), __LD(), __LD(), __LD(), \
               __LD()>                                                         \
        createListItemFuncTuple;                                               \
    std::tuple<__LIG(M1), __LIG(), __LIG(), __LIG(), __LIG(), __LIG(),         \
               __LIG(), __LIG(), __LIG(), __LIG(), __LIG(), __LIG(), __LIG(),  \
               __LIG(), __LIG(), __LIG(), __LIG(), __LIG(), __LIG(), __LIG(),  \
               __LIG(), __LIG(), __LIG(), __LIG(), __LIG(), __LIG(), __LIG(),  \
               __LIG(), __LIG(), __LIG(), __LIG(), __LIG()>                    \
        getListItemFuncTuple;                                                  \
    std::tuple<__OBJSIZE(M1), __OBJSIZE(), __OBJSIZE(), __OBJSIZE(),           \
               __OBJSIZE(), __OBJSIZE(), __OBJSIZE(), __OBJSIZE(),             \
               __OBJSIZE(), __OBJSIZE(), __OBJSIZE(), __OBJSIZE(),             \
               __OBJSIZE(), __OBJSIZE(), __OBJSIZE(), __OBJSIZE(),             \
               __OBJSIZE(), __OBJSIZE(), __OBJSIZE(), __OBJSIZE(),             \
               __OBJSIZE(), __OBJSIZE(), __OBJSIZE(), __OBJSIZE(),             \
               __OBJSIZE(), __OBJSIZE(), __OBJSIZE(), __OBJSIZE(),             \
               __OBJSIZE(), __OBJSIZE(), __OBJSIZE(), __OBJSIZE()>             \
        getContainerSizeFuncTuple;                                             \
    std::tuple<__MI(M1), __MI(), __MI(), __MI(), __MI(), __MI(), __MI(),       \
               __MI(), __MI(), __MI(), __MI(), __MI(), __MI(), __MI(), __MI(), \
               __MI(), __MI(), __MI(), __MI(), __MI(), __MI(), __MI(), __MI(), \
               __MI(), __MI(), __MI(), __MI(), __MI(), __MI(), __MI(), __MI(), \
               __MI()>                                                         \
        createMapItemFuncTuple;                                                \
    std::tuple<__MIG(M1), __MIG(), __MIG(), __MIG(), __MIG(), __MIG(),         \
               __MIG(), __MIG(), __MIG(), __MIG(), __MIG(), __MIG(), __MIG(),  \
               __MIG(), __MIG(), __MIG(), __MIG(), __MIG(), __MIG(), __MIG(),  \
               __MIG(), __MIG(), __MIG(), __MIG(), __MIG(), __MIG(), __MIG(),  \
               __MIG(), __MIG(), __MIG(), __MIG(), __MIG()>                    \
        getMapItemsFuncTuple;                                                  \
    std::tuple<__LIA(M1), __LIA(), __LIA(), __LIA(), __LIA(), __LIA(),         \
               __LIA(), __LIA(), __LIA(), __LIA(), __LIA(), __LIA(), __LIA(),  \
               __LIA(), __LIA(), __LIA(), __LIA(), __LIA(), __LIA(), __LIA(),  \
               __LIA(), __LIA(), __LIA(), __LIA(), __LIA(), __LIA(), __LIA(),  \
               __LIA(), __LIA(), __LIA(), __LIA(), __LIA()>                    \
        addListItemFuncTuple;                                                  \
    std::tuple<__MIA(M1), __MIA(), __MIA(), __MIA(), __MIA(), __MIA(),         \
               __MIA(), __MIA(), __MIA(), __MIA(), __MIA(), __MIA(), __MIA(),  \
               __MIA(), __MIA(), __MIA(), __MIA(), __MIA(), __MIA(), __MIA(),  \
               __MIA(), __MIA(), __MIA(), __MIA(), __MIA(), __MIA(), __MIA(),  \
               __MIA(), __MIA(), __MIA(), __MIA(), __MIA()>                    \
        addMapItemFuncTuple;

#define DECLARE_INIT_TUPLE_2(M1, M2)                                           \
    std::tuple<__S(M1), __S(M2), __D(), __D(), __D(), __D(), __D(), __D(),     \
               __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(),  \
               __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(),  \
               __D(), __D(), __D(), __D(), __D(), __D()>                       \
        setFuncTuple;                                                          \
    std::tuple<__G(M1), __G(M2), __D(), __D(), __D(), __D(), __D(), __D(),     \
               __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(),  \
               __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(),  \
               __D(), __D(), __D(), __D(), __D(), __D()>                       \
        getFuncTuple;                                                          \
    std::tuple<__C(M1), __C(M2), __D(), __D(), __D(), __D(), __D(), __D(),     \
               __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(),  \
               __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(),  \
               __D(), __D(), __D(), __D(), __D(), __D()>                       \
        createFuncTuple;                                                       \
    std::tuple<__L(M1), __L(M2), __LD(), __LD(), __LD(), __LD(), __LD(),       \
               __LD(), __LD(), __LD(), __LD(), __LD(), __LD(), __LD(), __LD(), \
               __LD(), __LD(), __LD(), __LD(), __LD(), __LD(), __LD(), __LD(), \
               __LD(), __LD(), __LD(), __LD(), __LD(), __LD(), __LD(), __LD(), \
               __LD()>                                                         \
        createListItemFuncTuple;                                               \
    std::tuple<__LIG(M1), __LIG(M2), __LIG(), __LIG(), __LIG(), __LIG(),       \
               __LIG(), __LIG(), __LIG(), __LIG(), __LIG(), __LIG(), __LIG(),  \
               __LIG(), __LIG(), __LIG(), __LIG(), __LIG(), __LIG(), __LIG(),  \
               __LIG(), __LIG(), __LIG(), __LIG(), __LIG(), __LIG(), __LIG(),  \
               __LIG(), __LIG(), __LIG(), __LIG(), __LIG()>                    \
        getListItemFuncTuple;                                                  \
    std::tuple<__OBJSIZE(M1), __OBJSIZE(M2), __OBJSIZE(), __OBJSIZE(),         \
               __OBJSIZE(), __OBJSIZE(), __OBJSIZE(), __OBJSIZE(),             \
               __OBJSIZE(), __OBJSIZE(), __OBJSIZE(), __OBJSIZE(),             \
               __OBJSIZE(), __OBJSIZE(), __OBJSIZE(), __OBJSIZE(),             \
               __OBJSIZE(), __OBJSIZE(), __OBJSIZE(), __OBJSIZE(),             \
               __OBJSIZE(), __OBJSIZE(), __OBJSIZE(), __OBJSIZE(),             \
               __OBJSIZE(), __OBJSIZE(), __OBJSIZE(), __OBJSIZE(),             \
               __OBJSIZE(), __OBJSIZE(), __OBJSIZE(), __OBJSIZE()>             \
        getContainerSizeFuncTuple;                                             \
    std::tuple<__MI(M1), __MI(M2), __MI(), __MI(), __MI(), __MI(), __MI(),     \
               __MI(), __MI(), __MI(), __MI(), __MI(), __MI(), __MI(), __MI(), \
               __MI(), __MI(), __MI(), __MI(), __MI(), __MI(), __MI(), __MI(), \
               __MI(), __MI(), __MI(), __MI(), __MI(), __MI(), __MI(), __MI(), \
               __MI()>                                                         \
        createMapItemFuncTuple;                                                \
    std::tuple<__MIG(M1), __MIG(M2), __MIG(), __MIG(), __MIG(), __MIG(),       \
               __MIG(), __MIG(), __MIG(), __MIG(), __MIG(), __MIG(), __MIG(),  \
               __MIG(), __MIG(), __MIG(), __MIG(), __MIG(), __MIG(), __MIG(),  \
               __MIG(), __MIG(), __MIG(), __MIG(), __MIG(), __MIG(), __MIG(),  \
               __MIG(), __MIG(), __MIG(), __MIG(), __MIG()>                    \
        getMapItemsFuncTuple;                                                  \
    std::tuple<__LIA(M1), __LIA(M2), __LIA(), __LIA(), __LIA(), __LIA(),       \
               __LIA(), __LIA(), __LIA(), __LIA(), __LIA(), __LIA(), __LIA(),  \
               __LIA(), __LIA(), __LIA(), __LIA(), __LIA(), __LIA(), __LIA(),  \
               __LIA(), __LIA(), __LIA(), __LIA(), __LIA(), __LIA(), __LIA(),  \
               __LIA(), __LIA(), __LIA(), __LIA(), __LIA()>                    \
        addListItemFuncTuple;                                                  \
    std::tuple<__MIA(M1), __MIA(M2), __MIA(), __MIA(), __MIA(), __MIA(),       \
               __MIA(), __MIA(), __MIA(), __MIA(), __MIA(), __MIA(), __MIA(),  \
               __MIA(), __MIA(), __MIA(), __MIA(), __MIA(), __MIA(), __MIA(),  \
               __MIA(), __MIA(), __MIA(), __MIA(), __MIA(), __MIA(), __MIA(),  \
               __MIA(), __MIA(), __MIA(), __MIA(), __MIA()>                    \
        addMapItemFuncTuple;

#define DECLARE_INIT_TUPLE_3(M1, M2, M3)                                       \
    std::tuple<__S(M1), __S(M2), __S(M3), __D(), __D(), __D(), __D(), __D(),   \
               __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(),  \
               __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(),  \
               __D(), __D(), __D(), __D(), __D(), __D()>                       \
        setFuncTuple;                                                          \
    std::tuple<__G(M1), __G(M2), __G(M3), __D(), __D(), __D(), __D(), __D(),   \
               __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(),  \
               __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(),  \
               __D(), __D(), __D(), __D(), __D(), __D()>                       \
        getFuncTuple;                                                          \
    std::tuple<__C(M1), __C(M2), __C(M3), __D(), __D(), __D(), __D(), __D(),   \
               __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(),  \
               __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(),  \
               __D(), __D(), __D(), __D(), __D(), __D()>                       \
        createFuncTuple;                                                       \
    std::tuple<__L(M1), __L(M2), __L(M3), __LD(), __LD(), __LD(), __LD(),      \
               __LD(), __LD(), __LD(), __LD(), __LD(), __LD(), __LD(), __LD(), \
               __LD(), __LD(), __LD(), __LD(), __LD(), __LD(), __LD(), __LD(), \
               __LD(), __LD(), __LD(), __LD(), __LD(), __LD(), __LD(), __LD(), \
               __LD()>                                                         \
        createListItemFuncTuple;                                               \
    std::tuple<__LIG(M1), __LIG(M2), __LIG(M3), __LIG(), __LIG(), __LIG(),     \
               __LIG(), __LIG(), __LIG(), __LIG(), __LIG(), __LIG(), __LIG(),  \
               __LIG(), __LIG(), __LIG(), __LIG(), __LIG(), __LIG(), __LIG(),  \
               __LIG(), __LIG(), __LIG(), __LIG(), __LIG(), __LIG(), __LIG(),  \
               __LIG(), __LIG(), __LIG(), __LIG(), __LIG()>                    \
        getListItemFuncTuple;                                                  \
    std::tuple<__OBJSIZE(M1), __OBJSIZE(M2), __OBJSIZE(M3), __OBJSIZE(),       \
               __OBJSIZE(), __OBJSIZE(), __OBJSIZE(), __OBJSIZE(),             \
               __OBJSIZE(), __OBJSIZE(), __OBJSIZE(), __OBJSIZE(),             \
               __OBJSIZE(), __OBJSIZE(), __OBJSIZE(), __OBJSIZE(),             \
               __OBJSIZE(), __OBJSIZE(), __OBJSIZE(), __OBJSIZE(),             \
               __OBJSIZE(), __OBJSIZE(), __OBJSIZE(), __OBJSIZE(),             \
               __OBJSIZE(), __OBJSIZE(), __OBJSIZE(), __OBJSIZE(),             \
               __OBJSIZE(), __OBJSIZE(), __OBJSIZE(), __OBJSIZE()>             \
        getContainerSizeFuncTuple;                                             \
    std::tuple<__MI(M1), __MI(M2), __MI(M3), __MI(), __MI(), __MI(), __MI(),   \
               __MI(), __MI(), __MI(), __MI(), __MI(), __MI(), __MI(), __MI(), \
               __MI(), __MI(), __MI(), __MI(), __MI(), __MI(), __MI(), __MI(), \
               __MI(), __MI(), __MI(), __MI(), __MI(), __MI(), __MI(), __MI(), \
               __MI()>                                                         \
        createMapItemFuncTuple;                                                \
    std::tuple<__MIG(M1), __MIG(M2), __MIG(M3), __MIG(), __MIG(), __MIG(),     \
               __MIG(), __MIG(), __MIG(), __MIG(), __MIG(), __MIG(), __MIG(),  \
               __MIG(), __MIG(), __MIG(), __MIG(), __MIG(), __MIG(), __MIG(),  \
               __MIG(), __MIG(), __MIG(), __MIG(), __MIG(), __MIG(), __MIG(),  \
               __MIG(), __MIG(), __MIG(), __MIG(), __MIG()>                    \
        getMapItemsFuncTuple;                                                  \
    std::tuple<__LIA(M1), __LIA(M2), __LIA(M3), __LIA(), __LIA(), __LIA(),     \
               __LIA(), __LIA(), __LIA(), __LIA(), __LIA(), __LIA(), __LIA(),  \
               __LIA(), __LIA(), __LIA(), __LIA(), __LIA(), __LIA(), __LIA(),  \
               __LIA(), __LIA(), __LIA(), __LIA(), __LIA(), __LIA(), __LIA(),  \
               __LIA(), __LIA(), __LIA(), __LIA(), __LIA()>                    \
        addListItemFuncTuple;                                                  \
    std::tuple<__MIA(M1), __MIA(M2), __MIA(M3), __MIA(), __MIA(), __MIA(),     \
               __MIA(), __MIA(), __MIA(), __MIA(), __MIA(), __MIA(), __MIA(),  \
               __MIA(), __MIA(), __MIA(), __MIA(), __MIA(), __MIA(), __MIA(),  \
               __MIA(), __MIA(), __MIA(), __MIA(), __MIA(), __MIA(), __MIA(),  \
               __MIA(), __MIA(), __MIA(), __MIA(), __MIA()>                    \
        addMapItemFuncTuple;

#define DECLARE_INIT_TUPLE_4(M1, M2, M3, M4)                                   \
    std::tuple<__S(M1), __S(M2), __S(M3), __S(M4), __D(), __D(), __D(), __D(), \
               __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(),  \
               __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(),  \
               __D(), __D(), __D(), __D(), __D(), __D()>                       \
        setFuncTuple;                                                          \
    std::tuple<__G(M1), __G(M2), __G(M3), __G(M4), __D(), __D(), __D(), __D(), \
               __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(),  \
               __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(),  \
               __D(), __D(), __D(), __D(), __D(), __D()>                       \
        getFuncTuple;                                                          \
    std::tuple<__C(M1), __C(M2), __C(M3), __C(M4), __D(), __D(), __D(), __D(), \
               __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(),  \
               __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(),  \
               __D(), __D(), __D(), __D(), __D(), __D()>                       \
        createFuncTuple;                                                       \
    std::tuple<__L(M1), __L(M2), __L(M3), __L(M4), __LD(), __LD(), __LD(),     \
               __LD(), __LD(), __LD(), __LD(), __LD(), __LD(), __LD(), __LD(), \
               __LD(), __LD(), __LD(), __LD(), __LD(), __LD(), __LD(), __LD(), \
               __LD(), __LD(), __LD(), __LD(), __LD(), __LD(), __LD(), __LD(), \
               __LD()>                                                         \
        createListItemFuncTuple;                                               \
    std::tuple<__LIG(M1), __LIG(M2), __LIG(M3), __LIG(M4), __LIG(), __LIG(),   \
               __LIG(), __LIG(), __LIG(), __LIG(), __LIG(), __LIG(), __LIG(),  \
               __LIG(), __LIG(), __LIG(), __LIG(), __LIG(), __LIG(), __LIG(),  \
               __LIG(), __LIG(), __LIG(), __LIG(), __LIG(), __LIG(), __LIG(),  \
               __LIG(), __LIG(), __LIG(), __LIG(), __LIG()>                    \
        getListItemFuncTuple;                                                  \
    std::tuple<__OBJSIZE(M1), __OBJSIZE(M2), __OBJSIZE(M3), __OBJSIZE(M4),     \
               __OBJSIZE(), __OBJSIZE(), __OBJSIZE(), __OBJSIZE(),             \
               __OBJSIZE(), __OBJSIZE(), __OBJSIZE(), __OBJSIZE(),             \
               __OBJSIZE(), __OBJSIZE(), __OBJSIZE(), __OBJSIZE(),             \
               __OBJSIZE(), __OBJSIZE(), __OBJSIZE(), __OBJSIZE(),             \
               __OBJSIZE(), __OBJSIZE(), __OBJSIZE(), __OBJSIZE(),             \
               __OBJSIZE(), __OBJSIZE(), __OBJSIZE(), __OBJSIZE(),             \
               __OBJSIZE(), __OBJSIZE(), __OBJSIZE(), __OBJSIZE()>             \
        getContainerSizeFuncTuple;                                             \
    std::tuple<__MI(M1), __MI(M2), __MI(M3), __MI(M4), __MI(), __MI(), __MI(), \
               __MI(), __MI(), __MI(), __MI(), __MI(), __MI(), __MI(), __MI(), \
               __MI(), __MI(), __MI(), __MI(), __MI(), __MI(), __MI(), __MI(), \
               __MI(), __MI(), __MI(), __MI(), __MI(), __MI(), __MI(), __MI(), \
               __MI()>                                                         \
        createMapItemFuncTuple;                                                \
    std::tuple<__MIG(M1), __MIG(M2), __MIG(M3), __MIG(M4), __MIG(), __MIG(),   \
               __MIG(), __MIG(), __MIG(), __MIG(), __MIG(), __MIG(), __MIG(),  \
               __MIG(), __MIG(), __MIG(), __MIG(), __MIG(), __MIG(), __MIG(),  \
               __MIG(), __MIG(), __MIG(), __MIG(), __MIG(), __MIG(), __MIG(),  \
               __MIG(), __MIG(), __MIG(), __MIG(), __MIG()>                    \
        getMapItemsFuncTuple;                                                  \
    std::tuple<__LIA(M1), __LIA(M2), __LIA(M3), __LIA(M4), __LIA(), __LIA(),   \
               __LIA(), __LIA(), __LIA(), __LIA(), __LIA(), __LIA(), __LIA(),  \
               __LIA(), __LIA(), __LIA(), __LIA(), __LIA(), __LIA(), __LIA(),  \
               __LIA(), __LIA(), __LIA(), __LIA(), __LIA(), __LIA(), __LIA(),  \
               __LIA(), __LIA(), __LIA(), __LIA(), __LIA()>                    \
        addListItemFuncTuple;                                                  \
    std::tuple<__MIA(M1), __MIA(M2), __MIA(M3), __MIA(M4), __MIA(), __MIA(),   \
               __MIA(), __MIA(), __MIA(), __MIA(), __MIA(), __MIA(), __MIA(),  \
               __MIA(), __MIA(), __MIA(), __MIA(), __MIA(), __MIA(), __MIA(),  \
               __MIA(), __MIA(), __MIA(), __MIA(), __MIA(), __MIA(), __MIA(),  \
               __MIA(), __MIA(), __MIA(), __MIA(), __MIA()>                    \
        addMapItemFuncTuple;

#define DECLARE_INIT_TUPLE_5(M1, M2, M3, M4, M5)                               \
    std::tuple<__S(M1), __S(M2), __S(M3), __S(M4), __S(M5), __D(), __D(),      \
               __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(),  \
               __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(),  \
               __D(), __D(), __D(), __D(), __D(), __D(), __D()>                \
        setFuncTuple;                                                          \
    std::tuple<__G(M1), __G(M2), __G(M3), __G(M4), __G(M5), __D(), __D(),      \
               __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(),  \
               __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(),  \
               __D(), __D(), __D(), __D(), __D(), __D(), __D()>                \
        getFuncTuple;                                                          \
    std::tuple<__C(M1), __C(M2), __C(M3), __C(M4), __C(M5), __D(), __D(),      \
               __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(),  \
               __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(),  \
               __D(), __D(), __D(), __D(), __D(), __D(), __D()>                \
        createFuncTuple;                                                       \
    std::tuple<__L(M1), __L(M2), __L(M3), __L(M4), __L(M5), __LD(), __LD(),    \
               __LD(), __LD(), __LD(), __LD(), __LD(), __LD(), __LD(), __LD(), \
               __LD(), __LD(), __LD(), __LD(), __LD(), __LD(), __LD(), __LD(), \
               __LD(), __LD(), __LD(), __LD(), __LD(), __LD(), __LD(), __LD(), \
               __LD()>                                                         \
        createListItemFuncTuple;                                               \
    std::tuple<__LIG(M1), __LIG(M2), __LIG(M3), __LIG(M4), __LIG(M5), __LIG(), \
               __LIG(), __LIG(), __LIG(), __LIG(), __LIG(), __LIG(), __LIG(),  \
               __LIG(), __LIG(), __LIG(), __LIG(), __LIG(), __LIG(), __LIG(),  \
               __LIG(), __LIG(), __LIG(), __LIG(), __LIG(), __LIG(), __LIG(),  \
               __LIG(), __LIG(), __LIG(), __LIG(), __LIG()>                    \
        getListItemFuncTuple;                                                  \
    std::tuple<__OBJSIZE(M1), __OBJSIZE(M2), __OBJSIZE(M3), __OBJSIZE(M4),     \
               __OBJSIZE(M5), __OBJSIZE(), __OBJSIZE(), __OBJSIZE(),           \
               __OBJSIZE(), __OBJSIZE(), __OBJSIZE(), __OBJSIZE(),             \
               __OBJSIZE(), __OBJSIZE(), __OBJSIZE(), __OBJSIZE(),             \
               __OBJSIZE(), __OBJSIZE(), __OBJSIZE(), __OBJSIZE(),             \
               __OBJSIZE(), __OBJSIZE(), __OBJSIZE(), __OBJSIZE(),             \
               __OBJSIZE(), __OBJSIZE(), __OBJSIZE(), __OBJSIZE(),             \
               __OBJSIZE(), __OBJSIZE(), __OBJSIZE(), __OBJSIZE()>             \
        getContainerSizeFuncTuple;                                             \
    std::tuple<__MI(M1), __MI(M2), __MI(M3), __MI(M4), __MI(M5), __MI(),       \
               __MI(), __MI(), __MI(), __MI(), __MI(), __MI(), __MI(), __MI(), \
               __MI(), __MI(), __MI(), __MI(), __MI(), __MI(), __MI(), __MI(), \
               __MI(), __MI(), __MI(), __MI(), __MI(), __MI(), __MI(), __MI(), \
               __MI(), __MI()>                                                 \
        createMapItemFuncTuple;                                                \
    std::tuple<__MIG(M1), __MIG(M2), __MIG(M3), __MIG(M4), __MIG(M5), __MIG(), \
               __MIG(), __MIG(), __MIG(), __MIG(), __MIG(), __MIG(), __MIG(),  \
               __MIG(), __MIG(), __MIG(), __MIG(), __MIG(), __MIG(), __MIG(),  \
               __MIG(), __MIG(), __MIG(), __MIG(), __MIG(), __MIG(), __MIG(),  \
               __MIG(), __MIG(), __MIG(), __MIG(), __MIG()>                    \
        getMapItemsFuncTuple;                                                  \
    std::tuple<__LIA(M1), __LIA(M2), __LIA(M3), __LIA(M4), __LIA(M5), __LIA(), \
               __LIA(), __LIA(), __LIA(), __LIA(), __LIA(), __LIA(), __LIA(),  \
               __LIA(), __LIA(), __LIA(), __LIA(), __LIA(), __LIA(), __LIA(),  \
               __LIA(), __LIA(), __LIA(), __LIA(), __LIA(), __LIA(), __LIA(),  \
               __LIA(), __LIA(), __LIA(), __LIA(), __LIA()>                    \
        addListItemFuncTuple;                                                  \
    std::tuple<__MIA(M1), __MIA(M2), __MIA(M3), __MIA(M4), __MIA(M5), __MIA(), \
               __MIA(), __MIA(), __MIA(), __MIA(), __MIA(), __MIA(), __MIA(),  \
               __MIA(), __MIA(), __MIA(), __MIA(), __MIA(), __MIA(), __MIA(),  \
               __MIA(), __MIA(), __MIA(), __MIA(), __MIA(), __MIA(), __MIA(),  \
               __MIA(), __MIA(), __MIA(), __MIA(), __MIA()>                    \
        addMapItemFuncTuple;

#define DECLARE_INIT_TUPLE_6(M1, M2, M3, M4, M5, M6)                           \
    std::tuple<__S(M1), __S(M2), __S(M3), __S(M4), __S(M5), __S(M6), __D(),    \
               __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(),  \
               __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(),  \
               __D(), __D(), __D(), __D(), __D(), __D(), __D()>                \
        setFuncTuple;                                                          \
    std::tuple<__G(M1), __G(M2), __G(M3), __G(M4), __G(M5), __G(M6), __D(),    \
               __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(),  \
               __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(),  \
               __D(), __D(), __D(), __D(), __D(), __D(), __D()>                \
        getFuncTuple;                                                          \
    std::tuple<__C(M1), __C(M2), __C(M3), __C(M4), __C(M5), __C(M6), __D(),    \
               __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(),  \
               __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(),  \
               __D(), __D(), __D(), __D(), __D(), __D(), __D()>                \
        createFuncTuple;                                                       \
    std::tuple<__L(M1), __L(M2), __L(M3), __L(M4), __L(M5), __L(M6), __LD(),   \
               __LD(), __LD(), __LD(), __LD(), __LD(), __LD(), __LD(), __LD(), \
               __LD(), __LD(), __LD(), __LD(), __LD(), __LD(), __LD(), __LD(), \
               __LD(), __LD(), __LD(), __LD(), __LD(), __LD(), __LD(), __LD(), \
               __LD()>                                                         \
        createListItemFuncTuple;                                               \
    std::tuple<__LIG(M1), __LIG(M2), __LIG(M3), __LIG(M4), __LIG(M5),          \
               __LIG(M6), __LIG(), __LIG(), __LIG(), __LIG(), __LIG(),         \
               __LIG(), __LIG(), __LIG(), __LIG(), __LIG(), __LIG(), __LIG(),  \
               __LIG(), __LIG(), __LIG(), __LIG(), __LIG(), __LIG(), __LIG(),  \
               __LIG(), __LIG(), __LIG(), __LIG(), __LIG(), __LIG(), __LIG()>  \
        getListItemFuncTuple;                                                  \
    std::tuple<__OBJSIZE(M1), __OBJSIZE(M2), __OBJSIZE(M3), __OBJSIZE(M4),     \
               __OBJSIZE(M5), __OBJSIZE(M6), __OBJSIZE(), __OBJSIZE(),         \
               __OBJSIZE(), __OBJSIZE(), __OBJSIZE(), __OBJSIZE(),             \
               __OBJSIZE(), __OBJSIZE(), __OBJSIZE(), __OBJSIZE(),             \
               __OBJSIZE(), __OBJSIZE(), __OBJSIZE(), __OBJSIZE(),             \
               __OBJSIZE(), __OBJSIZE(), __OBJSIZE(), __OBJSIZE(),             \
               __OBJSIZE(), __OBJSIZE(), __OBJSIZE(), __OBJSIZE(),             \
               __OBJSIZE(), __OBJSIZE(), __OBJSIZE(), __OBJSIZE()>             \
        getContainerSizeFuncTuple;                                             \
    std::tuple<__MI(M1), __MI(M2), __MI(M3), __MI(M4), __MI(M5), __MI(M6),     \
               __MI(), __MI(), __MI(), __MI(), __MI(), __MI(), __MI(), __MI(), \
               __MI(), __MI(), __MI(), __MI(), __MI(), __MI(), __MI(), __MI(), \
               __MI(), __MI(), __MI(), __MI(), __MI(), __MI(), __MI(), __MI(), \
               __MI(), __MI()>                                                 \
        createMapItemFuncTuple;                                                \
    std::tuple<__MIG(M1), __MIG(M2), __MIG(M3), __MIG(M4), __MIG(M5),          \
               __MIG(M6), __MIG(), __MIG(), __MIG(), __MIG(), __MIG(),         \
               __MIG(), __MIG(), __MIG(), __MIG(), __MIG(), __MIG(), __MIG(),  \
               __MIG(), __MIG(), __MIG(), __MIG(), __MIG(), __MIG(), __MIG(),  \
               __MIG(), __MIG(), __MIG(), __MIG(), __MIG(), __MIG(), __MIG()>  \
        getMapItemsFuncTuple;                                                  \
    std::tuple<__LIA(M1), __LIA(M2), __LIA(M3), __LIA(M4), __LIA(M5),          \
               __LIA(M6), __LIA(), __LIA(), __LIA(), __LIA(), __LIA(),         \
               __LIA(), __LIA(), __LIA(), __LIA(), __LIA(), __LIA(), __LIA(),  \
               __LIA(), __LIA(), __LIA(), __LIA(), __LIA(), __LIA(), __LIA(),  \
               __LIA(), __LIA(), __LIA(), __LIA(), __LIA(), __LIA(), __LIA()>  \
        addListItemFuncTuple;                                                  \
    std::tuple<__MIA(M1), __MIA(M2), __MIA(M3), __MIA(M4), __MIA(M5),          \
               __MIA(M6), __MIA(), __MIA(), __MIA(), __MIA(), __MIA(),         \
               __MIA(), __MIA(), __MIA(), __MIA(), __MIA(), __MIA(), __MIA(),  \
               __MIA(), __MIA(), __MIA(), __MIA(), __MIA(), __MIA(), __MIA(),  \
               __MIA(), __MIA(), __MIA(), __MIA(), __MIA(), __MIA(), __MIA()>  \
        addMapItemFuncTuple;

#define DECLARE_INIT_TUPLE_7(M1, M2, M3, M4, M5, M6, M7)                       \
    std::tuple<__S(M1), __S(M2), __S(M3), __S(M4), __S(M5), __S(M6), __S(M7),  \
               __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(),  \
               __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(),  \
               __D(), __D(), __D(), __D(), __D(), __D(), __D()>                \
        setFuncTuple;                                                          \
    std::tuple<__G(M1), __G(M2), __G(M3), __G(M4), __G(M5), __G(M6), __G(M7),  \
               __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(),  \
               __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(),  \
               __D(), __D(), __D(), __D(), __D(), __D(), __D()>                \
        getFuncTuple;                                                          \
    std::tuple<__C(M1), __C(M2), __C(M3), __C(M4), __C(M5), __C(M6), __C(M7),  \
               __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(),  \
               __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(),  \
               __D(), __D(), __D(), __D(), __D(), __D(), __D()>                \
        createFuncTuple;                                                       \
    std::tuple<__L(M1), __L(M2), __L(M3), __L(M4), __L(M5), __L(M6), __L(M7),  \
               __LD(), __LD(), __LD(), __LD(), __LD(), __LD(), __LD(), __LD(), \
               __LD(), __LD(), __LD(), __LD(), __LD(), __LD(), __LD(), __LD(), \
               __LD(), __LD(), __LD(), __LD(), __LD(), __LD(), __LD(), __LD(), \
               __LD()>                                                         \
        createListItemFuncTuple;                                               \
    std::tuple<__LIG(M1), __LIG(M2), __LIG(M3), __LIG(M4), __LIG(M5),          \
               __LIG(M6), __LIG(M7), __LIG(), __LIG(), __LIG(), __LIG(),       \
               __LIG(), __LIG(), __LIG(), __LIG(), __LIG(), __LIG(), __LIG(),  \
               __LIG(), __LIG(), __LIG(), __LIG(), __LIG(), __LIG(), __LIG(),  \
               __LIG(), __LIG(), __LIG(), __LIG(), __LIG(), __LIG(), __LIG()>  \
        getListItemFuncTuple;                                                  \
    std::tuple<__OBJSIZE(M1), __OBJSIZE(M2), __OBJSIZE(M3), __OBJSIZE(M4),     \
               __OBJSIZE(M5), __OBJSIZE(M6), __OBJSIZE(M7), __OBJSIZE(),       \
               __OBJSIZE(), __OBJSIZE(), __OBJSIZE(), __OBJSIZE(),             \
               __OBJSIZE(), __OBJSIZE(), __OBJSIZE(), __OBJSIZE(),             \
               __OBJSIZE(), __OBJSIZE(), __OBJSIZE(), __OBJSIZE(),             \
               __OBJSIZE(), __OBJSIZE(), __OBJSIZE(), __OBJSIZE(),             \
               __OBJSIZE(), __OBJSIZE(), __OBJSIZE(), __OBJSIZE(),             \
               __OBJSIZE(), __OBJSIZE(), __OBJSIZE(), __OBJSIZE()>             \
        getContainerSizeFuncTuple;                                             \
    std::tuple<__MI(M1), __MI(M2), __MI(M3), __MI(M4), __MI(M5), __MI(M6),     \
               __MI(M7), __MI(), __MI(), __MI(), __MI(), __MI(), __MI(),       \
               __MI(), __MI(), __MI(), __MI(), __MI(), __MI(), __MI(), __MI(), \
               __MI(), __MI(), __MI(), __MI(), __MI(), __MI(), __MI(), __MI(), \
               __MI(), __MI(), __MI()>                                         \
        createMapItemFuncTuple;                                                \
    std::tuple<__MIG(M1), __MIG(M2), __MIG(M3), __MIG(M4), __MIG(M5),          \
               __MIG(M6), __MIG(M7), __MIG(), __MIG(), __MIG(), __MIG(),       \
               __MIG(), __MIG(), __MIG(), __MIG(), __MIG(), __MIG(), __MIG(),  \
               __MIG(), __MIG(), __MIG(), __MIG(), __MIG(), __MIG(), __MIG(),  \
               __MIG(), __MIG(), __MIG(), __MIG(), __MIG(), __MIG(), __MIG()>  \
        getMapItemsFuncTuple;                                                  \
    std::tuple<__LIA(M1), __LIA(M2), __LIA(M3), __LIA(M4), __LIA(M5),          \
               __LIA(M6), __LIA(M7), __LIA(), __LIA(), __LIA(), __LIA(),       \
               __LIA(), __LIA(), __LIA(), __LIA(), __LIA(), __LIA(), __LIA(),  \
               __LIA(), __LIA(), __LIA(), __LIA(), __LIA(), __LIA(), __LIA(),  \
               __LIA(), __LIA(), __LIA(), __LIA(), __LIA(), __LIA(), __LIA()>  \
        addListItemFuncTuple;                                                  \
    std::tuple<__MIA(M1), __MIA(M2), __MIA(M3), __MIA(M4), __MIA(M5),          \
               __MIA(M6), __MIA(M7), __MIA(), __MIA(), __MIA(), __MIA(),       \
               __MIA(), __MIA(), __MIA(), __MIA(), __MIA(), __MIA(), __MIA(),  \
               __MIA(), __MIA(), __MIA(), __MIA(), __MIA(), __MIA(), __MIA(),  \
               __MIA(), __MIA(), __MIA(), __MIA(), __MIA(), __MIA(), __MIA()>  \
        addMapItemFuncTuple;

#define DECLARE_INIT_TUPLE_8(M1, M2, M3, M4, M5, M6, M7, M8)                   \
    std::tuple<__S(M1), __S(M2), __S(M3), __S(M4), __S(M5), __S(M6), __S(M7),  \
               __S(M8), __D(), __D(), __D(), __D(), __D(), __D(), __D(),       \
               __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(),  \
               __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D()>         \
        setFuncTuple;                                                          \
    std::tuple<__G(M1), __G(M2), __G(M3), __G(M4), __G(M5), __G(M6), __G(M7),  \
               __G(M8), __D(), __D(), __D(), __D(), __D(), __D(), __D(),       \
               __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(),  \
               __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D()>         \
        getFuncTuple;                                                          \
    std::tuple<__C(M1), __C(M2), __C(M3), __C(M4), __C(M5), __C(M6), __C(M7),  \
               __C(M8), __D(), __D(), __D(), __D(), __D(), __D(), __D(),       \
               __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(),  \
               __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D()>         \
        createFuncTuple;                                                       \
    std::tuple<__L(M1), __L(M2), __L(M3), __L(M4), __L(M5), __L(M6), __L(M7),  \
               __L(M8), __LD(), __LD(), __LD(), __LD(), __LD(), __LD(),        \
               __LD(), __LD(), __LD(), __LD(), __LD(), __LD(), __LD(), __LD(), \
               __LD(), __LD(), __LD(), __LD(), __LD(), __LD(), __LD(), __LD(), \
               __LD(), __LD()>                                                 \
        createListItemFuncTuple;                                               \
    std::tuple<__LIG(M1), __LIG(M2), __LIG(M3), __LIG(M4), __LIG(M5),          \
               __LIG(M6), __LIG(M7), __LIG(M8), __LIG(), __LIG(), __LIG(),     \
               __LIG(), __LIG(), __LIG(), __LIG(), __LIG(), __LIG(), __LIG(),  \
               __LIG(), __LIG(), __LIG(), __LIG(), __LIG(), __LIG(), __LIG(),  \
               __LIG(), __LIG(), __LIG(), __LIG(), __LIG(), __LIG(), __LIG()>  \
        getListItemFuncTuple;                                                  \
    std::tuple<__OBJSIZE(M1), __OBJSIZE(M2), __OBJSIZE(M3), __OBJSIZE(M4),     \
               __OBJSIZE(M5), __OBJSIZE(M6), __OBJSIZE(M7), __OBJSIZE(M8),     \
               __OBJSIZE(), __OBJSIZE(), __OBJSIZE(), __OBJSIZE(),             \
               __OBJSIZE(), __OBJSIZE(), __OBJSIZE(), __OBJSIZE(),             \
               __OBJSIZE(), __OBJSIZE(), __OBJSIZE(), __OBJSIZE(),             \
               __OBJSIZE(), __OBJSIZE(), __OBJSIZE(), __OBJSIZE(),             \
               __OBJSIZE(), __OBJSIZE(), __OBJSIZE(), __OBJSIZE(),             \
               __OBJSIZE(), __OBJSIZE(), __OBJSIZE(), __OBJSIZE()>             \
        getContainerSizeFuncTuple;                                             \
    std::tuple<__MI(M1), __MI(M2), __MI(M3), __MI(M4), __MI(M5), __MI(M6),     \
               __MI(M7), __MI(M8), __MI(), __MI(), __MI(), __MI(), __MI(),     \
               __MI(), __MI(), __MI(), __MI(), __MI(), __MI(), __MI(), __MI(), \
               __MI(), __MI(), __MI(), __MI(), __MI(), __MI(), __MI(), __MI(), \
               __MI(), __MI(), __MI()>                                         \
        createMapItemFuncTuple;                                                \
    std::tuple<__MIG(M1), __MIG(M2), __MIG(M3), __MIG(M4), __MIG(M5),          \
               __MIG(M6), __MIG(M7), __MIG(M8), __MIG(), __MIG(), __MIG(),     \
               __MIG(), __MIG(), __MIG(), __MIG(), __MIG(), __MIG(), __MIG(),  \
               __MIG(), __MIG(), __MIG(), __MIG(), __MIG(), __MIG(), __MIG(),  \
               __MIG(), __MIG(), __MIG(), __MIG(), __MIG(), __MIG(), __MIG()>  \
        getMapItemsFuncTuple;                                                  \
    std::tuple<__LIA(M1), __LIA(M2), __LIA(M3), __LIA(M4), __LIA(M5),          \
               __LIA(M6), __LIA(M7), __LIA(M8), __LIA(), __LIA(), __LIA(),     \
               __LIA(), __LIA(), __LIA(), __LIA(), __LIA(), __LIA(), __LIA(),  \
               __LIA(), __LIA(), __LIA(), __LIA(), __LIA(), __LIA(), __LIA(),  \
               __LIA(), __LIA(), __LIA(), __LIA(), __LIA(), __LIA(), __LIA()>  \
        addListItemFuncTuple;                                                  \
    std::tuple<__MIA(M1), __MIA(M2), __MIA(M3), __MIA(M4), __MIA(M5),          \
               __MIA(M6), __MIA(M7), __MIA(M8), __MIA(), __MIA(), __MIA(),     \
               __MIA(), __MIA(), __MIA(), __MIA(), __MIA(), __MIA(), __MIA(),  \
               __MIA(), __MIA(), __MIA(), __MIA(), __MIA(), __MIA(), __MIA(),  \
               __MIA(), __MIA(), __MIA(), __MIA(), __MIA(), __MIA(), __MIA()>  \
        addMapItemFuncTuple;

#define DECLARE_INIT_TUPLE_9(M1, M2, M3, M4, M5, M6, M7, M8, M9)               \
    std::tuple<__S(M1), __S(M2), __S(M3), __S(M4), __S(M5), __S(M6), __S(M7),  \
               __S(M8), __S(M9), __D(), __D(), __D(), __D(), __D(), __D(),     \
               __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(),  \
               __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D()>         \
        setFuncTuple;                                                          \
    std::tuple<__G(M1), __G(M2), __G(M3), __G(M4), __G(M5), __G(M6), __G(M7),  \
               __G(M8), __G(M9), __D(), __D(), __D(), __D(), __D(), __D(),     \
               __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(),  \
               __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D()>         \
        getFuncTuple;                                                          \
    std::tuple<__C(M1), __C(M2), __C(M3), __C(M4), __C(M5), __C(M6), __C(M7),  \
               __C(M8), __C(M9), __D(), __D(), __D(), __D(), __D(), __D(),     \
               __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(),  \
               __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D()>         \
        createFuncTuple;                                                       \
    std::tuple<__L(M1), __L(M2), __L(M3), __L(M4), __L(M5), __L(M6), __L(M7),  \
               __L(M8), __L(M9), __LD(), __LD(), __LD(), __LD(), __LD(),       \
               __LD(), __LD(), __LD(), __LD(), __LD(), __LD(), __LD(), __LD(), \
               __LD(), __LD(), __LD(), __LD(), __LD(), __LD(), __LD(), __LD(), \
               __LD(), __LD()>                                                 \
        createListItemFuncTuple;                                               \
    std::tuple<__LIG(M1), __LIG(M2), __LIG(M3), __LIG(M4), __LIG(M5),          \
               __LIG(M6), __LIG(M7), __LIG(M8), __LIG(M9), __LIG(), __LIG(),   \
               __LIG(), __LIG(), __LIG(), __LIG(), __LIG(), __LIG(), __LIG(),  \
               __LIG(), __LIG(), __LIG(), __LIG(), __LIG(), __LIG(), __LIG(),  \
               __LIG(), __LIG(), __LIG(), __LIG(), __LIG(), __LIG(), __LIG()>  \
        getListItemFuncTuple;                                                  \
    std::tuple<__OBJSIZE(M1), __OBJSIZE(M2), __OBJSIZE(M3), __OBJSIZE(M4),     \
               __OBJSIZE(M5), __OBJSIZE(M6), __OBJSIZE(M7), __OBJSIZE(M8),     \
               __OBJSIZE(M9), __OBJSIZE(), __OBJSIZE(), __OBJSIZE(),           \
               __OBJSIZE(), __OBJSIZE(), __OBJSIZE(), __OBJSIZE(),             \
               __OBJSIZE(), __OBJSIZE(), __OBJSIZE(), __OBJSIZE(),             \
               __OBJSIZE(), __OBJSIZE(), __OBJSIZE(), __OBJSIZE(),             \
               __OBJSIZE(), __OBJSIZE(), __OBJSIZE(), __OBJSIZE(),             \
               __OBJSIZE(), __OBJSIZE(), __OBJSIZE(), __OBJSIZE()>             \
        getContainerSizeFuncTuple;                                             \
    std::tuple<__MI(M1), __MI(M2), __MI(M3), __MI(M4), __MI(M5), __MI(M6),     \
               __MI(M7), __MI(M8), __MI(M9), __MI(), __MI(), __MI(), __MI(),   \
               __MI(), __MI(), __MI(), __MI(), __MI(), __MI(), __MI(), __MI(), \
               __MI(), __MI(), __MI(), __MI(), __MI(), __MI(), __MI(), __MI(), \
               __MI(), __MI(), __MI()>                                         \
        createMapItemFuncTuple;                                                \
    std::tuple<__MIG(M1), __MIG(M2), __MIG(M3), __MIG(M4), __MIG(M5),          \
               __MIG(M6), __MIG(M7), __MIG(M8), __MIG(M9), __MIG(), __MIG(),   \
               __MIG(), __MIG(), __MIG(), __MIG(), __MIG(), __MIG(), __MIG(),  \
               __MIG(), __MIG(), __MIG(), __MIG(), __MIG(), __MIG(), __MIG(),  \
               __MIG(), __MIG(), __MIG(), __MIG(), __MIG(), __MIG(), __MIG()>  \
        getMapItemsFuncTuple;                                                  \
    std::tuple<__LIA(M1), __LIA(M2), __LIA(M3), __LIA(M4), __LIA(M5),          \
               __LIA(M6), __LIA(M7), __LIA(M8), __LIA(M9), __LIA(), __LIA(),   \
               __LIA(), __LIA(), __LIA(), __LIA(), __LIA(), __LIA(), __LIA(),  \
               __LIA(), __LIA(), __LIA(), __LIA(), __LIA(), __LIA(), __LIA(),  \
               __LIA(), __LIA(), __LIA(), __LIA(), __LIA(), __LIA(), __LIA()>  \
        addListItemFuncTuple;                                                  \
    std::tuple<__MIA(M1), __MIA(M2), __MIA(M3), __MIA(M4), __MIA(M5),          \
               __MIA(M6), __MIA(M7), __MIA(M8), __MIA(M9), __MIA(), __MIA(),   \
               __MIA(), __MIA(), __MIA(), __MIA(), __MIA(), __MIA(), __MIA(),  \
               __MIA(), __MIA(), __MIA(), __MIA(), __MIA(), __MIA(), __MIA(),  \
               __MIA(), __MIA(), __MIA(), __MIA(), __MIA(), __MIA(), __MIA()>  \
        addMapItemFuncTuple;

#define DECLARE_INIT_TUPLE_10(M1, M2, M3, M4, M5, M6, M7, M8, M9, M10)         \
    std::tuple<__S(M1), __S(M2), __S(M3), __S(M4), __S(M5), __S(M6), __S(M7),  \
               __S(M8), __S(M9), __S(M10), __D(), __D(), __D(), __D(), __D(),  \
               __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(),  \
               __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D()>         \
        setFuncTuple;                                                          \
    std::tuple<__G(M1), __G(M2), __G(M3), __G(M4), __G(M5), __G(M6), __G(M7),  \
               __G(M8), __G(M9), __G(M10), __D(), __D(), __D(), __D(), __D(),  \
               __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(),  \
               __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D()>         \
        getFuncTuple;                                                          \
    std::tuple<__C(M1), __C(M2), __C(M3), __C(M4), __C(M5), __C(M6), __C(M7),  \
               __C(M8), __C(M9), __C(M10), __D(), __D(), __D(), __D(), __D(),  \
               __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(),  \
               __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D()>         \
        createFuncTuple;                                                       \
    std::tuple<__L(M1), __L(M2), __L(M3), __L(M4), __L(M5), __L(M6), __L(M7),  \
               __L(M8), __L(M9), __L(M10), __LD(), __LD(), __LD(), __LD(),     \
               __LD(), __LD(), __LD(), __LD(), __LD(), __LD(), __LD(), __LD(), \
               __LD(), __LD(), __LD(), __LD(), __LD(), __LD(), __LD(), __LD(), \
               __LD(), __LD()>                                                 \
        createListItemFuncTuple;                                               \
    std::tuple<__LIG(M1), __LIG(M2), __LIG(M3), __LIG(M4), __LIG(M5),          \
               __LIG(M6), __LIG(M7), __LIG(M8), __LIG(M9), __LIG(M10),         \
               __LIG(), __LIG(), __LIG(), __LIG(), __LIG(), __LIG(), __LIG(),  \
               __LIG(), __LIG(), __LIG(), __LIG(), __LIG(), __LIG(), __LIG(),  \
               __LIG(), __LIG(), __LIG(), __LIG(), __LIG(), __LIG(), __LIG(),  \
               __LIG()>                                                        \
        getListItemFuncTuple;                                                  \
    std::tuple<__OBJSIZE(M1), __OBJSIZE(M2), __OBJSIZE(M3), __OBJSIZE(M4),     \
               __OBJSIZE(M5), __OBJSIZE(M6), __OBJSIZE(M7), __OBJSIZE(M8),     \
               __OBJSIZE(M9), __OBJSIZE(M10), __OBJSIZE(), __OBJSIZE(),        \
               __OBJSIZE(), __OBJSIZE(), __OBJSIZE(), __OBJSIZE(),             \
               __OBJSIZE(), __OBJSIZE(), __OBJSIZE(), __OBJSIZE(),             \
               __OBJSIZE(), __OBJSIZE(), __OBJSIZE(), __OBJSIZE(),             \
               __OBJSIZE(), __OBJSIZE(), __OBJSIZE(), __OBJSIZE(),             \
               __OBJSIZE(), __OBJSIZE(), __OBJSIZE(), __OBJSIZE()>             \
        getContainerSizeFuncTuple;                                             \
    std::tuple<__MI(M1), __MI(M2), __MI(M3), __MI(M4), __MI(M5), __MI(M6),     \
               __MI(M7), __MI(M8), __MI(M9), __MI(M10), __MI(), __MI(),        \
               __MI(), __MI(), __MI(), __MI(), __MI(), __MI(), __MI(), __MI(), \
               __MI(), __MI(), __MI(), __MI(), __MI(), __MI(), __MI(), __MI(), \
               __MI(), __MI(), __MI(), __MI()>                                 \
        createMapItemFuncTuple;                                                \
    std::tuple<__MIG(M1), __MIG(M2), __MIG(M3), __MIG(M4), __MIG(M5),          \
               __MIG(M6), __MIG(M7), __MIG(M8), __MIG(M9), __MIG(M10),         \
               __MIG(), __MIG(), __MIG(), __MIG(), __MIG(), __MIG(), __MIG(),  \
               __MIG(), __MIG(), __MIG(), __MIG(), __MIG(), __MIG(), __MIG(),  \
               __MIG(), __MIG(), __MIG(), __MIG(), __MIG(), __MIG(), __MIG(),  \
               __MIG()>                                                        \
        getMapItemsFuncTuple;                                                  \
    std::tuple<__LIA(M1), __LIA(M2), __LIA(M3), __LIA(M4), __LIA(M5),          \
               __LIA(M6), __LIA(M7), __LIA(M8), __LIA(M9), __LIA(M10),         \
               __LIA(), __LIA(), __LIA(), __LIA(), __LIA(), __LIA(), __LIA(),  \
               __LIA(), __LIA(), __LIA(), __LIA(), __LIA(), __LIA(), __LIA(),  \
               __LIA(), __LIA(), __LIA(), __LIA(), __LIA(), __LIA(), __LIA(),  \
               __LIA()>                                                        \
        addListItemFuncTuple;                                                  \
    std::tuple<__MIA(M1), __MIA(M2), __MIA(M3), __MIA(M4), __MIA(M5),          \
               __MIA(M6), __MIA(M7), __MIA(M8), __MIA(M9), __MIA(M10),         \
               __MIA(), __MIA(), __MIA(), __MIA(), __MIA(), __MIA(), __MIA(),  \
               __MIA(), __MIA(), __MIA(), __MIA(), __MIA(), __MIA(), __MIA(),  \
               __MIA(), __MIA(), __MIA(), __MIA(), __MIA(), __MIA(), __MIA(),  \
               __MIA()>                                                        \
        addMapItemFuncTuple;

#define DECLARE_INIT_TUPLE_11(M1, M2, M3, M4, M5, M6, M7, M8, M9, M10, M11)    \
    std::tuple<__S(M1), __S(M2), __S(M3), __S(M4), __S(M5), __S(M6), __S(M7),  \
               __S(M8), __S(M9), __S(M10), __S(M11), __D(), __D(), __D(),      \
               __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(),  \
               __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D()>  \
        setFuncTuple;                                                          \
    std::tuple<__G(M1), __G(M2), __G(M3), __G(M4), __G(M5), __G(M6), __G(M7),  \
               __G(M8), __G(M9), __G(M10), __G(M11), __D(), __D(), __D(),      \
               __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(),  \
               __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D()>  \
        getFuncTuple;                                                          \
    std::tuple<__C(M1), __C(M2), __C(M3), __C(M4), __C(M5), __C(M6), __C(M7),  \
               __C(M8), __C(M9), __C(M10), __C(M11), __D(), __D(), __D(),      \
               __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(),  \
               __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D()>  \
        createFuncTuple;                                                       \
    std::tuple<__L(M1), __L(M2), __L(M3), __L(M4), __L(M5), __L(M6), __L(M7),  \
               __L(M8), __L(M9), __L(M10), __L(M11), __LD(), __LD(), __LD(),   \
               __LD(), __LD(), __LD(), __LD(), __LD(), __LD(), __LD(), __LD(), \
               __LD(), __LD(), __LD(), __LD(), __LD(), __LD(), __LD(), __LD(), \
               __LD(), __LD()>                                                 \
        createListItemFuncTuple;                                               \
    std::tuple<__LIG(M1), __LIG(M2), __LIG(M3), __LIG(M4), __LIG(M5),          \
               __LIG(M6), __LIG(M7), __LIG(M8), __LIG(M9), __LIG(M10),         \
               __LIG(M11), __LIG(), __LIG(), __LIG(), __LIG(), __LIG(),        \
               __LIG(), __LIG(), __LIG(), __LIG(), __LIG(), __LIG(), __LIG(),  \
               __LIG(), __LIG(), __LIG(), __LIG(), __LIG(), __LIG(), __LIG(),  \
               __LIG(), __LIG()>                                               \
        getListItemFuncTuple;                                                  \
    std::tuple<__OBJSIZE(M1), __OBJSIZE(M2), __OBJSIZE(M3), __OBJSIZE(M4),     \
               __OBJSIZE(M5), __OBJSIZE(M6), __OBJSIZE(M7), __OBJSIZE(M8),     \
               __OBJSIZE(M9), __OBJSIZE(M10), __OBJSIZE(M11), __OBJSIZE(),     \
               __OBJSIZE(), __OBJSIZE(), __OBJSIZE(), __OBJSIZE(),             \
               __OBJSIZE(), __OBJSIZE(), __OBJSIZE(), __OBJSIZE(),             \
               __OBJSIZE(), __OBJSIZE(), __OBJSIZE(), __OBJSIZE(),             \
               __OBJSIZE(), __OBJSIZE(), __OBJSIZE(), __OBJSIZE(),             \
               __OBJSIZE(), __OBJSIZE(), __OBJSIZE(), __OBJSIZE()>             \
        getContainerSizeFuncTuple;                                             \
    std::tuple<__MI(M1), __MI(M2), __MI(M3), __MI(M4), __MI(M5), __MI(M6),     \
               __MI(M7), __MI(M8), __MI(M9), __MI(M10), __MI(M11), __MI(),     \
               __MI(), __MI(), __MI(), __MI(), __MI(), __MI(), __MI(), __MI(), \
               __MI(), __MI(), __MI(), __MI(), __MI(), __MI(), __MI(), __MI(), \
               __MI(), __MI(), __MI(), __MI()>                                 \
        createMapItemFuncTuple;                                                \
    std::tuple<__MIG(M1), __MIG(M2), __MIG(M3), __MIG(M4), __MIG(M5),          \
               __MIG(M6), __MIG(M7), __MIG(M8), __MIG(M9), __MIG(M10),         \
               __MIG(M11), __MIG(), __MIG(), __MIG(), __MIG(), __MIG(),        \
               __MIG(), __MIG(), __MIG(), __MIG(), __MIG(), __MIG(), __MIG(),  \
               __MIG(), __MIG(), __MIG(), __MIG(), __MIG(), __MIG(), __MIG(),  \
               __MIG(), __MIG()>                                               \
        getMapItemsFuncTuple;                                                  \
    std::tuple<__LIA(M1), __LIA(M2), __LIA(M3), __LIA(M4), __LIA(M5),          \
               __LIA(M6), __LIA(M7), __LIA(M8), __LIA(M9), __LIA(M10),         \
               __LIA(M11), __LIA(), __LIA(), __LIA(), __LIA(), __LIA(),        \
               __LIA(), __LIA(), __LIA(), __LIA(), __LIA(), __LIA(), __LIA(),  \
               __LIA(), __LIA(), __LIA(), __LIA(), __LIA(), __LIA(), __LIA(),  \
               __LIA(), __LIA()>                                               \
        addListItemFuncTuple;                                                  \
    std::tuple<__MIA(M1), __MIA(M2), __MIA(M3), __MIA(M4), __MIA(M5),          \
               __MIA(M6), __MIA(M7), __MIA(M8), __MIA(M9), __MIA(M10),         \
               __MIA(M11), __MIA(), __MIA(), __MIA(), __MIA(), __MIA(),        \
               __MIA(), __MIA(), __MIA(), __MIA(), __MIA(), __MIA(), __MIA(),  \
               __MIA(), __MIA(), __MIA(), __MIA(), __MIA(), __MIA(), __MIA(),  \
               __MIA(), __MIA()>                                               \
        addMapItemFuncTuple;

#define DECLARE_INIT_TUPLE_12(M1, M2, M3, M4, M5, M6, M7, M8, M9, M10, M11,    \
                              M12)                                             \
    std::tuple<__S(M1), __S(M2), __S(M3), __S(M4), __S(M5), __S(M6), __S(M7),  \
               __S(M8), __S(M9), __S(M10), __S(M11), __S(M12), __D(), __D(),   \
               __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(),  \
               __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D()>  \
        setFuncTuple;                                                          \
    std::tuple<__G(M1), __G(M2), __G(M3), __G(M4), __G(M5), __G(M6), __G(M7),  \
               __G(M8), __G(M9), __G(M10), __G(M11), __G(M12), __D(), __D(),   \
               __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(),  \
               __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D()>  \
        getFuncTuple;                                                          \
    std::tuple<__C(M1), __C(M2), __C(M3), __C(M4), __C(M5), __C(M6), __C(M7),  \
               __C(M8), __C(M9), __C(M10), __C(M11), __C(M12), __D(), __D(),   \
               __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(),  \
               __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D()>  \
        createFuncTuple;                                                       \
    std::tuple<__L(M1), __L(M2), __L(M3), __L(M4), __L(M5), __L(M6), __L(M7),  \
               __L(M8), __L(M9), __L(M10), __L(M11), __L(M12), __LD(), __LD(), \
               __LD(), __LD(), __LD(), __LD(), __LD(), __LD(), __LD(), __LD(), \
               __LD(), __LD(), __LD(), __LD(), __LD(), __LD(), __LD(), __LD(), \
               __LD(), __LD()>                                                 \
        createListItemFuncTuple;                                               \
    std::tuple<__LIG(M1), __LIG(M2), __LIG(M3), __LIG(M4), __LIG(M5),          \
               __LIG(M6), __LIG(M7), __LIG(M8), __LIG(M9), __LIG(M10),         \
               __LIG(M11), __LIG(M12), __LIG(), __LIG(), __LIG(), __LIG(),     \
               __LIG(), __LIG(), __LIG(), __LIG(), __LIG(), __LIG(), __LIG(),  \
               __LIG(), __LIG(), __LIG(), __LIG(), __LIG(), __LIG(), __LIG(),  \
               __LIG(), __LIG()>                                               \
        getListItemFuncTuple;                                                  \
    std::tuple<__OBJSIZE(M1), __OBJSIZE(M2), __OBJSIZE(M3), __OBJSIZE(M4),     \
               __OBJSIZE(M5), __OBJSIZE(M6), __OBJSIZE(M7), __OBJSIZE(M8),     \
               __OBJSIZE(M9), __OBJSIZE(M10), __OBJSIZE(M11), __OBJSIZE(M12),  \
               __OBJSIZE(), __OBJSIZE(), __OBJSIZE(), __OBJSIZE(),             \
               __OBJSIZE(), __OBJSIZE(), __OBJSIZE(), __OBJSIZE(),             \
               __OBJSIZE(), __OBJSIZE(), __OBJSIZE(), __OBJSIZE(),             \
               __OBJSIZE(), __OBJSIZE(), __OBJSIZE(), __OBJSIZE(),             \
               __OBJSIZE(), __OBJSIZE(), __OBJSIZE(), __OBJSIZE()>             \
        getContainerSizeFuncTuple;                                             \
    std::tuple<__MI(M1), __MI(M2), __MI(M3), __MI(M4), __MI(M5), __MI(M6),     \
               __MI(M7), __MI(M8), __MI(M9), __MI(M10), __MI(M11), __MI(M12),  \
               __MI(), __MI(), __MI(), __MI(), __MI(), __MI(), __MI(), __MI(), \
               __MI(), __MI(), __MI(), __MI(), __MI(), __MI(), __MI(), __MI(), \
               __MI(), __MI(), __MI(), __MI()>                                 \
        createMapItemFuncTuple;                                                \
    std::tuple<__MIG(M1), __MIG(M2), __MIG(M3), __MIG(M4), __MIG(M5),          \
               __MIG(M6), __MIG(M7), __MIG(M8), __MIG(M9), __MIG(M10),         \
               __MIG(M11), __MIG(M12), __MIG(), __MIG(), __MIG(), __MIG(),     \
               __MIG(), __MIG(), __MIG(), __MIG(), __MIG(), __MIG(), __MIG(),  \
               __MIG(), __MIG(), __MIG(), __MIG(), __MIG(), __MIG(), __MIG(),  \
               __MIG(), __MIG()>                                               \
        getMapItemsFuncTuple;                                                  \
    std::tuple<__LIA(M1), __LIA(M2), __LIA(M3), __LIA(M4), __LIA(M5),          \
               __LIA(M6), __LIA(M7), __LIA(M8), __LIA(M9), __LIA(M10),         \
               __LIA(M11), __LIA(M12), __LIA(), __LIA(), __LIA(), __LIA(),     \
               __LIA(), __LIA(), __LIA(), __LIA(), __LIA(), __LIA(), __LIA(),  \
               __LIA(), __LIA(), __LIA(), __LIA(), __LIA(), __LIA(), __LIA(),  \
               __LIA(), __LIA()>                                               \
        addListItemFuncTuple;                                                  \
    std::tuple<__MIA(M1), __MIA(M2), __MIA(M3), __MIA(M4), __MIA(M5),          \
               __MIA(M6), __MIA(M7), __MIA(M8), __MIA(M9), __MIA(M10),         \
               __MIA(M11), __MIA(M12), __MIA(), __MIA(), __MIA(), __MIA(),     \
               __MIA(), __MIA(), __MIA(), __MIA(), __MIA(), __MIA(), __MIA(),  \
               __MIA(), __MIA(), __MIA(), __MIA(), __MIA(), __MIA(), __MIA(),  \
               __MIA(), __MIA()>                                               \
        addMapItemFuncTuple;

#define DECLARE_INIT_TUPLE_13(M1, M2, M3, M4, M5, M6, M7, M8, M9, M10, M11,    \
                              M12, M13)                                        \
    std::tuple<__S(M1), __S(M2), __S(M3), __S(M4), __S(M5), __S(M6), __S(M7),  \
               __S(M8), __S(M9), __S(M10), __S(M11), __S(M12), __S(M13),       \
               __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(),  \
               __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(),  \
               __D()>                                                          \
        setFuncTuple;                                                          \
    std::tuple<__G(M1), __G(M2), __G(M3), __G(M4), __G(M5), __G(M6), __G(M7),  \
               __G(M8), __G(M9), __G(M10), __G(M11), __G(M12), __G(M13),       \
               __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(),  \
               __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(),  \
               __D(), __D()>                                                   \
        getFuncTuple;                                                          \
    std::tuple<__C(M1), __C(M2), __C(M3), __C(M4), __C(M5), __C(M6), __C(M7),  \
               __C(M8), __C(M9), __C(M10), __C(M11), __C(M12), __C(M13),       \
               __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(),  \
               __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(),  \
               __D()>                                                          \
        createFuncTuple;                                                       \
    std::tuple<__L(M1), __L(M2), __L(M3), __L(M4), __L(M5), __L(M6), __L(M7),  \
               __L(M8), __L(M9), __L(M10), __L(M11), __L(M12), __L(M13),       \
               __LD(), __LD(), __LD(), __LD(), __LD(), __LD(), __LD(), __LD(), \
               __LD(), __LD(), __LD(), __LD(), __LD(), __LD(), __LD(), __LD(), \
               __LD(), __LD(), __LD()>                                         \
        createListItemFuncTuple;                                               \
    std::tuple<__LIG(M1), __LIG(M2), __LIG(M3), __LIG(M4), __LIG(M5),          \
               __LIG(M6), __LIG(M7), __LIG(M8), __LIG(M9), __LIG(M10),         \
               __LIG(M11), __LIG(M12), __LIG(M13), __LIG(), __LIG(), __LIG(),  \
               __LIG(), __LIG(), __LIG(), __LIG(), __LIG(), __LIG(), __LIG(),  \
               __LIG(), __LIG(), __LIG(), __LIG(), __LIG(), __LIG(), __LIG(),  \
               __LIG(), __LIG()>                                               \
        getListItemFuncTuple;                                                  \
    std::tuple<__OBJSIZE(M1), __OBJSIZE(M2), __OBJSIZE(M3), __OBJSIZE(M4),     \
               __OBJSIZE(M5), __OBJSIZE(M6), __OBJSIZE(M7), __OBJSIZE(M8),     \
               __OBJSIZE(M9), __OBJSIZE(M10), __OBJSIZE(M11), __OBJSIZE(M12),  \
               __OBJSIZE(M13), __OBJSIZE(), __OBJSIZE(), __OBJSIZE(),          \
               __OBJSIZE(), __OBJSIZE(), __OBJSIZE(), __OBJSIZE(),             \
               __OBJSIZE(), __OBJSIZE(), __OBJSIZE(), __OBJSIZE(),             \
               __OBJSIZE(), __OBJSIZE(), __OBJSIZE(), __OBJSIZE(),             \
               __OBJSIZE(), __OBJSIZE(), __OBJSIZE(), __OBJSIZE()>             \
        getContainerSizeFuncTuple;                                             \
    std::tuple<__MI(M1), __MI(M2), __MI(M3), __MI(M4), __MI(M5), __MI(M6),     \
               __MI(M7), __MI(M8), __MI(M9), __MI(M10), __MI(M11), __MI(M12),  \
               __MI(M13), __MI(), __MI(), __MI(), __MI(), __MI(), __MI(),      \
               __MI(), __MI(), __MI(), __MI(), __MI(), __MI(), __MI(), __MI(), \
               __MI(), __MI(), __MI(), __MI(), __MI()>                         \
        createMapItemFuncTuple;                                                \
    std::tuple<__MIG(M1), __MIG(M2), __MIG(M3), __MIG(M4), __MIG(M5),          \
               __MIG(M6), __MIG(M7), __MIG(M8), __MIG(M9), __MIG(M10),         \
               __MIG(M11), __MIG(M12), __MIG(M13), __MIG(), __MIG(), __MIG(),  \
               __MIG(), __MIG(), __MIG(), __MIG(), __MIG(), __MIG(), __MIG(),  \
               __MIG(), __MIG(), __MIG(), __MIG(), __MIG(), __MIG(), __MIG(),  \
               __MIG(), __MIG()>                                               \
        getMapItemsFuncTuple;                                                  \
    std::tuple<__LIA(M1), __LIA(M2), __LIA(M3), __LIA(M4), __LIA(M5),          \
               __LIA(M6), __LIA(M7), __LIA(M8), __LIA(M9), __LIA(M10),         \
               __LIA(M11), __LIA(M12), __LIA(M13), __LIA(), __LIA(), __LIA(),  \
               __LIA(), __LIA(), __LIA(), __LIA(), __LIA(), __LIA(), __LIA(),  \
               __LIA(), __LIA(), __LIA(), __LIA(), __LIA(), __LIA(), __LIA(),  \
               __LIA(), __LIA()>                                               \
        addListItemFuncTuple;                                                  \
    std::tuple<__MIA(M1), __MIA(M2), __MIA(M3), __MIA(M4), __MIA(M5),          \
               __MIA(M6), __MIA(M7), __MIA(M8), __MIA(M9), __MIA(M10),         \
               __MIA(M11), __MIA(M12), __MIA(M13), __MIA(), __MIA(), __MIA(),  \
               __MIA(), __MIA(), __MIA(), __MIA(), __MIA(), __MIA(), __MIA(),  \
               __MIA(), __MIA(), __MIA(), __MIA(), __MIA(), __MIA(), __MIA(),  \
               __MIA(), __MIA()>                                               \
        addMapItemFuncTuple;

#define DECLARE_INIT_TUPLE_14(M1, M2, M3, M4, M5, M6, M7, M8, M9, M10, M11,    \
                              M12, M13, M14)                                   \
    std::tuple<__S(M1), __S(M2), __S(M3), __S(M4), __S(M5), __S(M6), __S(M7),  \
               __S(M8), __S(M9), __S(M10), __S(M11), __S(M12), __S(M13),       \
               __S(M14), __D(), __D(), __D(), __D(), __D(), __D(), __D(),      \
               __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(),  \
               __D(), __D()>                                                   \
        setFuncTuple;                                                          \
    std::tuple<__G(M1), __G(M2), __G(M3), __G(M4), __G(M5), __G(M6), __G(M7),  \
               __G(M8), __G(M9), __G(M10), __G(M11), __G(M12), __G(M13),       \
               __G(M14), __D(), __D(), __D(), __D(), __D(), __D(), __D(),      \
               __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(),  \
               __D(), __D(), __D()>                                            \
        getFuncTuple;                                                          \
    std::tuple<__C(M1), __C(M2), __C(M3), __C(M4), __C(M5), __C(M6), __C(M7),  \
               __C(M8), __C(M9), __C(M10), __C(M11), __C(M12), __C(M13),       \
               __C(M14), __D(), __D(), __D(), __D(), __D(), __D(), __D(),      \
               __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(),  \
               __D(), __D()>                                                   \
        createFuncTuple;                                                       \
    std::tuple<__L(M1), __L(M2), __L(M3), __L(M4), __L(M5), __L(M6), __L(M7),  \
               __L(M8), __L(M9), __L(M10), __L(M11), __L(M12), __L(M13),       \
               __L(M14), __LD(), __LD(), __LD(), __LD(), __LD(), __LD(),       \
               __LD(), __LD(), __LD(), __LD(), __LD(), __LD(), __LD(), __LD(), \
               __LD(), __LD(), __LD(), __LD()>                                 \
        createListItemFuncTuple;                                               \
    std::tuple<__LIG(M1), __LIG(M2), __LIG(M3), __LIG(M4), __LIG(M5),          \
               __LIG(M6), __LIG(M7), __LIG(M8), __LIG(M9), __LIG(M10),         \
               __LIG(M11), __LIG(M12), __LIG(M13), __LIG(M14), __LIG(),        \
               __LIG(), __LIG(), __LIG(), __LIG(), __LIG(), __LIG(), __LIG(),  \
               __LIG(), __LIG(), __LIG(), __LIG(), __LIG(), __LIG(), __LIG(),  \
               __LIG(), __LIG(), __LIG()>                                      \
        getListItemFuncTuple;                                                  \
    std::tuple<__OBJSIZE(M1), __OBJSIZE(M2), __OBJSIZE(M3), __OBJSIZE(M4),     \
               __OBJSIZE(M5), __OBJSIZE(M6), __OBJSIZE(M7), __OBJSIZE(M8),     \
               __OBJSIZE(M9), __OBJSIZE(M10), __OBJSIZE(M11), __OBJSIZE(M12),  \
               __OBJSIZE(M13), __OBJSIZE(M14), __OBJSIZE(), __OBJSIZE(),       \
               __OBJSIZE(), __OBJSIZE(), __OBJSIZE(), __OBJSIZE(),             \
               __OBJSIZE(), __OBJSIZE(), __OBJSIZE(), __OBJSIZE(),             \
               __OBJSIZE(), __OBJSIZE(), __OBJSIZE(), __OBJSIZE(),             \
               __OBJSIZE(), __OBJSIZE(), __OBJSIZE(), __OBJSIZE()>             \
        getContainerSizeFuncTuple;                                             \
    std::tuple<__MI(M1), __MI(M2), __MI(M3), __MI(M4), __MI(M5), __MI(M6),     \
               __MI(M7), __MI(M8), __MI(M9), __MI(M10), __MI(M11), __MI(M12),  \
               __MI(M13), __MI(M14), __MI(), __MI(), __MI(), __MI(), __MI(),   \
               __MI(), __MI(), __MI(), __MI(), __MI(), __MI(), __MI(), __MI(), \
               __MI(), __MI(), __MI(), __MI(), __MI()>                         \
        createMapItemFuncTuple;                                                \
    std::tuple<__MIG(M1), __MIG(M2), __MIG(M3), __MIG(M4), __MIG(M5),          \
               __MIG(M6), __MIG(M7), __MIG(M8), __MIG(M9), __MIG(M10),         \
               __MIG(M11), __MIG(M12), __MIG(M13), __MIG(M14), __MIG(),        \
               __MIG(), __MIG(), __MIG(), __MIG(), __MIG(), __MIG(), __MIG(),  \
               __MIG(), __MIG(), __MIG(), __MIG(), __MIG(), __MIG(), __MIG(),  \
               __MIG(), __MIG(), __MIG()>                                      \
        getMapItemsFuncTuple;                                                  \
    std::tuple<__LIA(M1), __LIA(M2), __LIA(M3), __LIA(M4), __LIA(M5),          \
               __LIA(M6), __LIA(M7), __LIA(M8), __LIA(M9), __LIA(M10),         \
               __LIA(M11), __LIA(M12), __LIA(M13), __LIA(M14), __LIA(),        \
               __LIA(), __LIA(), __LIA(), __LIA(), __LIA(), __LIA(), __LIA(),  \
               __LIA(), __LIA(), __LIA(), __LIA(), __LIA(), __LIA(), __LIA(),  \
               __LIA(), __LIA(), __LIA()>                                      \
        addListItemFuncTuple;                                                  \
    std::tuple<__MIA(M1), __MIA(M2), __MIA(M3), __MIA(M4), __MIA(M5),          \
               __MIA(M6), __MIA(M7), __MIA(M8), __MIA(M9), __MIA(M10),         \
               __MIA(M11), __MIA(M12), __MIA(M13), __MIA(M14), __MIA(),        \
               __MIA(), __MIA(), __MIA(), __MIA(), __MIA(), __MIA(), __MIA(),  \
               __MIA(), __MIA(), __MIA(), __MIA(), __MIA(), __MIA(), __MIA(),  \
               __MIA(), __MIA(), __MIA()>                                      \
        addMapItemFuncTuple;

#define DECLARE_INIT_TUPLE_15(M1, M2, M3, M4, M5, M6, M7, M8, M9, M10, M11,    \
                              M12, M13, M14, M15)                              \
    std::tuple<__S(M1), __S(M2), __S(M3), __S(M4), __S(M5), __S(M6), __S(M7),  \
               __S(M8), __S(M9), __S(M10), __S(M11), __S(M12), __S(M13),       \
               __S(M14), __S(M15), __D(), __D(), __D(), __D(), __D(), __D(),   \
               __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(),  \
               __D(), __D()>                                                   \
        setFuncTuple;                                                          \
    std::tuple<__G(M1), __G(M2), __G(M3), __G(M4), __G(M5), __G(M6), __G(M7),  \
               __G(M8), __G(M9), __G(M10), __G(M11), __G(M12), __G(M13),       \
               __G(M14), __G(M15), __D(), __D(), __D(), __D(), __D(), __D(),   \
               __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(),  \
               __D(), __D()>                                                   \
        getFuncTuple;                                                          \
    std::tuple<__C(M1), __C(M2), __C(M3), __C(M4), __C(M5), __C(M6), __C(M7),  \
               __C(M8), __C(M9), __C(M10), __C(M11), __C(M12), __C(M13),       \
               __C(M14), __C(M15), __D(), __D(), __D(), __D(), __D(), __D(),   \
               __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(),  \
               __D(), __D()>                                                   \
        createFuncTuple;                                                       \
    std::tuple<__L(M1), __L(M2), __L(M3), __L(M4), __L(M5), __L(M6), __L(M7),  \
               __L(M8), __L(M9), __L(M10), __L(M11), __L(M12), __L(M13),       \
               __L(M14), __L(M15), __LD(), __LD(), __LD(), __LD(), __LD(),     \
               __LD(), __LD(), __LD(), __LD(), __LD(), __LD(), __LD(), __LD(), \
               __LD(), __LD(), __LD(), __LD()>                                 \
        createListItemFuncTuple;                                               \
    std::tuple<__LIG(M1), __LIG(M2), __LIG(M3), __LIG(M4), __LIG(M5),          \
               __LIG(M6), __LIG(M7), __LIG(M8), __LIG(M9), __LIG(M10),         \
               __LIG(M11), __LIG(M12), __LIG(M13), __LIG(M14), __LIG(M15),     \
               __LIG(), __LIG(), __LIG(), __LIG(), __LIG(), __LIG(), __LIG(),  \
               __LIG(), __LIG(), __LIG(), __LIG(), __LIG(), __LIG(), __LIG(),  \
               __LIG(), __LIG(), __LIG()>                                      \
        getListItemFuncTuple;                                                  \
    std::tuple<__OBJSIZE(M1), __OBJSIZE(M2), __OBJSIZE(M3), __OBJSIZE(M4),     \
               __OBJSIZE(M5), __OBJSIZE(M6), __OBJSIZE(M7), __OBJSIZE(M8),     \
               __OBJSIZE(M9), __OBJSIZE(M10), __OBJSIZE(M11), __OBJSIZE(M12),  \
               __OBJSIZE(M13), __OBJSIZE(M14), __OBJSIZE(M15), __OBJSIZE(),    \
               __OBJSIZE(), __OBJSIZE(), __OBJSIZE(), __OBJSIZE(),             \
               __OBJSIZE(), __OBJSIZE(), __OBJSIZE(), __OBJSIZE(),             \
               __OBJSIZE(), __OBJSIZE(), __OBJSIZE(), __OBJSIZE(),             \
               __OBJSIZE(), __OBJSIZE(), __OBJSIZE(), __OBJSIZE()>             \
        getContainerSizeFuncTuple;                                             \
    std::tuple<__MI(M1), __MI(M2), __MI(M3), __MI(M4), __MI(M5), __MI(M6),     \
               __MI(M7), __MI(M8), __MI(M9), __MI(M10), __MI(M11), __MI(M12),  \
               __MI(M13), __MI(M14), __MI(M15), __MI(), __MI(), __MI(),        \
               __MI(), __MI(), __MI(), __MI(), __MI(), __MI(), __MI(), __MI(), \
               __MI(), __MI(), __MI(), __MI(), __MI(), __MI()>                 \
        createMapItemFuncTuple;                                                \
    std::tuple<__MIG(M1), __MIG(M2), __MIG(M3), __MIG(M4), __MIG(M5),          \
               __MIG(M6), __MIG(M7), __MIG(M8), __MIG(M9), __MIG(M10),         \
               __MIG(M11), __MIG(M12), __MIG(M13), __MIG(M14), __MIG(M15),     \
               __MIG(), __MIG(), __MIG(), __MIG(), __MIG(), __MIG(), __MIG(),  \
               __MIG(), __MIG(), __MIG(), __MIG(), __MIG(), __MIG(), __MIG(),  \
               __MIG(), __MIG(), __MIG()>                                      \
        getMapItemsFuncTuple;                                                  \
    std::tuple<__LIA(M1), __LIA(M2), __LIA(M3), __LIA(M4), __LIA(M5),          \
               __LIA(M6), __LIA(M7), __LIA(M8), __LIA(M9), __LIA(M10),         \
               __LIA(M11), __LIA(M12), __LIA(M13), __LIA(M14), __LIA(M15),     \
               __LIA(), __LIA(), __LIA(), __LIA(), __LIA(), __LIA(), __LIA(),  \
               __LIA(), __LIA(), __LIA(), __LIA(), __LIA(), __LIA(), __LIA(),  \
               __LIA(), __LIA(), __LIA()>                                      \
        addListItemFuncTuple;                                                  \
    std::tuple<__MIA(M1), __MIA(M2), __MIA(M3), __MIA(M4), __MIA(M5),          \
               __MIA(M6), __MIA(M7), __MIA(M8), __MIA(M9), __MIA(M10),         \
               __MIA(M11), __MIA(M12), __MIA(M13), __MIA(M14), __MIA(M15),     \
               __MIA(), __MIA(), __MIA(), __MIA(), __MIA(), __MIA(), __MIA(),  \
               __MIA(), __MIA(), __MIA(), __MIA(), __MIA(), __MIA(), __MIA(),  \
               __MIA(), __MIA(), __MIA()>                                      \
        addMapItemFuncTuple;

#define DECLARE_INIT_TUPLE_16(M1, M2, M3, M4, M5, M6, M7, M8, M9, M10, M11,    \
                              M12, M13, M14, M15, M16)                         \
    std::tuple<__S(M1), __S(M2), __S(M3), __S(M4), __S(M5), __S(M6), __S(M7),  \
               __S(M8), __S(M9), __S(M10), __S(M11), __S(M12), __S(M13),       \
               __S(M14), __S(M15), __S(M16), __D(), __D(), __D(), __D(),       \
               __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(),  \
               __D(), __D(), __D()>                                            \
        setFuncTuple;                                                          \
    std::tuple<__G(M1), __G(M2), __G(M3), __G(M4), __G(M5), __G(M6), __G(M7),  \
               __G(M8), __G(M9), __G(M10), __G(M11), __G(M12), __G(M13),       \
               __G(M14), __G(M15), __G(M16), __D(), __D(), __D(), __D(),       \
               __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(),  \
               __D(), __D(), __D()>                                            \
        getFuncTuple;                                                          \
    std::tuple<__C(M1), __C(M2), __C(M3), __C(M4), __C(M5), __C(M6), __C(M7),  \
               __C(M8), __C(M9), __C(M10), __C(M11), __C(M12), __C(M13),       \
               __C(M14), __C(M15), __C(M16), __D(), __D(), __D(), __D(),       \
               __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(), __D(),  \
               __D(), __D(), __D()>                                            \
        createFuncTuple;                                                       \
    std::tuple<__L(M1), __L(M2), __L(M3), __L(M4), __L(M5), __L(M6), __L(M7),  \
               __L(M8), __L(M9), __L(M10), __L(M11), __L(M12), __L(M13),       \
               __L(M14), __L(M15), __L(M16), __LD(), __LD(), __LD(), __LD(),   \
               __LD(), __LD(), __LD(), __LD(), __LD(), __LD(), __LD(), __LD(), \
               __LD(), __LD(), __LD(), __LD()>                                 \
        createListItemFuncTuple;                                               \
    std::tuple<__LIG(M1), __LIG(M2), __LIG(M3), __LIG(M4), __LIG(M5),          \
               __LIG(M6), __LIG(M7), __LIG(M8), __LIG(M9), __LIG(M10),         \
               __LIG(M11), __LIG(M12), __LIG(M13), __LIG(M14), __LIG(M15),     \
               __LIG(M16), __LIG(), __LIG(), __LIG(), __LIG(), __LIG(),        \
               __LIG(), __LIG(), __LIG(), __LIG(), __LIG(), __LIG(), __LIG(),  \
               __LIG(), __LIG(), __LIG(), __LIG()>                             \
        getListItemFuncTuple;                                                  \
    std::tuple<__OBJSIZE(M1), __OBJSIZE(M2), __OBJSIZE(M3), __OBJSIZE(M4),     \
               __OBJSIZE(M5), __OBJSIZE(M6), __OBJSIZE(M7), __OBJSIZE(M8),     \
               __OBJSIZE(M9), __OBJSIZE(M10), __OBJSIZE(M11), __OBJSIZE(M12),  \
               __OBJSIZE(M13), __OBJSIZE(M14), __OBJSIZE(M15), __OBJSIZE(M16), \
               __OBJSIZE(), __OBJSIZE(), __OBJSIZE(), __OBJSIZE(),             \
               __OBJSIZE(), __OBJSIZE(), __OBJSIZE(), __OBJSIZE(),             \
               __OBJSIZE(), __OBJSIZE(), __OBJSIZE(), __OBJSIZE(),             \
               __OBJSIZE(), __OBJSIZE(), __OBJSIZE(), __OBJSIZE()>             \
        getContainerSizeFuncTuple;                                             \
    std::tuple<__MI(M1), __MI(M2), __MI(M3), __MI(M4), __MI(M5), __MI(M6),     \
               __MI(M7), __MI(M8), __MI(M9), __MI(M10), __MI(M11), __MI(M12),  \
               __MI(M13), __MI(M14), __MI(M15), __MI(M16), __MI(), __MI(),     \
               __MI(), __MI(), __MI(), __MI(), __MI(), __MI(), __MI(), __MI(), \
               __MI(), __MI(), __MI(), __MI(), __MI(), __MI()>                 \
        createMapItemFuncTuple;                                                \
    std::tuple<__MIG(M1), __MIG(M2), __MIG(M3), __MIG(M4), __MIG(M5),          \
               __MIG(M6), __MIG(M7), __MIG(M8), __MIG(M9), __MIG(M10),         \
               __MIG(M11), __MIG(M12), __MIG(M13), __MIG(M14), __MIG(M15),     \
               __MIG(M16), __MIG(), __MIG(), __MIG(), __MIG(), __MIG(),        \
               __MIG(), __MIG(), __MIG(), __MIG(), __MIG(), __MIG(), __MIG(),  \
               __MIG(), __MIG(), __MIG(), __MIG()>                             \
        getMapItemsFuncTuple;                                                  \
    std::tuple<__LIA(M1), __LIA(M2), __LIA(M3), __LIA(M4), __LIA(M5),          \
               __LIA(M6), __LIA(M7), __LIA(M8), __LIA(M9), __LIA(M10),         \
               __LIA(M11), __LIA(M12), __LIA(M13), __LIA(M14), __LIA(M15),     \
               __LIA(M16), __LIA(), __LIA(), __LIA(), __LIA(), __LIA(),        \
               __LIA(), __LIA(), __LIA(), __LIA(), __LIA(), __LIA(), __LIA(),  \
               __LIA(), __LIA(), __LIA(), __LIA()>                             \
        addListItemFuncTuple;                                                  \
    std::tuple<__MIA(M1), __MIA(M2), __MIA(M3), __MIA(M4), __MIA(M5),          \
               __MIA(M6), __MIA(M7), __MIA(M8), __MIA(M9), __MIA(M10),         \
               __MIA(M11), __MIA(M12), __MIA(M13), __MIA(M14), __MIA(M15),     \
               __MIA(M16), __MIA(), __MIA(), __MIA(), __MIA(), __MIA(),        \
               __MIA(), __MIA(), __MIA(), __MIA(), __MIA(), __MIA(), __MIA(),  \
               __MIA(), __MIA(), __MIA(), __MIA()>                             \
        addMapItemFuncTuple;

#define IMPLE_INIT_TUPLE_DETECT(CLASS, COUNT, ...)                             \
    IMPLE_INIT_TUPLE_DETECT_TRACE(CLASS, COUNT, __VA_ARGS__)
#define IMPLE_INIT_TUPLE_DETECT_TRACE(CLASS, COUNT, ...)                       \
    IMPLE_INIT_TUPLE_DETECT_TRACE1(CLASS, COUNT, __VA_ARGS__)
#define IMPLE_INIT_TUPLE_DETECT_TRACE1(CLASS, COUNT, ...)                      \
    IMPLE_INIT_TUPLE_##COUNT(CLASS, __VA_ARGS__)

#define IMPLE_INIT_TUPLE_1(CLASS, M1)                                          \
    std::function<decltype(M1)()> getobj =                                     \
        std::bind(&CLASS::__ReflectGet##M1, this);                             \
    std::function<void()> createobj =                                          \
        std::bind(&CLASS::__ReflectCreate##M1, this);                          \
    std::function<Object()> genItemObj =                                       \
        std::bind(&CLASS::__ReflectCreateListMember##M1, this);                \
    std::function<Object(int)> getItemObj = std::bind(                         \
        &CLASS::__ReflectGetListItem##M1, this, std::placeholders::_1);        \
    std::function<int()> getContainerSize =                                    \
        std::bind(&CLASS::__ReflectGetContainerSize##M1, this);                \
    std::function<Pair<Object, Object>()> createMapObj =               \
        std::bind(&CLASS::__ReflectCreateMapMember##M1, this);                 \
    std::function<ArrayList<Pair<Object, Object>>()> getMapItems =     \
        std::bind(&CLASS::__ReflectGetMapItems##M1, this);                     \
    std::function<void(Object)> addListItem = std::bind(                       \
        &CLASS::__ReflectAddListItem##M1, this, std::placeholders::_1);        \
    std::function<void(Object, Object)> addMapItem =                           \
        std::bind(&CLASS::__ReflectAddMapItem##M1, this,                       \
                  std::placeholders::_1, std::placeholders::_2);               \
    getFuncTuple = std::make_tuple(                                            \
        getobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj,    \
        dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj,  \
        dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj,  \
        dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj,  \
        dummyobj, dummyobj, dummyobj, dummyobj);                               \
    createFuncTuple = std::make_tuple(                                         \
        createobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, \
        dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj,  \
        dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj,  \
        dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj,  \
        dummyobj, dummyobj, dummyobj, dummyobj);                               \
    createListItemFuncTuple = std::make_tuple(                                 \
        genItemObj, dummycreateobj, dummycreateobj, dummycreateobj,            \
        dummycreateobj, dummycreateobj, dummycreateobj, dummycreateobj,        \
        dummycreateobj, dummycreateobj, dummycreateobj, dummycreateobj,        \
        dummycreateobj, dummycreateobj, dummycreateobj, dummycreateobj,        \
        dummycreateobj, dummycreateobj, dummycreateobj, dummycreateobj,        \
        dummycreateobj, dummycreateobj, dummycreateobj, dummycreateobj,        \
        dummycreateobj, dummycreateobj, dummycreateobj, dummycreateobj,        \
        dummycreateobj, dummycreateobj, dummycreateobj, dummycreateobj);       \
    getListItemFuncTuple = std::make_tuple(                                    \
        getItemObj, dummyligobj, dummyligobj, dummyligobj, dummyligobj,        \
        dummyligobj, dummyligobj, dummyligobj, dummyligobj, dummyligobj,       \
        dummyligobj, dummyligobj, dummyligobj, dummyligobj, dummyligobj,       \
        dummyligobj, dummyligobj, dummyligobj, dummyligobj, dummyligobj,       \
        dummyligobj, dummyligobj, dummyligobj, dummyligobj, dummyligobj,       \
        dummyligobj, dummyligobj, dummyligobj, dummyligobj, dummyligobj,       \
        dummyligobj, dummyligobj);                                             \
    getContainerSizeFuncTuple = std::make_tuple(                               \
        getContainerSize, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj,    \
        dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj,  \
        dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj,  \
        dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj,  \
        dummyobj, dummyobj, dummyobj, dummyobj, dummyobj);                     \
    createMapItemFuncTuple = std::make_tuple(                                  \
        createMapObj, dummycreateMapItem, dummycreateMapItem,                  \
        dummycreateMapItem, dummycreateMapItem, dummycreateMapItem,            \
        dummycreateMapItem, dummycreateMapItem, dummycreateMapItem,            \
        dummycreateMapItem, dummycreateMapItem, dummycreateMapItem,            \
        dummycreateMapItem, dummycreateMapItem, dummycreateMapItem,            \
        dummycreateMapItem, dummycreateMapItem, dummycreateMapItem,            \
        dummycreateMapItem, dummycreateMapItem, dummycreateMapItem,            \
        dummycreateMapItem, dummycreateMapItem, dummycreateMapItem,            \
        dummycreateMapItem, dummycreateMapItem, dummycreateMapItem,            \
        dummycreateMapItem, dummycreateMapItem, dummycreateMapItem,            \
        dummycreateMapItem, dummycreateMapItem);                               \
    getMapItemsFuncTuple =                                                     \
        std::make_tuple(getMapItems, dummygetMapItems, dummygetMapItems,       \
                        dummygetMapItems, dummygetMapItems, dummygetMapItems,  \
                        dummygetMapItems, dummygetMapItems, dummygetMapItems,  \
                        dummygetMapItems, dummygetMapItems, dummygetMapItems,  \
                        dummygetMapItems, dummygetMapItems, dummygetMapItems,  \
                        dummygetMapItems, dummygetMapItems, dummygetMapItems,  \
                        dummygetMapItems, dummygetMapItems, dummygetMapItems,  \
                        dummygetMapItems, dummygetMapItems, dummygetMapItems,  \
                        dummygetMapItems, dummygetMapItems, dummygetMapItems,  \
                        dummygetMapItems, dummygetMapItems, dummygetMapItems,  \
                        dummygetMapItems, dummygetMapItems);                   \
    addListItemFuncTuple =                                                     \
        std::make_tuple(addListItem, dummyAddListItem, dummyAddListItem,       \
                        dummyAddListItem, dummyAddListItem, dummyAddListItem,  \
                        dummyAddListItem, dummyAddListItem, dummyAddListItem,  \
                        dummyAddListItem, dummyAddListItem, dummyAddListItem,  \
                        dummyAddListItem, dummyAddListItem, dummyAddListItem,  \
                        dummyAddListItem, dummyAddListItem, dummyAddListItem,  \
                        dummyAddListItem, dummyAddListItem, dummyAddListItem,  \
                        dummyAddListItem, dummyAddListItem, dummyAddListItem,  \
                        dummyAddListItem, dummyAddListItem, dummyAddListItem,  \
                        dummyAddListItem, dummyAddListItem, dummyAddListItem,  \
                        dummyAddListItem, dummyAddListItem);                   \
    addMapItemFuncTuple = std::make_tuple(                                     \
        addMapItem, dummyAddMapItem, dummyAddMapItem, dummyAddMapItem,         \
        dummyAddMapItem, dummyAddMapItem, dummyAddMapItem, dummyAddMapItem,    \
        dummyAddMapItem, dummyAddMapItem, dummyAddMapItem, dummyAddMapItem,    \
        dummyAddMapItem, dummyAddMapItem, dummyAddMapItem, dummyAddMapItem,    \
        dummyAddMapItem, dummyAddMapItem, dummyAddMapItem, dummyAddMapItem,    \
        dummyAddMapItem, dummyAddMapItem, dummyAddMapItem, dummyAddMapItem,    \
        dummyAddMapItem, dummyAddMapItem, dummyAddMapItem, dummyAddMapItem,    \
        dummyAddMapItem, dummyAddMapItem, dummyAddMapItem, dummyAddMapItem);

#define IMPLE_INIT_TUPLE_2(CLASS, M1, M2)                                      \
    std::function<decltype(M1)()> getobj1 =                                    \
        std::bind(&CLASS::__ReflectGet##M1, this);                             \
    std::function<decltype(M2)()> getobj2 =                                    \
        std::bind(&CLASS::__ReflectGet##M2, this);                             \
    std::function<void()> createobj1 =                                         \
        std::bind(&CLASS::__ReflectCreate##M1, this);                          \
    std::function<void()> createobj2 =                                         \
        std::bind(&CLASS::__ReflectCreate##M2, this);                          \
    std::function<Object()> genItemObj1 =                                      \
        std::bind(&CLASS::__ReflectCreateListMember##M1, this);                \
    std::function<Object()> genItemObj2 =                                      \
        std::bind(&CLASS::__ReflectCreateListMember##M2, this);                \
    std::function<Object(int)> getItemObj1 = std::bind(                        \
        &CLASS::__ReflectGetListItem##M1, this, std::placeholders::_1);        \
    std::function<Object(int)> getItemObj2 = std::bind(                        \
        &CLASS::__ReflectGetListItem##M2, this, std::placeholders::_1);        \
    std::function<int()> getContainerSize1 =                                   \
        std::bind(&CLASS::__ReflectGetContainerSize##M1, this);                \
    std::function<int()> getContainerSize2 =                                   \
        std::bind(&CLASS::__ReflectGetContainerSize##M2, this);                \
    std::function<Pair<Object, Object>()> createMapObj1 =              \
        std::bind(&CLASS::__ReflectCreateMapMember##M1, this);                 \
    std::function<ArrayList<Pair<Object, Object>>()> getMapItems1 =    \
        std::bind(&CLASS::__ReflectGetMapItems##M1, this);                     \
    std::function<Pair<Object, Object>()> createMapObj2 =              \
        std::bind(&CLASS::__ReflectCreateMapMember##M2, this);                 \
    std::function<ArrayList<Pair<Object, Object>>()> getMapItems2 =    \
        std::bind(&CLASS::__ReflectGetMapItems##M2, this);                     \
    std::function<void(Object)> addListItem = std::bind(                       \
        &CLASS::__ReflectAddListItem##M1, this, std::placeholders::_1);        \
    std::function<void(Object, Object)> addMapItem =                           \
        std::bind(&CLASS::__ReflectAddMapItem##M1, this,                       \
                  std::placeholders::_1, std::placeholders::_2);               \
    std::function<void(Object)> addListItem2 = std::bind(                      \
        &CLASS::__ReflectAddListItem##M2, this, std::placeholders::_1);        \
    std::function<void(Object, Object)> addMapItem2 =                          \
        std::bind(&CLASS::__ReflectAddMapItem##M2, this,                       \
                  std::placeholders::_1, std::placeholders::_2);               \
    getFuncTuple = std::make_tuple(                                            \
        getobj1, getobj2, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj,    \
        dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj,  \
        dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj,  \
        dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj,  \
        dummyobj, dummyobj, dummyobj, dummyobj);                               \
    createFuncTuple = std::make_tuple(                                         \
        createobj1, createobj2, dummyobj, dummyobj, dummyobj, dummyobj,        \
        dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj,  \
        dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj,  \
        dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj,  \
        dummyobj, dummyobj, dummyobj, dummyobj, dummyobj);                     \
    createListItemFuncTuple = std::make_tuple(                                 \
        genItemObj1, genItemObj2, dummycreateobj, dummycreateobj,              \
        dummycreateobj, dummycreateobj, dummycreateobj, dummycreateobj,        \
        dummycreateobj, dummycreateobj, dummycreateobj, dummycreateobj,        \
        dummycreateobj, dummycreateobj, dummycreateobj, dummycreateobj,        \
        dummycreateobj, dummycreateobj, dummycreateobj, dummycreateobj,        \
        dummycreateobj, dummycreateobj, dummycreateobj, dummycreateobj,        \
        dummycreateobj, dummycreateobj, dummycreateobj, dummycreateobj,        \
        dummycreateobj, dummycreateobj, dummycreateobj, dummycreateobj);       \
    getListItemFuncTuple = std::make_tuple(                                    \
        getItemObj1, getItemObj2, dummyligobj, dummyligobj, dummyligobj,       \
        dummyligobj, dummyligobj, dummyligobj, dummyligobj, dummyligobj,       \
        dummyligobj, dummyligobj, dummyligobj, dummyligobj, dummyligobj,       \
        dummyligobj, dummyligobj, dummyligobj, dummyligobj, dummyligobj,       \
        dummyligobj, dummyligobj, dummyligobj, dummyligobj, dummyligobj,       \
        dummyligobj, dummyligobj, dummyligobj, dummyligobj, dummyligobj,       \
        dummyligobj, dummyligobj);                                             \
    getContainerSizeFuncTuple = std::make_tuple(                               \
        getContainerSize1, getContainerSize2, dummyobj, dummyobj, dummyobj,    \
        dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj,  \
        dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj,  \
        dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj,  \
        dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj);           \
    createMapItemFuncTuple = std::make_tuple(                                  \
        createMapObj1, createMapObj2, dummycreateMapItem, dummycreateMapItem,  \
        dummycreateMapItem, dummycreateMapItem, dummycreateMapItem,            \
        dummycreateMapItem, dummycreateMapItem, dummycreateMapItem,            \
        dummycreateMapItem, dummycreateMapItem, dummycreateMapItem,            \
        dummycreateMapItem, dummycreateMapItem, dummycreateMapItem,            \
        dummycreateMapItem, dummycreateMapItem, dummycreateMapItem,            \
        dummycreateMapItem, dummycreateMapItem, dummycreateMapItem,            \
        dummycreateMapItem, dummycreateMapItem, dummycreateMapItem,            \
        dummycreateMapItem, dummycreateMapItem, dummycreateMapItem,            \
        dummycreateMapItem, dummycreateMapItem, dummycreateMapItem,            \
        dummycreateMapItem);                                                   \
    getMapItemsFuncTuple =                                                     \
        std::make_tuple(getMapItems1, getMapItems2, dummygetMapItems,          \
                        dummygetMapItems, dummygetMapItems, dummygetMapItems,  \
                        dummygetMapItems, dummygetMapItems, dummygetMapItems,  \
                        dummygetMapItems, dummygetMapItems, dummygetMapItems,  \
                        dummygetMapItems, dummygetMapItems, dummygetMapItems,  \
                        dummygetMapItems, dummygetMapItems, dummygetMapItems,  \
                        dummygetMapItems, dummygetMapItems, dummygetMapItems,  \
                        dummygetMapItems, dummygetMapItems, dummygetMapItems,  \
                        dummygetMapItems, dummygetMapItems, dummygetMapItems,  \
                        dummygetMapItems, dummygetMapItems, dummygetMapItems,  \
                        dummygetMapItems, dummygetMapItems);                   \
    addListItemFuncTuple =                                                     \
        std::make_tuple(addListItem, addListItem2, dummyAddListItem,           \
                        dummyAddListItem, dummyAddListItem, dummyAddListItem,  \
                        dummyAddListItem, dummyAddListItem, dummyAddListItem,  \
                        dummyAddListItem, dummyAddListItem, dummyAddListItem,  \
                        dummyAddListItem, dummyAddListItem, dummyAddListItem,  \
                        dummyAddListItem, dummyAddListItem, dummyAddListItem,  \
                        dummyAddListItem, dummyAddListItem, dummyAddListItem,  \
                        dummyAddListItem, dummyAddListItem, dummyAddListItem,  \
                        dummyAddListItem, dummyAddListItem, dummyAddListItem,  \
                        dummyAddListItem, dummyAddListItem, dummyAddListItem,  \
                        dummyAddListItem, dummyAddListItem);                   \
    addMapItemFuncTuple = std::make_tuple(                                     \
        addMapItem, addMapItem2, dummyAddMapItem, dummyAddMapItem,             \
        dummyAddMapItem, dummyAddMapItem, dummyAddMapItem, dummyAddMapItem,    \
        dummyAddMapItem, dummyAddMapItem, dummyAddMapItem, dummyAddMapItem,    \
        dummyAddMapItem, dummyAddMapItem, dummyAddMapItem, dummyAddMapItem,    \
        dummyAddMapItem, dummyAddMapItem, dummyAddMapItem, dummyAddMapItem,    \
        dummyAddMapItem, dummyAddMapItem, dummyAddMapItem, dummyAddMapItem,    \
        dummyAddMapItem, dummyAddMapItem, dummyAddMapItem, dummyAddMapItem,    \
        dummyAddMapItem, dummyAddMapItem, dummyAddMapItem, dummyAddMapItem);

#define IMPLE_INIT_TUPLE_3(CLASS, M1, M2, M3)                                  \
    std::function<decltype(M1)()> getobj1 =                                    \
        std::bind(&CLASS::__ReflectGet##M1, this);                             \
    std::function<decltype(M2)()> getobj2 =                                    \
        std::bind(&CLASS::__ReflectGet##M2, this);                             \
    std::function<decltype(M3)()> getobj3 =                                    \
        std::bind(&CLASS::__ReflectGet##M3, this);                             \
    std::function<void()> createobj1 =                                         \
        std::bind(&CLASS::__ReflectCreate##M1, this);                          \
    std::function<void()> createobj2 =                                         \
        std::bind(&CLASS::__ReflectCreate##M2, this);                          \
    std::function<void()> createobj3 =                                         \
        std::bind(&CLASS::__ReflectCreate##M3, this);                          \
    std::function<Object()> genItemObj1 =                                      \
        std::bind(&CLASS::__ReflectCreateListMember##M1, this);                \
    std::function<Object()> genItemObj2 =                                      \
        std::bind(&CLASS::__ReflectCreateListMember##M2, this);                \
    std::function<Object()> genItemObj3 =                                      \
        std::bind(&CLASS::__ReflectCreateListMember##M3, this);                \
    std::function<Object(int)> getItemObj1 = std::bind(                        \
        &CLASS::__ReflectGetListItem##M1, this, std::placeholders::_1);        \
    std::function<Object(int)> getItemObj2 = std::bind(                        \
        &CLASS::__ReflectGetListItem##M2, this, std::placeholders::_1);        \
    std::function<Object(int)> getItemObj3 = std::bind(                        \
        &CLASS::__ReflectGetListItem##M3, this, std::placeholders::_1);        \
    std::function<int()> getContainerSize1 =                                   \
        std::bind(&CLASS::__ReflectGetContainerSize##M1, this);                \
    std::function<int()> getContainerSize2 =                                   \
        std::bind(&CLASS::__ReflectGetContainerSize##M2, this);                \
    std::function<int()> getContainerSize3 =                                   \
        std::bind(&CLASS::__ReflectGetContainerSize##M3, this);                \
    std::function<Pair<Object, Object>()> createMapObj1 =              \
        std::bind(&CLASS::__ReflectCreateMapMember##M1, this);                 \
    std::function<ArrayList<Pair<Object, Object>>()> getMapItems1 =    \
        std::bind(&CLASS::__ReflectGetMapItems##M1, this);                     \
    std::function<Pair<Object, Object>()> createMapObj2 =              \
        std::bind(&CLASS::__ReflectCreateMapMember##M2, this);                 \
    std::function<ArrayList<Pair<Object, Object>>()> getMapItems2 =    \
        std::bind(&CLASS::__ReflectGetMapItems##M2, this);                     \
    std::function<Pair<Object, Object>()> createMapObj3 =              \
        std::bind(&CLASS::__ReflectCreateMapMember##M3, this);                 \
    std::function<ArrayList<Pair<Object, Object>>()> getMapItems3 =    \
        std::bind(&CLASS::__ReflectGetMapItems##M3, this);                     \
    std::function<void(Object)> addListItem = std::bind(                       \
        &CLASS::__ReflectAddListItem##M1, this, std::placeholders::_1);        \
    std::function<void(Object, Object)> addMapItem =                           \
        std::bind(&CLASS::__ReflectAddMapItem##M1, this,                       \
                  std::placeholders::_1, std::placeholders::_2);               \
    std::function<void(Object)> addListItem2 = std::bind(                      \
        &CLASS::__ReflectAddListItem##M2, this, std::placeholders::_1);        \
    std::function<void(Object, Object)> addMapItem2 =                          \
        std::bind(&CLASS::__ReflectAddMapItem##M2, this,                       \
                  std::placeholders::_1, std::placeholders::_2);               \
    std::function<void(Object)> addListItem3 = std::bind(                      \
        &CLASS::__ReflectAddListItem##M3, this, std::placeholders::_1);        \
    std::function<void(Object, Object)> addMapItem3 =                          \
        std::bind(&CLASS::__ReflectAddMapItem##M3, this,                       \
                  std::placeholders::_1, std::placeholders::_2);               \
    getFuncTuple = std::make_tuple(                                            \
        getobj1, getobj2, getobj3, dummyobj, dummyobj, dummyobj, dummyobj,     \
        dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj,  \
        dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj,  \
        dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj,  \
        dummyobj, dummyobj, dummyobj, dummyobj);                               \
    createFuncTuple = std::make_tuple(                                         \
        createobj1, createobj2, createobj3, dummyobj, dummyobj, dummyobj,      \
        dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj,  \
        dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj,  \
        dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj,  \
        dummyobj, dummyobj, dummyobj, dummyobj, dummyobj);                     \
    createListItemFuncTuple = std::make_tuple(                                 \
        genItemObj1, genItemObj2, genItemObj3, dummycreateobj, dummycreateobj, \
        dummycreateobj, dummycreateobj, dummycreateobj, dummycreateobj,        \
        dummycreateobj, dummycreateobj, dummycreateobj, dummycreateobj,        \
        dummycreateobj, dummycreateobj, dummycreateobj, dummycreateobj,        \
        dummycreateobj, dummycreateobj, dummycreateobj, dummycreateobj,        \
        dummycreateobj, dummycreateobj, dummycreateobj, dummycreateobj,        \
        dummycreateobj, dummycreateobj, dummycreateobj, dummycreateobj,        \
        dummycreateobj, dummycreateobj, dummycreateobj);                       \
    getListItemFuncTuple = std::make_tuple(                                    \
        getItemObj1, getItemObj2, getItemObj3, dummyligobj, dummyligobj,       \
        dummyligobj, dummyligobj, dummyligobj, dummyligobj, dummyligobj,       \
        dummyligobj, dummyligobj, dummyligobj, dummyligobj, dummyligobj,       \
        dummyligobj, dummyligobj, dummyligobj, dummyligobj, dummyligobj,       \
        dummyligobj, dummyligobj, dummyligobj, dummyligobj, dummyligobj,       \
        dummyligobj, dummyligobj, dummyligobj, dummyligobj, dummyligobj,       \
        dummyligobj, dummyligobj);                                             \
    getContainerSizeFuncTuple = std::make_tuple(                               \
        getContainerSize1, getContainerSize2, getContainerSize3, dummyobj,     \
        dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj,  \
        dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj,  \
        dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj,  \
        dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj); \
    createMapItemFuncTuple = std::make_tuple(                                  \
        createMapObj1, createMapObj2, createMapObj3, dummycreateMapItem,       \
        dummycreateMapItem, dummycreateMapItem, dummycreateMapItem,            \
        dummycreateMapItem, dummycreateMapItem, dummycreateMapItem,            \
        dummycreateMapItem, dummycreateMapItem, dummycreateMapItem,            \
        dummycreateMapItem, dummycreateMapItem, dummycreateMapItem,            \
        dummycreateMapItem, dummycreateMapItem, dummycreateMapItem,            \
        dummycreateMapItem, dummycreateMapItem, dummycreateMapItem,            \
        dummycreateMapItem, dummycreateMapItem, dummycreateMapItem,            \
        dummycreateMapItem, dummycreateMapItem, dummycreateMapItem,            \
        dummycreateMapItem, dummycreateMapItem, dummycreateMapItem,            \
        dummycreateMapItem);                                                   \
    getMapItemsFuncTuple =                                                     \
        std::make_tuple(getMapItems1, getMapItems2, getMapItems3,              \
                        dummygetMapItems, dummygetMapItems, dummygetMapItems,  \
                        dummygetMapItems, dummygetMapItems, dummygetMapItems,  \
                        dummygetMapItems, dummygetMapItems, dummygetMapItems,  \
                        dummygetMapItems, dummygetMapItems, dummygetMapItems,  \
                        dummygetMapItems, dummygetMapItems, dummygetMapItems,  \
                        dummygetMapItems, dummygetMapItems, dummygetMapItems,  \
                        dummygetMapItems, dummygetMapItems, dummygetMapItems,  \
                        dummygetMapItems, dummygetMapItems, dummygetMapItems,  \
                        dummygetMapItems, dummygetMapItems, dummygetMapItems,  \
                        dummygetMapItems, dummygetMapItems);                   \
    addListItemFuncTuple =                                                     \
        std::make_tuple(addListItem, addListItem2, addListItem3,               \
                        dummyAddListItem, dummyAddListItem, dummyAddListItem,  \
                        dummyAddListItem, dummyAddListItem, dummyAddListItem,  \
                        dummyAddListItem, dummyAddListItem, dummyAddListItem,  \
                        dummyAddListItem, dummyAddListItem, dummyAddListItem,  \
                        dummyAddListItem, dummyAddListItem, dummyAddListItem,  \
                        dummyAddListItem, dummyAddListItem, dummyAddListItem,  \
                        dummyAddListItem, dummyAddListItem, dummyAddListItem,  \
                        dummyAddListItem, dummyAddListItem, dummyAddListItem,  \
                        dummyAddListItem, dummyAddListItem, dummyAddListItem,  \
                        dummyAddListItem, dummyAddListItem);                   \
    addMapItemFuncTuple = std::make_tuple(                                     \
        addMapItem, addMapItem2, addMapItem3, dummyAddMapItem,                 \
        dummyAddMapItem, dummyAddMapItem, dummyAddMapItem, dummyAddMapItem,    \
        dummyAddMapItem, dummyAddMapItem, dummyAddMapItem, dummyAddMapItem,    \
        dummyAddMapItem, dummyAddMapItem, dummyAddMapItem, dummyAddMapItem,    \
        dummyAddMapItem, dummyAddMapItem, dummyAddMapItem, dummyAddMapItem,    \
        dummyAddMapItem, dummyAddMapItem, dummyAddMapItem, dummyAddMapItem,    \
        dummyAddMapItem, dummyAddMapItem, dummyAddMapItem, dummyAddMapItem,    \
        dummyAddMapItem, dummyAddMapItem, dummyAddMapItem, dummyAddMapItem);

#define IMPLE_INIT_TUPLE_4(CLASS, M1, M2, M3, M4)                              \
    std::function<decltype(M1)()> getobj1 =                                    \
        std::bind(&CLASS::__ReflectGet##M1, this);                             \
    std::function<decltype(M2)()> getobj2 =                                    \
        std::bind(&CLASS::__ReflectGet##M2, this);                             \
    std::function<decltype(M3)()> getobj3 =                                    \
        std::bind(&CLASS::__ReflectGet##M3, this);                             \
    std::function<decltype(M4)()> getobj4 =                                    \
        std::bind(&CLASS::__ReflectGet##M4, this);                             \
    std::function<void()> createobj1 =                                         \
        std::bind(&CLASS::__ReflectCreate##M1, this);                          \
    std::function<void()> createobj2 =                                         \
        std::bind(&CLASS::__ReflectCreate##M2, this);                          \
    std::function<void()> createobj3 =                                         \
        std::bind(&CLASS::__ReflectCreate##M3, this);                          \
    std::function<void()> createobj4 =                                         \
        std::bind(&CLASS::__ReflectCreate##M4, this);                          \
    std::function<Object()> genItemObj1 =                                      \
        std::bind(&CLASS::__ReflectCreateListMember##M1, this);                \
    std::function<Object()> genItemObj2 =                                      \
        std::bind(&CLASS::__ReflectCreateListMember##M2, this);                \
    std::function<Object()> genItemObj3 =                                      \
        std::bind(&CLASS::__ReflectCreateListMember##M3, this);                \
    std::function<Object()> genItemObj4 =                                      \
        std::bind(&CLASS::__ReflectCreateListMember##M4, this);                \
    std::function<Object(int)> getItemObj1 = std::bind(                        \
        &CLASS::__ReflectGetListItem##M1, this, std::placeholders::_1);        \
    std::function<Object(int)> getItemObj2 = std::bind(                        \
        &CLASS::__ReflectGetListItem##M2, this, std::placeholders::_1);        \
    std::function<Object(int)> getItemObj3 = std::bind(                        \
        &CLASS::__ReflectGetListItem##M3, this, std::placeholders::_1);        \
    std::function<Object(int)> getItemObj4 = std::bind(                        \
        &CLASS::__ReflectGetListItem##M4, this, std::placeholders::_1);        \
    std::function<int()> getContainerSize1 =                                   \
        std::bind(&CLASS::__ReflectGetContainerSize##M1, this);                \
    std::function<int()> getContainerSize2 =                                   \
        std::bind(&CLASS::__ReflectGetContainerSize##M2, this);                \
    std::function<int()> getContainerSize3 =                                   \
        std::bind(&CLASS::__ReflectGetContainerSize##M3, this);                \
    std::function<int()> getContainerSize4 =                                   \
        std::bind(&CLASS::__ReflectGetContainerSize##M4, this);                \
    std::function<Pair<Object, Object>()> createMapObj1 =              \
        std::bind(&CLASS::__ReflectCreateMapMember##M1, this);                 \
    std::function<ArrayList<Pair<Object, Object>>()> getMapItems1 =    \
        std::bind(&CLASS::__ReflectGetMapItems##M1, this);                     \
    std::function<Pair<Object, Object>()> createMapObj2 =              \
        std::bind(&CLASS::__ReflectCreateMapMember##M2, this);                 \
    std::function<ArrayList<Pair<Object, Object>>()> getMapItems2 =    \
        std::bind(&CLASS::__ReflectGetMapItems##M2, this);                     \
    std::function<Pair<Object, Object>()> createMapObj3 =              \
        std::bind(&CLASS::__ReflectCreateMapMember##M3, this);                 \
    std::function<ArrayList<Pair<Object, Object>>()> getMapItems3 =    \
        std::bind(&CLASS::__ReflectGetMapItems##M3, this);                     \
    std::function<Pair<Object, Object>()> createMapObj4 =              \
        std::bind(&CLASS::__ReflectCreateMapMember##M4, this);                 \
    std::function<ArrayList<Pair<Object, Object>>()> getMapItems4 =    \
        std::bind(&CLASS::__ReflectGetMapItems##M4, this);                     \
    std::function<void(Object)> addListItem = std::bind(                       \
        &CLASS::__ReflectAddListItem##M1, this, std::placeholders::_1);        \
    std::function<void(Object, Object)> addMapItem =                           \
        std::bind(&CLASS::__ReflectAddMapItem##M1, this,                       \
                  std::placeholders::_1, std::placeholders::_2);               \
    std::function<void(Object)> addListItem2 = std::bind(                      \
        &CLASS::__ReflectAddListItem##M2, this, std::placeholders::_1);        \
    std::function<void(Object, Object)> addMapItem2 =                          \
        std::bind(&CLASS::__ReflectAddMapItem##M2, this,                       \
                  std::placeholders::_1, std::placeholders::_2);               \
    std::function<void(Object)> addListItem3 = std::bind(                      \
        &CLASS::__ReflectAddListItem##M3, this, std::placeholders::_1);        \
    std::function<void(Object, Object)> addMapItem3 =                          \
        std::bind(&CLASS::__ReflectAddMapItem##M3, this,                       \
                  std::placeholders::_1, std::placeholders::_2);               \
    std::function<void(Object)> addListItem4 = std::bind(                      \
        &CLASS::__ReflectAddListItem##M4, this, std::placeholders::_1);        \
    std::function<void(Object, Object)> addMapItem4 =                          \
        std::bind(&CLASS::__ReflectAddMapItem##M4, this,                       \
                  std::placeholders::_1, std::placeholders::_2);               \
    getFuncTuple = std::make_tuple(                                            \
        getobj1, getobj2, getobj3, getobj4, dummyobj, dummyobj, dummyobj,      \
        dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj,  \
        dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj,  \
        dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj,  \
        dummyobj, dummyobj, dummyobj, dummyobj);                               \
    createFuncTuple = std::make_tuple(                                         \
        createobj1, createobj2, createobj3, createobj4, dummyobj, dummyobj,    \
        dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj,  \
        dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj,  \
        dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj,  \
        dummyobj, dummyobj, dummyobj, dummyobj, dummyobj);                     \
    createListItemFuncTuple = std::make_tuple(                                 \
        genItemObj1, genItemObj2, genItemObj3, genItemObj4, dummycreateobj,    \
        dummycreateobj, dummycreateobj, dummycreateobj, dummycreateobj,        \
        dummycreateobj, dummycreateobj, dummycreateobj, dummycreateobj,        \
        dummycreateobj, dummycreateobj, dummycreateobj, dummycreateobj,        \
        dummycreateobj, dummycreateobj, dummycreateobj, dummycreateobj,        \
        dummycreateobj, dummycreateobj, dummycreateobj, dummycreateobj,        \
        dummycreateobj, dummycreateobj, dummycreateobj, dummycreateobj,        \
        dummycreateobj, dummycreateobj, dummycreateobj);                       \
    getListItemFuncTuple = std::make_tuple(                                    \
        getItemObj1, getItemObj2, getItemObj3, getItemObj4, dummyligobj,       \
        dummyligobj, dummyligobj, dummyligobj, dummyligobj, dummyligobj,       \
        dummyligobj, dummyligobj, dummyligobj, dummyligobj, dummyligobj,       \
        dummyligobj, dummyligobj, dummyligobj, dummyligobj, dummyligobj,       \
        dummyligobj, dummyligobj, dummyligobj, dummyligobj, dummyligobj,       \
        dummyligobj, dummyligobj, dummyligobj, dummyligobj, dummyligobj,       \
        dummyligobj, dummyligobj);                                             \
    getContainerSizeFuncTuple = std::make_tuple(                               \
        getContainerSize1, getContainerSize2, getContainerSize3,               \
        getContainerSize4, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj,   \
        dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj,  \
        dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj,  \
        dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj,  \
        dummyobj, dummyobj);                                                   \
    createMapItemFuncTuple = std::make_tuple(                                  \
        createMapObj1, createMapObj2, createMapObj3, createMapObj4,            \
        dummycreateMapItem, dummycreateMapItem, dummycreateMapItem,            \
        dummycreateMapItem, dummycreateMapItem, dummycreateMapItem,            \
        dummycreateMapItem, dummycreateMapItem, dummycreateMapItem,            \
        dummycreateMapItem, dummycreateMapItem, dummycreateMapItem,            \
        dummycreateMapItem, dummycreateMapItem, dummycreateMapItem,            \
        dummycreateMapItem, dummycreateMapItem, dummycreateMapItem,            \
        dummycreateMapItem, dummycreateMapItem, dummycreateMapItem,            \
        dummycreateMapItem, dummycreateMapItem, dummycreateMapItem,            \
        dummycreateMapItem, dummycreateMapItem, dummycreateMapItem,            \
        dummycreateMapItem);                                                   \
    getMapItemsFuncTuple =                                                     \
        std::make_tuple(getMapItems1, getMapItems2, getMapItems3,              \
                        getMapItems4, dummygetMapItems, dummygetMapItems,      \
                        dummygetMapItems, dummygetMapItems, dummygetMapItems,  \
                        dummygetMapItems, dummygetMapItems, dummygetMapItems,  \
                        dummygetMapItems, dummygetMapItems, dummygetMapItems,  \
                        dummygetMapItems, dummygetMapItems, dummygetMapItems,  \
                        dummygetMapItems, dummygetMapItems, dummygetMapItems,  \
                        dummygetMapItems, dummygetMapItems, dummygetMapItems,  \
                        dummygetMapItems, dummygetMapItems, dummygetMapItems,  \
                        dummygetMapItems, dummygetMapItems, dummygetMapItems,  \
                        dummygetMapItems, dummygetMapItems);                   \
    addListItemFuncTuple =                                                     \
        std::make_tuple(addListItem, addListItem2, addListItem3, addListItem4, \
                        dummyAddListItem, dummyAddListItem, dummyAddListItem,  \
                        dummyAddListItem, dummyAddListItem, dummyAddListItem,  \
                        dummyAddListItem, dummyAddListItem, dummyAddListItem,  \
                        dummyAddListItem, dummyAddListItem, dummyAddListItem,  \
                        dummyAddListItem, dummyAddListItem, dummyAddListItem,  \
                        dummyAddListItem, dummyAddListItem, dummyAddListItem,  \
                        dummyAddListItem, dummyAddListItem, dummyAddListItem,  \
                        dummyAddListItem, dummyAddListItem, dummyAddListItem,  \
                        dummyAddListItem, dummyAddListItem, dummyAddListItem,  \
                        dummyAddListItem);                                     \
    addMapItemFuncTuple = std::make_tuple(                                     \
        addMapItem, addMapItem2, addMapItem3, addMapItem4, dummyAddMapItem,    \
        dummyAddMapItem, dummyAddMapItem, dummyAddMapItem, dummyAddMapItem,    \
        dummyAddMapItem, dummyAddMapItem, dummyAddMapItem, dummyAddMapItem,    \
        dummyAddMapItem, dummyAddMapItem, dummyAddMapItem, dummyAddMapItem,    \
        dummyAddMapItem, dummyAddMapItem, dummyAddMapItem, dummyAddMapItem,    \
        dummyAddMapItem, dummyAddMapItem, dummyAddMapItem, dummyAddMapItem,    \
        dummyAddMapItem, dummyAddMapItem, dummyAddMapItem, dummyAddMapItem,    \
        dummyAddMapItem, dummyAddMapItem, dummyAddMapItem);

#define IMPLE_INIT_TUPLE_5(CLASS, M1, M2, M3, M4, M5)                          \
    std::function<decltype(M1)()> getobj1 =                                    \
        std::bind(&CLASS::__ReflectGet##M1, this);                             \
    std::function<decltype(M2)()> getobj2 =                                    \
        std::bind(&CLASS::__ReflectGet##M2, this);                             \
    std::function<decltype(M3)()> getobj3 =                                    \
        std::bind(&CLASS::__ReflectGet##M3, this);                             \
    std::function<decltype(M4)()> getobj4 =                                    \
        std::bind(&CLASS::__ReflectGet##M4, this);                             \
    std::function<decltype(M5)()> getobj5 =                                    \
        std::bind(&CLASS::__ReflectGet##M5, this);                             \
    std::function<void()> createobj1 =                                         \
        std::bind(&CLASS::__ReflectCreate##M1, this);                          \
    std::function<void()> createobj2 =                                         \
        std::bind(&CLASS::__ReflectCreate##M2, this);                          \
    std::function<void()> createobj3 =                                         \
        std::bind(&CLASS::__ReflectCreate##M3, this);                          \
    std::function<void()> createobj4 =                                         \
        std::bind(&CLASS::__ReflectCreate##M4, this);                          \
    std::function<void()> createobj5 =                                         \
        std::bind(&CLASS::__ReflectCreate##M5, this);                          \
    std::function<Object()> genItemObj1 =                                      \
        std::bind(&CLASS::__ReflectCreateListMember##M1, this);                \
    std::function<Object()> genItemObj2 =                                      \
        std::bind(&CLASS::__ReflectCreateListMember##M2, this);                \
    std::function<Object()> genItemObj3 =                                      \
        std::bind(&CLASS::__ReflectCreateListMember##M3, this);                \
    std::function<Object()> genItemObj4 =                                      \
        std::bind(&CLASS::__ReflectCreateListMember##M4, this);                \
    std::function<Object()> genItemObj5 =                                      \
        std::bind(&CLASS::__ReflectCreateListMember##M5, this);                \
    std::function<Object(int)> getItemObj1 = std::bind(                        \
        &CLASS::__ReflectGetListItem##M1, this, std::placeholders::_1);        \
    std::function<Object(int)> getItemObj2 = std::bind(                        \
        &CLASS::__ReflectGetListItem##M2, this, std::placeholders::_1);        \
    std::function<Object(int)> getItemObj3 = std::bind(                        \
        &CLASS::__ReflectGetListItem##M3, this, std::placeholders::_1);        \
    std::function<Object(int)> getItemObj4 = std::bind(                        \
        &CLASS::__ReflectGetListItem##M4, this, std::placeholders::_1);        \
    std::function<Object(int)> getItemObj5 = std::bind(                        \
        &CLASS::__ReflectGetListItem##M5, this, std::placeholders::_1);        \
    std::function<int()> getContainerSize1 =                                   \
        std::bind(&CLASS::__ReflectGetContainerSize##M1, this);                \
    std::function<int()> getContainerSize2 =                                   \
        std::bind(&CLASS::__ReflectGetContainerSize##M2, this);                \
    std::function<int()> getContainerSize3 =                                   \
        std::bind(&CLASS::__ReflectGetContainerSize##M3, this);                \
    std::function<int()> getContainerSize4 =                                   \
        std::bind(&CLASS::__ReflectGetContainerSize##M4, this);                \
    std::function<int()> getContainerSize5 =                                   \
        std::bind(&CLASS::__ReflectGetContainerSize##M5, this);                \
    std::function<Pair<Object, Object>()> createMapObj1 =              \
        std::bind(&CLASS::__ReflectCreateMapMember##M1, this);                 \
    std::function<ArrayList<Pair<Object, Object>>()> getMapItems1 =    \
        std::bind(&CLASS::__ReflectGetMapItems##M1, this);                     \
    std::function<Pair<Object, Object>()> createMapObj2 =              \
        std::bind(&CLASS::__ReflectCreateMapMember##M2, this);                 \
    std::function<ArrayList<Pair<Object, Object>>()> getMapItems2 =    \
        std::bind(&CLASS::__ReflectGetMapItems##M2, this);                     \
    std::function<Pair<Object, Object>()> createMapObj3 =              \
        std::bind(&CLASS::__ReflectCreateMapMember##M3, this);                 \
    std::function<ArrayList<Pair<Object, Object>>()> getMapItems3 =    \
        std::bind(&CLASS::__ReflectGetMapItems##M3, this);                     \
    std::function<Pair<Object, Object>()> createMapObj4 =              \
        std::bind(&CLASS::__ReflectCreateMapMember##M4, this);                 \
    std::function<ArrayList<Pair<Object, Object>>()> getMapItems4 =    \
        std::bind(&CLASS::__ReflectGetMapItems##M4, this);                     \
    std::function<Pair<Object, Object>()> createMapObj5 =              \
        std::bind(&CLASS::__ReflectCreateMapMember##M5, this);                 \
    std::function<ArrayList<Pair<Object, Object>>()> getMapItems5 =    \
        std::bind(&CLASS::__ReflectGetMapItems##M5, this);                     \
    std::function<void(Object)> addListItem = std::bind(                       \
        &CLASS::__ReflectAddListItem##M1, this, std::placeholders::_1);        \
    std::function<void(Object, Object)> addMapItem =                           \
        std::bind(&CLASS::__ReflectAddMapItem##M1, this,                       \
                  std::placeholders::_1, std::placeholders::_2);               \
    std::function<void(Object)> addListItem2 = std::bind(                      \
        &CLASS::__ReflectAddListItem##M2, this, std::placeholders::_1);        \
    std::function<void(Object, Object)> addMapItem2 =                          \
        std::bind(&CLASS::__ReflectAddMapItem##M2, this,                       \
                  std::placeholders::_1, std::placeholders::_2);               \
    std::function<void(Object)> addListItem3 = std::bind(                      \
        &CLASS::__ReflectAddListItem##M3, this, std::placeholders::_1);        \
    std::function<void(Object, Object)> addMapItem3 =                          \
        std::bind(&CLASS::__ReflectAddMapItem##M3, this,                       \
                  std::placeholders::_1, std::placeholders::_2);               \
    std::function<void(Object)> addListItem4 = std::bind(                      \
        &CLASS::__ReflectAddListItem##M4, this, std::placeholders::_1);        \
    std::function<void(Object, Object)> addMapItem4 =                          \
        std::bind(&CLASS::__ReflectAddMapItem##M4, this,                       \
                  std::placeholders::_1, std::placeholders::_2);               \
    std::function<void(Object)> addListItem5 = std::bind(                      \
        &CLASS::__ReflectAddListItem##M5, this, std::placeholders::_1);        \
    std::function<void(Object, Object)> addMapItem5 =                          \
        std::bind(&CLASS::__ReflectAddMapItem##M5, this,                       \
                  std::placeholders::_1, std::placeholders::_2);               \
    getFuncTuple = std::make_tuple(                                            \
        getobj1, getobj2, getobj3, getobj4, getobj5, dummyobj, dummyobj,       \
        dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj,  \
        dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj,  \
        dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj,  \
        dummyobj, dummyobj, dummyobj, dummyobj);                               \
    createFuncTuple = std::make_tuple(                                         \
        createobj1, createobj2, createobj3, createobj4, createobj5, dummyobj,  \
        dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj,  \
        dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj,  \
        dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj,  \
        dummyobj, dummyobj, dummyobj, dummyobj, dummyobj);                     \
    createListItemFuncTuple = std::make_tuple(                                 \
        genItemObj1, genItemObj2, genItemObj3, genItemObj4, genItemObj5,       \
        dummycreateobj, dummycreateobj, dummycreateobj, dummycreateobj,        \
        dummycreateobj, dummycreateobj, dummycreateobj, dummycreateobj,        \
        dummycreateobj, dummycreateobj, dummycreateobj, dummycreateobj,        \
        dummycreateobj, dummycreateobj, dummycreateobj, dummycreateobj,        \
        dummycreateobj, dummycreateobj, dummycreateobj, dummycreateobj,        \
        dummycreateobj, dummycreateobj, dummycreateobj, dummycreateobj,        \
        dummycreateobj, dummycreateobj, dummycreateobj);                       \
    getListItemFuncTuple = std::make_tuple(                                    \
        getItemObj1, getItemObj2, getItemObj3, getItemObj4, getItemObj5,       \
        dummyligobj, dummyligobj, dummyligobj, dummyligobj, dummyligobj,       \
        dummyligobj, dummyligobj, dummyligobj, dummyligobj, dummyligobj,       \
        dummyligobj, dummyligobj, dummyligobj, dummyligobj, dummyligobj,       \
        dummyligobj, dummyligobj, dummyligobj, dummyligobj, dummyligobj,       \
        dummyligobj, dummyligobj, dummyligobj, dummyligobj, dummyligobj,       \
        dummyligobj, dummyligobj);                                             \
    getContainerSizeFuncTuple = std::make_tuple(                               \
        getContainerSize1, getContainerSize2, getContainerSize3,               \
        getContainerSize4, getContainerSize5, dummyobj, dummyobj, dummyobj,    \
        dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj,  \
        dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj,  \
        dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj,  \
        dummyobj, dummyobj, dummyobj);                                         \
    createMapItemFuncTuple = std::make_tuple(                                  \
        createMapObj1, createMapObj2, createMapObj3, createMapObj4,            \
        createMapObj5, dummycreateMapItem, dummycreateMapItem,                 \
        dummycreateMapItem, dummycreateMapItem, dummycreateMapItem,            \
        dummycreateMapItem, dummycreateMapItem, dummycreateMapItem,            \
        dummycreateMapItem, dummycreateMapItem, dummycreateMapItem,            \
        dummycreateMapItem, dummycreateMapItem, dummycreateMapItem,            \
        dummycreateMapItem, dummycreateMapItem, dummycreateMapItem,            \
        dummycreateMapItem, dummycreateMapItem, dummycreateMapItem,            \
        dummycreateMapItem, dummycreateMapItem, dummycreateMapItem,            \
        dummycreateMapItem, dummycreateMapItem, dummycreateMapItem,            \
        dummycreateMapItem);                                                   \
    getMapItemsFuncTuple = std::make_tuple(                                    \
        getMapItems1, getMapItems2, getMapItems3, getMapItems4, getMapItems5,  \
        dummygetMapItems, dummygetMapItems, dummygetMapItems,                  \
        dummygetMapItems, dummygetMapItems, dummygetMapItems,                  \
        dummygetMapItems, dummygetMapItems, dummygetMapItems,                  \
        dummygetMapItems, dummygetMapItems, dummygetMapItems,                  \
        dummygetMapItems, dummygetMapItems, dummygetMapItems,                  \
        dummygetMapItems, dummygetMapItems, dummygetMapItems,                  \
        dummygetMapItems, dummygetMapItems, dummygetMapItems,                  \
        dummygetMapItems, dummygetMapItems, dummygetMapItems,                  \
        dummygetMapItems, dummygetMapItems, dummygetMapItems);                 \
    addListItemFuncTuple = std::make_tuple(                                    \
        addListItem, addListItem2, addListItem3, addListItem4, addListItem5,   \
        dummyAddListItem, dummyAddListItem, dummyAddListItem,                  \
        dummyAddListItem, dummyAddListItem, dummyAddListItem,                  \
        dummyAddListItem, dummyAddListItem, dummyAddListItem,                  \
        dummyAddListItem, dummyAddListItem, dummyAddListItem,                  \
        dummyAddListItem, dummyAddListItem, dummyAddListItem,                  \
        dummyAddListItem, dummyAddListItem, dummyAddListItem,                  \
        dummyAddListItem, dummyAddListItem, dummyAddListItem,                  \
        dummyAddListItem, dummyAddListItem, dummyAddListItem,                  \
        dummyAddListItem, dummyAddListItem, dummyAddListItem);                 \
    addMapItemFuncTuple = std::make_tuple(                                     \
        addMapItem, addMapItem2, addMapItem3, addMapItem4, addMapItem5,        \
        dummyAddMapItem, dummyAddMapItem, dummyAddMapItem, dummyAddMapItem,    \
        dummyAddMapItem, dummyAddMapItem, dummyAddMapItem, dummyAddMapItem,    \
        dummyAddMapItem, dummyAddMapItem, dummyAddMapItem, dummyAddMapItem,    \
        dummyAddMapItem, dummyAddMapItem, dummyAddMapItem, dummyAddMapItem,    \
        dummyAddMapItem, dummyAddMapItem, dummyAddMapItem, dummyAddMapItem,    \
        dummyAddMapItem, dummyAddMapItem, dummyAddMapItem, dummyAddMapItem,    \
        dummyAddMapItem, dummyAddMapItem, dummyAddMapItem);

#define IMPLE_INIT_TUPLE_6(CLASS, M1, M2, M3, M4, M5, M6)                      \
    std::function<decltype(M1)()> getobj1 =                                    \
        std::bind(&CLASS::__ReflectGet##M1, this);                             \
    std::function<decltype(M2)()> getobj2 =                                    \
        std::bind(&CLASS::__ReflectGet##M2, this);                             \
    std::function<decltype(M3)()> getobj3 =                                    \
        std::bind(&CLASS::__ReflectGet##M3, this);                             \
    std::function<decltype(M4)()> getobj4 =                                    \
        std::bind(&CLASS::__ReflectGet##M4, this);                             \
    std::function<decltype(M5)()> getobj5 =                                    \
        std::bind(&CLASS::__ReflectGet##M5, this);                             \
    std::function<decltype(M6)()> getobj6 =                                    \
        std::bind(&CLASS::__ReflectGet##M6, this);                             \
    std::function<void()> createobj1 =                                         \
        std::bind(&CLASS::__ReflectCreate##M1, this);                          \
    std::function<void()> createobj2 =                                         \
        std::bind(&CLASS::__ReflectCreate##M2, this);                          \
    std::function<void()> createobj3 =                                         \
        std::bind(&CLASS::__ReflectCreate##M3, this);                          \
    std::function<void()> createobj4 =                                         \
        std::bind(&CLASS::__ReflectCreate##M4, this);                          \
    std::function<void()> createobj5 =                                         \
        std::bind(&CLASS::__ReflectCreate##M5, this);                          \
    std::function<void()> createobj6 =                                         \
        std::bind(&CLASS::__ReflectCreate##M6, this);                          \
    std::function<Object()> genItemObj1 =                                      \
        std::bind(&CLASS::__ReflectCreateListMember##M1, this);                \
    std::function<Object()> genItemObj2 =                                      \
        std::bind(&CLASS::__ReflectCreateListMember##M2, this);                \
    std::function<Object()> genItemObj3 =                                      \
        std::bind(&CLASS::__ReflectCreateListMember##M3, this);                \
    std::function<Object()> genItemObj4 =                                      \
        std::bind(&CLASS::__ReflectCreateListMember##M4, this);                \
    std::function<Object()> genItemObj5 =                                      \
        std::bind(&CLASS::__ReflectCreateListMember##M5, this);                \
    std::function<Object()> genItemObj6 =                                      \
        std::bind(&CLASS::__ReflectCreateListMember##M6, this);                \
    std::function<Object(int)> getItemObj1 = std::bind(                        \
        &CLASS::__ReflectGetListItem##M1, this, std::placeholders::_1);        \
    std::function<Object(int)> getItemObj2 = std::bind(                        \
        &CLASS::__ReflectGetListItem##M2, this, std::placeholders::_1);        \
    std::function<Object(int)> getItemObj3 = std::bind(                        \
        &CLASS::__ReflectGetListItem##M3, this, std::placeholders::_1);        \
    std::function<Object(int)> getItemObj4 = std::bind(                        \
        &CLASS::__ReflectGetListItem##M4, this, std::placeholders::_1);        \
    std::function<Object(int)> getItemObj5 = std::bind(                        \
        &CLASS::__ReflectGetListItem##M5, this, std::placeholders::_1);        \
    std::function<Object(int)> getItemObj6 = std::bind(                        \
        &CLASS::__ReflectGetListItem##M6, this, std::placeholders::_1);        \
    std::function<int()> getContainerSize1 =                                   \
        std::bind(&CLASS::__ReflectGetContainerSize##M1, this);                \
    std::function<int()> getContainerSize2 =                                   \
        std::bind(&CLASS::__ReflectGetContainerSize##M2, this);                \
    std::function<int()> getContainerSize3 =                                   \
        std::bind(&CLASS::__ReflectGetContainerSize##M3, this);                \
    std::function<int()> getContainerSize4 =                                   \
        std::bind(&CLASS::__ReflectGetContainerSize##M4, this);                \
    std::function<int()> getContainerSize5 =                                   \
        std::bind(&CLASS::__ReflectGetContainerSize##M5, this);                \
    std::function<int()> getContainerSize6 =                                   \
        std::bind(&CLASS::__ReflectGetContainerSize##M6, this);                \
    std::function<Pair<Object, Object>()> createMapObj1 =              \
        std::bind(&CLASS::__ReflectCreateMapMember##M1, this);                 \
    std::function<ArrayList<Pair<Object, Object>>()> getMapItems1 =    \
        std::bind(&CLASS::__ReflectGetMapItems##M1, this);                     \
    std::function<Pair<Object, Object>()> createMapObj2 =              \
        std::bind(&CLASS::__ReflectCreateMapMember##M2, this);                 \
    std::function<ArrayList<Pair<Object, Object>>()> getMapItems2 =    \
        std::bind(&CLASS::__ReflectGetMapItems##M2, this);                     \
    std::function<Pair<Object, Object>()> createMapObj3 =              \
        std::bind(&CLASS::__ReflectCreateMapMember##M3, this);                 \
    std::function<ArrayList<Pair<Object, Object>>()> getMapItems3 =    \
        std::bind(&CLASS::__ReflectGetMapItems##M3, this);                     \
    std::function<Pair<Object, Object>()> createMapObj4 =              \
        std::bind(&CLASS::__ReflectCreateMapMember##M4, this);                 \
    std::function<ArrayList<Pair<Object, Object>>()> getMapItems4 =    \
        std::bind(&CLASS::__ReflectGetMapItems##M4, this);                     \
    std::function<Pair<Object, Object>()> createMapObj5 =              \
        std::bind(&CLASS::__ReflectCreateMapMember##M5, this);                 \
    std::function<ArrayList<Pair<Object, Object>>()> getMapItems5 =    \
        std::bind(&CLASS::__ReflectGetMapItems##M5, this);                     \
    std::function<Pair<Object, Object>()> createMapObj6 =              \
        std::bind(&CLASS::__ReflectCreateMapMember##M6, this);                 \
    std::function<ArrayList<Pair<Object, Object>>()> getMapItems6 =    \
        std::bind(&CLASS::__ReflectGetMapItems##M6, this);                     \
    std::function<void(Object)> addListItem = std::bind(                       \
        &CLASS::__ReflectAddListItem##M1, this, std::placeholders::_1);        \
    std::function<void(Object, Object)> addMapItem =                           \
        std::bind(&CLASS::__ReflectAddMapItem##M1, this,                       \
                  std::placeholders::_1, std::placeholders::_2);               \
    std::function<void(Object)> addListItem2 = std::bind(                      \
        &CLASS::__ReflectAddListItem##M2, this, std::placeholders::_1);        \
    std::function<void(Object, Object)> addMapItem2 =                          \
        std::bind(&CLASS::__ReflectAddMapItem##M2, this,                       \
                  std::placeholders::_1, std::placeholders::_2);               \
    std::function<void(Object)> addListItem3 = std::bind(                      \
        &CLASS::__ReflectAddListItem##M3, this, std::placeholders::_1);        \
    std::function<void(Object, Object)> addMapItem3 =                          \
        std::bind(&CLASS::__ReflectAddMapItem##M3, this,                       \
                  std::placeholders::_1, std::placeholders::_2);               \
    std::function<void(Object)> addListItem4 = std::bind(                      \
        &CLASS::__ReflectAddListItem##M4, this, std::placeholders::_1);        \
    std::function<void(Object, Object)> addMapItem4 =                          \
        std::bind(&CLASS::__ReflectAddMapItem##M4, this,                       \
                  std::placeholders::_1, std::placeholders::_2);               \
    std::function<void(Object)> addListItem5 = std::bind(                      \
        &CLASS::__ReflectAddListItem##M5, this, std::placeholders::_1);        \
    std::function<void(Object, Object)> addMapItem5 =                          \
        std::bind(&CLASS::__ReflectAddMapItem##M5, this,                       \
                  std::placeholders::_1, std::placeholders::_2);               \
    std::function<void(Object)> addListItem6 = std::bind(                      \
        &CLASS::__ReflectAddListItem##M6, this, std::placeholders::_1);        \
    std::function<void(Object, Object)> addMapItem6 =                          \
        std::bind(&CLASS::__ReflectAddMapItem##M6, this,                       \
                  std::placeholders::_1, std::placeholders::_2);               \
    getFuncTuple = std::make_tuple(                                            \
        getobj1, getobj2, getobj3, getobj4, getobj5, getobj6, dummyobj,        \
        dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj,  \
        dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj,  \
        dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj,  \
        dummyobj, dummyobj, dummyobj, dummyobj);                               \
    createFuncTuple = std::make_tuple(                                         \
        createobj1, createobj2, createobj3, createobj4, createobj5,            \
        createobj6, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj,          \
        dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj,  \
        dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj,  \
        dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj); \
    createListItemFuncTuple = std::make_tuple(                                 \
        genItemObj1, genItemObj2, genItemObj3, genItemObj4, genItemObj5,       \
        genItemObj6, dummycreateobj, dummycreateobj, dummycreateobj,           \
        dummycreateobj, dummycreateobj, dummycreateobj, dummycreateobj,        \
        dummycreateobj, dummycreateobj, dummycreateobj, dummycreateobj,        \
        dummycreateobj, dummycreateobj, dummycreateobj, dummycreateobj,        \
        dummycreateobj, dummycreateobj, dummycreateobj, dummycreateobj,        \
        dummycreateobj, dummycreateobj, dummycreateobj, dummycreateobj,        \
        dummycreateobj, dummycreateobj, dummycreateobj);                       \
    getListItemFuncTuple = std::make_tuple(                                    \
        getItemObj1, getItemObj2, getItemObj3, getItemObj4, getItemObj5,       \
        getItemObj6, dummyligobj, dummyligobj, dummyligobj, dummyligobj,       \
        dummyligobj, dummyligobj, dummyligobj, dummyligobj, dummyligobj,       \
        dummyligobj, dummyligobj, dummyligobj, dummyligobj, dummyligobj,       \
        dummyligobj, dummyligobj, dummyligobj, dummyligobj, dummyligobj,       \
        dummyligobj, dummyligobj, dummyligobj, dummyligobj, dummyligobj,       \
        dummyligobj, dummyligobj);                                             \
    getContainerSizeFuncTuple = std::make_tuple(                               \
        getContainerSize1, getContainerSize2, getContainerSize3,               \
        getContainerSize4, getContainerSize5, getContainerSize6, dummyobj,     \
        dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj,  \
        dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj,  \
        dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj,  \
        dummyobj, dummyobj, dummyobj, dummyobj);                               \
    createMapItemFuncTuple = std::make_tuple(                                  \
        createMapObj1, createMapObj2, createMapObj3, createMapObj4,            \
        createMapObj5, createMapObj6, dummycreateMapItem, dummycreateMapItem,  \
        dummycreateMapItem, dummycreateMapItem, dummycreateMapItem,            \
        dummycreateMapItem, dummycreateMapItem, dummycreateMapItem,            \
        dummycreateMapItem, dummycreateMapItem, dummycreateMapItem,            \
        dummycreateMapItem, dummycreateMapItem, dummycreateMapItem,            \
        dummycreateMapItem, dummycreateMapItem, dummycreateMapItem,            \
        dummycreateMapItem, dummycreateMapItem, dummycreateMapItem,            \
        dummycreateMapItem, dummycreateMapItem, dummycreateMapItem,            \
        dummycreateMapItem, dummycreateMapItem, dummycreateMapItem);           \
    getMapItemsFuncTuple = std::make_tuple(                                    \
        getMapItems1, getMapItems2, getMapItems3, getMapItems4, getMapItems5,  \
        getMapItems6, dummygetMapItems, dummygetMapItems, dummygetMapItems,    \
        dummygetMapItems, dummygetMapItems, dummygetMapItems,                  \
        dummygetMapItems, dummygetMapItems, dummygetMapItems,                  \
        dummygetMapItems, dummygetMapItems, dummygetMapItems,                  \
        dummygetMapItems, dummygetMapItems, dummygetMapItems,                  \
        dummygetMapItems, dummygetMapItems, dummygetMapItems,                  \
        dummygetMapItems, dummygetMapItems, dummygetMapItems,                  \
        dummygetMapItems, dummygetMapItems, dummygetMapItems,                  \
        dummygetMapItems, dummygetMapItems);                                   \
    addListItemFuncTuple = std::make_tuple(                                    \
        addListItem, addListItem2, addListItem3, addListItem4, addListItem5,   \
        addListItem6, dummyAddListItem, dummyAddListItem, dummyAddListItem,    \
        dummyAddListItem, dummyAddListItem, dummyAddListItem,                  \
        dummyAddListItem, dummyAddListItem, dummyAddListItem,                  \
        dummyAddListItem, dummyAddListItem, dummyAddListItem,                  \
        dummyAddListItem, dummyAddListItem, dummyAddListItem,                  \
        dummyAddListItem, dummyAddListItem, dummyAddListItem,                  \
        dummyAddListItem, dummyAddListItem, dummyAddListItem,                  \
        dummyAddListItem, dummyAddListItem, dummyAddListItem,                  \
        dummyAddListItem, dummyAddListItem);                                   \
    addMapItemFuncTuple = std::make_tuple(                                     \
        addMapItem, addMapItem2, addMapItem3, addMapItem4, addMapItem5,        \
        addMapItem6, dummyAddMapItem, dummyAddMapItem, dummyAddMapItem,        \
        dummyAddMapItem, dummyAddMapItem, dummyAddMapItem, dummyAddMapItem,    \
        dummyAddMapItem, dummyAddMapItem, dummyAddMapItem, dummyAddMapItem,    \
        dummyAddMapItem, dummyAddMapItem, dummyAddMapItem, dummyAddMapItem,    \
        dummyAddMapItem, dummyAddMapItem, dummyAddMapItem, dummyAddMapItem,    \
        dummyAddMapItem, dummyAddMapItem, dummyAddMapItem, dummyAddMapItem,    \
        dummyAddMapItem, dummyAddMapItem, dummyAddMapItem);

#define IMPLE_INIT_TUPLE_7(CLASS, M1, M2, M3, M4, M5, M6, M7)                  \
    std::function<decltype(M1)()> getobj1 =                                    \
        std::bind(&CLASS::__ReflectGet##M1, this);                             \
    std::function<decltype(M2)()> getobj2 =                                    \
        std::bind(&CLASS::__ReflectGet##M2, this);                             \
    std::function<decltype(M3)()> getobj3 =                                    \
        std::bind(&CLASS::__ReflectGet##M3, this);                             \
    std::function<decltype(M4)()> getobj4 =                                    \
        std::bind(&CLASS::__ReflectGet##M4, this);                             \
    std::function<decltype(M5)()> getobj5 =                                    \
        std::bind(&CLASS::__ReflectGet##M5, this);                             \
    std::function<decltype(M6)()> getobj6 =                                    \
        std::bind(&CLASS::__ReflectGet##M6, this);                             \
    std::function<decltype(M7)()> getobj7 =                                    \
        std::bind(&CLASS::__ReflectGet##M7, this);                             \
    std::function<void()> createobj1 =                                         \
        std::bind(&CLASS::__ReflectCreate##M1, this);                          \
    std::function<void()> createobj2 =                                         \
        std::bind(&CLASS::__ReflectCreate##M2, this);                          \
    std::function<void()> createobj3 =                                         \
        std::bind(&CLASS::__ReflectCreate##M3, this);                          \
    std::function<void()> createobj4 =                                         \
        std::bind(&CLASS::__ReflectCreate##M4, this);                          \
    std::function<void()> createobj5 =                                         \
        std::bind(&CLASS::__ReflectCreate##M5, this);                          \
    std::function<void()> createobj6 =                                         \
        std::bind(&CLASS::__ReflectCreate##M6, this);                          \
    std::function<void()> createobj7 =                                         \
        std::bind(&CLASS::__ReflectCreate##M7, this);                          \
    std::function<Object()> genItemObj1 =                                      \
        std::bind(&CLASS::__ReflectCreateListMember##M1, this);                \
    std::function<Object()> genItemObj2 =                                      \
        std::bind(&CLASS::__ReflectCreateListMember##M2, this);                \
    std::function<Object()> genItemObj3 =                                      \
        std::bind(&CLASS::__ReflectCreateListMember##M3, this);                \
    std::function<Object()> genItemObj4 =                                      \
        std::bind(&CLASS::__ReflectCreateListMember##M4, this);                \
    std::function<Object()> genItemObj5 =                                      \
        std::bind(&CLASS::__ReflectCreateListMember##M5, this);                \
    std::function<Object()> genItemObj6 =                                      \
        std::bind(&CLASS::__ReflectCreateListMember##M6, this);                \
    std::function<Object()> genItemObj7 =                                      \
        std::bind(&CLASS::__ReflectCreateListMember##M7, this);                \
    std::function<Object(int)> getItemObj1 = std::bind(                        \
        &CLASS::__ReflectGetListItem##M1, this, std::placeholders::_1);        \
    std::function<Object(int)> getItemObj2 = std::bind(                        \
        &CLASS::__ReflectGetListItem##M2, this, std::placeholders::_1);        \
    std::function<Object(int)> getItemObj3 = std::bind(                        \
        &CLASS::__ReflectGetListItem##M3, this, std::placeholders::_1);        \
    std::function<Object(int)> getItemObj4 = std::bind(                        \
        &CLASS::__ReflectGetListItem##M4, this, std::placeholders::_1);        \
    std::function<Object(int)> getItemObj5 = std::bind(                        \
        &CLASS::__ReflectGetListItem##M5, this, std::placeholders::_1);        \
    std::function<Object(int)> getItemObj6 = std::bind(                        \
        &CLASS::__ReflectGetListItem##M6, this, std::placeholders::_1);        \
    std::function<Object(int)> getItemObj7 = std::bind(                        \
        &CLASS::__ReflectGetListItem##M7, this, std::placeholders::_1);        \
    std::function<int()> getContainerSize1 =                                   \
        std::bind(&CLASS::__ReflectGetContainerSize##M1, this);                \
    std::function<int()> getContainerSize2 =                                   \
        std::bind(&CLASS::__ReflectGetContainerSize##M2, this);                \
    std::function<int()> getContainerSize3 =                                   \
        std::bind(&CLASS::__ReflectGetContainerSize##M3, this);                \
    std::function<int()> getContainerSize4 =                                   \
        std::bind(&CLASS::__ReflectGetContainerSize##M4, this);                \
    std::function<int()> getContainerSize5 =                                   \
        std::bind(&CLASS::__ReflectGetContainerSize##M5, this);                \
    std::function<int()> getContainerSize6 =                                   \
        std::bind(&CLASS::__ReflectGetContainerSize##M6, this);                \
    std::function<int()> getContainerSize7 =                                   \
        std::bind(&CLASS::__ReflectGetContainerSize##M7, this);                \
    std::function<Pair<Object, Object>()> createMapObj1 =              \
        std::bind(&CLASS::__ReflectCreateMapMember##M1, this);                 \
    std::function<ArrayList<Pair<Object, Object>>()> getMapItems1 =    \
        std::bind(&CLASS::__ReflectGetMapItems##M1, this);                     \
    std::function<Pair<Object, Object>()> createMapObj2 =              \
        std::bind(&CLASS::__ReflectCreateMapMember##M2, this);                 \
    std::function<ArrayList<Pair<Object, Object>>()> getMapItems2 =    \
        std::bind(&CLASS::__ReflectGetMapItems##M2, this);                     \
    std::function<Pair<Object, Object>()> createMapObj3 =              \
        std::bind(&CLASS::__ReflectCreateMapMember##M3, this);                 \
    std::function<ArrayList<Pair<Object, Object>>()> getMapItems3 =    \
        std::bind(&CLASS::__ReflectGetMapItems##M3, this);                     \
    std::function<Pair<Object, Object>()> createMapObj4 =              \
        std::bind(&CLASS::__ReflectCreateMapMember##M4, this);                 \
    std::function<ArrayList<Pair<Object, Object>>()> getMapItems4 =    \
        std::bind(&CLASS::__ReflectGetMapItems##M4, this);                     \
    std::function<Pair<Object, Object>()> createMapObj5 =              \
        std::bind(&CLASS::__ReflectCreateMapMember##M5, this);                 \
    std::function<ArrayList<Pair<Object, Object>>()> getMapItems5 =    \
        std::bind(&CLASS::__ReflectGetMapItems##M5, this);                     \
    std::function<Pair<Object, Object>()> createMapObj6 =              \
        std::bind(&CLASS::__ReflectCreateMapMember##M6, this);                 \
    std::function<ArrayList<Pair<Object, Object>>()> getMapItems6 =    \
        std::bind(&CLASS::__ReflectGetMapItems##M6, this);                     \
    std::function<Pair<Object, Object>()> createMapObj7 =              \
        std::bind(&CLASS::__ReflectCreateMapMember##M7, this);                 \
    std::function<ArrayList<Pair<Object, Object>>()> getMapItems7 =    \
        std::bind(&CLASS::__ReflectGetMapItems##M7, this);                     \
    std::function<void(Object)> addListItem = std::bind(                       \
        &CLASS::__ReflectAddListItem##M1, this, std::placeholders::_1);        \
    std::function<void(Object, Object)> addMapItem =                           \
        std::bind(&CLASS::__ReflectAddMapItem##M1, this,                       \
                  std::placeholders::_1, std::placeholders::_2);               \
    std::function<void(Object)> addListItem2 = std::bind(                      \
        &CLASS::__ReflectAddListItem##M2, this, std::placeholders::_1);        \
    std::function<void(Object, Object)> addMapItem2 =                          \
        std::bind(&CLASS::__ReflectAddMapItem##M2, this,                       \
                  std::placeholders::_1, std::placeholders::_2);               \
    std::function<void(Object)> addListItem3 = std::bind(                      \
        &CLASS::__ReflectAddListItem##M3, this, std::placeholders::_1);        \
    std::function<void(Object, Object)> addMapItem3 =                          \
        std::bind(&CLASS::__ReflectAddMapItem##M3, this,                       \
                  std::placeholders::_1, std::placeholders::_2);               \
    std::function<void(Object)> addListItem4 = std::bind(                      \
        &CLASS::__ReflectAddListItem##M4, this, std::placeholders::_1);        \
    std::function<void(Object, Object)> addMapItem4 =                          \
        std::bind(&CLASS::__ReflectAddMapItem##M4, this,                       \
                  std::placeholders::_1, std::placeholders::_2);               \
    std::function<void(Object)> addListItem5 = std::bind(                      \
        &CLASS::__ReflectAddListItem##M5, this, std::placeholders::_1);        \
    std::function<void(Object, Object)> addMapItem5 =                          \
        std::bind(&CLASS::__ReflectAddMapItem##M5, this,                       \
                  std::placeholders::_1, std::placeholders::_2);               \
    std::function<void(Object)> addListItem6 = std::bind(                      \
        &CLASS::__ReflectAddListItem##M6, this, std::placeholders::_1);        \
    std::function<void(Object, Object)> addMapItem6 =                          \
        std::bind(&CLASS::__ReflectAddMapItem##M6, this,                       \
                  std::placeholders::_1, std::placeholders::_2);               \
    std::function<void(Object)> addListItem7 = std::bind(                      \
        &CLASS::__ReflectAddListItem##M7, this, std::placeholders::_1);        \
    std::function<void(Object, Object)> addMapItem7 =                          \
        std::bind(&CLASS::__ReflectAddMapItem##M7, this,                       \
                  std::placeholders::_1, std::placeholders::_2);               \
    getFuncTuple = std::make_tuple(                                            \
        getobj1, getobj2, getobj3, getobj4, getobj5, getobj6, getobj7,         \
        dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj,  \
        dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj,  \
        dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj,  \
        dummyobj, dummyobj, dummyobj, dummyobj);                               \
    createFuncTuple = std::make_tuple(                                         \
        createobj1, createobj2, createobj3, createobj4, createobj5,            \
        createobj6, createobj7, dummyobj, dummyobj, dummyobj, dummyobj,        \
        dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj,  \
        dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj,  \
        dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj); \
    createListItemFuncTuple = std::make_tuple(                                 \
        genItemObj1, genItemObj2, genItemObj3, genItemObj4, genItemObj5,       \
        genItemObj6, genItemObj7, dummycreateobj, dummycreateobj,              \
        dummycreateobj, dummycreateobj, dummycreateobj, dummycreateobj,        \
        dummycreateobj, dummycreateobj, dummycreateobj, dummycreateobj,        \
        dummycreateobj, dummycreateobj, dummycreateobj, dummycreateobj,        \
        dummycreateobj, dummycreateobj, dummycreateobj, dummycreateobj,        \
        dummycreateobj, dummycreateobj, dummycreateobj, dummycreateobj,        \
        dummycreateobj, dummycreateobj, dummycreateobj);                       \
    getListItemFuncTuple = std::make_tuple(                                    \
        getItemObj1, getItemObj2, getItemObj3, getItemObj4, getItemObj5,       \
        getItemObj6, getItemObj7, dummyligobj, dummyligobj, dummyligobj,       \
        dummyligobj, dummyligobj, dummyligobj, dummyligobj, dummyligobj,       \
        dummyligobj, dummyligobj, dummyligobj, dummyligobj, dummyligobj,       \
        dummyligobj, dummyligobj, dummyligobj, dummyligobj, dummyligobj,       \
        dummyligobj, dummyligobj, dummyligobj, dummyligobj, dummyligobj,       \
        dummyligobj, dummyligobj);                                             \
    getContainerSizeFuncTuple = std::make_tuple(                               \
        getContainerSize1, getContainerSize2, getContainerSize3,               \
        getContainerSize4, getContainerSize5, getContainerSize6,               \
        getContainerSize7, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj,   \
        dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj,  \
        dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj,  \
        dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj);           \
    createMapItemFuncTuple = std::make_tuple(                                  \
        createMapObj1, createMapObj2, createMapObj3, createMapObj4,            \
        createMapObj5, createMapObj6, createMapObj7, dummycreateMapItem,       \
        dummycreateMapItem, dummycreateMapItem, dummycreateMapItem,            \
        dummycreateMapItem, dummycreateMapItem, dummycreateMapItem,            \
        dummycreateMapItem, dummycreateMapItem, dummycreateMapItem,            \
        dummycreateMapItem, dummycreateMapItem, dummycreateMapItem,            \
        dummycreateMapItem, dummycreateMapItem, dummycreateMapItem,            \
        dummycreateMapItem, dummycreateMapItem, dummycreateMapItem,            \
        dummycreateMapItem, dummycreateMapItem, dummycreateMapItem,            \
        dummycreateMapItem, dummycreateMapItem, dummycreateMapItem);           \
    getMapItemsFuncTuple = std::make_tuple(                                    \
        getMapItems1, getMapItems2, getMapItems3, getMapItems4, getMapItems5,  \
        getMapItems6, getMapItems7, dummygetMapItems, dummygetMapItems,        \
        dummygetMapItems, dummygetMapItems, dummygetMapItems,                  \
        dummygetMapItems, dummygetMapItems, dummygetMapItems,                  \
        dummygetMapItems, dummygetMapItems, dummygetMapItems,                  \
        dummygetMapItems, dummygetMapItems, dummygetMapItems,                  \
        dummygetMapItems, dummygetMapItems, dummygetMapItems,                  \
        dummygetMapItems, dummygetMapItems, dummygetMapItems,                  \
        dummygetMapItems, dummygetMapItems, dummygetMapItems,                  \
        dummygetMapItems, dummygetMapItems);                                   \
    addListItemFuncTuple = std::make_tuple(                                    \
        addListItem, addListItem2, addListItem3, addListItem4, addListItem5,   \
        addListItem6, addListItem7, dummyAddListItem, dummyAddListItem,        \
        dummyAddListItem, dummyAddListItem, dummyAddListItem,                  \
        dummyAddListItem, dummyAddListItem, dummyAddListItem,                  \
        dummyAddListItem, dummyAddListItem, dummyAddListItem,                  \
        dummyAddListItem, dummyAddListItem, dummyAddListItem,                  \
        dummyAddListItem, dummyAddListItem, dummyAddListItem,                  \
        dummyAddListItem, dummyAddListItem, dummyAddListItem,                  \
        dummyAddListItem, dummyAddListItem, dummyAddListItem,                  \
        dummyAddListItem, dummyAddListItem);                                   \
    addMapItemFuncTuple = std::make_tuple(                                     \
        addMapItem, addMapItem2, addMapItem3, addMapItem4, addMapItem5,        \
        addMapItem6, addMapItem7, dummyAddMapItem, dummyAddMapItem,            \
        dummyAddMapItem, dummyAddMapItem, dummyAddMapItem, dummyAddMapItem,    \
        dummyAddMapItem, dummyAddMapItem, dummyAddMapItem, dummyAddMapItem,    \
        dummyAddMapItem, dummyAddMapItem, dummyAddMapItem, dummyAddMapItem,    \
        dummyAddMapItem, dummyAddMapItem, dummyAddMapItem, dummyAddMapItem,    \
        dummyAddMapItem, dummyAddMapItem, dummyAddMapItem, dummyAddMapItem,    \
        dummyAddMapItem, dummyAddMapItem, dummyAddMapItem);

#define IMPLE_INIT_TUPLE_8(CLASS, M1, M2, M3, M4, M5, M6, M7, M8)              \
    std::function<decltype(M1)()> getobj1 =                                    \
        std::bind(&CLASS::__ReflectGet##M1, this);                             \
    std::function<decltype(M2)()> getobj2 =                                    \
        std::bind(&CLASS::__ReflectGet##M2, this);                             \
    std::function<decltype(M3)()> getobj3 =                                    \
        std::bind(&CLASS::__ReflectGet##M3, this);                             \
    std::function<decltype(M4)()> getobj4 =                                    \
        std::bind(&CLASS::__ReflectGet##M4, this);                             \
    std::function<decltype(M5)()> getobj5 =                                    \
        std::bind(&CLASS::__ReflectGet##M5, this);                             \
    std::function<decltype(M6)()> getobj6 =                                    \
        std::bind(&CLASS::__ReflectGet##M6, this);                             \
    std::function<decltype(M7)()> getobj7 =                                    \
        std::bind(&CLASS::__ReflectGet##M7, this);                             \
    std::function<decltype(M8)()> getobj8 =                                    \
        std::bind(&CLASS::__ReflectGet##M8, this);                             \
    std::function<void()> createobj1 =                                         \
        std::bind(&CLASS::__ReflectCreate##M1, this);                          \
    std::function<void()> createobj2 =                                         \
        std::bind(&CLASS::__ReflectCreate##M2, this);                          \
    std::function<void()> createobj3 =                                         \
        std::bind(&CLASS::__ReflectCreate##M3, this);                          \
    std::function<void()> createobj4 =                                         \
        std::bind(&CLASS::__ReflectCreate##M4, this);                          \
    std::function<void()> createobj5 =                                         \
        std::bind(&CLASS::__ReflectCreate##M5, this);                          \
    std::function<void()> createobj6 =                                         \
        std::bind(&CLASS::__ReflectCreate##M6, this);                          \
    std::function<void()> createobj7 =                                         \
        std::bind(&CLASS::__ReflectCreate##M7, this);                          \
    std::function<void()> createobj8 =                                         \
        std::bind(&CLASS::__ReflectCreate##M8, this);                          \
    std::function<Object()> genItemObj1 =                                      \
        std::bind(&CLASS::__ReflectCreateListMember##M1, this);                \
    std::function<Object()> genItemObj2 =                                      \
        std::bind(&CLASS::__ReflectCreateListMember##M2, this);                \
    std::function<Object()> genItemObj3 =                                      \
        std::bind(&CLASS::__ReflectCreateListMember##M3, this);                \
    std::function<Object()> genItemObj4 =                                      \
        std::bind(&CLASS::__ReflectCreateListMember##M4, this);                \
    std::function<Object()> genItemObj5 =                                      \
        std::bind(&CLASS::__ReflectCreateListMember##M5, this);                \
    std::function<Object()> genItemObj6 =                                      \
        std::bind(&CLASS::__ReflectCreateListMember##M6, this);                \
    std::function<Object()> genItemObj7 =                                      \
        std::bind(&CLASS::__ReflectCreateListMember##M7, this);                \
    std::function<Object()> genItemObj8 =                                      \
        std::bind(&CLASS::__ReflectCreateListMember##M8, this);                \
    std::function<Object(int)> getItemObj1 = std::bind(                        \
        &CLASS::__ReflectGetListItem##M1, this, std::placeholders::_1);        \
    std::function<Object(int)> getItemObj2 = std::bind(                        \
        &CLASS::__ReflectGetListItem##M2, this, std::placeholders::_1);        \
    std::function<Object(int)> getItemObj3 = std::bind(                        \
        &CLASS::__ReflectGetListItem##M3, this, std::placeholders::_1);        \
    std::function<Object(int)> getItemObj4 = std::bind(                        \
        &CLASS::__ReflectGetListItem##M4, this, std::placeholders::_1);        \
    std::function<Object(int)> getItemObj5 = std::bind(                        \
        &CLASS::__ReflectGetListItem##M5, this, std::placeholders::_1);        \
    std::function<Object(int)> getItemObj6 = std::bind(                        \
        &CLASS::__ReflectGetListItem##M6, this, std::placeholders::_1);        \
    std::function<Object(int)> getItemObj7 = std::bind(                        \
        &CLASS::__ReflectGetListItem##M7, this, std::placeholders::_1);        \
    std::function<Object(int)> getItemObj8 = std::bind(                        \
        &CLASS::__ReflectGetListItem##M8, this, std::placeholders::_1);        \
    std::function<int()> getContainerSize1 =                                   \
        std::bind(&CLASS::__ReflectGetContainerSize##M1, this);                \
    std::function<int()> getContainerSize2 =                                   \
        std::bind(&CLASS::__ReflectGetContainerSize##M2, this);                \
    std::function<int()> getContainerSize3 =                                   \
        std::bind(&CLASS::__ReflectGetContainerSize##M3, this);                \
    std::function<int()> getContainerSize4 =                                   \
        std::bind(&CLASS::__ReflectGetContainerSize##M4, this);                \
    std::function<int()> getContainerSize5 =                                   \
        std::bind(&CLASS::__ReflectGetContainerSize##M5, this);                \
    std::function<int()> getContainerSize6 =                                   \
        std::bind(&CLASS::__ReflectGetContainerSize##M6, this);                \
    std::function<int()> getContainerSize7 =                                   \
        std::bind(&CLASS::__ReflectGetContainerSize##M7, this);                \
    std::function<int()> getContainerSize8 =                                   \
        std::bind(&CLASS::__ReflectGetContainerSize##M8, this);                \
    std::function<Pair<Object, Object>()> createMapObj1 =              \
        std::bind(&CLASS::__ReflectCreateMapMember##M1, this);                 \
    std::function<ArrayList<Pair<Object, Object>>()> getMapItems1 =    \
        std::bind(&CLASS::__ReflectGetMapItems##M1, this);                     \
    std::function<Pair<Object, Object>()> createMapObj2 =              \
        std::bind(&CLASS::__ReflectCreateMapMember##M2, this);                 \
    std::function<ArrayList<Pair<Object, Object>>()> getMapItems2 =    \
        std::bind(&CLASS::__ReflectGetMapItems##M2, this);                     \
    std::function<Pair<Object, Object>()> createMapObj3 =              \
        std::bind(&CLASS::__ReflectCreateMapMember##M3, this);                 \
    std::function<ArrayList<Pair<Object, Object>>()> getMapItems3 =    \
        std::bind(&CLASS::__ReflectGetMapItems##M3, this);                     \
    std::function<Pair<Object, Object>()> createMapObj4 =              \
        std::bind(&CLASS::__ReflectCreateMapMember##M4, this);                 \
    std::function<ArrayList<Pair<Object, Object>>()> getMapItems4 =    \
        std::bind(&CLASS::__ReflectGetMapItems##M4, this);                     \
    std::function<Pair<Object, Object>()> createMapObj5 =              \
        std::bind(&CLASS::__ReflectCreateMapMember##M5, this);                 \
    std::function<ArrayList<Pair<Object, Object>>()> getMapItems5 =    \
        std::bind(&CLASS::__ReflectGetMapItems##M5, this);                     \
    std::function<Pair<Object, Object>()> createMapObj6 =              \
        std::bind(&CLASS::__ReflectCreateMapMember##M6, this);                 \
    std::function<ArrayList<Pair<Object, Object>>()> getMapItems6 =    \
        std::bind(&CLASS::__ReflectGetMapItems##M6, this);                     \
    std::function<Pair<Object, Object>()> createMapObj7 =              \
        std::bind(&CLASS::__ReflectCreateMapMember##M7, this);                 \
    std::function<ArrayList<Pair<Object, Object>>()> getMapItems7 =    \
        std::bind(&CLASS::__ReflectGetMapItems##M7, this);                     \
    std::function<Pair<Object, Object>()> createMapObj8 =              \
        std::bind(&CLASS::__ReflectCreateMapMember##M8, this);                 \
    std::function<ArrayList<Pair<Object, Object>>()> getMapItems8 =    \
        std::bind(&CLASS::__ReflectGetMapItems##M8, this);                     \
    std::function<void(Object)> addListItem = std::bind(                       \
        &CLASS::__ReflectAddListItem##M1, this, std::placeholders::_1);        \
    std::function<void(Object, Object)> addMapItem =                           \
        std::bind(&CLASS::__ReflectAddMapItem##M1, this,                       \
                  std::placeholders::_1, std::placeholders::_2);               \
    std::function<void(Object)> addListItem2 = std::bind(                      \
        &CLASS::__ReflectAddListItem##M2, this, std::placeholders::_1);        \
    std::function<void(Object, Object)> addMapItem2 =                          \
        std::bind(&CLASS::__ReflectAddMapItem##M2, this,                       \
                  std::placeholders::_1, std::placeholders::_2);               \
    std::function<void(Object)> addListItem3 = std::bind(                      \
        &CLASS::__ReflectAddListItem##M3, this, std::placeholders::_1);        \
    std::function<void(Object, Object)> addMapItem3 =                          \
        std::bind(&CLASS::__ReflectAddMapItem##M3, this,                       \
                  std::placeholders::_1, std::placeholders::_2);               \
    std::function<void(Object)> addListItem4 = std::bind(                      \
        &CLASS::__ReflectAddListItem##M4, this, std::placeholders::_1);        \
    std::function<void(Object, Object)> addMapItem4 =                          \
        std::bind(&CLASS::__ReflectAddMapItem##M4, this,                       \
                  std::placeholders::_1, std::placeholders::_2);               \
    std::function<void(Object)> addListItem5 = std::bind(                      \
        &CLASS::__ReflectAddListItem##M5, this, std::placeholders::_1);        \
    std::function<void(Object, Object)> addMapItem5 =                          \
        std::bind(&CLASS::__ReflectAddMapItem##M5, this,                       \
                  std::placeholders::_1, std::placeholders::_2);               \
    std::function<void(Object)> addListItem6 = std::bind(                      \
        &CLASS::__ReflectAddListItem##M6, this, std::placeholders::_1);        \
    std::function<void(Object, Object)> addMapItem6 =                          \
        std::bind(&CLASS::__ReflectAddMapItem##M6, this,                       \
                  std::placeholders::_1, std::placeholders::_2);               \
    std::function<void(Object)> addListItem7 = std::bind(                      \
        &CLASS::__ReflectAddListItem##M7, this, std::placeholders::_1);        \
    std::function<void(Object, Object)> addMapItem7 =                          \
        std::bind(&CLASS::__ReflectAddMapItem##M7, this,                       \
                  std::placeholders::_1, std::placeholders::_2);               \
    std::function<void(Object)> addListItem8 = std::bind(                      \
        &CLASS::__ReflectAddListItem##M8, this, std::placeholders::_1);        \
    std::function<void(Object, Object)> addMapItem8 =                          \
        std::bind(&CLASS::__ReflectAddMapItem##M8, this,                       \
                  std::placeholders::_1, std::placeholders::_2);               \
    getFuncTuple = std::make_tuple(                                            \
        getobj1, getobj2, getobj3, getobj4, getobj5, getobj6, getobj7,         \
        getobj8, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj,   \
        dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj,  \
        dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj,  \
        dummyobj, dummyobj, dummyobj, dummyobj);                               \
    createFuncTuple = std::make_tuple(                                         \
        createobj1, createobj2, createobj3, createobj4, createobj5,            \
        createobj6, createobj7, createobj8, dummyobj, dummyobj, dummyobj,      \
        dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj,  \
        dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj,  \
        dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj); \
    createListItemFuncTuple = std::make_tuple(                                 \
        genItemObj1, genItemObj2, genItemObj3, genItemObj4, genItemObj5,       \
        genItemObj6, genItemObj7, genItemObj8, dummycreateobj, dummycreateobj, \
        dummycreateobj, dummycreateobj, dummycreateobj, dummycreateobj,        \
        dummycreateobj, dummycreateobj, dummycreateobj, dummycreateobj,        \
        dummycreateobj, dummycreateobj, dummycreateobj, dummycreateobj,        \
        dummycreateobj, dummycreateobj, dummycreateobj, dummycreateobj,        \
        dummycreateobj, dummycreateobj, dummycreateobj, dummycreateobj,        \
        dummycreateobj, dummycreateobj);                                       \
    getListItemFuncTuple = std::make_tuple(                                    \
        getItemObj1, getItemObj2, getItemObj3, getItemObj4, getItemObj5,       \
        getItemObj6, getItemObj7, getItemObj8, dummyligobj, dummyligobj,       \
        dummyligobj, dummyligobj, dummyligobj, dummyligobj, dummyligobj,       \
        dummyligobj, dummyligobj, dummyligobj, dummyligobj, dummyligobj,       \
        dummyligobj, dummyligobj, dummyligobj, dummyligobj, dummyligobj,       \
        dummyligobj, dummyligobj, dummyligobj, dummyligobj, dummyligobj,       \
        dummyligobj, dummyligobj);                                             \
    getContainerSizeFuncTuple = std::make_tuple(                               \
        getContainerSize1, getContainerSize2, getContainerSize3,               \
        getContainerSize4, getContainerSize5, getContainerSize6,               \
        getContainerSize7, getContainerSize8, dummyobj, dummyobj, dummyobj,    \
        dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj,  \
        dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj,  \
        dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj); \
    createMapItemFuncTuple = std::make_tuple(                                  \
        createMapObj1, createMapObj2, createMapObj3, createMapObj4,            \
        createMapObj5, createMapObj6, createMapObj7, createMapObj8,            \
        dummycreateMapItem, dummycreateMapItem, dummycreateMapItem,            \
        dummycreateMapItem, dummycreateMapItem, dummycreateMapItem,            \
        dummycreateMapItem, dummycreateMapItem, dummycreateMapItem,            \
        dummycreateMapItem, dummycreateMapItem, dummycreateMapItem,            \
        dummycreateMapItem, dummycreateMapItem, dummycreateMapItem,            \
        dummycreateMapItem, dummycreateMapItem, dummycreateMapItem,            \
        dummycreateMapItem, dummycreateMapItem, dummycreateMapItem,            \
        dummycreateMapItem, dummycreateMapItem, dummycreateMapItem);           \
    getMapItemsFuncTuple = std::make_tuple(                                    \
        getMapItems1, getMapItems2, getMapItems3, getMapItems4, getMapItems5,  \
        getMapItems6, getMapItems7, getMapItems8, dummygetMapItems,            \
        dummygetMapItems, dummygetMapItems, dummygetMapItems,                  \
        dummygetMapItems, dummygetMapItems, dummygetMapItems,                  \
        dummygetMapItems, dummygetMapItems, dummygetMapItems,                  \
        dummygetMapItems, dummygetMapItems, dummygetMapItems,                  \
        dummygetMapItems, dummygetMapItems, dummygetMapItems,                  \
        dummygetMapItems, dummygetMapItems, dummygetMapItems,                  \
        dummygetMapItems, dummygetMapItems, dummygetMapItems,                  \
        dummygetMapItems, dummygetMapItems);                                   \
    addListItemFuncTuple = std::make_tuple(                                    \
        addListItem, addListItem2, addListItem3, addListItem4, addListItem5,   \
        addListItem6, addListItem7, addListItem8, dummyAddListItem,            \
        dummyAddListItem, dummyAddListItem, dummyAddListItem,                  \
        dummyAddListItem, dummyAddListItem, dummyAddListItem,                  \
        dummyAddListItem, dummyAddListItem, dummyAddListItem,                  \
        dummyAddListItem, dummyAddListItem, dummyAddListItem,                  \
        dummyAddListItem, dummyAddListItem, dummyAddListItem,                  \
        dummyAddListItem, dummyAddListItem, dummyAddListItem,                  \
        dummyAddListItem, dummyAddListItem, dummyAddListItem,                  \
        dummyAddListItem, dummyAddListItem);                                   \
    addMapItemFuncTuple = std::make_tuple(                                     \
        addMapItem, addMapItem2, addMapItem3, addMapItem4, addMapItem5,        \
        addMapItem6, addMapItem7, addMapItem8, dummyAddMapItem,                \
        dummyAddMapItem, dummyAddMapItem, dummyAddMapItem, dummyAddMapItem,    \
        dummyAddMapItem, dummyAddMapItem, dummyAddMapItem, dummyAddMapItem,    \
        dummyAddMapItem, dummyAddMapItem, dummyAddMapItem, dummyAddMapItem,    \
        dummyAddMapItem, dummyAddMapItem, dummyAddMapItem, dummyAddMapItem,    \
        dummyAddMapItem, dummyAddMapItem, dummyAddMapItem, dummyAddMapItem,    \
        dummyAddMapItem, dummyAddMapItem, dummyAddMapItem);

#define IMPLE_INIT_TUPLE_9(CLASS, M1, M2, M3, M4, M5, M6, M7, M8, M9)          \
    std::function<decltype(M1)()> getobj1 =                                    \
        std::bind(&CLASS::__ReflectGet##M1, this);                             \
    std::function<decltype(M2)()> getobj2 =                                    \
        std::bind(&CLASS::__ReflectGet##M2, this);                             \
    std::function<decltype(M3)()> getobj3 =                                    \
        std::bind(&CLASS::__ReflectGet##M3, this);                             \
    std::function<decltype(M4)()> getobj4 =                                    \
        std::bind(&CLASS::__ReflectGet##M4, this);                             \
    std::function<decltype(M5)()> getobj5 =                                    \
        std::bind(&CLASS::__ReflectGet##M5, this);                             \
    std::function<decltype(M6)()> getobj6 =                                    \
        std::bind(&CLASS::__ReflectGet##M6, this);                             \
    std::function<decltype(M7)()> getobj7 =                                    \
        std::bind(&CLASS::__ReflectGet##M7, this);                             \
    std::function<decltype(M8)()> getobj8 =                                    \
        std::bind(&CLASS::__ReflectGet##M8, this);                             \
    std::function<decltype(M9)()> getobj9 =                                    \
        std::bind(&CLASS::__ReflectGet##M9, this);                             \
    std::function<void()> createobj1 =                                         \
        std::bind(&CLASS::__ReflectCreate##M1, this);                          \
    std::function<void()> createobj2 =                                         \
        std::bind(&CLASS::__ReflectCreate##M2, this);                          \
    std::function<void()> createobj3 =                                         \
        std::bind(&CLASS::__ReflectCreate##M3, this);                          \
    std::function<void()> createobj4 =                                         \
        std::bind(&CLASS::__ReflectCreate##M4, this);                          \
    std::function<void()> createobj5 =                                         \
        std::bind(&CLASS::__ReflectCreate##M5, this);                          \
    std::function<void()> createobj6 =                                         \
        std::bind(&CLASS::__ReflectCreate##M6, this);                          \
    std::function<void()> createobj7 =                                         \
        std::bind(&CLASS::__ReflectCreate##M7, this);                          \
    std::function<void()> createobj8 =                                         \
        std::bind(&CLASS::__ReflectCreate##M8, this);                          \
    std::function<void()> createobj9 =                                         \
        std::bind(&CLASS::__ReflectCreate##M9, this);                          \
    std::function<Object()> genItemObj1 =                                      \
        std::bind(&CLASS::__ReflectCreateListMember##M1, this);                \
    std::function<Object()> genItemObj2 =                                      \
        std::bind(&CLASS::__ReflectCreateListMember##M2, this);                \
    std::function<Object()> genItemObj3 =                                      \
        std::bind(&CLASS::__ReflectCreateListMember##M3, this);                \
    std::function<Object()> genItemObj4 =                                      \
        std::bind(&CLASS::__ReflectCreateListMember##M4, this);                \
    std::function<Object()> genItemObj5 =                                      \
        std::bind(&CLASS::__ReflectCreateListMember##M5, this);                \
    std::function<Object()> genItemObj6 =                                      \
        std::bind(&CLASS::__ReflectCreateListMember##M6, this);                \
    std::function<Object()> genItemObj7 =                                      \
        std::bind(&CLASS::__ReflectCreateListMember##M7, this);                \
    std::function<Object()> genItemObj8 =                                      \
        std::bind(&CLASS::__ReflectCreateListMember##M8, this);                \
    std::function<Object()> genItemObj9 =                                      \
        std::bind(&CLASS::__ReflectCreateListMember##M9, this);                \
    std::function<Object(int)> getItemObj1 = std::bind(                        \
        &CLASS::__ReflectGetListItem##M1, this, std::placeholders::_1);        \
    std::function<Object(int)> getItemObj2 = std::bind(                        \
        &CLASS::__ReflectGetListItem##M2, this, std::placeholders::_1);        \
    std::function<Object(int)> getItemObj3 = std::bind(                        \
        &CLASS::__ReflectGetListItem##M3, this, std::placeholders::_1);        \
    std::function<Object(int)> getItemObj4 = std::bind(                        \
        &CLASS::__ReflectGetListItem##M4, this, std::placeholders::_1);        \
    std::function<Object(int)> getItemObj5 = std::bind(                        \
        &CLASS::__ReflectGetListItem##M5, this, std::placeholders::_1);        \
    std::function<Object(int)> getItemObj6 = std::bind(                        \
        &CLASS::__ReflectGetListItem##M6, this, std::placeholders::_1);        \
    std::function<Object(int)> getItemObj7 = std::bind(                        \
        &CLASS::__ReflectGetListItem##M7, this, std::placeholders::_1);        \
    std::function<Object(int)> getItemObj8 = std::bind(                        \
        &CLASS::__ReflectGetListItem##M8, this, std::placeholders::_1);        \
    std::function<Object(int)> getItemObj9 = std::bind(                        \
        &CLASS::__ReflectGetListItem##M9, this, std::placeholders::_1);        \
    std::function<int()> getContainerSize1 =                                   \
        std::bind(&CLASS::__ReflectGetContainerSize##M1, this);                \
    std::function<int()> getContainerSize2 =                                   \
        std::bind(&CLASS::__ReflectGetContainerSize##M2, this);                \
    std::function<int()> getContainerSize3 =                                   \
        std::bind(&CLASS::__ReflectGetContainerSize##M3, this);                \
    std::function<int()> getContainerSize4 =                                   \
        std::bind(&CLASS::__ReflectGetContainerSize##M4, this);                \
    std::function<int()> getContainerSize5 =                                   \
        std::bind(&CLASS::__ReflectGetContainerSize##M5, this);                \
    std::function<int()> getContainerSize6 =                                   \
        std::bind(&CLASS::__ReflectGetContainerSize##M6, this);                \
    std::function<int()> getContainerSize7 =                                   \
        std::bind(&CLASS::__ReflectGetContainerSize##M7, this);                \
    std::function<int()> getContainerSize8 =                                   \
        std::bind(&CLASS::__ReflectGetContainerSize##M8, this);                \
    std::function<int()> getContainerSize9 =                                   \
        std::bind(&CLASS::__ReflectGetContainerSize##M9, this);                \
    std::function<Pair<Object, Object>()> createMapObj1 =              \
        std::bind(&CLASS::__ReflectCreateMapMember##M1, this);                 \
    std::function<ArrayList<Pair<Object, Object>>()> getMapItems1 =    \
        std::bind(&CLASS::__ReflectGetMapItems##M1, this);                     \
    std::function<Pair<Object, Object>()> createMapObj2 =              \
        std::bind(&CLASS::__ReflectCreateMapMember##M2, this);                 \
    std::function<ArrayList<Pair<Object, Object>>()> getMapItems2 =    \
        std::bind(&CLASS::__ReflectGetMapItems##M2, this);                     \
    std::function<Pair<Object, Object>()> createMapObj3 =              \
        std::bind(&CLASS::__ReflectCreateMapMember##M3, this);                 \
    std::function<ArrayList<Pair<Object, Object>>()> getMapItems3 =    \
        std::bind(&CLASS::__ReflectGetMapItems##M3, this);                     \
    std::function<Pair<Object, Object>()> createMapObj4 =              \
        std::bind(&CLASS::__ReflectCreateMapMember##M4, this);                 \
    std::function<ArrayList<Pair<Object, Object>>()> getMapItems4 =    \
        std::bind(&CLASS::__ReflectGetMapItems##M4, this);                     \
    std::function<Pair<Object, Object>()> createMapObj5 =              \
        std::bind(&CLASS::__ReflectCreateMapMember##M5, this);                 \
    std::function<ArrayList<Pair<Object, Object>>()> getMapItems5 =    \
        std::bind(&CLASS::__ReflectGetMapItems##M5, this);                     \
    std::function<Pair<Object, Object>()> createMapObj6 =              \
        std::bind(&CLASS::__ReflectCreateMapMember##M6, this);                 \
    std::function<ArrayList<Pair<Object, Object>>()> getMapItems6 =    \
        std::bind(&CLASS::__ReflectGetMapItems##M6, this);                     \
    std::function<Pair<Object, Object>()> createMapObj7 =              \
        std::bind(&CLASS::__ReflectCreateMapMember##M7, this);                 \
    std::function<ArrayList<Pair<Object, Object>>()> getMapItems7 =    \
        std::bind(&CLASS::__ReflectGetMapItems##M7, this);                     \
    std::function<Pair<Object, Object>()> createMapObj8 =              \
        std::bind(&CLASS::__ReflectCreateMapMember##M8, this);                 \
    std::function<ArrayList<Pair<Object, Object>>()> getMapItems8 =    \
        std::bind(&CLASS::__ReflectGetMapItems##M8, this);                     \
    std::function<Pair<Object, Object>()> createMapObj9 =              \
        std::bind(&CLASS::__ReflectCreateMapMember##M9, this);                 \
    std::function<ArrayList<Pair<Object, Object>>()> getMapItems9 =    \
        std::bind(&CLASS::__ReflectGetMapItems##M9, this);                     \
    std::function<void(Object)> addListItem = std::bind(                       \
        &CLASS::__ReflectAddListItem##M1, this, std::placeholders::_1);        \
    std::function<void(Object, Object)> addMapItem =                           \
        std::bind(&CLASS::__ReflectAddMapItem##M1, this,                       \
                  std::placeholders::_1, std::placeholders::_2);               \
    std::function<void(Object)> addListItem2 = std::bind(                      \
        &CLASS::__ReflectAddListItem##M2, this, std::placeholders::_1);        \
    std::function<void(Object, Object)> addMapItem2 =                          \
        std::bind(&CLASS::__ReflectAddMapItem##M2, this,                       \
                  std::placeholders::_1, std::placeholders::_2);               \
    std::function<void(Object)> addListItem3 = std::bind(                      \
        &CLASS::__ReflectAddListItem##M3, this, std::placeholders::_1);        \
    std::function<void(Object, Object)> addMapItem3 =                          \
        std::bind(&CLASS::__ReflectAddMapItem##M3, this,                       \
                  std::placeholders::_1, std::placeholders::_2);               \
    std::function<void(Object)> addListItem4 = std::bind(                      \
        &CLASS::__ReflectAddListItem##M4, this, std::placeholders::_1);        \
    std::function<void(Object, Object)> addMapItem4 =                          \
        std::bind(&CLASS::__ReflectAddMapItem##M4, this,                       \
                  std::placeholders::_1, std::placeholders::_2);               \
    std::function<void(Object)> addListItem5 = std::bind(                      \
        &CLASS::__ReflectAddListItem##M5, this, std::placeholders::_1);        \
    std::function<void(Object, Object)> addMapItem5 =                          \
        std::bind(&CLASS::__ReflectAddMapItem##M5, this,                       \
                  std::placeholders::_1, std::placeholders::_2);               \
    std::function<void(Object)> addListItem6 = std::bind(                      \
        &CLASS::__ReflectAddListItem##M6, this, std::placeholders::_1);        \
    std::function<void(Object, Object)> addMapItem6 =                          \
        std::bind(&CLASS::__ReflectAddMapItem##M6, this,                       \
                  std::placeholders::_1, std::placeholders::_2);               \
    std::function<void(Object)> addListItem7 = std::bind(                      \
        &CLASS::__ReflectAddListItem##M7, this, std::placeholders::_1);        \
    std::function<void(Object, Object)> addMapItem7 =                          \
        std::bind(&CLASS::__ReflectAddMapItem##M7, this,                       \
                  std::placeholders::_1, std::placeholders::_2);               \
    std::function<void(Object)> addListItem8 = std::bind(                      \
        &CLASS::__ReflectAddListItem##M8, this, std::placeholders::_1);        \
    std::function<void(Object, Object)> addMapItem8 =                          \
        std::bind(&CLASS::__ReflectAddMapItem##M8, this,                       \
                  std::placeholders::_1, std::placeholders::_2);               \
    std::function<void(Object)> addListItem9 = std::bind(                      \
        &CLASS::__ReflectAddListItem##M9, this, std::placeholders::_1);        \
    std::function<void(Object, Object)> addMapItem9 =                          \
        std::bind(&CLASS::__ReflectAddMapItem##M9, this,                       \
                  std::placeholders::_1, std::placeholders::_2);               \
    getFuncTuple = std::make_tuple(                                            \
        getobj1, getobj2, getobj3, getobj4, getobj5, getobj6, getobj7,         \
        getobj8, getobj9, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj,    \
        dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj,  \
        dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj,  \
        dummyobj, dummyobj, dummyobj, dummyobj);                               \
    createFuncTuple = std::make_tuple(                                         \
        createobj1, createobj2, createobj3, createobj4, createobj5,            \
        createobj6, createobj7, createobj8, createobj9, dummyobj, dummyobj,    \
        dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj,  \
        dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj,  \
        dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj); \
    createListItemFuncTuple = std::make_tuple(                                 \
        genItemObj1, genItemObj2, genItemObj3, genItemObj4, genItemObj5,       \
        genItemObj6, genItemObj7, genItemObj8, genItemObj9, dummycreateobj,    \
        dummycreateobj, dummycreateobj, dummycreateobj, dummycreateobj,        \
        dummycreateobj, dummycreateobj, dummycreateobj, dummycreateobj,        \
        dummycreateobj, dummycreateobj, dummycreateobj, dummycreateobj,        \
        dummycreateobj, dummycreateobj, dummycreateobj, dummycreateobj,        \
        dummycreateobj, dummycreateobj, dummycreateobj, dummycreateobj,        \
        dummycreateobj, dummycreateobj);                                       \
    getListItemFuncTuple = std::make_tuple(                                    \
        getItemObj1, getItemObj2, getItemObj3, getItemObj4, getItemObj5,       \
        getItemObj6, getItemObj7, getItemObj8, getItemObj9, dummyligobj,       \
        dummyligobj, dummyligobj, dummyligobj, dummyligobj, dummyligobj,       \
        dummyligobj, dummyligobj, dummyligobj, dummyligobj, dummyligobj,       \
        dummyligobj, dummyligobj, dummyligobj, dummyligobj, dummyligobj,       \
        dummyligobj, dummyligobj, dummyligobj, dummyligobj, dummyligobj,       \
        dummyligobj, dummyligobj);                                             \
    getContainerSizeFuncTuple = std::make_tuple(                               \
        getContainerSize1, getContainerSize2, getContainerSize3,               \
        getContainerSize4, getContainerSize5, getContainerSize6,               \
        getContainerSize7, getContainerSize8, getContainerSize9, dummyobj,     \
        dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj,  \
        dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj,  \
        dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj,  \
        dummyobj);                                                             \
    createMapItemFuncTuple = std::make_tuple(                                  \
        createMapObj1, createMapObj2, createMapObj3, createMapObj4,            \
        createMapObj5, createMapObj6, createMapObj7, createMapObj8,            \
        createMapObj9, dummycreateMapItem, dummycreateMapItem,                 \
        dummycreateMapItem, dummycreateMapItem, dummycreateMapItem,            \
        dummycreateMapItem, dummycreateMapItem, dummycreateMapItem,            \
        dummycreateMapItem, dummycreateMapItem, dummycreateMapItem,            \
        dummycreateMapItem, dummycreateMapItem, dummycreateMapItem,            \
        dummycreateMapItem, dummycreateMapItem, dummycreateMapItem,            \
        dummycreateMapItem, dummycreateMapItem, dummycreateMapItem,            \
        dummycreateMapItem, dummycreateMapItem, dummycreateMapItem);           \
    getMapItemsFuncTuple = std::make_tuple(                                    \
        getMapItems1, getMapItems2, getMapItems3, getMapItems4, getMapItems5,  \
        getMapItems6, getMapItems7, getMapItems8, getMapItems9,                \
        dummygetMapItems, dummygetMapItems, dummygetMapItems,                  \
        dummygetMapItems, dummygetMapItems, dummygetMapItems,                  \
        dummygetMapItems, dummygetMapItems, dummygetMapItems,                  \
        dummygetMapItems, dummygetMapItems, dummygetMapItems,                  \
        dummygetMapItems, dummygetMapItems, dummygetMapItems,                  \
        dummygetMapItems, dummygetMapItems, dummygetMapItems,                  \
        dummygetMapItems, dummygetMapItems, dummygetMapItems,                  \
        dummygetMapItems, dummygetMapItems);                                   \
    addListItemFuncTuple = std::make_tuple(                                    \
        addListItem, addListItem2, addListItem3, addListItem4, addListItem5,   \
        addListItem6, addListItem7, addListItem8, addListItem9,                \
        dummyAddListItem, dummyAddListItem, dummyAddListItem,                  \
        dummyAddListItem, dummyAddListItem, dummyAddListItem,                  \
        dummyAddListItem, dummyAddListItem, dummyAddListItem,                  \
        dummyAddListItem, dummyAddListItem, dummyAddListItem,                  \
        dummyAddListItem, dummyAddListItem, dummyAddListItem,                  \
        dummyAddListItem, dummyAddListItem, dummyAddListItem,                  \
        dummyAddListItem, dummyAddListItem, dummyAddListItem,                  \
        dummyAddListItem, dummyAddListItem);                                   \
    addMapItemFuncTuple = std::make_tuple(                                     \
        addMapItem, addMapItem2, addMapItem3, addMapItem4, addMapItem5,        \
        addMapItem6, addMapItem7, addMapItem8, addMapItem9, dummyAddMapItem,   \
        dummyAddMapItem, dummyAddMapItem, dummyAddMapItem, dummyAddMapItem,    \
        dummyAddMapItem, dummyAddMapItem, dummyAddMapItem, dummyAddMapItem,    \
        dummyAddMapItem, dummyAddMapItem, dummyAddMapItem, dummyAddMapItem,    \
        dummyAddMapItem, dummyAddMapItem, dummyAddMapItem, dummyAddMapItem,    \
        dummyAddMapItem, dummyAddMapItem, dummyAddMapItem, dummyAddMapItem,    \
        dummyAddMapItem, dummyAddMapItem);

#define IMPLE_INIT_TUPLE_10(CLASS, M1, M2, M3, M4, M5, M6, M7, M8, M9, M10)    \
    std::function<decltype(M1)()> getobj1 =                                    \
        std::bind(&CLASS::__ReflectGet##M1, this);                             \
    std::function<decltype(M2)()> getobj2 =                                    \
        std::bind(&CLASS::__ReflectGet##M2, this);                             \
    std::function<decltype(M3)()> getobj3 =                                    \
        std::bind(&CLASS::__ReflectGet##M3, this);                             \
    std::function<decltype(M4)()> getobj4 =                                    \
        std::bind(&CLASS::__ReflectGet##M4, this);                             \
    std::function<decltype(M5)()> getobj5 =                                    \
        std::bind(&CLASS::__ReflectGet##M5, this);                             \
    std::function<decltype(M6)()> getobj6 =                                    \
        std::bind(&CLASS::__ReflectGet##M6, this);                             \
    std::function<decltype(M7)()> getobj7 =                                    \
        std::bind(&CLASS::__ReflectGet##M7, this);                             \
    std::function<decltype(M8)()> getobj8 =                                    \
        std::bind(&CLASS::__ReflectGet##M8, this);                             \
    std::function<decltype(M9)()> getobj9 =                                    \
        std::bind(&CLASS::__ReflectGet##M9, this);                             \
    std::function<decltype(M10)()> getobj10 =                                  \
        std::bind(&CLASS::__ReflectGet##M10, this);                            \
    std::function<void()> createobj1 =                                         \
        std::bind(&CLASS::__ReflectCreate##M1, this);                          \
    std::function<void()> createobj2 =                                         \
        std::bind(&CLASS::__ReflectCreate##M2, this);                          \
    std::function<void()> createobj3 =                                         \
        std::bind(&CLASS::__ReflectCreate##M3, this);                          \
    std::function<void()> createobj4 =                                         \
        std::bind(&CLASS::__ReflectCreate##M4, this);                          \
    std::function<void()> createobj5 =                                         \
        std::bind(&CLASS::__ReflectCreate##M5, this);                          \
    std::function<void()> createobj6 =                                         \
        std::bind(&CLASS::__ReflectCreate##M6, this);                          \
    std::function<void()> createobj7 =                                         \
        std::bind(&CLASS::__ReflectCreate##M7, this);                          \
    std::function<void()> createobj8 =                                         \
        std::bind(&CLASS::__ReflectCreate##M8, this);                          \
    std::function<void()> createobj9 =                                         \
        std::bind(&CLASS::__ReflectCreate##M9, this);                          \
    std::function<void()> createobj10 =                                        \
        std::bind(&CLASS::__ReflectCreate##M10, this);                         \
    std::function<Object()> genItemObj1 =                                      \
        std::bind(&CLASS::__ReflectCreateListMember##M1, this);                \
    std::function<Object()> genItemObj2 =                                      \
        std::bind(&CLASS::__ReflectCreateListMember##M2, this);                \
    std::function<Object()> genItemObj3 =                                      \
        std::bind(&CLASS::__ReflectCreateListMember##M3, this);                \
    std::function<Object()> genItemObj4 =                                      \
        std::bind(&CLASS::__ReflectCreateListMember##M4, this);                \
    std::function<Object()> genItemObj5 =                                      \
        std::bind(&CLASS::__ReflectCreateListMember##M5, this);                \
    std::function<Object()> genItemObj6 =                                      \
        std::bind(&CLASS::__ReflectCreateListMember##M6, this);                \
    std::function<Object()> genItemObj7 =                                      \
        std::bind(&CLASS::__ReflectCreateListMember##M7, this);                \
    std::function<Object()> genItemObj8 =                                      \
        std::bind(&CLASS::__ReflectCreateListMember##M8, this);                \
    std::function<Object()> genItemObj9 =                                      \
        std::bind(&CLASS::__ReflectCreateListMember##M9, this);                \
    std::function<Object()> genItemObj10 =                                     \
        std::bind(&CLASS::__ReflectCreateListMember##M10, this);               \
    std::function<Object(int)> getItemObj1 = std::bind(                        \
        &CLASS::__ReflectGetListItem##M1, this, std::placeholders::_1);        \
    std::function<Object(int)> getItemObj2 = std::bind(                        \
        &CLASS::__ReflectGetListItem##M2, this, std::placeholders::_1);        \
    std::function<Object(int)> getItemObj3 = std::bind(                        \
        &CLASS::__ReflectGetListItem##M3, this, std::placeholders::_1);        \
    std::function<Object(int)> getItemObj4 = std::bind(                        \
        &CLASS::__ReflectGetListItem##M4, this, std::placeholders::_1);        \
    std::function<Object(int)> getItemObj5 = std::bind(                        \
        &CLASS::__ReflectGetListItem##M5, this, std::placeholders::_1);        \
    std::function<Object(int)> getItemObj6 = std::bind(                        \
        &CLASS::__ReflectGetListItem##M6, this, std::placeholders::_1);        \
    std::function<Object(int)> getItemObj7 = std::bind(                        \
        &CLASS::__ReflectGetListItem##M7, this, std::placeholders::_1);        \
    std::function<Object(int)> getItemObj8 = std::bind(                        \
        &CLASS::__ReflectGetListItem##M8, this, std::placeholders::_1);        \
    std::function<Object(int)> getItemObj9 = std::bind(                        \
        &CLASS::__ReflectGetListItem##M9, this, std::placeholders::_1);        \
    std::function<Object(int)> getItemObj10 = std::bind(                       \
        &CLASS::__ReflectGetListItem##M10, this, std::placeholders::_1);       \
    std::function<int()> getContainerSize1 =                                   \
        std::bind(&CLASS::__ReflectGetContainerSize##M1, this);                \
    std::function<int()> getContainerSize2 =                                   \
        std::bind(&CLASS::__ReflectGetContainerSize##M2, this);                \
    std::function<int()> getContainerSize3 =                                   \
        std::bind(&CLASS::__ReflectGetContainerSize##M3, this);                \
    std::function<int()> getContainerSize4 =                                   \
        std::bind(&CLASS::__ReflectGetContainerSize##M4, this);                \
    std::function<int()> getContainerSize5 =                                   \
        std::bind(&CLASS::__ReflectGetContainerSize##M5, this);                \
    std::function<int()> getContainerSize6 =                                   \
        std::bind(&CLASS::__ReflectGetContainerSize##M6, this);                \
    std::function<int()> getContainerSize7 =                                   \
        std::bind(&CLASS::__ReflectGetContainerSize##M7, this);                \
    std::function<int()> getContainerSize8 =                                   \
        std::bind(&CLASS::__ReflectGetContainerSize##M8, this);                \
    std::function<int()> getContainerSize9 =                                   \
        std::bind(&CLASS::__ReflectGetContainerSize##M9, this);                \
    std::function<int()> getContainerSize10 =                                  \
        std::bind(&CLASS::__ReflectGetContainerSize##M10, this);               \
    std::function<Pair<Object, Object>()> createMapObj1 =              \
        std::bind(&CLASS::__ReflectCreateMapMember##M1, this);                 \
    std::function<ArrayList<Pair<Object, Object>>()> getMapItems1 =    \
        std::bind(&CLASS::__ReflectGetMapItems##M1, this);                     \
    std::function<Pair<Object, Object>()> createMapObj2 =              \
        std::bind(&CLASS::__ReflectCreateMapMember##M2, this);                 \
    std::function<ArrayList<Pair<Object, Object>>()> getMapItems2 =    \
        std::bind(&CLASS::__ReflectGetMapItems##M2, this);                     \
    std::function<Pair<Object, Object>()> createMapObj3 =              \
        std::bind(&CLASS::__ReflectCreateMapMember##M3, this);                 \
    std::function<ArrayList<Pair<Object, Object>>()> getMapItems3 =    \
        std::bind(&CLASS::__ReflectGetMapItems##M3, this);                     \
    std::function<Pair<Object, Object>()> createMapObj4 =              \
        std::bind(&CLASS::__ReflectCreateMapMember##M4, this);                 \
    std::function<ArrayList<Pair<Object, Object>>()> getMapItems4 =    \
        std::bind(&CLASS::__ReflectGetMapItems##M4, this);                     \
    std::function<Pair<Object, Object>()> createMapObj5 =              \
        std::bind(&CLASS::__ReflectCreateMapMember##M5, this);                 \
    std::function<ArrayList<Pair<Object, Object>>()> getMapItems5 =    \
        std::bind(&CLASS::__ReflectGetMapItems##M5, this);                     \
    std::function<Pair<Object, Object>()> createMapObj6 =              \
        std::bind(&CLASS::__ReflectCreateMapMember##M6, this);                 \
    std::function<ArrayList<Pair<Object, Object>>()> getMapItems6 =    \
        std::bind(&CLASS::__ReflectGetMapItems##M6, this);                     \
    std::function<Pair<Object, Object>()> createMapObj7 =              \
        std::bind(&CLASS::__ReflectCreateMapMember##M7, this);                 \
    std::function<ArrayList<Pair<Object, Object>>()> getMapItems7 =    \
        std::bind(&CLASS::__ReflectGetMapItems##M7, this);                     \
    std::function<Pair<Object, Object>()> createMapObj8 =              \
        std::bind(&CLASS::__ReflectCreateMapMember##M8, this);                 \
    std::function<ArrayList<Pair<Object, Object>>()> getMapItems8 =    \
        std::bind(&CLASS::__ReflectGetMapItems##M8, this);                     \
    std::function<Pair<Object, Object>()> createMapObj9 =              \
        std::bind(&CLASS::__ReflectCreateMapMember##M9, this);                 \
    std::function<ArrayList<Pair<Object, Object>>()> getMapItems9 =    \
        std::bind(&CLASS::__ReflectGetMapItems##M9, this);                     \
    std::function<Pair<Object, Object>()> createMapObj10 =             \
        std::bind(&CLASS::__ReflectCreateMapMember##M10, this);                \
    std::function<ArrayList<Pair<Object, Object>>()> getMapItems10 =   \
        std::bind(&CLASS::__ReflectGetMapItems##M10, this);                    \
    std::function<void(Object)> addListItem = std::bind(                       \
        &CLASS::__ReflectAddListItem##M1, this, std::placeholders::_1);        \
    std::function<void(Object, Object)> addMapItem =                           \
        std::bind(&CLASS::__ReflectAddMapItem##M1, this,                       \
                  std::placeholders::_1, std::placeholders::_2);               \
    std::function<void(Object)> addListItem2 = std::bind(                      \
        &CLASS::__ReflectAddListItem##M2, this, std::placeholders::_1);        \
    std::function<void(Object, Object)> addMapItem2 =                          \
        std::bind(&CLASS::__ReflectAddMapItem##M2, this,                       \
                  std::placeholders::_1, std::placeholders::_2);               \
    std::function<void(Object)> addListItem3 = std::bind(                      \
        &CLASS::__ReflectAddListItem##M3, this, std::placeholders::_1);        \
    std::function<void(Object, Object)> addMapItem3 =                          \
        std::bind(&CLASS::__ReflectAddMapItem##M3, this,                       \
                  std::placeholders::_1, std::placeholders::_2);               \
    std::function<void(Object)> addListItem4 = std::bind(                      \
        &CLASS::__ReflectAddListItem##M4, this, std::placeholders::_1);        \
    std::function<void(Object, Object)> addMapItem4 =                          \
        std::bind(&CLASS::__ReflectAddMapItem##M4, this,                       \
                  std::placeholders::_1, std::placeholders::_2);               \
    std::function<void(Object)> addListItem5 = std::bind(                      \
        &CLASS::__ReflectAddListItem##M5, this, std::placeholders::_1);        \
    std::function<void(Object, Object)> addMapItem5 =                          \
        std::bind(&CLASS::__ReflectAddMapItem##M5, this,                       \
                  std::placeholders::_1, std::placeholders::_2);               \
    std::function<void(Object)> addListItem6 = std::bind(                      \
        &CLASS::__ReflectAddListItem##M6, this, std::placeholders::_1);        \
    std::function<void(Object, Object)> addMapItem6 =                          \
        std::bind(&CLASS::__ReflectAddMapItem##M6, this,                       \
                  std::placeholders::_1, std::placeholders::_2);               \
    std::function<void(Object)> addListItem7 = std::bind(                      \
        &CLASS::__ReflectAddListItem##M7, this, std::placeholders::_1);        \
    std::function<void(Object, Object)> addMapItem7 =                          \
        std::bind(&CLASS::__ReflectAddMapItem##M7, this,                       \
                  std::placeholders::_1, std::placeholders::_2);               \
    std::function<void(Object)> addListItem8 = std::bind(                      \
        &CLASS::__ReflectAddListItem##M8, this, std::placeholders::_1);        \
    std::function<void(Object, Object)> addMapItem8 =                          \
        std::bind(&CLASS::__ReflectAddMapItem##M8, this,                       \
                  std::placeholders::_1, std::placeholders::_2);               \
    std::function<void(Object)> addListItem9 = std::bind(                      \
        &CLASS::__ReflectAddListItem##M9, this, std::placeholders::_1);        \
    std::function<void(Object, Object)> addMapItem9 =                          \
        std::bind(&CLASS::__ReflectAddMapItem##M9, this,                       \
                  std::placeholders::_1, std::placeholders::_2);               \
    std::function<void(Object)> addListItem10 = std::bind(                     \
        &CLASS::__ReflectAddListItem##M10, this, std::placeholders::_1);       \
    std::function<void(Object, Object)> addMapItem10 =                         \
        std::bind(&CLASS::__ReflectAddMapItem##M10, this,                      \
                  std::placeholders::_1, std::placeholders::_2);               \
    getFuncTuple = std::make_tuple(                                            \
        getobj1, getobj2, getobj3, getobj4, getobj5, getobj6, getobj7,         \
        getobj8, getobj9, getobj10, dummyobj, dummyobj, dummyobj, dummyobj,    \
        dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj,  \
        dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj,  \
        dummyobj, dummyobj, dummyobj, dummyobj);                               \
    createFuncTuple = std::make_tuple(                                         \
        createobj1, createobj2, createobj3, createobj4, createobj5,            \
        createobj6, createobj7, createobj8, createobj9, createobj10, dummyobj, \
        dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj,  \
        dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj,  \
        dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj); \
    createListItemFuncTuple = std::make_tuple(                                 \
        genItemObj1, genItemObj2, genItemObj3, genItemObj4, genItemObj5,       \
        genItemObj6, genItemObj7, genItemObj8, genItemObj9, genItemObj10,      \
        dummycreateobj, dummycreateobj, dummycreateobj, dummycreateobj,        \
        dummycreateobj, dummycreateobj, dummycreateobj, dummycreateobj,        \
        dummycreateobj, dummycreateobj, dummycreateobj, dummycreateobj,        \
        dummycreateobj, dummycreateobj, dummycreateobj, dummycreateobj,        \
        dummycreateobj, dummycreateobj, dummycreateobj, dummycreateobj,        \
        dummycreateobj, dummycreateobj);                                       \
    getListItemFuncTuple = std::make_tuple(                                    \
        getItemObj1, getItemObj2, getItemObj3, getItemObj4, getItemObj5,       \
        getItemObj6, getItemObj7, getItemObj8, getItemObj9, getItemObj10,      \
        dummyligobj, dummyligobj, dummyligobj, dummyligobj, dummyligobj,       \
        dummyligobj, dummyligobj, dummyligobj, dummyligobj, dummyligobj,       \
        dummyligobj, dummyligobj, dummyligobj, dummyligobj, dummyligobj,       \
        dummyligobj, dummyligobj, dummyligobj, dummyligobj, dummyligobj,       \
        dummyligobj, dummyligobj);                                             \
    getContainerSizeFuncTuple = std::make_tuple(                               \
        getContainerSize1, getContainerSize2, getContainerSize3,               \
        getContainerSize4, getContainerSize5, getContainerSize6,               \
        getContainerSize7, getContainerSize8, getContainerSize9,               \
        getContainerSize10, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj,  \
        dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj,  \
        dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj,  \
        dummyobj, dummyobj, dummyobj);                                         \
    createMapItemFuncTuple = std::make_tuple(                                  \
        createMapObj1, createMapObj2, createMapObj3, createMapObj4,            \
        createMapObj5, createMapObj6, createMapObj7, createMapObj8,            \
        createMapObj9, createMapObj10, dummycreateMapItem, dummycreateMapItem, \
        dummycreateMapItem, dummycreateMapItem, dummycreateMapItem,            \
        dummycreateMapItem, dummycreateMapItem, dummycreateMapItem,            \
        dummycreateMapItem, dummycreateMapItem, dummycreateMapItem,            \
        dummycreateMapItem, dummycreateMapItem, dummycreateMapItem,            \
        dummycreateMapItem, dummycreateMapItem, dummycreateMapItem,            \
        dummycreateMapItem, dummycreateMapItem, dummycreateMapItem,            \
        dummycreateMapItem, dummycreateMapItem);                               \
    getMapItemsFuncTuple = std::make_tuple(                                    \
        getMapItems1, getMapItems2, getMapItems3, getMapItems4, getMapItems5,  \
        getMapItems6, getMapItems7, getMapItems8, getMapItems9, getMapItems10, \
        dummygetMapItems, dummygetMapItems, dummygetMapItems,                  \
        dummygetMapItems, dummygetMapItems, dummygetMapItems,                  \
        dummygetMapItems, dummygetMapItems, dummygetMapItems,                  \
        dummygetMapItems, dummygetMapItems, dummygetMapItems,                  \
        dummygetMapItems, dummygetMapItems, dummygetMapItems,                  \
        dummygetMapItems, dummygetMapItems, dummygetMapItems,                  \
        dummygetMapItems, dummygetMapItems, dummygetMapItems,                  \
        dummygetMapItems);                                                     \
    addListItemFuncTuple = std::make_tuple(                                    \
        addListItem, addListItem2, addListItem3, addListItem4, addListItem5,   \
        addListItem6, addListItem7, addListItem8, addListItem9, addListItem10, \
        dummyAddListItem, dummyAddListItem, dummyAddListItem,                  \
        dummyAddListItem, dummyAddListItem, dummyAddListItem,                  \
        dummyAddListItem, dummyAddListItem, dummyAddListItem,                  \
        dummyAddListItem, dummyAddListItem, dummyAddListItem,                  \
        dummyAddListItem, dummyAddListItem, dummyAddListItem,                  \
        dummyAddListItem, dummyAddListItem, dummyAddListItem,                  \
        dummyAddListItem, dummyAddListItem, dummyAddListItem,                  \
        dummyAddListItem);                                                     \
    addMapItemFuncTuple = std::make_tuple(                                     \
        addMapItem, addMapItem2, addMapItem3, addMapItem4, addMapItem5,        \
        addMapItem6, addMapItem7, addMapItem8, addMapItem9, addMapItem10,      \
        dummyAddMapItem, dummyAddMapItem, dummyAddMapItem, dummyAddMapItem,    \
        dummyAddMapItem, dummyAddMapItem, dummyAddMapItem, dummyAddMapItem,    \
        dummyAddMapItem, dummyAddMapItem, dummyAddMapItem, dummyAddMapItem,    \
        dummyAddMapItem, dummyAddMapItem, dummyAddMapItem, dummyAddMapItem,    \
        dummyAddMapItem, dummyAddMapItem, dummyAddMapItem, dummyAddMapItem,    \
        dummyAddMapItem, dummyAddMapItem);

#define IMPLE_INIT_TUPLE_11(CLASS, M1, M2, M3, M4, M5, M6, M7, M8, M9, M10,    \
                            M11)                                               \
    std::function<decltype(M1)()> getobj1 =                                    \
        std::bind(&CLASS::__ReflectGet##M1, this);                             \
    std::function<decltype(M2)()> getobj2 =                                    \
        std::bind(&CLASS::__ReflectGet##M2, this);                             \
    std::function<decltype(M3)()> getobj3 =                                    \
        std::bind(&CLASS::__ReflectGet##M3, this);                             \
    std::function<decltype(M4)()> getobj4 =                                    \
        std::bind(&CLASS::__ReflectGet##M4, this);                             \
    std::function<decltype(M5)()> getobj5 =                                    \
        std::bind(&CLASS::__ReflectGet##M5, this);                             \
    std::function<decltype(M6)()> getobj6 =                                    \
        std::bind(&CLASS::__ReflectGet##M6, this);                             \
    std::function<decltype(M7)()> getobj7 =                                    \
        std::bind(&CLASS::__ReflectGet##M7, this);                             \
    std::function<decltype(M8)()> getobj8 =                                    \
        std::bind(&CLASS::__ReflectGet##M8, this);                             \
    std::function<decltype(M9)()> getobj9 =                                    \
        std::bind(&CLASS::__ReflectGet##M9, this);                             \
    std::function<decltype(M10)()> getobj10 =                                  \
        std::bind(&CLASS::__ReflectGet##M10, this);                            \
    std::function<decltype(M11)()> getobj11 =                                  \
        std::bind(&CLASS::__ReflectGet##M11, this);                            \
    std::function<void()> createobj1 =                                         \
        std::bind(&CLASS::__ReflectCreate##M1, this);                          \
    std::function<void()> createobj2 =                                         \
        std::bind(&CLASS::__ReflectCreate##M2, this);                          \
    std::function<void()> createobj3 =                                         \
        std::bind(&CLASS::__ReflectCreate##M3, this);                          \
    std::function<void()> createobj4 =                                         \
        std::bind(&CLASS::__ReflectCreate##M4, this);                          \
    std::function<void()> createobj5 =                                         \
        std::bind(&CLASS::__ReflectCreate##M5, this);                          \
    std::function<void()> createobj6 =                                         \
        std::bind(&CLASS::__ReflectCreate##M6, this);                          \
    std::function<void()> createobj7 =                                         \
        std::bind(&CLASS::__ReflectCreate##M7, this);                          \
    std::function<void()> createobj8 =                                         \
        std::bind(&CLASS::__ReflectCreate##M8, this);                          \
    std::function<void()> createobj9 =                                         \
        std::bind(&CLASS::__ReflectCreate##M9, this);                          \
    std::function<void()> createobj10 =                                        \
        std::bind(&CLASS::__ReflectCreate##M10, this);                         \
    std::function<void()> createobj11 =                                        \
        std::bind(&CLASS::__ReflectCreate##M11, this);                         \
    std::function<Object()> genItemObj1 =                                      \
        std::bind(&CLASS::__ReflectCreateListMember##M1, this);                \
    std::function<Object()> genItemObj2 =                                      \
        std::bind(&CLASS::__ReflectCreateListMember##M2, this);                \
    std::function<Object()> genItemObj3 =                                      \
        std::bind(&CLASS::__ReflectCreateListMember##M3, this);                \
    std::function<Object()> genItemObj4 =                                      \
        std::bind(&CLASS::__ReflectCreateListMember##M4, this);                \
    std::function<Object()> genItemObj5 =                                      \
        std::bind(&CLASS::__ReflectCreateListMember##M5, this);                \
    std::function<Object()> genItemObj6 =                                      \
        std::bind(&CLASS::__ReflectCreateListMember##M6, this);                \
    std::function<Object()> genItemObj7 =                                      \
        std::bind(&CLASS::__ReflectCreateListMember##M7, this);                \
    std::function<Object()> genItemObj8 =                                      \
        std::bind(&CLASS::__ReflectCreateListMember##M8, this);                \
    std::function<Object()> genItemObj9 =                                      \
        std::bind(&CLASS::__ReflectCreateListMember##M9, this);                \
    std::function<Object()> genItemObj10 =                                     \
        std::bind(&CLASS::__ReflectCreateListMember##M10, this);               \
    std::function<Object()> genItemObj11 =                                     \
        std::bind(&CLASS::__ReflectCreateListMember##M11, this);               \
    std::function<Object(int)> getItemObj1 = std::bind(                        \
        &CLASS::__ReflectGetListItem##M1, this, std::placeholders::_1);        \
    std::function<Object(int)> getItemObj2 = std::bind(                        \
        &CLASS::__ReflectGetListItem##M2, this, std::placeholders::_1);        \
    std::function<Object(int)> getItemObj3 = std::bind(                        \
        &CLASS::__ReflectGetListItem##M3, this, std::placeholders::_1);        \
    std::function<Object(int)> getItemObj4 = std::bind(                        \
        &CLASS::__ReflectGetListItem##M4, this, std::placeholders::_1);        \
    std::function<Object(int)> getItemObj5 = std::bind(                        \
        &CLASS::__ReflectGetListItem##M5, this, std::placeholders::_1);        \
    std::function<Object(int)> getItemObj6 = std::bind(                        \
        &CLASS::__ReflectGetListItem##M6, this, std::placeholders::_1);        \
    std::function<Object(int)> getItemObj7 = std::bind(                        \
        &CLASS::__ReflectGetListItem##M7, this, std::placeholders::_1);        \
    std::function<Object(int)> getItemObj8 = std::bind(                        \
        &CLASS::__ReflectGetListItem##M8, this, std::placeholders::_1);        \
    std::function<Object(int)> getItemObj9 = std::bind(                        \
        &CLASS::__ReflectGetListItem##M9, this, std::placeholders::_1);        \
    std::function<Object(int)> getItemObj10 = std::bind(                       \
        &CLASS::__ReflectGetListItem##M10, this, std::placeholders::_1);       \
    std::function<Object(int)> getItemObj11 = std::bind(                       \
        &CLASS::__ReflectGetListItem##M11, this, std::placeholders::_1);       \
    std::function<int()> getContainerSize1 =                                   \
        std::bind(&CLASS::__ReflectGetContainerSize##M1, this);                \
    std::function<int()> getContainerSize2 =                                   \
        std::bind(&CLASS::__ReflectGetContainerSize##M2, this);                \
    std::function<int()> getContainerSize3 =                                   \
        std::bind(&CLASS::__ReflectGetContainerSize##M3, this);                \
    std::function<int()> getContainerSize4 =                                   \
        std::bind(&CLASS::__ReflectGetContainerSize##M4, this);                \
    std::function<int()> getContainerSize5 =                                   \
        std::bind(&CLASS::__ReflectGetContainerSize##M5, this);                \
    std::function<int()> getContainerSize6 =                                   \
        std::bind(&CLASS::__ReflectGetContainerSize##M6, this);                \
    std::function<int()> getContainerSize7 =                                   \
        std::bind(&CLASS::__ReflectGetContainerSize##M7, this);                \
    std::function<int()> getContainerSize8 =                                   \
        std::bind(&CLASS::__ReflectGetContainerSize##M8, this);                \
    std::function<int()> getContainerSize9 =                                   \
        std::bind(&CLASS::__ReflectGetContainerSize##M9, this);                \
    std::function<int()> getContainerSize10 =                                  \
        std::bind(&CLASS::__ReflectGetContainerSize##M10, this);               \
    std::function<int()> getContainerSize11 =                                  \
        std::bind(&CLASS::__ReflectGetContainerSize##M11, this);               \
    std::function<Pair<Object, Object>()> createMapObj1 =              \
        std::bind(&CLASS::__ReflectCreateMapMember##M1, this);                 \
    std::function<ArrayList<Pair<Object, Object>>()> getMapItems1 =    \
        std::bind(&CLASS::__ReflectGetMapItems##M1, this);                     \
    std::function<Pair<Object, Object>()> createMapObj2 =              \
        std::bind(&CLASS::__ReflectCreateMapMember##M2, this);                 \
    std::function<ArrayList<Pair<Object, Object>>()> getMapItems2 =    \
        std::bind(&CLASS::__ReflectGetMapItems##M2, this);                     \
    std::function<Pair<Object, Object>()> createMapObj3 =              \
        std::bind(&CLASS::__ReflectCreateMapMember##M3, this);                 \
    std::function<ArrayList<Pair<Object, Object>>()> getMapItems3 =    \
        std::bind(&CLASS::__ReflectGetMapItems##M3, this);                     \
    std::function<Pair<Object, Object>()> createMapObj4 =              \
        std::bind(&CLASS::__ReflectCreateMapMember##M4, this);                 \
    std::function<ArrayList<Pair<Object, Object>>()> getMapItems4 =    \
        std::bind(&CLASS::__ReflectGetMapItems##M4, this);                     \
    std::function<Pair<Object, Object>()> createMapObj5 =              \
        std::bind(&CLASS::__ReflectCreateMapMember##M5, this);                 \
    std::function<ArrayList<Pair<Object, Object>>()> getMapItems5 =    \
        std::bind(&CLASS::__ReflectGetMapItems##M5, this);                     \
    std::function<Pair<Object, Object>()> createMapObj6 =              \
        std::bind(&CLASS::__ReflectCreateMapMember##M6, this);                 \
    std::function<ArrayList<Pair<Object, Object>>()> getMapItems6 =    \
        std::bind(&CLASS::__ReflectGetMapItems##M6, this);                     \
    std::function<Pair<Object, Object>()> createMapObj7 =              \
        std::bind(&CLASS::__ReflectCreateMapMember##M7, this);                 \
    std::function<ArrayList<Pair<Object, Object>>()> getMapItems7 =    \
        std::bind(&CLASS::__ReflectGetMapItems##M7, this);                     \
    std::function<Pair<Object, Object>()> createMapObj8 =              \
        std::bind(&CLASS::__ReflectCreateMapMember##M8, this);                 \
    std::function<ArrayList<Pair<Object, Object>>()> getMapItems8 =    \
        std::bind(&CLASS::__ReflectGetMapItems##M8, this);                     \
    std::function<Pair<Object, Object>()> createMapObj9 =              \
        std::bind(&CLASS::__ReflectCreateMapMember##M9, this);                 \
    std::function<ArrayList<Pair<Object, Object>>()> getMapItems9 =    \
        std::bind(&CLASS::__ReflectGetMapItems##M9, this);                     \
    std::function<Pair<Object, Object>()> createMapObj10 =             \
        std::bind(&CLASS::__ReflectCreateMapMember##M10, this);                \
    std::function<ArrayList<Pair<Object, Object>>()> getMapItems10 =   \
        std::bind(&CLASS::__ReflectGetMapItems##M10, this);                    \
    std::function<Pair<Object, Object>()> createMapObj11 =             \
        std::bind(&CLASS::__ReflectCreateMapMember##M11, this);                \
    std::function<ArrayList<Pair<Object, Object>>()> getMapItems11 =   \
        std::bind(&CLASS::__ReflectGetMapItems##M11, this);                    \
    std::function<void(Object)> addListItem = std::bind(                       \
        &CLASS::__ReflectAddListItem##M1, this, std::placeholders::_1);        \
    std::function<void(Object, Object)> addMapItem =                           \
        std::bind(&CLASS::__ReflectAddMapItem##M1, this,                       \
                  std::placeholders::_1, std::placeholders::_2);               \
    std::function<void(Object)> addListItem2 = std::bind(                      \
        &CLASS::__ReflectAddListItem##M2, this, std::placeholders::_1);        \
    std::function<void(Object, Object)> addMapItem2 =                          \
        std::bind(&CLASS::__ReflectAddMapItem##M2, this,                       \
                  std::placeholders::_1, std::placeholders::_2);               \
    std::function<void(Object)> addListItem3 = std::bind(                      \
        &CLASS::__ReflectAddListItem##M3, this, std::placeholders::_1);        \
    std::function<void(Object, Object)> addMapItem3 =                          \
        std::bind(&CLASS::__ReflectAddMapItem##M3, this,                       \
                  std::placeholders::_1, std::placeholders::_2);               \
    std::function<void(Object)> addListItem4 = std::bind(                      \
        &CLASS::__ReflectAddListItem##M4, this, std::placeholders::_1);        \
    std::function<void(Object, Object)> addMapItem4 =                          \
        std::bind(&CLASS::__ReflectAddMapItem##M4, this,                       \
                  std::placeholders::_1, std::placeholders::_2);               \
    std::function<void(Object)> addListItem5 = std::bind(                      \
        &CLASS::__ReflectAddListItem##M5, this, std::placeholders::_1);        \
    std::function<void(Object, Object)> addMapItem5 =                          \
        std::bind(&CLASS::__ReflectAddMapItem##M5, this,                       \
                  std::placeholders::_1, std::placeholders::_2);               \
    std::function<void(Object)> addListItem6 = std::bind(                      \
        &CLASS::__ReflectAddListItem##M6, this, std::placeholders::_1);        \
    std::function<void(Object, Object)> addMapItem6 =                          \
        std::bind(&CLASS::__ReflectAddMapItem##M6, this,                       \
                  std::placeholders::_1, std::placeholders::_2);               \
    std::function<void(Object)> addListItem7 = std::bind(                      \
        &CLASS::__ReflectAddListItem##M7, this, std::placeholders::_1);        \
    std::function<void(Object, Object)> addMapItem7 =                          \
        std::bind(&CLASS::__ReflectAddMapItem##M7, this,                       \
                  std::placeholders::_1, std::placeholders::_2);               \
    std::function<void(Object)> addListItem8 = std::bind(                      \
        &CLASS::__ReflectAddListItem##M8, this, std::placeholders::_1);        \
    std::function<void(Object, Object)> addMapItem8 =                          \
        std::bind(&CLASS::__ReflectAddMapItem##M8, this,                       \
                  std::placeholders::_1, std::placeholders::_2);               \
    std::function<void(Object)> addListItem9 = std::bind(                      \
        &CLASS::__ReflectAddListItem##M9, this, std::placeholders::_1);        \
    std::function<void(Object, Object)> addMapItem9 =                          \
        std::bind(&CLASS::__ReflectAddMapItem##M9, this,                       \
                  std::placeholders::_1, std::placeholders::_2);               \
    std::function<void(Object)> addListItem10 = std::bind(                     \
        &CLASS::__ReflectAddListItem##M10, this, std::placeholders::_1);       \
    std::function<void(Object, Object)> addMapItem10 =                         \
        std::bind(&CLASS::__ReflectAddMapItem##M10, this,                      \
                  std::placeholders::_1, std::placeholders::_2);               \
    std::function<void(Object)> addListItem11 = std::bind(                     \
        &CLASS::__ReflectAddListItem##M11, this, std::placeholders::_1);       \
    std::function<void(Object, Object)> addMapItem11 =                         \
        std::bind(&CLASS::__ReflectAddMapItem##M11, this,                      \
                  std::placeholders::_1, std::placeholders::_2);               \
    getFuncTuple = std::make_tuple(                                            \
        getobj1, getobj2, getobj3, getobj4, getobj5, getobj6, getobj7,         \
        getobj8, getobj9, getobj10, getobj11, dummyobj, dummyobj, dummyobj,    \
        dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj,  \
        dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj,  \
        dummyobj, dummyobj, dummyobj, dummyobj);                               \
    createFuncTuple = std::make_tuple(                                         \
        createobj1, createobj2, createobj3, createobj4, createobj5,            \
        createobj6, createobj7, createobj8, createobj9, createobj10,           \
        createobj11, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj,         \
        dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj,  \
        dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj,  \
        dummyobj, dummyobj);                                                   \
    createListItemFuncTuple = std::make_tuple(                                 \
        genItemObj1, genItemObj2, genItemObj3, genItemObj4, genItemObj5,       \
        genItemObj6, genItemObj7, genItemObj8, genItemObj9, genItemObj10,      \
        genItemObj11, dummycreateobj, dummycreateobj, dummycreateobj,          \
        dummycreateobj, dummycreateobj, dummycreateobj, dummycreateobj,        \
        dummycreateobj, dummycreateobj, dummycreateobj, dummycreateobj,        \
        dummycreateobj, dummycreateobj, dummycreateobj, dummycreateobj,        \
        dummycreateobj, dummycreateobj, dummycreateobj, dummycreateobj,        \
        dummycreateobj, dummycreateobj);                                       \
    getListItemFuncTuple = std::make_tuple(                                    \
        getItemObj1, getItemObj2, getItemObj3, getItemObj4, getItemObj5,       \
        getItemObj6, getItemObj7, getItemObj8, getItemObj9, getItemObj10,      \
        getItemObj11, dummyligobj, dummyligobj, dummyligobj, dummyligobj,      \
        dummyligobj, dummyligobj, dummyligobj, dummyligobj, dummyligobj,       \
        dummyligobj, dummyligobj, dummyligobj, dummyligobj, dummyligobj,       \
        dummyligobj, dummyligobj, dummyligobj, dummyligobj, dummyligobj,       \
        dummyligobj, dummyligobj);                                             \
    getContainerSizeFuncTuple = std::make_tuple(                               \
        getContainerSize1, getContainerSize2, getContainerSize3,               \
        getContainerSize4, getContainerSize5, getContainerSize6,               \
        getContainerSize7, getContainerSize8, getContainerSize9,               \
        getContainerSize10, getContainerSize11, dummyobj, dummyobj, dummyobj,  \
        dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj,  \
        dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj,  \
        dummyobj, dummyobj, dummyobj, dummyobj);                               \
    createMapItemFuncTuple = std::make_tuple(                                  \
        createMapObj1, createMapObj2, createMapObj3, createMapObj4,            \
        createMapObj5, createMapObj6, createMapObj7, createMapObj8,            \
        createMapObj9, createMapObj10, createMapObj11, dummycreateMapItem,     \
        dummycreateMapItem, dummycreateMapItem, dummycreateMapItem,            \
        dummycreateMapItem, dummycreateMapItem, dummycreateMapItem,            \
        dummycreateMapItem, dummycreateMapItem, dummycreateMapItem,            \
        dummycreateMapItem, dummycreateMapItem, dummycreateMapItem,            \
        dummycreateMapItem, dummycreateMapItem, dummycreateMapItem,            \
        dummycreateMapItem, dummycreateMapItem, dummycreateMapItem,            \
        dummycreateMapItem, dummycreateMapItem);                               \
    getMapItemsFuncTuple = std::make_tuple(                                    \
        getMapItems1, getMapItems2, getMapItems3, getMapItems4, getMapItems5,  \
        getMapItems6, getMapItems7, getMapItems8, getMapItems9, getMapItems10, \
        getMapItems11, dummygetMapItems, dummygetMapItems, dummygetMapItems,   \
        dummygetMapItems, dummygetMapItems, dummygetMapItems,                  \
        dummygetMapItems, dummygetMapItems, dummygetMapItems,                  \
        dummygetMapItems, dummygetMapItems, dummygetMapItems,                  \
        dummygetMapItems, dummygetMapItems, dummygetMapItems,                  \
        dummygetMapItems, dummygetMapItems, dummygetMapItems,                  \
        dummygetMapItems, dummygetMapItems, dummygetMapItems);                 \
    addListItemFuncTuple = std::make_tuple(                                    \
        addListItem, addListItem2, addListItem3, addListItem4, addListItem5,   \
        addListItem6, addListItem7, addListItem8, addListItem9, addListItem10, \
        addListItem11, dummyAddListItem, dummyAddListItem, dummyAddListItem,   \
        dummyAddListItem, dummyAddListItem, dummyAddListItem,                  \
        dummyAddListItem, dummyAddListItem, dummyAddListItem,                  \
        dummyAddListItem, dummyAddListItem, dummyAddListItem,                  \
        dummyAddListItem, dummyAddListItem, dummyAddListItem,                  \
        dummyAddListItem, dummyAddListItem, dummyAddListItem,                  \
        dummyAddListItem, dummyAddListItem, dummyAddListItem);                 \
    addMapItemFuncTuple = std::make_tuple(                                     \
        addMapItem, addMapItem2, addMapItem3, addMapItem4, addMapItem5,        \
        addMapItem6, addMapItem7, addMapItem8, addMapItem9, addMapItem10,      \
        addMapItem11, dummyAddMapItem, dummyAddMapItem, dummyAddMapItem,       \
        dummyAddMapItem, dummyAddMapItem, dummyAddMapItem, dummyAddMapItem,    \
        dummyAddMapItem, dummyAddMapItem, dummyAddMapItem, dummyAddMapItem,    \
        dummyAddMapItem, dummyAddMapItem, dummyAddMapItem, dummyAddMapItem,    \
        dummyAddMapItem, dummyAddMapItem, dummyAddMapItem, dummyAddMapItem,    \
        dummyAddMapItem, dummyAddMapItem);

#define IMPLE_INIT_TUPLE_12(CLASS, M1, M2, M3, M4, M5, M6, M7, M8, M9, M10,    \
                            M11, M12)                                          \
    std::function<decltype(M1)()> getobj1 =                                    \
        std::bind(&CLASS::__ReflectGet##M1, this);                             \
    std::function<decltype(M2)()> getobj2 =                                    \
        std::bind(&CLASS::__ReflectGet##M2, this);                             \
    std::function<decltype(M3)()> getobj3 =                                    \
        std::bind(&CLASS::__ReflectGet##M3, this);                             \
    std::function<decltype(M4)()> getobj4 =                                    \
        std::bind(&CLASS::__ReflectGet##M4, this);                             \
    std::function<decltype(M5)()> getobj5 =                                    \
        std::bind(&CLASS::__ReflectGet##M5, this);                             \
    std::function<decltype(M6)()> getobj6 =                                    \
        std::bind(&CLASS::__ReflectGet##M6, this);                             \
    std::function<decltype(M7)()> getobj7 =                                    \
        std::bind(&CLASS::__ReflectGet##M7, this);                             \
    std::function<decltype(M8)()> getobj8 =                                    \
        std::bind(&CLASS::__ReflectGet##M8, this);                             \
    std::function<decltype(M9)()> getobj9 =                                    \
        std::bind(&CLASS::__ReflectGet##M9, this);                             \
    std::function<decltype(M10)()> getobj10 =                                  \
        std::bind(&CLASS::__ReflectGet##M10, this);                            \
    std::function<decltype(M11)()> getobj11 =                                  \
        std::bind(&CLASS::__ReflectGet##M11, this);                            \
    std::function<decltype(M12)()> getobj12 =                                  \
        std::bind(&CLASS::__ReflectGet##M12, this);                            \
    std::function<void()> createobj1 =                                         \
        std::bind(&CLASS::__ReflectCreate##M1, this);                          \
    std::function<void()> createobj2 =                                         \
        std::bind(&CLASS::__ReflectCreate##M2, this);                          \
    std::function<void()> createobj3 =                                         \
        std::bind(&CLASS::__ReflectCreate##M3, this);                          \
    std::function<void()> createobj4 =                                         \
        std::bind(&CLASS::__ReflectCreate##M4, this);                          \
    std::function<void()> createobj5 =                                         \
        std::bind(&CLASS::__ReflectCreate##M5, this);                          \
    std::function<void()> createobj6 =                                         \
        std::bind(&CLASS::__ReflectCreate##M6, this);                          \
    std::function<void()> createobj7 =                                         \
        std::bind(&CLASS::__ReflectCreate##M7, this);                          \
    std::function<void()> createobj8 =                                         \
        std::bind(&CLASS::__ReflectCreate##M8, this);                          \
    std::function<void()> createobj9 =                                         \
        std::bind(&CLASS::__ReflectCreate##M9, this);                          \
    std::function<void()> createobj10 =                                        \
        std::bind(&CLASS::__ReflectCreate##M10, this);                         \
    std::function<void()> createobj11 =                                        \
        std::bind(&CLASS::__ReflectCreate##M11, this);                         \
    std::function<void()> createobj12 =                                        \
        std::bind(&CLASS::__ReflectCreate##M12, this);                         \
    std::function<Object()> genItemObj1 =                                      \
        std::bind(&CLASS::__ReflectCreateListMember##M1, this);                \
    std::function<Object()> genItemObj2 =                                      \
        std::bind(&CLASS::__ReflectCreateListMember##M2, this);                \
    std::function<Object()> genItemObj3 =                                      \
        std::bind(&CLASS::__ReflectCreateListMember##M3, this);                \
    std::function<Object()> genItemObj4 =                                      \
        std::bind(&CLASS::__ReflectCreateListMember##M4, this);                \
    std::function<Object()> genItemObj5 =                                      \
        std::bind(&CLASS::__ReflectCreateListMember##M5, this);                \
    std::function<Object()> genItemObj6 =                                      \
        std::bind(&CLASS::__ReflectCreateListMember##M6, this);                \
    std::function<Object()> genItemObj7 =                                      \
        std::bind(&CLASS::__ReflectCreateListMember##M7, this);                \
    std::function<Object()> genItemObj8 =                                      \
        std::bind(&CLASS::__ReflectCreateListMember##M8, this);                \
    std::function<Object()> genItemObj9 =                                      \
        std::bind(&CLASS::__ReflectCreateListMember##M9, this);                \
    std::function<Object()> genItemObj10 =                                     \
        std::bind(&CLASS::__ReflectCreateListMember##M10, this);               \
    std::function<Object()> genItemObj11 =                                     \
        std::bind(&CLASS::__ReflectCreateListMember##M11, this);               \
    std::function<Object()> genItemObj12 =                                     \
        std::bind(&CLASS::__ReflectCreateListMember##M12, this);               \
    std::function<Object(int)> getItemObj1 = std::bind(                        \
        &CLASS::__ReflectGetListItem##M1, this, std::placeholders::_1);        \
    std::function<Object(int)> getItemObj2 = std::bind(                        \
        &CLASS::__ReflectGetListItem##M2, this, std::placeholders::_1);        \
    std::function<Object(int)> getItemObj3 = std::bind(                        \
        &CLASS::__ReflectGetListItem##M3, this, std::placeholders::_1);        \
    std::function<Object(int)> getItemObj4 = std::bind(                        \
        &CLASS::__ReflectGetListItem##M4, this, std::placeholders::_1);        \
    std::function<Object(int)> getItemObj5 = std::bind(                        \
        &CLASS::__ReflectGetListItem##M5, this, std::placeholders::_1);        \
    std::function<Object(int)> getItemObj6 = std::bind(                        \
        &CLASS::__ReflectGetListItem##M6, this, std::placeholders::_1);        \
    std::function<Object(int)> getItemObj7 = std::bind(                        \
        &CLASS::__ReflectGetListItem##M7, this, std::placeholders::_1);        \
    std::function<Object(int)> getItemObj8 = std::bind(                        \
        &CLASS::__ReflectGetListItem##M8, this, std::placeholders::_1);        \
    std::function<Object(int)> getItemObj9 = std::bind(                        \
        &CLASS::__ReflectGetListItem##M9, this, std::placeholders::_1);        \
    std::function<Object(int)> getItemObj10 = std::bind(                       \
        &CLASS::__ReflectGetListItem##M10, this, std::placeholders::_1);       \
    std::function<Object(int)> getItemObj11 = std::bind(                       \
        &CLASS::__ReflectGetListItem##M11, this, std::placeholders::_1);       \
    std::function<Object(int)> getItemObj12 = std::bind(                       \
        &CLASS::__ReflectGetListItem##M12, this, std::placeholders::_1);       \
    std::function<int()> getContainerSize1 =                                   \
        std::bind(&CLASS::__ReflectGetContainerSize##M1, this);                \
    std::function<int()> getContainerSize2 =                                   \
        std::bind(&CLASS::__ReflectGetContainerSize##M2, this);                \
    std::function<int()> getContainerSize3 =                                   \
        std::bind(&CLASS::__ReflectGetContainerSize##M3, this);                \
    std::function<int()> getContainerSize4 =                                   \
        std::bind(&CLASS::__ReflectGetContainerSize##M4, this);                \
    std::function<int()> getContainerSize5 =                                   \
        std::bind(&CLASS::__ReflectGetContainerSize##M5, this);                \
    std::function<int()> getContainerSize6 =                                   \
        std::bind(&CLASS::__ReflectGetContainerSize##M6, this);                \
    std::function<int()> getContainerSize7 =                                   \
        std::bind(&CLASS::__ReflectGetContainerSize##M7, this);                \
    std::function<int()> getContainerSize8 =                                   \
        std::bind(&CLASS::__ReflectGetContainerSize##M8, this);                \
    std::function<int()> getContainerSize9 =                                   \
        std::bind(&CLASS::__ReflectGetContainerSize##M9, this);                \
    std::function<int()> getContainerSize10 =                                  \
        std::bind(&CLASS::__ReflectGetContainerSize##M10, this);               \
    std::function<int()> getContainerSize11 =                                  \
        std::bind(&CLASS::__ReflectGetContainerSize##M11, this);               \
    std::function<int()> getContainerSize12 =                                  \
        std::bind(&CLASS::__ReflectGetContainerSize##M12, this);               \
    std::function<Pair<Object, Object>()> createMapObj1 =              \
        std::bind(&CLASS::__ReflectCreateMapMember##M1, this);                 \
    std::function<ArrayList<Pair<Object, Object>>()> getMapItems1 =    \
        std::bind(&CLASS::__ReflectGetMapItems##M1, this);                     \
    std::function<Pair<Object, Object>()> createMapObj2 =              \
        std::bind(&CLASS::__ReflectCreateMapMember##M2, this);                 \
    std::function<ArrayList<Pair<Object, Object>>()> getMapItems2 =    \
        std::bind(&CLASS::__ReflectGetMapItems##M2, this);                     \
    std::function<Pair<Object, Object>()> createMapObj3 =              \
        std::bind(&CLASS::__ReflectCreateMapMember##M3, this);                 \
    std::function<ArrayList<Pair<Object, Object>>()> getMapItems3 =    \
        std::bind(&CLASS::__ReflectGetMapItems##M3, this);                     \
    std::function<Pair<Object, Object>()> createMapObj4 =              \
        std::bind(&CLASS::__ReflectCreateMapMember##M4, this);                 \
    std::function<ArrayList<Pair<Object, Object>>()> getMapItems4 =    \
        std::bind(&CLASS::__ReflectGetMapItems##M4, this);                     \
    std::function<Pair<Object, Object>()> createMapObj5 =              \
        std::bind(&CLASS::__ReflectCreateMapMember##M5, this);                 \
    std::function<ArrayList<Pair<Object, Object>>()> getMapItems5 =    \
        std::bind(&CLASS::__ReflectGetMapItems##M5, this);                     \
    std::function<Pair<Object, Object>()> createMapObj6 =              \
        std::bind(&CLASS::__ReflectCreateMapMember##M6, this);                 \
    std::function<ArrayList<Pair<Object, Object>>()> getMapItems6 =    \
        std::bind(&CLASS::__ReflectGetMapItems##M6, this);                     \
    std::function<Pair<Object, Object>()> createMapObj7 =              \
        std::bind(&CLASS::__ReflectCreateMapMember##M7, this);                 \
    std::function<ArrayList<Pair<Object, Object>>()> getMapItems7 =    \
        std::bind(&CLASS::__ReflectGetMapItems##M7, this);                     \
    std::function<Pair<Object, Object>()> createMapObj8 =              \
        std::bind(&CLASS::__ReflectCreateMapMember##M8, this);                 \
    std::function<ArrayList<Pair<Object, Object>>()> getMapItems8 =    \
        std::bind(&CLASS::__ReflectGetMapItems##M8, this);                     \
    std::function<Pair<Object, Object>()> createMapObj9 =              \
        std::bind(&CLASS::__ReflectCreateMapMember##M9, this);                 \
    std::function<ArrayList<Pair<Object, Object>>()> getMapItems9 =    \
        std::bind(&CLASS::__ReflectGetMapItems##M9, this);                     \
    std::function<Pair<Object, Object>()> createMapObj10 =             \
        std::bind(&CLASS::__ReflectCreateMapMember##M10, this);                \
    std::function<ArrayList<Pair<Object, Object>>()> getMapItems10 =   \
        std::bind(&CLASS::__ReflectGetMapItems##M10, this);                    \
    std::function<Pair<Object, Object>()> createMapObj11 =             \
        std::bind(&CLASS::__ReflectCreateMapMember##M11, this);                \
    std::function<ArrayList<Pair<Object, Object>>()> getMapItems11 =   \
        std::bind(&CLASS::__ReflectGetMapItems##M11, this);                    \
    std::function<Pair<Object, Object>()> createMapObj12 =             \
        std::bind(&CLASS::__ReflectCreateMapMember##M12, this);                \
    std::function<ArrayList<Pair<Object, Object>>()> getMapItems12 =   \
        std::bind(&CLASS::__ReflectGetMapItems##M12, this);                    \
    std::function<void(Object)> addListItem = std::bind(                       \
        &CLASS::__ReflectAddListItem##M1, this, std::placeholders::_1);        \
    std::function<void(Object, Object)> addMapItem =                           \
        std::bind(&CLASS::__ReflectAddMapItem##M1, this,                       \
                  std::placeholders::_1, std::placeholders::_2);               \
    std::function<void(Object)> addListItem2 = std::bind(                      \
        &CLASS::__ReflectAddListItem##M2, this, std::placeholders::_1);        \
    std::function<void(Object, Object)> addMapItem2 =                          \
        std::bind(&CLASS::__ReflectAddMapItem##M2, this,                       \
                  std::placeholders::_1, std::placeholders::_2);               \
    std::function<void(Object)> addListItem3 = std::bind(                      \
        &CLASS::__ReflectAddListItem##M3, this, std::placeholders::_1);        \
    std::function<void(Object, Object)> addMapItem3 =                          \
        std::bind(&CLASS::__ReflectAddMapItem##M3, this,                       \
                  std::placeholders::_1, std::placeholders::_2);               \
    std::function<void(Object)> addListItem4 = std::bind(                      \
        &CLASS::__ReflectAddListItem##M4, this, std::placeholders::_1);        \
    std::function<void(Object, Object)> addMapItem4 =                          \
        std::bind(&CLASS::__ReflectAddMapItem##M4, this,                       \
                  std::placeholders::_1, std::placeholders::_2);               \
    std::function<void(Object)> addListItem5 = std::bind(                      \
        &CLASS::__ReflectAddListItem##M5, this, std::placeholders::_1);        \
    std::function<void(Object, Object)> addMapItem5 =                          \
        std::bind(&CLASS::__ReflectAddMapItem##M5, this,                       \
                  std::placeholders::_1, std::placeholders::_2);               \
    std::function<void(Object)> addListItem6 = std::bind(                      \
        &CLASS::__ReflectAddListItem##M6, this, std::placeholders::_1);        \
    std::function<void(Object, Object)> addMapItem6 =                          \
        std::bind(&CLASS::__ReflectAddMapItem##M6, this,                       \
                  std::placeholders::_1, std::placeholders::_2);               \
    std::function<void(Object)> addListItem7 = std::bind(                      \
        &CLASS::__ReflectAddListItem##M7, this, std::placeholders::_1);        \
    std::function<void(Object, Object)> addMapItem7 =                          \
        std::bind(&CLASS::__ReflectAddMapItem##M7, this,                       \
                  std::placeholders::_1, std::placeholders::_2);               \
    std::function<void(Object)> addListItem8 = std::bind(                      \
        &CLASS::__ReflectAddListItem##M8, this, std::placeholders::_1);        \
    std::function<void(Object, Object)> addMapItem8 =                          \
        std::bind(&CLASS::__ReflectAddMapItem##M8, this,                       \
                  std::placeholders::_1, std::placeholders::_2);               \
    std::function<void(Object)> addListItem9 = std::bind(                      \
        &CLASS::__ReflectAddListItem##M9, this, std::placeholders::_1);        \
    std::function<void(Object, Object)> addMapItem9 =                          \
        std::bind(&CLASS::__ReflectAddMapItem##M9, this,                       \
                  std::placeholders::_1, std::placeholders::_2);               \
    std::function<void(Object)> addListItem10 = std::bind(                     \
        &CLASS::__ReflectAddListItem##M10, this, std::placeholders::_1);       \
    std::function<void(Object, Object)> addMapItem10 =                         \
        std::bind(&CLASS::__ReflectAddMapItem##M10, this,                      \
                  std::placeholders::_1, std::placeholders::_2);               \
    std::function<void(Object)> addListItem11 = std::bind(                     \
        &CLASS::__ReflectAddListItem##M11, this, std::placeholders::_1);       \
    std::function<void(Object, Object)> addMapItem11 =                         \
        std::bind(&CLASS::__ReflectAddMapItem##M11, this,                      \
                  std::placeholders::_1, std::placeholders::_2);               \
    std::function<void(Object)> addListItem12 = std::bind(                     \
        &CLASS::__ReflectAddListItem##M12, this, std::placeholders::_1);       \
    std::function<void(Object, Object)> addMapItem12 =                         \
        std::bind(&CLASS::__ReflectAddMapItem##M12, this,                      \
                  std::placeholders::_1, std::placeholders::_2);               \
    getFuncTuple = std::make_tuple(                                            \
        getobj1, getobj2, getobj3, getobj4, getobj5, getobj6, getobj7,         \
        getobj8, getobj9, getobj10, getobj11, getobj12, dummyobj, dummyobj,    \
        dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj,  \
        dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj);           \
    createFuncTuple = std::make_tuple(                                         \
        createobj1, createobj2, createobj3, createobj4, createobj5,            \
        createobj6, createobj7, createobj8, createobj9, createobj10,           \
        createobj11, createobj12, dummyobj, dummyobj, dummyobj, dummyobj,      \
        dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj,  \
        dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj,  \
        dummyobj, dummyobj);                                                   \
    createListItemFuncTuple = std::make_tuple(                                 \
        genItemObj1, genItemObj2, genItemObj3, genItemObj4, genItemObj5,       \
        genItemObj6, genItemObj7, genItemObj8, genItemObj9, genItemObj10,      \
        genItemObj11, genItemObj12, dummycreateobj, dummycreateobj,            \
        dummycreateobj, dummycreateobj, dummycreateobj, dummycreateobj,        \
        dummycreateobj, dummycreateobj, dummycreateobj, dummycreateobj,        \
        dummycreateobj, dummycreateobj, dummycreateobj, dummycreateobj,        \
        dummycreateobj, dummycreateobj, dummycreateobj, dummycreateobj,        \
        dummycreateobj, dummycreateobj);                                       \
    getListItemFuncTuple = std::make_tuple(                                    \
        getItemObj1, getItemObj2, getItemObj3, getItemObj4, getItemObj5,       \
        getItemObj6, getItemObj7, getItemObj8, getItemObj9, getItemObj10,      \
        getItemObj11, getItemObj12, dummyligobj, dummyligobj, dummyligobj,     \
        dummyligobj, dummyligobj, dummyligobj, dummyligobj, dummyligobj,       \
        dummyligobj, dummyligobj, dummyligobj, dummyligobj, dummyligobj,       \
        dummyligobj, dummyligobj, dummyligobj, dummyligobj, dummyligobj,       \
        dummyligobj, dummyligobj);                                             \
    getContainerSizeFuncTuple = std::make_tuple(                               \
        getContainerSize1, getContainerSize2, getContainerSize3,               \
        getContainerSize4, getContainerSize5, getContainerSize6,               \
        getContainerSize7, getContainerSize8, getContainerSize9,               \
        getContainerSize10, getContainerSize11, getContainerSize12, dummyobj,  \
        dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj,  \
        dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj,  \
        dummyobj, dummyobj, dummyobj, dummyobj, dummyobj);                     \
    createMapItemFuncTuple = std::make_tuple(                                  \
        createMapObj1, createMapObj2, createMapObj3, createMapObj4,            \
        createMapObj5, createMapObj6, createMapObj7, createMapObj8,            \
        createMapObj9, createMapObj10, createMapObj11, createMapObj12,         \
        dummycreateMapItem, dummycreateMapItem, dummycreateMapItem,            \
        dummycreateMapItem, dummycreateMapItem, dummycreateMapItem,            \
        dummycreateMapItem, dummycreateMapItem, dummycreateMapItem,            \
        dummycreateMapItem, dummycreateMapItem, dummycreateMapItem,            \
        dummycreateMapItem, dummycreateMapItem, dummycreateMapItem,            \
        dummycreateMapItem, dummycreateMapItem, dummycreateMapItem,            \
        dummycreateMapItem, dummycreateMapItem);                               \
    getMapItemsFuncTuple = std::make_tuple(                                    \
        getMapItems1, getMapItems2, getMapItems3, getMapItems4, getMapItems5,  \
        getMapItems6, getMapItems7, getMapItems8, getMapItems9, getMapItems10, \
        getMapItems11, getMapItems12, dummygetMapItems, dummygetMapItems,      \
        dummygetMapItems, dummygetMapItems, dummygetMapItems,                  \
        dummygetMapItems, dummygetMapItems, dummygetMapItems,                  \
        dummygetMapItems, dummygetMapItems, dummygetMapItems,                  \
        dummygetMapItems, dummygetMapItems, dummygetMapItems,                  \
        dummygetMapItems, dummygetMapItems, dummygetMapItems,                  \
        dummygetMapItems, dummygetMapItems, dummygetMapItems);                 \
    addListItemFuncTuple = std::make_tuple(                                    \
        addListItem, addListItem2, addListItem3, addListItem4, addListItem5,   \
        addListItem6, addListItem7, addListItem8, addListItem9, addListItem10, \
        addListItem11, addListItem12, dummyAddListItem, dummyAddListItem,      \
        dummyAddListItem, dummyAddListItem, dummyAddListItem,                  \
        dummyAddListItem, dummyAddListItem, dummyAddListItem,                  \
        dummyAddListItem, dummyAddListItem, dummyAddListItem,                  \
        dummyAddListItem, dummyAddListItem, dummyAddListItem,                  \
        dummyAddListItem, dummyAddListItem, dummyAddListItem,                  \
        dummyAddListItem, dummyAddListItem, dummyAddListItem);                 \
    addMapItemFuncTuple = std::make_tuple(                                     \
        addMapItem, addMapItem2, addMapItem3, addMapItem4, addMapItem5,        \
        addMapItem6, addMapItem7, addMapItem8, addMapItem9, addMapItem10,      \
        addMapItem11, addMapItem12, dummyAddMapItem, dummyAddMapItem,          \
        dummyAddMapItem, dummyAddMapItem, dummyAddMapItem, dummyAddMapItem,    \
        dummyAddMapItem, dummyAddMapItem, dummyAddMapItem, dummyAddMapItem,    \
        dummyAddMapItem, dummyAddMapItem, dummyAddMapItem, dummyAddMapItem,    \
        dummyAddMapItem, dummyAddMapItem, dummyAddMapItem, dummyAddMapItem,    \
        dummyAddMapItem, dummyAddMapItem);

#define IMPLE_INIT_TUPLE_13(CLASS, M1, M2, M3, M4, M5, M6, M7, M8, M9, M10,    \
                            M11, M12, M13)                                     \
    std::function<decltype(M1)()> getobj1 =                                    \
        std::bind(&CLASS::__ReflectGet##M1, this);                             \
    std::function<decltype(M2)()> getobj2 =                                    \
        std::bind(&CLASS::__ReflectGet##M2, this);                             \
    std::function<decltype(M3)()> getobj3 =                                    \
        std::bind(&CLASS::__ReflectGet##M3, this);                             \
    std::function<decltype(M4)()> getobj4 =                                    \
        std::bind(&CLASS::__ReflectGet##M4, this);                             \
    std::function<decltype(M5)()> getobj5 =                                    \
        std::bind(&CLASS::__ReflectGet##M5, this);                             \
    std::function<decltype(M6)()> getobj6 =                                    \
        std::bind(&CLASS::__ReflectGet##M6, this);                             \
    std::function<decltype(M7)()> getobj7 =                                    \
        std::bind(&CLASS::__ReflectGet##M7, this);                             \
    std::function<decltype(M8)()> getobj8 =                                    \
        std::bind(&CLASS::__ReflectGet##M8, this);                             \
    std::function<decltype(M9)()> getobj9 =                                    \
        std::bind(&CLASS::__ReflectGet##M9, this);                             \
    std::function<decltype(M10)()> getobj10 =                                  \
        std::bind(&CLASS::__ReflectGet##M10, this);                            \
    std::function<decltype(M11)()> getobj11 =                                  \
        std::bind(&CLASS::__ReflectGet##M11, this);                            \
    std::function<decltype(M12)()> getobj12 =                                  \
        std::bind(&CLASS::__ReflectGet##M12, this);                            \
    std::function<decltype(M13)()> getobj13 =                                  \
        std::bind(&CLASS::__ReflectGet##M13, this);                            \
    std::function<void()> createobj1 =                                         \
        std::bind(&CLASS::__ReflectCreate##M1, this);                          \
    std::function<void()> createobj2 =                                         \
        std::bind(&CLASS::__ReflectCreate##M2, this);                          \
    std::function<void()> createobj3 =                                         \
        std::bind(&CLASS::__ReflectCreate##M3, this);                          \
    std::function<void()> createobj4 =                                         \
        std::bind(&CLASS::__ReflectCreate##M4, this);                          \
    std::function<void()> createobj5 =                                         \
        std::bind(&CLASS::__ReflectCreate##M5, this);                          \
    std::function<void()> createobj6 =                                         \
        std::bind(&CLASS::__ReflectCreate##M6, this);                          \
    std::function<void()> createobj7 =                                         \
        std::bind(&CLASS::__ReflectCreate##M7, this);                          \
    std::function<void()> createobj8 =                                         \
        std::bind(&CLASS::__ReflectCreate##M8, this);                          \
    std::function<void()> createobj9 =                                         \
        std::bind(&CLASS::__ReflectCreate##M9, this);                          \
    std::function<void()> createobj10 =                                        \
        std::bind(&CLASS::__ReflectCreate##M10, this);                         \
    std::function<void()> createobj11 =                                        \
        std::bind(&CLASS::__ReflectCreate##M11, this);                         \
    std::function<void()> createobj12 =                                        \
        std::bind(&CLASS::__ReflectCreate##M12, this);                         \
    std::function<void()> createobj13 =                                        \
        std::bind(&CLASS::__ReflectCreate##M13, this);                         \
    std::function<Object()> genItemObj1 =                                      \
        std::bind(&CLASS::__ReflectCreateListMember##M1, this);                \
    std::function<Object()> genItemObj2 =                                      \
        std::bind(&CLASS::__ReflectCreateListMember##M2, this);                \
    std::function<Object()> genItemObj3 =                                      \
        std::bind(&CLASS::__ReflectCreateListMember##M3, this);                \
    std::function<Object()> genItemObj4 =                                      \
        std::bind(&CLASS::__ReflectCreateListMember##M4, this);                \
    std::function<Object()> genItemObj5 =                                      \
        std::bind(&CLASS::__ReflectCreateListMember##M5, this);                \
    std::function<Object()> genItemObj6 =                                      \
        std::bind(&CLASS::__ReflectCreateListMember##M6, this);                \
    std::function<Object()> genItemObj7 =                                      \
        std::bind(&CLASS::__ReflectCreateListMember##M7, this);                \
    std::function<Object()> genItemObj8 =                                      \
        std::bind(&CLASS::__ReflectCreateListMember##M8, this);                \
    std::function<Object()> genItemObj9 =                                      \
        std::bind(&CLASS::__ReflectCreateListMember##M9, this);                \
    std::function<Object()> genItemObj10 =                                     \
        std::bind(&CLASS::__ReflectCreateListMember##M10, this);               \
    std::function<Object()> genItemObj11 =                                     \
        std::bind(&CLASS::__ReflectCreateListMember##M11, this);               \
    std::function<Object()> genItemObj12 =                                     \
        std::bind(&CLASS::__ReflectCreateListMember##M12, this);               \
    std::function<Object()> genItemObj13 =                                     \
        std::bind(&CLASS::__ReflectCreateListMember##M13, this);               \
    std::function<Object(int)> getItemObj1 = std::bind(                        \
        &CLASS::__ReflectGetListItem##M1, this, std::placeholders::_1);        \
    std::function<Object(int)> getItemObj2 = std::bind(                        \
        &CLASS::__ReflectGetListItem##M2, this, std::placeholders::_1);        \
    std::function<Object(int)> getItemObj3 = std::bind(                        \
        &CLASS::__ReflectGetListItem##M3, this, std::placeholders::_1);        \
    std::function<Object(int)> getItemObj4 = std::bind(                        \
        &CLASS::__ReflectGetListItem##M4, this, std::placeholders::_1);        \
    std::function<Object(int)> getItemObj5 = std::bind(                        \
        &CLASS::__ReflectGetListItem##M5, this, std::placeholders::_1);        \
    std::function<Object(int)> getItemObj6 = std::bind(                        \
        &CLASS::__ReflectGetListItem##M6, this, std::placeholders::_1);        \
    std::function<Object(int)> getItemObj7 = std::bind(                        \
        &CLASS::__ReflectGetListItem##M7, this, std::placeholders::_1);        \
    std::function<Object(int)> getItemObj8 = std::bind(                        \
        &CLASS::__ReflectGetListItem##M8, this, std::placeholders::_1);        \
    std::function<Object(int)> getItemObj9 = std::bind(                        \
        &CLASS::__ReflectGetListItem##M9, this, std::placeholders::_1);        \
    std::function<Object(int)> getItemObj10 = std::bind(                       \
        &CLASS::__ReflectGetListItem##M10, this, std::placeholders::_1);       \
    std::function<Object(int)> getItemObj11 = std::bind(                       \
        &CLASS::__ReflectGetListItem##M11, this, std::placeholders::_1);       \
    std::function<Object(int)> getItemObj12 = std::bind(                       \
        &CLASS::__ReflectGetListItem##M12, this, std::placeholders::_1);       \
    std::function<Object(int)> getItemObj13 = std::bind(                       \
        &CLASS::__ReflectGetListItem##M13, this, std::placeholders::_1);       \
    std::function<int()> getContainerSize1 =                                   \
        std::bind(&CLASS::__ReflectGetContainerSize##M1, this);                \
    std::function<int()> getContainerSize2 =                                   \
        std::bind(&CLASS::__ReflectGetContainerSize##M2, this);                \
    std::function<int()> getContainerSize3 =                                   \
        std::bind(&CLASS::__ReflectGetContainerSize##M3, this);                \
    std::function<int()> getContainerSize4 =                                   \
        std::bind(&CLASS::__ReflectGetContainerSize##M4, this);                \
    std::function<int()> getContainerSize5 =                                   \
        std::bind(&CLASS::__ReflectGetContainerSize##M5, this);                \
    std::function<int()> getContainerSize6 =                                   \
        std::bind(&CLASS::__ReflectGetContainerSize##M6, this);                \
    std::function<int()> getContainerSize7 =                                   \
        std::bind(&CLASS::__ReflectGetContainerSize##M7, this);                \
    std::function<int()> getContainerSize8 =                                   \
        std::bind(&CLASS::__ReflectGetContainerSize##M8, this);                \
    std::function<int()> getContainerSize9 =                                   \
        std::bind(&CLASS::__ReflectGetContainerSize##M9, this);                \
    std::function<int()> getContainerSize10 =                                  \
        std::bind(&CLASS::__ReflectGetContainerSize##M10, this);               \
    std::function<int()> getContainerSize11 =                                  \
        std::bind(&CLASS::__ReflectGetContainerSize##M11, this);               \
    std::function<int()> getContainerSize12 =                                  \
        std::bind(&CLASS::__ReflectGetContainerSize##M12, this);               \
    std::function<int()> getContainerSize13 =                                  \
        std::bind(&CLASS::__ReflectGetContainerSize##M13, this);               \
    std::function<Pair<Object, Object>()> createMapObj1 =              \
        std::bind(&CLASS::__ReflectCreateMapMember##M1, this);                 \
    std::function<ArrayList<Pair<Object, Object>>()> getMapItems1 =    \
        std::bind(&CLASS::__ReflectGetMapItems##M1, this);                     \
    std::function<Pair<Object, Object>()> createMapObj2 =              \
        std::bind(&CLASS::__ReflectCreateMapMember##M2, this);                 \
    std::function<ArrayList<Pair<Object, Object>>()> getMapItems2 =    \
        std::bind(&CLASS::__ReflectGetMapItems##M2, this);                     \
    std::function<Pair<Object, Object>()> createMapObj3 =              \
        std::bind(&CLASS::__ReflectCreateMapMember##M3, this);                 \
    std::function<ArrayList<Pair<Object, Object>>()> getMapItems3 =    \
        std::bind(&CLASS::__ReflectGetMapItems##M3, this);                     \
    std::function<Pair<Object, Object>()> createMapObj4 =              \
        std::bind(&CLASS::__ReflectCreateMapMember##M4, this);                 \
    std::function<ArrayList<Pair<Object, Object>>()> getMapItems4 =    \
        std::bind(&CLASS::__ReflectGetMapItems##M4, this);                     \
    std::function<Pair<Object, Object>()> createMapObj5 =              \
        std::bind(&CLASS::__ReflectCreateMapMember##M5, this);                 \
    std::function<ArrayList<Pair<Object, Object>>()> getMapItems5 =    \
        std::bind(&CLASS::__ReflectGetMapItems##M5, this);                     \
    std::function<Pair<Object, Object>()> createMapObj6 =              \
        std::bind(&CLASS::__ReflectCreateMapMember##M6, this);                 \
    std::function<ArrayList<Pair<Object, Object>>()> getMapItems6 =    \
        std::bind(&CLASS::__ReflectGetMapItems##M6, this);                     \
    std::function<Pair<Object, Object>()> createMapObj7 =              \
        std::bind(&CLASS::__ReflectCreateMapMember##M7, this);                 \
    std::function<ArrayList<Pair<Object, Object>>()> getMapItems7 =    \
        std::bind(&CLASS::__ReflectGetMapItems##M7, this);                     \
    std::function<Pair<Object, Object>()> createMapObj8 =              \
        std::bind(&CLASS::__ReflectCreateMapMember##M8, this);                 \
    std::function<ArrayList<Pair<Object, Object>>()> getMapItems8 =    \
        std::bind(&CLASS::__ReflectGetMapItems##M8, this);                     \
    std::function<Pair<Object, Object>()> createMapObj9 =              \
        std::bind(&CLASS::__ReflectCreateMapMember##M9, this);                 \
    std::function<ArrayList<Pair<Object, Object>>()> getMapItems9 =    \
        std::bind(&CLASS::__ReflectGetMapItems##M9, this);                     \
    std::function<Pair<Object, Object>()> createMapObj10 =             \
        std::bind(&CLASS::__ReflectCreateMapMember##M10, this);                \
    std::function<ArrayList<Pair<Object, Object>>()> getMapItems10 =   \
        std::bind(&CLASS::__ReflectGetMapItems##M10, this);                    \
    std::function<Pair<Object, Object>()> createMapObj11 =             \
        std::bind(&CLASS::__ReflectCreateMapMember##M11, this);                \
    std::function<ArrayList<Pair<Object, Object>>()> getMapItems11 =   \
        std::bind(&CLASS::__ReflectGetMapItems##M11, this);                    \
    std::function<Pair<Object, Object>()> createMapObj12 =             \
        std::bind(&CLASS::__ReflectCreateMapMember##M12, this);                \
    std::function<ArrayList<Pair<Object, Object>>()> getMapItems12 =   \
        std::bind(&CLASS::__ReflectGetMapItems##M12, this);                    \
    std::function<Pair<Object, Object>()> createMapObj13 =             \
        std::bind(&CLASS::__ReflectCreateMapMember##M13, this);                \
    std::function<ArrayList<Pair<Object, Object>>()> getMapItems13 =   \
        std::bind(&CLASS::__ReflectGetMapItems##M13, this);                    \
    std::function<void(Object)> addListItem = std::bind(                       \
        &CLASS::__ReflectAddListItem##M1, this, std::placeholders::_1);        \
    std::function<void(Object, Object)> addMapItem =                           \
        std::bind(&CLASS::__ReflectAddMapItem##M1, this,                       \
                  std::placeholders::_1, std::placeholders::_2);               \
    std::function<void(Object)> addListItem2 = std::bind(                      \
        &CLASS::__ReflectAddListItem##M2, this, std::placeholders::_1);        \
    std::function<void(Object, Object)> addMapItem2 =                          \
        std::bind(&CLASS::__ReflectAddMapItem##M2, this,                       \
                  std::placeholders::_1, std::placeholders::_2);               \
    std::function<void(Object)> addListItem3 = std::bind(                      \
        &CLASS::__ReflectAddListItem##M3, this, std::placeholders::_1);        \
    std::function<void(Object, Object)> addMapItem3 =                          \
        std::bind(&CLASS::__ReflectAddMapItem##M3, this,                       \
                  std::placeholders::_1, std::placeholders::_2);               \
    std::function<void(Object)> addListItem4 = std::bind(                      \
        &CLASS::__ReflectAddListItem##M4, this, std::placeholders::_1);        \
    std::function<void(Object, Object)> addMapItem4 =                          \
        std::bind(&CLASS::__ReflectAddMapItem##M4, this,                       \
                  std::placeholders::_1, std::placeholders::_2);               \
    std::function<void(Object)> addListItem5 = std::bind(                      \
        &CLASS::__ReflectAddListItem##M5, this, std::placeholders::_1);        \
    std::function<void(Object, Object)> addMapItem5 =                          \
        std::bind(&CLASS::__ReflectAddMapItem##M5, this,                       \
                  std::placeholders::_1, std::placeholders::_2);               \
    std::function<void(Object)> addListItem6 = std::bind(                      \
        &CLASS::__ReflectAddListItem##M6, this, std::placeholders::_1);        \
    std::function<void(Object, Object)> addMapItem6 =                          \
        std::bind(&CLASS::__ReflectAddMapItem##M6, this,                       \
                  std::placeholders::_1, std::placeholders::_2);               \
    std::function<void(Object)> addListItem7 = std::bind(                      \
        &CLASS::__ReflectAddListItem##M7, this, std::placeholders::_1);        \
    std::function<void(Object, Object)> addMapItem7 =                          \
        std::bind(&CLASS::__ReflectAddMapItem##M7, this,                       \
                  std::placeholders::_1, std::placeholders::_2);               \
    std::function<void(Object)> addListItem8 = std::bind(                      \
        &CLASS::__ReflectAddListItem##M8, this, std::placeholders::_1);        \
    std::function<void(Object, Object)> addMapItem8 =                          \
        std::bind(&CLASS::__ReflectAddMapItem##M8, this,                       \
                  std::placeholders::_1, std::placeholders::_2);               \
    std::function<void(Object)> addListItem9 = std::bind(                      \
        &CLASS::__ReflectAddListItem##M9, this, std::placeholders::_1);        \
    std::function<void(Object, Object)> addMapItem9 =                          \
        std::bind(&CLASS::__ReflectAddMapItem##M9, this,                       \
                  std::placeholders::_1, std::placeholders::_2);               \
    std::function<void(Object)> addListItem10 = std::bind(                     \
        &CLASS::__ReflectAddListItem##M10, this, std::placeholders::_1);       \
    std::function<void(Object, Object)> addMapItem10 =                         \
        std::bind(&CLASS::__ReflectAddMapItem##M10, this,                      \
                  std::placeholders::_1, std::placeholders::_2);               \
    std::function<void(Object)> addListItem11 = std::bind(                     \
        &CLASS::__ReflectAddListItem##M11, this, std::placeholders::_1);       \
    std::function<void(Object, Object)> addMapItem11 =                         \
        std::bind(&CLASS::__ReflectAddMapItem##M11, this,                      \
                  std::placeholders::_1, std::placeholders::_2);               \
    std::function<void(Object)> addListItem12 = std::bind(                     \
        &CLASS::__ReflectAddListItem##M12, this, std::placeholders::_1);       \
    std::function<void(Object, Object)> addMapItem12 =                         \
        std::bind(&CLASS::__ReflectAddMapItem##M12, this,                      \
                  std::placeholders::_1, std::placeholders::_2);               \
    std::function<void(Object)> addListItem13 = std::bind(                     \
        &CLASS::__ReflectAddListItem##M13, this, std::placeholders::_1);       \
    std::function<void(Object, Object)> addMapItem13 =                         \
        std::bind(&CLASS::__ReflectAddMapItem##M13, this,                      \
                  std::placeholders::_1, std::placeholders::_2);               \
    getFuncTuple = std::make_tuple(                                            \
        getobj1, getobj2, getobj3, getobj4, getobj5, getobj6, getobj7,         \
        getobj8, getobj9, getobj10, getobj11, getobj12, getobj13, dummyobj,    \
        dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj,  \
        dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj,  \
        dummyobj, dummyobj, dummyobj, dummyobj);                               \
    createFuncTuple = std::make_tuple(                                         \
        createobj1, createobj2, createobj3, createobj4, createobj5,            \
        createobj6, createobj7, createobj8, createobj9, createobj10,           \
        createobj11, createobj12, createobj13, dummyobj, dummyobj, dummyobj,   \
        dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj,  \
        dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj,  \
        dummyobj, dummyobj);                                                   \
    createListItemFuncTuple = std::make_tuple(                                 \
        genItemObj1, genItemObj2, genItemObj3, genItemObj4, genItemObj5,       \
        genItemObj6, genItemObj7, genItemObj8, genItemObj9, genItemObj10,      \
        genItemObj11, genItemObj12, genItemObj13, dummycreateobj,              \
        dummycreateobj, dummycreateobj, dummycreateobj, dummycreateobj,        \
        dummycreateobj, dummycreateobj, dummycreateobj, dummycreateobj,        \
        dummycreateobj, dummycreateobj, dummycreateobj, dummycreateobj,        \
        dummycreateobj, dummycreateobj, dummycreateobj, dummycreateobj,        \
        dummycreateobj, dummycreateobj);                                       \
    getListItemFuncTuple = std::make_tuple(                                    \
        getItemObj1, getItemObj2, getItemObj3, getItemObj4, getItemObj5,       \
        getItemObj6, getItemObj7, getItemObj8, getItemObj9, getItemObj10,      \
        getItemObj11, getItemObj12, getItemObj13, dummyligobj, dummyligobj,    \
        dummyligobj, dummyligobj, dummyligobj, dummyligobj, dummyligobj,       \
        dummyligobj, dummyligobj, dummyligobj, dummyligobj, dummyligobj,       \
        dummyligobj, dummyligobj, dummyligobj, dummyligobj, dummyligobj,       \
        dummyligobj, dummyligobj);                                             \
    getContainerSizeFuncTuple = std::make_tuple(                               \
        getContainerSize1, getContainerSize2, getContainerSize3,               \
        getContainerSize4, getContainerSize5, getContainerSize6,               \
        getContainerSize7, getContainerSize8, getContainerSize9,               \
        getContainerSize10, getContainerSize11, getContainerSize12,            \
        getContainerSize13, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj,  \
        dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj,  \
        dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj); \
    createMapItemFuncTuple = std::make_tuple(                                  \
        createMapObj1, createMapObj2, createMapObj3, createMapObj4,            \
        createMapObj5, createMapObj6, createMapObj7, createMapObj8,            \
        createMapObj9, createMapObj10, createMapObj11, createMapObj12,         \
        createMapObj13, dummycreateMapItem, dummycreateMapItem,                \
        dummycreateMapItem, dummycreateMapItem, dummycreateMapItem,            \
        dummycreateMapItem, dummycreateMapItem, dummycreateMapItem,            \
        dummycreateMapItem, dummycreateMapItem, dummycreateMapItem,            \
        dummycreateMapItem, dummycreateMapItem, dummycreateMapItem,            \
        dummycreateMapItem, dummycreateMapItem, dummycreateMapItem,            \
        dummycreateMapItem, dummycreateMapItem);                               \
    getMapItemsFuncTuple = std::make_tuple(                                    \
        getMapItems1, getMapItems2, getMapItems3, getMapItems4, getMapItems5,  \
        getMapItems6, getMapItems7, getMapItems8, getMapItems9, getMapItems10, \
        getMapItems11, getMapItems12, getMapItems13, dummygetMapItems,         \
        dummygetMapItems, dummygetMapItems, dummygetMapItems,                  \
        dummygetMapItems, dummygetMapItems, dummygetMapItems,                  \
        dummygetMapItems, dummygetMapItems, dummygetMapItems,                  \
        dummygetMapItems, dummygetMapItems, dummygetMapItems,                  \
        dummygetMapItems, dummygetMapItems, dummygetMapItems,                  \
        dummygetMapItems, dummygetMapItems, dummygetMapItems);                 \
    addListItemFuncTuple = std::make_tuple(                                    \
        addListItem, addListItem2, addListItem3, addListItem4, addListItem5,   \
        addListItem6, addListItem7, addListItem8, addListItem9, addListItem10, \
        addListItem11, addListItem12, addListItem13, dummyAddListItem,         \
        dummyAddListItem, dummyAddListItem, dummyAddListItem,                  \
        dummyAddListItem, dummyAddListItem, dummyAddListItem,                  \
        dummyAddListItem, dummyAddListItem, dummyAddListItem,                  \
        dummyAddListItem, dummyAddListItem, dummyAddListItem,                  \
        dummyAddListItem, dummyAddListItem, dummyAddListItem,                  \
        dummyAddListItem, dummyAddListItem, dummyAddListItem);                 \
    addMapItemFuncTuple = std::make_tuple(                                     \
        addMapItem, addMapItem2, addMapItem3, addMapItem4, addMapItem5,        \
        addMapItem6, addMapItem7, addMapItem8, addMapItem9, addMapItem10,      \
        addMapItem11, addMapItem12, addMapItem13, dummyAddMapItem,             \
        dummyAddMapItem, dummyAddMapItem, dummyAddMapItem, dummyAddMapItem,    \
        dummyAddMapItem, dummyAddMapItem, dummyAddMapItem, dummyAddMapItem,    \
        dummyAddMapItem, dummyAddMapItem, dummyAddMapItem, dummyAddMapItem,    \
        dummyAddMapItem, dummyAddMapItem, dummyAddMapItem, dummyAddMapItem,    \
        dummyAddMapItem, dummyAddMapItem);

#define IMPLE_INIT_TUPLE_14(CLASS, M1, M2, M3, M4, M5, M6, M7, M8, M9, M10,    \
                            M11, M12, M13, M14)                                \
    std::function<decltype(M1)()> getobj1 =                                    \
        std::bind(&CLASS::__ReflectGet##M1, this);                             \
    std::function<decltype(M2)()> getobj2 =                                    \
        std::bind(&CLASS::__ReflectGet##M2, this);                             \
    std::function<decltype(M3)()> getobj3 =                                    \
        std::bind(&CLASS::__ReflectGet##M3, this);                             \
    std::function<decltype(M4)()> getobj4 =                                    \
        std::bind(&CLASS::__ReflectGet##M4, this);                             \
    std::function<decltype(M5)()> getobj5 =                                    \
        std::bind(&CLASS::__ReflectGet##M5, this);                             \
    std::function<decltype(M6)()> getobj6 =                                    \
        std::bind(&CLASS::__ReflectGet##M6, this);                             \
    std::function<decltype(M7)()> getobj7 =                                    \
        std::bind(&CLASS::__ReflectGet##M7, this);                             \
    std::function<decltype(M8)()> getobj8 =                                    \
        std::bind(&CLASS::__ReflectGet##M8, this);                             \
    std::function<decltype(M9)()> getobj9 =                                    \
        std::bind(&CLASS::__ReflectGet##M9, this);                             \
    std::function<decltype(M10)()> getobj10 =                                  \
        std::bind(&CLASS::__ReflectGet##M10, this);                            \
    std::function<decltype(M11)()> getobj11 =                                  \
        std::bind(&CLASS::__ReflectGet##M11, this);                            \
    std::function<decltype(M12)()> getobj12 =                                  \
        std::bind(&CLASS::__ReflectGet##M12, this);                            \
    std::function<decltype(M13)()> getobj13 =                                  \
        std::bind(&CLASS::__ReflectGet##M13, this);                            \
    std::function<decltype(M14)()> getobj14 =                                  \
        std::bind(&CLASS::__ReflectGet##M14, this);                            \
    std::function<void()> createobj1 =                                         \
        std::bind(&CLASS::__ReflectCreate##M1, this);                          \
    std::function<void()> createobj2 =                                         \
        std::bind(&CLASS::__ReflectCreate##M2, this);                          \
    std::function<void()> createobj3 =                                         \
        std::bind(&CLASS::__ReflectCreate##M3, this);                          \
    std::function<void()> createobj4 =                                         \
        std::bind(&CLASS::__ReflectCreate##M4, this);                          \
    std::function<void()> createobj5 =                                         \
        std::bind(&CLASS::__ReflectCreate##M5, this);                          \
    std::function<void()> createobj6 =                                         \
        std::bind(&CLASS::__ReflectCreate##M6, this);                          \
    std::function<void()> createobj7 =                                         \
        std::bind(&CLASS::__ReflectCreate##M7, this);                          \
    std::function<void()> createobj8 =                                         \
        std::bind(&CLASS::__ReflectCreate##M8, this);                          \
    std::function<void()> createobj9 =                                         \
        std::bind(&CLASS::__ReflectCreate##M9, this);                          \
    std::function<void()> createobj10 =                                        \
        std::bind(&CLASS::__ReflectCreate##M10, this);                         \
    std::function<void()> createobj11 =                                        \
        std::bind(&CLASS::__ReflectCreate##M11, this);                         \
    std::function<void()> createobj12 =                                        \
        std::bind(&CLASS::__ReflectCreate##M12, this);                         \
    std::function<void()> createobj13 =                                        \
        std::bind(&CLASS::__ReflectCreate##M13, this);                         \
    std::function<void()> createobj14 =                                        \
        std::bind(&CLASS::__ReflectCreate##M14, this);                         \
    std::function<Object()> genItemObj1 =                                      \
        std::bind(&CLASS::__ReflectCreateListMember##M1, this);                \
    std::function<Object()> genItemObj2 =                                      \
        std::bind(&CLASS::__ReflectCreateListMember##M2, this);                \
    std::function<Object()> genItemObj3 =                                      \
        std::bind(&CLASS::__ReflectCreateListMember##M3, this);                \
    std::function<Object()> genItemObj4 =                                      \
        std::bind(&CLASS::__ReflectCreateListMember##M4, this);                \
    std::function<Object()> genItemObj5 =                                      \
        std::bind(&CLASS::__ReflectCreateListMember##M5, this);                \
    std::function<Object()> genItemObj6 =                                      \
        std::bind(&CLASS::__ReflectCreateListMember##M6, this);                \
    std::function<Object()> genItemObj7 =                                      \
        std::bind(&CLASS::__ReflectCreateListMember##M7, this);                \
    std::function<Object()> genItemObj8 =                                      \
        std::bind(&CLASS::__ReflectCreateListMember##M8, this);                \
    std::function<Object()> genItemObj9 =                                      \
        std::bind(&CLASS::__ReflectCreateListMember##M9, this);                \
    std::function<Object()> genItemObj10 =                                     \
        std::bind(&CLASS::__ReflectCreateListMember##M10, this);               \
    std::function<Object()> genItemObj11 =                                     \
        std::bind(&CLASS::__ReflectCreateListMember##M11, this);               \
    std::function<Object()> genItemObj12 =                                     \
        std::bind(&CLASS::__ReflectCreateListMember##M12, this);               \
    std::function<Object()> genItemObj13 =                                     \
        std::bind(&CLASS::__ReflectCreateListMember##M13, this);               \
    std::function<Object()> genItemObj14 =                                     \
        std::bind(&CLASS::__ReflectCreateListMember##M14, this);               \
    std::function<Object(int)> getItemObj1 = std::bind(                        \
        &CLASS::__ReflectGetListItem##M1, this, std::placeholders::_1);        \
    std::function<Object(int)> getItemObj2 = std::bind(                        \
        &CLASS::__ReflectGetListItem##M2, this, std::placeholders::_1);        \
    std::function<Object(int)> getItemObj3 = std::bind(                        \
        &CLASS::__ReflectGetListItem##M3, this, std::placeholders::_1);        \
    std::function<Object(int)> getItemObj4 = std::bind(                        \
        &CLASS::__ReflectGetListItem##M4, this, std::placeholders::_1);        \
    std::function<Object(int)> getItemObj5 = std::bind(                        \
        &CLASS::__ReflectGetListItem##M5, this, std::placeholders::_1);        \
    std::function<Object(int)> getItemObj6 = std::bind(                        \
        &CLASS::__ReflectGetListItem##M6, this, std::placeholders::_1);        \
    std::function<Object(int)> getItemObj7 = std::bind(                        \
        &CLASS::__ReflectGetListItem##M7, this, std::placeholders::_1);        \
    std::function<Object(int)> getItemObj8 = std::bind(                        \
        &CLASS::__ReflectGetListItem##M8, this, std::placeholders::_1);        \
    std::function<Object(int)> getItemObj9 = std::bind(                        \
        &CLASS::__ReflectGetListItem##M9, this, std::placeholders::_1);        \
    std::function<Object(int)> getItemObj10 = std::bind(                       \
        &CLASS::__ReflectGetListItem##M10, this, std::placeholders::_1);       \
    std::function<Object(int)> getItemObj11 = std::bind(                       \
        &CLASS::__ReflectGetListItem##M11, this, std::placeholders::_1);       \
    std::function<Object(int)> getItemObj12 = std::bind(                       \
        &CLASS::__ReflectGetListItem##M12, this, std::placeholders::_1);       \
    std::function<Object(int)> getItemObj13 = std::bind(                       \
        &CLASS::__ReflectGetListItem##M13, this, std::placeholders::_1);       \
    std::function<Object(int)> getItemObj14 = std::bind(                       \
        &CLASS::__ReflectGetListItem##M14, this, std::placeholders::_1);       \
    std::function<int()> getContainerSize1 =                                   \
        std::bind(&CLASS::__ReflectGetContainerSize##M1, this);                \
    std::function<int()> getContainerSize2 =                                   \
        std::bind(&CLASS::__ReflectGetContainerSize##M2, this);                \
    std::function<int()> getContainerSize3 =                                   \
        std::bind(&CLASS::__ReflectGetContainerSize##M3, this);                \
    std::function<int()> getContainerSize4 =                                   \
        std::bind(&CLASS::__ReflectGetContainerSize##M4, this);                \
    std::function<int()> getContainerSize5 =                                   \
        std::bind(&CLASS::__ReflectGetContainerSize##M5, this);                \
    std::function<int()> getContainerSize6 =                                   \
        std::bind(&CLASS::__ReflectGetContainerSize##M6, this);                \
    std::function<int()> getContainerSize7 =                                   \
        std::bind(&CLASS::__ReflectGetContainerSize##M7, this);                \
    std::function<int()> getContainerSize8 =                                   \
        std::bind(&CLASS::__ReflectGetContainerSize##M8, this);                \
    std::function<int()> getContainerSize9 =                                   \
        std::bind(&CLASS::__ReflectGetContainerSize##M9, this);                \
    std::function<int()> getContainerSize10 =                                  \
        std::bind(&CLASS::__ReflectGetContainerSize##M10, this);               \
    std::function<int()> getContainerSize11 =                                  \
        std::bind(&CLASS::__ReflectGetContainerSize##M11, this);               \
    std::function<int()> getContainerSize12 =                                  \
        std::bind(&CLASS::__ReflectGetContainerSize##M12, this);               \
    std::function<int()> getContainerSize13 =                                  \
        std::bind(&CLASS::__ReflectGetContainerSize##M13, this);               \
    std::function<int()> getContainerSize14 =                                  \
        std::bind(&CLASS::__ReflectGetContainerSize##M14, this);               \
    std::function<Pair<Object, Object>()> createMapObj1 =              \
        std::bind(&CLASS::__ReflectCreateMapMember##M1, this);                 \
    std::function<ArrayList<Pair<Object, Object>>()> getMapItems1 =    \
        std::bind(&CLASS::__ReflectGetMapItems##M1, this);                     \
    std::function<Pair<Object, Object>()> createMapObj2 =              \
        std::bind(&CLASS::__ReflectCreateMapMember##M2, this);                 \
    std::function<ArrayList<Pair<Object, Object>>()> getMapItems2 =    \
        std::bind(&CLASS::__ReflectGetMapItems##M2, this);                     \
    std::function<Pair<Object, Object>()> createMapObj3 =              \
        std::bind(&CLASS::__ReflectCreateMapMember##M3, this);                 \
    std::function<ArrayList<Pair<Object, Object>>()> getMapItems3 =    \
        std::bind(&CLASS::__ReflectGetMapItems##M3, this);                     \
    std::function<Pair<Object, Object>()> createMapObj4 =              \
        std::bind(&CLASS::__ReflectCreateMapMember##M4, this);                 \
    std::function<ArrayList<Pair<Object, Object>>()> getMapItems4 =    \
        std::bind(&CLASS::__ReflectGetMapItems##M4, this);                     \
    std::function<Pair<Object, Object>()> createMapObj5 =              \
        std::bind(&CLASS::__ReflectCreateMapMember##M5, this);                 \
    std::function<ArrayList<Pair<Object, Object>>()> getMapItems5 =    \
        std::bind(&CLASS::__ReflectGetMapItems##M5, this);                     \
    std::function<Pair<Object, Object>()> createMapObj6 =              \
        std::bind(&CLASS::__ReflectCreateMapMember##M6, this);                 \
    std::function<ArrayList<Pair<Object, Object>>()> getMapItems6 =    \
        std::bind(&CLASS::__ReflectGetMapItems##M6, this);                     \
    std::function<Pair<Object, Object>()> createMapObj7 =              \
        std::bind(&CLASS::__ReflectCreateMapMember##M7, this);                 \
    std::function<ArrayList<Pair<Object, Object>>()> getMapItems7 =    \
        std::bind(&CLASS::__ReflectGetMapItems##M7, this);                     \
    std::function<Pair<Object, Object>()> createMapObj8 =              \
        std::bind(&CLASS::__ReflectCreateMapMember##M8, this);                 \
    std::function<ArrayList<Pair<Object, Object>>()> getMapItems8 =    \
        std::bind(&CLASS::__ReflectGetMapItems##M8, this);                     \
    std::function<Pair<Object, Object>()> createMapObj9 =              \
        std::bind(&CLASS::__ReflectCreateMapMember##M9, this);                 \
    std::function<ArrayList<Pair<Object, Object>>()> getMapItems9 =    \
        std::bind(&CLASS::__ReflectGetMapItems##M9, this);                     \
    std::function<Pair<Object, Object>()> createMapObj10 =             \
        std::bind(&CLASS::__ReflectCreateMapMember##M10, this);                \
    std::function<ArrayList<Pair<Object, Object>>()> getMapItems10 =   \
        std::bind(&CLASS::__ReflectGetMapItems##M10, this);                    \
    std::function<Pair<Object, Object>()> createMapObj11 =             \
        std::bind(&CLASS::__ReflectCreateMapMember##M11, this);                \
    std::function<ArrayList<Pair<Object, Object>>()> getMapItems11 =   \
        std::bind(&CLASS::__ReflectGetMapItems##M11, this);                    \
    std::function<Pair<Object, Object>()> createMapObj12 =             \
        std::bind(&CLASS::__ReflectCreateMapMember##M12, this);                \
    std::function<ArrayList<Pair<Object, Object>>()> getMapItems12 =   \
        std::bind(&CLASS::__ReflectGetMapItems##M12, this);                    \
    std::function<Pair<Object, Object>()> createMapObj13 =             \
        std::bind(&CLASS::__ReflectCreateMapMember##M13, this);                \
    std::function<ArrayList<Pair<Object, Object>>()> getMapItems13 =   \
        std::bind(&CLASS::__ReflectGetMapItems##M13, this);                    \
    std::function<Pair<Object, Object>()> createMapObj14 =             \
        std::bind(&CLASS::__ReflectCreateMapMember##M14, this);                \
    std::function<ArrayList<Pair<Object, Object>>()> getMapItems14 =   \
        std::bind(&CLASS::__ReflectGetMapItems##M14, this);                    \
    std::function<void(Object)> addListItem = std::bind(                       \
        &CLASS::__ReflectAddListItem##M1, this, std::placeholders::_1);        \
    std::function<void(Object, Object)> addMapItem =                           \
        std::bind(&CLASS::__ReflectAddMapItem##M1, this,                       \
                  std::placeholders::_1, std::placeholders::_2);               \
    std::function<void(Object)> addListItem2 = std::bind(                      \
        &CLASS::__ReflectAddListItem##M2, this, std::placeholders::_1);        \
    std::function<void(Object, Object)> addMapItem2 =                          \
        std::bind(&CLASS::__ReflectAddMapItem##M2, this,                       \
                  std::placeholders::_1, std::placeholders::_2);               \
    std::function<void(Object)> addListItem3 = std::bind(                      \
        &CLASS::__ReflectAddListItem##M3, this, std::placeholders::_1);        \
    std::function<void(Object, Object)> addMapItem3 =                          \
        std::bind(&CLASS::__ReflectAddMapItem##M3, this,                       \
                  std::placeholders::_1, std::placeholders::_2);               \
    std::function<void(Object)> addListItem4 = std::bind(                      \
        &CLASS::__ReflectAddListItem##M4, this, std::placeholders::_1);        \
    std::function<void(Object, Object)> addMapItem4 =                          \
        std::bind(&CLASS::__ReflectAddMapItem##M4, this,                       \
                  std::placeholders::_1, std::placeholders::_2);               \
    std::function<void(Object)> addListItem5 = std::bind(                      \
        &CLASS::__ReflectAddListItem##M5, this, std::placeholders::_1);        \
    std::function<void(Object, Object)> addMapItem5 =                          \
        std::bind(&CLASS::__ReflectAddMapItem##M5, this,                       \
                  std::placeholders::_1, std::placeholders::_2);               \
    std::function<void(Object)> addListItem6 = std::bind(                      \
        &CLASS::__ReflectAddListItem##M6, this, std::placeholders::_1);        \
    std::function<void(Object, Object)> addMapItem6 =                          \
        std::bind(&CLASS::__ReflectAddMapItem##M6, this,                       \
                  std::placeholders::_1, std::placeholders::_2);               \
    std::function<void(Object)> addListItem7 = std::bind(                      \
        &CLASS::__ReflectAddListItem##M7, this, std::placeholders::_1);        \
    std::function<void(Object, Object)> addMapItem7 =                          \
        std::bind(&CLASS::__ReflectAddMapItem##M7, this,                       \
                  std::placeholders::_1, std::placeholders::_2);               \
    std::function<void(Object)> addListItem8 = std::bind(                      \
        &CLASS::__ReflectAddListItem##M8, this, std::placeholders::_1);        \
    std::function<void(Object, Object)> addMapItem8 =                          \
        std::bind(&CLASS::__ReflectAddMapItem##M8, this,                       \
                  std::placeholders::_1, std::placeholders::_2);               \
    std::function<void(Object)> addListItem9 = std::bind(                      \
        &CLASS::__ReflectAddListItem##M9, this, std::placeholders::_1);        \
    std::function<void(Object, Object)> addMapItem9 =                          \
        std::bind(&CLASS::__ReflectAddMapItem##M9, this,                       \
                  std::placeholders::_1, std::placeholders::_2);               \
    std::function<void(Object)> addListItem10 = std::bind(                     \
        &CLASS::__ReflectAddListItem##M10, this, std::placeholders::_1);       \
    std::function<void(Object, Object)> addMapItem10 =                         \
        std::bind(&CLASS::__ReflectAddMapItem##M10, this,                      \
                  std::placeholders::_1, std::placeholders::_2);               \
    std::function<void(Object)> addListItem11 = std::bind(                     \
        &CLASS::__ReflectAddListItem##M11, this, std::placeholders::_1);       \
    std::function<void(Object, Object)> addMapItem11 =                         \
        std::bind(&CLASS::__ReflectAddMapItem##M11, this,                      \
                  std::placeholders::_1, std::placeholders::_2);               \
    std::function<void(Object)> addListItem12 = std::bind(                     \
        &CLASS::__ReflectAddListItem##M12, this, std::placeholders::_1);       \
    std::function<void(Object, Object)> addMapItem12 =                         \
        std::bind(&CLASS::__ReflectAddMapItem##M12, this,                      \
                  std::placeholders::_1, std::placeholders::_2);               \
    std::function<void(Object)> addListItem13 = std::bind(                     \
        &CLASS::__ReflectAddListItem##M13, this, std::placeholders::_1);       \
    std::function<void(Object, Object)> addMapItem13 =                         \
        std::bind(&CLASS::__ReflectAddMapItem##M13, this,                      \
                  std::placeholders::_1, std::placeholders::_2);               \
    std::function<void(Object)> addListItem14 = std::bind(                     \
        &CLASS::__ReflectAddListItem##M14, this, std::placeholders::_1);       \
    std::function<void(Object, Object)> addMapItem14 =                         \
        std::bind(&CLASS::__ReflectAddMapItem##M14, this,                      \
                  std::placeholders::_1, std::placeholders::_2);               \
    getFuncTuple = std::make_tuple(                                            \
        getobj1, getobj2, getobj3, getobj4, getobj5, getobj6, getobj7,         \
        getobj8, getobj9, getobj10, getobj11, getobj12, getobj13, getobj14,    \
        dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj,  \
        dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj,  \
        dummyobj, dummyobj, dummyobj, dummyobj);                               \
    createFuncTuple = std::make_tuple(                                         \
        createobj1, createobj2, createobj3, createobj4, createobj5,            \
        createobj6, createobj7, createobj8, createobj9, createobj10,           \
        createobj11, createobj12, createobj13, createobj14, dummyobj,          \
        dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj,  \
        dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj,  \
        dummyobj, dummyobj, dummyobj);                                         \
    createListItemFuncTuple = std::make_tuple(                                 \
        genItemObj1, genItemObj2, genItemObj3, genItemObj4, genItemObj5,       \
        genItemObj6, genItemObj7, genItemObj8, genItemObj9, genItemObj10,      \
        genItemObj11, genItemObj12, genItemObj13, genItemObj14,                \
        dummycreateobj, dummycreateobj, dummycreateobj, dummycreateobj,        \
        dummycreateobj, dummycreateobj, dummycreateobj, dummycreateobj,        \
        dummycreateobj, dummycreateobj, dummycreateobj, dummycreateobj,        \
        dummycreateobj, dummycreateobj, dummycreateobj, dummycreateobj,        \
        dummycreateobj, dummycreateobj);                                       \
    getListItemFuncTuple = std::make_tuple(                                    \
        getItemObj1, getItemObj2, getItemObj3, getItemObj4, getItemObj5,       \
        getItemObj6, getItemObj7, getItemObj8, getItemObj9, getItemObj10,      \
        getItemObj11, getItemObj12, getItemObj13, getItemObj14, dummyligobj,   \
        dummyligobj, dummyligobj, dummyligobj, dummyligobj, dummyligobj,       \
        dummyligobj, dummyligobj, dummyligobj, dummyligobj, dummyligobj,       \
        dummyligobj, dummyligobj, dummyligobj, dummyligobj, dummyligobj,       \
        dummyligobj, dummyligobj);                                             \
    getContainerSizeFuncTuple = std::make_tuple(                               \
        getContainerSize1, getContainerSize2, getContainerSize3,               \
        getContainerSize4, getContainerSize5, getContainerSize6,               \
        getContainerSize7, getContainerSize8, getContainerSize9,               \
        getContainerSize10, getContainerSize11, getContainerSize12,            \
        getContainerSize13, getContainerSize14, dummyobj, dummyobj, dummyobj,  \
        dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj,  \
        dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj,  \
        dummyobj);                                                             \
    createMapItemFuncTuple = std::make_tuple(                                  \
        createMapObj1, createMapObj2, createMapObj3, createMapObj4,            \
        createMapObj5, createMapObj6, createMapObj7, createMapObj8,            \
        createMapObj9, createMapObj10, createMapObj11, createMapObj12,         \
        createMapObj13, createMapObj14, dummycreateMapItem,                    \
        dummycreateMapItem, dummycreateMapItem, dummycreateMapItem,            \
        dummycreateMapItem, dummycreateMapItem, dummycreateMapItem,            \
        dummycreateMapItem, dummycreateMapItem, dummycreateMapItem,            \
        dummycreateMapItem, dummycreateMapItem, dummycreateMapItem,            \
        dummycreateMapItem, dummycreateMapItem, dummycreateMapItem,            \
        dummycreateMapItem, dummycreateMapItem);                               \
    getMapItemsFuncTuple = std::make_tuple(                                    \
        getMapItems1, getMapItems2, getMapItems3, getMapItems4, getMapItems5,  \
        getMapItems6, getMapItems7, getMapItems8, getMapItems9, getMapItems10, \
        getMapItems11, getMapItems12, getMapItems13, getMapItems14,            \
        dummygetMapItems, dummygetMapItems, dummygetMapItems,                  \
        dummygetMapItems, dummygetMapItems, dummygetMapItems,                  \
        dummygetMapItems, dummygetMapItems, dummygetMapItems,                  \
        dummygetMapItems, dummygetMapItems, dummygetMapItems,                  \
        dummygetMapItems, dummygetMapItems, dummygetMapItems,                  \
        dummygetMapItems, dummygetMapItems, dummygetMapItems);                 \
    addListItemFuncTuple = std::make_tuple(                                    \
        addListItem, addListItem2, addListItem3, addListItem4, addListItem5,   \
        addListItem6, addListItem7, addListItem8, addListItem9, addListItem10, \
        addListItem11, addListItem12, addListItem13, addListItem14,            \
        dummyAddListItem, dummyAddListItem, dummyAddListItem,                  \
        dummyAddListItem, dummyAddListItem, dummyAddListItem,                  \
        dummyAddListItem, dummyAddListItem, dummyAddListItem,                  \
        dummyAddListItem, dummyAddListItem, dummyAddListItem,                  \
        dummyAddListItem, dummyAddListItem, dummyAddListItem,                  \
        dummyAddListItem, dummyAddListItem, dummyAddListItem);                 \
    addMapItemFuncTuple = std::make_tuple(                                     \
        addMapItem, addMapItem2, addMapItem3, addMapItem4, addMapItem5,        \
        addMapItem6, addMapItem7, addMapItem8, addMapItem9, addMapItem10,      \
        addMapItem11, addMapItem12, addMapItem13, addMapItem14,                \
        dummyAddMapItem, dummyAddMapItem, dummyAddMapItem, dummyAddMapItem,    \
        dummyAddMapItem, dummyAddMapItem, dummyAddMapItem, dummyAddMapItem,    \
        dummyAddMapItem, dummyAddMapItem, dummyAddMapItem, dummyAddMapItem,    \
        dummyAddMapItem, dummyAddMapItem, dummyAddMapItem, dummyAddMapItem,    \
        dummyAddMapItem, dummyAddMapItem);

#define IMPLE_INIT_TUPLE_15(CLASS, M1, M2, M3, M4, M5, M6, M7, M8, M9, M10,    \
                            M11, M12, M13, M14, M15)                           \
    std::function<decltype(M1)()> getobj1 =                                    \
        std::bind(&CLASS::__ReflectGet##M1, this);                             \
    std::function<decltype(M2)()> getobj2 =                                    \
        std::bind(&CLASS::__ReflectGet##M2, this);                             \
    std::function<decltype(M3)()> getobj3 =                                    \
        std::bind(&CLASS::__ReflectGet##M3, this);                             \
    std::function<decltype(M4)()> getobj4 =                                    \
        std::bind(&CLASS::__ReflectGet##M4, this);                             \
    std::function<decltype(M5)()> getobj5 =                                    \
        std::bind(&CLASS::__ReflectGet##M5, this);                             \
    std::function<decltype(M6)()> getobj6 =                                    \
        std::bind(&CLASS::__ReflectGet##M6, this);                             \
    std::function<decltype(M7)()> getobj7 =                                    \
        std::bind(&CLASS::__ReflectGet##M7, this);                             \
    std::function<decltype(M8)()> getobj8 =                                    \
        std::bind(&CLASS::__ReflectGet##M8, this);                             \
    std::function<decltype(M9)()> getobj9 =                                    \
        std::bind(&CLASS::__ReflectGet##M9, this);                             \
    std::function<decltype(M10)()> getobj10 =                                  \
        std::bind(&CLASS::__ReflectGet##M10, this);                            \
    std::function<decltype(M11)()> getobj11 =                                  \
        std::bind(&CLASS::__ReflectGet##M11, this);                            \
    std::function<decltype(M12)()> getobj12 =                                  \
        std::bind(&CLASS::__ReflectGet##M12, this);                            \
    std::function<decltype(M13)()> getobj13 =                                  \
        std::bind(&CLASS::__ReflectGet##M13, this);                            \
    std::function<decltype(M14)()> getobj14 =                                  \
        std::bind(&CLASS::__ReflectGet##M14, this);                            \
    std::function<decltype(M15)()> getobj15 =                                  \
        std::bind(&CLASS::__ReflectGet##M15, this);                            \
    std::function<void()> createobj1 =                                         \
        std::bind(&CLASS::__ReflectCreate##M1, this);                          \
    std::function<void()> createobj2 =                                         \
        std::bind(&CLASS::__ReflectCreate##M2, this);                          \
    std::function<void()> createobj3 =                                         \
        std::bind(&CLASS::__ReflectCreate##M3, this);                          \
    std::function<void()> createobj4 =                                         \
        std::bind(&CLASS::__ReflectCreate##M4, this);                          \
    std::function<void()> createobj5 =                                         \
        std::bind(&CLASS::__ReflectCreate##M5, this);                          \
    std::function<void()> createobj6 =                                         \
        std::bind(&CLASS::__ReflectCreate##M6, this);                          \
    std::function<void()> createobj7 =                                         \
        std::bind(&CLASS::__ReflectCreate##M7, this);                          \
    std::function<void()> createobj8 =                                         \
        std::bind(&CLASS::__ReflectCreate##M8, this);                          \
    std::function<void()> createobj9 =                                         \
        std::bind(&CLASS::__ReflectCreate##M9, this);                          \
    std::function<void()> createobj10 =                                        \
        std::bind(&CLASS::__ReflectCreate##M10, this);                         \
    std::function<void()> createobj11 =                                        \
        std::bind(&CLASS::__ReflectCreate##M11, this);                         \
    std::function<void()> createobj12 =                                        \
        std::bind(&CLASS::__ReflectCreate##M12, this);                         \
    std::function<void()> createobj13 =                                        \
        std::bind(&CLASS::__ReflectCreate##M13, this);                         \
    std::function<void()> createobj14 =                                        \
        std::bind(&CLASS::__ReflectCreate##M14, this);                         \
    std::function<void()> createobj15 =                                        \
        std::bind(&CLASS::__ReflectCreate##M15, this);                         \
    std::function<Object()> genItemObj1 =                                      \
        std::bind(&CLASS::__ReflectCreateListMember##M1, this);                \
    std::function<Object()> genItemObj2 =                                      \
        std::bind(&CLASS::__ReflectCreateListMember##M2, this);                \
    std::function<Object()> genItemObj3 =                                      \
        std::bind(&CLASS::__ReflectCreateListMember##M3, this);                \
    std::function<Object()> genItemObj4 =                                      \
        std::bind(&CLASS::__ReflectCreateListMember##M4, this);                \
    std::function<Object()> genItemObj5 =                                      \
        std::bind(&CLASS::__ReflectCreateListMember##M5, this);                \
    std::function<Object()> genItemObj6 =                                      \
        std::bind(&CLASS::__ReflectCreateListMember##M6, this);                \
    std::function<Object()> genItemObj7 =                                      \
        std::bind(&CLASS::__ReflectCreateListMember##M7, this);                \
    std::function<Object()> genItemObj8 =                                      \
        std::bind(&CLASS::__ReflectCreateListMember##M8, this);                \
    std::function<Object()> genItemObj9 =                                      \
        std::bind(&CLASS::__ReflectCreateListMember##M9, this);                \
    std::function<Object()> genItemObj10 =                                     \
        std::bind(&CLASS::__ReflectCreateListMember##M10, this);               \
    std::function<Object()> genItemObj11 =                                     \
        std::bind(&CLASS::__ReflectCreateListMember##M11, this);               \
    std::function<Object()> genItemObj12 =                                     \
        std::bind(&CLASS::__ReflectCreateListMember##M12, this);               \
    std::function<Object()> genItemObj13 =                                     \
        std::bind(&CLASS::__ReflectCreateListMember##M13, this);               \
    std::function<Object()> genItemObj14 =                                     \
        std::bind(&CLASS::__ReflectCreateListMember##M14, this);               \
    std::function<Object()> genItemObj15 =                                     \
        std::bind(&CLASS::__ReflectCreateListMember##M15, this);               \
    std::function<Object(int)> getItemObj1 = std::bind(                        \
        &CLASS::__ReflectGetListItem##M1, this, std::placeholders::_1);        \
    std::function<Object(int)> getItemObj2 = std::bind(                        \
        &CLASS::__ReflectGetListItem##M2, this, std::placeholders::_1);        \
    std::function<Object(int)> getItemObj3 = std::bind(                        \
        &CLASS::__ReflectGetListItem##M3, this, std::placeholders::_1);        \
    std::function<Object(int)> getItemObj4 = std::bind(                        \
        &CLASS::__ReflectGetListItem##M4, this, std::placeholders::_1);        \
    std::function<Object(int)> getItemObj5 = std::bind(                        \
        &CLASS::__ReflectGetListItem##M5, this, std::placeholders::_1);        \
    std::function<Object(int)> getItemObj6 = std::bind(                        \
        &CLASS::__ReflectGetListItem##M6, this, std::placeholders::_1);        \
    std::function<Object(int)> getItemObj7 = std::bind(                        \
        &CLASS::__ReflectGetListItem##M7, this, std::placeholders::_1);        \
    std::function<Object(int)> getItemObj8 = std::bind(                        \
        &CLASS::__ReflectGetListItem##M8, this, std::placeholders::_1);        \
    std::function<Object(int)> getItemObj9 = std::bind(                        \
        &CLASS::__ReflectGetListItem##M9, this, std::placeholders::_1);        \
    std::function<Object(int)> getItemObj10 = std::bind(                       \
        &CLASS::__ReflectGetListItem##M10, this, std::placeholders::_1);       \
    std::function<Object(int)> getItemObj11 = std::bind(                       \
        &CLASS::__ReflectGetListItem##M11, this, std::placeholders::_1);       \
    std::function<Object(int)> getItemObj12 = std::bind(                       \
        &CLASS::__ReflectGetListItem##M12, this, std::placeholders::_1);       \
    std::function<Object(int)> getItemObj13 = std::bind(                       \
        &CLASS::__ReflectGetListItem##M13, this, std::placeholders::_1);       \
    std::function<Object(int)> getItemObj14 = std::bind(                       \
        &CLASS::__ReflectGetListItem##M14, this, std::placeholders::_1);       \
    std::function<Object(int)> getItemObj15 = std::bind(                       \
        &CLASS::__ReflectGetListItem##M15, this, std::placeholders::_1);       \
    std::function<int()> getContainerSize1 =                                   \
        std::bind(&CLASS::__ReflectGetContainerSize##M1, this);                \
    std::function<int()> getContainerSize2 =                                   \
        std::bind(&CLASS::__ReflectGetContainerSize##M2, this);                \
    std::function<int()> getContainerSize3 =                                   \
        std::bind(&CLASS::__ReflectGetContainerSize##M3, this);                \
    std::function<int()> getContainerSize4 =                                   \
        std::bind(&CLASS::__ReflectGetContainerSize##M4, this);                \
    std::function<int()> getContainerSize5 =                                   \
        std::bind(&CLASS::__ReflectGetContainerSize##M5, this);                \
    std::function<int()> getContainerSize6 =                                   \
        std::bind(&CLASS::__ReflectGetContainerSize##M6, this);                \
    std::function<int()> getContainerSize7 =                                   \
        std::bind(&CLASS::__ReflectGetContainerSize##M7, this);                \
    std::function<int()> getContainerSize8 =                                   \
        std::bind(&CLASS::__ReflectGetContainerSize##M8, this);                \
    std::function<int()> getContainerSize9 =                                   \
        std::bind(&CLASS::__ReflectGetContainerSize##M9, this);                \
    std::function<int()> getContainerSize10 =                                  \
        std::bind(&CLASS::__ReflectGetContainerSize##M10, this);               \
    std::function<int()> getContainerSize11 =                                  \
        std::bind(&CLASS::__ReflectGetContainerSize##M11, this);               \
    std::function<int()> getContainerSize12 =                                  \
        std::bind(&CLASS::__ReflectGetContainerSize##M12, this);               \
    std::function<int()> getContainerSize13 =                                  \
        std::bind(&CLASS::__ReflectGetContainerSize##M13, this);               \
    std::function<int()> getContainerSize14 =                                  \
        std::bind(&CLASS::__ReflectGetContainerSize##M14, this);               \
    std::function<int()> getContainerSize15 =                                  \
        std::bind(&CLASS::__ReflectGetContainerSize##M15, this);               \
    std::function<Pair<Object, Object>()> createMapObj1 =              \
        std::bind(&CLASS::__ReflectCreateMapMember##M1, this);                 \
    std::function<ArrayList<Pair<Object, Object>>()> getMapItems1 =    \
        std::bind(&CLASS::__ReflectGetMapItems##M1, this);                     \
    std::function<Pair<Object, Object>()> createMapObj2 =              \
        std::bind(&CLASS::__ReflectCreateMapMember##M2, this);                 \
    std::function<ArrayList<Pair<Object, Object>>()> getMapItems2 =    \
        std::bind(&CLASS::__ReflectGetMapItems##M2, this);                     \
    std::function<Pair<Object, Object>()> createMapObj3 =              \
        std::bind(&CLASS::__ReflectCreateMapMember##M3, this);                 \
    std::function<ArrayList<Pair<Object, Object>>()> getMapItems3 =    \
        std::bind(&CLASS::__ReflectGetMapItems##M3, this);                     \
    std::function<Pair<Object, Object>()> createMapObj4 =              \
        std::bind(&CLASS::__ReflectCreateMapMember##M4, this);                 \
    std::function<ArrayList<Pair<Object, Object>>()> getMapItems4 =    \
        std::bind(&CLASS::__ReflectGetMapItems##M4, this);                     \
    std::function<Pair<Object, Object>()> createMapObj5 =              \
        std::bind(&CLASS::__ReflectCreateMapMember##M5, this);                 \
    std::function<ArrayList<Pair<Object, Object>>()> getMapItems5 =    \
        std::bind(&CLASS::__ReflectGetMapItems##M5, this);                     \
    std::function<Pair<Object, Object>()> createMapObj6 =              \
        std::bind(&CLASS::__ReflectCreateMapMember##M6, this);                 \
    std::function<ArrayList<Pair<Object, Object>>()> getMapItems6 =    \
        std::bind(&CLASS::__ReflectGetMapItems##M6, this);                     \
    std::function<Pair<Object, Object>()> createMapObj7 =              \
        std::bind(&CLASS::__ReflectCreateMapMember##M7, this);                 \
    std::function<ArrayList<Pair<Object, Object>>()> getMapItems7 =    \
        std::bind(&CLASS::__ReflectGetMapItems##M7, this);                     \
    std::function<Pair<Object, Object>()> createMapObj8 =              \
        std::bind(&CLASS::__ReflectCreateMapMember##M8, this);                 \
    std::function<ArrayList<Pair<Object, Object>>()> getMapItems8 =    \
        std::bind(&CLASS::__ReflectGetMapItems##M8, this);                     \
    std::function<Pair<Object, Object>()> createMapObj9 =              \
        std::bind(&CLASS::__ReflectCreateMapMember##M9, this);                 \
    std::function<ArrayList<Pair<Object, Object>>()> getMapItems9 =    \
        std::bind(&CLASS::__ReflectGetMapItems##M9, this);                     \
    std::function<Pair<Object, Object>()> createMapObj10 =             \
        std::bind(&CLASS::__ReflectCreateMapMember##M10, this);                \
    std::function<ArrayList<Pair<Object, Object>>()> getMapItems10 =   \
        std::bind(&CLASS::__ReflectGetMapItems##M10, this);                    \
    std::function<Pair<Object, Object>()> createMapObj11 =             \
        std::bind(&CLASS::__ReflectCreateMapMember##M11, this);                \
    std::function<ArrayList<Pair<Object, Object>>()> getMapItems11 =   \
        std::bind(&CLASS::__ReflectGetMapItems##M11, this);                    \
    std::function<Pair<Object, Object>()> createMapObj12 =             \
        std::bind(&CLASS::__ReflectCreateMapMember##M12, this);                \
    std::function<ArrayList<Pair<Object, Object>>()> getMapItems12 =   \
        std::bind(&CLASS::__ReflectGetMapItems##M12, this);                    \
    std::function<Pair<Object, Object>()> createMapObj13 =             \
        std::bind(&CLASS::__ReflectCreateMapMember##M13, this);                \
    std::function<ArrayList<Pair<Object, Object>>()> getMapItems13 =   \
        std::bind(&CLASS::__ReflectGetMapItems##M13, this);                    \
    std::function<Pair<Object, Object>()> createMapObj14 =             \
        std::bind(&CLASS::__ReflectCreateMapMember##M14, this);                \
    std::function<ArrayList<Pair<Object, Object>>()> getMapItems14 =   \
        std::bind(&CLASS::__ReflectGetMapItems##M14, this);                    \
    std::function<Pair<Object, Object>()> createMapObj15 =             \
        std::bind(&CLASS::__ReflectCreateMapMember##M15, this);                \
    std::function<ArrayList<Pair<Object, Object>>()> getMapItems15 =   \
        std::bind(&CLASS::__ReflectGetMapItems##M15, this);                    \
    std::function<void(Object)> addListItem = std::bind(                       \
        &CLASS::__ReflectAddListItem##M1, this, std::placeholders::_1);        \
    std::function<void(Object, Object)> addMapItem =                           \
        std::bind(&CLASS::__ReflectAddMapItem##M1, this,                       \
                  std::placeholders::_1, std::placeholders::_2);               \
    std::function<void(Object)> addListItem2 = std::bind(                      \
        &CLASS::__ReflectAddListItem##M2, this, std::placeholders::_1);        \
    std::function<void(Object, Object)> addMapItem2 =                          \
        std::bind(&CLASS::__ReflectAddMapItem##M2, this,                       \
                  std::placeholders::_1, std::placeholders::_2);               \
    std::function<void(Object)> addListItem3 = std::bind(                      \
        &CLASS::__ReflectAddListItem##M3, this, std::placeholders::_1);        \
    std::function<void(Object, Object)> addMapItem3 =                          \
        std::bind(&CLASS::__ReflectAddMapItem##M3, this,                       \
                  std::placeholders::_1, std::placeholders::_2);               \
    std::function<void(Object)> addListItem4 = std::bind(                      \
        &CLASS::__ReflectAddListItem##M4, this, std::placeholders::_1);        \
    std::function<void(Object, Object)> addMapItem4 =                          \
        std::bind(&CLASS::__ReflectAddMapItem##M4, this,                       \
                  std::placeholders::_1, std::placeholders::_2);               \
    std::function<void(Object)> addListItem5 = std::bind(                      \
        &CLASS::__ReflectAddListItem##M5, this, std::placeholders::_1);        \
    std::function<void(Object, Object)> addMapItem5 =                          \
        std::bind(&CLASS::__ReflectAddMapItem##M5, this,                       \
                  std::placeholders::_1, std::placeholders::_2);               \
    std::function<void(Object)> addListItem6 = std::bind(                      \
        &CLASS::__ReflectAddListItem##M6, this, std::placeholders::_1);        \
    std::function<void(Object, Object)> addMapItem6 =                          \
        std::bind(&CLASS::__ReflectAddMapItem##M6, this,                       \
                  std::placeholders::_1, std::placeholders::_2);               \
    std::function<void(Object)> addListItem7 = std::bind(                      \
        &CLASS::__ReflectAddListItem##M7, this, std::placeholders::_1);        \
    std::function<void(Object, Object)> addMapItem7 =                          \
        std::bind(&CLASS::__ReflectAddMapItem##M7, this,                       \
                  std::placeholders::_1, std::placeholders::_2);               \
    std::function<void(Object)> addListItem8 = std::bind(                      \
        &CLASS::__ReflectAddListItem##M8, this, std::placeholders::_1);        \
    std::function<void(Object, Object)> addMapItem8 =                          \
        std::bind(&CLASS::__ReflectAddMapItem##M8, this,                       \
                  std::placeholders::_1, std::placeholders::_2);               \
    std::function<void(Object)> addListItem9 = std::bind(                      \
        &CLASS::__ReflectAddListItem##M9, this, std::placeholders::_1);        \
    std::function<void(Object, Object)> addMapItem9 =                          \
        std::bind(&CLASS::__ReflectAddMapItem##M9, this,                       \
                  std::placeholders::_1, std::placeholders::_2);               \
    std::function<void(Object)> addListItem10 = std::bind(                     \
        &CLASS::__ReflectAddListItem##M10, this, std::placeholders::_1);       \
    std::function<void(Object, Object)> addMapItem10 =                         \
        std::bind(&CLASS::__ReflectAddMapItem##M10, this,                      \
                  std::placeholders::_1, std::placeholders::_2);               \
    std::function<void(Object)> addListItem11 = std::bind(                     \
        &CLASS::__ReflectAddListItem##M11, this, std::placeholders::_1);       \
    std::function<void(Object, Object)> addMapItem11 =                         \
        std::bind(&CLASS::__ReflectAddMapItem##M11, this,                      \
                  std::placeholders::_1, std::placeholders::_2);               \
    std::function<void(Object)> addListItem12 = std::bind(                     \
        &CLASS::__ReflectAddListItem##M12, this, std::placeholders::_1);       \
    std::function<void(Object, Object)> addMapItem12 =                         \
        std::bind(&CLASS::__ReflectAddMapItem##M12, this,                      \
                  std::placeholders::_1, std::placeholders::_2);               \
    std::function<void(Object)> addListItem13 = std::bind(                     \
        &CLASS::__ReflectAddListItem##M13, this, std::placeholders::_1);       \
    std::function<void(Object, Object)> addMapItem13 =                         \
        std::bind(&CLASS::__ReflectAddMapItem##M13, this,                      \
                  std::placeholders::_1, std::placeholders::_2);               \
    std::function<void(Object)> addListItem14 = std::bind(                     \
        &CLASS::__ReflectAddListItem##M14, this, std::placeholders::_1);       \
    std::function<void(Object, Object)> addMapItem14 =                         \
        std::bind(&CLASS::__ReflectAddMapItem##M14, this,                      \
                  std::placeholders::_1, std::placeholders::_2);               \
    std::function<void(Object)> addListItem15 = std::bind(                     \
        &CLASS::__ReflectAddListItem##M15, this, std::placeholders::_1);       \
    std::function<void(Object, Object)> addMapItem15 =                         \
        std::bind(&CLASS::__ReflectAddMapItem##M15, this,                      \
                  std::placeholders::_1, std::placeholders::_2);               \
    getFuncTuple = std::make_tuple(                                            \
        getobj1, getobj2, getobj3, getobj4, getobj5, getobj6, getobj7,         \
        getobj8, getobj9, getobj10, getobj11, getobj12, getobj13, getobj14,    \
        getobj15, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj,  \
        dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj,  \
        dummyobj, dummyobj, dummyobj, dummyobj);                               \
    createFuncTuple = std::make_tuple(                                         \
        createobj1, createobj2, createobj3, createobj4, createobj5,            \
        createobj6, createobj7, createobj8, createobj9, createobj10,           \
        createobj11, createobj12, createobj13, createobj14, createobj15,       \
        dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj,  \
        dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj,  \
        dummyobj, dummyobj, dummyobj);                                         \
    createListItemFuncTuple = std::make_tuple(                                 \
        genItemObj1, genItemObj2, genItemObj3, genItemObj4, genItemObj5,       \
        genItemObj6, genItemObj7, genItemObj8, genItemObj9, genItemObj10,      \
        genItemObj11, genItemObj12, genItemObj13, genItemObj14, genItemObj15,  \
        dummycreateobj, dummycreateobj, dummycreateobj, dummycreateobj,        \
        dummycreateobj, dummycreateobj, dummycreateobj, dummycreateobj,        \
        dummycreateobj, dummycreateobj, dummycreateobj, dummycreateobj,        \
        dummycreateobj, dummycreateobj, dummycreateobj, dummycreateobj,        \
        dummycreateobj);                                                       \
    getListItemFuncTuple = std::make_tuple(                                    \
        getItemObj1, getItemObj2, getItemObj3, getItemObj4, getItemObj5,       \
        getItemObj6, getItemObj7, getItemObj8, getItemObj9, getItemObj10,      \
        getItemObj11, getItemObj12, getItemObj13, getItemObj14, getItemObj15,  \
        dummyligobj, dummyligobj, dummyligobj, dummyligobj, dummyligobj,       \
        dummyligobj, dummyligobj, dummyligobj, dummyligobj, dummyligobj,       \
        dummyligobj, dummyligobj, dummyligobj, dummyligobj, dummyligobj,       \
        dummyligobj, dummyligobj);                                             \
    getContainerSizeFuncTuple = std::make_tuple(                               \
        getContainerSize1, getContainerSize2, getContainerSize3,               \
        getContainerSize4, getContainerSize5, getContainerSize6,               \
        getContainerSize7, getContainerSize8, getContainerSize9,               \
        getContainerSize10, getContainerSize11, getContainerSize12,            \
        getContainerSize13, getContainerSize14, getContainerSize15, dummyobj,  \
        dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj,  \
        dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj,  \
        dummyobj, dummyobj);                                                   \
    createMapItemFuncTuple = std::make_tuple(                                  \
        createMapObj1, createMapObj2, createMapObj3, createMapObj4,            \
        createMapObj5, createMapObj6, createMapObj7, createMapObj8,            \
        createMapObj9, createMapObj10, createMapObj11, createMapObj12,         \
        createMapObj13, createMapObj14, createMapObj15, dummycreateMapItem,    \
        dummycreateMapItem, dummycreateMapItem, dummycreateMapItem,            \
        dummycreateMapItem, dummycreateMapItem, dummycreateMapItem,            \
        dummycreateMapItem, dummycreateMapItem, dummycreateMapItem,            \
        dummycreateMapItem, dummycreateMapItem, dummycreateMapItem,            \
        dummycreateMapItem, dummycreateMapItem, dummycreateMapItem,            \
        dummycreateMapItem);                                                   \
    getMapItemsFuncTuple = std::make_tuple(                                    \
        getMapItems1, getMapItems2, getMapItems3, getMapItems4, getMapItems5,  \
        getMapItems6, getMapItems7, getMapItems8, getMapItems9, getMapItems10, \
        getMapItems11, getMapItems12, getMapItems13, getMapItems14,            \
        getMapItems15, dummygetMapItems, dummygetMapItems, dummygetMapItems,   \
        dummygetMapItems, dummygetMapItems, dummygetMapItems,                  \
        dummygetMapItems, dummygetMapItems, dummygetMapItems,                  \
        dummygetMapItems, dummygetMapItems, dummygetMapItems,                  \
        dummygetMapItems, dummygetMapItems, dummygetMapItems,                  \
        dummygetMapItems, dummygetMapItems);                                   \
    addListItemFuncTuple = std::make_tuple(                                    \
        addListItem, addListItem2, addListItem3, addListItem4, addListItem5,   \
        addListItem6, addListItem7, addListItem8, addListItem9, addListItem10, \
        addListItem11, addListItem12, addListItem13, addListItem14,            \
        addListItem15, dummyAddListItem, dummyAddListItem, dummyAddListItem,   \
        dummyAddListItem, dummyAddListItem, dummyAddListItem,                  \
        dummyAddListItem, dummyAddListItem, dummyAddListItem,                  \
        dummyAddListItem, dummyAddListItem, dummyAddListItem,                  \
        dummyAddListItem, dummyAddListItem, dummyAddListItem,                  \
        dummyAddListItem, dummyAddListItem);                                   \
    addMapItemFuncTuple = std::make_tuple(                                     \
        addMapItem, addMapItem2, addMapItem3, addMapItem4, addMapItem5,        \
        addMapItem6, addMapItem7, addMapItem8, addMapItem9, addMapItem10,      \
        addMapItem11, addMapItem12, addMapItem13, addMapItem14, addMapItem15,  \
        dummyAddMapItem, dummyAddMapItem, dummyAddMapItem, dummyAddMapItem,    \
        dummyAddMapItem, dummyAddMapItem, dummyAddMapItem, dummyAddMapItem,    \
        dummyAddMapItem, dummyAddMapItem, dummyAddMapItem, dummyAddMapItem,    \
        dummyAddMapItem, dummyAddMapItem, dummyAddMapItem, dummyAddMapItem,    \
        dummyAddMapItem);

#define IMPLE_INIT_TUPLE_16(CLASS, M1, M2, M3, M4, M5, M6, M7, M8, M9, M10,    \
                            M11, M12, M13, M14, M15, M16)                      \
    std::function<decltype(M1)()> getobj1 =                                    \
        std::bind(&CLASS::__ReflectGet##M1, this);                             \
    std::function<decltype(M2)()> getobj2 =                                    \
        std::bind(&CLASS::__ReflectGet##M2, this);                             \
    std::function<decltype(M3)()> getobj3 =                                    \
        std::bind(&CLASS::__ReflectGet##M3, this);                             \
    std::function<decltype(M4)()> getobj4 =                                    \
        std::bind(&CLASS::__ReflectGet##M4, this);                             \
    std::function<decltype(M5)()> getobj5 =                                    \
        std::bind(&CLASS::__ReflectGet##M5, this);                             \
    std::function<decltype(M6)()> getobj6 =                                    \
        std::bind(&CLASS::__ReflectGet##M6, this);                             \
    std::function<decltype(M7)()> getobj7 =                                    \
        std::bind(&CLASS::__ReflectGet##M7, this);                             \
    std::function<decltype(M8)()> getobj8 =                                    \
        std::bind(&CLASS::__ReflectGet##M8, this);                             \
    std::function<decltype(M9)()> getobj9 =                                    \
        std::bind(&CLASS::__ReflectGet##M9, this);                             \
    std::function<decltype(M10)()> getobj10 =                                  \
        std::bind(&CLASS::__ReflectGet##M10, this);                            \
    std::function<decltype(M11)()> getobj11 =                                  \
        std::bind(&CLASS::__ReflectGet##M11, this);                            \
    std::function<decltype(M12)()> getobj12 =                                  \
        std::bind(&CLASS::__ReflectGet##M12, this);                            \
    std::function<decltype(M13)()> getobj13 =                                  \
        std::bind(&CLASS::__ReflectGet##M13, this);                            \
    std::function<decltype(M14)()> getobj14 =                                  \
        std::bind(&CLASS::__ReflectGet##M14, this);                            \
    std::function<decltype(M15)()> getobj15 =                                  \
        std::bind(&CLASS::__ReflectGet##M15, this);                            \
    std::function<decltype(M16)()> getobj16 =                                  \
        std::bind(&CLASS::__ReflectGet##M16, this);                            \
    std::function<void()> createobj1 =                                         \
        std::bind(&CLASS::__ReflectCreate##M1, this);                          \
    std::function<void()> createobj2 =                                         \
        std::bind(&CLASS::__ReflectCreate##M2, this);                          \
    std::function<void()> createobj3 =                                         \
        std::bind(&CLASS::__ReflectCreate##M3, this);                          \
    std::function<void()> createobj4 =                                         \
        std::bind(&CLASS::__ReflectCreate##M4, this);                          \
    std::function<void()> createobj5 =                                         \
        std::bind(&CLASS::__ReflectCreate##M5, this);                          \
    std::function<void()> createobj6 =                                         \
        std::bind(&CLASS::__ReflectCreate##M6, this);                          \
    std::function<void()> createobj7 =                                         \
        std::bind(&CLASS::__ReflectCreate##M7, this);                          \
    std::function<void()> createobj8 =                                         \
        std::bind(&CLASS::__ReflectCreate##M8, this);                          \
    std::function<void()> createobj9 =                                         \
        std::bind(&CLASS::__ReflectCreate##M9, this);                          \
    std::function<void()> createobj10 =                                        \
        std::bind(&CLASS::__ReflectCreate##M10, this);                         \
    std::function<void()> createobj11 =                                        \
        std::bind(&CLASS::__ReflectCreate##M11, this);                         \
    std::function<void()> createobj12 =                                        \
        std::bind(&CLASS::__ReflectCreate##M12, this);                         \
    std::function<void()> createobj13 =                                        \
        std::bind(&CLASS::__ReflectCreate##M13, this);                         \
    std::function<void()> createobj14 =                                        \
        std::bind(&CLASS::__ReflectCreate##M14, this);                         \
    std::function<void()> createobj15 =                                        \
        std::bind(&CLASS::__ReflectCreate##M15, this);                         \
    std::function<void()> createobj16 =                                        \
        std::bind(&CLASS::__ReflectCreate##M16, this);                         \
    std::function<Object()> genItemObj1 =                                      \
        std::bind(&CLASS::__ReflectCreateListMember##M1, this);                \
    std::function<Object()> genItemObj2 =                                      \
        std::bind(&CLASS::__ReflectCreateListMember##M2, this);                \
    std::function<Object()> genItemObj3 =                                      \
        std::bind(&CLASS::__ReflectCreateListMember##M3, this);                \
    std::function<Object()> genItemObj4 =                                      \
        std::bind(&CLASS::__ReflectCreateListMember##M4, this);                \
    std::function<Object()> genItemObj5 =                                      \
        std::bind(&CLASS::__ReflectCreateListMember##M5, this);                \
    std::function<Object()> genItemObj6 =                                      \
        std::bind(&CLASS::__ReflectCreateListMember##M6, this);                \
    std::function<Object()> genItemObj7 =                                      \
        std::bind(&CLASS::__ReflectCreateListMember##M7, this);                \
    std::function<Object()> genItemObj8 =                                      \
        std::bind(&CLASS::__ReflectCreateListMember##M8, this);                \
    std::function<Object()> genItemObj9 =                                      \
        std::bind(&CLASS::__ReflectCreateListMember##M9, this);                \
    std::function<Object()> genItemObj10 =                                     \
        std::bind(&CLASS::__ReflectCreateListMember##M10, this);               \
    std::function<Object()> genItemObj11 =                                     \
        std::bind(&CLASS::__ReflectCreateListMember##M11, this);               \
    std::function<Object()> genItemObj12 =                                     \
        std::bind(&CLASS::__ReflectCreateListMember##M12, this);               \
    std::function<Object()> genItemObj13 =                                     \
        std::bind(&CLASS::__ReflectCreateListMember##M13, this);               \
    std::function<Object()> genItemObj14 =                                     \
        std::bind(&CLASS::__ReflectCreateListMember##M14, this);               \
    std::function<Object()> genItemObj15 =                                     \
        std::bind(&CLASS::__ReflectCreateListMember##M15, this);               \
    std::function<Object()> genItemObj16 =                                     \
        std::bind(&CLASS::__ReflectCreateListMember##M16, this);               \
    std::function<Object(int)> getItemObj1 = std::bind(                        \
        &CLASS::__ReflectGetListItem##M1, this, std::placeholders::_1);        \
    std::function<Object(int)> getItemObj2 = std::bind(                        \
        &CLASS::__ReflectGetListItem##M2, this, std::placeholders::_1);        \
    std::function<Object(int)> getItemObj3 = std::bind(                        \
        &CLASS::__ReflectGetListItem##M3, this, std::placeholders::_1);        \
    std::function<Object(int)> getItemObj4 = std::bind(                        \
        &CLASS::__ReflectGetListItem##M4, this, std::placeholders::_1);        \
    std::function<Object(int)> getItemObj5 = std::bind(                        \
        &CLASS::__ReflectGetListItem##M5, this, std::placeholders::_1);        \
    std::function<Object(int)> getItemObj6 = std::bind(                        \
        &CLASS::__ReflectGetListItem##M6, this, std::placeholders::_1);        \
    std::function<Object(int)> getItemObj7 = std::bind(                        \
        &CLASS::__ReflectGetListItem##M7, this, std::placeholders::_1);        \
    std::function<Object(int)> getItemObj8 = std::bind(                        \
        &CLASS::__ReflectGetListItem##M8, this, std::placeholders::_1);        \
    std::function<Object(int)> getItemObj9 = std::bind(                        \
        &CLASS::__ReflectGetListItem##M9, this, std::placeholders::_1);        \
    std::function<Object(int)> getItemObj10 = std::bind(                       \
        &CLASS::__ReflectGetListItem##M10, this, std::placeholders::_1);       \
    std::function<Object(int)> getItemObj11 = std::bind(                       \
        &CLASS::__ReflectGetListItem##M11, this, std::placeholders::_1);       \
    std::function<Object(int)> getItemObj12 = std::bind(                       \
        &CLASS::__ReflectGetListItem##M12, this, std::placeholders::_1);       \
    std::function<Object(int)> getItemObj13 = std::bind(                       \
        &CLASS::__ReflectGetListItem##M13, this, std::placeholders::_1);       \
    std::function<Object(int)> getItemObj14 = std::bind(                       \
        &CLASS::__ReflectGetListItem##M14, this, std::placeholders::_1);       \
    std::function<Object(int)> getItemObj15 = std::bind(                       \
        &CLASS::__ReflectGetListItem##M15, this, std::placeholders::_1);       \
    std::function<Object(int)> getItemObj16 = std::bind(                       \
        &CLASS::__ReflectGetListItem##M16, this, std::placeholders::_1);       \
    std::function<int()> getContainerSize2 =                                   \
        std::bind(&CLASS::__ReflectGetContainerSize##M2, this);                \
    std::function<int()> getContainerSize3 =                                   \
        std::bind(&CLASS::__ReflectGetContainerSize##M3, this);                \
    std::function<int()> getContainerSize4 =                                   \
        std::bind(&CLASS::__ReflectGetContainerSize##M4, this);                \
    std::function<int()> getContainerSize5 =                                   \
        std::bind(&CLASS::__ReflectGetContainerSize##M5, this);                \
    std::function<int()> getContainerSize6 =                                   \
        std::bind(&CLASS::__ReflectGetContainerSize##M6, this);                \
    std::function<int()> getContainerSize7 =                                   \
        std::bind(&CLASS::__ReflectGetContainerSize##M7, this);                \
    std::function<int()> getContainerSize8 =                                   \
        std::bind(&CLASS::__ReflectGetContainerSize##M8, this);                \
    std::function<int()> getContainerSize9 =                                   \
        std::bind(&CLASS::__ReflectGetContainerSize##M9, this);                \
    std::function<int()> getContainerSize10 =                                  \
        std::bind(&CLASS::__ReflectGetContainerSize##M10, this);               \
    std::function<int()> getContainerSize11 =                                  \
        std::bind(&CLASS::__ReflectGetContainerSize##M11, this);               \
    std::function<int()> getContainerSize12 =                                  \
        std::bind(&CLASS::__ReflectGetContainerSize##M12, this);               \
    std::function<int()> getContainerSize13 =                                  \
        std::bind(&CLASS::__ReflectGetContainerSize##M13, this);               \
    std::function<int()> getContainerSize14 =                                  \
        std::bind(&CLASS::__ReflectGetContainerSize##M14, this);               \
    std::function<int()> getContainerSize15 =                                  \
        std::bind(&CLASS::__ReflectGetContainerSize##M15, this);               \
    std::function<int()> getContainerSize16 =                                  \
        std::bind(&CLASS::__ReflectGetContainerSize##M16, this);               \
    std::function<Pair<Object, Object>()> createMapObj1 =              \
        std::bind(&CLASS::__ReflectCreateMapMember##M1, this);                 \
    std::function<ArrayList<Pair<Object, Object>>()> getMapItems1 =    \
        std::bind(&CLASS::__ReflectGetMapItems##M1, this);                     \
    std::function<Pair<Object, Object>()> createMapObj2 =              \
        std::bind(&CLASS::__ReflectCreateMapMember##M2, this);                 \
    std::function<ArrayList<Pair<Object, Object>>()> getMapItems2 =    \
        std::bind(&CLASS::__ReflectGetMapItems##M2, this);                     \
    std::function<Pair<Object, Object>()> createMapObj3 =              \
        std::bind(&CLASS::__ReflectCreateMapMember##M3, this);                 \
    std::function<ArrayList<Pair<Object, Object>>()> getMapItems3 =    \
        std::bind(&CLASS::__ReflectGetMapItems##M3, this);                     \
    std::function<Pair<Object, Object>()> createMapObj4 =              \
        std::bind(&CLASS::__ReflectCreateMapMember##M4, this);                 \
    std::function<ArrayList<Pair<Object, Object>>()> getMapItems4 =    \
        std::bind(&CLASS::__ReflectGetMapItems##M4, this);                     \
    std::function<Pair<Object, Object>()> createMapObj5 =              \
        std::bind(&CLASS::__ReflectCreateMapMember##M5, this);                 \
    std::function<ArrayList<Pair<Object, Object>>()> getMapItems5 =    \
        std::bind(&CLASS::__ReflectGetMapItems##M5, this);                     \
    std::function<Pair<Object, Object>()> createMapObj6 =              \
        std::bind(&CLASS::__ReflectCreateMapMember##M6, this);                 \
    std::function<ArrayList<Pair<Object, Object>>()> getMapItems6 =    \
        std::bind(&CLASS::__ReflectGetMapItems##M6, this);                     \
    std::function<Pair<Object, Object>()> createMapObj7 =              \
        std::bind(&CLASS::__ReflectCreateMapMember##M7, this);                 \
    std::function<ArrayList<Pair<Object, Object>>()> getMapItems7 =    \
        std::bind(&CLASS::__ReflectGetMapItems##M7, this);                     \
    std::function<Pair<Object, Object>()> createMapObj8 =              \
        std::bind(&CLASS::__ReflectCreateMapMember##M8, this);                 \
    std::function<ArrayList<Pair<Object, Object>>()> getMapItems8 =    \
        std::bind(&CLASS::__ReflectGetMapItems##M8, this);                     \
    std::function<Pair<Object, Object>()> createMapObj9 =              \
        std::bind(&CLASS::__ReflectCreateMapMember##M9, this);                 \
    std::function<ArrayList<Pair<Object, Object>>()> getMapItems9 =    \
        std::bind(&CLASS::__ReflectGetMapItems##M9, this);                     \
    std::function<Pair<Object, Object>()> createMapObj10 =             \
        std::bind(&CLASS::__ReflectCreateMapMember##M10, this);                \
    std::function<ArrayList<Pair<Object, Object>>()> getMapItems10 =   \
        std::bind(&CLASS::__ReflectGetMapItems##M10, this);                    \
    std::function<Pair<Object, Object>()> createMapObj11 =             \
        std::bind(&CLASS::__ReflectCreateMapMember##M11, this);                \
    std::function<ArrayList<Pair<Object, Object>>()> getMapItems11 =   \
        std::bind(&CLASS::__ReflectGetMapItems##M11, this);                    \
    std::function<Pair<Object, Object>()> createMapObj12 =             \
        std::bind(&CLASS::__ReflectCreateMapMember##M12, this);                \
    std::function<ArrayList<Pair<Object, Object>>()> getMapItems12 =   \
        std::bind(&CLASS::__ReflectGetMapItems##M12, this);                    \
    std::function<Pair<Object, Object>()> createMapObj13 =             \
        std::bind(&CLASS::__ReflectCreateMapMember##M13, this);                \
    std::function<ArrayList<Pair<Object, Object>>()> getMapItems13 =   \
        std::bind(&CLASS::__ReflectGetMapItems##M13, this);                    \
    std::function<Pair<Object, Object>()> createMapObj14 =             \
        std::bind(&CLASS::__ReflectCreateMapMember##M14, this);                \
    std::function<ArrayList<Pair<Object, Object>>()> getMapItems14 =   \
        std::bind(&CLASS::__ReflectGetMapItems##M14, this);                    \
    std::function<Pair<Object, Object>()> createMapObj15 =             \
        std::bind(&CLASS::__ReflectCreateMapMember##M15, this);                \
    std::function<ArrayList<Pair<Object, Object>>()> getMapItems15 =   \
        std::bind(&CLASS::__ReflectGetMapItems##M15, this);                    \
    std::function<Pair<Object, Object>()> createMapObj16 =             \
        std::bind(&CLASS::__ReflectCreateMapMember##M16, this);                \
    std::function<ArrayList<Pair<Object, Object>>()> getMapItems16 =   \
        std::bind(&CLASS::__ReflectGetMapItems##M16, this);                    \
    std::function<void(Object)> addListItem = std::bind(                       \
        &CLASS::__ReflectAddListItem##M1, this, std::placeholders::_1);        \
    std::function<void(Object, Object)> addMapItem =                           \
        std::bind(&CLASS::__ReflectAddMapItem##M1, this,                       \
                  std::placeholders::_1, std::placeholders::_2);               \
    std::function<void(Object)> addListItem2 = std::bind(                      \
        &CLASS::__ReflectAddListItem##M2, this, std::placeholders::_1);        \
    std::function<void(Object, Object)> addMapItem2 =                          \
        std::bind(&CLASS::__ReflectAddMapItem##M2, this,                       \
                  std::placeholders::_1, std::placeholders::_2);               \
    std::function<void(Object)> addListItem3 = std::bind(                      \
        &CLASS::__ReflectAddListItem##M3, this, std::placeholders::_1);        \
    std::function<void(Object, Object)> addMapItem3 =                          \
        std::bind(&CLASS::__ReflectAddMapItem##M3, this,                       \
                  std::placeholders::_1, std::placeholders::_2);               \
    std::function<void(Object)> addListItem4 = std::bind(                      \
        &CLASS::__ReflectAddListItem##M4, this, std::placeholders::_1);        \
    std::function<void(Object, Object)> addMapItem4 =                          \
        std::bind(&CLASS::__ReflectAddMapItem##M4, this,                       \
                  std::placeholders::_1, std::placeholders::_2);               \
    std::function<void(Object)> addListItem5 = std::bind(                      \
        &CLASS::__ReflectAddListItem##M5, this, std::placeholders::_1);        \
    std::function<void(Object, Object)> addMapItem5 =                          \
        std::bind(&CLASS::__ReflectAddMapItem##M5, this,                       \
                  std::placeholders::_1, std::placeholders::_2);               \
    std::function<void(Object)> addListItem6 = std::bind(                      \
        &CLASS::__ReflectAddListItem##M6, this, std::placeholders::_1);        \
    std::function<void(Object, Object)> addMapItem6 =                          \
        std::bind(&CLASS::__ReflectAddMapItem##M6, this,                       \
                  std::placeholders::_1, std::placeholders::_2);               \
    std::function<void(Object)> addListItem7 = std::bind(                      \
        &CLASS::__ReflectAddListItem##M7, this, std::placeholders::_1);        \
    std::function<void(Object, Object)> addMapItem7 =                          \
        std::bind(&CLASS::__ReflectAddMapItem##M7, this,                       \
                  std::placeholders::_1, std::placeholders::_2);               \
    std::function<void(Object)> addListItem8 = std::bind(                      \
        &CLASS::__ReflectAddListItem##M8, this, std::placeholders::_1);        \
    std::function<void(Object, Object)> addMapItem8 =                          \
        std::bind(&CLASS::__ReflectAddMapItem##M8, this,                       \
                  std::placeholders::_1, std::placeholders::_2);               \
    std::function<void(Object)> addListItem9 = std::bind(                      \
        &CLASS::__ReflectAddListItem##M9, this, std::placeholders::_1);        \
    std::function<void(Object, Object)> addMapItem9 =                          \
        std::bind(&CLASS::__ReflectAddMapItem##M9, this,                       \
                  std::placeholders::_1, std::placeholders::_2);               \
    std::function<void(Object)> addListItem10 = std::bind(                     \
        &CLASS::__ReflectAddListItem##M10, this, std::placeholders::_1);       \
    std::function<void(Object, Object)> addMapItem10 =                         \
        std::bind(&CLASS::__ReflectAddMapItem##M10, this,                      \
                  std::placeholders::_1, std::placeholders::_2);               \
    std::function<void(Object)> addListItem11 = std::bind(                     \
        &CLASS::__ReflectAddListItem##M11, this, std::placeholders::_1);       \
    std::function<void(Object, Object)> addMapItem11 =                         \
        std::bind(&CLASS::__ReflectAddMapItem##M11, this,                      \
                  std::placeholders::_1, std::placeholders::_2);               \
    std::function<void(Object)> addListItem12 = std::bind(                     \
        &CLASS::__ReflectAddListItem##M12, this, std::placeholders::_1);       \
    std::function<void(Object, Object)> addMapItem12 =                         \
        std::bind(&CLASS::__ReflectAddMapItem##M12, this,                      \
                  std::placeholders::_1, std::placeholders::_2);               \
    std::function<void(Object)> addListItem13 = std::bind(                     \
        &CLASS::__ReflectAddListItem##M13, this, std::placeholders::_1);       \
    std::function<void(Object, Object)> addMapItem13 =                         \
        std::bind(&CLASS::__ReflectAddMapItem##M13, this,                      \
                  std::placeholders::_1, std::placeholders::_2);               \
    std::function<void(Object)> addListItem14 = std::bind(                     \
        &CLASS::__ReflectAddListItem##M14, this, std::placeholders::_1);       \
    std::function<void(Object, Object)> addMapItem14 =                         \
        std::bind(&CLASS::__ReflectAddMapItem##M14, this,                      \
                  std::placeholders::_1, std::placeholders::_2);               \
    std::function<void(Object)> addListItem15 = std::bind(                     \
        &CLASS::__ReflectAddListItem##M15, this, std::placeholders::_1);       \
    std::function<void(Object, Object)> addMapItem15 =                         \
        std::bind(&CLASS::__ReflectAddMapItem##M15, this,                      \
                  std::placeholders::_1, std::placeholders::_2);               \
    std::function<void(Object)> addListItem16 = std::bind(                     \
        &CLASS::__ReflectAddListItem##M16, this, std::placeholders::_1);       \
    std::function<void(Object, Object)> addMapItem16 =                         \
        std::bind(&CLASS::__ReflectAddMapItem##M16, this,                      \
                  std::placeholders::_1, std::placeholders::_2);               \
    getFuncTuple = std::make_tuple(                                            \
        getobj1, getobj2, getobj3, getobj4, getobj5, getobj6, getobj7,         \
        getobj8, getobj9, getobj10, getobj11, getobj12, getobj13, getobj14,    \
        getobj15, getobj16, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj,  \
        dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj,  \
        dummyobj, dummyobj, dummyobj, dummyobj);                               \
    createFuncTuple = std::make_tuple(                                         \
        createobj1, createobj2, createobj3, createobj4, createobj5,            \
        createobj6, createobj7, createobj8, createobj9, createobj10,           \
        createobj11, createobj12, createobj13, createobj14, createobj15,       \
        createobj16, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj,         \
        dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj,  \
        dummyobj, dummyobj, dummyobj, dummyobj);                               \
    createListItemFuncTuple = std::make_tuple(                                 \
        genItemObj1, genItemObj2, genItemObj3, genItemObj4, genItemObj5,       \
        genItemObj6, genItemObj7, genItemObj8, genItemObj9, genItemObj10,      \
        genItemObj11, genItemObj12, genItemObj13, genItemObj14, genItemObj15,  \
        genItemObj16, dummycreateobj, dummycreateobj, dummycreateobj,          \
        dummycreateobj, dummycreateobj, dummycreateobj, dummycreateobj,        \
        dummycreateobj, dummycreateobj, dummycreateobj, dummycreateobj,        \
        dummycreateobj, dummycreateobj, dummycreateobj, dummycreateobj,        \
        dummycreateobj);                                                       \
    getListItemFuncTuple = std::make_tuple(                                    \
        getItemObj1, getItemObj2, getItemObj3, getItemObj4, getItemObj5,       \
        getItemObj6, getItemObj7, getItemObj8, getItemObj9, getItemObj10,      \
        getItemObj11, getItemObj12, getItemObj13, getItemObj14, getItemObj15,  \
        getItemObj16, dummyligobj, dummyligobj, dummyligobj, dummyligobj,      \
        dummyligobj, dummyligobj, dummyligobj, dummyligobj, dummyligobj,       \
        dummyligobj, dummyligobj, dummyligobj, dummyligobj, dummyligobj,       \
        dummyligobj, dummyligobj);                                             \
    getContainerSizeFuncTuple = std::make_tuple(                               \
        getContainerSize1, getContainerSize2, getContainerSize3,               \
        getContainerSize4, getContainerSize5, getContainerSize6,               \
        getContainerSize7, getContainerSize8, getContainerSize9,               \
        getContainerSize10, getContainerSize11, getContainerSize12,            \
        getContainerSize13, getContainerSize14, getContainerSize15,            \
        getContainerSize16, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj,  \
        dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj, dummyobj,  \
        dummyobj, dummyobj, dummyobj, dummyobj);                               \
    createMapItemFuncTuple = std::make_tuple(                                  \
        createMapObj1, createMapObj2, createMapObj3, createMapObj4,            \
        createMapObj5, createMapObj6, createMapObj7, createMapObj8,            \
        createMapObj9, createMapObj10, createMapObj11, createMapObj12,         \
        createMapObj13, createMapObj14, createMapObj15, createMapObj16,        \
        dummycreateMapItem, dummycreateMapItem, dummycreateMapItem,            \
        dummycreateMapItem, dummycreateMapItem, dummycreateMapItem,            \
        dummycreateMapItem, dummycreateMapItem, dummycreateMapItem,            \
        dummycreateMapItem, dummycreateMapItem, dummycreateMapItem,            \
        dummycreateMapItem, dummycreateMapItem, dummycreateMapItem,            \
        dummycreateMapItem);                                                   \
    getMapItemsFuncTuple = std::make_tuple(                                    \
        getMapItems1, getMapItems2, getMapItems3, getMapItems4, getMapItems5,  \
        getMapItems6, getMapItems7, getMapItems8, getMapItems9, getMapItems10, \
        getMapItems11, getMapItems12, getMapItems13, getMapItems14,            \
        getMapItems15, getMapItems16, dummygetMapItems, dummygetMapItems,      \
        dummygetMapItems, dummygetMapItems, dummygetMapItems,                  \
        dummygetMapItems, dummygetMapItems, dummygetMapItems,                  \
        dummygetMapItems, dummygetMapItems, dummygetMapItems,                  \
        dummygetMapItems, dummygetMapItems, dummygetMapItems,                  \
        dummygetMapItems, dummygetMapItems);                                   \
    addListItemFuncTuple = std::make_tuple(                                    \
        addListItem, addListItem2, addListItem3, addListItem4, addListItem5,   \
        addListItem6, addListItem7, addListItem8, addListItem9, addListItem10, \
        addListItem11, addListItem12, addListItem13, addListItem14,            \
        addListItem15, addListItem16, dummyAddListItem, dummyAddListItem,      \
        dummyAddListItem, dummyAddListItem, dummyAddListItem,                  \
        dummyAddListItem, dummyAddListItem, dummyAddListItem,                  \
        dummyAddListItem, dummyAddListItem, dummyAddListItem,                  \
        dummyAddListItem, dummyAddListItem, dummyAddListItem,                  \
        dummyAddListItem, dummyAddListItem);                                   \
    addMapItemFuncTuple = std::make_tuple(                                     \
        addMapItem, addMapItem2, addMapItem3, addMapItem4, addMapItem5,        \
        addMapItem6, addMapItem7, addMapItem8, addMapItem9, addMapItem10,      \
        addMapItem11, addMapItem12, addMapItem13, addMapItem14, addMapItem15,  \
        addMapItem16, dummyAddMapItem, dummyAddMapItem, dummyAddMapItem,       \
        dummyAddMapItem, dummyAddMapItem, dummyAddMapItem, dummyAddMapItem,    \
        dummyAddMapItem, dummyAddMapItem, dummyAddMapItem, dummyAddMapItem,    \
        dummyAddMapItem, dummyAddMapItem, dummyAddMapItem, dummyAddMapItem,    \
        dummyAddMapItem);

#define DECLARE_REFLECT_FIELD(CLASS, ...)                                      \
  private:                                                                     \
    HashMap<String, Field> __maps;                                             \
    IMPLE_SET_FUNCTION_DETECT(_##CLASS, GET_ARG_COUNT(__VA_ARGS__),            \
                              __VA_ARGS__)                                     \
    DECLARE_INIT_TUPLE_DETECT(_##CLASS, GET_ARG_COUNT(__VA_ARGS__),            \
                              __VA_ARGS__)                                     \
    int __ReflectDummy() { return 0; }                                         \
    Object __ReflectCreateDummy() { return nullptr; }                          \
    Object __ReflectListItemGetDummy(int) { return nullptr; }                  \
    Pair<Object, Object> __createMapItemDummy() { return nullptr; }    \
    ArrayList<Pair<Object, Object>> __getMapItemsDummy() {             \
        return nullptr;                                                        \
    }                                                                          \
    void __addListItemDummy(Object) {}                                         \
    void __addMapItemDummy(Object, Object) {}                                  \
                                                                               \
  public:                                                                      \
    static const int __isReflected = 1;                                        \
    sp<_String> __ReflectClassName() { return createString(#CLASS); }          \
    void __ReflectInit() {                                                     \
        int index = 0;                                                         \
        std::function<int(void)> dummyobj =                                    \
            std::bind(&_##CLASS::__ReflectDummy, this);                        \
        std::function<Object(void)> dummycreateobj =                           \
            std::bind(&_##CLASS::__ReflectCreateDummy, this);                  \
        std::function<Object(int)> dummyligobj =                               \
            std::bind(&_##CLASS::__ReflectListItemGetDummy, this,              \
                      std::placeholders::_1);                                  \
        std::function<Pair<Object, Object>()> dummycreateMapItem =     \
            std::bind(&_##CLASS::__createMapItemDummy, this);                  \
        std::function<ArrayList<Pair<Object, Object>>()>               \
            dummygetMapItems = std::bind(&_##CLASS::__getMapItemsDummy, this); \
        std::function<void(Object)> dummyAddListItem = std::bind(              \
            &_##CLASS::__addListItemDummy, this, std::placeholders::_1);       \
        std::function<void(Object, Object)> dummyAddMapItem =                  \
            std::bind(&_##CLASS::__addMapItemDummy, this,                      \
                      std::placeholders::_1, std::placeholders::_2);           \
        __maps = createHashMap<String, Field>();                               \
        IMPLE_INIT_FUNCTION_DETECT(_##CLASS, GET_ARG_COUNT(__VA_ARGS__),       \
                                   __VA_ARGS__)                                \
        IMPLE_INIT_TUPLE_DETECT(_##CLASS, GET_ARG_COUNT(__VA_ARGS__),          \
                                __VA_ARGS__)                                   \
    }                                                                          \
    Field getField(String name) { return __maps->get(name); }                  \
    ArrayList<Field> getAllFields() { return __maps->entrySet(); }             \
    template <typename Q> Q *genDataPoint(sp<Q> t) {                           \
        Q *data = new Q();                                                     \
        data->__ReflectInit();                                                 \
        return data;                                                           \
    }                                                                          \
    template <typename Q, typename P>                                          \
    Pair<Object, Object> genHashMapData(HashMap<Q, P> map) {           \
        Q key;                                                                 \
        auto keyP = genDataPoint(key);                                         \
        key.set_pointer(keyP);                                                 \
        P value;                                                               \
        auto valueP = genDataPoint(value);                                     \
        value.set_pointer(valueP);                                             \
        return createPair<Object, Object>(key, value);                 \
    }                                                                          \
    template <typename Q> Object genArrayListData(ArrayList<Q> list) {         \
        Q param;                                                               \
        auto pointer = genDataPoint(param);                                    \
        param.set_pointer(pointer);                                            \
        return param;                                                          \
    }                                                                          \
    template <typename Q> Pair<Object, Object> genHashMapData(Q t) {   \
        return nullptr;                                                        \
    }                                                                          \
    template <typename Q> Object genArrayListData(Q t) { return nullptr; }     \
    template <typename Q, typename P>                                          \
    void addHashMapItem(HashMap<Q, P> map, Object key, Object value) {         \
        map->put(Cast<Q>(key), Cast<P>(value));                                \
    }                                                                          \
    template <typename Q>                                                      \
    void addHashMapItem(Q t, Object key, Object value) {}                      \
    template <typename Q, typename P>                                          \
    ArrayList<Pair<Object, Object>> getHashMapItems(                   \
        HashMap<Q, P> map) {                                                   \
        ArrayList<Pair<Object, Object>> list =                         \
            createArrayList<Pair<Object, Object>>();                   \
        MapIterator<Q, P> iterator = map->getIterator();                       \
        while (iterator->hasValue()) {                                         \
            Pair<Object, Object> pair =                                \
                createPair<Object, Object>(iterator->getKey(),         \
                                                   iterator->getValue());      \
            list->add(pair);                                                   \
            iterator->next();                                                  \
        }                                                                      \
        return list;                                                           \
    }                                                                          \
    template <typename Q> void addArrayListData(ArrayList<Q> list, Object v) { \
        list->add(Cast<Q>(v));                                                 \
    }                                                                          \
    template <typename Q> void addArrayListData(Q t, Object v) {}              \
    template <typename Q>                                                      \
    Object getArrayListItem(ArrayList<Q> list, int index) {                    \
        if (list == nullptr || index == list->size()) {                        \
            return nullptr;                                                    \
        }                                                                      \
        return list->get(index);                                               \
    }                                                                          \
    template <typename Q> Object getArrayListItem(Q t, int index) {            \
        return nullptr;                                                        \
    }                                                                          \
    template <typename Q>                                                      \
    ArrayList<Pair<Object, Object>> getHashMapItems(Q t) {             \
        return nullptr;                                                        \
    }                                                                          \
    template <typename Q> int __getContainerSize(ArrayList<Q> list) {          \
        if (list == nullptr) {                                                 \
            return 0;                                                          \
        }                                                                      \
        return list->size();                                                   \
    }                                                                          \
    template <typename Q, typename P>                                          \
    int __getContainerSize(HashMap<Q, P> map) {                                \
        if (map == nullptr) {                                                  \
            return 0;                                                          \
        }                                                                      \
        return map->size();                                                    \
    }                                                                          \
    template <typename Q> int __getContainerSize(Q t) { return -1; }           \
    int __getFieldIntValue(const std::string &name) {                                \
        FieldContentValue v = __getFieldContentValue(name);                    \
        return v->intValue;                                                    \
    }                                                                          \
    long __getFieldLongValue(const std::string &name) {                              \
        FieldContentValue v = __getFieldContentValue(name);                    \
        return v->longValue;                                                   \
    }                                                                          \
    uint8_t __getFieldByteValue(const std::string &name) {                           \
        FieldContentValue v = __getFieldContentValue(name);                    \
        return v->uint8Value;                                                  \
    }                                                                          \
    bool __getFieldBoolValue(const std::string &name) {                              \
        FieldContentValue v = __getFieldContentValue(name);                    \
        return v->boolValue;                                                   \
    }                                                                          \
    double __getFieldDoubleValue(const std::string &name) {                          \
        FieldContentValue v = __getFieldContentValue(name);                    \
        return v->doubleValue;                                                 \
    }                                                                          \
    float __getFieldFloatValue(const std::string &name) {                            \
        FieldContentValue v = __getFieldContentValue(name);                    \
        return v->floatValue;                                                  \
    }                                                                          \
    uint8_t __getFieldUint8Value(const std::string &name) {                          \
        FieldContentValue v = __getFieldContentValue(name);                    \
        return v->uint8Value;                                                  \
    }                                                                          \
    uint16_t __getFieldUint16Value(const std::string &name) {                        \
        FieldContentValue v = __getFieldContentValue(name);                    \
        return v->uint16Value;                                                 \
    }                                                                          \
    uint32_t __getFieldUint32Value(const std::string &name) {                        \
        FieldContentValue v = __getFieldContentValue(name);                    \
        return v->uint32Value;                                                 \
    }                                                                          \
    uint64_t __getFieldUint64Value(const std::string &name) {                        \
        FieldContentValue v = __getFieldContentValue(name);                    \
        return v->uint64Value;                                                 \
    }                                                                          \
    Object __getFieldObjectValue(const std::string &name) {                          \
        FieldContentValue v = __getFieldContentValue(name);                    \
        return v->objectValue;                                                 \
    }                                                                          \
    String __getFieldStringValue(const std::string &name) {                          \
        FieldContentValue v = __getFieldContentValue(name);                    \
        return v->stringValue;                                                 \
    }                                                                          \
    void __setFieldIntValue(const std::string &name, int value) {                    \
        __setFieldValue(name, value);                                          \
    }                                                                          \
    void __setFieldByteValue(const std::string &name, uint8_t value) {               \
        __setFieldValue(name, value);                                          \
    }                                                                          \
    void __setFieldDoubleValue(const std::string &name, double value) {              \
        __setFieldValue(name, value);                                          \
    }                                                                          \
    void __setFieldFloatValue(const std::string &name, float value) {                \
        __setFieldValue(name, value);                                          \
    }                                                                          \
    void __setFieldLongValue(const std::string &name, long value) {                  \
        __setFieldValue(name, value);                                          \
    }                                                                          \
    void __setFieldUint8Value(const std::string &name, uint8_t value) {              \
        __setFieldValue(name, value);                                          \
    }                                                                          \
    void __setFieldBoolValue(const std::string &name, bool value) {                  \
        __setFieldValue(name, value);                                          \
    }                                                                          \
    void __setFieldUint16Value(const std::string &name, uint16_t value) {            \
        __setFieldValue(name, value);                                          \
    }                                                                          \
    void __setFieldUint32Value(const std::string &name, uint32_t value) {            \
        __setFieldValue(name, value);                                          \
    }                                                                          \
    void __setFieldUint64Value(const std::string &name, uint64_t value) {            \
        __setFieldValue(name, value);                                          \
    }                                                                          \
    void __setFieldStringValue(const std::string &name, std::string value) {         \
        __setFieldValue(name, createString(value));                            \
    }                                                                          \
    void __setFieldObjectValue(const std::string &name, Object value) {              \
        __setFieldValue(name, value);                                          \
    }                                                                          \
    template <typename Q> void __setFieldValue(const std::string &name, Q value) {   \
        Field f = __maps->get(createString(name));                             \
        _FieldContent<Q> *content =                                            \
            dynamic_cast<_FieldContent<Q> *>(f.get_pointer());                 \
        content->setfunc(value);                                               \
    }                                                                          \
    FieldContentValue __getFieldContentValue(const std::string &name) {              \
        Field f = __maps->get(createString(name));                             \
        FieldContentValue val = createFieldContentValue();                     \
        switch (f->getId()) {                                                  \
        case 0:                                                                \
            val->set(std::get<0>(getFuncTuple)());                             \
            break;                                                             \
        case 1:                                                                \
            val->set(std::get<1>(getFuncTuple)());                             \
            break;                                                             \
        case 2:                                                                \
            val->set(std::get<2>(getFuncTuple)());                             \
            break;                                                             \
        case 3:                                                                \
            val->set(std::get<3>(getFuncTuple)());                             \
            break;                                                             \
        case 4:                                                                \
            val->set(std::get<4>(getFuncTuple)());                             \
            break;                                                             \
        case 5:                                                                \
            val->set(std::get<5>(getFuncTuple)());                             \
            break;                                                             \
        case 6:                                                                \
            val->set(std::get<6>(getFuncTuple)());                             \
            break;                                                             \
        case 7:                                                                \
            val->set(std::get<7>(getFuncTuple)());                             \
            break;                                                             \
        case 8:                                                                \
            val->set(std::get<8>(getFuncTuple)());                             \
            break;                                                             \
        case 9:                                                                \
            val->set(std::get<9>(getFuncTuple)());                             \
            break;                                                             \
        case 10:                                                               \
            val->set(std::get<10>(getFuncTuple)());                            \
            break;                                                             \
        case 11:                                                               \
            val->set(std::get<11>(getFuncTuple)());                            \
            break;                                                             \
        case 12:                                                               \
            val->set(std::get<12>(getFuncTuple)());                            \
            break;                                                             \
        case 13:                                                               \
            val->set(std::get<13>(getFuncTuple)());                            \
            break;                                                             \
        case 14:                                                               \
            val->set(std::get<14>(getFuncTuple)());                            \
            break;                                                             \
        case 15:                                                               \
            val->set(std::get<15>(getFuncTuple)());                            \
            break;                                                             \
        }                                                                      \
        return val;                                                            \
    }                                                                          \
    void __createFieldObject(const std::string &name) {                              \
        Field f = __maps->get(createString(name));                             \
        switch (f->getId()) {                                                  \
        case 0:                                                                \
            std::get<0>(createFuncTuple)();                                    \
            break;                                                             \
        case 1:                                                                \
            std::get<1>(createFuncTuple)();                                    \
            break;                                                             \
        case 2:                                                                \
            std::get<2>(createFuncTuple)();                                    \
            break;                                                             \
        case 3:                                                                \
            std::get<3>(createFuncTuple)();                                    \
            break;                                                             \
        case 4:                                                                \
            std::get<4>(createFuncTuple)();                                    \
            break;                                                             \
        case 5:                                                                \
            std::get<5>(createFuncTuple)();                                    \
            break;                                                             \
        case 6:                                                                \
            std::get<6>(createFuncTuple)();                                    \
            break;                                                             \
        case 7:                                                                \
            std::get<7>(createFuncTuple)();                                    \
            break;                                                             \
        case 8:                                                                \
            std::get<8>(createFuncTuple)();                                    \
            break;                                                             \
        case 9:                                                                \
            std::get<9>(createFuncTuple)();                                    \
            break;                                                             \
        case 10:                                                               \
            std::get<10>(createFuncTuple)();                                   \
            break;                                                             \
        case 11:                                                               \
            std::get<11>(createFuncTuple)();                                   \
            break;                                                             \
        case 12:                                                               \
            std::get<12>(createFuncTuple)();                                   \
            break;                                                             \
        case 13:                                                               \
            std::get<13>(createFuncTuple)();                                   \
            break;                                                             \
        case 14:                                                               \
            std::get<14>(createFuncTuple)();                                   \
            break;                                                             \
        case 15:                                                               \
            std::get<15>(createFuncTuple)();                                   \
            break;                                                             \
        }                                                                      \
    }                                                                          \
    Pair<Object, Object> __createMapItemObject(const std::string &name) {            \
        Field f = __maps->get(createString(name));                             \
        switch (f->getId()) {                                                  \
        case 0:                                                                \
            return std::get<0>(createMapItemFuncTuple)();                      \
            break;                                                             \
        case 1:                                                                \
            return std::get<1>(createMapItemFuncTuple)();                      \
            break;                                                             \
        case 2:                                                                \
            return std::get<2>(createMapItemFuncTuple)();                      \
            break;                                                             \
        case 3:                                                                \
            return std::get<3>(createMapItemFuncTuple)();                      \
            break;                                                             \
        case 4:                                                                \
            return std::get<4>(createMapItemFuncTuple)();                      \
            break;                                                             \
        case 5:                                                                \
            return std::get<5>(createMapItemFuncTuple)();                      \
            break;                                                             \
        case 6:                                                                \
            return std::get<6>(createMapItemFuncTuple)();                      \
            break;                                                             \
        case 7:                                                                \
            return std::get<7>(createMapItemFuncTuple)();                      \
            break;                                                             \
        case 8:                                                                \
            return std::get<8>(createMapItemFuncTuple)();                      \
            break;                                                             \
        case 9:                                                                \
            return std::get<9>(createMapItemFuncTuple)();                      \
            break;                                                             \
        case 10:                                                               \
            return std::get<10>(createMapItemFuncTuple)();                     \
            break;                                                             \
        case 11:                                                               \
            return std::get<11>(createMapItemFuncTuple)();                     \
            break;                                                             \
        case 12:                                                               \
            return std::get<12>(createMapItemFuncTuple)();                     \
            break;                                                             \
        case 13:                                                               \
            return std::get<13>(createMapItemFuncTuple)();                     \
            break;                                                             \
        case 14:                                                               \
            return std::get<14>(createMapItemFuncTuple)();                     \
            break;                                                             \
        case 15:                                                               \
            return std::get<15>(createMapItemFuncTuple)();                     \
            break;                                                             \
        }                                                                      \
        return nullptr;                                                        \
    }                                                                          \
    Object __createListItemObject(const std::string &name) {                          \
        Field f = __maps->get(createString(name));                             \
        switch (f->getId()) {                                                  \
        case 0:                                                                \
            return std::get<0>(createListItemFuncTuple)();                     \
            break;                                                             \
        case 1:                                                                \
            return std::get<1>(createListItemFuncTuple)();                     \
            break;                                                             \
        case 2:                                                                \
            return std::get<2>(createListItemFuncTuple)();                     \
            break;                                                             \
        case 3:                                                                \
            return std::get<3>(createListItemFuncTuple)();                     \
            break;                                                             \
        case 4:                                                                \
            return std::get<4>(createListItemFuncTuple)();                     \
            break;                                                             \
        case 5:                                                                \
            return std::get<5>(createListItemFuncTuple)();                     \
            break;                                                             \
        case 6:                                                                \
            return std::get<6>(createListItemFuncTuple)();                     \
            break;                                                             \
        case 7:                                                                \
            return std::get<7>(createListItemFuncTuple)();                     \
            break;                                                             \
        case 8:                                                                \
            return std::get<8>(createListItemFuncTuple)();                     \
            break;                                                             \
        case 9:                                                                \
            return std::get<9>(createListItemFuncTuple)();                     \
            break;                                                             \
        case 10:                                                               \
            return std::get<10>(createListItemFuncTuple)();                    \
            break;                                                             \
        case 11:                                                               \
            return std::get<11>(createListItemFuncTuple)();                    \
            break;                                                             \
        case 12:                                                               \
            return std::get<12>(createListItemFuncTuple)();                    \
            break;                                                             \
        case 13:                                                               \
            return std::get<13>(createListItemFuncTuple)();                    \
            break;                                                             \
        case 14:                                                               \
            return std::get<14>(createListItemFuncTuple)();                    \
            break;                                                             \
        case 15:                                                               \
            return std::get<15>(createListItemFuncTuple)();                    \
            break;                                                             \
        }                                                                      \
        return nullptr;                                                        \
    }                                                                          \
    Object __getListItemObject(const std::string &name, int index) {                  \
        Field f = __maps->get(createString(name));                             \
        switch (f->getId()) {                                                  \
        case 0:                                                                \
            return std::get<0>(getListItemFuncTuple)(index);                   \
            break;                                                             \
        case 1:                                                                \
            return std::get<1>(getListItemFuncTuple)(index);                   \
            break;                                                             \
        case 2:                                                                \
            return std::get<2>(getListItemFuncTuple)(index);                   \
            break;                                                             \
        case 3:                                                                \
            return std::get<3>(getListItemFuncTuple)(index);                   \
            break;                                                             \
        case 4:                                                                \
            return std::get<4>(getListItemFuncTuple)(index);                   \
            break;                                                             \
        case 5:                                                                \
            return std::get<5>(getListItemFuncTuple)(index);                   \
            break;                                                             \
        case 6:                                                                \
            return std::get<6>(getListItemFuncTuple)(index);                   \
            break;                                                             \
        case 7:                                                                \
            return std::get<7>(getListItemFuncTuple)(index);                   \
            break;                                                             \
        case 8:                                                                \
            return std::get<8>(getListItemFuncTuple)(index);                   \
            break;                                                             \
        case 9:                                                                \
            return std::get<9>(getListItemFuncTuple)(index);                   \
            break;                                                             \
        case 10:                                                               \
            return std::get<10>(getListItemFuncTuple)(index);                  \
            break;                                                             \
        case 11:                                                               \
            return std::get<11>(getListItemFuncTuple)(index);                  \
            break;                                                             \
        case 12:                                                               \
            return std::get<12>(getListItemFuncTuple)(index);                  \
            break;                                                             \
        case 13:                                                               \
            return std::get<13>(getListItemFuncTuple)(index);                  \
            break;                                                             \
        case 14:                                                               \
            return std::get<14>(getListItemFuncTuple)(index);                  \
            break;                                                             \
        case 15:                                                               \
            return std::get<15>(getListItemFuncTuple)(index);                  \
            break;                                                             \
        }                                                                      \
        return nullptr;                                                        \
    }                                                                          \
    void __addMapItemObject(const std::string &name, sp<_Object> key,                \
                            sp<_Object> value) {                               \
        Field f = __maps->get(createString(name));                             \
        switch (f->getId()) {                                                  \
        case 0:                                                                \
            return std::get<0>(addMapItemFuncTuple)(key, value);               \
            break;                                                             \
        case 1:                                                                \
            return std::get<1>(addMapItemFuncTuple)(key, value);               \
            break;                                                             \
        case 2:                                                                \
            return std::get<2>(addMapItemFuncTuple)(key, value);               \
            break;                                                             \
        case 3:                                                                \
            return std::get<3>(addMapItemFuncTuple)(key, value);               \
            break;                                                             \
        case 4:                                                                \
            return std::get<4>(addMapItemFuncTuple)(key, value);               \
            break;                                                             \
        case 5:                                                                \
            return std::get<5>(addMapItemFuncTuple)(key, value);               \
            break;                                                             \
        case 6:                                                                \
            return std::get<6>(addMapItemFuncTuple)(key, value);               \
            break;                                                             \
        case 7:                                                                \
            return std::get<7>(addMapItemFuncTuple)(key, value);               \
            break;                                                             \
        case 8:                                                                \
            return std::get<8>(addMapItemFuncTuple)(key, value);               \
            break;                                                             \
        case 9:                                                                \
            return std::get<9>(addMapItemFuncTuple)(key, value);               \
            break;                                                             \
        case 10:                                                               \
            return std::get<10>(addMapItemFuncTuple)(key, value);              \
            break;                                                             \
        case 11:                                                               \
            return std::get<11>(addMapItemFuncTuple)(key, value);              \
            break;                                                             \
        case 12:                                                               \
            return std::get<12>(addMapItemFuncTuple)(key, value);              \
            break;                                                             \
        case 13:                                                               \
            return std::get<13>(addMapItemFuncTuple)(key, value);              \
            break;                                                             \
        case 14:                                                               \
            return std::get<14>(addMapItemFuncTuple)(key, value);              \
            break;                                                             \
        case 15:                                                               \
            return std::get<15>(addMapItemFuncTuple)(key, value);              \
            break;                                                             \
        }                                                                      \
    }                                                                          \
    void __addListItemObject(const std::string &name, sp<_Object> obj) {             \
        Field f = __maps->get(createString(name));                             \
        switch (f->getId()) {                                                  \
        case 0:                                                                \
            return std::get<0>(addListItemFuncTuple)(obj);                     \
            break;                                                             \
        case 1:                                                                \
            return std::get<1>(addListItemFuncTuple)(obj);                     \
            break;                                                             \
        case 2:                                                                \
            return std::get<2>(addListItemFuncTuple)(obj);                     \
            break;                                                             \
        case 3:                                                                \
            return std::get<3>(addListItemFuncTuple)(obj);                     \
            break;                                                             \
        case 4:                                                                \
            return std::get<4>(addListItemFuncTuple)(obj);                     \
            break;                                                             \
        case 5:                                                                \
            return std::get<5>(addListItemFuncTuple)(obj);                     \
            break;                                                             \
        case 6:                                                                \
            return std::get<6>(addListItemFuncTuple)(obj);                     \
            break;                                                             \
        case 7:                                                                \
            return std::get<7>(addListItemFuncTuple)(obj);                     \
            break;                                                             \
        case 8:                                                                \
            return std::get<8>(addListItemFuncTuple)(obj);                     \
            break;                                                             \
        case 9:                                                                \
            return std::get<9>(addListItemFuncTuple)(obj);                     \
            break;                                                             \
        case 10:                                                               \
            return std::get<10>(addListItemFuncTuple)(obj);                    \
            break;                                                             \
        case 11:                                                               \
            return std::get<11>(addListItemFuncTuple)(obj);                    \
            break;                                                             \
        case 12:                                                               \
            return std::get<12>(addListItemFuncTuple)(obj);                    \
            break;                                                             \
        case 13:                                                               \
            return std::get<13>(addListItemFuncTuple)(obj);                    \
            break;                                                             \
        case 14:                                                               \
            return std::get<14>(addListItemFuncTuple)(obj);                    \
            break;                                                             \
        case 15:                                                               \
            return std::get<15>(addListItemFuncTuple)(obj);                    \
            break;                                                             \
        }                                                                      \
    }                                                                          \
    ArrayList<Pair<Object, Object>> __getMapItemObjects(                       \
        const std::string &name) {                                                   \
        Field f = __maps->get(createString(name));                             \
        switch (f->getId()) {                                                  \
        case 0:                                                                \
            return std::get<0>(getMapItemsFuncTuple)();                        \
            break;                                                             \
        case 1:                                                                \
            return std::get<1>(getMapItemsFuncTuple)();                        \
            break;                                                             \
        case 2:                                                                \
            return std::get<2>(getMapItemsFuncTuple)();                        \
            break;                                                             \
        case 3:                                                                \
            return std::get<3>(getMapItemsFuncTuple)();                        \
            break;                                                             \
        case 4:                                                                \
            return std::get<4>(getMapItemsFuncTuple)();                        \
            break;                                                             \
        case 5:                                                                \
            return std::get<5>(getMapItemsFuncTuple)();                        \
            break;                                                             \
        case 6:                                                                \
            return std::get<6>(getMapItemsFuncTuple)();                        \
            break;                                                             \
        case 7:                                                                \
            return std::get<7>(getMapItemsFuncTuple)();                        \
            break;                                                             \
        case 8:                                                                \
            return std::get<8>(getMapItemsFuncTuple)();                        \
            break;                                                             \
        case 9:                                                                \
            return std::get<9>(getMapItemsFuncTuple)();                        \
            break;                                                             \
        case 10:                                                               \
            return std::get<10>(getMapItemsFuncTuple)();                       \
            break;                                                             \
        case 11:                                                               \
            return std::get<11>(getMapItemsFuncTuple)();                       \
            break;                                                             \
        case 12:                                                               \
            return std::get<12>(getMapItemsFuncTuple)();                       \
            break;                                                             \
        case 13:                                                               \
            return std::get<13>(getMapItemsFuncTuple)();                       \
            break;                                                             \
        case 14:                                                               \
            return std::get<14>(getMapItemsFuncTuple)();                       \
            break;                                                             \
        case 15:                                                               \
            return std::get<15>(getMapItemsFuncTuple)();                       \
            break;                                                             \
        }                                                                      \
        return nullptr;                                                        \
    }                                                                          \
    int __getContainerSize(const std::string &name) {                                 \
        Field f = __maps->get(createString(name));                             \
        switch (f->getId()) {                                                  \
        case 0:                                                                \
            return std::get<0>(getContainerSizeFuncTuple)();                   \
            break;                                                             \
        case 1:                                                                \
            return std::get<1>(getContainerSizeFuncTuple)();                   \
            break;                                                             \
        case 2:                                                                \
            return std::get<2>(getContainerSizeFuncTuple)();                   \
            break;                                                             \
        case 3:                                                                \
            return std::get<3>(getContainerSizeFuncTuple)();                   \
            break;                                                             \
        case 4:                                                                \
            return std::get<4>(getContainerSizeFuncTuple)();                   \
            break;                                                             \
        case 5:                                                                \
            return std::get<5>(getContainerSizeFuncTuple)();                   \
            break;                                                             \
        case 6:                                                                \
            return std::get<6>(getContainerSizeFuncTuple)();                   \
            break;                                                             \
        case 7:                                                                \
            return std::get<7>(getContainerSizeFuncTuple)();                   \
            break;                                                             \
        case 8:                                                                \
            return std::get<8>(getContainerSizeFuncTuple)();                   \
            break;                                                             \
        case 9:                                                                \
            return std::get<9>(getContainerSizeFuncTuple)();                   \
            break;                                                             \
        case 10:                                                               \
            return std::get<10>(getContainerSizeFuncTuple)();                  \
            break;                                                             \
        case 11:                                                               \
            return std::get<11>(getContainerSizeFuncTuple)();                  \
            break;                                                             \
        case 12:                                                               \
            return std::get<12>(getContainerSizeFuncTuple)();                  \
            break;                                                             \
        case 13:                                                               \
            return std::get<13>(getContainerSizeFuncTuple)();                  \
            break;                                                             \
        case 14:                                                               \
            return std::get<14>(getContainerSizeFuncTuple)();                  \
            break;                                                             \
        case 15:                                                               \
            return std::get<15>(getContainerSizeFuncTuple)();                  \
            break;                                                             \
        }                                                                      \
        return -1;                                                             \
    }

#endif
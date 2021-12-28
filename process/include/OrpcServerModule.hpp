#ifndef __OBOTCHA_RPC_SERVER_MODULE_H__
#define __OBOTCHA_RPC_SERVER_MODULE_H__

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sys/types.h>
#include <typeinfo>
#include <utility>

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "JsonValue.hpp"
#include "JsonReader.hpp"
#include "String.hpp"
#include "Reflect.hpp"

namespace obotcha {

OrpcReflector ServerReflects[1024*32];

//no param function
#define ImplOrpcServerFunc_1(Entry) \
    OrpcResult _OrpcServerFunc_##Entry()

#define DeclareOrpcServerFuncImpl_1(Entry) \
    ImplOrpcServerFunc_1(Entry);

#define InvokeOrpcServerFunc_1(Entry) \
    _OrpcServerFunc_##Entry()


//1 Param
#define ImplOrpcServerFunc_3(Entry,\
                            Type1,Param1) \
    OrpcResult _OrpcServerFunc_##Entry(Type1 Param1)

#define DeclareOrpcServerFuncImpl_3(Entry,\
                               Type1,Param1) \
    ImplOrpcServerFunc_3(Entry,Type1,Param1);

#define InvokeOrpcServerFunc_2(Entry,Param1) \
    _OrpcServerFunc_##Entry(Param1)

//2
#define ImplOrpcServerFunc_5(Entry,\
                            Type1,Param1,\
                            Type2,Param2) \
    OrpcResult _OrpcServerFunc_##Entry(Type1 Param1,Type2 Param2)

#define DeclareOrpcServerFuncImpl_5(Entry,\
                               Type1,Param1,\
                               Type2,Param2) \
    ImplOrpcServerFunc_5(Entry,\
                        Type1,Param1,\
                        Type2,Param2);

#define InvokeOrpcServerFunc_3(Entry,Param1,Param2) \
    _OrpcServerFunc_##Entry(Param1,Param2)

//3
#define ImplOrpcServerFunc_7(Entry,\
                               Type1,Param1,\
                               Type2,Param2,\
                               Type3,Param3) \
    OrpcResult _OrpcServerFunc_##Entry(Entry,Type1 Param1,Type2 Param2,Type3 Param3)

#define DeclareOrpcServerFuncImpl_7(Entry,\
                               Type1,Param1,\
                               Type2,Param2,\
                               Type3,Param3) \
    ImplOrpcServerFunc_7(Entry,\
                        Type1,Param1,\
                        Type2,Param2,\
                        Type3,Param3);

#define InvokeOrpcServerFunc_4(Entry,Param1,Param2,Param3) \
    _OrpcServerFunc_##Entry(Param1,Param2,Param3)

//4
#define ImplOrpcServerFunc_9(Entry,\
                               Type1,Param1,\
                               Type2,Param2,\
                               Type3,Param3,\
                               Type4,Param4) \
    OrpcResult _OrpcServerFunc_##Entry(Type1 Param1,Type2 Param2,Type3 Param3,Type4 Param4)

#define DeclareOrpcServerFuncImpl_9(Entry,\
                               Type1,Param1,\
                               Type2,Param2,\
                               Type3,Param3,\
                               Type4,Param4) \
    ImplOrpcServerFunc_9(Entry,\
                        Type1,Param1,\
                        Type2,Param2,\
                        Type3,Param3,\
                        Type4 Param4);

#define InvokeOrpcServerFunc_5(Entry,Param1,Param2,Param3,Param4) \
    _OrpcServerFunc_##Entry(Param1,Param2,Param3,Param4)

//5
#define ImplOrpcServerFunc_11(Entry,\
                               Type1,Param1,\
                               Type2,Param2,\
                               Type3,Param3,\
                               Type4,Param4,\
                               Type5,Param5) \
    OrpcResult _OrpcServerFunc_##Entry(Type1 Param1,Type2 Param2,Type3 Param3,Type4 Param4,Type5 Param5)

#define DeclareOrpcServerFuncImpl_11(Entry,\
                               Type1,Param1,\
                               Type2,Param2,\
                               Type3,Param3,\
                               Type4,Param4,\
                               Type5,Param5) \
    ImplOrpcServerFunc_11(Entry,\
                          Type1,Param1,\
                          Type2,Param2,\
                          Type3,Param3,\
                          Type4,Param4,\
                          Type5,Param5);

#define InvokeOrpcServerFunc_6(Entry,Param1,Param2,Param3,Param4,Param5) \
    _OrpcServerFunc_##Entry(Param1,Param2,Param3,Param4,Param5)

//6
#define ImplOrpcServerFunc_13(Entry,\
                               Type1,Param1,\
                               Type2,Param2,\
                               Type3,Param3,\
                               Type4,Param4,\
                               Type5,Param5,\
                               Type6,Param6) \
    OrpcResult _OrpcServerFunc_##Entry(Type1 Param1,Type2 Param2,Type3 Param3,\
                                       Type4 Param4,Type5 Param5,Type6 Param6)

#define DeclareOrpcServerFuncImpl_13(Entry,\
                               Type1,Param1,\
                               Type2,Param2,\
                               Type3,Param3,\
                               Type4,Param4,\
                               Type5,Param5,\
                               Type6,Param6) \
    ImplOrpcServerFunc_13(Entry,\
                          Type1,Param1,\
                          Type2,Param2,\
                          Type3,Param3,\
                          Type4,Param4,\
                          Type5,Param5,\
                          Type6,Param6);


#define InvokeOrpcServerFunc_7(Entry,Param1,Param2,Param3,Param4,Param5,Param6) \
    _OrpcServerFunc_##Entry(Param1,Param2,Param3,Param4,Param5,Param6)

//7
#define ImplOrpcServerFunc_15(Entry,\
                               Type1,Param1,\
                               Type2,Param2,\
                               Type3,Param3,\
                               Type4,Param4,\
                               Type5,Param5,\
                               Type6,Param6,\
                               Type7,Param7) \
    OrpcResult _OrpcServerFunc_##Entry(Type1 Param1,Type2 Param2,Type3 Param3,\
                                       Type4 Param4,Type5 Param5,Type6 Param6,\
                                       Type7 Param7)

#define DeclareOrpcServerFuncImpl_15(Entry,\
                               Type1,Param1,\
                               Type2,Param2,\
                               Type3,Param3,\
                               Type4,Param4,\
                               Type5,Param5,\
                               Type6,Param6,\
                               Type7,Param7) \
    ImplOrpcServerFunc_15(Entry,\
                          Type1,Param1,\
                          Type2,Param2,\
                          Type3,Param3,\
                          Type4,Param4,\
                          Type5,Param5,\
                          Type6,Param6,\
                          Type7,Param7);

#define InvokeOrpcServerFunc_8(Entry,Param1,Param2,Param3,Param4,Param5,Param6,Param7) \
    _OrpcServerFunc_##Entry(Param1,Param2,Param3,Param4,Param5,Param6,Param7)

//8
#define ImplOrpcServerFunc_17(Entry,\
                               Type1,Param1,\
                               Type2,Param2,\
                               Type3,Param3,\
                               Type4,Param4,\
                               Type5,Param5,\
                               Type6,Param6,\
                               Type7,Param7,\
                               Type8,Param8) \
    OrpcResult _OrpcServerFunc_##Entry(Type1 Param1,Type2 Param2,Type3 Param3,\
                                       Type4 Param4,Type5 Param5,Type6 Param6,\
                                       Type7 Param7,Type8 Param8)

#define DeclareOrpcServerFuncImpl_17(Entry,\
                               Type1,Param1,\
                               Type2,Param2,\
                               Type3,Param3,\
                               Type4,Param4,\
                               Type5,Param5,\
                               Type6,Param6,\
                               Type7,Param7,\
                               Type8,Param8) \
    ImplOrpcServerFunc_17(Entry,\
                          Type1,Param1,\
                          Type2,Param2,\
                          Type3,Param3,\
                          Type4,Param4,\
                          Type5,Param5,\
                          Type6,Param6,\
                          Type7,Param7,\
                          Type8,Param8);

#define InvokeOrpcServerFunc_9(Entry,Param1,Param2,Param3,Param4,Param5,Param6,Param7,Param8) \
    _OrpcServerFunc_##Entry(Param1,Param2,Param3,Param4,Param5,Param6,Param7,Param8)

//9
#define ImplOrpcServerFunc_19(Entry,\
                               Type1,Param1,\
                               Type2,Param2,\
                               Type3,Param3,\
                               Type4,Param4,\
                               Type5,Param5,\
                               Type6,Param6,\
                               Type7,Param7,\
                               Type8,Param8,\
                               Type9,Param9) \
    OrpcResult _OrpcServerFunc_##Entry(Type1 Param1,Type2 Param2,Type3 Param3,\
                                       Type4 Param4,Type5 Param5,Type6 Param6,\
                                       Type7 Param7,Type8 Param8,Type9 Param9)
                                       
#define DeclareOrpcServerFuncImpl_19(Entry,\
                               Type1,Param1,\
                               Type2,Param2,\
                               Type3,Param3,\
                               Type4,Param4,\
                               Type5,Param5,\
                               Type6,Param6,\
                               Type7,Param7,\
                               Type8,Param8,\
                               Type9,Param9) \
    ImplOrpcServerFunc_19(Entry,\
                          Type1,Param1,\
                          Type2,Param2,\
                          Type3,Param3,\
                          Type4,Param4,\
                          Type5,Param5,\
                          Type6,Param6,\
                          Type7,Param7,\
                          Type8,Param8,\
                          Type9 Param9);

#define InvokeOrpcServerFunc_10(Entry,Param1,Param2,Param3,Param4,Param5,Param6,Param7,Param8,Param9,Param10) \
    _OrpcServerFunc_##Entry(Param1,Param2,Param3,Param4,Param5,Param6,Param7,Param8,Param9,Param10)

//Server Method Declaration
#define DeclareOrpcServerFuncInner1(Count, ...) \
    DeclareOrpcServerFuncImpl_##Count(__VA_ARGS__)

#define DeclareOrpcServerFuncInner(Count, ...) \
    DeclareOrpcServerFuncInner1(Count,__VA_ARGS__)

#define DeclareOrpcServerFunc(...) \
    DeclareOrpcServerFuncInner(GET_ARG_COUNT(__VA_ARGS__),__VA_ARGS__)

//IMPLEMENT FUNCTION
#define ImplOrpcServerFuncInner1(Count, ...) \
    ImplOrpcServerFunc_##Count(__VA_ARGS__)

#define ImplOrpcServerFuncInner(Count, ...) \
    ImplOrpcServerFuncInner1(Count,__VA_ARGS__)

#define ImplOrpcServerFunc(...) \
    ImplOrpcServerFuncInner(GET_ARG_COUNT(__VA_ARGS__),__VA_ARGS__)



//INVOKE FUNCTION
#define InvokeOrpcServerFuncInner1(Count, ...) \
    InvokeOrpcServerFunc_##Count(__VA_ARGS__)

#define InvokeOrpcServerFuncInner(Count, ...) \
    InvokeOrpcServerFuncInner1(Count,__VA_ARGS__)

#define InvokeOrpcServerFunc(...) \
    InvokeOrpcServerFuncInner(GET_ARG_COUNT(__VA_ARGS__),__VA_ARGS__)

}

#endif

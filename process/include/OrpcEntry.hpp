#ifndef __OBOTCHA_RPC_ENTRY_H__
#define __OBOTCHA_RPC_ENTRY_H__

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "JsonValue.hpp"
#include "JsonReader.hpp"
#include "String.hpp"
#include "Reflect.hpp"

namespace obotcha {

#define DeclareOrpcEntryImpl_1(Entry) \
    const int _ORPC_ID_##Entry = Entry;\
    DECLARE_CLASS(OrpcEntry_##Entry) {};

#define DeclareOrpcEntryImpl_3(Entry,\
                               Type1,Param1) \
    const int _ORPC_ID_##Entry = Entry;\
    DECLARE_CLASS(OrpcEntry_##Entry) {\
        public:\
            Type1 Param1;\
            DECLARE_REFLECT_FIELD(OrpcEntry_##Entry,Param1)\
    };

#define DeclareOrpcEntryImpl_5(Entry,\
                               Type1,Param1,\
                               Type2,Param2) \
    const int _ORPC_ID_##Entry = Entry;\
    DECLARE_CLASS(OrpcEntry_##Entry) {\
        public:\
            Type1 Param1;\
            Type2 Param2;\
            DECLARE_REFLECT_FIELD(OrpcEntry_##Entry,Param1,Param2)\
    };

#define DeclareOrpcEntryImpl_7(Entry,\
                               Type1,Param1,\
                               Type2,Param2,\
                               Type3,Param3) \
    const int _ORPC_ID_##Entry = Entry;\
    DECLARE_CLASS(OrpcEntry_##Entry) {\
        public:\
            Type1 Param1;\
            Type2 Param2;\
            Type3 Param3;\
            DECLARE_REFLECT_FIELD(OrpcEntry_##Entry,Param1,Param2,Param3)\
    };

#define DeclareOrpcEntryImpl_9(Entry,\
                               Type1,Param1,\
                               Type2,Param2,\
                               Type3,Param3,\
                               Type4,Param4) \
    const int _ORPC_ID_##Entry = Entry;\
    DECLARE_CLASS(OrpcEntry_##Entry) {\
        public:\
            Type1 Param1;\
            Type2 Param2;\
            Type3 Param3;\
            Type4 Param4;\
            DECLARE_REFLECT_FIELD(OrpcEntry_##Entry,Param1,Param2,Param3,Param4)\
    };

#define DeclareOrpcEntryImpl_11(Entry,\
                               Type1,Param1,\
                               Type2,Param2,\
                               Type3,Param3,\
                               Type4,Param4,\
                               Type5,Param5) \
    const int _ORPC_ID_##Entry = Entry;\
    DECLARE_CLASS(OrpcEntry_##Entry) {\
        public:\
            Type1 Param1;\
            Type2 Param2;\
            Type3 Param3;\
            Type4 Param4;\
            Type5 Param5;\
            DECLARE_REFLECT_FIELD(OrpcEntry_##Entry,Param1,Param2,Param3,Param4,Param5)\
    };

#define DeclareOrpcEntryImpl_13(Entry,\
                               Type1,Param1,\
                               Type2,Param2,\
                               Type3,Param3,\
                               Type4,Param4,\
                               Type5,Param5,\
                               Type6,Param6) \
    const int _ORPC_ID_##Entry = Entry;\
    DECLARE_CLASS(OrpcEntry_##Entry) {\
        public:\
            Type1 Param1;\
            Type2 Param2;\
            Type3 Param3;\
            Type4 Param4;\
            Type5 Param5;\
            Type6 Param6;\
            DECLARE_REFLECT_FIELD(OrpcEntry_##Entry,Param1,Param2,Param3,Param4,Param5,Param6)\
    };

#define DeclareOrpcEntryImpl_15(Entry,\
                               Type1,Param1,\
                               Type2,Param2,\
                               Type3,Param3,\
                               Type4,Param4,\
                               Type5,Param5,\
                               Type6,Param6,\
                               Type7,Param7) \
    const int _ORPC_ID_##Entry = Entry;\
    DECLARE_CLASS(OrpcEntry_##Entry) {\
        public:\
            Type1 Param1;\
            Type2 Param2;\
            Type3 Param3;\
            Type4 Param4;\
            Type5 Param5;\
            Type6 Param6;\
            Type7 Param7;\
            DECLARE_REFLECT_FIELD(OrpcEntry_##Entry,Param1,Param2,Param3,Param4,Param5,Param6,Param7)\
    };

#define DeclareOrpcEntryImpl_17(Entry,\
                               Type1,Param1,\
                               Type2,Param2,\
                               Type3,Param3,\
                               Type4,Param4,\
                               Type5,Param5,\
                               Type6,Param6,\
                               Type7,Param7,\
                               Type8,Param8) \
    const int _ORPC_ID_##Entry = Entry;\
    DECLARE_CLASS(OrpcEntry_##Entry) {\
        public:\
            Type1 Param1;\
            Type2 Param2;\
            Type3 Param3;\
            Type4 Param4;\
            Type5 Param5;\
            Type6 Param6;\
            Type7 Param7;\
            Type8 Param8;\
            DECLARE_REFLECT_FIELD(OrpcEntry_##Entry,Param1,Param2,Param3,Param4,Param5,Param6,Param7,Param8)\
    };

#define DeclareOrpcEntryImpl_19(Entry,\
                               Type1,Param1,\
                               Type2,Param2,\
                               Type3,Param3,\
                               Type4,Param4,\
                               Type5,Param5,\
                               Type6,Param6,\
                               Type7,Param7,\
                               Type8,Param8,\
                               Type9,Param9) \
    const int _ORPC_ID_##Entry = Entry;\
    DECLARE_CLASS(OrpcEntry_##Entry) {\
        public:\
            Type1 Param1;\
            Type2 Param2;\
            Type3 Param3;\
            Type4 Param4;\
            Type5 Param5;\
            Type6 Param6;\
            Type7 Param7;\
            Type8 Param8;\
            Type9 Param9;\
            DECLARE_REFLECT_FIELD(OrpcEntry_##Entry,Param1,Param2,Param3,Param4,Param5,Param6,Param7,Param8,Param9)\
    };

//Orpc Entry
#define DeclareOrpcEntryInner1(Count, ...) \
    DeclareOrpcEntryImpl_##Count(__VA_ARGS__)

#define DeclareOrpcEntryInner(Count, ...) \
    DeclareOrpcEntryInner1(Count,__VA_ARGS__)

#define DeclareOrpcEntry(...) \
    DeclareOrpcEntryInner(GET_ARG_COUNT(__VA_ARGS__),__VA_ARGS__)


DECLARE_CLASS(OrpcReflector) {
public:
    virtual void onReflect(Object,String) = 0;
};

DECLARE_TEMPLATE_CLASS(OrpcReflectorImpl,1) IMPLEMENTS(OrpcReflector) {
public:
    void onReflect(Object o,String v) {
        JsonReader reader = createJsonReader(v);
        auto jvalue = reader->get();
        jvalue->reflectTo(o);
    }
};

DECLARE_CLASS(OrpcResult) {
//TODO
};

}
#endif

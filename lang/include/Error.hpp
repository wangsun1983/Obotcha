#ifndef __ERROR_HPP__
#define __ERROR_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "String.hpp"

namespace obotcha {

enum ErrorType {
    InvalidParam = 200,
    InvalidStatus,
    FileNotExists,
    AlreadyExecute,
    AlreadyExists,
    AlreadyComplete,
    AlreadyDestroy,
    NotCreate,
    NotStart,
    OverSize,
    MiniZipFail,
    NetBindFail,
    NetListenFail,
    NetConnectFail,
    AttributeSetFail,
    OpenFail,
    CreateFail,
    WriteFail,
    ReadFail,
    MmapFail,
    GenKeyFail,
    SetKeyFail,
    NotFound,
    WaitTimeout,
    WaitFail,
    NotSupport,
    ErrorMax,
}; 

DECLARE_SIMPLE_CLASS(Error) {
public:
    String toString(int error);

private:
    static const String ErrorString;
    static const String InvalidParamString;
    static const String InvalidStatusString;
    static const String FileNotExistsString;
    static const String AlreadyExistsString;
    static const String AlreadyDestroyString;
    static const String NotCreateString;
    static const String NotStartString;
    static const String OverSizeString;
    static const String MiniZipFailString;
    static const String NetBindFailString;
    static const String NetListenFailString;
    static const String NetConnectFailString;
    static const String CreateFailString;
    static const String AttributeSetFailString;
    static const String OpenFailString;
    static const String WriteFailString;
    static const String ReadFailString;
    static const String MmapFailString;
    static const String GenKeyFailString;
    static const String SetKeyFailString;
    static const String NotFoundString;
    static const String WaitTimeoutString;
    static const String WaitFailString;
    static const String NotSupportString;

};

}

#endif
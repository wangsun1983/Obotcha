#ifndef __OBOTCHA_ERROR_HPP__
#define __OBOTCHA_ERROR_HPP__

#include "Object.hpp"
#include "String.hpp"

namespace obotcha {

//if we are lazy,use Fail/Success as return value;
enum GeneralResultType{
    FAIL = -1,
    SUCCESS = 0
};

enum ErrorType {
    InvalidParam = 200,
    InvalidStatus,
    FileNotExists,
    AlreadyRegist,
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
    NetAddrAlreadyUseFail,
    AttributeSetFail,
    OpenFail,
    LockFail,
    LockBusy,
    UnLockInvalid,
    UnLockFail,
    UnLockPerm, //The calling thread does not own the mutex. 
    CreateFail,
    WriteFail,
    WriteAgain,
    ReadFail,
    MmapFail,
    GenKeyFail,
    SetKeyFail,
    NotFound,
    WaitTimeout,
    WaitFail,
    NotSupport,
    SqlFailWrongParam,
    SqlFailOpen,
    SqlFailNoDb,
    SqlExecFail,
    SqlTransactionFail,
    ErrorMax,
};

DECLARE_CLASS(Error) {
public:
    static String toString(int error);

private:
    const static char* errors[];
};

} // namespace obotcha

#endif

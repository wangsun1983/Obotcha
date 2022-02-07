#include "Error.hpp"
#include "Object.hpp"
#include "StrongPointer.hpp"

namespace obotcha {

const char* st(Error)::errors[] = {
    "Invalid Param",            //InvalidParam,
    "Invalid Status",           //InvalidStatus,
    "File Not Exists",          //FileNotExists,
    "Already Regist",           //AlreadyRegist,
    "Already Execute",          //AlreadyExecute,
    "Already Exists",           //AlreadyExists,
    "Already Complete",         //AlreadyComplete,
    "Already Destroy",          //AlreadyDestroy,
    "Not Create",               //NotCreate,
    "Not Start",                //NotStart,
    "Over Size",                //OverSize,
    "MiniZip Fail",             //MiniZipFail,
    "Net Bind Fail",            //NetBindFail,
    "Net Listen Fail",          //NetListenFail,
    "Net Connect Fail",         //NetConnectFail,
    "Net Address Already Used", //NetAddrAlreadyUseFail,
    "Attribute Set Fail",       //AttributeSetFail,
    "Open Fail",                //OpenFail,
    "Lock Fail",                //LockFail,
    "Lock Busy",                //LockBusy,
    "UnLock Invalid",           //UnLockInvalid,
    "UnLock Fail",              //UnLockFail,
    "UnLock Permission Error",  //UnLockPerm, //The calling thread does not own the mutex. 
    "Create Fail",              //CreateFail,
    "Write Fail",               //WriteFail,
    "Write Again",              //WriteAgain,
    "Read Fail",                //ReadFail,
    "Mmap Fail",                //MmapFail,
    "Gen Key Fail",             //GenKeyFail,
    "Set Key Fail",             //SetKeyFail,
    "Not Found",                //NotFound,
    "Wait Timeout",             //WaitTimeout,
    "Wait Fail",                //WaitFail,
    "Not Support",              //NotSupport,
    "Sql Wrong Param",          //SqlFailWrongParam,
    "Sql Open Fail",            //SqlFailOpen,
    "Sql No Db",                //SqlFailNoDb,
    "Sql Exec Fail",            //SqlExecFail,
    "Sql Transaction Fail",     //SqlTransactionFail,
};

String _Error::toString(int error) {
    error = (error < 0)?-error:error;
    return createString(errors[error-InvalidParam]);
}

} // namespace obotcha
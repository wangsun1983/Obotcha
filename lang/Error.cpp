#include "Error.hpp"
#include "Object.hpp"
#include "StrongPointer.hpp"

namespace obotcha {

const String _Error::ErrorString = createString("Error");
const String _Error::InvalidParamString = createString("Invalid Param");
const String _Error::InvalidStatusString = createString("Invalid Status");
const String _Error::FileNotExistsString = createString("File Not Exists");
const String _Error::AlreadyExistsString = createString("Already Exists");
const String _Error::AlreadyDestroyString = createString("Already Destroy");
const String _Error::NotCreateString = createString("Not Create");
const String _Error::NotStartString = createString("Not Start");
const String _Error::OverSizeString = createString("Over Size");
const String _Error::MiniZipFailString = createString("Mini Zip Fail");
const String _Error::NetBindFailString = createString("Net Bind Fail");
const String _Error::NetListenFailString = createString("Net Listen Fail");
const String _Error::NetConnectFailString = createString("Net Connect Fail");
const String _Error::CreateFailString = createString("Create Fail");
const String _Error::AttributeSetFailString =
    createString("Attribute Set Fail");
const String _Error::OpenFailString = createString("Open Fail");
const String _Error::WriteFailString = createString("Write Fail");
const String _Error::ReadFailString = createString("Read Fail");
const String _Error::MmapFailString = createString("Mmap Fail");
const String _Error::GenKeyFailString = createString("Generate Key Fail");
const String _Error::SetKeyFailString = createString("Set Key Fail");
const String _Error::NotFoundString = createString("Not Found");
const String _Error::WaitTimeoutString = createString("Wait Timeout");
const String _Error::WaitFailString = createString("Wait Fail");
const String _Error::NotSupportString = createString("Not Support");
const String _Error::SqlFailWrongParamString = createString("Sql Wrong Param");
const String _Error::SqlFailOpenString = createString("Sql Open Fail");
const String _Error::SqlFailNoDbString = createString("Sql No Db");
const String _Error::SqlExecFailString = createString("Sql Exec Error");
const String _Error::SqlTransactionFailString =
    createString("Sql Transaction Error");

String _Error::toString(int error) {
    switch (error) {
    case -1:
        return ErrorString;

    case -InvalidParam:
        return InvalidParamString;

    case -InvalidStatus:
        return InvalidStatusString;

    case -FileNotExists:
        return FileNotExistsString;

    case -AlreadyExists:
        return AlreadyExistsString;

    case -AlreadyDestroy:
        return AlreadyDestroyString;

    case -NotCreate:
        return NotCreateString;

    case -NotStart:
        return NotStartString;

    case -OverSize:
        return OverSizeString;

    case -MiniZipFail:
        return MiniZipFailString;

    case -NetBindFail:
        return NetBindFailString;

    case -NetListenFail:
        return NetListenFailString;

    case -NetConnectFail:
        return NetConnectFailString;

    case -AttributeSetFail:
        return AttributeSetFailString;

    case -OpenFail:
        return OpenFailString;

    case -CreateFail:
        return CreateFailString;

    case -WriteFail:
        return WriteFailString;

    case -ReadFail:
        return ReadFailString;

    case -MmapFail:
        return MmapFailString;

    case -GenKeyFail:
        return GenKeyFailString;

    case -SetKeyFail:
        return SetKeyFailString;

    case -NotFound:
        return NotFoundString;

    case -WaitTimeout:
        return WaitTimeoutString;

    case -WaitFail:
        return WaitFailString;

    case -NotSupport:
        return NotSupportString;

    case SqlFailWrongParam:
        return SqlFailWrongParamString;

    case SqlFailOpen:
        return SqlFailOpenString;

    case SqlFailNoDb:
        return SqlFailNoDbString;

    case SqlExecFail:
        return SqlExecFailString;

    case SqlTransactionFail:
        return SqlTransactionFailString;
    }

    return nullptr;
}

} // namespace obotcha
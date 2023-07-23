#include "MessageDigestInterface.hpp"
#include "FileInputStream.hpp"

namespace obotcha {


String _MessageDigestInterface::encodeFile(File file) {
    Inspect(file == nullptr || !file->exists(),0)

    FileInputStream stream = createFileInputStream(file);
    stream->open();
    ByteArray arr = stream->readAll();
    stream->close();
    return encodeContent(arr);
}

String _MessageDigestInterface::encodeString(String data) {
    return encodeContent(data->toByteArray());
}

}

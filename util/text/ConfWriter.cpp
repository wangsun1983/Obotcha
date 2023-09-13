#include "ConfWriter.hpp"
#include "FileOutputStream.hpp"

namespace obotcha {

const String _ConfWriter::kConfOutputTemplate = createString("%s = %s \r\n");

_ConfWriter::_ConfWriter(File file) {
    if(!file->exists()) {
        file->createNewFile();
    }
    mFile = file;
}

_ConfWriter::_ConfWriter(String path):_ConfWriter(createFile(path)) {

}

void _ConfWriter::write(ConfValue value) {
    auto stream = createFileOutputStream(mFile);
    stream->open();
    auto iterator = value->getIterator();
    while(iterator->hasValue()) {
        auto conftag = iterator->getTag();
        auto confvalue = iterator->getValue();
        stream->writeString(st(String)::Format(kConfOutputTemplate->toChars(),
                                        conftag->toChars(),
                                        confvalue->toChars()));
        iterator->next();
    }

    stream->close();
}

} // namespace obotcha


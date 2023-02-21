#include "ConfWriter.hpp"
#include "FileOutputStream.hpp"

namespace obotcha {

const String _ConfWriter::ConfOutputTemplate = createString("%s = %s \r\n");

_ConfWriter::_ConfWriter(File file) {
    if(!file->exists()) {
        file->createNewFile();
    }
    mFile = file;
}

_ConfWriter::_ConfWriter(String path):_ConfWriter(createFile(path)) {

}

_ConfWriter::_ConfWriter(const char *path):_ConfWriter(createFile(path)) {

}

void _ConfWriter::write(ConfValue value) {
    auto stream = createFileOutputStream(mFile);
    stream->open();
    auto iterator = value->getIterator();
    while(iterator->hasValue()) {
        auto tag = iterator->getTag();
        auto value = iterator->getValue();
        stream->writeString(st(String)::format(ConfOutputTemplate->toChars(),
                                        tag->toChars(),
                                        value->toChars()));

        iterator->next();
    }

    stream->close();
}

void _ConfWriter::close() {
    //TODO
}

} // namespace obotcha


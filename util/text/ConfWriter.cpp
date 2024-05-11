#include "ConfWriter.hpp"
#include "FileOutputStream.hpp"

namespace obotcha {

const String _ConfWriter::kConfOutputTemplate = String::New("%s = %s \r\n");

_ConfWriter::_ConfWriter(File file) {
    if(!file->exists()) {
        file->createNewFile();
    }
    mFile = file;
}

_ConfWriter::_ConfWriter(String path):_ConfWriter(File::New(path)) {

}

void _ConfWriter::write(ConfValue value) {
    auto stream = FileOutputStream::New(mFile);
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


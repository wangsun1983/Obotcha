#include "json/reader.h"

#include "ByteArray.hpp"
#include "FileInputStream.hpp"
#include "InitializeException.hpp"
#include "JsonReader.hpp"

namespace obotcha {

sp<_JsonReader> _JsonReader::loadContent(String content) {
    mValue = parse(content);
    return AutoClone(this);
}

sp<_JsonReader> _JsonReader::loadFile(File file) {
    if (!file->exists()) {
        Trigger(InitializeException, "file not exist")
    }

    mValue = parse(file);
    return AutoClone(this);
}

JsonValue _JsonReader::get() { 
    return mValue;
}

JsonValue _JsonReader::parse(File f) const {
    auto stream = createFileInputStream(f);
    stream->open();
    ByteArray buff = stream->readAll();
    stream->close();
    return parse(buff->toString());
}

JsonValue _JsonReader::parse(String content) const {
    Json::CharReaderBuilder builder;
    const std::unique_ptr<Json::CharReader> reader(builder.newCharReader());
    JsonValue value = createJsonValue();
    JSONCPP_STRING errs;
    if (!reader->parse(content->toChars(),
                        content->toChars() + content->size(), 
                        &value->jvalue,
                        &errs)) {
        LOG(ERROR)<<"JsonReader parse "<<content->toChars()
                  <<" fail,error is "<<errs.c_str();
        return nullptr;
    }

    return value->isNull()?nullptr:value;
}

} // namespace obotcha
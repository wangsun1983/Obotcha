#include "StringBuffer.hpp"
#include "SqlContentValues.hpp"
#include "ForEveryOne.hpp"

namespace obotcha {

_SqlContentValues::_SqlContentValues() {
    mContents = createHashMap<String,SqlContent>();
}

String _SqlContentValues::getTags() {
    StringBuffer buffer = createStringBuffer();
    buffer->append("(");
    auto tags = mContents->keySet();
    ForEveryOne(tag,tags) {
        buffer->append(tag,",");
    }
    
    buffer->crop(0,buffer->size() - 1);
    buffer->append(")");
    return buffer->toString();
}

String _SqlContentValues::getValues() {
    StringBuffer buffer = createStringBuffer();
    buffer->append("(");
    auto entries = mContents->entrySet();
    ForEveryOne(entry,entries) {
        if(entry->isStringContent) {
            buffer->append("\"",entry->mContent->get(),"\"",",");
        } else {
            buffer->append(entry->mContent->get(),",");
        }
    }
    
    buffer->crop(0,buffer->size() - 1);
    buffer->append(")");
    return buffer->toString();
}

HashMap<String,SqlContent> _SqlContentValues::getContentValues() {
    return mContents;
}

} // namespace obotcha
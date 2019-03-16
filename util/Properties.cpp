#include "Properties.hpp"
#include "FileInputStream.hpp"
#include "FileOutputStream.hpp"

namespace obotcha {

const String _Properties::gPropEqualString = "=";
const String _Properties::gPropEnterString = "\n";

_Properties::_Properties() {
    mProps = createHashMap<String,String>();
}
    
void _Properties::set(String key,String value) {
    mProps->put(key,value);
}
    
String _Properties::get(String key) {
    return mProps->get(key);
}

void _Properties::load(File file) {
    FileInputStream stream = createFileInputStream(file);
    stream->open();
    String line = stream->readLine();
    while(line != nullptr) {
        int index = line->indexOf(gPropEqualString);
        if(index > 0) {
            String tag = line->subString(0,index);
            String value = line->subString(index + 1,line->size() - 1);
            mProps->put(tag,value);
        }

        line = stream->readLine();
    }
}

void _Properties::save(String path) {
    
    FileOutputStream stream = createFileOutputStream(path);
    MapIterator<String,String> iterator = mProps->getIterator();
    stream->open(st(FileOutputStream)::FileOpenType::Trunc);

    while(iterator->hasValue()) {
        String key = createString(iterator->getKey());
        key->trim();

        String value = createString(iterator->getValue());
        value->trim();
        
        key->append(gPropEqualString);
        key->append(value);
        key->append(gPropEnterString);
        stream->writeString(key);
        if(!iterator->next()) {
            break;
        }
    }
     
    stream->flush();
    stream->close();    
}

}
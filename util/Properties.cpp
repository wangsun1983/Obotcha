#include "Properties.hpp"
#include "FileInputStream.hpp"
#include "FileOutputStream.hpp"
#include "Error.hpp"

namespace obotcha {

const String _Properties::gPropEqualString = "=";
const String _Properties::gPropEnterString = "\n";

_Properties::_Properties() {
    mProps = createHashMap<String,String>();
    mFile = nullptr;
}
    
void _Properties::set(String key,String value) {
    if(value == nullptr) {
        mProps->remove(key);
    } else {
        mProps->put(key,value);
    }
}
    
String _Properties::get(String key) {
    return mProps->get(key);
}

void _Properties::remove(String key) {
    mProps->remove(key);
}

int _Properties::load(String path) {
    mFile = createFile(path);
    if(!mFile->exists()) {
        return -FileNotExists;
    }

    return load(mFile);
}

int _Properties::load(File file) {
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

    stream->close();

    return 0;
}

int _Properties::save() {
    if(mFile == nullptr) {
        return -NotCreate;
    }

    return save(mFile->getAbsolutePath());
}

int _Properties::saveAs(File file) {
    if(file == nullptr) {
        return -InvalidParam;
    }

    return save(file->getAbsolutePath());
}

int _Properties::saveAs(String path) {
   return save(path);
}

int _Properties::save(String path) {
    FileOutputStream stream = createFileOutputStream(path);
    MapIterator<String,String> iterator = mProps->getIterator();
    stream->open(st(FileOutputStream)::Trunc);

    while(iterator->hasValue()) {
        String key = createString(iterator->getKey());
        key->trim();

        String value = createString(iterator->getValue());
        value->trim();
        
        String outStr = key->append(gPropEqualString);
        outStr = outStr->append(value);
        outStr = outStr->append(gPropEnterString);
        stream->writeString(outStr);
        if(!iterator->next()) {
            break;
        }
    }
     
    stream->flush();
    stream->close();

    return 0;  
}

void _Properties::clear() {
    mProps->clear();
}

}
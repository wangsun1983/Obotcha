#include "Properties.hpp"
#include "FileInputStream.hpp"
#include "FileOutputStream.hpp"
#include "Error.hpp"
#include "StringReader.hpp"

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
    StringReader reader = createStringReader(stream);

    String line = reader->readLine();
    if(line != nullptr) {
        printf("line is %s \n",line->toChars());
    } else {
        printf("line is nullptr \n");
    }

    while(line != nullptr) {
        int index = line->indexOf(gPropEqualString);
        printf("index is %d \n",index);
        if(index > 0) {
            printf("substring at 0 \n");
            String tag = line->subString(0,index);
            if(tag == nullptr) {
                printf("tag is nullptr \n");
            }

            String value = line->subString(index + 1,line->size() - index - 1);
            if(value == nullptr) {
                printf("value is nullptr \n");
            }
            mProps->put(tag,value);
        }

        line = reader->readLine();
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
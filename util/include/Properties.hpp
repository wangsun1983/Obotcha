#ifndef __OBOTCHA_PROPERTIES_HPP__
#define __OBOTCHA_PROPERTIES_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "HashMap.hpp"
#include "File.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(Properties) {

public:
    _Properties();
    
    void set(String key,String value);
    
    String get(String key);

    void remove(String key);

    int load(String path);

    int load(File file);

    int save();

    int saveAs(File file);

    int saveAs(String path);

    void clear();

private:

    int save(String path);

    HashMap<String,String> mProps;

    const static String gPropEqualString;
    
    const static String gPropEnterString;
    
    File mFile;

};

}
#endif
#ifndef __PROPERTIES_HPP__
#define __PROPERTIES_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "HashMap.hpp"
#include "File.hpp"

namespace obotcha {

enum PropertiesFailReason {
    PropertiesFailFileNotExit = 200,
};

DECLARE_SIMPLE_CLASS(Properties) {

public:
    _Properties();
    
    void set(String key,String value);
    
    String get(String key);

    void remove(String key);

    int load(String path);

    int load(File file);

    int save(String path);

    int save(File file);

    void clear();

private:
    HashMap<String,String> mProps;

    const static String gPropEqualString;
    
    const static String gPropEnterString;

};

}
#endif
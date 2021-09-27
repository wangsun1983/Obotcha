#include "StrongPointer.hpp"
#include "Object.hpp"
#include "SecretKey.hpp"

namespace obotcha {

//content/keytype/keyheadtype
int _SecretKey::generate(String decKeyFile,String encKeyFile,String params) {
    if(params == nullptr || params->size() == 0) {
        return generate(decKeyFile,encKeyFile,createArrayList<String>());
    }

    ArrayList<String> paramlist = params->split("/");
    if(paramlist->size() == 0) {
        paramlist->add(params);
    }
    return generate(decKeyFile,encKeyFile,paramlist);
}

}


#include "SecretKey.hpp"

namespace obotcha {

//content/keytype/keyheadtype
int _SecretKey::generate(String decKeyFile,String encKeyFile,String params) {
    if(params == nullptr || params->size() == 0) {
        return generate(decKeyFile,encKeyFile,ArrayList<String>::New());
    }

    ArrayList<String> paramlist = params->split("/");
    if(paramlist == nullptr) {
        paramlist = ArrayList<String>::New();
        paramlist->add(params);
    }
    return generate(decKeyFile,encKeyFile,paramlist);
}

int _SecretKey::generate(String decKeyFile,String encKeyFile) {
    return generate(decKeyFile,encKeyFile,ArrayList<String>::New());
}

}


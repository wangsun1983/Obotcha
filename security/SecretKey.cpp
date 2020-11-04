#include "StrongPointer.hpp"
#include "Object.hpp"
#include "SecretKey.hpp"

namespace obotcha {

//content/keytype/keyheadtype
int _SecretKey::generate(String decKeyFile,String encKeyFile,String params) {
    ArrayList<String> paramlist = params->split("/");
    return generate(decKeyFile,encKeyFile,paramlist);
}

}


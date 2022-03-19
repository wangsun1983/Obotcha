#include "Sqlite3ConnectParam.hpp"

namespace obotcha {

const String _Sqlite3ConnectParam::Path = "path";
    
void _Sqlite3ConnectParam::setPath(String p) {
    this->set(Path,p);
}

String _Sqlite3ConnectParam::getPath() {
    return get(Path);
}

} // namespace obotcha

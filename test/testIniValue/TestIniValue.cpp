#include <stdio.h>
#include <unistd.h>

#include "IniValue.hpp"
#include "IniReader.hpp"
#include "Log.hpp"

using namespace obotcha;

int main() {
    IniReader reader = createIniReader("twisted.ini");
    IniValue value = reader->parse();

    String vv = value->getString("quotes","h1",createString("ff"));
    LOGD("vv is ",vv);

}

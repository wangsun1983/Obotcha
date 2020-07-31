#include <initializer_list>
#include "Log.hpp"

namespace obotcha {

void InitLog() {
    google::InitGoogleLogging("Obotcha");
}

}
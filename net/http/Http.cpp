#include "Http.hpp"

namespace obotcha {

String _Http::Config::kMultiPartDirectory = createString("./tmp/");
int _Http::Config::kServerThreadNum = 4;
int _Http::Config::kBufferSize = 1024*256;


void _Http::configMultPartDirectory(String path) {
    Config::kMultiPartDirectory = path;
}

} // namespace obotcha

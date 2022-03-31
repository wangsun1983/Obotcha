#include "YamlWriter.hpp"

namespace obotcha {


_YamlWriter::_YamlWriter(String path) {
    mFile = createFile(path);
}

_YamlWriter::_YamlWriter(File file) {
    mFile = file;
}

void _YamlWriter::write(YamlValue value) {
    std::ofstream fout(mFile->getAbsolutePath()->toChars());
    fout << value->yamlNode;
    fout.close();
}



} // namespace obotcha

#include <stdio.h>
#include <unistd.h>

#include "YamlReader.hpp"
#include "YamlValue.hpp"
#include "YamlArray.hpp"
#include "Log.hpp"

using namespace obotcha;

struct TestData {
    std::string path;
    std::string name;
};

int main() {
    YamlReader reader = createYamlReader("test.yaml");
    YamlValue value = reader->parseNode();

    YamlArray vv = value->getYamlArray("platform");
    String str1 = vv->getString(0,"default");

    int int1 = vv->getInt(2,1122);

    YamlArray artif = value->getYamlArray("artifacts");
    YamlValue artifV = artif->getYamlValue(0);
    //struct TestData t;
    //artifV->reflect(&t);
    //std::cout<<"path is "<<t.path<<std::endl;
    //std::cout<<"name is "<<t.name<<std::endl;

    LOGD("vv is ",str1);
    LOGD("vv is ",int1);

}

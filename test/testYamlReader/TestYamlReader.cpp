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
    YamlReader reader = createYamlReader(createFile("test.yaml"));
    YamlValue root = reader->get();

    //version: '{build}'
    String value1 = root->getString(createString("version"),createString(""));
    if(!value1->equals("{build}")) {
      printf("---[TestYamlReader Test parse()} case1] [FAILED]--- \n");
    }

    //os: Visual Studio 2015
    String value2 = root->getString(createString("os"),createString(""));
    if(!value2->equals("Visual Studio 2015")) {
      printf("---[TestYamlReader Test parse()} case2] [FAILED]--- \n");
    }

    //environment:
    //  matrix:
    //  - Toolset: v140
    //  - Toolset: v120
    //  - Toolset: v110
    //  - Toolset: v100
    YamlValue value3 = root->getYamlValue(createString("environment"));
    YamlValue value3_1 = value3->getYamlValue(createString("matrix"));
    YamlValue value3_1_1 = value3_1->getYamlValueAt(0);
    String chckV = value3_1_1->getString(createString("Toolset"),createString(""));
    if(!chckV->equals("v140")) {
      printf("---[TestYamlReader Test parse()} case3] [FAILED]--- \n");
    }

    YamlValue value3_1_2 = value3_1->getYamlValueAt(1);
    chckV = value3_1_2->getString(createString("Toolset"),createString(""));
    if(!chckV->equals("v120")) {
      printf("---[TestYamlReader Test parse()} case4] [FAILED]--- \n");
    }

    YamlValue value3_1_3 = value3_1->getYamlValueAt(2);
    chckV = value3_1_3->getString(createString("Toolset"),createString(""));
    if(!chckV->equals("v110")) {
      printf("---[TestYamlReader Test parse()} case5] [FAILED]--- \n");
    }

    YamlValue value3_1_4 = value3_1->getYamlValueAt(3);
    chckV = value3_1_4->getString(createString("Toolset"),createString(""));
    if(!chckV->equals("v100")) {
      printf("---[TestYamlReader Test parse()} case6] [FAILED]--- \n");
    }

    printf("---[TestYamlReader Test parse()} case100] [OK]--- \n");
#if 0
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
#endif

}

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

    YamlValue value4 = root->getYamlValue("platform");
    String value4_1 = value4->getStringAt(0,createString(""));
    if(!value4_1->equals("Win32")) {
      printf("---[TestYamlReader Test parse()} case7] [FAILED]--- \n");
    }

    String value4_2 = value4->getStringAt(1,createString(""));
    if(!value4_2->equals("x64")) {
      printf("---[TestYamlReader Test parse()} case8] [FAILED]--- \n");
    }

    String value4_3 = value4->getStringAt(2,createString(""));
    if(!value4_3->equals("111")) {
      printf("---[TestYamlReader Test parse()} case9] [FAILED]--- \n");
    }

    YamlValue value5 = root->getYamlValue("configuration");
    String value5_1 = value5->getStringAt(0,createString(""));
    if(!value5_1->equals("Debug")) {
      printf("---[TestYamlReader Test parse()} case10] [FAILED]--- \n");
    }

    YamlValue value6 = root->getYamlValue("build");
    String value6_1 = value6->getString("verbosity",createString(""));
    if(!value6_1->equals("minimal")) {
      printf("---[TestYamlReader Test parse()} case11] [FAILED]--- \n");
    }

    YamlValue value7 = root->getYamlValue("artifacts");
    YamlValue value7_1 = value7->getYamlValueAt(0);
    String value7_2 = value7_1->getString("path",createString(""));
    String value7_3 = value7_1->getString("name",createString(""));
    if(!value7_2->equals("_build/Testing/Temporary/*") || !value7_3->equals("test_results")) {
      printf("---[TestYamlReader Test parse()} case12] [FAILED]--- \n");
    }

    YamlValue value8 = root->getYamlValue("before_build");
    YamlValue value8_1 = value8->getYamlValueAt(0);
    String str8_1 = value8_1->getString(createString("ps"),createString(""));
    String vv = createString("Write-Output \"Configuration: $env:CONFIGURATION\"\n"\
    "Write-Output \"Platform: $env:PLATFORM\"\n"\
    "$generator = switch ($env:TOOLSET)\n"\
    "{\n"\
    "    \"v140\" {\"Visual Studio 14 2015\"}\n"\
    "    \"v120\" {\"Visual Studio 12 2013\"}\n"\
    "    \"v110\" {\"Visual Studio 11 2012\"}\n"\
    "    \"v100\" {\"Visual Studio 10 2010\"}\n"\
    "}\n"\
    "if ($env:PLATFORM -eq \"x64\")\n"\
    "{\n"\
    "    $generator = \"$generator Win64\"\n"\
    "}\n");

    if(!str8_1->equals(vv)) {
      printf("value is %s \n",vv->toChars());
      printf("---[TestYamlReader Test parse()} case13] [FAILED]--- \n");
    }

    printf("---[TestYamlReader Test parse()} case14] [OK]--- \n");
}

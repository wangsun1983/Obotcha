#include <stdio.h>
#include <unistd.h>

//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "Double.hpp"
#include "XmlReader.hpp"
#include "XmlValue.hpp"
#include "XmlDocument.hpp"

using namespace obotcha;
const char *testdata[46][3] = {
  {"BeiJing54" ,"6378245.0" ,"298.3"},
  {"XiAn80" ,"6378140.0" ,"298.257"},
  {"CGCS2000" ,"6378137.0" ,"298.257222101"},
  {"WGS-84" ,"6378137.0" ,"298.257223563"},
  {"WGS-72" ,"6378135.0" ,"298.26"},
  {"WGS-66" ,"6378145.0" ,"298.25"},
  {"WGS-60" ,"6378165.0" ,"298.3"},
  {"Krassovsky" ,"6378245.0" ,"298.3"},
  {"International" ,"6378388.0" ,"297.0"},
  {"MERIT-83" ,"6378137.0" ,"298.257"},
  {"SGS85" ,"6378136.0" ,"298.257"},
  {"GRS80" ,"6378137.0" ,"298.257222101"},
  {"GRS75" ,"6378140.0" ,"298.257"},
  {"Airy 1830" ,"6377563.396" ,"299.3249753150"},
  {"Modified Airy" ,"6377340.189" ,"299.32493736548"},
  {"Aust_SA" ,"6378160.0" ,"298.25"},
  {"Bessel 1841" ,"6377397.155" ,"299.15281285"},
  {"Clarke 1880" ,"6378249.145" ,"293.4663"},
  {"Clarke 1866" ,"6378206.4" ,"294.9786982139"},
  {"GRS67" ,"6378160.0" ,"298.247167427"},
  {"APL4.9" ,"6378137.0" ,"298.25"},
  {"Andrae" ,"6377104.43" ,"300.0"},
  {"Bessel_nam" ,"6377483.865" ,"299.1528128"},
  {"CPM" ,"6375738.7" ,"334.29"},
  {"Delamber" ,"6376428.0" ,"311.5"},
  {"Engelis" ,"6378136.05" ,"298.2566"},
  {"Everest30" ,"6377276.345" ,"300.8017"},
  {"Everest48" ,"6377304.063" ,"300.8017"},
  {"Everest56" ,"6377301.243" ,"300.8017"},
  {"Everest69" ,"6377295.664" ,"300.8017"},
  {"EverestSS" ,"6377298.556" ,"300.8017"},
  {"Fischer60" ,"6378166.0" ,"298.3"},
  {"Fischer60m" ,"6378155.0" ,"298.3"},
  {"Fischer68" ,"6378150.0" ,"298.3"},
  {"Helmert" ,"6378200.0" ,"298.3"},
  {"Hough" ,"6378270.0" ,"297.0"},
  {"IAU76" ,"6378140.0" ,"298.257"},
  {"Kaula" ,"6378163.0" ,"298.24"},
  {"Lerch" ,"6378139.0" ,"298.257"},
  {"Maupertius" ,"6397300.0" ,"191.0"},
  {"New_intl" ,"6378157.5" ,"298.24961539"},
  {"NWL9D" ,"6378145.0" ,"298.25"},
  {"Plessis" ,"6376523.0" ,"0.0"},
  {"Southeast_asia" ,"6378155.0" ,"298.3000002409"},
  {"Sphere" ,"6370997.0" ,"298.257"},
  {"Walbeck" ,"6376896.0" ,"302.7800001817"},
};


int simpleattrtest() {
    printf("---[XmlReader Test Start]--- \n");
    XmlReader reader = createXmlReader(createFile("test.xml"));
    XmlDocument doc = reader->get();

    String content = doc->toString();
    //printf("content is %s \n",content->toChars());

    XmlValue root = doc->getRootNode();
    //printf("name is %s \n",root->getName()->toChars());
    String name = root->getName();
    if(name == nullptr ||!name->equals("EllipsoidParams")) {
        printf("---[XmlReader Test parse()} case1] [FAILED]--- \n");
        return 0;
    }

    XmlValueIterator iterator = root->getValueIterator();
    int nodecount = 0;
    int attrcount = 0;

    while(iterator->hasValue()) {
        XmlValue node = iterator->getValue();
        XmlAttrIterator attriterator = node->getAttrIterator();
        attrcount = 0;
        while(attriterator->hasValue()) {
            if(!attriterator->getValue()->equals(testdata[nodecount][attrcount])) {
               printf("---[XmlReader Test parse()} case1] [FAILED]--- \n");
            }
            attriterator->next();
            attrcount++;
        }

        iterator->next();
        nodecount++;
    }

    printf("---[XmlReader Test parse()} case1] [OK]--- \n");
    return 0;
}

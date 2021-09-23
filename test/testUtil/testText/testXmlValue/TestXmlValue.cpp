#include <stdio.h>
#include <unistd.h>

//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "Double.hpp"
#include "XmlReader.hpp"
#include "XmlValue.hpp"
#include "XmlDocument.hpp"

using namespace obotcha;

extern void testXmlValueFromFile();
extern void testXmlValueFromMemory();

int main() {
    testXmlValueFromFile();
    testXmlValueFromMemory();
    return 0;
}

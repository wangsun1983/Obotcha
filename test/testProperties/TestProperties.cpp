#include <stdio.h>
#include <unistd.h>

#include "Properties.hpp"



int main() {
    Properties props = createProperties();
    String tag = "tag1";
    String val = "val1";
    props->set(tag,val);

    String v2 = props->get(tag);
    printf("get v2 is %s \n",v2->toChars());

    props->save("/home/dji/mysource/Obotcha/test/testProperties/abc.txt");
}

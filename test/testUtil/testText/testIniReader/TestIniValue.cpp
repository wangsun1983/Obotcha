#include <stdio.h>
#include <unistd.h>

#include "IniReader.hpp"
#include "Log.hpp"

using namespace obotcha;

void testIniValue() {
    while(1) {
      IniReader reader = createIniReader(createFile("testData.ini"));
      HashMap<String,HashMap<String,String>> iniValues = reader->getAll();
      if(iniValues == nullptr) {
        printf("IniValue test1-------[FAILED] \n");
        break;
      }

      //root(no Section)
      HashMap<String,String> v1 = iniValues->get(S(""));
      if(v1 == nullptr || v1->size() != 1) {
        printf("IniValue test2-------[FAILED] \n");
        break;
      }

      String v2 = v1->get(S("abc1"));
      if(v2 == nullptr || !v2->equals("1")) {
        printf("IniValue test3-------[FAILED] \n");
        break;
      }

      //l1
      HashMap<String,String> l1maps = iniValues->get(S("l1"));
      if(l1maps == nullptr || l1maps->size() != 6) {
        printf("IniValue test4-------[FAILED] \n");
        break;
      }

      if(l1maps->get(S("a")) == nullptr || !l1maps->get(S("a"))->equals("1")) {
        printf("IniValue test5-------[FAILED] \n");
        break;
      }

      if(l1maps->get(S("b")) == nullptr || !l1maps->get(S("b"))->equals("2")) {
        printf("IniValue test6-------[FAILED] \n");
        break;
      }

      if(l1maps->get(S("c")) == nullptr || !l1maps->get(S("c"))->equals("3")) {
        printf("IniValue test7-------[FAILED] \n");
        break;
      }

      if(l1maps->get(S("e")) == nullptr || !l1maps->get(S("e"))->equals("4")) {
        printf("IniValue test8-------[FAILED] \n");
        break;
      }

      if(l1maps->get(S("f")) == nullptr || !l1maps->get(S("f"))->equals("5")) {
        printf("IniValue test9-------[FAILED] \n");
        break;
      }

      if(l1maps->get(S("g")) == nullptr || !l1maps->get(S("g"))->equals("6")) {
        printf("IniValue test10-------[FAILED] \n");
        break;
      }

      //l2
      HashMap<String,String> l2maps = iniValues->get(S("l2"));
      if(l2maps->get(S("a")) == nullptr || !l2maps->get(S("a"))->equals("7")) {
        printf("IniValue test10_1-------[FAILED] \n");
        break;
      }

      if(l2maps->get(S("b")) == nullptr || !l2maps->get(S("b"))->equals("8")) {
        printf("IniValue test11-------[FAILED] \n");
        break;
      }

      if(l2maps->get(S("c")) == nullptr || !l2maps->get(S("c"))->equals("9")) {
        printf("IniValue test12-------[FAILED] \n");
        break;
      }

      if(l2maps->get(S("d")) == nullptr || !l2maps->get(S("d"))->equals("10")) {
        printf("IniValue test13-------[FAILED] \n");
        break;
      }

      //l3
      HashMap<String,String> l3maps = iniValues->get(S("l3"));
      if(l3maps->get(S("a")) == nullptr || !l3maps->get(S("a"))->equals("1.1")) {
        printf("IniValue test14-------[FAILED] \n");
        break;
      }

      if(l3maps->get(S("b")) == nullptr || !l3maps->get(S("b"))->equals("2.1")) {
        printf("IniValue test15-------[FAILED] \n");
        break;
      }

      if(l3maps->get(S("c")) == nullptr || !l3maps->get(S("c"))->equals("3.1")) {
        printf("IniValue test16-------[FAILED] \n");
        break;
      }

      //l4
      HashMap<String,String> l4maps = iniValues->get(S("l4"));
      if(l4maps->get(S("a")) == nullptr || !l4maps->get(S("a"))->equals("true")) {
        printf("IniValue test17-------[FAILED] \n");
        break;
      }

      if(l4maps->get(S("b")) == nullptr || !l4maps->get(S("b"))->equals("false")) {
        printf("IniValue test18-------[FAILED] \n");
        break;
      }

      if(l4maps->get(S("c")) == nullptr || !l4maps->get(S("c"))->equals("true")) {
        printf("IniValue test19-------[FAILED] \n");
        break;
      }

      if(l4maps->get(S("d")) == nullptr || !l4maps->get(S("d"))->equals("false")) {
        printf("IniValue test20-------[FAILED] \n");
        break;
      }

      break;
    }

    while(1) {
      IniReader reader = createIniReader(createFile("twisted.ini"));
      HashMap<String,HashMap<String,String>> iniValues = reader->getAll();

      //root(no Section)
      HashMap<String,String> v1 = iniValues->get(S(""));
      if(v1 == nullptr || v1->size() != 1) {
        printf("IniValue test21-------[FAILED] \n");
        break;
      }

      String v2 = v1->get(S("abc1f"));
      if(v2 == nullptr || !v2->equals("12f")) {
        printf("IniValue test22-------[FAILED] \n");
        break;
      }

      //blanks
      HashMap<String,String> blanksMaps = iniValues->get(S("blanks"));
      if(blanksMaps == nullptr || blanksMaps->size() != 20) {
        printf("IniValue test22_1-------[FAILED] \n");
        break;
      }

      if(blanksMaps->get(S("a")) == nullptr || !blanksMaps->get(S("a"))->equals("1")) {
        printf("IniValue test23-------[FAILED] \n");
        break;
      }

      if(blanksMaps->get(S("b")) == nullptr || !blanksMaps->get(S("b"))->equals("1")) {
        printf("IniValue test24-------[FAILED] \n");
        break;
      }

      if(blanksMaps->get(S("c")) == nullptr || !blanksMaps->get(S("c"))->equals("1")) {
        printf("IniValue test25-------[FAILED] \n");
        break;
      }

      if(blanksMaps->get(S("d")) == nullptr || !blanksMaps->get(S("d"))->equals("1")) {
        printf("IniValue test26-------[FAILED] \n");
        break;
      }

      if(blanksMaps->get(S("e")) == nullptr || !blanksMaps->get(S("e"))->equals("1")) {
        printf("IniValue test27-------[FAILED] \n");
        break;
      }

      if(blanksMaps->get(S("f")) == nullptr || !blanksMaps->get(S("f"))->equals("1")) {
        printf("IniValue test28-------[FAILED] \n");
        break;
      }

      if(blanksMaps->get(S("g")) == nullptr || !blanksMaps->get(S("g"))->equals("1")) {
        printf("IniValue test29-------[FAILED] \n");
        break;
      }

      if(blanksMaps->get(S("h")) == nullptr || !blanksMaps->get(S("h"))->equals("1")) {
        printf("IniValue test30-------[FAILED] \n");
        break;
      }

      if(blanksMaps->get(S("i")) == nullptr || !blanksMaps->get(S("i"))->equals("1")) {
        printf("IniValue test31-------[FAILED] \n");
        break;
      }

      if(blanksMaps->get(S("j")) == nullptr || !blanksMaps->get(S("j"))->equals("1")) {
        printf("IniValue test32-------[FAILED] \n");
        break;
      }

      if(blanksMaps->get(S("k")) == nullptr || !blanksMaps->get(S("k"))->equals("1")) {
        printf("IniValue test33-------[FAILED] \n");
        break;
      }

      if(blanksMaps->get(S("l")) == nullptr || !blanksMaps->get(S("l"))->equals("1")) {
        printf("IniValue test34-------[FAILED] \n");
        break;
      }

      if(blanksMaps->get(S("m")) == nullptr || !blanksMaps->get(S("m"))->equals("1")) {
        printf("IniValue test35-------[FAILED] \n");
        break;
      }

      if(blanksMaps->get(S("n")) == nullptr || !blanksMaps->get(S("n"))->equals("1")) {
        printf("IniValue test36-------[FAILED] \n");
        break;
      }

      if(blanksMaps->get(S("o")) == nullptr || !blanksMaps->get(S("o"))->equals("1")) {
        printf("IniValue test37-------[FAILED] \n");
        break;
      }

      if(blanksMaps->get(S("p")) == nullptr || !blanksMaps->get(S("p"))->equals("1")) {
        printf("IniValue test38-------[FAILED] \n");
        break;
      }

      if(blanksMaps->get(S("q")) == nullptr || !blanksMaps->get(S("q"))->equals("1")) {
        printf("IniValue test39-------[FAILED] \n");
        break;
      }

      if(blanksMaps->get(S("r")) == nullptr || !blanksMaps->get(S("r"))->equals("1")) {
        printf("IniValue test40-------[FAILED] \n");
        break;
      }

      if(blanksMaps->get(S("s")) == nullptr || !blanksMaps->get(S("s"))->equals("1")) {
        printf("IniValue test41-------[FAILED] \n");
        break;
      }

      if(blanksMaps->get(S("t")) == nullptr || !blanksMaps->get(S("t"))->equals("1")) {
        printf("IniValue test42-------[FAILED] \n");
        break;
      }

      //[empty]
      HashMap<String,String> emptyMaps = iniValues->get(S("empty"));

      if(emptyMaps == nullptr || emptyMaps->size() != 14) {
        printf("IniValue test43-------[FAILED] \n");
        break;
      }

      if(emptyMaps->get(S("a")) == nullptr || emptyMaps->get(S("a"))->size() != 0) {
        printf("IniValue test44-------[FAILED] \n");
        break;
      }

      if(emptyMaps->get(S("b")) == nullptr || emptyMaps->get(S("b"))->size() != 0) {
        printf("IniValue test45-------[FAILED] \n");
        break;
      }

      if(emptyMaps->get(S("c")) == nullptr || emptyMaps->get(S("c"))->size() != 0) {
        printf("IniValue test46-------[FAILED] \n");
        break;
      }

      if(emptyMaps->get(S("d")) == nullptr || emptyMaps->get(S("d"))->size() != 0) {
        printf("IniValue test45-------[FAILED] \n");
        break;
      }

      if(emptyMaps->get(S("e")) == nullptr || emptyMaps->get(S("e"))->size() != 0) {
        printf("IniValue test46-------[FAILED] \n");
        break;
      }

      if(emptyMaps->get(S("f")) == nullptr || emptyMaps->get(S("f"))->size() != 0) {
        printf("IniValue test47-------[FAILED] \n");
        break;
      }

      if(emptyMaps->get(S("g")) == nullptr || emptyMaps->get(S("g"))->size() != 0) {
        printf("IniValue test48-------[FAILED] \n");
        break;
      }

      if(emptyMaps->get(S("h")) == nullptr || emptyMaps->get(S("h"))->size() != 0) {
        printf("IniValue test49-------[FAILED] \n");
        break;
      }

      if(emptyMaps->get(S("i")) == nullptr || emptyMaps->get(S("i"))->size() != 0) {
        printf("IniValue test50-------[FAILED] \n");
        break;
      }

      if(emptyMaps->get(S("j")) == nullptr || emptyMaps->get(S("j"))->size() != 0) {
        printf("IniValue test51-------[FAILED] \n");
        break;
      }

      if(emptyMaps->get(S("k")) == nullptr || emptyMaps->get(S("k"))->size() != 0) {
        printf("IniValue test52-------[FAILED] \n");
        break;
      }

      if(emptyMaps->get(S("l")) == nullptr || emptyMaps->get(S("l"))->size() != 0) {
        printf("IniValue test53-------[FAILED] \n");
        break;
      }

      if(emptyMaps->get(S("m")) == nullptr || emptyMaps->get(S("m"))->size() != 0) {
        printf("IniValue test54-------[FAILED] \n");
        break;
      }

      if(emptyMaps->get(S("n")) == nullptr || emptyMaps->get(S("n"))->size() != 0) {
        printf("IniValue test55-------[FAILED] \n");
        break;
      }

      //[peculiar]
      HashMap<String,String> peculiarMaps = iniValues->get(S("peculiar"));

      if(peculiarMaps == nullptr || peculiarMaps->size() != 12) {
        printf("IniValue test56-------[FAILED] \n");
        break;
      }

      if(peculiarMaps->get(S("a")) == nullptr || !peculiarMaps->get(S("a"))->equals(";")) {
        printf("IniValue test57-------[FAILED],v is %s \n",peculiarMaps->get(S("a"))->toChars());
        break;
      }

      if(peculiarMaps->get(S("b")) == nullptr || !peculiarMaps->get(S("b"))->equals("#")) {
        printf("IniValue test58-------[FAILED] \n");
        break;
      }

      if(peculiarMaps->get(S("c")) == nullptr || !peculiarMaps->get(S("c"))->equals(";")) {
        printf("IniValue test59-------[FAILED] \n");
        break;
      }

      if(peculiarMaps->get(S("d")) == nullptr || !peculiarMaps->get(S("d"))->equals("#")) {
        printf("IniValue test60-------[FAILED] \n");
        break;
      }

      if(peculiarMaps->get(S("e")) == nullptr || !peculiarMaps->get(S("e"))->equals("\\")) {
        printf("IniValue test61-------[FAILED] \n");
        break;
      }

      if(peculiarMaps->get(S("f")) == nullptr || !peculiarMaps->get(S("f"))->equals("\\")) {
        printf("IniValue test62-------[FAILED] \n");
        break;
      }

      if(peculiarMaps->get(S("g")) == nullptr || !peculiarMaps->get(S("g"))->equals("\\")) {
        printf("IniValue test63-------[FAILED] \n");
        break;
      }

      if(peculiarMaps->get(S("h")) == nullptr || !peculiarMaps->get(S("h"))->equals("\\")) {
        printf("IniValue test64-------[FAILED] \n");
        break;
      }

      if(peculiarMaps->get(S("i")) == nullptr || peculiarMaps->get(S("i"))->size() != 0) {
        printf("IniValue test65-------[FAILED] \n");
        break;
      }

      if(peculiarMaps->get(S("j")) == nullptr || peculiarMaps->get(S("j"))->size() != 0) {
        printf("IniValue test66-------[FAILED] \n");
        break;
      }

      if(peculiarMaps->get(S("k")) == nullptr || peculiarMaps->get(S("k"))->size() != 0) {
        printf("IniValue test67-------[FAILED] \n");
        break;
      }

      if(peculiarMaps->get(S("l")) == nullptr || peculiarMaps->get(S("l"))->size() != 0) {
        printf("IniValue test68-------[FAILED] \n");
        break;
      }

      //[quotes]
      HashMap<String,String> quotesMap = iniValues->get(S("quotes"));
      if(quotesMap->get(S("s1")) == nullptr || !quotesMap->get(S("s1"))->equals("'")) {
        printf("IniValue test69_1-------[FAILED],value is %s \n",quotesMap->get(S("s1"))->toChars());
        break;
      }

      if(quotesMap->get(S("s2")) == nullptr || quotesMap->get(S("s2"))->size() != 0) {
        printf("IniValue quotes test70_1-------[FAILED] \n");
        break;
      }

      if(quotesMap->get(S("s3")) == nullptr || quotesMap->get(S("s3"))->equals("'")) {
        printf("IniValue quotes test71_1-------[FAILED] \n");
        break;
      }

      if(quotesMap->get(S("s4")) == nullptr || quotesMap->get(S("s4"))->equals("'")) {
        printf("IniValue quotes test72_1-------[FAILED] \n");
        break;
      }

      if(quotesMap->get(S("d1")) == nullptr || !quotesMap->get(S("d1"))->equals("\"")) {
        printf("IniValue quotes test69-------[FAILED],value is %s \n",quotesMap->get(S("d1"))->toChars());
        break;
      }

      if(quotesMap->get(S("d2")) == nullptr || quotesMap->get(S("d2"))->size() != 0) {
        printf("IniValue quotes test70-------[FAILED] \n");
        break;
      }

      if(quotesMap->get(S("d3")) == nullptr || !quotesMap->get(S("d3"))->equals("\"\"\"")) {
        printf("IniValue quotes test71-------[FAILED],value is %s \n",quotesMap->get(S("d3"))->toChars());
        break;
      }

      if(quotesMap->get(S("d4")) == nullptr || !quotesMap->get(S("d4"))->equals("\"\"\"\"")) {
        printf("IniValue quotes test72-------[FAILED] ,value is %s \n",quotesMap->get(S("d4"))->toChars());
        break;
      }

      if(quotesMap->get(S("m1")) == nullptr || !quotesMap->get(S("m1"))->equals("\"")) {
        printf("IniValue quotes test73-------[FAILED] \n");
        break;
      }

      if(quotesMap->get(S("m2")) == nullptr || !quotesMap->get(S("m2"))->equals("\'")) {
        printf("IniValue quotes test74-------[FAILED] \n");
        break;
      }

      if(quotesMap->get(S("h1")) == nullptr || !quotesMap->get(S("h1"))->equals("hello\'world")) {
        printf("IniValue quotes test75-------[FAILED] value is %s\n",quotesMap->get(S("h1"))->toChars());
        break;
      }

      if(quotesMap->get(S("h2")) == nullptr || !quotesMap->get(S("h2"))->equals("hello")) {
        printf("IniValue quotes test76-------[FAILED] \n");
        break;
      }

      if(quotesMap->get(S("h3")) == nullptr || !quotesMap->get(S("h3"))->equals("hello")) {
        printf("IniValue quotes test77-------[FAILED] \n");
        break;
      }

      if(quotesMap->get(S("h4")) == nullptr || !quotesMap->get(S("h4"))->equals("hello\"world")) {
        printf("IniValue quotes test77-------[FAILED] \n");
        break;
      }

      if(quotesMap->get(S("h5")) == nullptr || !quotesMap->get(S("h5"))->equals("hello")) {
        printf("IniValue quotes test78-------[FAILED] \n");
        break;
      }

      if(quotesMap->get(S("h6")) == nullptr || !quotesMap->get(S("h6"))->equals("hello")) {
        printf("IniValue quotes test78-------[FAILED] \n");
        break;
      }

      //section a
      if(iniValues->get(S("a")) == nullptr || iniValues->get(S("a"))->size() != 0) {
        printf("IniValue quotes test79-------[FAILED] \n");
        break;
      }

      if(iniValues->get(S("b")) == nullptr || iniValues->get(S("b"))->size() != 0) {
        printf("IniValue quotes test80-------[FAILED] \n");
        break;
      }

      if(iniValues->get(S("c")) == nullptr || iniValues->get(S("c"))->size() != 0) {
        printf("IniValue quotes test81-------[FAILED] \n");
        break;
      }

      if(iniValues->get(S("d")) == nullptr || iniValues->get(S("d"))->size() != 0) {
        printf("IniValue quotes test82-------[FAILED] \n");
        break;
      }

      if(iniValues->get(S("begin    end")) == nullptr || iniValues->get(S("begin    end"))->size() != 0) {
        printf("IniValue quotes test83-------[FAILED] \n");
        break;
      }

      if(iniValues->get(S("open[")) == nullptr || iniValues->get(S("open["))->size() != 0) {
        printf("IniValue quotes test84-------[FAILED] \n");
        break;
      }

      //multi inputs
      HashMap<String,String> multiInputMaps = iniValues->get(S("multi"));
      if(multiInputMaps == nullptr || multiInputMaps->size() != 12) {
        printf("IniValue quotes test85-------[FAILED],multiInputMaps->size() is %d \n",multiInputMaps->size());
        break;
      }

      if(multiInputMaps->get(S("a")) == nullptr || !multiInputMaps->get(S("a"))->equals(S("beginend"))) {
        printf("IniValue quotes test86-------[FAILED] \n");
        break;
      }

      if(multiInputMaps->get(S("b")) == nullptr || !multiInputMaps->get(S("b"))->equals(S("begin end"))) {
        printf("IniValue quotes test87-------[FAILED] \n");
        break;
      }

      if(multiInputMaps->get(S("c")) == nullptr || !multiInputMaps->get(S("c"))->equals(S("begin  end"))) {
        printf("IniValue quotes test88-------[FAILED] \n");
        break;
      }

      if(multiInputMaps->get(S("d")) == nullptr || !multiInputMaps->get(S("d"))->equals(S("1234"))) {
        printf("IniValue quotes test89-------[FAILED],v is %s \n",multiInputMaps->get(S("d"))->toChars());
        break;
      }

      if(multiInputMaps->get(S("e")) == nullptr || !multiInputMaps->get(S("e"))->equals(S("1     2     3     4"))) {
        printf("IniValue quotes test90-------[FAILED],v is %s \n",multiInputMaps->get(S("e"))->toChars());
        break;
      }

      if(multiInputMaps->get(S("f")) == nullptr || !multiInputMaps->get(S("f"))->equals(S("1"))) {
        printf("IniValue quotes test91-------[FAILED] \n");
        break;
      }

      if(multiInputMaps->get(S("ww")) == nullptr || !multiInputMaps->get(S("ww"))->equals(S("1,2,3,4"))) {
        printf("IniValue quotes test92-------[FAILED],v is %s \n",multiInputMaps->get(S("ww"))->toChars());
        break;
      }

      if(multiInputMaps->get(S("hidden")) == nullptr || !multiInputMaps->get(S("hidden"))->equals(S("because of the preceding backslash multi-lining the comment"))) {
        printf("IniValue quotes test93-------[FAILED] \n");
        break;
      }

      if(multiInputMaps->get(S("visible")) == nullptr || !multiInputMaps->get(S("visible"))->equals(S("1"))) {
        printf("IniValue quotes test94-------[FAILED] \n");
        break;
      }

      if(multiInputMaps->get(S("g")) == nullptr || !multiInputMaps->get(S("g"))->equals(S("1"))) {
        printf("IniValue quotes test95-------[FAILED] \n");
        break;
      }

      if(multiInputMaps->get(S("h")) == nullptr || !multiInputMaps->get(S("h"))->equals(S("1"))) {
        printf("IniValue quotes test96-------[FAILED],value is %s \n",multiInputMaps->get(S("h"))->toChars());
        break;
      }

      if(multiInputMaps->get(S("multi line key")) == nullptr || !multiInputMaps->get(S("multi line key"))->equals(S("multi line value"))) {
        printf("IniValue quotes test96-------[FAILED],value is %s \n",multiInputMaps->get(S("multi line key"))->toChars());
        break;
      }

      break;
    }

    printf("IniValue test100-------[OK] \n");
}

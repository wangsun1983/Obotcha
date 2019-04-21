#include <stdio.h>
#include <iostream>
#include <type_traits>

#include <string.h>
#include "String.hpp"
#include "ArrayList.hpp"

using namespace obotcha;

int main() {

  printf("---[String Test Start]--- \n");
  //test String()
  while(1) {
    String str1 = createString();
    if(str1->size() != 0) {
        printf("String construct test1-------[FAIL] \n");
        break;
    }

    printf("String construct test1-------[OK] \n");
    break;
  }

  //test String(String v)
  while(1) {
    String str1 = nullptr;
    String str2 = createString(str1);
    if(str2->size() != 0) {
      printf("String construct test2-------[FAIL] \n");
      break;
    }

    if(str2 == nullptr) {
      printf("String construct test2-------[FAIL] \n");
      break;
    }

    printf("String construct test2-------[OK] \n");
    break;
  }

  //test _String(std::string v);
  while(1) {
    std::string v("abc");
    String str = createString(v);
    if(str->size() != 3) {
        printf("String construct test3-------[FAIL] \n");
        break;
    }

    if(!str->equals("abc")) {
        printf("String construct test4-------[FAIL] \n");
        break;
    }

    printf("String construct test5-------[OK] \n");
    break;
  }

  //_String(String v);
  while(1) {
    std::string v("abc");
    String str = createString(v);
    String str2 = createString(str);
    if(str2->size() != 3) {
        printf("String construct test6-------[FAIL] \n");
        break;
    }

    if(!str2->equals("abc")) {
        printf("String construct test7-------[FAIL] \n");
        break;
    }

    String str3;
    String str4 = createString(str3);
    if(str4->size() != 0) {
        printf("String construct test8-------[FAIL] \n");
    }

    printf("String construct test8-------[OK] \n");
    break;
  }

  //_String(const char *v);
  while(1) {
    String str = createString("abc");
    if(str->size() != 3) {
        printf("String construct test9-------[FAIL] \n");
        break;
    }

    if(!str->equals("abc")) {
        printf("String construct test10-------[FAIL] \n");
        break;
    }

    String str2 = createString((const char *)nullptr);
    if(str2 == nullptr) {
      printf("String construct test11-------[FAIL] \n");
      break;
    }

    printf("String construct test12-------[OK] \n");
    break;
  }

  //_String::_String(char *v,int start,int length)
  while(1) {
    String str = createString("abc",1,2);
    if(!str->equals("bc")) {
        printf("String construct test13-------[FAIL] \n");
        break;
    }

    String str2 = createString("abc",2,1);
    if(!str2->equals("c")) {
        printf("String construct test14-------[FAIL] \n");
        break;
    }

    String str3 = createString("abc",2,2);
    if(str3->size() != 0) {
        printf("String construct test15-------[FAIL] \n");
        break;
    }

    printf("String construct test16-------[OK] \n");
    break;
  }

  //_String(Integer v);
  while(1) {
    Integer v1 = createInteger(123);
    String str1 = createString(v1);
    if(!str1->equals("123")) {
      printf("String construct test17-------[FAIL] \n");
      break;
    }

    Integer v2;
    String str2 = createString(v2);
    if(str2->size() != 0) {
      printf("String construct test18-------[FAIL] \n");
      break;
    }
    printf("String construct test18-------[OK] \n");
    break;
  }

  //_String::_String(Boolean v)
  while(1) {
    Boolean v1 = createBoolean(true);
    String str1 = createString(v1);
    if(!str1->equals("true")) {
      printf("String construct test19-------[FAIL] \n");
      break;
    }

    Boolean v2 = createBoolean(false);
    String str2 = createString(v2);
    if(!str2->equals("false")) {
      printf("String construct test20-------[FAIL] \n");
      break;
    }

    Boolean v3;
    String str3 = createString(v3);
    if(str3->size() != 0) {
      printf("String construct test21-------[FAIL] \n");
      break;
    }

    printf("String construct test22-------[OK] \n");
    break;
  }

  //_String(Float v);
  while(1) {
    Float v1 = createFloat(1.2f);
    String str1 = createString(v1);
    if(!str1->equals("1.2")) {
      printf("String construct test23-------[FAIL] \n");
      break;
    }

    Float v2 = createFloat(1.3f);
    String str2 = createString(v2);
    if(!str2->equals("1.3")) {
      printf("String construct test24-------[FAIL] \n");
      break;
    }

    Float v3;
    String str3 = createString(v3);
    if(str3->size() != 0) {
      printf("String construct test25-------[FAIL] \n");
      break;
    }

    printf("String construct test26-------[OK] \n");
    break;
  }

  //    _String(Double v);
  while(1) {
    Double v1 = createDouble(1.2);
    String str1 = createString(v1);
    if(!str1->equals("1.2")) {
      printf("String construct test27-------[FAIL] \n");
      break;
    }

    Double v2 = createDouble(1.3);
    String str2 = createString(v2);
    if(!str2->equals("1.3")) {
      printf("String construct test28-------[FAIL] \n");
      break;
    }

    Double v3;
    String str3 = createString(v3);
    if(str3->size() != 0) {
      printf("String construct test29-------[FAIL] \n");
      break;
    }

    printf("String construct test30-------[OK] \n");
    break;
  }

  //_String(Long v);
  while(1) {
    Long v1 = createLong(1234567);
    String str1 = createString(v1);
    if(!str1->equals("1234567")) {
      printf("String construct test31-------[FAIL] \n");
      break;
    }

    Long v2 = createLong(345678);
    String str2 = createString(v2);
    if(!str2->equals("345678")) {
      printf("String construct test32-------[FAIL] \n");
      break;
    }

    Long v3;
    String str3 = createString(v3);
    if(str3->size() != 0) {
      printf("String construct test33-------[FAIL] \n");
      break;
    }

    printf("String construct test34-------[OK] \n");
    break;
  }

  //_String(int v);
  while(1) {
    int v = 100;
    String s = createString(v);
    if(!s->equals("100")) {
      printf("String construct test35-------[FAIL] \n");
      break;
    }

    printf("String construct test36-------[OK] \n");
    break;
  }

  //_String(bool v);
  while(1) {
    bool v = false;
    String s = createString(v);
    if(!s->equals("false")) {
      printf("String construct test37-------[FAIL] \n");
      break;
    }

    bool v2 = true;
    String s2 = createString(v2);
    if(!s2->equals("true")) {
      printf("String construct test38-------[FAIL] \n");
      break;
    }

    printf("String construct test39-------[OK] \n");
    break;
  }

  //_String(float v);
  while(1) {
    float v = 100.1f;
    String s = createString(v);
    if(!s->equals("100.1")) {
      printf("String construct test40-------[FAIL] \n");
      break;
    }

    printf("String construct test41-------[OK] \n");
    break;
  }

  //_String(double v);
  while(1) {
    double v = 100.01;
    String s = createString(v);
    if(!s->equals("100.01")) {
      printf("String construct test42-------[FAIL] \n");
      break;
    }

    printf("String construct test43-------[OK] \n");
    break;
  }

  //_String(long v);
  while(1) {
    long v = 100011;
    String s = createString(v);
    if(!s->equals("100011")) {
      printf("String construct test44-------[FAIL] \n");
      break;
    }

    printf("String construct test45-------[OK] \n");
    break;
  }

  //test replaceAll()
  while(1) {
      String str = createString("AaAbAc");
      String str2 = str->replaceAll("A","t");
      //printf("after replace is %s \n",str2->toChars());
      if(!str2->equals("tatbtc")) {
        printf("String replaceAll test1-------[FAIL] \n");
        break;
      }

      printf("String replaceAll test1-------[OK] \n");
      break;
  }

  //void split(String v,T t);
  while(1) {
    String abc1 = "1,2,3,4,5";
    ArrayList<String> list = createArrayList<String>();
    abc1->split(",",list);
    if(list->size() != 5) {
      printf("String split test1-------[FAIL] \n");
      break;
    }

    if(!list->get(0)->equals("1")
      ||!list->get(1)->equals("2")
      ||!list->get(2)->equals("3")
      ||!list->get(3)->equals("4")
      ||!list->get(4)->equals("5")) {
      printf("String split test2-------[FAIL] \n");
      break;
    }

    String abc2 = "a,b,c";
    ArrayList<String> list2 = createArrayList<String>();
    abc2->split("||",list2);
    if(list2->size() != 0) {
      printf("String split test3-------[FAIL] \n");
      break;
    }

#if 0
    //this case cannot be excuted
    String abc3;
    ArrayList<String> list3 = createArrayList<String>();
    abc3->split("||",list3);
    if(list3->size() != 0) {
      printf("String split test4-------[FAIL] \n");
      break;
    }
#endif

    printf("String split test5-------[OK] \n");
    break;

  }

  //const char * toChars();
  while(1) {
    String abc = "hello world";
    const char *p = abc->toChars();
    if(strcmp(p,"hello world") != 0) {
      printf("String toChars test1-------[FAIL] \n");
      break;
    }

    printf("String toChars test1-------[OK] \n");
    break;
  }

  //String subString(int start,int end);
  while(1) {
    String abc = "helloworld";
    String str = abc->subString(1,3);
    if(!str->equals("ell")) {
      printf("String subString test1-------[FAIL] \n");
      break;
    }

    String str2 = abc->subString(20,30);
    if(str2 != nullptr) {
      printf("String subString test2-------[FAIL] \n");
      break;
    }

    String str3 = abc->subString(1,100);
    if(str3 != nullptr) {
      printf("String subString test3-------[FAIL] \n");
      break;
    }

    String str4 = abc->subString(5,2);
    if(str4 != nullptr) {
      printf("String subString test4-------[FAIL] \n");
      break;
    }

    printf("String subString test-------[OK] \n");
    break;

  }

  //char charAt(int index);
  while(1) {
    String abc = "hello world";
    //char *p = abc->toChars();
    if(abc->charAt(1) != 'e') {
      printf("String charAt test1-------[FAIL] \n");
      break;
    }

    if(abc->charAt(90) != -1) {
      printf("String charAt test2-------[FAIL] \n");
      break;
    }

    printf("String charAt test3-------[OK] \n");
    break;
  }

  //bool contains(String val);
  while(1) {
    String abc = "abcd";
    if(!abc->contains("bc")) {
      printf("String contains test1 -------[FAIL] \n");
      break;
    }

    String abc2;
    if(abc->contains(abc2)) {
      printf("String contains test2 -------[FAIL] \n");
      break;
    }

    printf("String contains test3-------[OK] \n");
    break;
  }

  //String trim();
  while(1) {
    String abc = " a b c ";
    String abc2 = abc->trim();
    if(abc2->equals(abc)) {
      printf("String trim test1----------[FAIL] \n");
      break;
    }

    printf("String trim test1----------[OK] \n");
    break;
  }

  //String trimALl()
  while(1) {
    String abc = " a b c d ";
    String abc2 = abc->trimAll();
    if(!abc2->equals("abcd")) {
      printf("String trimAll test1----------[FAIL] \n");
      break;
    }
    printf("String trimALL test1----------[OK] \n");
    break;
  }

  //int size();
  while(1) {
    String abc = "abcd";
    if(abc->size() != 4) {
      printf("String size test1----------[FAIL] \n");
      break;
    }

    String abc2 = "";
    //printf("abc2 size is %d \n",abc2->size());
    if(abc2->size() != 0) {
      printf("String size test2----------[FAIL] \n");
      break;
    }

#if 0
//null point cannot access
    String abc3 = nullptr;
    if(abc->size() != 0) {
      printf("String size test3----------[FAIL] \n");
      break;
    }
#endif

    printf("String size test3----------[OK] \n");
    break;
  }

  //int indexOf(String v);
  while(1) {
    String abc = "abcde";
    int index = abc->indexOf("cd");
    if(index != 2) {
      printf("String indexOf test1----------[FAILED] \n");
      break;
    }

    index = abc->indexOf("q");
    if(index != -1) {
      printf("String indexOf test2----------[FAILED] \n");
      break;
    }

    index = abc->indexOf(nullptr);
    if(index != -1) {
      printf("String indexOf test3----------[FAILED] \n");
      break;
    }

    printf("String indexOf test4----------[OK] \n");
    break;
  }

  //    void append(String s);
  while(1) {
    String abc = "abcd";
    String abc2 = "efg";
    String abc3 = abc->append(abc2);

    if(!abc3->equals("abcdefg")) {
      printf("String append test1----------[FAIL] \n");
      break;
    }

#if 0
    //null point cannot test
    String abc4 = nullptr;
    String abc5 = abc4->append("123");
    if(!abc5->equals("123")) {
      printf("String append test2----------[FAIL] \n");
      break;
    }
#endif
    String abc6 = "a";
    String abc7 = abc6->append(nullptr);
    if(!abc7->equals("a")) {
      printf("String append test3----------[FAIL] \n");
      break;
    }

    printf("String append test3----------[OK] \n");
    break;
  }

  //    String append(const char *p);
  while(1) {
      String abc = "aaa";
      const char* t1 = "b";
      String r1 = abc->append(t1);
      if(!r1->equals("aaab")) {
        printf("String append test4----------[FAIL] \n");
        break;
      }

      if(!abc->equals("aaa")) {
        printf("String append test5----------[FAIL] \n");
        break;
      }

      printf("String append test5----------[OK] \n");
      break;
  }


  //Integer toInteger();
  while(1) {
    String abc ="123";
    Integer t1 = abc->toInteger();

    if(!t1->equals(123)) {
      printf("String toInteger test1----------[FAIL] \n");
      break;
    }

    String abc2 = "abc";
    Integer t2 = abc2->toInteger();
    if(t2 != nullptr) {
      printf("String toInteger test2----------[FAIL] \n");
      break;
    }

    printf("String toInteger test3----------[OK] \n");
    break;
  }

  //Boolean toBoolean();
  while(1) {
    String abc = "true";
    Boolean b1 = abc->toBoolean();
    if(!b1->toValue()) {
        printf("String toBoolean test1----------[FAIL] \n");
        break;
    }

    String abc2 = "false";
    Boolean b2 = abc2->toBoolean();
    if(b2->toValue()) {
        printf("String toBoolean test2----------[FAIL] \n");
        break;
    }

    String abc3 = "aaa";
    Boolean b3 = abc3->toBoolean();
    if(b3 != nullptr) {
      printf("String toBoolean test3----------[FAIL] \n");
      break;
    }

    printf("String toBoolean test4----------[OK] \n");
    break;
  }

  //Float toFloat();
  while(1) {
    String abc = "1.2";
    Float f = abc->toFloat();
    if(f->toValue() != 1.2f) {
       printf("String toFloat test1----------[FAIL] \n");
       break;
    }

    String abc2 = "a";
    Float f2 = abc2->toFloat();
    if(f2 != nullptr) {
      printf("String toFloat test2----------[FAIL] \n");
      break;
    }

    printf("String toFloat test3----------[OK] \n");
    break;
  }

  //    Double toDouble();
  while(1) {
    String abc = "1.2";
    Double f = abc->toDouble();
    //std::out<<"double f is "<<f<<std::endl;
    //printf("double f is %lf \n",f->toValue());
    if(f->toValue() != 1.2) {
      //TODO
       printf("String toDouble test1----------[FAIL] TODO \n");
       break;
    }

    String abc2 = "a";
    Double f2 = abc2->toDouble();
    if(f2 != nullptr) {
      printf("String toDouble test2----------[FAIL] \n");
      break;
    }

    printf("String toDouble test3----------[OK] \n");
    break;
  }

  //     int toBasicInt();
  while(1) {
    String abc = "123";
    int val = abc->toBasicInt();
    if(val != 123) {
      printf("String toBasicInt test1----------[FAIL] \n");
      break;
    }

    String abc2 = "1a b";
    int val2 = abc2->toBasicInt();
    if(val2 != 0) {
      printf("String toBasicInt test2----------[FAIL] \n");
      break;
    }

    printf("String toBasicInt test3----------[OK] \n");
    break;
  }

  //    bool toBasicBool();
  while(1) {
    String abc = "true";
    bool val = abc->toBasicBool();
    if(!val) {
      printf("String toBasicBool test1----------[FAIL] \n");
      break;
    }

    String abc2 = "True";
    bool val2 = abc2->toBasicBool();
    if(!val2) {
      printf("String toBasicBool test2----------[FAIL] \n");
      break;
    }

    String abc3 = "false";
    bool val3 = abc3->toBasicBool();
    if(val3) {
      printf("String toBasicBool test3----------[FAIL] \n");
      break;
    }

    String abc4 = "fAlse";
    bool val4 = abc4->toBasicBool();
    if(val4) {
      printf("String toBasicBool test4----------[FAIL] \n");
      break;
    }

    String abc5 = "ggg";
    bool val5 = abc5->toBasicBool();
    if(val5) {
      printf("String toBasicBool test5----------[FAIL] \n");
      break;
    }

    printf("String toBasicBool test6----------[OK] \n");
    break;
  }

  //float toBasicFloat();
  while(1) {
    String abc1 = "1.222";
    float v1 = abc1->toBasicFloat();
    if(v1 != 1.222f) {
      printf("String toBasicFloat test1----------[FAIL] \n");
      break;
    }

    String abc2 = "1";
    float v2 = abc2->toBasicFloat();
    if(v2 != 1.0f) {
      printf("String toBasicFloat test2----------[FAIL] \n");
      break;
    }

    String abc3 = "1ab";
    float v3 = abc3->toBasicFloat();
    //printf("v3 is %f \n",v3);
    if(v3 != 0.0f) {
      printf("String toBasicFloat test3----------[FAIL] \n");
      break;
    }

    printf("String toBasicFloat test4----------[OK] \n");
    break;
  }

  //double toBasicDouble();
  while(1) {
    String abc1 = "1.222";
    double v1 = abc1->toBasicDouble();
    if(v1 != 1.222) {
      printf("String toBasicDouble test1----------[FAIL] \n");
      break;
    }

    String abc2 = "1";
    double v2 = abc2->toBasicDouble();
    if(v2 != 1.0) {
      printf("String toBasicDouble test2----------[FAIL] \n");
      break;
    }

    String abc3 = "1ab";
    double v3 = abc3->toBasicDouble();
    if(v3 != 0.0) {
      printf("String toBasicDouble test3----------[FAIL] \n");
      break;
    }

    printf("String toBasicDouble test4----------[OK] \n");
    break;
  }

  //    static String valueOf(Integer v);
  while(1) {
    Integer v1 = createInteger(100);
    String a1 = st(String)::valueOf(v1);
    if(!a1->equals("100")) {
      printf("String valueOf test1----------[FAIL] \n");
      break;
    }

    Integer v2;
    String a2 = st(String)::valueOf(v2);
    if(a2 != nullptr) {
      printf("String valueOf test2----------[FAIL] \n");
      break;
    }

    printf("String valueOf test3----------[OK] \n");
    break;
  }

  //    static String valueOf(Boolean v);
  while(1) {
    Boolean v1 = createBoolean(true);
    String a1 = st(String)::valueOf(v1);
    if(!a1->equals("true")) {
      printf("String valueOf test3----------[FAIL] \n");
      break;
    }

    Boolean v2 = createBoolean(false);
    String a2 = st(String)::valueOf(v2);
    if(!a2->equals("false")) {
      printf("String valueOf test4----------[FAIL] \n");
      break;
    }

    Boolean v3;
    String a3 = st(String)::valueOf(v3);
    if(a3 != nullptr) {
      printf("String valueOf test5----------[FAIL] \n");
      break;
    }

    printf("String valueOf test6----------[OK] \n");
    break;
  }

  //static String valueOf(Double v);
  while(1) {
    Double v1 = createDouble(100);
    String a1 = st(String)::valueOf(v1);
    if(!a1->equals("100.0")) {
      //TODO
      printf("String valueOf test7----------[FAIL] TODO\n");
      break;
    }

    Double v2;
    String a2 = st(String)::valueOf(v2);
    if(a2 != nullptr) {
      printf("String valueOf test8----------[FAIL] \n");
      break;
    }

    printf("String valueOf test9----------[OK] \n");
    break;
  }


  //static String valueOf(Float v);
  while(1) {
    Float v1 = createFloat(100);
    String a1 = st(String)::valueOf(v1);
    if(!a1->equals("100")) {
      printf("String valueOf test10----------[FAIL] \n");
      break;
    }

    Float v2;
    String a2 = st(String)::valueOf(v2);
    if(a2 != nullptr) {
      printf("String valueOf test11----------[FAIL] \n");
      break;
    }

    printf("String valueOf test12----------[OK] \n");
    break;
  }

  //static String valueOf(int v);
  while(1) {
    int i = -1;
    String v1 = st(String)::valueOf(i);
    if(!v1->equals("-1")) {
      printf("String valueOf test13----------[FAIL] \n");
      break;
    }

    int i2 = 10;
    String v2 = st(String)::valueOf(i2);
    if(!v2->equals("10")) {
      printf("String valueOf test14----------[FAIL] \n");
      break;
    }

    printf("String valueOf test15----------[OK] \n");
    break;
  }

  //  static String valueOf(bool v);
  while(1) {
    bool i = false;
    String v1 = st(String)::valueOf(i);
    if(!v1->equals("false")) {
      printf("String valueOf test16----------[FAIL] \n");
      break;
    }

    bool i2 = true;
    String v2 = st(String)::valueOf(i2);
    if(!v2->equals("true")) {
      printf("String valueOf test17----------[FAIL] \n");
      break;
    }

    printf("String valueOf test18----------[OK] \n");
    break;
  }

  //  static String valueOf(double v);
  while(1) {
    double i = -1.0;
    String v1 = st(String)::valueOf(i);
    if(!v1->equals("-1")) {
      printf("String valueOf test19----------[FAIL] \n");
      break;
    }

    double i2 = 10;
    String v2 = st(String)::valueOf(i2);
    //printf("v2 is %s \n",v2->toChars());
    if(!v2->equals("10")) {
      printf("String valueOf test20----------[FAIL] \n");
      break;
    }

    printf("String valueOf test21----------[OK] \n");
    break;
  }

  //  static String valueOf(float v);
  while(1) {
    float i = -1.0f;
    String v1 = st(String)::valueOf(i);
    if(!v1->equals("-1")) {
      printf("String valueOf test22----------[FAIL] \n");
      break;
    }

    float i2 = 10;
    String v2 = st(String)::valueOf(i2);
    //printf("v2 is %s \n",v2->toChars());
    if(!v2->equals("10")) {
      printf("String valueOf test23----------[FAIL] \n");
      break;
    }

    printf("String valueOf test24----------[OK] \n");
    break;
  }

  //  static String valueOf(char *p);
  while(1) {
    const char *p1 = "abc";
    String s1 = st(String)::valueOf(p1);
    if(!s1->equals("abc")) {
      printf("String valueOf test25----------[FAIL] \n");
      break;
    }

    const char *p2 = nullptr;
    String s2 = st(String)::valueOf(p2);
    if(s2 != nullptr) {
        printf("String valueOf test26----------[FAIL] \n");
        break;
    }

    printf("String valueOf test27----------[OK] \n");
    break;
  }

  //equals(String s);
  while(1) {
    String s1 = "abc";
    String s2 = "abc";
    if(!s1->equals(s2)) {
      printf("String equals test1 ----------[FAIL] \n");
      break;
    }

    String s3 = "dd";
    if(s1->equals(s3)) {
      printf("String equals test2 ----------[FAIL] \n");
      break;
    }

    String s4;
    if(s1->equals(s4)) {
      printf("String equals test3 ----------[FAIL] \n");
      break;
    }

    printf("String equals test4 ----------[OK] \n");
    break;
  }

  //equals(String s);
  while(1) {
    String s1 = "abc";
    std::string s2 = "abc";
    if(!s1->equals(s2)) {
      printf("String equals test5 ----------[FAIL] \n");
      break;
    }

    std::string s3 = "dd";
    if(s1->equals(s3)) {
      printf("String equals test6 ----------[FAIL] \n");
      break;
    }

    std::string s4;
    if(s1->equals(s4)) {
      printf("String equals test7 ----------[FAIL] \n");
      break;
    }

    printf("String equals test8 ----------[OK] \n");
    break;
  }

  //  bool equals(const char *s);
  while(1) {
    String s1 = "abc";
    const char * s2 = "abc";
    if(!s1->equals(s2)) {
      printf("String equals test9 ----------[FAIL] \n");
      break;
    }

    const char *s3 = "dd";
    if(s1->equals(s3)) {
      printf("String equals test10 ----------[FAIL] \n");
      break;
    }

    const char *s4 = nullptr;
    if(s1->equals(s4)) {
      printf("String equals test11 ----------[FAIL] \n");
      break;
    }

    printf("String equals test12 ----------[OK] \n");
    break;
  }

  //std::string getStdString();
  //while(1) {
    //TODO
  //}

  //String toLowerCase();
  while(1) {
    String abc = "123AbC";
    String t1 = abc->toLowerCase();
    if(!t1->equals("123abc")) {
      printf("String toLowerCase test1 ----------[FAIL] \n");
      break;
    }

    String abc2 = "123";
    String t2 = abc2->toLowerCase();
    if(!t2->equals("123")) {
      printf("String toLowerCase test2 ----------[FAIL] \n");
      break;
    }

    String abc3 = "123 ABD";
    String t3 = abc3->toLowerCase();
    if(!t3->equals("123 abd")) {
      printf("String toLowerCase test3 ----------[FAIL] \n");
      break;
    }

    printf("String toLowerCase test4 ----------[OK] \n");
    break;
  }

  //    String toUpperCase();
  while(1) {
    String abc = "abc";
    String t1 = abc->toUpperCase();
    //printf("t1 is %s \n",t1->toChars());
    if(!t1->equals("ABC")) {
      printf("String toUpperCase test1 ----------[FAIL] \n");
      break;
    }

    String abc2 = "123";
    String t2 = abc2->toUpperCase();
    if(!t2->equals("123")) {
      printf("String toUpperCase test2 ----------[FAIL] \n");
      break;
    }

    String abc3 = "123 abc";
    String t3 = abc3->toUpperCase();
    if(!t3->equals("123 ABC")) {
      printf("String toUpperCase test3 ----------[FAIL] \n");
      break;
    }

    printf("String toUpperCase test4 ----------[OK] \n");
    break;
  }

  //test replaceFirst()
  while(1) {
      String str = createString("AaAbAc");
      String str2 = str->replaceFirst("A","t");
      //printf("after replace is %s \n",str2->toChars());
      if(!str2->equals("taAbAc")) {
        printf("String replaceFirst test1-------[FAIL] \n");
        break;
      }

      printf("String replaceFirst test1-------[OK] \n");
      break;
  }


  //test equalsIgnoreCase()
  while(1) {
      String str = createString("AaAbAc");
      if(!str->equalsIgnoreCase("aaabAC")) {
        printf("String equalsIgnoreCase test1-------[FAIL] \n");
        break;
      }

      String str2;
      if(str->equalsIgnoreCase(str2)) {
        printf("String equalsIgnoreCase test2-------[FAIL] \n");
        break;
      }

      printf("String equalsIgnoreCase test3-------[OK] \n");
      break;
  }

  //int indexOfIgnoreCase(String str);
  while(1) {
     String str1 = createString("aabbccdd");
     String str2 = createString("AA");
     if(str1->indexOfIgnoreCase(str2) != 0) {
       printf("String indexOfIgnoreCase test1-------[FAIL] \n");
       break;
     }

     String str3;
     if(str1->indexOfIgnoreCase(str3)) {
       printf("String indexOfIgnoreCase test2-------[FAIL] \n");
       break;
     }

     printf("String indexOfIgnoreCase test3-------[OK] \n");
     break;
  }

  //containsIgnoreCase
  while(1) {
      String str = createString("AaAbAc");
      if(!str->containsIgnoreCase("ab")) {
        printf("String containsIgnoreCase test1-------[FAIL] \n");
        break;
      }

      if(str->containsIgnoreCase("dd")) {
        printf("String containsIgnoreCase test2-------[FAIL] \n");
        break;
      }

      printf("String containsIgnoreCase test1-------[OK] \n");
      break;
  }

  //isEmpty()
  while(1) {
    String abc = "";
    if(!abc->isEmpty()) {
      printf("String isEmpty test1-------[FAIL] \n");
      break;
    }

    printf("String isEmpty test2-------[OK] \n");
    break;
  }

  //    bool endsWith(String s);
  while(1) {
    String abc = "abc";
    if(!abc->endsWith("c")) {
      printf("String endsWith test1-------[FAIL] \n");
      break;
    }

    if(abc->endsWith("f")) {
      printf("String endsWith test2-------[FAIL] \n");
      break;
    }

    if(abc->endsWith(nullptr)) {
      printf("String endsWith test3-------[FAIL] \n");
      break;
    }

    printf("String endsWith test4-------[OK] \n");
    break;
  }

  //    int lastIndexOf(String v);
  while(1) {
    String abc = "aabbccaaaa";
    int index = abc->lastIndexOf("aa");
    //printf("index is %d \n",index);
    if(index != 9) {
      printf("String lastIndexof test1-------[FAIL] \n");
      break;
    }

    int index2 = abc->lastIndexOf("zz");
    if(index2 != -1) {
      printf("String lastIndexof test2-------[FAIL] \n");
      break;
    }

    int index3 = abc->lastIndexOf(nullptr);
    if(index3 != -1) {
      printf("String lastIndexof test3-------[FAIL] \n");
      break;
    }

    printf("String lastIndexof test4-------[OK] \n");
    break;
  }

  //  bool startsWith(String v);
  while(1) {
    String abc = "aabbccaa";
    if(abc->startsWith("aa")) {
      printf("String startsWith test1-------[FAIL] \n");
      break;
    }

    if(!abc->startsWith("bb")) {
      printf("String startsWith test2-------[FAIL] \n");
      break;
    }

    if(abc->startsWith(nullptr)) {
      printf("String startsWith test3-------[FAIL] \n");
      break;
    }

    printf("String startsWith test4-------[OK] \n");
    break;
  }



}

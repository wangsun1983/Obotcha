#include <stdio.h>
#include <unistd.h>

//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "Object.hpp"
#include "StrongPointer.hpp"

using namespace obotcha;

DECLARE_CLASS(TestData1) {
public:
  _TestData1(int i) {
    value = i;
  }

  uint64_t hashcode() {
    return 1;
  }

  bool equals(const TestData1 t1) {
      return true;
  }

private:
  int value;
};

DECLARE_CLASS(TestData2) {
public:
  int j;

  bool equals(TestData2 v) {
    return j == v->j;
  }
};

DECLARE_CLASS(TestData3) {
public:
  int j;

  bool equals(TestData3 v) {
    return false;
  }
};

DECLARE_CLASS(DataTT) {
public:
  int j;
};

DECLARE_CLASS(Student) {
public:
  int j;

  bool equals(DataTT v) {
    return j == v->j;
  }
};

int testEqual() {
  while(1) {
    TestData1 d1 = createTestData1(1);
    TestData1 d2 = createTestData1(2);
    if(d1 != d2) {
      printf("Object Equal test1-------[FAIL] \n");
      break;
    }

    TestData2 d3 = createTestData2();
    d3->j = 10;
    TestData2 d4 = createTestData2();
    d4->j = 10;
    if(d3 != d4) {
      printf("Object Equal test2-------[FAIL] \n");
      break;
    }

    //inline bool operator == (const sp<U>& o) const {
    TestData3 d5 = createTestData3();
    d3->j = 10;
    TestData3 d6 = createTestData3();
    d4->j = 10;
    if(d5 == d6) {
      printf("Object Equal test3-------[FAIL] \n");
      break;
    }

    Student s1 = createStudent();
    s1->j = 100;

    DataTT s2 = createDataTT();
    s2->j = 100;

    if(s1 != s2) {
      printf("Object Equal test4-------[FAIL] \n");
      break;
    }

    //inline bool operator == (const T* o) const {
    TestData1 data1 = createTestData1(1);
    _TestData1 *data2 = new _TestData1(1);
    if(data1 != data2) {
      printf("Object Equal test5-------[FAIL] \n");
      break;
    }

    //inline bool operator == (const U* o) const {
    _DataTT *data3 = new _DataTT();
    data3->j = 100;

    Student data4 = createStudent();
    data4->j = 100;

    if(data4 != data3) {
      printf("Object Equal test6-------[FAIL] \n");
      break;
    }

    printf("Object Equal test5-------[OK] \n");
    break;
  }
}

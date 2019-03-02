#include <stdio.h>
#include <iostream>
#include <type_traits>

#include "String.hpp"
#include "ArrayList.hpp"
#include "Runnable.hpp"
#include "ExecutorService.hpp"

DECLARE_SIMPLE_CLASS(TT) {
public:
  int i;
};

DECLARE_SIMPLE_CLASS(TT2) {
public:
  int j;
};


int main() {

    //String abc = const_str("aaa");
    /*
    _TT *p = new _TT();
    char *mychar;
    try {
        _TT2 *q = dynamic_cast<_TT2 *>(mychar);
        if(q == nullptr) {
          printf("it is null \n");
        }
    } catch(std::bad_cast& bc) {

    }
    */
    String qq = "abc";
    //qq = "abc";

    printf("qq is %s \n",qq->toChars());




/*
	printf("vv is %d \n",std::is_base_of<_Q2,_Q1>::value);
	if(std::is_base_of<_Q2,_Q1>::value == 0) {
		printf("it is 0 \n");
	} else {
		printf("it is 1 \n");
	}
	*/
  //printf("value is %d \n",instanceof(q4,q3));
	//printf("value2 is %d \n",INSTANCE_OF(t,p));

	/*
	String str = createString("abc");

	//Test toChars();
	const char *v = str->toChars();
  printf("v is %s \n",v);

	//Test append
	String str2 = createString("123");
	str2->append(str);
	printf("str2 is %s\n", str2->toChars());

	//Test substring
	String str3 = str2->subString(0,2);
	printf("str3 is %s \n",str3->toChars());

	//Test trim
	String str4 = createString("    a b c d     ");
	printf("str4 is %s \n",str4->toChars());
	String str5 = str4->trim();
	printf("str5 is %s \n",str5->toChars());

	//Test split
	String str6 = createString(",i,i,j,j,aa,tt,  t");
	ArrayList<String>list = createArrayList<String>();
	str6->split<ArrayList<String>>(createString(","),list);
  int size = list->size();

  for(int i = 0;i < size;i++) {
		String str = list->get(i);
		printf("split v[%d] is %s \n",i,str->toChars());
	}

	//Test valueof
	String str8 = st(String)::valueOf(1.2f);
	printf("1.2f valueof is %s \n",str8->toChars());

	String str9 = st(String)::valueOf(15);
	printf("int valueof is %s \n",str9->toChars());

	String str10 = st(String)::valueOf(true);
	printf("bool valueof is %s \n",str10->toChars());

	//Test equals
	String str11 = createString("abc");
	String str12 = createString("abc");
	if(str11->equals(str12)) {
		printf("same string \n");
	} else {
		printf("not string \n");
	}

	//Test toInteger
	String str13 = createString("12");
	printf("toInteger is %d \n",str13->toBasicInt());

	String str14 = createString("false");
	bool result = str14->toBasicBool();
	if(!result) {
		printf("it is false \n");
	} else {
		printf("it is true \n");
	}
	*/

}

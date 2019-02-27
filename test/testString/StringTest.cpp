#include <stdio.h>

#include "String.hpp"
#include "ArrayList.hpp"

int main() {
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

}

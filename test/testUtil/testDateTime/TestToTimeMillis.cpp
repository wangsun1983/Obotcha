#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <memory.h>

//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "ByteArray.hpp"
#include "StrongPointer.hpp"
#include "ArrayIndexOutOfBoundsException.hpp"
#include "DateTime.hpp"
#include "Calendar.hpp"
#include "String.hpp"

using namespace obotcha;

void testToTimeMillis() {
	Calendar now = createCalendar();
	DateTime date = now->getDateTime();
	if(date->toTimeMillis() != now->toTimeMillis()) {
		printf("DateTime toTimeMillis test1-------[FAILED],now is %ld,date is %ld \n",now->toTimeMillis(),date->toTimeMillis());
	}

	printf("DateTime toTimeMillis test100-------[OK] \n");
}

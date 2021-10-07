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

void parseISO8601()
{
	DateTime dt = createDateTime("2005-01-08T12:30:00Z");
	if(dt->year() != 2005 ||
	   dt->month() != st(Calendar)::January ||
		 dt->dayOfMonth() != 8 ||
		 dt->hour() != 12||
		 dt->minute() != 30||
		 dt->second() != 0||
		 dt->tzd() != 0) {
			printf("DateTime parseISO8601 test1-------[FAIL]\n");
	}

	dt = createDateTime("2005-01-08T12:30:00+01:00");
	if(dt->year() != 2005 ||
	   dt->month() != st(Calendar)::January ||
		 dt->dayOfMonth() != 8 ||
		 dt->hour() != 12||
		 dt->minute() != 30||
		 dt->second() != 0||
		 dt->tzd() != 3600) {
      printf("DateTime parseISO8601 test2-------[FAIL] \n");
	}

	dt = createDateTime("2005-01-08T12:30:00-01:00");
	if(dt->year() != 2005 ||
	   dt->month() != st(Calendar)::January ||
		 dt->dayOfMonth() != 8 ||
		 dt->hour() != 12||
		 dt->minute() != 30||
		 dt->second() != 0||
		 dt->tzd() != -3600) {
      printf("DateTime parseISO8601 test3-------[FAIL] \n");
	}

	dt = createDateTime("2005-01-08");
	if(dt->year() != 2005 ||
	   dt->month() != st(Calendar)::January ||
		 dt->dayOfMonth() != 8 ||
		 dt->hour() != 0||
		 dt->minute() != 0||
		 dt->second() != 0||
		 dt->tzd() != 0) {
			printf("year is %d,month is %d,dayOfMonth is %d,hour is %d,minute is %d,second is %d,tzd is %d \n",
 			        dt->year(),dt->month(),dt->dayOfMonth(),dt->hour(),dt->minute(),dt->second(),dt->tzd());

      printf("DateTime parseISO8601 test4-------[FAIL] \n");
	}
	printf("DateTime parseISO8601 test5-------[OK] \n");
}

void parseISO8601Frac()
{
	int tzd;
	DateTime dt = createDateTime("2005-01-08T12:30:00Z");

	if(dt->year() != 2005 ||
		 dt->month() != st(Calendar)::January ||
		 dt->dayOfMonth() != 8 ||
		 dt->hour() != 12||
		 dt->minute() != 30||
		 dt->second() != 0||
		 dt->millisecond() != 0||
		 dt->microsecond() != 0||
		 dt->tzd() != 0) {
			printf("DateTime testISO8601Frac test1-------[FAIL] \n");
	}

	dt = createDateTime("2005-01-08T12:30:00+01:00");
	if(dt->year() != 2005 ||
		 dt->month() != st(Calendar)::January ||
		 dt->dayOfMonth() != 8 ||
		 dt->hour() != 12||
		 dt->minute() != 30||
		 dt->second() != 0||
		 dt->millisecond() != 0||
		 dt->microsecond() != 0||
		 dt->tzd() != 3600) {
			printf("year is %d,month is %d,dayOfMonth is %d,hour is %d,minute is %d,second is %d,tzd is %d \n",
							dt->year(),dt->month(),dt->dayOfMonth(),dt->hour(),dt->minute(),dt->second(),dt->tzd());

			printf("DateTime testISO8601Frac test2-------[FAIL] \n");
	}

	dt = createDateTime("2005-01-08T12:30:00-01:00");
	if(dt->year() != 2005 ||
		 dt->month() != st(Calendar)::January ||
		 dt->dayOfMonth() != 8 ||
		 dt->hour() != 12||
		 dt->minute() != 30||
		 dt->second() != 0||
		 dt->millisecond() != 0||
		 dt->microsecond() != 0||
		 dt->tzd() != -3600) {
			printf("year is %d,month is %d,dayOfMonth is %d,hour is %d,minute is %d,second is %d,tzd is %d \n",
							dt->year(),dt->month(),dt->dayOfMonth(),dt->hour(),dt->minute(),dt->second(),dt->tzd());

			printf("DateTime testISO8601Frac test3-------[FAIL] \n");
	}

	dt = createDateTime("2005-01-08T12:30:00");
	if(dt->year() != 2005 ||
		 dt->month() != st(Calendar)::January ||
		 dt->dayOfMonth() != 8 ||
		 dt->hour() != 12||
		 dt->minute() != 30||
		 dt->second() != 0||
		 dt->millisecond() != 0||
		 dt->microsecond() != 0||
		 dt->tzd() != 0) {
			printf("year is %d,month is %d,dayOfMonth is %d,hour is %d,minute is %d,second is %d,tzd is %d \n",
							dt->year(),dt->month(),dt->dayOfMonth(),dt->hour(),dt->minute(),dt->second(),dt->tzd());

			printf("DateTime testISO8601Frac test4-------[FAIL] \n");
	}

	dt = createDateTime("2005-01-08");
	if(dt->year() != 2005 ||
		 dt->month() != st(Calendar)::January ||
		 dt->dayOfMonth() != 8 ||
		 dt->hour() != 0||
		 dt->minute() != 0||
		 dt->second() != 0||
		 dt->millisecond() != 0||
		 dt->microsecond() != 0||
		 dt->tzd() != 0) {
			printf("year is %d,month is %d,dayOfMonth is %d,hour is %d,minute is %d,second is %d,tzd is %d \n",
							dt->year(),dt->month(),dt->dayOfMonth(),dt->hour(),dt->minute(),dt->second(),dt->tzd());

			printf("DateTime testISO8601Frac test5-------[FAIL] \n");
	}

	dt = createDateTime("2005-01-08T12:30:00.1Z");
	if(dt->year() != 2005 ||
		 dt->month() != st(Calendar)::January ||
		 dt->dayOfMonth() != 8 ||
		 dt->hour() != 12||
		 dt->minute() != 30||
		 dt->second() != 0||
		 dt->millisecond() != 100||
		 dt->microsecond() != 0||
		 dt->tzd() != 0) {
			 printf("year is %d,month is %d,dayOfMonth is %d,hour is %d,minute is %d,second is %d,millsecond is %d,microsecond is %d,tzd is %d \n",
 							dt->year(),dt->month(),dt->dayOfMonth(),dt->hour(),dt->minute(),dt->second(),dt->millisecond(),dt->microsecond(),dt->tzd());

			printf("DateTime testISO8601Frac test6-------[FAIL] \n");
	}

	dt = createDateTime("2005-01-08T12:30:00.123+01:00");
	if(dt->year() != 2005 ||
		 dt->month() != st(Calendar)::January ||
		 dt->dayOfMonth() != 8 ||
		 dt->hour() != 12||
		 dt->minute() != 30||
		 dt->second() != 0||
		 dt->millisecond() != 123||
		 dt->microsecond() != 0||
		 dt->tzd() != 3600) {
			printf("year is %d,month is %d,dayOfMonth is %d,hour is %d,minute is %d,second is %d,tzd is %d \n",
							dt->year(),dt->month(),dt->dayOfMonth(),dt->hour(),dt->minute(),dt->second(),dt->tzd());

			printf("DateTime testISO8601Frac test7-------[FAIL] \n");
	}

	dt = createDateTime("2005-01-08T12:30:00.12345-01:00");
	if(dt->year() != 2005 ||
		 dt->month() != st(Calendar)::January ||
		 dt->dayOfMonth() != 8 ||
		 dt->hour() != 12||
		 dt->minute() != 30||
		 dt->second() != 0||
		 dt->millisecond() != 123||
		 dt->microsecond() != 450||
		 dt->tzd() != -3600) {
			printf("year is %d,month is %d,dayOfMonth is %d,hour is %d,minute is %d,second is %d,tzd is %d \n",
							dt->year(),dt->month(),dt->dayOfMonth(),dt->hour(),dt->minute(),dt->second(),dt->tzd());

			printf("DateTime testISO8601Frac test8-------[FAIL] \n");
	}

	dt = createDateTime("2010-09-23T16:17:01.2817002+02:00");
	if(dt->year() != 2010 ||
		 dt->month() != st(Calendar)::September ||
		 dt->dayOfMonth() != 23 ||
		 dt->hour() != 16||
		 dt->minute() != 17||
		 dt->second() != 1||
		 dt->millisecond() != 281||
		 dt->microsecond() != 700||
		 dt->tzd() != 7200) {
			printf("year is %d,month is %d,dayOfMonth is %d,hour is %d,minute is %d,second is %d,tzd is %d \n",
							dt->year(),dt->month(),dt->dayOfMonth(),dt->hour(),dt->minute(),dt->second(),dt->tzd());

			printf("DateTime testISO8601Frac test9-------[FAIL] \n");
	}

	dt = createDateTime("2005-01-08T12:30:00");
	if(dt->year() != 2005 ||
		 dt->month() != st(Calendar)::January ||
		 dt->dayOfMonth() != 8 ||
		 dt->hour() != 12||
		 dt->minute() != 30||
		 dt->second() != 0||
		 dt->millisecond() != 0||
		 dt->microsecond() != 0||
		 dt->tzd() != 0) {
			printf("year is %d,month is %d,dayOfMonth is %d,hour is %d,minute is %d,second is %d,tzd is %d \n",
							dt->year(),dt->month(),dt->dayOfMonth(),dt->hour(),dt->minute(),dt->second(),dt->tzd());

			printf("DateTime testISO8601Frac test10-------[FAIL] \n");
	}

	dt = createDateTime("2005-01-08T12:30:00.123456");
	if(dt->year() != 2005 ||
		 dt->month() != st(Calendar)::January ||
		 dt->dayOfMonth() != 8 ||
		 dt->hour() != 12||
		 dt->minute() != 30||
		 dt->second() != 0||
		 dt->millisecond() != 123||
		 dt->microsecond() != 456||
		 dt->tzd() != 0) {
			printf("year is %d,month is %d,dayOfMonth is %d,hour is %d,minute is %d,second is %d,tzd is %d \n",
							dt->year(),dt->month(),dt->dayOfMonth(),dt->hour(),dt->minute(),dt->second(),dt->tzd());

			printf("DateTime testISO8601Frac test11-------[FAIL] \n");
	}

	dt = createDateTime("2005-01-08");
	if(dt->year() != 2005 ||
		 dt->month() != st(Calendar)::January ||
		 dt->dayOfMonth() != 8 ||
		 dt->hour() != 0||
		 dt->minute() != 0||
		 dt->second() != 0||
		 dt->millisecond() != 0||
		 dt->microsecond() != 0||
		 dt->tzd() != 0) {
			printf("year is %d,month is %d,dayOfMonth is %d,hour is %d,minute is %d,second is %d,tzd is %d \n",
							dt->year(),dt->month(),dt->dayOfMonth(),dt->hour(),dt->minute(),dt->second(),dt->tzd());

			printf("DateTime testISO8601Frac test12-------[FAIL] \n");
	}

  printf("DateTime testISO8601Frac test13-------[OK] \n");
}

void parseRFC822() {
	int tzd;
	DateTime dt = createDateTime("Sat, 8 Jan 05 12:30:00 GMT");
	if(dt->year() != 2005 ||
		 dt->month() != st(Calendar)::January ||
		 dt->dayOfMonth() != 8 ||
		 dt->hour() != 12||
		 dt->minute() != 30||
		 dt->second() != 0||
		 dt->tzd() != 0) {
			printf("year is %d,month is %d,dayOfMonth is %d,hour is %d,minute is %d,second is %d,tzd is %d \n",
							dt->year(),dt->month(),dt->dayOfMonth(),dt->hour(),dt->minute(),dt->second(),dt->tzd());

			printf("DateTime parseRFC822 test1-------[FAIL] \n");
	}

	dt = createDateTime("Sat, 8 Jan 05 12:30:00 +0100");
	if(dt->year() != 2005 ||
		 dt->month() != st(Calendar)::January ||
		 dt->dayOfMonth() != 8 ||
		 dt->hour() != 12||
		 dt->minute() != 30||
		 dt->second() != 0||
		 dt->tzd() != 3600) {
			printf("year is %d,month is %d,dayOfMonth is %d,hour is %d,minute is %d,second is %d,tzd is %d \n",
							dt->year(),dt->month(),dt->dayOfMonth(),dt->hour(),dt->minute(),dt->second(),dt->tzd());

			printf("DateTime parseRFC822 test2-------[FAIL] \n");
	}

	dt = createDateTime("Sat, 8 Jan 05 12:30:00 -0100");
	if(dt->year() != 2005 ||
		 dt->month() != st(Calendar)::January ||
		 dt->dayOfMonth() != 8 ||
		 dt->hour() != 12||
		 dt->minute() != 30||
		 dt->second() != 0||
		 dt->tzd() != -3600) {
			printf("year is %d,month is %d,dayOfMonth is %d,hour is %d,minute is %d,second is %d,tzd is %d \n",
							dt->year(),dt->month(),dt->dayOfMonth(),dt->hour(),dt->minute(),dt->second(),dt->tzd());

			printf("DateTime parseRFC822 test3-------[FAIL] \n");
	}

	dt = createDateTime("Tue, 18 Jan 05 12:30:00 CDT");
	if(dt->year() != 2005 ||
		 dt->month() != st(Calendar)::January ||
		 dt->dayOfMonth() != 18 ||
		 dt->hour() != 12||
		 dt->minute() != 30||
		 dt->second() != 0||
		 dt->tzd() != -18000) {
			printf("year is %d,month is %d,dayOfMonth is %d,hour is %d,minute is %d,second is %d,tzd is %d \n",
							dt->year(),dt->month(),dt->dayOfMonth(),dt->hour(),dt->minute(),dt->second(),dt->tzd());

			printf("DateTime parseRFC822 test4-------[FAIL] \n");
	}

	dt = createDateTime("Wed, 12 Sep 73 02:01:12 CST");
	if(dt->year() != 1973 ||
		 dt->month() != st(Calendar)::September ||
		 dt->dayOfMonth() != 12 ||
		 dt->hour() != 2||
		 dt->minute() != 1||
		 dt->second() != 12||
		 dt->tzd() != -21600) {
			printf("year is %d,month is %d,dayOfMonth is %d,hour is %d,minute is %d,second is %d,tzd is %d \n",
							dt->year(),dt->month(),dt->dayOfMonth(),dt->hour(),dt->minute(),dt->second(),dt->tzd());

			printf("DateTime parseRFC822 test4-------[FAIL] \n");
	}

	dt = createDateTime("12 Sep 73 02:01:12 EST");
	if(dt->year() != 1973 ||
		 dt->month() != st(Calendar)::September ||
		 dt->dayOfMonth() != 12 ||
		 dt->hour() != 2||
		 dt->minute() != 1||
		 dt->second() != 12||
		 dt->tzd() != -18000) {
			printf("year is %d,month is %d,dayOfMonth is %d,hour is %d,minute is %d,second is %d,tzd is %d \n",
							dt->year(),dt->month(),dt->dayOfMonth(),dt->hour(),dt->minute(),dt->second(),dt->tzd());

			printf("DateTime parseRFC822 test5-------[FAIL] \n");
	}
	printf("DateTime parseRFC822 test6-------[OK] \n");
}

void parseRFC1123()
{
	DateTime dt = createDateTime("Sat, 8 Jan 2005 12:30:00 GMT");
	if(dt->year() != 2005 ||
		 dt->month() != st(Calendar)::January ||
		 dt->dayOfMonth() != 8 ||
		 dt->hour() != 12||
		 dt->minute() != 30||
		 dt->second() != 0||
		 dt->tzd() != 0) {
			printf("year is %d,month is %d,dayOfMonth is %d,hour is %d,minute is %d,second is %d,tzd is %d \n",
							dt->year(),dt->month(),dt->dayOfMonth(),dt->hour(),dt->minute(),dt->second(),dt->tzd());

			printf("DateTime RFC1123 test1-------[FAIL] \n");
	}


	dt = createDateTime("Sat, 8 Jan 2005 12:30:00 +0100");
	if(dt->year() != 2005 ||
		 dt->month() != st(Calendar)::January ||
		 dt->dayOfMonth() != 8 ||
		 dt->hour() != 12||
		 dt->minute() != 30||
		 dt->second() != 0||
		 dt->tzd() != 3600) {
			printf("year is %d,month is %d,dayOfMonth is %d,hour is %d,minute is %d,second is %d,tzd is %d \n",
							dt->year(),dt->month(),dt->dayOfMonth(),dt->hour(),dt->minute(),dt->second(),dt->tzd());

			printf("DateTime RFC1123 test2-------[FAIL] \n");
	}

	dt = createDateTime("Sat, 8 Jan 2005 12:30:00 -0100");
	if(dt->year() != 2005 ||
		 dt->month() != st(Calendar)::January ||
		 dt->dayOfMonth() != 8 ||
		 dt->hour() != 12||
		 dt->minute() != 30||
		 dt->second() != 0||
		 dt->tzd() != -3600) {
			printf("year is %d,month is %d,dayOfMonth is %d,hour is %d,minute is %d,second is %d,tzd is %d \n",
							dt->year(),dt->month(),dt->dayOfMonth(),dt->hour(),dt->minute(),dt->second(),dt->tzd());

			printf("DateTime RFC1123 test3-------[FAIL] \n");
	}

	dt = createDateTime("Tue, 18 Jan 2005 12:30:00 CDT");
	if(dt->year() != 2005 ||
		 dt->month() != st(Calendar)::January ||
		 dt->dayOfMonth() != 18 ||
		 dt->hour() != 12||
		 dt->minute() != 30||
		 dt->second() != 0||
		 dt->tzd() != -18000) {
			printf("year is %d,month is %d,dayOfMonth is %d,hour is %d,minute is %d,second is %d,tzd is %d \n",
							dt->year(),dt->month(),dt->dayOfMonth(),dt->hour(),dt->minute(),dt->second(),dt->tzd());

			printf("DateTime RFC1123 test4-------[FAIL] \n");
	}

	dt = createDateTime("Wed, 12 Sep 1973 02:01:12 CST");
	if(dt->year() != 1973 ||
		 dt->month() != st(Calendar)::September ||
		 dt->dayOfMonth() != 12 ||
		 dt->hour() != 2||
		 dt->minute() != 1||
		 dt->second() != 12||
		 dt->tzd() != -21600) {
			printf("year is %d,month is %d,dayOfMonth is %d,hour is %d,minute is %d,second is %d,tzd is %d \n",
							dt->year(),dt->month(),dt->dayOfMonth(),dt->hour(),dt->minute(),dt->second(),dt->tzd());

			printf("DateTime RFC1123 test5-------[FAIL] \n");
	}

	dt = createDateTime("12 Sep 1973 02:01:12 EST");
	if(dt->year() != 1973 ||
		 dt->month() != st(Calendar)::September ||
		 dt->dayOfMonth() != 12 ||
		 dt->hour() != 2||
		 dt->minute() != 1||
		 dt->second() != 12||
		 dt->tzd() != -18000) {
			printf("year is %d,month is %d,dayOfMonth is %d,hour is %d,minute is %d,second is %d,tzd is %d \n",
							dt->year(),dt->month(),dt->dayOfMonth(),dt->hour(),dt->minute(),dt->second(),dt->tzd());

			printf("DateTime RFC1123 test6-------[FAIL] \n");
	}
  printf("DateTime RFC1123 test7-------[OK] \n");
}

void parseHTTP()
{
	DateTime dt = createDateTime("Sat, 08 Jan 2005 12:30:00 GMT");
	if(dt->year() != 2005 ||
		 dt->month() != st(Calendar)::January ||
		 dt->dayOfMonth() != 8 ||
		 dt->hour() != 12||
		 dt->minute() != 30||
		 dt->second() != 0) {
			printf("year is %d,month is %d,dayOfMonth is %d,hour is %d,minute is %d,second is %d,tzd is %d \n",
							dt->year(),dt->month(),dt->dayOfMonth(),dt->hour(),dt->minute(),dt->second(),dt->tzd());

			printf("DateTime parseHttp test1-------[FAIL] \n");
	}

	dt = createDateTime("Sat, 08 Jan 2005 12:30:00 +0100");
	if(dt->year() != 2005 ||
		 dt->month() != st(Calendar)::January ||
		 dt->dayOfMonth() != 8 ||
		 dt->hour() != 12||
		 dt->minute() != 30||
		 dt->second() != 0 ||
	   dt->tzd() != 3600) {
			printf("year is %d,month is %d,dayOfMonth is %d,hour is %d,minute is %d,second is %d,tzd is %d \n",
							dt->year(),dt->month(),dt->dayOfMonth(),dt->hour(),dt->minute(),dt->second(),dt->tzd());

			printf("DateTime parseHttp test2-------[FAIL] \n");
	}

	dt = createDateTime("Sat, 08 Jan 2005 12:30:00 -0100");
	if(dt->year() != 2005 ||
		 dt->month() != st(Calendar)::January ||
		 dt->dayOfMonth() != 8 ||
		 dt->hour() != 12||
		 dt->minute() != 30||
		 dt->second() != 0 ||
		 dt->tzd() != -3600) {
			printf("year is %d,month is %d,dayOfMonth is %d,hour is %d,minute is %d,second is %d,tzd is %d \n",
							dt->year(),dt->month(),dt->dayOfMonth(),dt->hour(),dt->minute(),dt->second(),dt->tzd());
			printf("DateTime parseHttp test3-------[FAIL] \n");
	}
  printf("DateTime parseHttp test4-------[OK] \n");
}

void parseRFC850()
{
	DateTime dt = createDateTime("Saturday, 8-Jan-05 12:30:00 GMT");
	if(dt->year() != 2005 ||
		 dt->month() != st(Calendar)::January ||
		 dt->dayOfMonth() != 8 ||
		 dt->hour() != 12||
		 dt->minute() != 30||
		 dt->second() != 0 ||
		 dt->tzd() != 0) {
			printf("year is %d,month is %d,dayOfMonth is %d,hour is %d,minute is %d,second is %d,tzd is %d \n",
							dt->year(),dt->month(),dt->dayOfMonth(),dt->hour(),dt->minute(),dt->second(),dt->tzd());
			printf("DateTime parseRFC850 test1-------[FAIL] \n");
	}

	dt = createDateTime("Saturday, 8-Jan-05 12:30:00 +0100");
	if(dt->year() != 2005 ||
		 dt->month() != st(Calendar)::January ||
		 dt->dayOfMonth() != 8 ||
		 dt->hour() != 12||
		 dt->minute() != 30||
		 dt->second() != 0 ||
		 dt->tzd() != 3600) {
			printf("year is %d,month is %d,dayOfMonth is %d,hour is %d,minute is %d,second is %d,tzd is %d \n",
							dt->year(),dt->month(),dt->dayOfMonth(),dt->hour(),dt->minute(),dt->second(),dt->tzd());
			printf("DateTime parseRFC850 test2-------[FAIL] \n");
	}

	dt = createDateTime("Saturday, 8-Jan-05 12:30:00 -0100");
	if(dt->year() != 2005 ||
		 dt->month() != st(Calendar)::January ||
		 dt->dayOfMonth() != 8 ||
		 dt->hour() != 12||
		 dt->minute() != 30||
		 dt->second() != 0 ||
		 dt->tzd() != -3600) {
			printf("year is %d,month is %d,dayOfMonth is %d,hour is %d,minute is %d,second is %d,tzd is %d \n",
							dt->year(),dt->month(),dt->dayOfMonth(),dt->hour(),dt->minute(),dt->second(),dt->tzd());
			printf("DateTime parseRFC850 test3-------[FAIL] \n");
	}

	dt = createDateTime("Wed, 12-Sep-73 02:01:12 CST");
	if(dt->year() != 1973 ||
		 dt->month() != st(Calendar)::September ||
		 dt->dayOfMonth() != 12 ||
		 dt->hour() != 2||
		 dt->minute() != 1||
		 dt->second() != 12 ||
		 dt->tzd() != -21600) {
			printf("year is %d,month is %d,dayOfMonth is %d,hour is %d,minute is %d,second is %d,tzd is %d \n",
							dt->year(),dt->month(),dt->dayOfMonth(),dt->hour(),dt->minute(),dt->second(),dt->tzd());
			printf("DateTime parseRFC850 test4-------[FAIL] \n");
	}
	printf("DateTime parseRFC850 test5-------[OK] \n");
}

void parseRFC1036() {
	DateTime dt = createDateTime("Saturday, 8 Jan 05 12:30:00 GMT");
	if(dt->year() != 2005 ||
		 dt->month() != st(Calendar)::January ||
		 dt->dayOfMonth() != 8 ||
		 dt->hour() != 12||
		 dt->minute() != 30||
		 dt->second() != 0 ||
		 dt->tzd() != 0) {
			printf("year is %d,month is %d,dayOfMonth is %d,hour is %d,minute is %d,second is %d,tzd is %d \n",
							dt->year(),dt->month(),dt->dayOfMonth(),dt->hour(),dt->minute(),dt->second(),dt->tzd());
			printf("DateTime parseRFC1036 test1-------[FAIL] \n");
	}

	dt = createDateTime("Saturday, 8 Jan 05 12:30:00 +0100");
	if(dt->year() != 2005 ||
		 dt->month() != st(Calendar)::January ||
		 dt->dayOfMonth() != 8 ||
		 dt->hour() != 12||
		 dt->minute() != 30||
		 dt->second() != 0 ||
		 dt->tzd() != 3600) {
			printf("year is %d,month is %d,dayOfMonth is %d,hour is %d,minute is %d,second is %d,tzd is %d \n",
							dt->year(),dt->month(),dt->dayOfMonth(),dt->hour(),dt->minute(),dt->second(),dt->tzd());
			printf("DateTime parseRFC1036 test2-------[FAIL] \n");
	}

	dt = createDateTime("Saturday, 8 Jan 05 12:30:00 -0100");
	if(dt->year() != 2005 ||
		 dt->month() != st(Calendar)::January ||
		 dt->dayOfMonth() != 8 ||
		 dt->hour() != 12||
		 dt->minute() != 30||
		 dt->second() != 0 ||
		 dt->tzd() != -3600) {
			printf("year is %d,month is %d,dayOfMonth is %d,hour is %d,minute is %d,second is %d,tzd is %d \n",
							dt->year(),dt->month(),dt->dayOfMonth(),dt->hour(),dt->minute(),dt->second(),dt->tzd());
			printf("DateTime parseRFC1036 test3-------[FAIL] \n");
	}
	printf("DateTime parseRFC1036 test4-------[OK] \n");
}

void parseASCTIME() {
	DateTime dt = createDateTime("Sat Jan  8 12:30:00 2005");
	if(dt->year() != 2005 ||
		 dt->month() != st(Calendar)::January ||
		 dt->dayOfMonth() != 8 ||
		 dt->hour() != 12||
		 dt->minute() != 30||
		 dt->second() != 0 ||
		 dt->tzd() != 0) {
			printf("year is %d,month is %d,dayOfMonth is %d,hour is %d,minute is %d,second is %d,tzd is %d \n",
							dt->year(),dt->month(),dt->dayOfMonth(),dt->hour(),dt->minute(),dt->second(),dt->tzd());
			printf("DateTime parseASCTIME test1-------[FAIL] \n");
	}
	printf("DateTime parseASCTIME test1-------[OK] \n");
}

void parseSORTABLE() {
	DateTime dt = createDateTime("2005-01-08 12:30:00");
	if(dt->year() != 2005 ||
		 dt->month() != st(Calendar)::January ||
		 dt->dayOfMonth() != 8 ||
		 dt->hour() != 12||
		 dt->minute() != 30||
		 dt->second() != 0 ||
		 dt->tzd() != 0) {
			printf("year is %d,month is %d,dayOfMonth is %d,hour is %d,minute is %d,second is %d,tzd is %d \n",
							dt->year(),dt->month(),dt->dayOfMonth(),dt->hour(),dt->minute(),dt->second(),dt->tzd());
			printf("DateTime parseSORTABLE test1-------[FAIL] \n");
	}

	dt = createDateTime("2005-01-08");
	if(dt->year() != 2005 ||
		 dt->month() != st(Calendar)::January ||
		 dt->dayOfMonth() != 8 ||
		 dt->hour() != 0||
		 dt->minute() != 0||
		 dt->second() != 0 ||
		 dt->tzd() != 0) {
			printf("year is %d,month is %d,dayOfMonth is %d,hour is %d,minute is %d,second is %d,tzd is %d \n",
							dt->year(),dt->month(),dt->dayOfMonth(),dt->hour(),dt->minute(),dt->second(),dt->tzd());
			printf("DateTime parseSORTABLE test2-------[FAIL] \n");
	}
	printf("DateTime parseSORTABLE test3-------[OK] \n");
}

void parseCustom() {
	DateTime dt = createDateTime(createString("%d-%b-%Y"),createString("18-Jan-2005"));
	if(dt->year() != 2005 ||
		 dt->month() != st(Calendar)::January ||
		 dt->dayOfMonth() != 18 ||
		 dt->hour() != 0||
		 dt->minute() != 0||
		 dt->second() != 0 ||
		 dt->tzd() != 0) {
			printf("year is %d,month is %d,dayOfMonth is %d,hour is %d,minute is %d,second is %d,tzd is %d \n",
							dt->year(),dt->month(),dt->dayOfMonth(),dt->hour(),dt->minute(),dt->second(),dt->tzd());
			printf("DateTime parseCustom test1-------[FAIL] \n");
	}

	dt = createDateTime(createString("%m/%d/%y"),createString("01/18/05"));
	if(dt->year() != 2005 ||
		 dt->month() != st(Calendar)::January ||
		 dt->dayOfMonth() != 18 ||
		 dt->hour() != 0||
		 dt->minute() != 0||
		 dt->second() != 0 ||
		 dt->tzd() != 0) {
			printf("year is %d,month is %d,dayOfMonth is %d,hour is %d,minute is %d,second is %d,tzd is %d \n",
							dt->year(),dt->month(),dt->dayOfMonth(),dt->hour(),dt->minute(),dt->second(),dt->tzd());
			printf("DateTime parseCustom test2-------[FAIL] \n");
	}

	dt = createDateTime(createString("%h:%M %a"),createString("12:30 am"));
	if(dt->hour() != 0||
		 dt->minute() != 30||
		 dt->second() != 0 ) {
			printf("year is %d,month is %d,dayOfMonth is %d,hour is %d,minute is %d,second is %d,tzd is %d \n",
							dt->year(),dt->month(),dt->dayOfMonth(),dt->hour(),dt->minute(),dt->second(),dt->tzd());
			printf("DateTime parseCustom test3-------[FAIL] \n");
	}

	dt = createDateTime(createString("%h:%M %a"),createString("12:30 PM"));
	if(dt->hour() != 12||
		 dt->minute() != 30||
		 dt->second() != 0 ) {
			printf("year is %d,month is %d,dayOfMonth is %d,hour is %d,minute is %d,second is %d,tzd is %d \n",
							dt->year(),dt->month(),dt->dayOfMonth(),dt->hour(),dt->minute(),dt->second(),dt->tzd());
			printf("DateTime parseCustom test4-------[FAIL] \n");
	}

	printf("DateTime parseCustom test5-------[OK] \n");
}

void parsetest() {
	parseISO8601();
	parseISO8601Frac();
	parseRFC822();
	parseRFC1123();
	parseHTTP();
	parseRFC850();
	parseRFC1036();
	parseASCTIME();
	parseSORTABLE();
	parseCustom();
}

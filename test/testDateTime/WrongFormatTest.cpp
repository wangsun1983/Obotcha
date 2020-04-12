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
#include "InitializeException.hpp"

using namespace obotcha;

int wrongformat() {
	  try {
		    DateTime t = createDateTime(st(DateTime)::FormatISO8601Frac,"2005-01-08T12.30:00Z");
				printf("DateTime wrongformat test1-------[FAIL] \n");
		} catch(InitializeException e) {}

		try {
		    DateTime t = createDateTime(st(DateTime)::FormatISO8601Frac,"2005-01-8T12:30:00+01:00");
				printf("DateTime wrongformat test2-------[FAIL] \n");
		} catch(InitializeException e) {}

		try {
		    DateTime t = createDateTime(st(DateTime)::FormatISO8601Frac,"2005-01-0812:30:00-01:00");
				printf("DateTime wrongformat test3-------[FAIL] \n");
		} catch(InitializeException e) {}

		try {
		    DateTime t = createDateTime(st(DateTime)::FormatISO8601Frac,"2005-01-08T12:30:0");
				printf("DateTime wrongformat test4-------[FAIL] \n");
		} catch(InitializeException e) {}

		try {
				DateTime t = createDateTime(st(DateTime)::FormatISO8601Frac,"2005-01-8");
				printf("DateTime wrongformat test5-------[FAIL] \n");
		} catch(InitializeException e) {}

		try {
				DateTime t = createDateTime(st(DateTime)::FormatISO8601Frac,"2005-1-08T12:30:00Z");
				printf("DateTime wrongformat test6-------[FAIL] \n");
		} catch(InitializeException e) {}

		try {
				DateTime t = createDateTime(st(DateTime)::FormatISO8601Frac,"2005-01-08Z12:30:00+01:00");
				printf("DateTime wrongformat test7-------[FAIL] \n");
		} catch(InitializeException e) {}

		try {
				DateTime t = createDateTime(st(DateTime)::FormatISO8601Frac,"2005-01-08T12:30:00-01.00");
				printf("DateTime wrongformat test8-------[FAIL] \n");
		} catch(InitializeException e) {}

		try {
				DateTime t = createDateTime(st(DateTime)::FormatISO8601Frac,"2005-01-08T12;30:00");
				printf("DateTime wrongformat test9------[FAIL] \n");
		} catch(InitializeException e) {}

		try {
				DateTime t = createDateTime(st(DateTime)::FormatISO8601Frac,"2005-01+08");
				printf("DateTime wrongformat test10-------[FAIL] \n");
		} catch(InitializeException e) {}

		try {
				DateTime t = createDateTime(st(DateTime)::FormatISO8601Frac,"2005-01-08T12:30:00.123*01:00");
				printf("DateTime wrongformat test11-------[FAIL] \n");
		} catch(InitializeException e) {}

		try {
				DateTime t = createDateTime(st(DateTime)::FormatISO8601Frac,"201009-23T16:17:01.2817002+02:00");
				printf("DateTime wrongformat test12-------[FAIL] \n");
		} catch(InitializeException e) {}

		try {
				DateTime t = createDateTime(st(DateTime)::FormatISO8601Frac,"005-01-08T12:30:00.123456");
				printf("DateTime wrongformat test13-------[FAIL] \n");
		} catch(InitializeException e) {}

		try {
				DateTime t = createDateTime(st(DateTime)::FormatISO8601Frac,"2005-01-0");
				printf("DateTime wrongformat test14-------[FAIL] \n");
		} catch(InitializeException e) {}

		try {
				DateTime t = createDateTime(st(DateTime)::FormatISO8601Frac,"jnghjgnbcfjb");
				printf("DateTime wrongformat test15-------[FAIL] \n");
		} catch(InitializeException e) {}

		try {
				DateTime t = createDateTime(st(DateTime)::FormatRFC822,"at, 8 Jan 05 12:30:00 GMT");
				printf("DateTime wrongformat test16-------[FAIL] \n");
		} catch(InitializeException e) {}

		try {
				DateTime t = createDateTime(st(DateTime)::FormatRFC822,"Sat, x Jan 05 12:30:00 +0100");
				printf("DateTime wrongformat test17-------[FAIL] \n");
		} catch(InitializeException e) {}

		try {
				DateTime t = createDateTime(st(DateTime)::FormatRFC822,"Sat, 8 Jan 05 12:30:00 *0100");
				printf("DateTime wrongformat test18-------[FAIL] \n");
		} catch(InitializeException e) {}

		try {
				DateTime t = createDateTime(st(DateTime)::FormatRFC822,"Tue, 18 Jan 05 12:30:00 abc");
				printf("DateTime wrongformat test19-------[FAIL] \n");
		} catch(InitializeException e) {}

		try {
				DateTime t = createDateTime(st(DateTime)::FormatRFC822,"Wed, 12 Sep 73 02:01:2 CST");
				printf("DateTime wrongformat test20-------[FAIL] \n");
		} catch(InitializeException e) {}

		try {
				DateTime t = createDateTime(st(DateTime)::FormatRFC822,"12 Sep 73 02.01:12 EST");
				printf("DateTime wrongformat test21-------[FAIL] \n");
		} catch(InitializeException e) {}

		try {
				DateTime t = createDateTime(st(DateTime)::FormatRFC1123,"Sat, 8 Jan 2005 12:30:00 GPX");
				printf("DateTime wrongformat test22-------[FAIL] \n");
		} catch(InitializeException e) {}

		try {
				DateTime t = createDateTime(st(DateTime)::FormatRFC1123,"Sat, 8 Jan 2005 xy:30:00 +0100");
				printf("DateTime wrongformat test23-------[FAIL] \n");
		} catch(InitializeException e) {}

		try {
				DateTime t = createDateTime(st(DateTime)::FormatRFC1123,"Sat, 8 Jan 205 12:30:00 -0100");
				printf("DateTime wrongformat test24-------[FAIL] \n");
		} catch(InitializeException e) {}

		try {
				DateTime t = createDateTime(st(DateTime)::FormatRFC1123,"Sat, 8 Jan 205 12:30:00 -0100");
				printf("DateTime wrongformat test25-------[FAIL] \n");
		} catch(InitializeException e) {}

		try {
				DateTime t = createDateTime(st(DateTime)::FormatHTTP,"Sat, 08 Jn 2005 12:30:00 GMT");
				printf("DateTime wrongformat test26-------[FAIL] \n");
		} catch(InitializeException e) {}

		try {
				DateTime t = createDateTime(st(DateTime)::FormatHTTP,"Sat 08 Jan 2005 12:30:00 -0100");
				printf("DateTime wrongformat test27-------[FAIL] \n");
		} catch(InitializeException e) {}

		try {
				DateTime t = createDateTime(st(DateTime)::FormatRFC850,"Saturday, 8-Jan 05 12:30:00 GMT");
				printf("DateTime wrongformat test28-------[FAIL] \n");
		} catch(InitializeException e) {}

		try {
				DateTime t = createDateTime(st(DateTime)::FormatRFC850,"Saturday, 8+Jan-05 12:30:00 +0100");
				printf("DateTime wrongformat test29-------[FAIL] \n");
		} catch(InitializeException e) {}

		try {
				DateTime t = createDateTime(st(DateTime)::FormatRFC850,"Saturday 8-Jan-05 12:30:00 -0100");
				printf("DateTime wrongformat test30-------[FAIL] \n");
		} catch(InitializeException e) {}

		try {
				DateTime t = createDateTime(st(DateTime)::FormatRFC850,"Wed, 12-pep-73 02:01:12 CST");
				printf("DateTime wrongformat test31-------[FAIL] \n");
		} catch(InitializeException e) {}

		try {
				DateTime t = createDateTime(st(DateTime)::FormatRFC1036,"Saturday, 8 Jan 0512:30:00 GMT");
				printf("DateTime wrongformat test32-------[FAIL] \n");
		} catch(InitializeException e) {}

		try {
				DateTime t = createDateTime(st(DateTime)::FormatRFC1036,"Saturday, 8 Jan 051 12:30:00 +0100");
				printf("DateTime wrongformat test33-------[FAIL] \n");
		} catch(InitializeException e) {}

		try {
				DateTime t = createDateTime(st(DateTime)::FormatRFC1036,"Saturday, 8 Jan 05 12:30:00 -0100x");
				printf("DateTime wrongformat test34-------[FAIL] \n");
		} catch(InitializeException e) {}

		try {
				DateTime t = createDateTime(st(DateTime)::FormatASCTIME,"Bat Jan  8 12:30:00 2005");
				printf("DateTime wrongformat test35-------[FAIL] \n");
		} catch(InitializeException e) {}

		try {
				DateTime t = createDateTime(st(DateTime)::FormatSORTABLE,"2005-01-08 12:30;00");
				printf("DateTime wrongformat test36-------[FAIL] \n");
		} catch(InitializeException e) {}

		try {
				DateTime t = createDateTime(st(DateTime)::FormatSORTABLE,"2005+01-08");
				printf("DateTime wrongformat test36-------[FAIL] \n");
		} catch(InitializeException e) {}

		try {
				DateTime t = createDateTime(createString(""),createString("12:30 PM"));
				printf("DateTime wrongformat test37-------[FAIL] \n");
		} catch(InitializeException e) {}

    printf("DateTime wrongformat test10-------[OK] \n");
}

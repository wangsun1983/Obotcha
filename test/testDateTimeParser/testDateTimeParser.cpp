#include <stdio.h>
#include <unistd.h>

//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "Aes.hpp"
#include "String.hpp"
#include "ByteArray.hpp"
#include "NumberFormatter.hpp"
#include "Calendar.hpp"
#include "DateTimeFormatter.hpp"
#include "DateTimeParser.hpp"

using namespace obotcha;

int main() {
    //static String format(const int value);
    printf("---[DateTimeParser Test Start]--- \n");
	String str = createString("Wed, 14 Aug 2019 06:51:26 GMT");
    DateTime date = st(DateTimeParser)::parse(DateTimeFormatHTTP,str);
    printf("date:year is %d,month is %d,day is %d,hour is %d,minute is %d,second is %d \n",
        date->year(),
        date->month(),
        date->dayOfMonth(),
        date->hour(),
        date->minute(),
        date->second());

    String str2 = createString("Sunday, 06-Nov-94 08:49:37 GMT");
    date = st(DateTimeParser)::parse(DateTimeFormatRFC1036,str2);
    printf("date2:year is %d,month is %d,day is %d,hour is %d,minute is %d,second is %d \n",
        date->year(),
        date->month(),
        date->dayOfMonth(),
        date->hour(),
        date->minute(),
        date->second());

    String str3 = createString("Sun Nov  6 08:49:37 1994");
    date = st(DateTimeParser)::parse(DateTimeFormatASCTIME,str3);
    printf("date3:year is %d,month is %d,day is %d,hour is %d,minute is %d,second is %d \n",
        date->year(),
        date->month(),
        date->dayOfMonth(),
        date->hour(),
        date->minute(),
        date->second());


    String str4 = createString("Sun Nov  6 08:49:37 1994");
    date = st(DateTimeParser)::parse(str4);
    printf("date4:year is %d,month is %d,day is %d,hour is %d,minute is %d,second is %d \n",
        date->year(),
        date->month(),
        date->dayOfMonth(),
        date->hour(),
        date->minute(),
        date->second());

   
    //String format(const int value, const int width);
	//String format0(const int value, const int width);

}

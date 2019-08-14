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

using namespace obotcha;

int main() {
    //static String format(const int value);
    printf("---[DateTimeFormatter Test Start]--- \n");
	//while(1) {
        Calendar c = createCalendar();
        DateTime date = c->getGmtDateTime();
        String str = st(DateTimeFormatter)::format(date,DateTimeFormatHTTP);
        printf("date time is %s \n",str->toChars());
    //}
    time_t rawtime;
    time(&rawtime);
    struct tm *info = gmtime(&rawtime );
   
    char *p = asctime(info);
    printf("p is %s \n",p);
    //String format(const int value, const int width);
	//String format0(const int value, const int width);

}

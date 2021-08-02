#include <stdio.h>
#include <unistd.h>
#include <time.h>

#include "Calendar.hpp"
#include "File.hpp"
#include "FileInputStream.hpp"
#include "ArrayList.hpp"
#include "testCalendar.hpp"
#include "StringReader.hpp"

using namespace obotcha;

ArrayList<TimeData> monthList;
ArrayList<TimeData> dateList;
ArrayList<TimeData> hourList;
ArrayList<TimeData> minuteList;
ArrayList<TimeData> secondList;
ArrayList<TimeData> yearList;

extern int testCaldnerCreate();
extern int testCalendarIncreaseYear();
extern int testCalendarIncreaseDay();
extern int testCalendarIncreaseMonth();
extern int testCalendarIncreaseHour();
extern int testCalendarIncreaseMinute();
extern int testCalendarIncreaseSecond();
extern int testCalendarDecreaseYear();
extern int testCalendarDecreaseDay();
extern int testCalendarDecreaseMonth();
extern int testCalendarDecreaseHour();
extern int testCalendarDecreaseMinute();
extern int testCalendarDecreaseSecond();


extern int convertDayOfWeekFromJava(int);

void simpleTest() {
  Calendar c = createCalendar(9277732677921l);
  printf("day of week is %d \n",c->get(st(Calendar)::DayOfWeek));
  printf("day of year is %d \n",c->get(st(Calendar)::DayOfYear));
  printf("day of month is %d \n",c->get(st(Calendar)::DayOfMonth));
}

ArrayList<TimeData> analyse(File f) {
    FileInputStream stream = createFileInputStream(f);
    stream->open();

    bool isStart = true;
    TimeData data = nullptr;
    ArrayList<TimeData> list = createArrayList<TimeData>();
    StringReader reader = createStringReader(stream);

    while(1) {

      String content = reader->readLine();
      if(content == nullptr) {
        break;
      }
      //printf("content is %s \n",content->toChars());
      if(content->indexOf("-------") != -1) {
          //printf("add data11111 \n");
          //if(isStart) {
            //printf("add data22222 \n");
            //data = createTimeData();
          //  isStart = false;
          //} else {
            //printf("add data33333 \n");
            //printf("data year is %d \n",data->year);
            //printf("data month is %d \n",data->month);
            //printf("data dayOfYear is %d \n",data->dayOfYear);
            //printf("data dayOfWeek is %d \n",data->dayOfWeek);
            //printf("data dayOfMonth is %d \n",data->dayOfMonth);
            //printf("data hour is %d \n",data->hour);
            //printf("data minute is %d \n",data->minute);
            //printf("data second is %d \n",data->second);
            //printf("data millisecond is %d \n",data->millisecond);
            if(data != nullptr) {
              list->add(data);
            }
            data = createTimeData();
            
          //  isStart = true;
          //}
      } else if(content->indexOf("time") != -1) {
          int index = content->lastIndexOf(" ");
          String timeStr = content->subString(index + 1,content->size() - index - 1);
          long value = timeStr->toBasicLong();
          data->time = value;
          //printf("time is %ld \n",data->time);
      } else if(content->indexOf("hour") != -1) {
          int index = content->lastIndexOf(" ");
          String hourStr = content->subString(index + 1,content->size() - index - 1);
          int value = hourStr->toBasicInt();
          data->hour = value;
          //printf("hour is %d \n",data->hour);
      } else if(content->indexOf("minute") != -1) {
          int index = content->lastIndexOf(" ");
          String minuteStr = content->subString(index + 1,content->size() - index - 1);
          int value = minuteStr->toBasicInt();
          data->minute = value;
          //printf("minute is %d \n",data->minute);
      } else if(content->indexOf("millisecond") != -1) {
          int index = content->lastIndexOf(" ");
          String millStr = content->subString(index + 1,content->size() - index - 1);
          int value = millStr->toBasicInt();
          data->millisecond = value;
          //printf("millisecond is %d \n",data->millisecond);
      } else if(content->indexOf("dayOfYear") != -1) {
          int index = content->lastIndexOf(" ");
          String dayOfYearStr = content->subString(index + 1,content->size() - index - 1);
          int value = dayOfYearStr->toBasicInt();
          data->dayOfYear = value;
          //printf("dayOfYear is %d \n",data->dayOfYear);
      } else if(content->indexOf("dayOfWeek") != -1) {
          int index = content->lastIndexOf(" ");
          String dayOfWeekStr = content->subString(index + 1,content->size() - index - 1);
          int value = dayOfWeekStr->toBasicInt();
          data->dayOfWeek = value;
          //printf("dayOfWeek is %d \n",data->dayOfWeek);
      } else if(content->indexOf("dayOfMonth") != -1) {
          int index = content->lastIndexOf(" ");
          String dayOfMonthStr = content->subString(index + 1,content->size() - index - 1);
          int value = dayOfMonthStr->toBasicInt();
          data->dayOfMonth = value;
          //printf("dayOfMonth is %d \n",data->dayOfMonth);
      } else if(content->indexOf("year") != -1) {
          int index = content->lastIndexOf(" ");
          String yearStr = content->subString(index + 1,content->size() - index - 1);
          int value = yearStr->toBasicInt();
          data->year = value;
          //printf("year is %d \n",data->year);
      } else if(content->indexOf("month") != -1) {
          int index = content->lastIndexOf(" ");
          String monthStr = content->subString(index + 1,content->size() - index - 1);
          int value = monthStr->toBasicInt();
          data->month = value;
          //printf("month is %d \n",data->month);
      } else if(content->indexOf("day") != -1) {
          int index = content->lastIndexOf(" ");
          String dayStr = content->subString(index + 1,content->size() - index - 1);
          int value = dayStr->toBasicInt();
          data->day = value;
          //printf("day is %d \n",data->day);
      } else if(content->indexOf("second") != -1) {
          int index = content->lastIndexOf(" ");
          String secondStr = content->subString(index + 1,content->size() - index - 1);
          int value = secondStr->toBasicInt();
          data->second = value;
          //printf("second is %d \n",data->second);
      }
    }

    return list;
}


int main() {
    //Test
    printf("start calndar test \n");
    File dateFile = createFile("./testData/date.txt");
    File hourFile = createFile("./testData/hour.txt");
    File minuteFile = createFile("./testData/minute.txt");
    File secondFile = createFile("./testData/second.txt");
    File yearFile = createFile("./testData/year.txt");
    File monthFile = createFile("./testData/month.txt");

    dateList = analyse(dateFile);
    hourList = analyse(hourFile);
    minuteList = analyse(minuteFile);
    secondList = analyse(secondFile);
    yearList = analyse(yearFile);
    monthList = analyse(monthFile);

    testCaldnerCreate();
    testCalendarIncreaseYear();
    testCalendarIncreaseDay();
    testCalendarIncreaseMonth();
    testCalendarIncreaseHour();
    testCalendarIncreaseMinute();
    testCalendarIncreaseSecond();

    testCalendarDecreaseYear();
    testCalendarDecreaseDay();
    testCalendarDecreaseMonth();
    testCalendarDecreaseHour();
    testCalendarDecreaseMinute();
    testCalendarDecreaseSecond();

    return 0;

}

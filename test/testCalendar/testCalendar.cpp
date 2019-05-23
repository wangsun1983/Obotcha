#include <stdio.h>
#include <unistd.h>
#include <time.h>

#include "Calendar.hpp"
#include "File.hpp"
#include "FileInputStream.hpp"
#include "ArrayList.hpp"

using namespace obotcha;

DECLARE_SIMPLE_CLASS(TimeData) {
public:
  long time;
  int year;
  int month;
  int day;
  int hour;
  int minute;
  int second;
  int millisecond;
  int dayOfYear;
  int dayOfWeek;
  int dayOfMonth;

  ~_TimeData() {
    //printf("remove ~~~~ \n");
  }
};

ArrayList<TimeData> analyse(File f) {
    FileInputStream stream = createFileInputStream(f);
    stream->open();

    bool isStart = true;
    TimeData data;
    ArrayList<TimeData> list = createArrayList<TimeData>();

    while(1) {
      String content = stream->readLine();
      if(content == nullptr) {
        break;
      }
      //printf("content is %s \n",content->toChars());
      if(content->indexOf("-------") != -1) {
          //printf("add data11111 \n");
          if(isStart) {
            //printf("add data22222 \n");
            data = createTimeData();
            isStart = false;
          } else {
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

            list->add(data);
            isStart = true;
          }
      } else if(content->indexOf("time") != -1) {
          int index = content->lastIndexOf(" ");
          String timeStr = content->subString(index + 1,content->size() - 1);
          long value = timeStr->toBasicLong();
          data->time = value;
          //printf("time is %ld \n",data->time);
      } else if(content->indexOf("hour") != -1) {
          int index = content->lastIndexOf(" ");
          String hourStr = content->subString(index + 1,content->size() - 1);
          int value = hourStr->toBasicInt();
          data->hour = value;
          //printf("hour is %d \n",data->hour);
      } else if(content->indexOf("minute") != -1) {
          int index = content->lastIndexOf(" ");
          String minuteStr = content->subString(index + 1,content->size() - 1);
          int value = minuteStr->toBasicInt();
          data->minute = value;
          //printf("minute is %d \n",data->minute);
      } else if(content->indexOf("millisecond") != -1) {
          int index = content->lastIndexOf(" ");
          String millStr = content->subString(index + 1,content->size() - 1);
          int value = millStr->toBasicInt();
          data->millisecond = value;
          //printf("millisecond is %d \n",data->millisecond);
      } else if(content->indexOf("dayOfYear") != -1) {
          int index = content->lastIndexOf(" ");
          String dayOfYearStr = content->subString(index + 1,content->size() - 1);
          int value = dayOfYearStr->toBasicInt();
          data->dayOfYear = value;
          //printf("dayOfYear is %d \n",data->dayOfYear);
      } else if(content->indexOf("dayOfWeek") != -1) {
          int index = content->lastIndexOf(" ");
          String dayOfWeekStr = content->subString(index + 1,content->size() - 1);
          int value = dayOfWeekStr->toBasicInt();
          data->dayOfWeek = value;
          //printf("dayOfWeek is %d \n",data->dayOfWeek);
      } else if(content->indexOf("dayOfMonth") != -1) {
          int index = content->lastIndexOf(" ");
          String dayOfMonthStr = content->subString(index + 1,content->size() - 1);
          int value = dayOfMonthStr->toBasicInt();
          data->dayOfMonth = value;
          //printf("dayOfMonth is %d \n",data->dayOfMonth);
      } else if(content->indexOf("year") != -1) {
          int index = content->lastIndexOf(" ");
          String yearStr = content->subString(index + 1,content->size() - 1);
          int value = yearStr->toBasicInt();
          data->year = value;
          //printf("year is %d \n",data->year);
      } else if(content->indexOf("month") != -1) {
          int index = content->lastIndexOf(" ");
          String monthStr = content->subString(index + 1,content->size() - 1);
          int value = monthStr->toBasicInt();
          data->month = value;
          //printf("month is %d \n",data->month);
      } else if(content->indexOf("day") != -1) {
          int index = content->lastIndexOf(" ");
          String dayStr = content->subString(index + 1,content->size() - 1);
          int value = dayStr->toBasicInt();
          data->day = value;
          //printf("day is %d \n",data->day);
      } else if(content->indexOf("second") != -1) {
          int index = content->lastIndexOf(" ");
          String secondStr = content->subString(index + 1,content->size() - 1);
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
    //File hourFile = createFile("./testData/hour.txt");
    //File minuteFile = createFile("./testData/minute.txt");
    //File secondFile = createFile("./testData/second.txt");
    //File yearFile = createFile("./testData/year.txt");
    printf("start analyse \n");
    ArrayList<TimeData> dateList = analyse(dateFile);
    printf("end analyse \n");

    //Calendar(long int timeMillis)
    while(1) {
        int size = dateList->size();
        //printf("data size is %d \n",size);
        for(int i = 0;i<size;i++) {
          TimeData d1 = dateList->get(i);
          Calendar c1 = createCalendar(d1->time);
          if(c1->get(CalendarType::Year) != d1->year ||
             c1->get(CalendarType::Month) != d1->month ||
             c1->get(CalendarType::DayOfYear) != (d1->dayOfYear - 1) ||
             c1->get(CalendarType::DayOfWeek) != (d1->dayOfWeek - 1) ||
             c1->get(CalendarType::DayOfMonth) != d1->dayOfMonth ||
             c1->get(CalendarType::Hour) != d1->hour ||
             c1->get(CalendarType::Minute) != d1->minute ||
             c1->get(CalendarType::Second) != d1->second ||
             c1->get(CalendarType::MSecond) != d1->millisecond) {

               printf("Calndear year is %d,data year is %d \n",c1->get(CalendarType::Year),d1->year);
               printf("Calndear month is %d,data month is %d \n",c1->get(CalendarType::Month),d1->month);
               printf("Calndear dayOfYear is %d,data dayOfYear is %d \n",c1->get(CalendarType::DayOfYear),d1->dayOfYear);
               printf("Calndear dayOfWeek is %d,data dayOfWeek is %d \n",c1->get(CalendarType::DayOfWeek),d1->dayOfWeek);
               printf("Calndear dayOfMonth is %d,data dayOfMonth is %d \n",c1->get(CalendarType::DayOfMonth),d1->dayOfMonth);
               printf("Calndear hour is %d,data hour is %d \n",c1->get(CalendarType::Hour),d1->hour);
               printf("Calndear minute is %d,data minute is %d \n",c1->get(CalendarType::Minute),d1->minute);
               printf("Calndear second is %d,data second is %d \n",c1->get(CalendarType::Second),d1->second);
               printf("Calndear millisecond is %d,data millisecond is %d \n",c1->get(CalendarType::MSecond),d1->millisecond);

               printf("---[Calendar Test {Calendar(long int timeMillis)} case1] [FAILED]--- \n");
               return 0;
          }

          printf("i is %d \n",i);
        }

        break;

    }

    return 0;




}

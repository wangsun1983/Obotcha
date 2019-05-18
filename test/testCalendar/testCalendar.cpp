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

      if(content->indexOf("-------") != -1) {
          if(isStart) {
            data = createTimeData();
          } else {
            list->add(data);
            isStart = true;
          }
      } else if(content->indexOf("time") != -1) {
          int index = content->lastIndexOf(" ");
          String timeStr = content->subString(index + 1,content->size() - 1);
          long value = timeStr->toBasicLong();
          data->time = value;
      } else if(content->indexOf("year") != -1) {
          int index = content->lastIndexOf(" ");
          String yearStr = content->subString(index + 1,content->size() - 1);
          int value = yearStr->toBasicInt();
          data->year = value;
      } else if(content->indexOf("month") != -1) {
          int index = content->lastIndexOf(" ");
          String monthStr = content->subString(index + 1,content->size() - 1);
          int value = monthStr->toBasicInt();
          data->month = value;
      } else if(content->indexOf("day") != -1) {
          int index = content->lastIndexOf(" ");
          String dayStr = content->subString(index + 1,content->size() - 1);
          int value = dayStr->toBasicInt();
          data->day = value;
      } else if(content->indexOf("hour") != -1) {
          int index = content->lastIndexOf(" ");
          String hourStr = content->subString(index + 1,content->size() - 1);
          int value = hourStr->toBasicInt();
          data->hour = value;
      } else if(content->indexOf("minute") != -1) {
          int index = content->lastIndexOf(" ");
          String minuteStr = content->subString(index + 1,content->size() - 1);
          int value = minuteStr->toBasicInt();
          data->minute = value;
      } else if(content->indexOf("second") != -1) {
          int index = content->lastIndexOf(" ");
          String secondStr = content->subString(index + 1,content->size() - 1);
          int value = secondStr->toBasicInt();
          data->second = value;
      } else if(content->indexOf("millisecond") != -1) {
          int index = content->lastIndexOf(" ");
          String millStr = content->subString(index + 1,content->size() - 1);
          int value = millStr->toBasicInt();
          data->millisecond = value;
      } else if(content->indexOf("dayOfYear") != -1) {
          int index = content->lastIndexOf(" ");
          String dayOfYearStr = content->subString(index + 1,content->size() - 1);
          int value = dayOfYearStr->toBasicInt();
          data->dayOfYear = value;
      } else if(content->indexOf("dayOfWeek") != -1) {
          int index = content->lastIndexOf(" ");
          String dayOfWeekStr = content->subString(index + 1,content->size() - 1);
          int value = dayOfWeekStr->toBasicInt();
          data->dayOfWeek = value;
      } else if(content->indexOf("dayOfMonth") != -1) {
          int index = content->lastIndexOf(" ");
          String dayOfMonthStr = content->subString(index + 1,content->size() - 1);
          int value = dayOfMonthStr->toBasicInt();
          data->dayOfMonth = value;
      }
    }
}

int main() {
    //Test
    File dateFile = createFile("./testData/date.txt");
    //File hourFile = createFile("./testData/hour.txt");
    //File minuteFile = createFile("./testData/minute.txt");
    //File secondFile = createFile("./testData/second.txt");
    //File yearFile = createFile("./testData/year.txt");

    ArrayList<TimeData> dateList = analyse(dateFile);

    while(1) {

    }






}

#ifndef _TEST_CALENDAR_CREATE_HPP
#define _TEST_CALENDAR_CREATE_HPP

namespace obotcha {

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

}
#endif


#include "calendar.h"

Calendar::Calendar()
{}

CalendarDay Calendar::getCalendarDayByName(QString nameDay){
    CalendarDay cd;
    foreach (CalendarDay day, _days) {
        if(day._day == nameDay){
            cd = day;
            break;
        }
    }

    return cd;
}


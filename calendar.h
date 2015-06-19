#ifndef CALENDAR_H
#define CALENDAR_H

#include "calendarday.h"
#include <QList>

class Calendar
{
public:
    Calendar();

    QList<CalendarDay> _days;

    CalendarDay getCalendarDayByName(QString nameDay);
};

#endif // CALENDAR_H

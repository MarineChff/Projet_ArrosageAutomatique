#ifndef CALENDARDAY_H
#define CALENDARDAY_H

#include <QBitArray>
#include <QString>

class CalendarDay
{
public:
    CalendarDay();

    QString _day;
    QBitArray _bitArrayDay;
};

#endif // CALENDARDAY_H

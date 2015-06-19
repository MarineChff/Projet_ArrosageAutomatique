
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QMessageBox>
#include <QTimeEdit>
#include <QSpinBox>
#include <QCheckBox>
#include <QPair>
#include <list>
#include <stdio.h>
#include <time.h>
#include <bitset>




MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label_validation->setVisible(false);

    _currentDay = "Lundi";

    /*foreach (QObject *element, ui->tab->children())
    {
        if(element->objectName().contains("checkBox"))
        {
            _listCheckBox.push_back((QCheckBox*) element);
            i++;
        }
    }*/
    _listCheckBox.push_back(ui->checkBox_1);
    _listCheckBox.push_back(ui->checkBox_2);
    _listCheckBox.push_back(ui->checkBox_3);
    _listCheckBox.push_back(ui->checkBox_4);
    _listCheckBox.push_back(ui->checkBox_5);
    _listCheckBox.push_back(ui->checkBox_6);
    _listCheckBox.push_back(ui->checkBox_7);
    _listCheckBox.push_back(ui->checkBox_8);
    _listCheckBox.push_back(ui->checkBox_9);
    _listCheckBox.push_back(ui->checkBox_10);
    _listCheckBox.push_back(ui->checkBox_11);
    _listCheckBox.push_back(ui->checkBox_12);
    _listCheckBox.push_back(ui->checkBox_13);
    _listCheckBox.push_back(ui->checkBox_14);
    _listCheckBox.push_back(ui->checkBox_15);
    _listCheckBox.push_back(ui->checkBox_16);
    _listCheckBox.push_back(ui->checkBox_17);
    _listCheckBox.push_back(ui->checkBox_18);
    _listCheckBox.push_back(ui->checkBox_19);
    _listCheckBox.push_back(ui->checkBox_20);
    _listCheckBox.push_back(ui->checkBox_21);
    _listCheckBox.push_back(ui->checkBox_22);
    _listCheckBox.push_back(ui->checkBox_23);
    _listCheckBox.push_back(ui->checkBox_24);
    _listCheckBox.push_back(ui->checkBox_25);
    _listCheckBox.push_back(ui->checkBox_26);
    _listCheckBox.push_back(ui->checkBox_27);
    _listCheckBox.push_back(ui->checkBox_28);
    _listCheckBox.push_back(ui->checkBox_29);
    _listCheckBox.push_back(ui->checkBox_30);
    _listCheckBox.push_back(ui->checkBox_31);
    _listCheckBox.push_back(ui->checkBox_32);
    _listCheckBox.push_back(ui->checkBox_33);
    _listCheckBox.push_back(ui->checkBox_34);
    _listCheckBox.push_back(ui->checkBox_35);
    _listCheckBox.push_back(ui->checkBox_36);
    _listCheckBox.push_back(ui->checkBox_37);
    _listCheckBox.push_back(ui->checkBox_38);
    _listCheckBox.push_back(ui->checkBox_39);
    _listCheckBox.push_back(ui->checkBox_40);
    _listCheckBox.push_back(ui->checkBox_41);
    _listCheckBox.push_back(ui->checkBox_42);
    _listCheckBox.push_back(ui->checkBox_43);
    _listCheckBox.push_back(ui->checkBox_44);
    _listCheckBox.push_back(ui->checkBox_45);
    _listCheckBox.push_back(ui->checkBox_46);
    _listCheckBox.push_back(ui->checkBox_47);
    _listCheckBox.push_back(ui->checkBox_48);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_comboBox_currentIndexChanged(const QString &arg1)
{
    ui->label_validation->setVisible(false);
    _currentDay = arg1;

    std::cout << _calendar._days.size() << std::endl;

    foreach (CalendarDay cd, _calendar._days){
        if(cd._day == _currentDay){
            int i = 0;
            foreach(QCheckBox* cb, _listCheckBox){
                cb->setChecked(cd._bitArrayDay.at(i));
                ++i;
            }
            break;
        }
        else {
            foreach(QCheckBox* cb, _listCheckBox){
                cb->setChecked(false);
            }
        }
    }

    std::cout << arg1.toStdString() << std::endl;
    
}

int MainWindow::calculSeconds(int hours, int minutes){
    return (hours * 3600) + (minutes * 60);
}

void MainWindow::on_pushButton_clicked()
{
    //controle si le jour n'est pas dans le calendar
    int j = 0;
    foreach (CalendarDay cd, _calendar._days){
        if(cd._day == _currentDay){
            _calendar._days.removeAt(j);
            break;
        }
        ++j;
    }

    QBitArray bitArrayDay;
    bitArrayDay.resize(48);
    for(int i = 0; i < _listCheckBox.size(); i++){
        QCheckBox* cb = _listCheckBox.at(i);
        std::cout << cb->objectName().toStdString() << std::endl;
        bitArrayDay[i] = cb->isChecked();
    }

    CalendarDay calendarDay;
    calendarDay._day = _currentDay;
    calendarDay._bitArrayDay = bitArrayDay;

    _calendar._days.push_back(calendarDay);

    ui->label_validation->setVisible(true);
}

void MainWindow::on_pushButton_end_clicked()
{
    QBitArray bitArrayCalendar;
    bitArrayCalendar.resize(360);

    /* CALENDRIER */
    QList<QString> days;
    days.push_back("Lundi");
    days.push_back("Mardi");
    days.push_back("Mercredi");
    days.push_back("Jeudi");
    days.push_back("Vendredi");
    days.push_back("Samedi");
    days.push_back("Dimanche");

    int j = 0;
    foreach(QString day, days){
        CalendarDay calendarDay = _calendar.getCalendarDayByName(day);
        //std::cout << j << std::endl;
        if (calendarDay._bitArrayDay.size() > 0){
            for (int i = 0; i < calendarDay._bitArrayDay.size(); i++) {
                //std::cout << calendarDay._bitArrayDay.at(i);
                bitArrayCalendar[j] = calendarDay._bitArrayDay.at(i);
                ++j;
            }
        } else {
            for(int i = 0; i < 48; i++){
                //std::cout << false;
                bitArrayCalendar[j] = false;
                j++;
            }
        }
        //std::cout << "" <<std::endl;
    }

    /* 1/2 HEURE COURANTE */
    char *wday[] = {"Dimanche", "Lundi", "Mardi", "Mercredi",
                    "Jeudi", "Vendredi", "Samedi", "Inconnu"};

    struct tm time_check;
    int year, month, day;

    /*  Input a year, month and day to find the weekday for */
    year = 2015;
    month = 6;
    day = 18;

    /*  load the time_check structure with the data */
    time_check.tm_year = year - 1900;
    time_check.tm_mon  = month - 1;

    time_check.tm_mday = day;
    time_check.tm_hour = 0;
    time_check.tm_min  = 0;
    time_check.tm_sec  = 1;
    time_check.tm_isdst = -1;

    /*  call mktime to fill in the weekday field of the structure */
    if (mktime(&time_check) == -1)
        time_check.tm_wday = 7;

    QString systemDay = (QString)wday[time_check.tm_wday];
    //std::cout << systemDay.toStdString() << std::endl;

    /* Heure système */
    time_t timer1;
    time(&timer1);
    int secondes, minutes, heures;
    struct tm *newTime1;
    newTime1 = localtime(&timer1);
    heures = newTime1->tm_hour;		    // Les heures sont dans "heures"
    minutes = newTime1->tm_min;		    // Les minutes sont dans "minutes"
    secondes = newTime1->tm_sec;		// Les secondes sont dans "secondes"

    //std::cout << heures << ":" << minutes << std::endl;

    int intHalfHourDaySystem;
    if(systemDay == "Lundi"){
        intHalfHourDaySystem = 0;
    } else if (systemDay == "Mardi") {
        intHalfHourDaySystem = 48;
    } else if (systemDay == "Mercredi") {
        intHalfHourDaySystem = 96;
    } else if(systemDay == "Jeudi"){
        intHalfHourDaySystem = 144;
    } else if (systemDay == "Vendredi") {
        intHalfHourDaySystem = 192;
    } else if (systemDay == "Samedi") {
        intHalfHourDaySystem = 240;
    } else if (systemDay == "Dimanche") {
        intHalfHourDaySystem = 288;
    }

    //int calculHalfHour = heures * 2;
    intHalfHourDaySystem += heures * 2;

    if(minutes > 30){
        intHalfHourDaySystem += 1;
    }

    //std::cout << intHalfHourDaySystem << std::endl;

    std::bitset<16> bit_halfHour(intHalfHourDaySystem);
    //std::cout << bit_halfHour;

    for(int k = 0; k < 16; k++){
        bitArrayCalendar[j] = bit_halfHour[k];
        j++;
    }

    /* TAUX HUMIDITE */
    int taux = ui->spinBox_tauxHumidite->value();
    std::bitset<8> bit_humidite(taux);
    //std::cout << bit_humidite;

    for(int l = 0; l < 8; l++){
        bitArrayCalendar[j] = bit_humidite[l];
        j++;
    }

    //std::cout << j << std::endl;

    for(int m =0; m < 360; m++){
        std::cout << bitArrayCalendar[m];
    }


}

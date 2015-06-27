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
    ui(new Ui::MainWindow),
    _controller()
{

    ui->setupUi(this);
    ui->label_validation->setVisible(false);
    ui->label_traitement->setVisible(false);

    _currentDay = "Lundi";

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

    //std::cout << _listCheckBox.size() << std::endl;


    foreach (CalendarDay cd, _calendar._days){
        if(cd._day == _currentDay){
            int i = 0;
            foreach(QCheckBox* cb, _listCheckBox){
                std::cout << cb->objectName().toStdString() << std::endl;
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
        // On récupère le calendrier de chaque jour de la semaine
        CalendarDay calendarDay = _calendar.getCalendarDayByName(day);
        //std::cout << j << std::endl;
        // Si on a un calendrier pour le jour, on récupère son bitArray qu'on met dans le bitArray global
        if (calendarDay._bitArrayDay.size() > 0){
            for (int i = 0; i < 48; i++) {
                bitArrayCalendar[j] = calendarDay._bitArrayDay.at(i);
                ++j;
            }
        } else {
            // Sinon on passe que des 0 au bitArray glocal sur 48 bits
            for(int i = 0; i < 48; i++){
                //std::cout << false;
                bitArrayCalendar[j] = false;
                ++j;
            }
        }
        //std::cout << "" <<std::endl;
    }

    /* 1/2 HEURE COURANTE DU SYSTEME */
    QDate systemDate = QDate::currentDate();
    QTime systemTime = QTime::currentTime();


    int minutes, heures;
    heures = systemTime.hour();    // Les heures
    minutes = systemTime.minute(); 	 // Les minutes

    //std::cout << heures << ":" << minutes << std::endl;

    int intHalfHourDaySystem = ((systemDate.dayOfWeek() - 1) * 48) + (heures * 2);

    // Si minutes > 30 on a passé une 1/2 heure supp
    if(minutes > 30){
        intHalfHourDaySystem += 1;
    }

    //std::cout << intHalfHourDaySystem << std::endl;

    // On convertit la 1/2 courante sur 16 bits et on l'ajoute au bitArray global
    std::bitset<16> bit_halfHour(intHalfHourDaySystem);
    //std::cout << bit_halfHour << std::endl;
    for(int k = 15; k >= 0; k--){
        bitArrayCalendar[j] = bit_halfHour[k];
        j++;
    }

    /* TAUX HUMIDITE */
    int taux = ui->spinBox_tauxHumidite->value();
    // On convertit le taux sur 8 bits et on l'ajoute au bitArray global
    std::bitset<8> bit_humidite(taux);
    for(int l = 7; l >= 0; l--){
        bitArrayCalendar[j] = bit_humidite[l];
        j++;
    }

    //Affichage du tableau de bit -- peut être commenté
    std::cout << "Le calendrier contient " << bitArrayCalendar.size() << " bits" << std::endl;
    for(int m =0; m < bitArrayCalendar.size(); m++){
        std::cout << bitArrayCalendar[m];
    }
    std::cout << std::endl;

    // Envoi sur le PIC
    _controller.setBits(bitArrayCalendar);


    ui->label_traitement->setVisible(true);


}

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "calendarday.h"
#include "calendar.h"
#include <QMainWindow>
#include <QList>
#include <QCheckBox>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_comboBox_currentIndexChanged(const QString &arg1);

    void on_pushButton_clicked();

    void on_pushButton_end_clicked();

private:
    Ui::MainWindow *ui;

    QString _currentDay;
    QList<QCheckBox*> _listCheckBox;

    Calendar _calendar;

};

#endif // MAINWINDOW_H

#include "mainwindow.h"
#include <QApplication>
#include <iostream>
#include <bitset>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();

    /*int x = 55;
    std::bitset<8> bin_x(x);
    std::cout << bin_x;

    return 0;*/
}

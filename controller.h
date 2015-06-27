#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QBitArray>

class Controller
{
public:
    Controller();
    void setBits(QBitArray bits);
    void writeToSerial();
private:
    QBitArray _currentParameters;

    QByteArray bitsToBytes(QBitArray bits);
};

#endif // CONTROLLER_H

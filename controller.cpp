#include "controller.h"

QT_USE_NAMESPACE
#include <QtSerialPort/QSerialPort>
#include "serialportwriter.h"

Controller::Controller()
{
}

QByteArray Controller::bitsToBytes(QBitArray bits) {
    QByteArray bytes;
    bytes.resize(bits.count()/8+1);
    bytes.fill(0);
    // Convert from QBitArray to QByteArray
    for(int b=0; b<bits.count(); ++b)
        bytes[b/8] = ( bytes.at(b/8) | ((bits[b]?1:0)<<(b%8)));
    return bytes;
}

void Controller::setBits(QBitArray bits)
{
    // Copying bits
    _currentParameters.clear();
    _currentParameters.resize(bits.size());
    for(int m = 0; m < bits.size(); m++){
        _currentParameters[m] = bits[m];
    }

    writeToSerial();
}

void Controller::writeToSerial()
{
    QSerialPort serialPort;
    QString serialPortName = "/dev/ttyUSB0";
    serialPort.setPortName(serialPortName);

    int serialPortBaudRate = QSerialPort::Baud2400;
    serialPort.setBaudRate(serialPortBaudRate);
    serialPort.open(QIODevice::WriteOnly);

    SerialPortWriter serialPortWriter(&serialPort);
    serialPortWriter.write(bitsToBytes(_currentParameters));
}

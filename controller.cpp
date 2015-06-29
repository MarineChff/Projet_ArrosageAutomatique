#include "controller.h"

QT_USE_NAMESPACE
#include <QtSerialPort/QSerialPort>

#include <QDebug>

Controller::Controller()
{
}

QByteArray Controller::bitsToBytes(QBitArray bits) {
    qDebug() << bits.size();
    QByteArray bytes;
    bytes.resize(bits.count()/8);
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
    serialPort.open(QIODevice::ReadWrite);

    QTextStream standardOutput(stdout);
    QByteArray writeData = bitsToBytes(_currentParameters);
    qint64 bytesWritten = serialPort.write(writeData);

    if (bytesWritten == -1) {
        standardOutput << QObject::tr("Failed to write the data to port %1, error: %2").arg(serialPortName).arg(serialPort.errorString()) << endl;
        return;
    } else if (bytesWritten != writeData.size()) {
        standardOutput << QObject::tr("Failed to write all the data to port %1, error: %2").arg(serialPortName).arg(serialPort.errorString()) << endl;
        return;
    } else if (!serialPort.waitForBytesWritten(5000)) {
        standardOutput << QObject::tr("Operation timed out or an error occurred for port %1, error: %2").arg(serialPortName).arg(serialPort.errorString()) << endl;
        return;
    }

    standardOutput << QObject::tr("Data successfully sent to port %1").arg(serialPortName) << endl;

}

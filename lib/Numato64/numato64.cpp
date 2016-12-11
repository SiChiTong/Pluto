#include "numato64.h"
#include <iostream>

namespace Pluto
{

Numato64::Numato64(QObject *parent) :
    QObject(parent),
    mConnected(false),
    mPortName("undefined"),
    mBaudrate(115200),
    mSerialPort(NULL)
{
    mSerialPort = new QSerialPort(this);
}

int Numato64::connectToBoard(QString portName, int baudrate)
{
    if (mSerialPort->isOpen()) disconnectFromBoard();

    // Set to default if not specified.
    if (portName=="") portName = DEFAULT_NUMATO64_PORT;
    if (baudrate==0)  baudrate = DEFAULT_BAUDRATE;

    // Update private variables.
    mPortName = portName;
    mBaudrate = baudrate;

    // Configure port.
    mSerialPort->setPortName(portName);
    mSerialPort->setBaudRate(baudrate);
    mSerialPort->setDataBits(QSerialPort::Data8);
    mSerialPort->setParity(QSerialPort::NoParity);
    mSerialPort->setStopBits(QSerialPort::OneStop);
    mSerialPort->setFlowControl(QSerialPort::NoFlowControl);

    mSerialPort->open(QIODevice::ReadWrite);
    if( ! mSerialPort->isOpen() )
    {
        return 0;
    }

    connect(mSerialPort, &QSerialPort::readyRead,
            this, &Numato64::_readUpdate);

    connect(&mStatusTimer, &QTimer::timeout,
            this, &Numato64::_queryUpdate);

    mStatusTimer.start(1000);

    mConnected = true;
    return 1;
}

int Numato64::disconnectFromBoard()
{
    if (isConnected())
    {
        // Stop timer, disconnect signal, close port
        mStatusTimer.stop();
        disconnect(mSerialPort, &QSerialPort::readyRead,
                this, &Numato64::_readUpdate);
        mSerialPort->close();
        mConnected = false;
    }
    return 1;
}

bool Numato64::isConnected()
{
    return mConnected;
}

Numato64::Status Numato64::getUpdatedData()
{
    return mStatus;
}

void Numato64::_readUpdate()
{
    QString a = mSerialPort->readAll();
    std::cout<<"Numato64:"<<qPrintable(a)<<std::endl;
    std::cout.flush();
}

void Numato64::_queryUpdate()
{
    static int sensorId = 0;

    if (sensorId < 24)
    {
        QString command("adc read ");
        command += QString::number(sensorId) + "\n";
        mSerialPort->write(command.toStdString().c_str());
    }
    else
    {
        mSerialPort->write("gpio readall\n");
    }
    sensorId++;
    if(sensorId==64) sensorId=0;
}

} // namespace Pluto

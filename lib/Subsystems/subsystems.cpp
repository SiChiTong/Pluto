#include "subsystems.h"
#include <iostream>

namespace Pluto
{

class Status
{
public:
    int analogIrSensors[NUM_ANALOG_IR_SENSOR];
    int binaryIrSensors[NUM_BINARY_IR_SENSOR];
    int analogCurrentSensor[NUM_ANALOG_CURRENT_SENSOR];
    int analogSonarSensor[NUM_ANALOG_SONAR_SENSOR];
    int encoder[NUM_ENCODER];
    int relay[NUM_RELAY];
};


Subsystems::Subsystems(const char *name)
{
    setObjectName(name);
    std::cout<<qPrintable(objectName())<<" created"<<std::endl;

    mStatus = new Status();
    mDrivePort    = new QSerialPort(this);
    mRelayPort    = new QSerialPort(this);
    mStatusTimer  = new QTimer(this);
}


int Subsystems::getSensor(int type, int number)
{
    (void)type;
    (void)number;
    int value = -1;
    return value;
}


void Subsystems::connectSubsystems()
{
    mDrivePort->setPortName(DRIVE_PORT);
    mDrivePort->setBaudRate(115200);
    mDrivePort->setDataBits(QSerialPort::Data8);
    mDrivePort->setParity(QSerialPort::NoParity);
    mDrivePort->setStopBits(QSerialPort::OneStop);
    mDrivePort->setFlowControl(QSerialPort::NoFlowControl);

    mRelayPort->setPortName(RELAY_PORT);
    mRelayPort->setBaudRate(115200);
    mRelayPort->setDataBits(QSerialPort::Data8);
    mRelayPort->setParity(QSerialPort::NoParity);
    mRelayPort->setStopBits(QSerialPort::OneStop);
    mRelayPort->setFlowControl(QSerialPort::NoFlowControl);

    if( ! mNumato64.connectToBoard() )
    {
        std::cerr<<"failed opening Numato64"<<std::endl;
    }

    mConnected = true;
}

void Subsystems::_readDriveUpdate()
{
    QByteArray a = mDrivePort->readAll();
    a[a.size()] = 0;
    std::cout<<"Drive Data:"<<qPrintable(a)<<std::endl;
    std::cout.flush();
}

void Subsystems::_readRelayUpdate()
{
    QByteArray a = mRelayPort->readAll();
    a[a.size()] = 0;
    std::cout<<"Relay Data:"<<qPrintable(a)<<std::endl;
    std::cout.flush();
}

void Subsystems::_handleStatusTimer()
{

}

void Subsystems::disconnectSubsystems()
{
    mDrivePort->close();
    mRelayPort->close();
    mConnected = false;
}

} // namespace Pluto

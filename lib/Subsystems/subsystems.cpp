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
    mNumato64Port = new QSerialPort(this);
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
    mNumato64Port->setPortName(NUMATO64_PORT);
    mNumato64Port->setBaudRate(115200);
    mNumato64Port->setDataBits(QSerialPort::Data8);
    mNumato64Port->setParity(QSerialPort::NoParity);
    mNumato64Port->setStopBits(QSerialPort::OneStop);
    mNumato64Port->setFlowControl(QSerialPort::NoFlowControl);

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

    mNumato64Port->open(QIODevice::ReadWrite);
    mDrivePort->open(QIODevice::ReadWrite);
    mRelayPort->open(QIODevice::ReadWrite);

    if( ! mNumato64Port->isOpen() ||
        ! mDrivePort->isOpen() ||
        ! mRelayPort->isOpen() )
    {
        std::cerr<<"unable to open usb serial device"<<std::endl;
    }

    connect(mNumato64Port, &QSerialPort::readyRead,
            this, &Subsystems::_readNumato64Update);
    connect(mDrivePort, &QSerialPort::readyRead,
            this, &Subsystems::_readDriveUpdate);
    connect(mRelayPort, &QSerialPort::readyRead,
            this, &Subsystems::_readRelayUpdate);

    connect(mStatusTimer, &QTimer::timeout,
            this, &Subsystems::_handleStatusTimer);

    mRelayPort->write("gpio notify on\n");
    mConnected = true;
}

void Subsystems::_readNumato64Update()
{
    static int sensorId = 0;
    QByteArray a = mNumato64Port->readAll();
    a[a.size()] = 0;
    
    if( 16 < a.size() )
    {
        std::cout<<"Numato64 Digital:"<<qPrintable(a)<<std::endl;
        sensorId = 0;
    }
    else
    {
        std::cout<<"Numato64 Analog "<<sensorId<<":"<<qPrintable(a)<<std::endl;
        sensorId++;
    }
    std::cout.flush();
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
    mNumato64Port->write("gpio readall\n");
    mNumato64Port->write("adc read 00\n");
    mNumato64Port->write("adc read 01\n");
    mNumato64Port->write("adc read 02\n");
    mNumato64Port->write("adc read 03\n");
    mNumato64Port->write("adc read 04\n");
    mDrivePort->write("?\n");
    mRelayPort->write("?\n");
}

void Subsystems::disconnectSubsystems()
{
    mNumato64Port->close();
    mDrivePort->close();
    mRelayPort->close();
    mConnected = false;
}

} // namespace Pluto

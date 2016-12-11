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
    if( ! mNumato64.connectToBoard() )
    {
        std::cerr<<"failed opening Numato64"<<std::endl;
    }
    if( ! mNumato4Relay.connectToBoard() )
    {
        std::cerr<<"failed opening Numato4Relay"<<std::endl;
    }
    mConnected = mNumato4Relay.isConnected() & mNumato64.isConnected();
}

void Subsystems::_readDriveUpdate()
{
}

void Subsystems::_readRelayUpdate()
{
}

void Subsystems::_handleStatusTimer()
{

}

void Subsystems::disconnectSubsystems()
{
    mNumato64.disconnectFromBoard();
    mNumato4Relay.disconnectFromBoard();
    mDrivePort->close();

    mConnected = false;
}

} // namespace Pluto

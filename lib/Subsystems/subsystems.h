#ifndef SUBSYSTEMS_H
#define SUBSYSTEMS_H

#include "resources.h"

#include <QObject>
#include <QList>
#include <stdio.h>
#include <QSerialPort>
#include <QTimer>

namespace Pluto
{

#define DRIVE_PORT    "/dev/ttyUSB0"
#define NUMATO64_PORT "/dev/ttyACM0"
#define RELAY_PORT    "/dev/ttyACM1"

// Forward declaration.
class Status;

//-------------------------------------------------------------------
// Class to find the connected subsystems and populate local objects.
//-------------------------------------------------------------------

class Subsystems : public QObject
{
    Q_OBJECT

public:

    // Constructor
    Subsystems(const char *name);

    // getSensor()
    // Returns the current value of specified sensor.
    // Refer to resources.h
    int getSensor(int type, int number);


public slots:

    // connectSubsystems()
    // Connects to all available subsystems.
    void connectSubsystems();
    
    // disconnectSubsystems()
    // Disconnects all subsystems.
    void disconnectSubsystems();

private:
    Status      *mStatus;
    QSerialPort *mNumato64Port;
    QSerialPort *mDrivePort;
    QSerialPort *mRelayPort;
    QTimer      *mStatusTimer;

    bool mConnected;

    void _readNumato64Update();
    void _readDriveUpdate();
    void _readRelayUpdate();

    void _handleStatusTimer();
};

}
#endif // SUBSYSTEMS_H

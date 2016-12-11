#ifndef SUBSYSTEMS_H
#define SUBSYSTEMS_H

#include "resources.h"

#include <QObject>
#include <QList>
#include <stdio.h>
#include <QSerialPort>
#include <QTimer>

#include <numato64.h>
#include <numato4relay.h>

namespace Pluto
{

#define DRIVE_PORT    "/dev/ttyUSB0"

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
    Numato64 mNumato64;
    Numato4Relay mNumato4Relay;

    QSerialPort *mDrivePort;
    QTimer      *mStatusTimer;

    bool mConnected;

    void _readDriveUpdate();
    void _readRelayUpdate();

    void _handleStatusTimer();
};

}
#endif // SUBSYSTEMS_H

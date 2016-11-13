#ifndef SUBSYSTEMS_H
#define SUBSYSTEMS_H

#include <QObject>
#include <QList>
#include <stdio.h>

namespace Pluto
{

class System
{
public:
    System(const char *ssData, const char *portName)
    {
        char _name[64];
        char _version[64];

        sscanf(ssData, "Name: %s Version: %s", _name, _version);

        name = QString(_name);
        version = QString(_version);
        port = QString(portName);
    }

    QString name;
    QString version;
    QString port;
};


//-------------------------------------------------------------------
// Class to find the connected subsystems and populate local objects.
//-------------------------------------------------------------------

class Subsystems : public QObject
{
    Q_OBJECT

public:

    Subsystems(const char *name);

public slots:

    void connectSubsystems();
    void searchSubsystems();
    void disconnectSubsystems();

    QList<System*> getSubsystemList();

private:

    QList<System*> mSubsystemList;
};

}
#endif // SUBSYSTEMS_H

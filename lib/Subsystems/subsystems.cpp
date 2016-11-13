#include "subsystems.h"

#include <iostream>

namespace Pluto
{

/*
Port:  /dev/ttyUSB2 ===> Name:Ir Sensors,Version:pluto-0.0.1

Port:  /dev/ttyUSB1 ===> Name:Power Control System,Version:pluto-0.0.1

Port:  /dev/ttyUSB0 ===> Name:Sabertooth Motor Drive,Version:pluto-0.0.1
*/

Subsystems::Subsystems(const char *name)
{
    setObjectName(name);
    std::cout<<qPrintable(objectName())<<" created"<<std::endl;
}

void Subsystems::connectSubsystems()
{

}

void Subsystems::searchSubsystems()
{
    for (QList<System*>::iterator i=mSubsystemList.begin(); i!=mSubsystemList.end(); ++i)
    {
        mSubsystemList.pop_front();
    }
    System *s0 = new System("Name: IrSensors Version: 0.0.1", "/dev/ttyUSB0");
    System *s1 = new System("Name: PowerControl System Version: 0.0.1", "/dev/ttyUSB1");
    System *s2 = new System("Name: MotorDrive Version: 0.0.1", "/dev/ttyUSB2");

    mSubsystemList.append(s0);
    mSubsystemList.append(s1);
    mSubsystemList.append(s2);
}

void Subsystems::disconnectSubsystems()
{

}

QList<System*> Subsystems::getSubsystemList()
{
    return mSubsystemList;
}

}

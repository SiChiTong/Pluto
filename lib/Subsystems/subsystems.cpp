#include "subsystems.h"

#include <iostream>

namespace Pluto
{

Subsystems::Subsystems(const char *name)
{
    setObjectName(name);
    std::cout<<qPrintable(objectName())<<" created"<<std::endl;
}

}

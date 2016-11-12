#ifndef SUBSYSTEMS_H
#define SUBSYSTEMS_H

#include <QObject>

namespace Pluto
{
class Subsystems : public QObject
{
    Q_OBJECT
public:
    Subsystems(const char *name);
};
}

#endif // SUBSYSTEMS_H

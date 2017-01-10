#ifndef ROBOTEQ_GLOBAL_H
#define ROBOTEQ_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(ROBOTEQ_LIBRARY)
#  define ROBOTEQSHARED_EXPORT Q_DECL_EXPORT
#else
#  define ROBOTEQSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // ROBOTEQ_GLOBAL_H

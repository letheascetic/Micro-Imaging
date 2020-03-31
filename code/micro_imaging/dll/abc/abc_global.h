#ifndef ABC_GLOBAL_H
#define ABC_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(ABC_LIBRARY)
#  define ABC_EXPORT Q_DECL_EXPORT
#else
#  define ABC_EXPORT Q_DECL_IMPORT
#endif

#endif // ABC_GLOBAL_H

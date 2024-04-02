#ifndef ENCRYPTION_GLOBAL_H
#define ENCRYPTION_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(ENCRYPTION_LIBRARY)
#define ENCRYPTION_EXPORT Q_DECL_EXPORT
#else
#define ENCRYPTION_EXPORT Q_DECL_IMPORT
#endif

#endif // ENCRYPTION_GLOBAL_H

#ifndef DLLPROJECT111_GLOBAL_H
#define DLLPROJECT111_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(DLLPROJECT111_LIBRARY)
#  define DLLPROJECT111SHARED_EXPORT Q_DECL_EXPORT
#else
#  define DLLPROJECT111SHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // DLLPROJECT111_GLOBAL_H

#ifndef BRACKETORDER_GLOBAL_H
#define BRACKETORDER_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(BRACKETORDER_LIBRARY)
#  define BRACKETORDERSHARED_EXPORT Q_DECL_EXPORT
#else
#  define BRACKETORDERSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // BRACKETORDER_GLOBAL_H

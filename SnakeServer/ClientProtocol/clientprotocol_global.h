#ifndef CLIENTPROTOCOL_GLOBAL_H
#define CLIENTPROTOCOL_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(CLIENTPROTOCOL_LIBRARY)
#  define CLIENTPROTOCOLSHARED_EXPORT Q_DECL_EXPORT
#else
#  define CLIENTPROTOCOLSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // CLIENTPROTOCOL_GLOBAL_H

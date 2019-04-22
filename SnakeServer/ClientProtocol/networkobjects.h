#ifndef NETWORKOBJECTS_H
#define NETWORKOBJECTS_H

#include <QMap>
#include <QSet>
#include "ping.h"
#include "factorynetobjects.h"

namespace ClientProtocol {
extern const qint8 PingType;

}

#define PING PingType
#endif // NETWORKOBJECTS_H

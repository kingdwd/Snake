#include "factorynetobjects.h"
#include "clientprotocol.h"
#include "ping.h"

namespace ClientProtocol {

auto i = FactoryNetObjects::regType<Ping>();


BaseNetworkObject *FactoryNetObjects::build(qint8 type) {
    if (!map.contains(type)) {
        return nullptr;
    }

    return map.value(type)->create();
}

NetworkClassSize FactoryNetObjects::getSize(qint8 type) {
    return types_sizes.value(type);
}

bool FactoryNetObjects::isRegisteredType(qint8 type) {
    return map.contains(type);
}

#define PING i;

}

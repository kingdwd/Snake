#include "factorynetobjects.h"
#include "clientprotocol.h"

namespace ClientProtocol {

BaseNetworkObject *FactoryNetObjects::build(quint8 type) {
    if (!map.contains(type)) {
        return nullptr;
    }

    return map.value(type)->create();
}

NetworkClassSize FactoryNetObjects::getSize(quint8 type) {
    return types_sizes.value(type);
}

bool FactoryNetObjects::isRegisteredType(quint8 type) {
    return map.contains(type);
}

}

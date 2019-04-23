#ifndef FACTORYNETOBJECTS_H
#define FACTORYNETOBJECTS_H
#include "clientprotocol_global.h"
#include "basenetworkobject.h"
#include <QMap>
#include <typeinfo>
namespace ClientProtocol {

class CLIENTPROTOCOLSHARED_EXPORT FactoryNetObjects {
private:
    static QMap<quint8, BaseNetworkObject*> map;
    static QMap<quint8, NetworkClassSize> types_sizes;

public:
    FactoryNetObjects() = delete;

    static BaseNetworkObject *build(quint8 type);
    static NetworkClassSize getSize(quint8 type);
    static bool isRegisteredType(quint8 type);

    template<typename T>
    static bool regType(quint8 id) {
        if (map.contains(id)) {
            return false;
        }

        auto tempObj = new T();
        map.insert(id, tempObj);
        types_sizes.insert(id, tempObj->classSize());
        return true;
    }
};
}


#endif // FACTORYNETOBJECTS_H

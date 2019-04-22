#ifndef FACTORYNETOBJECTS_H
#define FACTORYNETOBJECTS_H
#include "clientprotocol_global.h"
#include "basenetworkobject.h"
#include <QMap>
#include <typeinfo>
namespace ClientProtocol {

class CLIENTPROTOCOLSHARED_EXPORT FactoryNetObjects {
private:
    static QMap<qint8, BaseNetworkObject*> map;
    static QMap<quint64, qint8> types_hashes;
    static QMap<qint8, NetworkClassSize> types_sizes;

public:
    FactoryNetObjects() = delete;

    static BaseNetworkObject *build(qint8 type);
    static NetworkClassSize getSize(qint8 type);
    static bool isRegisteredType(qint8 type);

    template<typename T>
    static qint8 regType() {
        auto temp = typeid (T).hash_code();
        if (types_hashes.contains(temp)) {
            return types_hashes.value(temp);
        }

        auto tempObj = new T();
        map.insert(static_cast<char>(types_hashes.size()), tempObj);
        types_sizes.insert(static_cast<char>(types_hashes.size()), tempObj->classSize());
        types_hashes.insert(temp, static_cast<char>(types_hashes.size()));
        return types_hashes.value(temp);
    }
};
}


#endif // FACTORYNETOBJECTS_H

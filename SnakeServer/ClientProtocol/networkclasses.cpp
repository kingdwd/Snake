#include "networkclasses.h"

#include <QVariant>
namespace ClientProtocol {

NetworkClasses::NetworkClasses()
{

}


bool NetworkClasses::isNumber(NetworkClasses::Type type) {
    return isInteger(type) || isReal(type);
}

bool NetworkClasses::isStream(NetworkClasses::Type type) {
    return isString(type) || isVariant(type);
}

bool NetworkClasses::isCustomType(NetworkClasses::Type type) {
    return (type & CustomType) && type <= LastCustomType && !(type & BaseType);
}

bool NetworkClasses::isInteger(NetworkClasses::Type type) {
    return type == Int || type == UInt || type == Char ||
            type == UChar || type == Short ||
            type == UShort || type == SHA256;
}

bool NetworkClasses::isReal(NetworkClasses::Type type) {
    return type == Float || type == UFloat || type == Double ||
            type == UDouble;
}

bool NetworkClasses::isString(NetworkClasses::Type type) {
    return type == String;
}

bool NetworkClasses::isArray(NetworkClasses::Type type) {
    return type & Array;
}

bool NetworkClasses::isVariant(NetworkClasses::Type type) {
    return type == Variant;
}

unsigned int NetworkClasses::getSizeType(NetworkClasses::Type type) {
    switch (type) {
    case Char:
    case UChar: return sizeof (char);
    case Short:
    case UShort: return sizeof(short);
    case Int:
    case UInt: return sizeof(int);
    case Float:
    case UFloat: return sizeof (float);
    case Double:
    case UDouble: return sizeof (double);
    case SHA256: return 32;
    default: return 0;
    }
}

void NetworkClasses::byteCast(NetworkClasses::Type type,
                              const QVariant& item,
                              QByteArray& res) {
    res.clear();

    const void* data = item.data();
    res.append(reinterpret_cast<char*>(&data),
               static_cast<int>(getSizeType(type)));

}

}

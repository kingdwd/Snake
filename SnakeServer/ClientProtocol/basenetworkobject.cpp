#include "basenetworkobject.h"

namespace ClientProtocol {



int BaseNetworkObject::id() const {
    return _id;
}

void BaseNetworkObject::setId(int id) {
    _id = id;
}

qint8 BaseNetworkObject::class() const
{
    return _class;
}

BaseNetworkObject::BaseNetworkObject() {

}

BaseNetworkObject *BaseNetworkObject::create() const {
    return new BaseNetworkObject();
}

BaseNetworkObject::~BaseNetworkObject() {

}

NetworkClassSize BaseNetworkObject::classSize() const {
    return sizeof(_id) + sizeof (_class);
}

QDataStream &BaseNetworkObject::writeToStream(QDataStream &stream) const {
    stream << _class;
    stream << _id;
    return stream;
}

QDataStream &BaseNetworkObject::readFromStream(QDataStream &stream) {
    stream >> _class;
    stream >> _id;
    return stream;
}
}

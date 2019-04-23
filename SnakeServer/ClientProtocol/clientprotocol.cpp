#include "clientprotocol.h"
#include "gamedata.h"
#include "getitem.h"
#include "login.h"
#include "updateplayerdata.h"

#include <QDataStream>
#include <QVariantMap>
#include <factorynetobjects.h>

#define DEFAULT_GAME_PORT 7777

namespace ClientProtocol {


Header::Header() {
    reset();
}

bool Header::isValid() const {

    if (sizeof (*this) != 4) {
        return false;
    }

    return isValidSize(command, size);
}

void Header::reset() {
    size = 0;
    command = Undefined;
    type = Responke;
}

Package::Package() {
    reset();
}

bool Package::isValid() const {
    if (!hdr.isValid()) {
        return false;
    }

    if (data.size() && hdr.command != data.at(0)) {
        return false;
    }

    return hdr.size == static_cast<unsigned int> (data.size());
}

bool Package::parse(BaseNetworkObject** res) const {
    if (!isValid())
        return false;

    auto obj = FactoryNetObjects::build(hdr.command);

    QDataStream stream(data);
    obj->readFromStream(stream);
    *res = obj;

    return true;
}


bool Package::create(const BaseNetworkObject *obj, Type type) {

    if (!obj) {
        return false;
    }

    auto command = obj->getClass();

    if (command < 0) {
        return false;
    }

    QDataStream stream(&data, QIODevice::ReadWrite);
    obj->writeToStream(stream);

    hdr.command = static_cast<quint8>(command);
    hdr.type = type;
    hdr.size = static_cast<unsigned int>(data.size());

    return isValid();
}

bool Package::create(Command cmd, Type type) {


    if (cmd == Command::Undefined) {
        return false;
    }

    hdr.command = static_cast<quint8>(cmd);
    hdr.type = type;
    hdr.size = static_cast<unsigned int>(data.size());

    return isValid();
}

QByteArray Package::toBytes() const {
    QByteArray res;
    res.append(reinterpret_cast<char*>(const_cast<Header*>(&hdr)),
               sizeof (hdr));

    res.append(data);
    return res;
}

void Package::reset() {
    hdr.reset();
    data.clear();
}

bool isValidSize(quint8 type, unsigned int size) {

    if (!FactoryNetObjects::isRegisteredType(type)) {
        return false;
    }

    return FactoryNetObjects::getSize(type).isValid(size);
}

bool initClientProtockol() {
    if (!FactoryNetObjects::regType<Login>(
                static_cast<quint8>(Command::Login))) {
        return false;
    }

    if (!FactoryNetObjects::regType<UpdatePlayerData>(
                static_cast<quint8>(Command::UpdatePlayerData))) {
        return false;
    }

    if (!FactoryNetObjects::regType<GameData>(
                static_cast<quint8>(Command::GameData))) {
        return false;
    }

    if (!FactoryNetObjects::regType<GetItem>(
                static_cast<quint8>(Command::GetItem))) {
        return false;
    }
    return true;
}

}

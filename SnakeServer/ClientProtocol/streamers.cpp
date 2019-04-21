#include "streamers.h"

#include <QDataStream>
#include "networkobjects.h"
#include <QMap>
#include <QVariant>
#include <QVariantMap>

namespace ClientProtocol {


NetworkClasses::Type Streamers::baseRead(QDataStream &stream, QVariantMap &map,
                                     const NetworkClasses::Type checkType) {
    unsigned short command;
    int id;

    stream >> id;
    stream >> command;

    map["command"] = command;
    map["id"] = id;

    return static_cast<NetworkClasses::Type>(command & checkType);
}

NetworkClasses::Type Streamers::baseWrite(QDataStream &stream, const QVariantMap &map) {
    unsigned short command = static_cast<unsigned short>(map.value("command").toUInt());
    int id = map.value("id").toInt();

    stream << id;
    stream << command;

    return static_cast<NetworkClasses::Type>(command & NetworkClasses::CustomType);
}

bool Streamers::read(QDataStream &stream, QVariantMap &map, const NetworkClasses::Type checkType) {
    auto type = baseRead(stream, map, checkType);
    if (!type) {
        return false;
    }

    auto parseRules = networkObjects.value(type);

    for (auto iter = parseRules.begin(); iter != parseRules.end(); ++iter) {

        auto property = iter.key();
        auto typeItem = iter.value();

        if (NetworkClasses::isNumber(typeItem)) {

            int size = static_cast<int> (NetworkClasses::getSizeType(typeItem));

            if (!size)
                return false;

            char *data = new char[static_cast<unsigned int>(size)];
            if (size != stream.readRawData(data, size)) {
                return false;
            }

            map.insert(property, QVariant::fromValue(QByteArray(data, size)));

        }
        else if (NetworkClasses::isString(typeItem)) {
            QStringList val;
            stream >> val;
            map.insert(property, val);

        }
        else if (NetworkClasses::isArray(typeItem)) {
            NetworkClasses::Type arrayType = static_cast<NetworkClasses::Type>(typeItem & ~NetworkClasses::Array);

            if (NetworkClasses::isString(arrayType)) {
                QStringList list;
                stream >> list;
                map.insert(property, list);

            } else {

                QByteArray array;
                stream >> array;

                QVariantList varList;

                auto size = static_cast<int>(NetworkClasses::getSizeType(arrayType));
                for (int i = 0; i < array.size(); i+= size) {
                    varList.push_back(QVariant::fromValue(array.mid(i, size)));
                }
                map.insert(property, varList);
            }
        }
    }

    return true;
}

bool Streamers::read(const QByteArray &data, QVariantMap &map) {
    QDataStream stream(data);
    return read(stream, map);
}

bool Streamers::readNumber(NetworkClasses::Type type, QVariant &value, QDataStream &stream) {

    int size = static_cast<int> (NetworkClasses::getSizeType(type));

    if (!size)
        return false;

    char *data = new char[static_cast<unsigned int>(size)];
    if (size != stream.readRawData(data, size)) {
        return false;
    }

    value = QVariant::fromValue(QByteArray(data, size));
    return value.isValid();
}

bool Streamers::write(QDataStream &stream, const QVariantMap &map) {

    auto type = baseWrite(stream, map);
    if (!type) {
        return false;
    }

    auto parseRules = networkObjects.value(type);

    for (auto iter = parseRules.begin(); iter != parseRules.end(); ++iter) {
        auto property = iter.key();
        auto typeItem = iter.value();
        auto value = map.value(property);

        if (NetworkClasses::isNumber(typeItem)) {

            QByteArray val;
            NetworkClasses::byteCast(typeItem, value, val);

            auto size = val.size();

            if (size != stream.writeRawData(static_cast<char*>(val.data()), size)) {
                return false;
            }
        }
        else if (NetworkClasses::isString(typeItem)) {
            stream << value.toString();
        }
        else if (NetworkClasses::isArray(typeItem)) {
            NetworkClasses::Type arrayType = static_cast<NetworkClasses::Type>(typeItem & ~NetworkClasses::Array);

            if (NetworkClasses::isString(arrayType)) {
                stream << value.toStringList();
            } else {

                QByteArray array;
                auto varList = value.toList();
                for (auto &&i : varList) {
                    QByteArray val;
                    NetworkClasses::byteCast(arrayType, i, val);
                    array.append(val);
                }
                stream << array;
            }
        }
    }

    return true;
}

bool Streamers::write(QByteArray &data, const QVariantMap &map) {
    QDataStream stream(&data, QIODevice::WriteOnly);

    return write(stream, map);
}

bool Streamers::writeNumber(NetworkClasses::Type type, const QVariant & value, QDataStream& stream) {
    QByteArray val;
    NetworkClasses::byteCast(type, value, val);

    auto size = val.size();

    if (size != stream.writeRawData(static_cast<char*>(val.data()), size)) {
        return false;
    }

    return true;
}
}

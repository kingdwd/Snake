#include "gamedata.h"
#include "config.h"


namespace ClientProtocol {

GameData::GameData()
{

}

QList<int> GameData::getTimeClick() const {
    return timeClick;
}

void GameData::setTimeClick(const QList<int> &value) {
    timeClick = value;
}

int& GameData::operator[](int index) {
    return timeClick[index];
}

BaseNetworkObject *GameData::create() const {
    return new GameData();
}

NetworkClassSize GameData::classSize() const {
    auto size = UpdatePlayerData::classSize();

    return NetworkClassSize(size.min + 4, size.max + 4 + 2 * MAX_SIZE);
}

QDataStream &GameData::writeToStream(QDataStream &stream) const {
    UpdatePlayerData::writeToStream(stream);
    stream << timeClick;
    return stream;
}

QDataStream &GameData::readFromStream(QDataStream &stream) {
    UpdatePlayerData::readFromStream(stream);
    stream >> timeClick;
    return stream;
}

}

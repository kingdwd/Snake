#include "player.h"
#include "config.h"

namespace ClientProtocol {


QString Player::getName() const
{
    return name;
}

void Player::setName(const QString &value)
{
    name = value;
}

QString Player::getGmail() const
{
    return gmail;
}

void Player::setGmail(const QString &value)
{
    gmail = value;
}

unsigned int Player::getMany() const
{
    return many;
}

void Player::setMany(unsigned int value)
{
    many = value;
}

unsigned int Player::getRecord() const
{
    return record;
}

void Player::setRecord(unsigned int value)
{
    record = value;
}

QList<int> Player::getItems() const
{
    return items;
}

void Player::setItems(const QList<int> &value)
{
    items = value;
}

int Player::getCureentSnake() const
{
    return cureentSnake;
}

void Player::setCureentSnake(int value)
{
    cureentSnake = value;
}


Player::Player()
{

}

BaseNetworkObject *Player::create() const {
    return new Player();
}

NetworkClassSize Player::classSize() const {
    auto size = UpdatePlayerData::classSize();

    return NetworkClassSize(size.min + 4, size.max + 4 + 2 * MAX_SIZE);
}

QDataStream &Player::writeToStream(QDataStream &stream) const {
    UpdatePlayerData::writeToStream(stream);
    stream << timeClick;
    return stream;
}

QDataStream &Player::readFromStream(QDataStream &stream) {
    UpdatePlayerData::readFromStream(stream);
    stream >> timeClick;
    return stream;
}
}

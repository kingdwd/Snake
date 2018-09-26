#include "itemworld.h"
#include <cmath>
#include <QDateTime>

double ItemWorld::getX() const
{
    return x;
}

void ItemWorld::setX(double value)
{
    x = value;
}

double ItemWorld::getY() const
{
    return y;
}

void ItemWorld::setY(double value)
{
    y = value;
}

void ItemWorld::render(){
    qint64 tempTime = QDateTime::currentMSecsSinceEpoch() - time;
    double mx = x + *speed;
    x += (mx - x) / 1000 * tempTime;
    time = QDateTime::currentMSecsSinceEpoch();
}

QString *ItemWorld::getTexture() const
{
    return texture;
}

void ItemWorld::setTexture(QString *value)
{
    texture = value;
}

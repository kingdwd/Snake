#include "snake.h"
#include "guiobject.h"

#include <QDateTime>
#include <QMap>
#include <QRectF>
#include <cmath>

Snake::Snake() {
}

const QVector<Head *> &Snake::getItems() const {
    return items;
}

void Snake::render() {

    auto centerX = [](const Head* head) {
        return head->x()/* + (head->w() / 2)*/;
    };

    auto centerY = [](const Head* head) {
        return head->y() /*+ (head->h() / 2)*/;
    };

    for (int i = items.length() - 1; i >= 0; --i) {

        if (dead) {
            items[i]->render();
            continue;
        }

        if (i == 0) {
            if (isClick) {
                if (countClick & 1){
                    items[i]->setAngle(45);
                } else {
                    items[i]->setAngle(315);
                }
                isClick = false;
            }
        } else  {

            double _atan2 = atan2(centerY(items[i - 1]) - centerY(items[i]),
                    centerX(items[i - 1]) - centerX(items[i])) * 90;

            items[i]->setAngle(_atan2);
        }

        items[i]->render();
    }
}

double Snake::checDistance(int i) {

    auto result = (items[i]->rect().y() -
    items[i - 1]->rect().y()) / rataticonDistance;

    return result;

}

double Snake::getRataticonDistance() const {
    return rataticonDistance;
}

void Snake::setRataticonDistance(double value) {
    rataticonDistance = value;
}

void Snake::unPause() {
    for ( int i = 0; i < items.size(); ++i ) {
        items[i]->unPause();
    }
}

double Snake::sizeByLvl(double lvl , int count) const {
    double maxSize = 9;
    double minSize = 5;

    double pos = (1 - (lvl / count));

    QList<QPair<double, double>> snakeGradientSize {
        {1, 4},
        {0.99, 7},
        {0.8, 5},
        {0.6, 6},
        {0.0, 3}
    };

    double local = 0;
    int index = 0;

    while (index + 1 < snakeGradientSize.size()
           && pos <= snakeGradientSize[index].first) {

        maxSize = snakeGradientSize[index].second;
        minSize = snakeGradientSize[index + 1].second;

        auto range = snakeGradientSize[index].first -
                snakeGradientSize[index + 1].first;

        local = ( range - (snakeGradientSize[index].first - pos)) /
                   range;

        index++;
    }

    return local * (maxSize - minSize) + minSize;
}

void Snake::changeCountObjects(int count) {
    if (count > 0) {
        double margin = 60.0 / count;
        for ( int i = 0; i < count; ++i ) {

            auto size = sizeByLvl(i, count);
            auto obj = new Head(margin * (count - i),
                                50, size , size,
                                this->speed);

            obj->setY(50 + obj->h() / 2);

            items.push_back(obj);
        }

    } else {
        for ( int i = count; i < 0; ++i ) {
            auto obj = items.first();
            items.removeFirst();
            delete obj;
        }
    }
}

QMap<int, GuiObject*> Snake::init(int size, double *speed) {

    QMap<int, GuiObject*> res;

    if (size <= 0) {
        return res;
    }

    this->speed = speed;

    changeCountObjects(size - items.size());

    for (auto i : items) {
        res[i->guiId()] = i;
    }

    dead = false;

    return res;
}

bool Snake::isInited() const {
    return items.size();
}

void Snake::clearItems() {
    for (auto i : items) {
        delete i;
    }
    items.clear();
}

void Snake::resetPosotion() {
    double margin = 60.0 / items.size();

    for ( int i = 0; i < items.size(); ++i ) {
        items[i]->setX(margin * (items.size() - i));
        items[i]->setY(50 + items[i]->h() / 2);
        items[i]->setAngle(0);
    }
}

void Snake::kill() {
    dead = true;
}

bool Snake::isDead() const {
    return dead;
}

Snake::~Snake() {
    clearItems();
}

void Snake::clear() {
    clearItems();
}

void Snake::reverse() {
    if (isClick) {
        return;
    }
    isClick = true;
    countClick++;
}

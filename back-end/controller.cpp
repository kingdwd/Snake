#include "controller.h"
#include <cmath>
#include <ctime>
#include "diff.h"
#include "lvls.h"

Controller::Controller() {
    srand(static_cast<unsigned int>(time(nullptr)));
    timer = new QTimer();
    timer->setInterval(33);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
}

bool Controller::nextLvl() {
    if (lvl + 1 >= lvls.size()) {
        return true;
    }

    generateDiff(world.init(lvls.value(++lvl)));


    return false;
}

void Controller::generateDiff(const QMap<int, GuiObject *>& objs) {


    auto removeIds = objectsContainer.keys();
    QList<int> addedIds;

    for (auto i = objs.begin(); i != objs.end(); ++i) {
        if (objectsContainer.contains(i.key())) {
            removeIds.removeOne(i.key());
        } else {
            objectsContainer.insert(i.key(), i.value());
            addedIds.push_back(i.key());
        }
    }

    if (removeIds.size() || addedIds.size()) {
        Diff diff;

        diff.setRemoveIds(removeIds);
        diff.setAddedIds(addedIds);
        emit gameObjectsChanged(diff);
    }
}

void Controller::update() {
    world.render();
    if(world.isDefiat()) {
        stopTimer();
    }
}

void Controller::newGame() {
    WorldRules newGameRules = lvls.first();
    lvl = 0;
    generateDiff(world.init(newGameRules));
    startTimer();
}

QObject *Controller::getGameObject(int id) {
    return objectsContainer.value(id, nullptr);
}

void Controller::startTimer() {
    timer->start();
}

void Controller::stopTimer() {
    timer->stop();
}

void Controller::buttonPress() {
    world.reversClick();
}


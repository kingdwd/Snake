#include "testutils.h"

#include <QCoreApplication>
#include <QDateTime>

TestUtils::TestUtils()
{

}

bool TestUtils::wait(const bool &forWait, int msec) {
    auto curmsec = QDateTime::currentMSecsSinceEpoch() + msec;
    while (curmsec > QDateTime::currentMSecsSinceEpoch() && !forWait) {
        QCoreApplication::processEvents();
    }
    QCoreApplication::processEvents();
    return forWait;
}

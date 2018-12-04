#include "localrecords.h"

#include <QDataStream>
#include <QDir>
#include <QFile>

void LocalRecords::save() {
    auto path = QDir::homePath() + "/snake/snake.records";
    QFile file(path);

    if (file.open(QIODevice::WriteOnly)) {
        QDataStream stream(&file);
        stream << m_records;
        file.close();
    }
}

void LocalRecords::load() {
    auto path = QDir::homePath() + "/snake/snake.records";
    QFile file(path);

    if (file.open(QIODevice::ReadOnly)) {
        QDataStream stream(&file);
        stream >> m_records;
        file.close();
    }
}

LocalRecords::LocalRecords() {
    load();
}

LocalRecords::~LocalRecords() {
    save();
}

QStringList LocalRecords::records() const {
    return m_records;
}

void LocalRecords::append(const QString &name, int points) {
    if (name.isEmpty()) return;

    m_records.push_back(QString(" %0:%1 ").arg(name).arg(points));
    emit recordsChanged(m_records);

}

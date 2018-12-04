#ifndef LOCALRECORDS_H
#define LOCALRECORDS_H

#include <QObject>


class LocalRecords: public QObject
{
    Q_OBJECT

    Q_PROPERTY( QStringList records READ records NOTIFY recordsChanged)

private:
    QStringList m_records;

    void save();
    void load();

public:
    LocalRecords();
    ~LocalRecords();
    QStringList records() const;

public slots:
    void append(const QString& name, int points);
signals:
    void recordsChanged(QStringList records);
};

#endif // LOCALRECORDS_H

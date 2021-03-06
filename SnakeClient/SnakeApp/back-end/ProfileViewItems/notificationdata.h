#ifndef NOTIFICATIONDATA_H
#define NOTIFICATIONDATA_H
#include <QObject>

class NotificationData
{
    Q_GADGET
    Q_PROPERTY(QString text READ text)
    Q_PROPERTY(QString img READ img)
    Q_PROPERTY(QString title READ title)
    Q_PROPERTY(int type READ type)

    QString _text;
    QString _img;
    QString _title;
    int _type;

public:

    enum Type {
        Normal,
        Warning = 1,
        Error = 2,
    };

    explicit NotificationData(const QString& title = "",
                              const QString& text = "",
                              const QString& img = "",
                              Type type = Type::Normal);

    Q_INVOKABLE QString text() const;
    Q_INVOKABLE QString img() const;
    Q_INVOKABLE QString title() const;
    Q_INVOKABLE int type() const;

    bool operator ==(const NotificationData &righ);
    bool operator !=(const NotificationData &righ);

};

#endif // NOTIFICATIONDATA_H

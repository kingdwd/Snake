#include "notificationdata.h"

NotificationData::NotificationData(const QString &title,
                                   const QString &text,
                                   const QString &img, Type type) {

    _text = text;
    _title = title;
    _img = img;
    _type = type;
}

QString NotificationData::text() const {
    return _text;
}

QString NotificationData::img() const {
    return _img;
}

QString NotificationData::title() const {
    return _title;
}

bool NotificationData::operator ==(const NotificationData &righ) {
    return _title == righ._title &&
            _text == righ._text &&
            _img == righ._img &&
            _type == righ._type;
}

bool NotificationData::operator !=(const NotificationData &righ) {
    return !operator==(righ);
}

int NotificationData::type() const {
    return _type;
}

#ifndef BASENETWORKOBJECT_H
#define BASENETWORKOBJECT_H

#include "networkclasssize.h"

#include <cstdlib>
#include <QDataStream>
namespace ClientProtocol {



class BaseNetworkObject
{
private:
    int _id = -1;
    qint8 _class = -1;
protected:

    BaseNetworkObject();

public:
    virtual BaseNetworkObject* create() const;
    virtual ~BaseNetworkObject();

    virtual NetworkClassSize classSize() const;
    virtual QDataStream& writeToStream(QDataStream& stream) const;
    virtual QDataStream& readFromStream(QDataStream& stream);
    int id() const;
    void setId(int id);
    qint8 getClass() const;
};

}
#endif // BASENETWORKOBJECT_H

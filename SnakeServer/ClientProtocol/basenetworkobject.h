#ifndef BASENETWORKOBJECT_H
#define BASENETWORKOBJECT_H

#include <cstdlib>

class BaseNetworkObject
{
private:
    int _id = -1;
    size_t _type;

public:
    BaseNetworkObject();
};

#endif // BASENETWORKOBJECT_H

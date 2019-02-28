#ifndef NETWORKCLASSES_H
#define NETWORKCLASSES_H
#include "clientprotocol_global.h"

namespace ClientProtocol {


class CLIENTPROTOCOLSHARED_EXPORT NetworkClasses
{

public:
    enum Type: unsigned short {
        Undefined = 0x00,

        // base types
        Char =      0x01,
        UChar =     0x02,
        Short =     0x03,
        UShort =    0x04,
        Int =       0x05,
        UInt =      0x06,
        Float =     0x07,
        UFloat =    0x08,
        Double =    0x09,
        UDouble =   0x0a,
        String =    0x0b,
        Variant =   0x0c,
        SHA256 =    0x0d,

        // baseArray
        Array =     0x80,

        ArrayChar =     Array | Char,
        ArrayUChar =    Array | UChar,
        ArrayShort =    Array | Short,
        ArrayUShort =   Array | UShort,
        ArrayInt =      Array | Int,
        ArrayUInt =     Array | UInt,
        ArrayFloat =    Array | Float,
        ArrayUfloat =   Array | UFloat,
        ArrayDouble =   Array | Double,
        ArrayUDouble =  Array | UDouble,
        ArrayString =   Array | String,
        ArrayVariant =  Array | Variant,

        BaseType = 0x00FF,

        // custom types
        Snake =     0x0100,
        Player =    0x0200,
        Map    =    0x0300,
        Game   =    0x0400,

        // general objects
        GeneralObject = 0x8000,

        CustomType = 0xFF00,

    };

    static bool isInteger(Type);
    static bool isReal(Type);
    static bool isString(Type);
    static bool isArray(Type);
    static bool isVariant(Type);
    static bool isNumber(Type);
    static bool isStream(Type);

    static int getSizeType(Type);
    NetworkClasses();
};
}
#endif // NETWORKCLASSES_H

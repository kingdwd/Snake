#ifndef NETWORKCLASSSIZE_H
#define NETWORKCLASSSIZE_H

namespace ClientProtocol {
struct NetworkClassSize {
    unsigned int min = 0;
    unsigned int max = 0;

    bool isStaticType();

    NetworkClassSize(unsigned int size);
    NetworkClassSize& operator = (unsigned int size);
    bool isValid(unsigned int size) const;
};
}



#endif // NETWORKCLASSSIZE_H

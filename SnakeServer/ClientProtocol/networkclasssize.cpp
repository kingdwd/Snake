#include "networkclasssize.h"

namespace ClientProtocol {

bool NetworkClassSize::isStaticType() {
    return min == max;
}

NetworkClassSize::NetworkClassSize(unsigned int size) {
    operator=(size);
}

NetworkClassSize::NetworkClassSize(unsigned int min, unsigned int maxDif) {
    operator=(min);
    max += maxDif;
}

NetworkClassSize &NetworkClassSize::operator =(unsigned int size) {
    min = max = size;
    return *this;
}

bool NetworkClassSize::isValid(unsigned int size) const {
    return size <= max && size >= min;
}
}

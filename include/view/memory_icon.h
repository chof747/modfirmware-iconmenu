#ifndef MODFIRMWARE_MEMORYICON_H
#define MODFIRMWARE_MEMORYICON_H

#include "icon.h"
#include <stdexcept>
#include <cstring>

namespace ModFirmWare {

class MemoryIcon : public Icon {
public:
    MemoryIcon(uint16_t width, uint16_t height, const uint8_t* bitmap);

    virtual const uint8_t* getBitmap() const override {
        return bitmap;
    }

private:
    const uint8_t* bitmap;
};

} // namespace ModFirmWare

#endif // MODFIRMWARE_MEMORYICON_H
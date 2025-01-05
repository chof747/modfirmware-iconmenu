#ifndef MODFIRMWARE_FILESYSTEMICON_H
#define MODFIRMWARE_FILESYSTEMICON_H

#include "icon.h"
#include <memory>

namespace ModFirmWare
{

  class FileIcon : public Icon
  {
  public:
    FileIcon(uint16_t width, uint16_t height, const char *filepath);

    virtual const uint8_t *getBitmap() const override { return bitmap.get(); }

  private:
    void loadBitmap();

    const char *filepath;
    std::unique_ptr<uint8_t[]> bitmap;
  };

}

#endif // MODFIRMWARE_FILESYSTEMICON_H

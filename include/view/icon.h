#ifndef MODFIRMWARE_ICON_H
#define MODFIRMWARE_ICON_H

#include <stdint.h>
#include <memory>

namespace ModFirmWare
{

  class Icon
  {
  public:
    Icon(uint16_t width, uint16_t height);
    virtual ~Icon();

    // Pure virtual method that provides a read-only pointer to the original bitmap
    virtual const uint8_t *getBitmap() const = 0;

    // Method to get a pointer to the inverted bitmap
    const uint8_t *getInverted();

    uint16_t width() const;
    uint16_t height() const;

  protected:
    // Method to generate the inverted bitmap (lazy initialization)
    void generateInvertedBitmap();

  private:
    uint16_t width_;
    uint16_t height_;
    std::unique_ptr<uint8_t[]> inverted_bitmap;
  };

} // namespace ModFirmWare

#endif // MODFIRMWARE_ICON_H

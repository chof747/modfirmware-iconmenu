#include "view/icon.h"

#include <stdint.h>
#include <memory>

using namespace ModFirmWare;

#define LOGTAG "view/icon"

Icon::Icon(uint16_t width, uint16_t height)
    //****************************************************************************************
    : width_(width), height_(height), inverted_bitmap(nullptr), logger(LogEngine::getInstance())
{
}

Icon::~Icon() = default;
//****************************************************************************************

uint16_t Icon::width() const
//****************************************************************************************
{
  return width_;
}

uint16_t Icon::height() const
//****************************************************************************************
{
  return height_;
}

const uint8_t *Icon::getInverted()
//****************************************************************************************
{
  if (!inverted_bitmap)
  {
    generateInvertedBitmap();
  }
  return inverted_bitmap.get();
}

bool Icon::validateBitmapSize(size_t bitmap_size) const
//****************************************************************************************
{
  size_t expected_size = (width() * height() + 7) / 8;
  if (bitmap_size < expected_size)
  {
    logger->error(LOGTAG, "Image for icon is not the expected size %d, but has size %d", expected_size, bitmap_size);
    return false;
  }
  return true;
}

void Icon::generateInvertedBitmap()
//****************************************************************************************
{
  if (nullptr != getBitmap())
  {
    size_t size = (width_ * height_ + 7) / 8; // Calculate the size in bytes, assuming 1 bit per pixel
    inverted_bitmap = std::unique_ptr<uint8_t[]>(new uint8_t[size]);
    const uint8_t *original_bitmap = getBitmap();
    for (size_t i = 0; i < size; ++i)
    {
      inverted_bitmap[i] = ~original_bitmap[i];
    }
  }
}

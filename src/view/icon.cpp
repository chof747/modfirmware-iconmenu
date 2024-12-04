#include "view/icon.h"

#include <stdint.h>
#include <memory>

using namespace ModFirmWare;

Icon::Icon(uint16_t width, uint16_t height)
//****************************************************************************************
    : width_(width), height_(height), inverted_bitmap(nullptr)
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

void Icon::generateInvertedBitmap()
//****************************************************************************************
{
  size_t size = (width_ * height_ + 7) / 8; // Calculate the size in bytes, assuming 1 bit per pixel
  inverted_bitmap = std::unique_ptr<uint8_t[]>(new uint8_t[size]);
  const uint8_t *original_bitmap = getBitmap();
  for (size_t i = 0; i < size; ++i)
  {
    inverted_bitmap[i] = ~original_bitmap[i];
  }
}

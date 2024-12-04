#include "view/memory_icon.h"


using namespace ModFirmWare;

MemoryIcon::MemoryIcon(uint16_t width, uint16_t height, const uint8_t *bitmap)
//****************************************************************************************
    : Icon(width, height), bitmap(bitmap)
{
  size_t expected_size = (width * height + 7) / 8;
  if (bitmap == nullptr)
  {
    throw std::invalid_argument("Bitmap pointer cannot be null");
  }
  if (expected_size > std::strlen(reinterpret_cast<const char *>(bitmap)))
  {
    throw std::invalid_argument("Bitmap size does not match the expected size for the given dimensions");
  }
}

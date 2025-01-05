#include "view/memory_icon.h"

using namespace ModFirmWare;

MemoryIcon::MemoryIcon(uint16_t width, uint16_t height, const uint8_t *bitmap)
//****************************************************************************************
    : Icon(width, height), bitmap(bitmap)
{
  if (!validateBitmapSize((width * height + 7) / 8))
  {
    bitmap = nullptr;
  }
}

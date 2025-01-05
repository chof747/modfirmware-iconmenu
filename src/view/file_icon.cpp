#include "view/file_icon.h"
#include <FS.h>
#include <SPIFFS.h>

using namespace ModFirmWare;

#define LOGTAG "view/fileicon"

FileIcon::FileIcon(uint16_t width, uint16_t height, const char *filepath)
    : Icon(width, height), filepath(filepath), bitmap(nullptr)
//****************************************************************************************
{
  loadBitmap();
}

void FileIcon::loadBitmap()
//****************************************************************************************
{
  if (!SPIFFS.begin())
  {
    logger->error(LOGTAG, "Failed to mount SPIFFS file system");
    return;
  }
  if (filepath == nullptr || strlen(filepath) == 0)
  {
    logger->error(LOGTAG, "File path is invalid or empty");
    return;
  }
  File file = SPIFFS.open(filepath, "r");
  if (!file)
  {
    logger->error(LOGTAG, "Failed to open bitmap file: %s", filepath);
    return;
  }

  size_t size = file.size();
  validateBitmapSize(size);

  file.seek(0, SeekSet);
  bitmap = std::unique_ptr<uint8_t[]>(new uint8_t[size]);
  if (file.read(bitmap.get(), size) != size)
  {
    logger->error(LOGTAG, "Failed to read bitmap data from file: %s", filepath);
  }
}

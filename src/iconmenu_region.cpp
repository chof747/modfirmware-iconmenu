#include "iconmenu_region.h"
#include "model/iconmenu_item.h"
#include "view/icon.h"

using namespace ModFirmWare;

#define LOGTAG "iconregion"

IconMenuRegion::IconMenuRegion(const window_t &window, TFTDisplay *display)
//********************************************************************************
    : DisplayRegion(window, display), iconWidth(32), iconHeight(32),
      iconMargin(5), captionMargin(5), paginationMargin(10),
      currentIndex(0), needsUpdate(false)
{
}

void IconMenuRegion::setIconSize(uint16_t width, uint16_t height)
//********************************************************************************
{
    iconWidth = width;
    iconHeight = height;
    needsUpdate = true;
}

void IconMenuRegion::setMargins(uint16_t iconMargin, uint16_t captionMargin, uint16_t paginationMargin)
//********************************************************************************
{
    this->iconMargin = iconMargin;
    this->captionMargin = captionMargin;
    this->paginationMargin = paginationMargin;
    needsUpdate = true;
}

void IconMenuRegion::setMenuItems(const std::vector<IconMenuItem *> &items)
//********************************************************************************
{
    menuItems = items;
    needsUpdate = true;
}

void IconMenuRegion::setCurrentIndex(size_t index)
//********************************************************************************
{
    if (currentIndex != index)
    {
        currentIndex = index;
        needsUpdate = true;
    }
}

void IconMenuRegion::updateCanvas()
//********************************************************************************
{
    if (!needsUpdate)
        return;

    auto* gfx = display();
    gfx->fillScreen(0); // Clear screen

    // Determine font height (assume 8 pixels if not using a custom font)
    int fontHeight = getTextHeight("A");

    // Calculate the height of each row (icon + caption + margin)
    int rowHeight = iconHeight + captionMargin * 2 + fontHeight;

    // Calculate grid dimensions
    size_t cols = (width() - iconMargin) / (iconWidth + iconMargin);
    size_t rows = (rowHeight !=0) ? height() / rowHeight : 1;
    size_t itemsPerPage = cols * rows;

    logger->debug(LOGTAG, "width = %d, height = %d", width(), height());
    logger->debug(LOGTAG, "iconWidth = %d, iconHeight = %d", iconWidth, iconHeight);
    logger->debug(LOGTAG, "iconMargin = %d, fontHeight = %d, captionMargin = %d", iconMargin, fontHeight, captionMargin);
    logger->debug(LOGTAG, "cols = %d, rows = %d", cols, rows);
    logger->debug(LOGTAG, "itemsperpage = %d", itemsPerPage);

    // Calculate current page
    size_t currentPage = (itemsPerPage != 0) ? currentIndex / itemsPerPage : 0;
    size_t totalPages = (itemsPerPage != 0) ? (menuItems.size() + itemsPerPage - 1) / itemsPerPage : 1;

    // Render icons and captions for the current page
    size_t startIndex = currentPage * itemsPerPage;
    for (size_t i = 0; i < itemsPerPage; ++i)
    {
        size_t itemIndex = startIndex + i;
        if (itemIndex >= menuItems.size())
            break;

        size_t col = i % cols;
        size_t row = i / cols;

        int x = iconMargin + col * (iconWidth + iconMargin);
        int y = captionMargin + row * rowHeight;

        logger->debug(LOGTAG, "item = %s, index = %d, col = %d, row= %d, x = %d, y = %d",
          menuItems[itemIndex]->getCaption(), i, col, row, x, y);

        // Draw the icon
        const uint8_t* bitmap = (itemIndex == currentIndex)
                                    ? menuItems[itemIndex]->getIcon()->getInverted() // Selected icon inverted
                                    : menuItems[itemIndex]->getIcon()->getBitmap();
        gfx->drawBitmap(x, y, bitmap, iconWidth, iconHeight, 0xFFFF);

        // Draw the caption
        gfx->setCursor(x, y + iconHeight + captionMargin);
        gfx->print(menuItems[itemIndex]->getCaption());
    }

    // Draw pagination
    drawPagination(currentPage, totalPages);

    // Reset the needsUpdate flag after drawing
    needsUpdate = false;
}

void IconMenuRegion::drawPagination(size_t pageIndex, size_t totalPages)
//********************************************************************************
{
    auto *gfx = display();
    int dotRadius = 3;
    int dotSpacing = 2 * dotRadius + 5;
    int startX = (width() - (dotSpacing * totalPages)) / 2;
    int y = height() - paginationMargin;

    for (size_t i = 0; i < totalPages; ++i)
    {
        int x = startX + i * dotSpacing;
        if (i == pageIndex)
            gfx->fillCircle(x, y, dotRadius, 1); // Filled circle for current page
        else
            gfx->drawCircle(x, y, dotRadius, 1); // Empty circle for other pages
    }
}

bool IconMenuRegion::isUpdated() const
//********************************************************************************
{
    return needsUpdate;
}

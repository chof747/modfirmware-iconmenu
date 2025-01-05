#ifndef ICONMENU_REGION_H
#define ICONMENU_REGION_H

#include "display_region.h"
#include "view/icon.h" // Fixed include path

namespace ModFirmWare
{
    class IconMenuItem; // Forward declaration

    class IconMenuRegion : public DisplayRegion
    {
    public:
        IconMenuRegion(const window_t &window, TFTDisplay *display);

        void setIconSize(uint16_t width, uint16_t height);
        void setMargins(uint16_t iconMargin, uint16_t captionMargin, uint16_t paginationMargin);

        void setMenuItems(const std::vector<IconMenuItem *> &items); // Set menu items to render
        void setCurrentIndex(size_t index);                          // Update the current selection index

    protected:
        void updateCanvas() override;

        bool isUpdated() const override; // Implemented to resolve abstract class issue

    private:
        uint16_t iconWidth;
        uint16_t iconHeight;
        uint16_t iconMargin;
        uint16_t captionMargin;
        uint16_t paginationMargin;

        size_t currentIndex;                   // Currently selected item index
        bool needsUpdate;                      // Tracks whether a refresh is needed
        std::vector<IconMenuItem *> menuItems; // All menu items

        void drawPagination(size_t pageIndex, size_t totalPages); // Draw pagination indicators
    };
}

#endif // ICONMENU_REGION_H

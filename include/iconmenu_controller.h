#ifndef ICONMENU_CONTROLLER_H
#define ICONMENU_CONTROLLER_H

#include <vector>
#include "idleablecontroller.h"
#include "model/iconmenu_item.h"
#include "display_region.h"

namespace ModFirmWare
{
    class RotaryEncoder;
    class GPIOButton;
    class IconMenuRegion;
    class TFTDisplay;

    class IconMenuController : public IdleableController
    {
    public:
        IconMenuController(RotaryEncoder* encoder, GPIOButton* encoderButton, GPIOButton* backButton, 
                           TFTDisplay* display, DisplayRegion::window_t window, Controller* idleController);

        void activate() override;
        void loop() override;
        void deactivate() override;

        void addMenuItem(IconMenuItem* item); 
        void addMenuItem(IconMenuItem* item, Controller* controller);
        void setDimensions(uint16_t iconWidth, uint16_t iconHeight, uint16_t iconMargin, uint16_t captionMargin, uint16_t paginationMargin);

    private:
        RotaryEncoder* encoder;
        GPIOButton* encoderButton;
        GPIOButton* backButton;
        IconMenuRegion* region;
        TFTDisplay* display;

        std::vector<IconMenuItem*> menuItems; // List of menu items
        size_t currentIndex; // Current selected item index

        void highlightCurrentItem(); // Highlight the current item
        void selectCurrentItem();    // Activate the selected item
        void attachControls();
    };
}

#endif // ICONMENU_CONTROLLER_H

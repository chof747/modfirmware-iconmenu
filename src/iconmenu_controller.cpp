#include "iconmenu_controller.h"
#include "iconmenu_region.h"
#include "roteryencoder.h"
#include "gpiobutton.h"
#include "tftdisplay.h"

using namespace ModFirmWare;

IconMenuController::IconMenuController(RotaryEncoder *encoder, GPIOButton *encoderButton, GPIOButton *backButton,
                                       TFTDisplay *display, DisplayRegion::window_t window, Controller *idleController)
    //********************************************************************************
    : IdleableController(idleController), display(display), // Pass idle controller
      encoder(encoder), encoderButton(encoderButton), backButton(backButton), currentIndex(0)
{
    region = new IconMenuRegion(window, display);
}

void IconMenuController::addMenuItem(IconMenuItem *item)
//********************************************************************************
{
    menuItems.push_back(item);
    region->setMenuItems(menuItems);
}

void IconMenuController::addMenuItem(IconMenuItem *item, Controller *controller)
//********************************************************************************
{
    item->assignController(controller);
    addMenuItem(item);
}

void ModFirmWare::IconMenuController::setDimensions(uint16_t iconWidth, uint16_t iconHeight,
                                                    uint16_t iconMargin, uint16_t captionMargin,
                                                    uint16_t paginationMargin)
//********************************************************************************
{
    region->setIconSize(iconWidth, iconHeight);
    region->setMargins(iconMargin, captionMargin, paginationMargin);
}

void IconMenuController::activate()
//********************************************************************************
{
    currentIndex = 0; // Reset to the first item
    display->registerRegion(region);
    highlightCurrentItem();

    attachControls();
    IdleableController::activate();
}

void IconMenuController::loop()
//********************************************************************************
{
    IdleableController::loop();
}

void IconMenuController::deactivate()
//********************************************************************************
{
    IdleableController::deactivate();
}

void IconMenuController::highlightCurrentItem()
//********************************************************************************
{
    if (!menuItems.empty())
    {
        region->setCurrentIndex(currentIndex);
    }
}

void IconMenuController::selectCurrentItem()
//********************************************************************************
{
    if (!menuItems.empty())
    {
        menuItems[currentIndex]->activate();
    }
}

void IconMenuController::attachControls()
//********************************************************************************
{
    // Encoder callbacks
    encoder->setOnClockwise([this](long counter)
                            {
        currentIndex = (currentIndex + 1) % menuItems.size();
        highlightCurrentItem(); 
        watchdog(); });
    encoder->setOnCounterClockwise([this](long counter)
                                   {
        currentIndex = (currentIndex == 0) ? menuItems.size() - 1 : currentIndex - 1;
        highlightCurrentItem();
        watchdog(); });

    // Button callbacks
    encoderButton->setButtonPressedCallBack([this](uint16_t state, Buttons::click_t type)
                                            { 
        watchdog();
        if (type == Buttons::SINGLE) selectCurrentItem(); });

    backButton->setButtonPressedCallBack([this](uint16_t state, Buttons::click_t type)
                                         {
        watchdog();
        if (type == Buttons::SINGLE) gotoPrev(); });
}

#include "model/iconmenu_item.h"
#include "controller.h"

using namespace ModFirmWare;

IconMenuItem::IconMenuItem(Icon* icon, const char* caption, Controller* controller)
//********************************************************************************
    : icon(icon), caption(caption), controller(controller)
{
}

void IconMenuItem::activate()
//********************************************************************************
{
    if (controller)
    {
        controller->activate(); // Activates the associated controller
    }
}

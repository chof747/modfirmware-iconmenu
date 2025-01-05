#ifndef ICONMENU_ITEM_H
#define ICONMENU_ITEM_H

#include "view/icon.h"

namespace ModFirmWare
{
    class Controller;

    class IconMenuItem
    {
    public:
        IconMenuItem(Icon* icon, const char* caption, Controller* controller);

        inline Icon* getIcon() const { return icon; }
        inline const char* getCaption() const { return caption; }
        void activate(); 

        inline void assignController(Controller* newController) { controller = newController; } 

    private:
        Icon* icon;
        const char* caption;
        Controller* controller;
    };
}

#endif // ICONMENU_ITEM_H

# IconMenu Library

A library that provides a menu with Icons for a small tftdisplay which can be controlled with a rotary encoder

## Features

### Display of Menu

The icon menu displays an array of n x m black and white (bitmap) icons with captions below, which together constitute a menu item. Key considerations include:

- Icon and Caption Layout:

  - The number of icons in a row and column is determined by:
  - Icon width and height (set during menu setup by the user).
  - Caption height (set during menu setup by the user).
  - Configurable margins between:
    - Icons.
    - Icons and their captions.
    - Pagination indicators at the bottom (if used).

- Pagination Support:

  - Pagination indicators (dots at the bottom) are displayed when there are more menu items than can fit on one screen.
  - Margins at the bottom are adjusted to accommodate these indicators.

- Dynamic Display Dimensions:

  - The menu is provided a pointer to the display object (descendant of Adafruit_ST7735).
  - Display dimensions (width and height) are queried dynamically using the display object’s API.

### Navigation

- Rotary Encoder:
  - Navigation through menu items is handled by a rotary encoder.
  - Clockwise and counterclockwise turns move through the menu items.
  - The currently active menu item is visually highlighted by inverting the icon’s colors.
- Selection:
  - Clicking the rotary encoder button selects the current menu item.
  - A reference to a class that handles the rotary encoder is provided to the menu.
- Back Navigation:
  - A separate back button skips back to the previous screen/controller.
  - A reference to a class that handles the back button is provided to the menu.

### Pagination

- When more items exist than can be displayed on one screen:
  - Paging Logic:
    - When navigating forward past the last item on the current screen, the next page is displayed.
    - Conversely, navigating backward past the first item returns to the previous page.
  - Looping Behavior:
  - After the last page, the menu loops back to the first page.
  - Before the first page, the menu loops back to the last page.
- Pagination Indicators:
  - Small circles at the bottom of the screen.
  - The active page is shown as a filled circle; all others are empty circles.

### Selecting Menu Items

- When a menu item is selected:
  - The controller associated with the selected menu item is activated.
  - A reference to the controller class is provided to the menu.

### Configuration and Integration
- Icon Dimensions:
  - Width and height of icons are determined by the user during menu setup.
  - An Icon class is used to manage the bitmap data and provide an inverting function for highlighting.
- Default Margins:
  - Margins are initialized with default values and can be updated via setter methods.
- Integration with Framework:
  - The menu system integrates with the existing Model/View/Controller framework of ModFirmWare.


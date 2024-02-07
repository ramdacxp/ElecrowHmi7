// ----------------------------------------------------------------------------
// Elecrow HMI 7 display - Button
// ----------------------------------------------------------------------------

#pragma once

#include "HMI7LGFX.hpp"

class Button
{
private:
  LGFX &lcd;

public:
  uint16_t x = 10;
  uint16_t y = 10;
  uint16_t w = 200;
  uint16_t h = 100;
  uint8_t r = 10;
  String title;
  int fore = TFT_WHITE;
  int back = TFT_NAVY;

  // constructor(s)
  Button(LGFX &_lcd, uint16_t _x, uint16_t _y, String _title)
      : lcd(_lcd), x(_x), y(_y), title(_title)
  {
  }

  // methods
  void draw()
  {
    Serial.printf("Draw Button %d:%d %dx%d: %s", x, y, w, h, title);

    lcd.fillRoundRect(x, y, w, h, r, back);
    lcd.drawRoundRect(x, y, w, h, r, fore);

    lcd.setTextSize(1);
    lcd.setTextColor(fore, back);
    lcd.drawString(title, x + 10, y + 10, &fonts::Font4);
  }

  bool isHit(uint16_t _x, uint16_t _y)
  {
    return (_x >= x) && (_x <= x + w) && (_y > y) && (_y < y + h);
  }
};

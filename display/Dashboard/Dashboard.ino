// ----------------------------------------------------------------------------
// Elecrow HMI 7 display - Dashboard
// ----------------------------------------------------------------------------
// Board: ESP32S3 Dev Module
// Port: COM3 (or the one related to CH340G in device maganer)
// ----------------------------------------------------------------------------
// Tools > Partition Scheme: Huge APP (3MB No OTA/1MB SPIFFS)
// Tools > PSRAM: OPI PSRAM
// ----------------------------------------------------------------------------
// Required Libs:
// - LovyanGFX by lovyan03, v1.1.12
// - TAMC_GT911, by TAMC, v1.02
// ----------------------------------------------------------------------------
// To upload, press and hold BOOT while pressing RESET to enter Firmware mode.
// ----------------------------------------------------------------------------

// LCD back light
#define TFT_BL 2

// Own settings for device specific LGFX class
#include "HMI7LGFX.hpp"
#include "Button.hpp"
#include "Touchpad.hpp"
#include <LovyanGFX.hpp>

// The instance of the LCD display
LGFX lcd;
Touchpad tp;
Button b1(lcd, 20, 70, "Test 1");
Button b2(lcd, 300, 70, "Backlight");

void setup() {
  Serial.begin(9600);
  Serial.println();
  Serial.println("Dashboard Demo");

#ifdef TFT_BL
  // Enable Backlight
  pinMode(TFT_BL, OUTPUT);
  digitalWrite(TFT_BL, HIGH);
#endif

  lcd.init();
  tp.init();

  // Other color for second btn
  b2.back = TFT_OLIVE;

  drawDashboard();
  fontTest();
}

void loop() {
  delay(10);

  Touchpad::UpdateResult result = tp.update();
  if (result == Touchpad::UpdateResult::Released) {

    // btn 1
    if (b1.isHit(tp.x(), tp.y())) {
      b1.back = (b1.back == TFT_NAVY) ? TFT_MAROON : TFT_NAVY;
      b1.draw();
    }

    // btn 2
    if (b2.isHit(tp.x(), tp.y())) {
      b2.back = (b2.back == TFT_NAVY) ? TFT_MAGENTA : TFT_NAVY;
      digitalWrite(TFT_BL, b2.back == TFT_NAVY ? HIGH : LOW);
    }
  }
}

void drawDashboard() {
  lcd.fillScreen(TFT_BLACK);

  lcd.setFont(&fonts::AsciiFont24x48);
  lcd.drawString("Dashboard Demo", 20, 10);

  b1.draw();
  b2.draw();
}

void fontTest() {
  lcd.setTextSize(1);
  lcd.setTextColor(TFT_YELLOW, TFT_BLACK);

  lcd.setFont(&fonts::Font4);
  lcd.drawString("Font4", 10, 200);

  lcd.setFont(&fonts::Font6);
  lcd.drawString("6 1234567890", 10, 230);

  lcd.setFont(&fonts::Font7);
  lcd.drawString("7 1234567890", 10, 270);

  lcd.setFont(&fonts::Font8);
  lcd.drawString("8 1234567890", 10, 320);

  lcd.setFont(&fonts::AsciiFont24x48);
  lcd.drawString("AsciiFont24x48", 10, 420);

  // ---

  lcd.setFont(&fonts::Font0);
  lcd.drawString("Font0", 400, 200);

  lcd.setFont(&fonts::Font2);
  lcd.drawString("Font2", 400, 240);

  lcd.setFont(&fonts::Font8x8C64);
  lcd.drawString("Font8x8C64", 400, 280);
}

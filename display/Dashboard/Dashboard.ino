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
Button b1(lcd, 50, 50, "Test 1");
Button b2(lcd, 300, 50, "Backlight");

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
  lcd.setTextSize(2);
  lcd.setCursor(10, 10);
  lcd.printf("Dashboard Demo");
  b1.draw();
  b2.draw();
}

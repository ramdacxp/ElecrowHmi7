// ----------------------------------------------------------------------------
// Elecrow HMI 7 display - Touch Cross
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
#include <LovyanGFX.hpp>

#include "touch.h"

LGFX lcd;

void setup() {
  Serial.begin(9600);
  Serial.println();
  Serial.println("Touch Cross Sample");

  touch_init();

#ifdef TFT_BL
  pinMode(TFT_BL, OUTPUT);
  digitalWrite(TFT_BL, LOW);
  delay(500);
  digitalWrite(TFT_BL, HIGH);
#endif

  lcd.init();
  lcd.fillScreen(TFT_BLACK);
  lcd.setTextSize(2);

  lcd.setCursor(50, 50);
  lcd.printf("Touch me :)");
}

void loop() {
  delay(10);
  touch_update();

  if (touch_hasChanged()) {
    if (touch_active) {
      lcd.fillScreen(TFT_BLUE);
      lcd.setCursor(50, 50);
      lcd.printf("X: %d", touch_x);
      lcd.setCursor(50, 80);
      lcd.printf("Y: %d", touch_y);

      lcd.drawFastHLine(0, touch_y, 800, TFT_RED);
      lcd.drawFastVLine(touch_x, 0, 480, TFT_GREEN);
    } else {
      lcd.fillScreen(TFT_GREEN);
      lcd.setCursor(50, 50);
      lcd.print("No touching");
    }
    touch_apply();
  }
}

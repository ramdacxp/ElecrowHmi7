// ----------------------------------------------------------------------------
// Elecrow HMI 7 display - Hello World
// ----------------------------------------------------------------------------
// Board: ESP32S3 Dev Module
// Port: COM3 (or the one related to CH340G in device maganer)
// ----------------------------------------------------------------------------
// Tools > Partition Scheme: Huge APP (3MB No OTA/1MB SPIFFS)
// Tools > PSRAM: OPI PSRAM
// ----------------------------------------------------------------------------
// Required Libs:
// - LovyanGFX by lovyan03, v1.1.12
// ----------------------------------------------------------------------------
// To upload, press and hold BOOT while pressing RESET to enter Firmware mode.
// ----------------------------------------------------------------------------

// LCD back light
#define TFT_BL 2

// Own settings for device specific LGFX class
#include "HMI7LGFX.hpp"
#include <LovyanGFX.hpp>

// The instance of the LCD display
LGFX lcd;

void setup() {
  Serial.begin(9600);
  Serial.println();
  Serial.println("Mischa Display Demo");

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
  lcd.printf("Hallo Bad Steben");

  // lcd.fillRect(_width - size - 1, 0, size + 1, size + 1, color_bg);
  // lcd.drawLine(0, 0, 0, size, color_fg);
}

void loop() {
  // put your main code here, to run repeatedly
}

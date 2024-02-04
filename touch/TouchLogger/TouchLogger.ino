// ----------------------------------------------------------------------------
// Elecrow HMI 7 display - Touch Logger Sample
// ----------------------------------------------------------------------------
// Board: ESP32S3 Dev Module
// Port: COM3 (or the one related to CH340G in device maganer)
// ----------------------------------------------------------------------------
// Tools > Partition Scheme: Huge APP (3MB No OTA/1MB SPIFFS)
// Tools > PSRAM: OPI PSRAM
// ----------------------------------------------------------------------------
// Required Libs:
// - TAMC_GT911, by TAMC, v1.02
// ----------------------------------------------------------------------------
// To upload, press and hold BOOT while pressing RESET to enter Firmware mode.
// ----------------------------------------------------------------------------

#include "touch.h"

void setup() {
  Serial.begin(9600);
  Serial.println();
  Serial.println("Touch Logger Sample");
  Serial.println("Please touch the screen to see the coordinates.");

  touch_init();
}

void loop() {
  delay(10);
  touch_update();

  if (touch_hasChanged()) {
    if (touch_active) {
      Serial.print("Touched at: ");
      Serial.print(touch_x);
      Serial.print(", ");
      Serial.println(touch_y);
    } else {
      Serial.println("Not touched");
    }
    touch_apply();
  }
}

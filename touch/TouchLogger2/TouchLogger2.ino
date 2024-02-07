// ----------------------------------------------------------------------------
// Elecrow HMI 7 display - Touch Logger Sample (V2)
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

#include "Touchpad.hpp"

Touchpad tp;

void setup() {
  Serial.begin(9600);
  Serial.println();
  Serial.println("Touch Logger Sample V2");
  Serial.println("Please touch the screen to see the coordinates.");

  tp.init();
}

void loop() {
  delay(10);

  switch (tp.update()) {
    case Touchpad::UpdateResult::Pressed:
      Serial.printf("PRESSED (%d:%d) - %d\n", tp.x(), tp.y(), tp.active());
      break;
    case Touchpad::UpdateResult::Released:
      Serial.printf("RELEASED (%d:%d) - %d\n", tp.x(), tp.y(), tp.active());
      break;
    case Touchpad::UpdateResult::Reset:
      Serial.println("RESET");
      break;
  }

}

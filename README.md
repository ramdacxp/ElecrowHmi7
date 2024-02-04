# Elecrow HMI 7 display

This repository contains updated Arduino code for the Elecrow HMI 7" display.

All code is based on the sample programs provided in the [Elecrow Wiki](https://www.elecrow.com/wiki/index.php?title=ESP32_Display_7.0%27%27_Intelligent_Touch_Screen_Wi-Fi%26BLE_800*480_HMI_Display), but are updated to be used in the latest Arduino IDE and with latest library versions.

## Requirements

* You need the device: ESP32 Display 7.0" Intelligent Touch Screen Wi-Fi&BLE 800*480 HMI Display
* [Arduino IDE 2.2.1](https://www.arduino.cc/en/software)
* [Download this repository](https://github.com/ramdacxp/ElecrowHmi7/archive/refs/heads/main.zip) or clone it via [git](https://git-scm.com/downloads) by executing

  ```cmd
  cd MySuperRepoDirectory
  git clone https://github.com/ramdacxp/ElecrowHmi7.git
  ```

## One-Time Setup

In the Arduino IDE add the **support for generic ESP32 boards** in the `File > Preferences` dialog. Add the following line to the `Additioal board manager URLs` field:

```text
https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
```

In the `Library Manger` on the left side search for the following libraries and install them:

* `LovyanGFX` (by lovyan03; current version: 1.1.12)

## Connect and upload code

* Open one of the `*.ino` files in the Arduino IDE
* Connect the device and check its COM port in the Windows device manager (most likely will be `COM3`)
* In the dropdown above the code select board `ESP32S3^Dev Module` and port `COM3`
* In `Tools > Partition Scheme* choose `Huge APP (3MB No OTA/1MB SPIFFS)`
* In `Tools > PSRAM` choose `OPI PSRAM`
* **Activate the firmware mode of the device** by holding down the `BOOT` button on the device and shortly pressing the `RESET` button
* Compile and upload the code via the `[->]` button in the IDE
* Open the Serial Monitor window via the `[.-O..]` button
* If the upload was successful, press the `RESET` button on the device to **leave the firmware mode**  

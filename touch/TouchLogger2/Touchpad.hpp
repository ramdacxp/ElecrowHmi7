// ----------------------------------------------------------------------------
// Elecrow HMI 7 display - Touchpad support via class
// ----------------------------------------------------------------------------
// Required Libs:
// - TAMC_GT911, by TAMC, v1.02
//   https://github.com/TAMCTec/gt911-arduino.git
// ----------------------------------------------------------------------------

#pragma once

#define TP_NOT_USED -1
#define TP_DEFAULT_SCL 20
#define TP_DEFAULT_SDA 19
#define TP_DEFAULT_WIDTH 800
#define TP_DEFAULT_HEIGHT 480

#include "Arduino.h"
#include <TAMC_GT911.h>
#include <Wire.h>

class Touchpad {
private:
  // members
  TAMC_GT911 _ts = TAMC_GT911(TP_DEFAULT_SDA, TP_DEFAULT_SCL, TP_NOT_USED, TP_NOT_USED, TP_DEFAULT_WIDTH, TP_DEFAULT_HEIGHT);
  TP_Point _point;
  bool _active;

public:
  // constructor(s)
  Touchpad() {
    //  _ts = TAMC_GT911(TP_DEFAULT_SDA, TP_DEFAULT_SCL, TP_NOT_USED, TP_NOT_USED, TP_DEFAULT_WIDTH, TP_DEFAULT_HEIGHT);
  }

  // Touchpad(uint8_t sda, uint8_t scl, uint16_t width, uint16_t height)
  // {
  //   _ts = TAMC_GT911(sda, scl, -1, -1, width, height);
  // }

  uint16_t x() {
    return _point.x;
  }
  uint16_t y() {
    return _point.y;
  }
  bool active() {
    return _active;
  }

  // methods
  void init() {
    Wire.begin(TP_DEFAULT_SDA, TP_DEFAULT_SCL);
    _ts.begin();
    _ts.setRotation(ROTATION_INVERTED); // ROTATION_NORMAL
    _active = false;
  }

  enum UpdateResult {
    Reset,
    Pressed,
    Released,
    NotChanged
  };

  UpdateResult update() {
    _ts.read();

    if (_ts.isTouched) {
      // is error data is returned, try to reset
      if ((_ts.points[0].x == 65535) || (_ts.points[0].y == 65535)) {
        _ts.reset();
        return UpdateResult::Reset;
      }

      if ((_point != _ts.points[0]) || (_active == false)) {
        _point = _ts.points[0];
        _active = true;
        return UpdateResult::Pressed;
      }
    } else if (_active == true) {
      _active = false;
      return UpdateResult::Released;
    }

    return UpdateResult::NotChanged;
  }
};

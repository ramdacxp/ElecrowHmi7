// ----------------------------------------------------------------------------
// Elecrow HMI 7 display - Touch Support
// ----------------------------------------------------------------------------
// Required Libs:
// - TAMC_GT911, by TAMC, v1.02
//   https://github.com/TAMCTec/gt911-arduino.git
// ----------------------------------------------------------------------------

#pragma once

#define TOUCH_GT911_SCL 20  // 20
#define TOUCH_GT911_SDA 19  // 19
#define TOUCH_GT911_INT -1  //-1
#define TOUCH_GT911_RST -1  // 38

#define TOUCH_GT911_ROTATION ROTATION_NORMAL

#define TOUCH_DISP_W 800
#define TOUCH_DISP_H 480

#define TOUCH_MAP_X_MIN TOUCH_DISP_W
#define TOUCH_MAP_X_MAX 0
#define TOUCH_MAP_Y_MIN TOUCH_DISP_H
#define TOUCH_MAP_Y_MAX 0

int touch_x = 0;
int touch_y = 0;
bool touch_active = false;

int touch_last_x = 0;
int touch_last_y = 0;
bool touch_last_active = false;

#include <Wire.h>
#include <TAMC_GT911.h>

TAMC_GT911 ts = TAMC_GT911(
  TOUCH_GT911_SDA, TOUCH_GT911_SCL, TOUCH_GT911_INT, TOUCH_GT911_RST,
  max(TOUCH_MAP_X_MIN, TOUCH_MAP_X_MAX), max(TOUCH_MAP_Y_MIN, TOUCH_MAP_Y_MAX));

void touch_init() {
  Wire.begin(TOUCH_GT911_SDA, TOUCH_GT911_SCL);
  ts.begin();
  ts.setRotation(TOUCH_GT911_ROTATION);

  touch_x = 0;
  touch_y = 0;
  touch_active = false;
  touch_last_x = 0;
  touch_last_y = 0;
  touch_last_active = false;
}

void touch_update() {
  ts.read();

  if (ts.isTouched) {

    if ((ts.points[0].x == 65535) || (ts.points[0].y == 65535)) {
      ts.reset();
      return;
    }

    touch_x = map(ts.points[0].x, TOUCH_MAP_X_MIN, TOUCH_MAP_X_MAX, 0, TOUCH_DISP_W - 1);
    touch_y = map(ts.points[0].y, TOUCH_MAP_Y_MIN, TOUCH_MAP_Y_MAX, 0, TOUCH_DISP_H - 1);
    touch_active = true;
  } else {
    touch_active = false;
  }
}

bool touch_hasChanged() {
  return ((touch_x != touch_last_x) || (touch_y != touch_last_y) || (touch_active != touch_last_active));
}

void touch_apply() {
  touch_last_x = touch_x;
  touch_last_y = touch_y;
  touch_last_active = touch_active;
}

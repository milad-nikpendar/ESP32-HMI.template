/*
   lvgl_touch_gt911 header V1.0.0
   Created by Milad Nikpendar
*/
#ifndef LVGL_TOUCH_GT911_H
#define LVGL_TOUCH_GT911_H

// ---- Configuration ----
#define TCH_I2C_ADDR GT911_I2C_ADDR_28 // GT911 I2C address (0x28)
#define TCH_MODE GT911_MODE_POLLING    // or GT911_MODE_INTERRUPT
#define TCH_ROTATION initGT911::Rotate::_0
// #define Debug_GT911_Serial

#ifdef Debug_GT911_Serial
#define TCH_Log(a) Serial.println("[GT911] " + String(a))
#else
#define TCH_Log(a)
#endif // Debug_GT911_Serial

/* initlialize the capitive touchpad */
#include <Wire.h>
#include "I2Cscanner.h"
#include <initGT911.h>
initGT911 Touchscreen(&Wire, TCH_I2C_ADDR);   // create GT911 object
#define Touched Touchscreen.touched(TCH_MODE) // check if the touchpad is touched

/* initialize the touchpad */
void hmi_touch_init()
{
  /* initialize the capacitive touchpad */
  Wire.begin(I2C_SDA, I2C_SCL, 400000);
  // I2Cscanner(&Wire);

#if TCH_MODE == GT911_MODE_INTERRUPT
  Touchscreen.begin(TCH_IRQ, -1, 400000);
#else
  Touchscreen.begin(-1, -1, 400000);
#endif // TCH_MODE == GT911_MODE_INTERRUPT
  Touchscreen.setupDisplay(TFT_HOR_RES, TFT_VER_RES, TCH_ROTATION);
}

/*Read the touchpad*/
void hmi_touch_read(lv_indev_t *indev, lv_indev_data_t *data)
{
  /* read the capacitive touchpad */
  if (Touched == 1)
  {
    data->state = LV_INDEV_STATE_PRESSED;

    GTPoint *tp = Touchscreen.getPoints();
    data->point.x = tp[0].x;
    data->point.y = tp[0].y;
    TCH_Log(String(data->point.x) + "\t" + String(data->point.y));
  }
  else if (Touched > 1)
  {
    Serial.println("Multi touch found!");
  }
  else
  {
    data->state = LV_INDEV_STATE_RELEASED; // touch is released
  }
}
#endif // LVGL_TOUCH_GT911_H

#include <Arduino.h>
#include "function.h"

void setup()
{
  Serial.begin(115200); // Initialize serial communication

  chipInfo();        // Display chip information
  displayFreeHeap(); // Display heap information
  hmi_touch_init();  // Initialize touch screen
  hmi_lvgl_init();   // Initialize LVGL and UI

#ifdef WS2812Pin // begin RGB LED if defined
  RGB.begin();
  RGB.show(33, 255, 33); // Red, Green, Blue
#endif                   // WS2812Pin

#ifdef BuzzerPin // begin buzzer if defined
  beep.begin();
  beep.pulse(3000, 100); // 3000hz for 100ms
#endif                   // BuzzerPin
}

void loop()
{
  hmi_lvgl_handler();
  DELAY(5);
}

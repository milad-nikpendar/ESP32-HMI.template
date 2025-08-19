#include "config.h"

// #include the libraries you want to use in functions
#include "esp32-hmi/lvgl_functions.h"

// Create your project global values

#ifdef WS2812Pin
#include "src/statusRGB.h"
statusRGB RGB(WS2812Pin); // RGB LED object
#endif                    // WS2812Pin

#ifdef BuzzerPin
#include "src/initBuzzer.h"
// Buzzer beep(BuzzerPin); // Buzzer object
RtosBuzzer beep(BuzzerPin); // Buzzer object
#endif                      // BuzzerPin

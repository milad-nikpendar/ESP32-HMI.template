/*
   statusRGB header V1.0.0
   Created by Milad Nikpendar
*/
#include <Adafruit_NeoPixel.h>
Adafruit_NeoPixel pixels;

struct Timer_t {
  uint32_t timer;
  bool isTimeout(uint32_t time) {
    return (millis() - timer > time) ? true : false;
  }
  void reset() {
    timer = millis();
  }
};

class statusRGB {
  public:
    Timer_t timer;

    statusRGB(uint8_t pin) {
      _pin = pin;
    }
    void begin() {
      pixels.updateLength(1);
      pixels.setPin(_pin);
      pixels.updateType(NEO_GRB + NEO_KHZ800);
      pixels.begin();
    }
    void show(uint8_t r, uint8_t g, uint8_t b) {
      if (r < 0) r = 0; else if (r > 255) r = 255;
      if (g < 0) g = 0; else if (g > 255) g = 255;
      if (b < 0) b = 0; else if (b > 255) b = 255;

      pixels.clear();
      pixels.setBrightness(bright);
      pixels.setPixelColor(0, pixels.Color(r, g, b));
      pixels.show();
    }
    void toggle(uint8_t r, uint8_t g, uint8_t b) {
      static bool isToggle;
      if (isToggle) show(0, 0, 0);
      else show(r, g, b);
      isToggle = !isToggle;
    }
    void toggle(uint8_t r, uint8_t g, uint8_t b, uint16_t time) {
      if (timer.isTimeout(time)) {
        toggle(r, g, b); 
        timer.reset();
      }
    }
  private:
    uint8_t _pin;
    uint8_t bright = 255;
};

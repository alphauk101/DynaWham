#ifndef __LED_CTRL__
#define __LED_CTRL__
#include "Adafruit_NeoPixel.h"

#define LED_PIN   5 /*pin the leds are connected to*/
#define LED_COUNT 8

class led {
  public:
    void led_init(void);
    /*We only have 8 leds which is why the byte is used. Each bit represents
    a state of an LED the colour is hard code*/
    void set_treadle(byte);
  private:
    void strafe(uint32_t, bool);
    void fade(bool);
    void setall(uint32_t); /**sets the colour NOT brightness or show*/
    Adafruit_NeoPixel strip = Adafruit_NeoPixel(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
};
#endif

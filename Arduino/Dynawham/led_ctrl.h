#ifndef __LED_CTRL__
#define __LED_CTRL__
#include "Adafruit_NeoPixel.h"
#include "defines.h"

#define LED_PIN   5 /*pin the leds are connected to*/
#define LED_COUNT 8

class led {
  public:
    void led_init(void);
    /*We only have 8 leds which is why the byte is used. Each bit represents
    a state of an LED the colour is hard code*/
    void set_treadle(byte);
    /*When a mode change is actioned we can show this on the LEDs*/
    void led_set_mode(Mode);
    /*To give a funky effect everytime a program is changed we can show it on the LEDs*/
    void led_set_program(uint8_t);
  private:
    void strafe(uint32_t, bool);
    void fade(bool);
    void setall(uint32_t); /**sets the colour NOT brightness or show*/
    Adafruit_NeoPixel strip = Adafruit_NeoPixel(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
};
#endif

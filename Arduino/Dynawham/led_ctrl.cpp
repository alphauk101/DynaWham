#include "led_ctrl.h"

/*delays in ms*/
#define STRAFE_DELAY      50
#define FADE_DELAY        5
#define NORMAL_BRIGHT     255 /*Our typical brightness used when setting leds*/

#define TREADLE_COLOUR    strip.Color(255, 0, 255)

void led::led_init()
{
  strip.begin();
  /*Make a pretty start up anima*/
  this->strafe(strip.Color(255, 0, 0), true);
  delay(STRAFE_DELAY);
  this->strafe(strip.Color(0, 255, 0), false);
  delay(STRAFE_DELAY);
  this->strafe(strip.Color(0, 0, 255), true);

  strip.clear();
  strip.show();

  /*Just fades white at the mmoment*/
  this->fade(true);
  this->fade(false);
  /*At this point we are all off waiting for input from app*/
}

void led::fade(bool dir) {
  uint8_t c = 0;
  for (uint16_t i = 0; i < 255; i++) {
    /*set all the leds*/
    if (dir) {
      c = i;
    } else {
      c = (255 - i);
    }

    this->setall(strip.Color(c, c, c));

    strip.show();
    delay(FADE_DELAY);
  }
}

void led::strafe(uint32_t col, bool dir)
{
  strip.clear();
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    if (dir) {
      strip.setPixelColor(i, col);
    } else {
      strip.setPixelColor((strip.numPixels() - i), col);
    }

    /*Set full brightness and apply this iteration*/
    strip.setBrightness(NORMAL_BRIGHT);
    strip.show();
    delay(STRAFE_DELAY);
  }
}

void led::set_treadle(byte trdle)
{
  strip.clear();
  for(uint8_t a = 0; a < 8; a++)
  {
    if(trdle & (1 << a)){
      strip.setPixelColor(a, TREADLE_COLOUR);
    }
  }
  strip.setBrightness(NORMAL_BRIGHT);
  strip.show();
}

void led::setall(uint32_t col)
{
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, col);
  }
}


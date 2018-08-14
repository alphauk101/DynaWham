#include "led_ctrl.h"

/*delays in ms*/
#define STRAFE_DELAY      50
#define FADE_DELAY        5
#define NORMAL_BRIGHT     255 /*Our typical brightness used when setting leds*/

#define TREADLE_COLOUR      strip.Color(255, 0, 255)
#define PROGRAM1_COLOUR     strip.Color(0, 0, 255)
#define PROGRAM2_COLOUR     strip.Color(0, 255, 0)
#define BG_COLOUR           strip.Color(25, 0, 0)

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

/*We can do different things with the modes*/
void led::led_set_mode(Mode mode)
{
  
}

void led::led_set_program(uint8_t program)
{
  /*#define DW_SHALLOW        1
#define DW_DEEP           2
#define DW_TWOOCTUP       3
#define DW_OCTUP          4
#define DW_OCTDOWN        5
#define DW_TWOOCTDOWN     6
#define DW_DIVE           7
#define DW_DROP           8
#define DW_H_OCT          9        
#define DW_H_5TH4TH       10
#define DW_H_4TH3RD       11
#define DW_H_5TH7TH       12
#define DW_H_5TH6TH       13
#define DW_H_4TH5TH       14
#define DW_H_3RD4TH       15
#define DW_H_3RD3RD       16
#define DW_H_2ND3RD       17*/
  strip.clear();
  this->setall(BG_COLOUR);
  if(program < 10){
    strip.setPixelColor(program-1, PROGRAM1_COLOUR);
  }else{
    strip.setPixelColor((program-10), PROGRAM2_COLOUR);
  }
  strip.show();


/*
  switch(program)
  {
    case DW_SHALLOW:
    
    break;
    case DW_DEEP:
    
    break;
    case DW_TWOOCTUP:
    
    break;
    case DW_OCTUP:
    
    break;
    case DW_OCTDOWN:
    
    break;
    case DW_TWOOCTDOWN:
    
    break;
    case DW_DIVE:
    
    break;
    case DW_DROP:
    
    break;
    case DW_H_OCT:
    
    break;
    case DW_H_5TH4TH:
    
    break;
    case DW_H_4TH3RD:
    
    break;
    case DW_H_5TH7TH:
    
    break;
    case DW_H_5TH6TH:
    
    break;
    case DW_H_4TH5TH:
    
    break;
    case DW_H_3RD4TH:
    
    break;
    case DW_H_3RD3RD:
    
    break;
    case DW_H_2ND3RD:
    
    break;
    default:
    break;
  }
  */
}


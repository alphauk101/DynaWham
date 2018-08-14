#include "presets.h"

void presets::init(uint8_t *buff_p) {
  /*Store the buffer pointer*/
  presets_data.buff_ptr = buff_p;
  presets_data.last_tick = millis();/*We keep a record of this for timing reasons*/
  presets_data.mode = NONE;

  this->clear_mode();
}

void presets::set_mode(Mode mode)
{
  if (mode != presets_data.mode)
  {
    this->clear_mode();
    presets_data.mode = mode;
  }
}

/*Clears all data in the mode struct should be used everytime the mode is
  changed.*/
void presets::clear_mode()
{
  memset(&presets_data.mode_data, 0, sizeof(MODE_DATA_S));
}

/*This nudge comes through from the main on every iteration of the loop*/
uint16_t presets::nudge() {

  presets_data.tx_len = 0;/*default to zero*/

  /*Firstly grab the current time*/
  presets_data.last_tick = millis();

  /*check whether we are actually in a preset mode*/
  switch (presets_data.mode)
  {
    case XYLO:
      this->xylo_nudge();
      break;
    case RUN:
      this->run_nudge();
      break;
    case NONE:
    default:
      /*We have either a mode none or an error either way set 0 byte length*/
      presets_data.tx_len = 0;
      break;
  }

  /*If there is a length value above 0 then we can assume that the appropriate bytes for this program change
    have been inserted into the buffer*/
  return presets_data.tx_len = 0;
}

void presets::run_nudge()
{
  if (presets_data.mode_data.last_program == 0)
  {
    presets_data.mode_data.last_program = DW_SHALLOW;
    presets_data.mode_data.dir = true;
  }else{
    if (presets_data.mode_data.dir)
    {
      presets_data.mode_data.last_program++;
      if (presets_data.mode_data.last_program == DW_H_2ND3RD)
      {
        /*reverse the flow*/
        presets_data.mode_data.dir = false;
      }
    }else{
      presets_data.mode_data.last_program--;
      if (presets_data.mode_data.last_program == DW_SHALLOW)
      {
        /*reverse the flow*/
        presets_data.mode_data.dir = true;
      }
    }
  }
  /*show this program*/
  LED.led_set_program(presets_data.mode_data.last_program);

  /*Finally pacakge the bytes to go*/
  *presets_data.buff_ptr = presets_data.mode_data.last_program;
  presets_data.tx_len = 1;
}

void presets::xylo_nudge()
{
  /*XYLO is
    #define DW_H_5TH4TH       10
    #define DW_H_4TH3RD       11
    #define DW_H_5TH7TH       12
    #define DW_H_5TH6TH       13
    #define DW_H_4TH5TH       14
    #define DW_H_3RD4TH       15
    #define DW_H_3RD3RD       16
    #define DW_H_2ND3RD       17
    and back again*/
  /*With XYLO we change with every nudge (for now)*/
  if (presets_data.mode_data.last_program == 0)
  {
    presets_data.mode_data.last_program = DW_H_2ND3RD;
    presets_data.mode_data.dir = false;
  } else {
    if (presets_data.mode_data.dir)
    {
      presets_data.mode_data.last_program++;
      if (presets_data.mode_data.last_program == DW_H_2ND3RD)
      {
        /*reverse the flow*/
        presets_data.mode_data.dir = false;
      }
    } else {
      presets_data.mode_data.last_program--;
      if (presets_data.mode_data.last_program == DW_H_5TH4TH)
      {
        /*reverse the flow*/
        presets_data.mode_data.dir = true;
      }
    }
  }

  /*show this program*/
  LED.led_set_program(presets_data.mode_data.last_program);

  /*Finally pacakge the bytes to go*/
  *presets_data.buff_ptr = presets_data.mode_data.last_program;
  presets_data.tx_len = 1;
}




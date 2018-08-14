#include "presets.h"

void presets::init(uint8_t *buff_p) {
  /*Store the buffer pointer*/
  presets_data.buff_ptr = buff_p;
  presets_data.last_tick = millis();/*We keep a record of this for timing reasons*/
  presets_data.mode = NONE;

  this->clear_mode();
}

/*Clears all data in the mode struct should be used everytime the mode is 
changed.*/
void presets::clear_mode()
{
  memset(&presets_data.mode_data,0,sizeof(MODE_DATA_S));
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

uint16_t presets::xylo_nudge()
{
  /*With XYLO we change with every nudge (for now)*/

  
  

}




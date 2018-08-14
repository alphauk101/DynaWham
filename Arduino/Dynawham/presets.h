#ifndef __PRESETS__
#define __PRESETS__
#include <Arduino.h>
#include "defines.h"


enum Mode {
  NONE,
  XYLO    /*mode that scales up and down on the harmonic modes*/
};

struct MODE_DATA_S {

};

struct PRESET_DATA_S {
  unsigned long     last_tick;

  uint8_t           *buff_ptr; /*Buffer used for sending data*/

  uint16_t          tx_len; /*Number of bytes to be transmitted if any*/

  Mode              mode;

  MODE_DATA_S       mode_data;
};


class presets
{
  public:
    void init(uint8_t*);
    /*We use a nudge function from the main to decide whether any data needs to
      be sent - it returns a number of bytes to be sent if 0 then assume there are none.*/
    uint16_t nudge(void);
  private:
    uint16_t xylo_nudge(void);
    void clear_mode(void);
    PRESET_DATA_S presets_data;

};
#endif

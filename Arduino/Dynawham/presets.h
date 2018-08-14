#ifndef __PRESETS__
#define __PRESETS__
#include <Arduino.h>
#include "defines.h"
#include "led_ctrl.h"

extern led LED;

struct MODE_DATA_S {
  uint8_t       last_program;/*Last sent program*/

  bool          dir;/*Typically used for detecting which direction we are travelling*/
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

    /*Sets the mode - can be changed at any time*/
    void set_mode(Mode);

  private:
    void run_nudge(void);
    void xylo_nudge(void);
    void clear_mode(void);
    PRESET_DATA_S presets_data;

};
#endif

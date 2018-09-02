/*
  reference:
  https://www.midi.org/specifications-old/item/table-1-summary-of-midi-message
  https://www.midi.org/specifications-old/item/table-3-control-change-messages-data-bytes-2
*/
#include "led_ctrl.h"
#include "presets.h"
#include "defines.h"
#include "TimerOne.h"

led LED;
presets PRESETS;

uint16_t byte_to_send = 0;
#define POT_SAMPLE_TIME   100000

#define POT_TOL           10 //ADC steps

#define MIDI_CHANNEL      0x00
#define POT_PIN           A0
#define POT_MAX           1023
#define POT_MIN           443
#define PROGRAM_CHANGE    0xC0
#define CONTINUE_MSG      0xB0
#define EXP_PEDAL         0x0B
#define PACKET_LENGTH     5
byte midi_buff[PACKET_LENGTH];

#define CMD_DELAY         100 /*The minimum time between a midi command due to transistion and processing time etc.*/

volatile int pot_value = 0;
int tmp_p_value = 0;
int CC_midi;

void setup() {

  Serial1.begin(31250);/*The baud rate of midi*/
  //erial.begin(9600);

  Timer1.initialize(POT_SAMPLE_TIME); // set a timer of length 100000 microseconds (or 0.1 sec - or 10Hz => the led will blink 5 times, 5 cycles of on-and-off, per second)
  Timer1.attachInterrupt( timerIsr ); // attach the service routine here

  LED.led_init();

  /*Pass the buffer to the presets initilisation*/
  PRESETS.init(&midi_buff[0]);

  PRESETS.set_mode(XYLO);
  /*reset this*/
  byte_to_send = 0;
}

bool dir = true;
uint8_t exp_v = 0;
void loop() {
  /*
    if(dir)
    {
      exp_v++;
      if(exp_v == 127){
        dir = false;
      }
    }else{
      exp_v--;
      if(exp_v == 0){
        dir = true;
      }
    }
     send_cont(exp_v);
  */


  

  byte_to_send = PRESETS.nudge();
  if (byte_to_send > 0) {
    /*Send these bytes to the program*/
    byte p = midi_buff[0];
    send_program_change(p);
  }




  if( (pot_value < (tmp_p_value-POT_TOL)) || (pot_value > (tmp_p_value+POT_TOL)) )
  {
    CC_midi = map(pot_value, POT_MIN, POT_MAX, 0, 127); //127 = max midi CC value
    send_cont(CC_midi);
    set_treadle_led(CC_midi);
    tmp_p_value = pot_value;
  }
  
  delay(CMD_DELAY);
}

void set_treadle_led(uint8_t v)
{
  byte tr = 0;
  /*
    tr = (v/1)?(1<<0):0;
    tr |= (v/2)?(1<<1):0;
    tr |= (v/4)?(1<<2):0;
    tr |= (v/8)?(1<<3):0;
    tr |= (v/16)?(1<<4):0;
    tr |= (v/32)?(1<<5):0;
    tr |= (v/64)?(1<<6):0;
    tr |= (v/128)?(1<<7):0;
  */

  int b = v / 16;
  for (int a = 0 ; a < 8; a++)
  {
    if (a <= b) {
      tr |= (1 << a);
    }
  }
  LED.set_treadle(tr);
}

/*Pass the byte for the the program change*/
void send_program_change(byte program)
{
  /*First the channel/status*/
  midi_buff[0] = (PROGRAM_CHANGE | MIDI_CHANNEL);
  /*Program byte*/
  midi_buff[1] =  (program & 0x7F);

  LED.led_set_program(program);
  /*Now send this packet*/
  send_midi(2);
}

/*Send the byte for the continuous message*/
void send_cont(byte cont)
{
  /*First the channel/status*/
  midi_buff[0] = (CONTINUE_MSG | MIDI_CHANNEL);
  /*CC byte*/
  midi_buff[1] =  (EXP_PEDAL & 0x7F);
  /*exp value*/
  midi_buff[2] =  (cont);

  send_midi(3);
}

void send_midi(int len)
{
  for (int a = 0 ; a < len; a++) {
    Serial1.write(midi_buff[a]);
  }
}

void timerIsr()
{
  //Serial.println(analogRead(POT_PIN));
  pot_value = analogRead(POT_PIN);
}




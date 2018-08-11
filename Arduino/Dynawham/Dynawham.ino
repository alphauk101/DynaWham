/*
  reference:
  https://www.midi.org/specifications-old/item/table-1-summary-of-midi-message
  https://www.midi.org/specifications-old/item/table-3-control-change-messages-data-bytes-2
*/

#define MIDI_CHANNEL      0x00

#define PROGRAM_CHANGE    0xC0
#define CONTINUE_MSG      0xB0
#define EXP_PEDAL         0x0B
#define PACKET_LENGTH     5
byte midi_buff[PACKET_LENGTH];

#define CMD_DELAY         100

void setup() {

  Serial.begin(31250);/*The baud rate of midi*/
  //Serial.begin(57600);


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
  
  
  send_program_change(exp_v);
  exp_v++;
  if(exp_v  == 15)exp_v = 0;
  
  delay(CMD_DELAY);

}

/*Pass the byte for the the program change*/
void send_program_change(byte program)
{
  /*First the channel/status*/
  midi_buff[0] = (PROGRAM_CHANGE | MIDI_CHANNEL);
  /*Program byte*/
  midi_buff[1] =  (program & 0x7F);
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
    Serial.write(midi_buff[a]);
  }
}





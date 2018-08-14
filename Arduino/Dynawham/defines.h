#ifndef __DEFINES__
#define __DEFINES__

/*Define the pedal midi program channels here.*/
#define DW_SHALLOW        1
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
#define DW_H_2ND3RD       17

enum Mode {
  NONE,
  XYLO,    /*mode that scales up and down on the harmonic modes*/
  RUN     /*does all programs back and fourth*/
};



#endif

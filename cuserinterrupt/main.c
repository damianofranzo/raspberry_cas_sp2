#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <wiringPi.h> 

#define BUTTON_PIN 11
//it's GPIO7
#define OUTPUT_PIN 26
//it's GPIO12

volatile int delaytime=50;

//User-level ISR
void SignalUpDownInterrupt(void) {
  digitalWrite(OUTPUT_PIN,1);
  delay(delaytime);
  digitalWrite(OUTPUT_PIN,0);
}
 

int main() {
  // sets up the wiringPi library
  if (wiringPiSetup () < 0) {
      fprintf (stderr, "Unable to setup wiringPi: %s\n", strerror (errno));
      return 1;
  }

  if (wiringPiISR (BUTTON_PIN, INT_EDGE_RISING, &SignalUpDownInterrupt) < 0 ) {
      fprintf (stderr, "Unable to setup ISR for INT_EDGE_BOTH: %s\n", strerror (errno));
      return 1;
  }
  //it's inizialized the user-level ISR related to GPIO associated to number BUTTOM_PIN
  //the flag INT_EDGE_RISING indicates that the user-level ISR has to be called only in low-high transition
 
  while ( 1 ) {
    printf( "Program running\n");
    delay( 1000 );
  }
 
  return 0;
}

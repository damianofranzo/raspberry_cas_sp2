#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <wiringPi.h>

// Use GPIO Pin 17, which is Pin 0 for wiringPi library
 
#define BUTTON_PIN 0
 
// counters that track when the signal goes up and down 
volatile int upcounter = 0;
volatile int downcounter = 0;
volatile int flag=0;
 
// -------------------------------------------------------------------------
 
void SignalUpDownInterrupt(void) {
  if(flag){
    upcounter++;
    flag=0;
    //pinx V up
  }
  else{
    downcounter++;
    flag=1;
     //pinx V up
  }
}

 
// -------------------------------------------------------------------------
 
int main() {
  // sets up the wiringPi library
  if (wiringPiSetup () < 0) {
      fprintf (stderr, "Unable to setup wiringPi: %s\n", strerror (errno));
      return 1;
  }

  if (wiringPiISR (BUTTON_PIN, INT_EDGE_BOTH, &SignalUpDownInterrupt) < 0 ) {
      fprintf (stderr, "Unable to setup ISR for INT_EDGE_BOTH: %s\n", strerror (errno));
      return 1;
  }

 
  // display counter value every second.
  while ( 1 ) {
    printf( "Up times: %d Down times: %d \n", upcounter,downcounter);
    upcounter = 0;
    downcounter=0;
    delay( 1000 ); // wait 1 second
  }
 
  return 0;
}

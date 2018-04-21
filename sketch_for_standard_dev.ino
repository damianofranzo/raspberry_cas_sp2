/*This code, used for Arduino, is able to evaluate the delay between two rising edges of 2 waves, exploiting the internal registers of the ADC and its ISR. The resolution that is able to achieved is around 
 * 12 us, therefore the expected delays need to be grater than 12us. This system is useful for obtaing a "N" delays divided by a certain instant that strictly depends on the "PERIOD" of the square 
 * wave generator. The sketch provides the measures, printing them on the serial monitor; therefore they can be used in another software in order to evaluate the standard deviation and draw a plot. 
 * In addition, the expected delays have to be less than 2^(16)-1 bit that represents the limit for the variables int */

#define N 1000                        // number of measures that you want to perform
#define PERIOD 10000                  // period of the square wave generator (in us)

unsigned long start = 0;              
int intervals[N]; 
int interval;                      
int i = 0;                                             
bool first_rising, complete, deelay = false;           
bool active = true; 

void setup() 
{
  Serial.begin(2000000);              // Baudrate of serial monitor
  
  /*clear prescaler bits*/
  ADCSRA &= ~(bit (ADPS0) | bit (ADPS1) | bit (ADPS2));
  /*enable free running mode*/ 
  ADCSRB = (0 << ADTS2) | (0 << ADTS1) | (0 << ADTS0); 
  /*reference : EXTERNAL (REFS1=0, REFS0=0), channel 1 */
  ADMUX = 0b00000001;
  /* 1 << "" enables: ADATE -> Autotrigger; ADEN -> enable ADC; 
  ADSC -> start mesuraments */
  ADCSRA |= (1 << ADATE) | (1 << ADEN) | (1 << ADSC);
  /*prescaler = 1*/
  ADCSRA |=0x00; 
}

void loop() 
{ 
  if(active) bitSet(ADCSRA, ADIE);          // enable the interrupt (just once)
  
  if(complete){
    for(i = 0; i< N; i++){

/*If the interval is greater than the period of the square wave in input, it means that the system didn't manage to verify a single moment of delay between the two rising edges of the 
two waves (input and output) and it gets the value on the second rising edge of the raspberry output (it could be casued by the changing of the hardware channel in the ISR). 
So, deleting the period of the input wave (in us), we are able to estimate a suitable value*/ 
     
      if (intervals[i] > PERIOD){ 
        intervals[i] -= PERIOD; 
      }      

      Serial.println(intervals[i]);         // print on the serial monitor the values obtained
    }
    complete = false;
  }
   active = false;
}


/*Interrupt service routine*/

ISR(ADC_vect) 
{
  if( ADCW > 900 && deelay){                // only when the signal is "HIGH" and there was a delay
    
    if (!first_rising){                     // if it receives the rising edge of the sware wave generator
      ADMUX = 0b00000101;                   // change the ADC channel in order to wait the rising edge of the Raspberry output (channel 5)                         
      first_rising = true;                  // the first rising is received
      deelay = false;                       // wait for the delay
      start = micros();                     // start the counting
    }
        
    else {                                  // if it receives the rising edge from the raspberry outout 
      ADMUX = 0b00000001;                   // change the ADC channel in order to wait the rising edge of the square wave generator again
      interval = micros() - start;          // the delay is obtained by means the difference between the actual time and the previous one
      intervals[i] =  interval;              
      first_rising = false;                 // wait for another rising edge from the square wave generator
      deelay = false;                       // and for a new delay ("LOW" voltage value)
      i++;                                  // increments the number of intervals collected
    }    
  }
  
  else if (ADCW < 100 ){                    // if a "LOW" voltage is received
    deelay = true;                          // a delay is performed 
  }
  
  if(i == N){                               // when N measures are performed
    bitClear(ADCSRA, ADIE);                 // disable the ISR
    complete = true; 
  }
}





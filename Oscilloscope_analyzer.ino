/*
The passthrough routine will simply output the vaule
read by the analogShield input IN0 and put the same
value out on output OUT0.
V1.0 9/2013 W. Esposito
*/
#include <analogShield.h>   //Include to use analog shied.

//switches for FHT (FFT) library options.
#define LOG_OUT 1 // use the log output function
#define FHT_N 256 // set to 256 point fht

#include <FHT.h> // include the library, must happen after the #defines.


void setup()
{
  //disable some interrupts so that we have less jitter.
  TIMSK0 = 0; // turn off timer0 for lower jitter
}

unsigned int count = 0;
void loop()
{
  while(1) { //not leaving the loop function reduces jitter
    cli();  // UDRE interrupt slows this way down on arduino1.0, so we stop all interrupts.
    for (int i = 0 ; i < FHT_N ; i++) { // save 256 samples
      fht_input[i] = analog.signedRead(0); // put real data into bins
    }
    //now, the fourier functions!
    fht_window(); // window the data for better frequency response
    fht_reorder(); // reorder the data before doing the fht  
    fht_run(); // process the data in the fht
    fht_mag_log(); // take the output of the fht
    sei();
    displayVector(fht_log_out, FHT_N/2);
  }
}

void displayVector(byte* vector, int len)
{
  analog.write(0, 65535);  //write out the value on port labeled 'OUT0'
  delayMicroseconds(10);
  for(int i = 0; i < len; i++)
  {
    analog.write(0, vector[i]<<7);  //write out the value on port labeled 'OUT0'
    delayMicroseconds(31);
  }  
  analog.write(0,0);
}

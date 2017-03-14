/* Blink without Delay

 Turns on and off a light emitting diode (LED) connected to a digital
 pin, without using the delay() function.  This means that other code
 can run at the same time without being interrupted by the LED code.

 The circuit:
 * LED attached from pin 13 to ground.
 * Note: on most Arduinos, there is already an LED on the board
 that's attached to pin 13, so no hardware is needed for this example.

 created 2005
 by David A. Mellis
 modified 8 Feb 2010
 by Paul Stoffregen
 modified 11 Nov 2013
 by Scott Fitzgerald


 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/BlinkWithoutDelay
 */

// constants won't change. Used here to set a pin number :
const int ledPinMin =  4;      // the number of the LED pin
const int ledPinMax = 13;

unsigned int state = ledPinMin;  // state of the sequencer

// Generally, you should use "unsigned long" for variables that hold time
// The value will quickly become too large for an int to store
unsigned long previousMillis = 0;        // will store last time LED was updated

// constants won't change :
const long interval = 100;           // interval at which to blink (milliseconds)
unsigned short dir = 1;
void setup() {
  // set the digital pin as output:
  for (int i = ledPinMin; i <= ledPinMax; i++)
    pinMode( i, OUTPUT);

  dir = 1;
  state = ledPinMin; // reset state

}

void loop()
{

  // check to see if it's time to blink the LED; that is, if the
  // difference between the current time and last time you blinked
  // the LED is bigger than the interval at which you want to
  // blink the LED.
  unsigned long currentMillis = millis();
  
  if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;

    for ( int i = ledPinMin; i <= ledPinMax; i++)
    {

      if (i == state) {
        digitalWrite (i , HIGH);
      } else {
        digitalWrite (i , LOW);
      }
    }
    // increase state
    state = state +  dir;

    // check if we did reach the max
    if (state  == ledPinMax)
    {
      dir = -1 ;
    }
    else {
      if (state == ledPinMin) dir = 1;
    }

  }


}


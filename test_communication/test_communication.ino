/* Multikey_MC17 - 16-bit I2C port conversion of Keypad's Multikey
:: G. D. (Joe) Young Feb 12, 2013
:: MC23017 version - GDY May 19, 2014
::
|| @file MultiKey.ino
|| @version 1.0
|| @author Mark Stanley
|| @contact mstanley@technologist.com
||
|| @description
|| | The latest version, 3.0, of the keypad library supports up to 10
|| | active keys all being pressed at the same time. This sketch is an
|| | example of how you can get multiple key presses from a keypad or
|| | keyboard.
|| #
*/

#include <Keypad.h>
#include <Keypad_MC17.h>    // I2C i/o library for Keypad
#include <Wire.h>           // I2C library for Keypad_MC17

#define I2CADDR 0x0        // address of MCP23017 chip on I2C bus

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
char keys[ROWS][COLS] = {
  {'1','2','3', 'A'},
  {'4','5','6', 'B'},
  {'7','8','9', 'C'},
  {'*','0','#', 'D'}
};
byte rowPins[ROWS] = {7, 6, 5, 4}; //connect to the row pinouts of the kpd
byte colPins[COLS] = {3, 2, 1, 0}; //connect to the column pinouts of the kpd

// modify constructor for I2C i/o
Keypad_MC17 kpd( makeKeymap(keys), rowPins, colPins, ROWS, COLS, I2CADDR );



void setup() {
  Serial.begin(9600);
  //Wire.begin( );
  kpd.begin( );                // now does not starts wire library
  //kpd.setDebounceTime(1);

  Serial.println("Init Done");
}

unsigned long loopCount = 0;
unsigned long startTime = millis();
String msg = "";



void loop() {

  loopCount++;
  if ( (millis()-startTime)>1000 ) {
      //Serial.println(loopCount);
      startTime = millis();
      loopCount = 0;
  }

  // Fills kpd.key[ ] array with up-to 10 active keys.
  // Returns true if there are ANY active keys.
  if (kpd.getKeys())
  {
    Serial.print("Greg");

    for (int i=0; i<LIST_MAX; i++)   // Scan the whole key list.
    {
      if ( kpd.key[i].stateChanged )   // Only find keys that have changed state.
      {
        switch (kpd.key[i].kstate) {  // Report active key state : IDLE, PRESSED, HOLD, or RELEASED
            case PRESSED:
                msg = " PRESSED.";
                break;
            case HOLD:
                msg = " HOLD.";
                break;
            case RELEASED:
                msg = " RELEASED.";
                break;
            case IDLE:
                msg = " IDLE.";
        }
        Serial.print("Key ");
        Serial.print(kpd.key[i].kchar);
        Serial.println(msg);
      }
    }
  }
}  // End loop

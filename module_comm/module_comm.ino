#include <Wire.h>
#include <Adafruit_MCP23017.h>
#include "Adafruit_Keypad.h"

int delai_latence=0;
int digit1 = 0b0000000100000000; // pin 8 
int digit2 = 0b0000100000000000; // pin 11
int digit3 = 0b0001000000000000; // pin 12 
int digit4 = 0b0000000000000100; //pin 2; 
int segA =   0b0000001000000000; // 9;
int segB =   0b0010000000000000; // 13;
int segC =   0b0000000000010000; //4;
int segD =   0b0000000001000000; // 6;
int segE =   0b0000000010000000; // 7;
int segF =   0b0000010000000000; //10;
int segG =   0b0000000000001000; // 3;
int dp =     0b0000000000100000; // 5; //dp = digital point


int BASE_MASK = digit1 | digit2| digit3 | digit4;
int DIGIT1 = BASE_MASK & ~digit1;
int DIGIT2 = BASE_MASK & ~digit2;
int DIGIT3 = BASE_MASK & ~digit3;
int DIGIT4 = BASE_MASK & ~digit4;

int INDEX_EMPTY = 16;
int seg_vals[17] = {
  segA | segB | segC | segD | segE | segF, 
  segB | segC , 
  segA | segB |  segD | segE | segG,
  segA | segB | segC | segD | segG,
  segB | segC | segF | segG, 
  segA | segC | segD | segF | segG,
  segA | segC | segD | segE | segF | segG,
  segA | segB | segC,
  segA | segB | segC | segD | segE | segF | segG,
  segA | segB | segC | segD | segF | segG,
  segA | segB | segC | segE | segF | segG,
  segC | segD | segE | segF | segG,
  segA | segD | segE | segF,
  segB | segC | segD | segE | segG,
  segA | segD | segE | segF | segG,
  segA | segE | segF | segG,
  dp,
};
Adafruit_MCP23017 mcp;

const byte ROWS = 4; // rows
const byte COLS = 4; // columns
//define the symbols on the buttons of the keypads
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {5, 4, 3, 2}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {9, 8, 7, 6}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Adafruit_Keypad customKeypad = Adafruit_Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS);

char code[4] = {'1', '9', '2', '7'};
int index_code = 0;
char frame_buffer[4] = {' ', ' ', ' ' ,' '};

#define REF_LED 11
#define MORSE_LED 12


void setup()
{
  Serial.begin(9600);
  customKeypad.begin();
  
  mcp.begin();
  for (int i = 0; i < 16; i++) {
    mcp.pinMode(i, OUTPUT);
  }  
  pinMode(REF_LED, OUTPUT);
  pinMode(MORSE_LED, OUTPUT);
}

int convert_to_hex(char c)
{
  if ( (c - '0') < 10 && (c - '0') >= 0)
    return (c - '0');
  else if ( (c - 'A') < 6 && (c - 'A') >= 0)
    return (c - 'A' + 10);
  else 
    return INDEX_EMPTY;
}


void display_frame_buffer()
{

  mcp.writeGPIOAB( seg_vals[convert_to_hex(frame_buffer[0])] | DIGIT1);
  mcp.writeGPIOAB(0 | BASE_MASK );
  mcp.writeGPIOAB( seg_vals[convert_to_hex(frame_buffer[1])] | DIGIT2);
  mcp.writeGPIOAB(0 | BASE_MASK);
  mcp.writeGPIOAB( seg_vals[convert_to_hex(frame_buffer[2])] | DIGIT3);
  mcp.writeGPIOAB(0 | BASE_MASK);
  mcp.writeGPIOAB( seg_vals[convert_to_hex(frame_buffer[3])] | DIGIT4);
  mcp.writeGPIOAB(0 | BASE_MASK); 
}

#define BASE_FREQUENCY 1000

enum LED_STATE {
  SPACE,
  WAIT_1,
  WAIT_2
};

#define SIZE_PATTERN 13

LED_STATE morse_digit[10][SIZE_PATTERN] = {
  {SPACE, WAIT_2, SPACE, WAIT_2, SPACE, WAIT_2, SPACE, WAIT_2, SPACE, WAIT_2, SPACE, SPACE, SPACE},
  {SPACE, WAIT_1, SPACE, WAIT_2, SPACE, WAIT_2, SPACE, WAIT_2, SPACE, WAIT_2, SPACE, SPACE, SPACE},
  {SPACE, WAIT_1, SPACE, WAIT_1, SPACE, WAIT_2, SPACE, WAIT_2, SPACE, WAIT_2, SPACE, SPACE, SPACE},
  {SPACE, WAIT_1, SPACE, WAIT_1, SPACE, WAIT_1, SPACE, WAIT_2, SPACE, WAIT_2, SPACE, SPACE, SPACE},
  {SPACE, WAIT_1, SPACE, WAIT_1, SPACE, WAIT_1, SPACE, WAIT_1, SPACE, WAIT_2, SPACE, SPACE, SPACE},
  {SPACE, WAIT_1, SPACE, WAIT_1, SPACE, WAIT_1, SPACE, WAIT_1, SPACE, WAIT_1, SPACE, SPACE, SPACE},
  {SPACE, WAIT_2, SPACE, WAIT_1, SPACE, WAIT_1, SPACE, WAIT_1, SPACE, WAIT_1, SPACE, SPACE, SPACE},
  {SPACE, WAIT_2, SPACE, WAIT_2, SPACE, WAIT_1, SPACE, WAIT_1, SPACE, WAIT_1, SPACE, SPACE, SPACE},
  {SPACE, WAIT_2, SPACE, WAIT_2, SPACE, WAIT_2, SPACE, WAIT_1, SPACE, WAIT_1, SPACE, SPACE, SPACE},
  {SPACE, WAIT_2, SPACE, WAIT_2, SPACE, WAIT_2, SPACE, WAIT_2, SPACE, WAIT_1, SPACE, SPACE, SPACE},
};

int current_step = 0;
int morse_led_state = LOW;
unsigned long morse_led_timestamp = 0;

void blink_morse_led()
{
  
  unsigned long currentMillis = millis();
  int digit_to_print = convert_to_hex(code[index_code]);

  unsigned long wait_time = morse_digit[digit_to_print][current_step] == WAIT_2 ? 2*BASE_FREQUENCY : BASE_FREQUENCY;

  if (currentMillis - morse_led_timestamp >= wait_time) {

    Serial.print(morse_led_timestamp);
    Serial.print(" ");
    Serial.println(currentMillis);

    morse_led_timestamp = currentMillis;        
    current_step++;
    if (current_step == SIZE_PATTERN) current_step = 0;

    if (morse_digit[digit_to_print][current_step] == SPACE) {
      morse_led_state = LOW;      
    }
    else {
      morse_led_state = HIGH;
    }
  }
 
  digitalWrite(MORSE_LED, morse_led_state);
}

unsigned long ref_led_timestamp = 0;
int ref_led_state= LOW;
void blink_ref_led()
{
  unsigned long currentMillis = millis();

  if ( (currentMillis - ref_led_timestamp) >= BASE_FREQUENCY) {
    ref_led_timestamp = currentMillis;

    if (ref_led_state == LOW) {
      ref_led_state = HIGH;
    } else {
      ref_led_state = LOW;
    }
  }
  digitalWrite(REF_LED, ref_led_state);
}

bool done = false;
void loop()
{
  if (!done) {
    customKeypad.tick();
    while(customKeypad.available()){
      keypadEvent e = customKeypad.read();
      if(e.bit.EVENT == KEY_JUST_RELEASED) 
      {
        char carac = (char)e.bit.KEY;
        if (carac == code[index_code]) {
          frame_buffer[index_code] = code[index_code];
          index_code++;

          //Reset the morse code 
           current_step = 0;
          
          if (index_code == 4) done = true;
        }
        else {
          for (int i = 0 ; i < index_code; i++)
            frame_buffer[i] = ' ';
          index_code = 0;
        }
      }
    }
    display_frame_buffer();   
    blink_ref_led();
    blink_morse_led();
  }

  if (done) {
    for (int i = 0; i < 125; i++)
      display_frame_buffer();
    delay(500);

    digitalWrite(REF_LED, LOW);
    digitalWrite(MORSE_LED, LOW);
  } 
}

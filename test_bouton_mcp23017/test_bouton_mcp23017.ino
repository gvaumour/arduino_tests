#include <Wire.h>
#include "Adafruit_MCP23017.h"

Adafruit_MCP23017 mcp;

int com_buttons[4];
char result[100];

void setup() {

  Serial.begin(9600);

  mcp.begin();

  for (int i = 8; i < 12 ; i++) {
    mcp.pinMode(i, INPUT); 
    mcp.pullUp(i,HIGH);
  } 

  for (int i = 0; i < 4; i++) {
    com_buttons[i] = mcp.digitalRead(i+8);
  }

  Serial.println("Initialization done");

}

void loop() {

  for (int i = 0; i < 4; i++) {
     int state = mcp.digitalRead(i+8);
  
    if (state != com_buttons[i]) {
      com_buttons[i] = state;
      const char* state_str = (state == LOW) ? "RELEASED" : "PRESSED";
      
      sprintf(result, "Bouton %d %s", i , state_str);
      Serial.println(result);
    }
  }
  delay(10);
}

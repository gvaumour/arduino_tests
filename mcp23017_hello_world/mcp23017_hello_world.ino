#include <Wire.h>
#include "Adafruit_MCP23017.h"

Adafruit_MCP23017 mcp[2];

int leds[4][5] = {
  {3, 4, 5, 6, 7},
  {0, 1, 2, 12, 10},
  {6, 7, 5, 3, 4},
  {10, 9, 11, 8, 12}
};


void setup() {
  mcp[0].begin();
  mcp[1].begin(1);

  for (int j = 0; j < 2; j++) {
    for (int i = 0; i < 16 ; i++) {
      mcp[j].pinMode(i, OUTPUT); 
    } 
  }
  for (int j = 0; j < 2; j++) {
    for (int i = 0; i < 16 ; i++) {
      mcp[j].digitalWrite(i, LOW); 
    } 
  }
}
void loop() {
  int index_mcp;

  for(int i = 0 ; i < 4 ; i++) {
    for(int j = 0 ; j < 5; j++) {
      index_mcp = i < 2 ? 0 : 1;
      mcp[index_mcp].digitalWrite(leds[i][j] , HIGH);
      delay(300);
      mcp[index_mcp].digitalWrite(leds[i][j] , LOW);
    }
  }
}

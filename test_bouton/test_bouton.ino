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

  Serial.begin(9600);
  
  pinMode(8, INPUT);
  pinMode(7, INPUT);
  pinMode(6, INPUT);
  pinMode(5, INPUT);
}

int buttons[4] = {LOW, LOW, LOW, LOW};
int value[4] = {0, 0, 0, 0};

void switch_line(int index_line)
{
  int index_mcp = index_line < 2 ? 0 : 1;
  if (buttons[index_line] == HIGH) {
    for(int j = 0 ; j < 5; j++) {
      mcp[index_mcp].digitalWrite(leds[index_line][j] , HIGH);
    }
  }
  else {
    for(int j = 0 ; j < 5; j++) {
       mcp[index_mcp].digitalWrite(leds[index_line][j] , LOW);
    }
  }
}

void update_value(int index_line)
{
  int index_mcp = index_line < 2 ? 0 : 1;
  for (int i = 0 ; i < 5; i++){
    Serial.print(index_line);
    Serial.print(", value = ");
    Serial.println(value[index_line]);

    int mask = 0x1 << i;
    mcp[index_mcp].digitalWrite(leds[index_line][i], (mask & value[index_line]) > 0 ? HIGH : LOW);
  }
}



void loop() {
  int index_mcp;
  for (int i = 0; i < 4; i++) {
    int last_state = buttons[i];
    buttons[i] = digitalRead(i+5);
    if (last_state == LOW && buttons[i] == HIGH) {
      value[i]++;
      if (value[i] == 32) 
        value[i] = 0;
      Serial.println("Change state");
      update_value(i);

    }
  }

//  for (int i = 0; i < 4; i++)
}

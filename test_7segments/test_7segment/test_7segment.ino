#include <Wire.h>
#include <Adafruit_MCP23017.h>



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

int seg_vals[16] = {
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
};
Adafruit_MCP23017 mcp;


void setup()
{
  mcp.begin();
  for (int i = 0; i < 16; i++) {
    mcp.pinMode(i, OUTPUT);
  }  
}

void loop()
{
    for (int i = 0 ; i < 250 ; i++) {
      mcp.writeGPIOAB( seg_vals[10] | DIGIT1);
      mcp.writeGPIOAB(0 | BASE_MASK );
      mcp.writeGPIOAB( seg_vals[11] | DIGIT2);
      mcp.writeGPIOAB(0 | BASE_MASK);
      mcp.writeGPIOAB( seg_vals[12] | DIGIT3);
      mcp.writeGPIOAB(0 | BASE_MASK);
      mcp.writeGPIOAB( seg_vals[13] | DIGIT4);
      mcp.writeGPIOAB(0 | BASE_MASK);    
    }
    for (int i = 0 ; i < 500 ; i++) {
      mcp.writeGPIOAB( seg_vals[14] | DIGIT1);
      mcp.writeGPIOAB(0 | BASE_MASK );
      mcp.writeGPIOAB( seg_vals[15] | DIGIT2);
      mcp.writeGPIOAB(0 | BASE_MASK );
    }
  
//affiche4digits(2017);
}

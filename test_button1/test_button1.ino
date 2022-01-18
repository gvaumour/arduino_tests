#include <Wire.h>

bool default_state1;
bool default_state0;

int led_state0 = LOW;
int led_state1 = LOW;

void setup() {

  Serial.begin(9600);
  pinMode(12, INPUT_PULLUP);
  pinMode(13, INPUT_PULLUP);

  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);

  digitalWrite(10 , led_state0);
  digitalWrite(11 , led_state1);

  Serial.println("Initialization done");

}

int readButton(int pin)
{
  int sum = 0;
  int stuff= 0;
  for (int i = 0 ; i < 10; i++){
    stuff = digitalRead(pin);
    //Serial.print("stuff = ");
    //Serial.println(stuff);
    sum += (stuff == HIGH) ? 1: 0;
  }

  //Serial.print("sum= ");
  //Serial.println(sum);
  
  return (sum > 0 ) ? HIGH : LOW;
}

void loop() {

  int state0 = digitalRead(12);
  int state1 = digitalRead(13);
  
  Serial.print("State0 = ");
  Serial.print(state0);
  Serial.print(", state1 = ");
  Serial.println(state1);

  if (state0 != default_state0) {
    default_state0 = state0;
    led_state0 = (default_state0 == HIGH) ? HIGH : LOW;
  }
  if (state1 != default_state1) {
    default_state1 = state1;
    led_state1 = (default_state1 == HIGH) ? HIGH : LOW;
  }
  digitalWrite(10, led_state0);
  digitalWrite(11, led_state1);
}

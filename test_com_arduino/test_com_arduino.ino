#include <Wire.h>

void setup() {
  // Start the I2C Bus as Master
  Wire.begin(); 
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  
}

void loop() {
  Wire.beginTransmission(9); // transmit to device #9
  Wire.write(100);              // sends x 
  Wire.endTransmission();    // stop transmitting
  Wire.requestFrom(9, 6);    // request 6 bytes from slave device #8

  while (Wire.available()) { // slave may send less than requested
    char x = Wire.read(); // receive a byte as character
    Serial.print(x);         // print the character

  }
  delay(500);

}

#include <Wire.h>

int ledPin = 11;
int x = 0;
void setup() {
  Serial.begin(9600);
  pinMode (ledPin, OUTPUT);
  // Start the I2C Bus as Slave on address 9
  Wire.begin(9); 
  // Attach a function to trigger when something is received.
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);

  pinMode(LED_BUILTIN, OUTPUT);
}
void requestEvent()
{
  Wire.write("Hello ");
}

void receiveEvent(int bytes) {
  x = Wire.read();    // read one character from the I2C
}

unsigned long previousMillis = 0;
int ledState = LOW;

void loop() {
  Serial.println(x);
  int pwm = map(x,0, 1023, 0, 255); 
  analogWrite(ledPin, x);

   unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= 1000) {
    previousMillis = currentMillis;

    if (ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }
  }
  digitalWrite(LED_BUILTIN, ledState);
}

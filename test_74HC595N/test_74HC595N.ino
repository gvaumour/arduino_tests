//**************************************************************//
//  Name    : shiftOutCode, Hello World
//  Author  : Carlyn Maw,Tom Igoe, David A. Mellis
//  Date    : 25 Oct, 2006
//  Modified: 23 Mar 2010
//  Version : 2.0
//  Notes   : Code for using a 74HC595 Shift Register           //
//          : to count from 0 to 255
//****************************************************************

//Pin connected to ST_CP of 74HC595
int latchPin = 10;

//Pin connected to SH_CP of 74HC595
int clockPin = 11;

////Pin connected to DS of 74HC595
int dataPin = 9;

void setup() {
  //set pins to output so you can control the shift register
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);


  Serial.begin(9600);
}

void loop() {

  // take the latchPin low so
  // the LEDs don't change while you're sending in bits:
  
  for (int i = 0 ; i < 24; i++){

    if (i == 0 || i == 8 || i == 16 || i == 17)
      continue;

    digitalWrite(latchPin, LOW);

    if (i > 0 && i < 8){
      shiftOut(dataPin, clockPin, MSBFIRST, 0x00);
      shiftOut(dataPin, clockPin, MSBFIRST, 0x00);
      shiftOut(dataPin, clockPin, MSBFIRST, 1 << (i%8));    
      Serial.println("1");

    }
    else if( i > 8 && i < 16){
      shiftOut(dataPin, clockPin, MSBFIRST, 0x00);
      shiftOut(dataPin, clockPin, MSBFIRST, 1 << (i%8));
      shiftOut(dataPin, clockPin, MSBFIRST, 0x00);      
      Serial.println("2");
    }
    else {

      shiftOut(dataPin, clockPin, MSBFIRST, 1 << (i%8));
      shiftOut(dataPin, clockPin, MSBFIRST, 0x00);
      shiftOut(dataPin, clockPin, MSBFIRST, 0x00);      
      Serial.println("3");
    }
    Serial.print(i);
    Serial.println("greg");
    digitalWrite(latchPin, HIGH);
    delay(100);
  }
}

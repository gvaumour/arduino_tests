//
// Use of timer2 to generate a signal for a particular frequency on pin 11
//
//

const int sensor_clock_pin = 11;   // OC2A output pin for ATmega328 boards
int frame_request_pin = 10; // Also called DET_UNKOWN_SIG
int image_enable_pin = 9; // Must be pulled-up 
int sensor_output_a = A1;  // Output A
int sensor_output_b = A2;  // Output B

const int alim_25V= 6;  


// Constants are computed at compile time

// If you change the prescale value, it affects CS22, CS21, and CS20
// For a given prescale value, the eight-bit number that you
// load into OCR2A determines the frequency according to the
// following formulas:
//
// With no prescaling, an ocr2val of 3 causes the output pin to
// toggle the value every four CPU clock cycles. That is, the
// period is equal to eight slock cycles.
//
// With F_CPU = 16 MHz, the result is 2 MHz.
//
// Note that the prescale value is just for printing; changing it here
// does not change the clock division ratio for the timer!  To change
// the timer prescale division, use different bits for CS22:0 below
const int prescale  = 1;
const int ocr2aval  = 1; 
// The following are scaled for convenient printing
//

// Period in microseconds
const float period    = prescale * (ocr2aval+1) / (F_CPU/1.0e6);

// Frequency in Hz
const float freq      = 1.0e6 / period;

void setup()
{
    pinMode(sensor_clock_pin, OUTPUT);
    Serial.begin(9600);
 
    // Set Timer 2 CTC mode with no prescaling.  OC2A toggles on compare match
    //
    // WGM22:0 = 010: CTC Mode, toggle OC 
    // WGM2 bits 1 and 0 are in TCCR2A,
    // WGM2 bit 2 is in TCCR2B
    // COM2A0 sets OC2A (arduino pin 11 on Uno or Duemilanove) to toggle on compare match
    //
    TCCR2A = ((1 << WGM21) | (1 << COM2A0));

    // Set Timer 2  No prescaling  (i.e. prescale division = 1)
    //
    // CS22:0 = 001: Use CPU clock with no prescaling
    // CS2 bits 2:0 are all in TCCR2B
    TCCR2B = (1 << CS20);

    // Make sure Compare-match register A interrupt for timer2 is disabled
    TIMSK2 = 0;
    // This value determines the output frequency
    OCR2A = ocr2aval;
/*

    Serial.print("F_CPU    = ");
    Serial.println(F_CPU);
    
    Serial.print("Period    = ");
    Serial.print(period); 
    Serial.println(" microseconds");
    Serial.print("Frequency = ");
    Serial.print(freq); 
    Serial.println(" Hz");
  */  
    pinMode(frame_request_pin, OUTPUT);
    pinMode(image_enable_pin, OUTPUT);
    pinMode(sensor_clock_pin, OUTPUT);
    pinMode(alim_25V, OUTPUT);

    pinMode(sensor_output_a, INPUT);
    pinMode(sensor_output_b, INPUT);
}


void loop()
{

  analogWrite(frame_request_pin, 0);
  analogWrite(image_enable_pin, 124);
  analogWrite(alim_25V, 127);
/*
  analogWrite(image_enable_pin, 127);
  analogWrite(alim_25V, 154);
*/
  delay(100); 
  analogWrite(frame_request_pin, 255);
  delay(50); 
  analogWrite(frame_request_pin, 0);

  for (int i = 0 ; i < 20000; i++) {
    int a = analogRead(sensor_output_a);
    int b = analogRead(sensor_output_b);
    //Serial.print(a);
    //Serial.print(" ");
    Serial.println(b);
  }
}                          

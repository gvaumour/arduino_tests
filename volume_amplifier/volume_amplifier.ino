 #include <WSWire.h>
 
// 0x4B is the default i2c address
#define MAX9744_I2CADDR 0x4A

// We'll track the volume level in this variable.
int8_t thevol = 63;

void setup() {
  Serial.begin(9600);
  Serial.println("MAX9744 demo");

  Wire.begin();
  pinMode(7, OUTPUT);
  digitalWrite(7, HIGH);

  if (! setvolume(thevol)) {
    Serial.println("Failed to set volume, MAX9744 not found!");
    digitalWrite(7, LOW);
    while (1);
  }
}


// Setting the volume is very simple! Just write the 6-bit
// volume to the i2c bus. That's it!
boolean setvolume(int8_t v) {
  // cant be higher than 63 or lower than 0
  if (v > 63) v = 63;
  if (v < 0) v = 0;
  Serial.print("Setting volume to ");
  Serial.println(v);
  
  Wire.beginTransmission(MAX9744_I2CADDR);
  Serial.println("Begin writing");
  Wire.write(v);
 Serial.println("End writing");
 int ret = Wire.endTransmission();
   if (ret == 0) 
  {
    Serial.println("End transmission");
    return true;
     
  }
  else 
  {
    Serial.print("Not ok ret = ");
  Serial.println(ret);
    return false; 
  }
}

// Read in + and - characters to set the volume.
void loop() {

  if (! Serial.available())  { 
   // digitalWrite(7, LOW);
    return;
  }
  
  // read a character from serial console
  char c = Serial.read();
  
  // increase
  if (c == '+') {
    thevol++;
  }
  // decrease
  else if (c == '-') {
    thevol--;
  }
  // ignore anything else
  else 
    return;
    
  if (thevol > 63) thevol = 63;
  if (thevol < 0) thevol = 0;

  setvolume(thevol);
}

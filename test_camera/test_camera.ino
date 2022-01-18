
// Capteur => Breadboard => Arduinio 
// Data 
// 2 (out) => 30 => 4 
// 3  (out) => 29 => 5
// 6 (input) => 28 => 6
// 7 (inout) => 27 => 7
// 10 (input) => 26 => 8
// 
// Clock/VCC/Reset
// 11 (input) => 25 => 9
// 13 (input)  => 24 => 10
// 14 => 23 => 11 
// 15 => 22 => 12
// 18 => 21 => 3.3V 

void setup() {
  // put your setup code here, to run once:

  pinMode(4, INPUT);
  pinMode(5, INPUT);
  pinMode(6, INPUT);
  pinMode(7, INPUT);
  pinMode(8, INPUT);

  
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);


  Serial.begin(9600);
}

void loop() {

  digitalWrite(12, LOW);
  digitalWrite(9, HIGH);
  digitalWrite(10, HIGH);
  digitalWrite(11, HIGH);

  
  // put your main code here, to run repeatedly:

  int sum = 0; 
  for (int i = 4; i <= 8 ; i++){
    int value = digitalRead(i);
    sum += value << i;
  }

  Serial.print("Inputs are 0x");
  Serial.println(sum);
  delay(500);
}

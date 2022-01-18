/*
 * 
 * Typical pin layout used:
 * -----------------------------------------------------------------------------------------
 *             MFRC522      Arduino       Arduino   Arduino    Arduino          Arduino
 *             Reader/PCD   Uno/101       Mega      Nano v3    Leonardo/Micro   Pro Micro
 * Signal      Pin          Pin           Pin       Pin        Pin              Pin
 * -----------------------------------------------------------------------------------------
 * RST/Reset   RST          9             5         D9         RESET/ICSP-5     RST
 * SPI SS      SDA(SS)      10            53        D10        10               10
 * SPI MOSI    MOSI         11 / ICSP-4   51        D11        ICSP-4           16
 * SPI MISO    MISO         12 / ICSP-1   50        D12        ICSP-1           14
 * SPI SCK     SCK          13 / ICSP-3   52        D13        ICSP-3           15
 */

#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         9          // Configurable, see typical pin layout above
#define SS_PIN          10         // Configurable, see typical pin layout above


static byte BADGE1_UID[4] = {0x5A, 0x5B, 0xCB, 0x6A};
//#define CARD1_UID 0x2A375DBD


MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance

int status = LOW;
bool led_status = LOW;

void setup() {
  Serial.begin(9600);   // Initialize serial communications with the PC
  while (!Serial);    // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
  SPI.begin();      // Init SPI bus
  mfrc522.PCD_Init();   // Init MFRC522
  //delay(4);       // Optional delay. Some board do need more time after init to be ready, see Readme
  //mfrc522.PCD_DumpVersionToSerial();  // Show details of PCD - MFRC522 Card Reader details
  //Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));
  pinMode(8, OUTPUT);
}

bool is_badge_uid(MFRC522::Uid a)
{
  int i;
  if (a.size == 4) {
    for (i = 0 ; i < 4; i++) {
      if (a.uidByte[i] != BADGE1_UID[i])
        return false;
    }
  }
  return true;
}

void loop() {
  // Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
  if (mfrc522.PICC_IsNewCardPresent()) {
    Serial.println("Detected a RFID tag");
    if (mfrc522.PICC_ReadCardSerial()) {
      Serial.println("Read the uid info");
      if (is_badge_uid(mfrc522.uid)){
        status = HIGH;
        Serial.println("status = HIGH");
      }
      else {
        Serial.println("status = LOW");
        status = LOW;
      }
    }
  }
  digitalWrite(8 , status);
  /*
  if (status) {
    if (timer - last_time >  BLINKING_TIME) {
      digitalWrite(8, led_status);
    }
  }*/
  // Dump debug info about the card; PICC_HaltA() is automatically called
  //mfrc522.PICC_DumpToSerial(&(mfrc522.uid));
}

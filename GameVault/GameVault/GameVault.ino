#include "config.h"

void setup() {

  lcd.init();
  lcd.backlight();

  SPI.begin();
  rfid.PCD_Init();

  Serial.begin(9600);

}
void loop() {
  
  if (!rfid.PICC_IsNewCardPresent()) {
    // If there is no new card readed do not contain to other steps of loop
    return; 
  }

  else if (!rfid.PICC_ReadCardSerial()) {
    // There is a card that has been readed but it does not in a shape of desired format
    display("Cannot read card");
    return;
  } else {
    // Card readed successfully!

    // Create a char array for store card id. 
    char UID[18];
    UID[0] = '\0';
  
    for (byte i = 0; i < rfid.uid.size; i++) {
      // destination: &UID[i * 2]
      // format: "%02X"
      // write: rfid.uid.uidByte[i]
      sprintf(&UID[i * 2], "%02X", rfid.uid.uidByte[i]);
    }

    // display the card id that has been written
    display(UID);

    // If the card's ID has matched with our 4 local card ID, print card no and card code.
    for (int i=0;i<4;i++) {

      if ( strcmp(UID, cardArray[i]) == 0 ) {

        Serial.print("Card no: ");
        Serial.print(i + 1);
        Serial.print("   Card code: ");
        Serial.println(UID);

      }

    }

    // Securely finish the reading process
    rfid.PICC_HaltA();
    rfid.PCD_StopCrypto1();
  }
}

void display(char* txt) {

  lcd.clear();
  lcd.setCursor(0,0);

  int length = strlen(txt);

  if (length > 16) {

    for(int i = 0; i < 16; i++) lcd.print(txt[i]);
    lcd.setCursor(0, 1);
    lcd.print(&txt[16]);

  } else {
    lcd.print(txt);
  }

}
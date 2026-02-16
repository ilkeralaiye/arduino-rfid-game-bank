#include "config.h"

void setup() {

  lcd.init();
  lcd.backlight();

  Serial.begin(9600);

  display("Hello, world, this is great");

}

void loop() {


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
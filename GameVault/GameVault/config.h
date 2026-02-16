#ifndef CONFIG_H
#define CONFIG_H

#include <Wire.h>
#include <LiquidCrystal_I2C.h> // LCD Screen
#include <Keypad.h> // Keypad
#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN A0

const byte rows[4] = {2, 3, 4, 5};
const byte cols[4] = {6, 7, 8, 9};

char *cardArray[4] = {"AAE96E06", "25DB6F06", "CE6E5906", "C7065906"};

char keys[4][4] = {
  {'D', 'C', 'B', 'A'},
  {'#', '9', '6', '3'},
  {'0', '8', '5', '2'},
  {'*', '7', '4', '1'},
};

LiquidCrystal_I2C lcd(0x27, 16, 2);
Keypad keypad = Keypad(makeKeymap(keys), rows, cols, 4, 4);

MFRC522 rfid(SS_PIN, RST_PIN);

MFRC522::MIFARE_Key key;

#endif
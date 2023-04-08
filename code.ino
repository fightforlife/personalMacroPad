#include "DigiKeyboard.h"
#include <OnewireKeypad.h>

#define KEY_F13 0x68 // Keyboard F13
#define KEY_F14 0x69 // Keyboard F14
#define KEY_F15 0x6a // Keyboard F15
#define KEY_F16 0x6b // Keyboard F16
#define KEY_F17 0x6c // Keyboard F17
#define KEY_F18 0x6d // Keyboard F18
#define KEY_F19 0x6e // Keyboard F19
#define KEY_F20 0x6f // Keyboard F20
#define KEY_F21 0x70 // Keyboard F21
#define KEY_MOD_LCTRL  0x01
#define KEY_MOD_LSHIFT 0x02

const char KEYS1[] = {
  KEY_F15, KEY_F14, KEY_F13,
  KEY_F18, KEY_F17, KEY_F16,
  KEY_F21, KEY_F20, KEY_F19,
};
const char KEYS2[] = {
  KEY_F13, KEY_F14, KEY_F15,
  KEY_F16, KEY_F17, KEY_F18,
  KEY_F19, KEY_F20, KEY_F21,
};
OnewireKeypad <Print, 9 > KP1(Serial, KEYS1, 3, 3, 0, 10000, 2200, 2200);
OnewireKeypad <Print, 9 > KP2(Serial, KEYS2, 3, 3, 1, 10000, 2200, 2200);

void setup() {
  KP1.SetKeypadVoltage(4.82);
  KP1.SetDebounceTime(5);
  KP1.SetHoldTime(500);
  KP2.SetKeypadVoltage(4.82);
  KP2.SetDebounceTime(5);
  KP2.SetHoldTime(500);
}


void loop() {

  if ( char key = KP1.Getkey() ) {
    switch (KP1.Key_State()) {
      case PRESSED:
        digitalWrite(1, HIGH);
        DigiKeyboard.sendKeyPress(key,KEY_MOD_LCTRL);
        break;

      case RELEASED:
        digitalWrite(1, LOW);  
        DigiKeyboard.sendKeyStroke(0);
        break;

      case HELD:
        digitalWrite(1, HIGH);
        DigiKeyboard.sendKeyPress(key,KEY_MOD_LCTRL);
        break;
    }
  }
  //DigiKeyboard.update();

  if ( char key = KP2.Getkey() ) {
    switch (KP2.Key_State()) {
      case PRESSED:
        digitalWrite(1, HIGH);
        DigiKeyboard.sendKeyPress(key,KEY_MOD_LSHIFT);
        break;

      case RELEASED:
        digitalWrite(1, LOW);  
        DigiKeyboard.sendKeyStroke(0);
        break;

      case HELD:
        digitalWrite(1, HIGH);
        DigiKeyboard.sendKeyPress(key,KEY_MOD_LSHIFT);
        break;
    }
  }
  DigiKeyboard.update();  
}
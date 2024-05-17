/*
This is USB-MIDI example using matrix Keypad as a MIDI controller over ESP32 chip.
Works only with USB OTG on.
You can use https://midi.city/ to get testing MIDI sound generator.
*/

#if ARDUINO_USB_MODE
#warning This sketch should be used when USB is in OTG mode
void setup() {}
void loop() {}
#else

#include <math.h>

#include "USB.h"
#include "USBMIDI.h"
#include <Keypad.h>

USBMIDI MIDI;

#define MIDI_NOTE_C4 60
#define MIDI_NOTE_D4 62
#define MIDI_NOTE_E4 64
#define MIDI_NOTE_F4 65
#define MIDI_NOTE_G4 67
#define MIDI_NOTE_A4 69
#define MIDI_NOTE_H4 71
#define MIDI_NOTE_C5 72

#define MIDI_NOTE_BMIN1 33

const byte ROWS = 4; //four rows
const byte COLS = 4; //three columns

char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

//ESP32S3 DevKit v1.1 PINS
byte rowPins[ROWS] = {4,5,6,7}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {15,16,17,18}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );


///// Arduino Hooks /////

void setup() {
  Serial.begin(115200);
  MIDI.begin();
  USB.begin();
}

void loop() {

  char key = keypad.getKey();
  
  if (key) {
    switch(key) {
      case '1':
        MIDI.noteOn(MIDI_NOTE_C4, 64);
        MIDI.noteOff(MIDI_NOTE_C4, 0);
        break; 
      case '2':
        MIDI.noteOn(MIDI_NOTE_D4, 64);
        MIDI.noteOff(MIDI_NOTE_D4, 0);
        break; 
      case '3':
        MIDI.noteOn(MIDI_NOTE_E4, 64);
        MIDI.noteOff(MIDI_NOTE_E4, 0);
        break; 
      case '4':
        MIDI.noteOn(MIDI_NOTE_F4, 64);
        MIDI.noteOff(MIDI_NOTE_F4, 0);
        break; 
      case '5':
        MIDI.noteOn(MIDI_NOTE_G4, 64);
        MIDI.noteOff(MIDI_NOTE_G4, 0);
        break; 
      case '6':
        MIDI.noteOn(MIDI_NOTE_A4, 64);
        MIDI.noteOff(MIDI_NOTE_A4, 0);
        break; 
      case '7':
        MIDI.noteOn(MIDI_NOTE_H4, 64);
        MIDI.noteOff(MIDI_NOTE_H4, 0);
        break; 
      case '8':
        MIDI.noteOn(MIDI_NOTE_C5, 64);
        MIDI.noteOff(MIDI_NOTE_C5, 0);
        break;
      default:
        MIDI.noteOn(MIDI_NOTE_BMIN1, 120);
        MIDI.noteOff(MIDI_NOTE_BMIN1, 0);
        break;         
    }
    Serial.println(key);
  }

}
#endif /* ARDUINO_USB_MODE */

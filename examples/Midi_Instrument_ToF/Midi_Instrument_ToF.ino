/*
This is an example of a Simple MIDI Instrument using an ESP32 with a native USB support stack (S2, S3,
etc.) and VL53L0X ToF sensor.
*/

#if ARDUINO_USB_MODE
#warning This sketch should be used when USB is in OTG mode
void setup() {}
void loop() {}
#else

#include <math.h>
#include "Adafruit_VL53L0X.h"
#include "USB.h"
#include "USBMIDI.h"

#define BUTTON_PIN 0

// static const uint8_t SDA = 8;
// static const uint8_t SCL = 9;

Adafruit_VL53L0X lox = Adafruit_VL53L0X();
USBMIDI MIDI;

void setup() {
  Serial.begin(115200);
  MIDI.begin();
  USB.begin();

  pinMode(BUTTON_PIN, INPUT_PULLUP);
  
  if (!lox.begin()) {
    Serial.println(F("Failed to boot VL53L0X"));
    while(1);
  }
}

void loop() {
  // If button is pressed, keed playing current note or keep off
  if (digitalRead(BUTTON_PIN) != LOW) {
    static uint8_t note = 0;
    uint8_t last_note = note;

    // Read ToF measurement data
    VL53L0X_RangingMeasurementData_t measure;
    lox.rangingTest(&measure, false); // pass in 'true' to get debug data printout!
    if (measure.RangeStatus != 4 && measure.RangeMilliMeter != 8191) {  // phase failures have incorrect data
      note = map(measure.RangeMilliMeter, 0, 800, 50, 70);
      //Serial.printf("Distance %d (mm)", measure.RangeMilliMeter);
    } else {
      note = 0;
      //Serial.println(" Measurement out of range ");
    }
  
    // Play new note and turn off previous note
    if(note != 0){
      MIDI.noteOn(note, 64);
    }
    if(last_note != note && last_note != 0 || note == 0){
      MIDI.noteOff(last_note, 0);
    }
  }
}
#endif /* ARDUINO_USB_MODE */

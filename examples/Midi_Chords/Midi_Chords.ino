/*
 * This example plays one of the pre-defined chords when one of the buttons connected to an ESP is pressed.
 * The potentiometer controls the scale in which the chords are played.
 * With the potentiometer all way to the left, the scale is C major.
 * The buttons are mapped like this:
 * GPIO0 - I chord (i.e. C major)
 * GPIO1 - IV chord (i.e. F major)
 * GPIO2 - V chord (i.e. G major)
 * GPIO3 - iv chord (i.e. A minor)
 * By rotating the potentiometer, you can change the scale, moving all the chords up and down.
 * You can modify the chords or add more by changing the "chords" array below.
 * You can define up to 4 MIDI notes per chord.
 */

#if ARDUINO_USB_MODE
#warning This sketch should be used when USB is in OTG mode
void setup() {}
void loop() {}
#else

#include "USB.h"
#include "USBMIDI.h"
USBMIDI MIDI;


#define MAX_NOTES_IN_CHORD 4

struct Chord {
  Chord(int gpio_, int n0 = -1, int n1 = -1, int n2 = -1, int n3 = -1) {
    gpio = gpio_;
    notes[0] = n0;
    notes[1] = n1;
    notes[2] = n2;
    notes[3] = n3;
    button_state = 0;
  }

  void setup() {
    pinMode(gpio, INPUT_PULLUP);
  }

  void updateState() {
    button_state = (button_state << 1) | digitalRead(gpio) | 0xfe00;
  }

  bool pressed() {
    return button_state == 0xff00;
  }

  bool released() {
    return button_state == 0xfe1f;
  }

  int gpio;
  uint16_t button_state;
  int notes[MAX_NOTES_IN_CHORD];
};

Chord chords[] = {
  Chord(0, 0, 4, 7),        // I chord
  Chord(35, 5, 9, 12),       // IV chord
  Chord(2, 7, 11, 14),      // V chord
  Chord(1, 9, 12, 16),      // iv chord
};

const int baseNote = 48;    // C3

static int lastScaleRoot = -1;
const char* scaleRootName[] = {
  "C",
  "C#",
  "D",
  "D#",
  "E",
  "F",
  "F#",
  "G",
  "G#",
  "A",
  "A#",
  "B"
};


void setup() {
  Serial.begin(115200);
  Serial.println("Starting MIDI example!");
  MIDI.begin();
  USB.begin();
    
  for (Chord& chord: chords) {
    chord.setup();
  }
}

void loop() {
  int scaleRoot = map(analogRead(5), 0, 4095, 0, 11);

  if (scaleRoot != lastScaleRoot) {
    Serial.printf("Scale: %s\n", scaleRootName[scaleRoot]);
    lastScaleRoot = scaleRoot;
  }

  for (Chord& chord: chords) {
    chord.updateState();
    if (chord.pressed()) {
      for (int note: chord.notes) {
        if (note != -1) {
          MIDI.noteOn(scaleRoot + note + baseNote, 64, 1);
        }
      }
      Serial.printf("Pressed (%d)\n", chord.gpio);
    } else if (chord.released()) {
      for (int note: chord.notes) {
        if (note != -1) {
          MIDI.noteOn(scaleRoot + note + baseNote, 0, 1);
        }
      }
      Serial.printf("Released (%d)\n", chord.gpio);
    }
  }
}
#endif /* ARDUINO_USB_MODE */

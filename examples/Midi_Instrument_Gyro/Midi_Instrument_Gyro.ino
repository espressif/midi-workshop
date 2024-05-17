/*
This is an example of a Simple MIDI Instrument using an ESP32 with a native USB support stack (S2, S3,
etc.) and MPU-6050 MotionTracking device (I2C 3-axis gyroscope, 3-axis accelerometer).
*/
#if ARDUINO_USB_MODE
#warning This sketch should be used when USB is in OTG mode
void setup() {}
void loop() {}
#else

#include <math.h>

#include "USB.h"
#include "USBMIDI.h"
USBMIDI MIDI;

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
Adafruit_MPU6050 mpu;

// static const uint8_t SDA = 8;
// static const uint8_t SCL = 9;

void setup()
{
    Serial.begin(115200);

    if (!mpu.begin())
    {
        Serial.println("Failed to find MPU6050 chip");
        while (1)
        {
            delay(10);
        }
    }
    Serial.println("MPU6050 Found!");

    // mpu.setAccelerometerRange(MPU6050_RANGE_4_G);
    // mpu.setGyroRange(MPU6050_RANGE_250_DEG);
    mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

    MIDI.begin();
    USB.begin();

    delay(100);
}

// Just to get the MIDI notes to the normal range
#define NOTE_SHIFT 48

void loop()
{
    // Get new sensor events with the readings
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);

    // Calculate the note from the tilt on Y axis
    int x = floor(a.acceleration.y * 1.25) + 12.5; // Get <-10.0, 10.0> measured MPU range to around <0.0, 25.0>
    int note = int(x) + NOTE_SHIFT;                // Shift the note to <48, 73> range

    // Stop playing other notes
    for (int i = 0; i <= 108; i++)
    {
        if (note != i)
        {
            MIDI.noteOff(i, 0);
        }
    }

    // Play the current calculated node on channel 1 (default)
    MIDI.noteOn(note, 64);

    // Use gyro to play some other notes once on channel 10
    if (g.gyro.x >= 3.0)
    {
        MIDI.noteOn(60, 64, 10);
        MIDI.noteOff(60, 0, 10);
    }
    if (g.gyro.z >= 3.0)
    {
        MIDI.noteOn(65, 64, 10);
        MIDI.noteOff(65, 0, 10);
    }
    if (g.gyro.y >= 3.0)
    {
        MIDI.noteOn(70, 64, 10);
        MIDI.noteOff(70, 0, 10);
    }

    delay(100);
}
#endif /* ARDUINO_USB_MODE */

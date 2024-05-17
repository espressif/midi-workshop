# USB MIDI workshop

## List of used hardware

- ESP32-S3 Devkit-C development board
- 2 USB cables
- Keypad (4x4 membrane matrix)
- Potentiometer
- Photoresistor
- Accelerometer + gyroscope (MPU-6050)
- Time of Flight distance sensor (VL53L0X) 
- Wires

## Software requirements 

- [Arduino IDE](https://www.arduino.cc/en/software)

### Arduino board library

Add `https://espressif.github.io/arduino-esp32/package_esp32_dev_index.json` URL to `File -> Preferences -> Additional boards manager URLs`.

Find and install `esp32` package in Board manager (version `3.0.0-rc3`).

For more detailed installation info click [here](https://docs.espressif.com/projects/arduino-esp32/en/latest/installing.html#installing-using-arduino-ide).

### Arduino libraries

- `Keypad`
- `Adafruit MPU6050`
- `Adafruit_VL53L0X`

Install via `Tools -> Manage libraries`.

## Board configuration

1. Set board to ESP32-S3 in `Tools -> Board -> esp32 -> ESP32S3 Dev Module`
1. Set USB mode to USB-OTG `Tools -> USB Mode -> USB-OTG (TinyUSB)`
1. Connect the dev board to the PC (UART USB port)
1. Select the according port in `Tools -> Port`
1. ___Optional___: Set Core Debug Level to `Debug` in `Tools -> Core Debug Level`
1. Connect the dev board to the PC with the second USB port as well
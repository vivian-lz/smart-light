# Smart Dorm Light

A custom ESP32-based smart controller for an existing IR-controlled RGBW dorm light.

The goal is to reverse-engineer the light's existing IR remote, reproduce its commands with an ESP32, and eventually build a custom PCB that adds smart-home functionality without modifying the original light.

## Project Goals

* Reverse-engineer the existing RGBW light's IR remote
* Capture and store IR commands such as:

  * Power
  * Red
  * Green
  * Blue
  * White
  * Brightness
  * Presets / modes
* Use an ESP32 to reproduce the remote's IR commands
* Control the light from a phone over Wi-Fi
* Create custom lighting presets
* Add automatic lighting based on ambient room brightness
* Design a custom PCB integrating the ESP32, IR circuitry, and ambient-light sensor
* Eventually package the electronics into a small enclosure

## System Overview

### Current System

```text
Original Remote
      |
      | Infrared
      v
RGBW Light
```

The original remote transmits encoded infrared commands that the light's internal IR receiver interprets.

### Planned System

```text
                  Wi-Fi
Phone  <---------------------->  ESP32
                                  |
                    +-------------+-------------+
                    |                           |
                    v                           v
               IR Transmitter             Ambient Light
                    |                       Sensor
                    v
                RGBW Light
```

The ESP32 will learn the commands transmitted by the original remote and later reproduce them using its own IR transmitter.

## Development Stages

### Phase 1 — IR Receiver / Reverse Engineering

Use an ESP32 and an IR receiver to investigate the existing remote.

The ESP32 will:

1. Detect the output of the IR receiver.
2. Measure the timing between signal transitions.
3. Print the captured timing information over USB serial.
4. Compare repeated transmissions of the same button.
5. Compare different buttons to determine how the commands differ.

Initial commands to investigate:

* Power
* Red
* Green
* Blue
* White
* Brightness Up
* Brightness Down
* Preset / Mode buttons

At this stage, the project does **not** need an IR transmitter, custom PCB, phone interface, or ambient-light sensor.

### Phase 2 — IR Transmission

Add an IR LED and transistor-based driver.

```text
ESP32 GPIO
    |
    v
Transistor Switch
    |
    v
IR LED
    |
    | Infrared
    v
RGBW Light
```

The ESP32 will reproduce a captured command and verify that the original light responds correctly.

The first target is:

> Capture the RED command → reproduce the RED command → light turns RED.

### Phase 3 — Phone Control

Add a simple web interface hosted by the ESP32.

Example controls:

* Power
* Color selection
* Brightness
* Presets
* Automatic mode

The phone communicates with the ESP32 over Wi-Fi, eliminating the need for a dedicated mobile app.

### Phase 4 — Ambient-Light Automation

Add an ambient-light sensor such as the BH1750.

The ESP32 can use measured room brightness to automatically control the light.

Example:

```text
Room becomes dark
       ↓
Ambient light < threshold
       ↓
Turn light ON
```

Hysteresis can be used to prevent the light from rapidly switching between ON and OFF around the threshold.

### Phase 5 — Custom PCB

Once the breadboard prototype works, design a custom PCB containing:

* ESP32 module
* IR receiver
* IR LED
* Transistor driver
* Ambient-light sensor
* USB-C power
* 3.3 V regulation
* Pushbuttons
* Status LED
* Test points

The PCB will be designed in KiCad.

## Hardware

### Prototype

* ESP32 development board
* IR receiver module
* Original RGBW light
* Original IR remote
* Breadboard
* Jumper wires
* Resistors
* NPN transistor or small logic-level NMOS for IR transmission

### Final PCB

Potential components:

* ESP32-C3 module
* IR receiver
* ~940 nm IR LED
* Logic-level NMOS transistor
* BH1750 ambient-light sensor
* 3.3 V regulator
* USB-C connector
* Pushbuttons
* Status LED
* Decoupling capacitors
* Test points

Component choices will be finalized after experimentally determining the IR characteristics of the existing remote.

## Firmware

The firmware will initially be developed using the Arduino IDE and ESP32 Arduino core.

Planned firmware functionality:

```text
IR signal capture
      ↓
Command storage
      ↓
IR command transmission
      ↓
Wi-Fi control
      ↓
Lighting presets
      ↓
Ambient-light automation
```

The initial firmware will focus only on capturing and inspecting IR receiver timing.

## Engineering Questions to Investigate

* What IR carrier frequency does the original remote use?
* What IR encoding/protocol is being used?
* Are commands repeated while a button is held?
* How are brightness commands represented?
* How are preset/mode commands represented?
* How reliably can the ESP32 reproduce the original timing?
* What IR LED current is required for reliable room-scale operation?
* Should the final IR driver use an NPN transistor or NMOS?
* How should the PCB be physically positioned relative to the light for reliable IR transmission?

## Validation

Validation will occur incrementally rather than waiting until the final PCB.

### Prototype validation

* Verify repeated remote commands produce repeatable timing data.
* Verify different buttons produce distinguishable commands.
* Verify ESP32-generated IR commands produce the same response as the original remote.
* Verify operation from typical dorm-room distances and angles.

### PCB validation

Test points will be included for:

* ESP32 power
* 3.3 V rail
* IR receiver output
* IR transmitter driver
* Sensor communication

An oscilloscope can then be used during lab testing to inspect the electrical waveforms and validate the final hardware.

## Future Ideas

Possible stretch goals:

* Scheduling
* Sunrise/sunset-based lighting
* Additional lighting devices
* Multiple-room/light control
* Physical rotary encoder
* Capacitive touch controls
* Enclosure
* Home Assistant integration
* Combining multiple IR-controlled devices into one controller

## Project Philosophy

This project intentionally starts as a small reverse-engineering experiment and grows into a consumer-electronics PCB project.

The objective is not just to make a smart light, but to practice the full hardware development cycle:

**Reverse engineering → firmware → signal analysis → circuit design → PCB design → bring-up → validation → consumer product**


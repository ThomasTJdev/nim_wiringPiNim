# wiringPiNim

Nim-lang wrapper for the C library wiringPi. This wrapper implements some of the wiringPi functions for quick access in Nim for controlling a Raspberry Pi.

# General

Only "Core funcions" is available. If other functions in the wiringPi C library is needed, please make a PR or a Issue with details.

# Prerequisites

Your need to have installed/build the wiringPi library on your system.

Either follow http://wiringpi.com/download-and-install/ or:
```
cd
git clone git://git.drogon.net/wiringPi
cd wiringPi
./build
```

To ensure that the wiringPi library is installed correctly, this command should give you some output:
```
gpio readall
```

# Include wiringPiNim in your code

## Imports

```nim
import wiringPiNim
```

## Add to your code

### Init

It is required that you initialize the board, before you use the GPIO's. This can be done with:

```nim
if piSetup() >= 0:
  echo "The RPi is ready"
```

### Have fun

Please look in the sourcecode `wiringPiNim.nim` or generate the docs `nim doc wiringPiNim.nim` for further information.

```nim
if piSetup() >= 0:
  piPinModeOutput(24)
  piDigitalWrite(24, 1)
  piDigitalRead(24)
```

# Available procs

```nim
proc piSetup*(): cint
  ## Setup/initialize the RPi.
  ##
  ## This maps the GPIO to the wiringPi pin numbering scheme

proc piSetupGPIO*(): cint
  ## Setup/initialize the RPi.
  ##
  ## This maps the GPIOs to Broadcom.
  ##
  ## Root is required.

proc piSetupPhys*(): cint
  ## Setup/initialize the RPi.
  ##
  ## This maps the GPIOs to Broadcom and use the physical pin numbers on 
  ## the P1 connector only.
  ##
  ## Root is required.

proc piSetupSys*(): cint
  ## Setup/initialize the RPi.
  ##
  ## This initialises wiringPi but uses the /sys/class/gpio interface 
  ## rather than accessing the hardware directly

proc piPinModeOutput*(pin: cint)
  ## Sets the pinmode to OUTPUT

proc piPinModeInput*(pin: cint)
  ## Sets the pinmode to INPUT

proc piPinModeGPIO*(pin: cint)
  ## Sets the pinmode to GPIO_CLOCK
  ##
  ## Note that only wiringPi pin 7 (BCM_GPIO 4) supports CLOCK output

proc piPinModePWM*(pin: cint)
  ## Sets the pinmode to PWM_OUTPUT
  ##
  ## Note that only wiringPi pin 1 (BCM_GPIO 18) supports PWM output

proc piDigitalPWM*(pin, value: cint)
  ## Writes the value to the PWM register for the given pin. The Raspberry
  ## Pi has one on-board PWM pin, pin 1 (BMC_GPIO 18, Phys 12) and the
  ## range is 0-1024. Other PWM devices may have other PWM ranges.

proc piDigitalWrite*(pin, value: cint)
  ## Writes the value HIGH or LOW (1 or 0) to the given pin which must have
  ## been previously set as an output.

proc piDigitalRead*(pin: cint): cint
  ## This function returns the value read at the given pin. It will be HIGH 
  ## or LOW (1 or 0) depending on the logic level at the pin.

proc piPullOff*(pin: cint): cint
  ## Sets the pull-up or pull-down resistor mode to no-pull up/down

proc piPullDown*(pin: cint): cint
  ## Sets the pull-up or pull-down resistor mode to pull to ground

proc piPullUp*(pin: cint): cint
  ## Sets the pull-up or pull-down resistor mode to pull to 3.3v

proc analogWrite*(pin, value: cint)
  ## This writes the given value to the supplied analog pin. You will need 
  ## to register additional analog modules to enable this function for 
  ## devices such as the Gertboard.

proc analogRead*(pin: cint): cint
  ## This returns the value read on the supplied analog input pin. You will 
  ## need to register additional analog modules to enable this function for
  ## devices such as the Gertboard, quick2Wire analog board, etc.

```

# String to cint

Please note that the args is in `cint`. To transform a string, the following method could be used:

```nim
let pinString = "2"
let pinCint = toU32(parseInt(pinString))
```

# Examples

## Activating a buzzer
```nim
import wiringPiNim, os

# Setting the pin for a buzzer
const buzzer = 6

if piSetup() >= 0:
  echo "RPi is setup and ready for use"

  # Setting the buzzers pin to output
  piPinModeOutput(buzzer)

  # Turning on the buzzer
  piDigitialWrite(buzzer, 1)
  echo piDigitalRead(buzzer)      
  echo "Buzzer is activated"

  sleep(2000)

  # Turning off the buzzer
  piDigitalWrite(buzzer, 0)
  echo piDigitalRead(buzzer)
  echo "Buzzer is deactivated"
```

## LED flashing (async)
```nim
import wiringPiNim, asyncdispatch

# Setting the pin for a LED
const led = 24

proc flashLed() {.async.} =
  if piSetup() >= 0:
    # Setting the LEDs pin to output
    piPinModeOutput(led)
    echo "RPi is setup and ready for use"

    while true:
      piDigitalWrite(led, 1)
      await sleepAsync(800)

      piDigitalWrite(led, 0)
      await sleepAsync(800)

waitFor flashLed()
```

## LED flashing (sync)
```nim
import wiringPiNim, os

# Setting the pin for a LED
const led = 24

proc flashLed() =
  if piSetup() >= 0:
    # Setting the LEDs pin to output
    piPinModeOutput(led)
    echo "RPi is setup and ready for use"

    while true:
      piDigitalWrite(led, 1)
      sleep(800)

      piDigitalWrite(led, 0)
      sleep(800)

flashLed()
```

## Monitoring with a PIR sensor
```nim
import wiringPiNim, os

const pir = 1

proc monitorPir() =
  if piSetup() >= 0:
    piPinModeInput(pir)

    while true:
      if piDigitalRead(pir) == 1:
        echo "Detected something!"
      sleep(200)

monitorPir()
```

## Monitoring with a magnetic door contact
```nim 
import wiringPiNim, asyncdispatch

const door = 29

proc monitorDoor() {.async.} =
  if piSetup() >= 0:
    piPinModeOutput(door)
    piPullUp(door)

    while true:
      if piDigitalRead(door) == 1:
        echo "Door is open!"
      await sleepAsync(200)

waitFor monitorDoor()
```
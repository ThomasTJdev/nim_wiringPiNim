#include <wiringPi.h>
#include <wiringPiSPI.h>

int piSetup() {
    return wiringPiSetup();
}

int piSetupGPIO() {
    return wiringPiSetupGpio();
}

int piSetupPhys() {
    return wiringPiSetupPhys();
}

int piSetupSys() {
    return wiringPiSetupSys();
}

void piPinModeOutput(int pin)
{
    pinMode (pin, OUTPUT);
}

void piPinModeInput(int pin)
{
    pinMode (pin, INPUT);
}

void piPinModePWM(int pin)
{
    pinMode (pin, PWM_OUTPUT);
}

void piPinModeGPIO(int pin)
{
    pinMode (pin, GPIO_CLOCK);
}

void piPwmWrite(int pin, int value)
{
    pwmWrite(pin, value);
}

void piDigitalWrite(int pin, int value)
{
    digitalWrite(pin, value);
}

int piDigitalRead(int pin)
{
    return digitalRead(pin);
}

void piPullOff(int pin)
{
    pullUpDnControl(pin, PUD_OFF);
}

void piPullDown(int pin)
{
    pullUpDnControl(pin, PUD_DOWN);
}

void piPullUp(int pin)
{
    pullUpDnControl(pin, PUD_UP);
}

void analogWrite(int pin, int value)
{
    analogWrite(pin, value);
}

int analogRead(int pin)
{
    return analogRead(pin);
}

int piSPISetup(int channel, int speed) {
    return wiringPiSPISetup(channel, speed);
}

int piSPIDataRW (int channel, unsigned char *data, int len) {
    return wiringPiSPIDataRW (channel, data, len);
}
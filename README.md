# LED-Cycling
Arduino FastLED library w/ delay effects. Effects handled via switch buttons. 

## Environment Setup
- [ ] Arduino Uno
- [ ] Breadboard
- [ ] (3) 330 Ohm Resistors
- [ ] (2) Button Switches
- [ ] (9) Male to Male Jumper Wires
- [ ] Setup an .ino file via the Arduino IDE. 
- [ ] Install the FastLED library via Tools > Manage Libraries > [FastLED by Daniel Garcia](https://github.com/FastLED/FastLED) > Install

## Board Setup
I'm using an Arduino Uno & a WS2812 LED strip. Since I'm only using 5 LEDs of the strip, I was able to power it with the Uno's onboard 5V. So no external power sources are used for the LED strip in this project. 

## Input_Pullup vs. INPUT
```
pinMode(CYCLE_BUTTON, INPUT_PULLUP);
pinMode(STOP_BUTTON, INPUT_PULLUP);
```
Pulls the floating buttons up. Allowing us to detect high passes when open, and low when pressed.Further [documentation here](https://www.arduino.cc/en/Tutorial/DigitalPins)


## Brightness
```
FastLED.setBrightness(20);
```
If not using a light diffuser, and for less load on the voltage, running the LED strip is ideal for daylight applications.

## Blinking Effect without Delay
```
leds[0] = CRGB(255, 255, 0);
FastLED.setBrightness(beatsin8(50,0,20)); //beatsin8(bpm, min, max)
```
Working around delay() is a pain when implementing switches! Prior to the final build of the LED Cycling project, I had versions with delay() and milis(). Delay didn't allow the cycling effect button work immediately. I had to wait until the delay timer was up. Milis() was just messy haha. To work around this we can use the beatsin8 function. This allows us to create a sin wave on our current. We define the beats per minute, which affects how often the lights blink. Sin also has a cute fade effect (because it's a sin wave and decreases on a curve). So it gives our blinking a nice lighthouse look -- instead of a epilepsy curse. By defining the .setBrightness, the min and max values in the beats() will affect the brightness of the led. Love it! 

## loops() instead of cases
Loops use less memory than switch cases. Here's a [dicussion forum on it](https://forum.arduino.cc/index.php/topic,44519.0.html)

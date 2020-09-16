#include <FastLED.h>

#define LED_PIN 6
#define NUM_LEDS 5
#define CYCLE_BUTTON 4
#define STOP_BUTTON 3

CRGB leds[NUM_LEDS];


int currentMode = 0;   // counts button presses
int maxModes = 5;      //how many loops for modes
int buttonState = 0;         // current button state
int lastButtonState = 0;     // last state of butt

int stopState = 0;
int prevStop = 0;

void setup() {
  pinMode(CYCLE_BUTTON, INPUT_PULLUP);
  pinMode(STOP_BUTTON, INPUT_PULLUP);
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(20);
  Serial.begin(9600); //debugging
  Serial.println("Serial has begun"); //debugging
}

void loop() {
  stopState = digitalRead(STOP_BUTTON);
  buttonState = digitalRead(CYCLE_BUTTON);

  if (stopState != prevStop) {
    if (stopState == HIGH) {
      Serial.println("chicken");
    }
    else {Serial.println("other");}
  }

  if (buttonState != lastButtonState) {
    if (buttonState == HIGH) {
      currentMode++;
      //Serial.println("on");
      Serial.print("number of button pushes: ");
      Serial.println(currentMode);
    } else {
      // if digitalRead = LOW, do this
      //Serial.println("off");
    }
    delay(10); //avoids debounding
  }
  
  if (currentMode == 1) {
    lightOne();
  }
  
  if (currentMode == 2) {
    lightTwo();
  }
  
  if (currentMode == 3) {
    lightThree();
  }

  if (currentMode == 4) {
    allTogether();
  }

  if (currentMode == 5) {
    randomColors();
  }

  if(currentMode == 6) {
    pingPong();
  }
  
  if (currentMode == 7) {
    turnOff();
  }
  if (currentMode == 8) {
    currentMode = 0;
  }
  // replaces current state as last one
  lastButtonState = buttonState;
  prevStop = stopState;
  FastLED.show();
}

void lightOne() {
  leds[0] = CRGB(255, 255, 0);
}

void lightTwo() {
  FastLED.clear();
  leds[1] = CRGB(0, 255, 0);
}

void lightThree() {
  FastLED.clear();
  leds[2] = CRGB(0, 0, 255);
}

void allTogether() {
  FastLED.clear();
  leds[0] = CRGB(255, 255, 0);
  leds[1] = CRGB(0, 255, 0);
  leds[2] = CRGB(0, 0, 255);
}

void randomColors() {
  fadeToBlackBy( leds, NUM_LEDS, 10);
  int pos = random16(NUM_LEDS);
  leds[pos] += CHSV( random8(64), 200, 255);
}

void pingPong() {
    fadeToBlackBy( leds, NUM_LEDS, 20);
  int pos = beatsin16( 13, 0, NUM_LEDS-1 );
  leds[pos] += CRGB( 243, 129, 255);
}

void turnOff() {
  FastLED.clear();
}

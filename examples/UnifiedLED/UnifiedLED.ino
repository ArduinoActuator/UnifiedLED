


#define GROVE_NEO_PIXEL
#define GROVE_MONO_LED
#define USE_SIMPLE_COLOR_LED
#define GROVE_LED_CIRCULAR
#define GROVE_LED_BAR
#define GROVE_CHAINABLE_LED

#include "UnifiedLED.h"



//BE SURE USE CORRESPONDING DEVICE
//Grove_LED_Bar bar(6, 7, 0, LED_CIRCULAR_24);
//FOR LED_BAR_10
//Grove_LED_Bar bar(7, 6, 1, LED_BAR_10); // Clock pin, Data pin, Orientation
//Grove_LED_Bar bar(6, 7, 0, LED_BAR_10); // Clock pin, Data pin, Orientation


#ifdef GROVE_LED_BAR
Grove_LED_Bar bar(3, 2, 0, LED_BAR_10);
UnifiedLED ledBar(&(bar),LED_BAR, 10, LED_FORWARD);
#endif /* GROVE_LED_BAR */

#ifdef GROVE_LED_CIRCULAR
Grove_LED_Bar circle(4, 5, 0, LED_CIRCULAR_24);
UnifiedLED ledCircle(&(circle),LED_CIRCULAR, 24, LED_FORWARD);
#endif /* GROVE_LED_CIRCULAR */


#ifdef GROVE_CHAINABLE_LED
#define NUM_CHAIN_LEDS  3
ChainableLED chain(8, 9, NUM_CHAIN_LEDS);
UnifiedLED ledChain(&(chain), P98X3_LED, NUM_CHAIN_LEDS);
#endif /* GROVE_CHAINABLE_LED */

#ifdef GROVE_NEO_PIXEL
#define NUM_NEO_PIXEL 10
#define NEO_PIXEL_PIN 10
Adafruit_NeoPixel strip(NUM_NEO_PIXEL, NEO_PIXEL_PIN, NEO_GRB + NEO_KHZ800);
UnifiedLED neoPixel(&(strip), NEO_PIXEL_LED, NUM_NEO_PIXEL);
#endif /* GROVE_NEO_PIXEL */

#ifdef USE_SIMPLE_COLOR_LED
#define SIMPLE_COLOR_LED_RED_PIN 11
#define SIMPLE_COLOR_LED_GREEN_PIN 12
#define SIMPLE_COLOR_LED_BLUE_PIN 13
UnifiedLED cathodeCommon(SIMPLE_COLOR_LED_RED_PIN, SIMPLE_COLOR_LED_GREEN_PIN, SIMPLE_COLOR_LED_BLUE_PIN, PULL_UP);
#endif /* USE_SIMPLE_COLOR_LED */

#ifdef GROVE_MONO_LED
#define GROVE_MONO_LED_PIN 6
UnifiedLED mono_led(GROVE_MONO_LED_PIN, PULL_DOWN);
//UnifiedLED mono_led(GROVE_MONO_LED_PIN, PULL_UP);
#endif /* GROVE_MONO_LED */


void setup() {
  Serial.begin(9600);
  delay(3000);
  Serial.println("setup start");
#ifdef LED_HAL_USE_MY9221

#ifdef GROVE_LED_BAR
  ledBar.begin();
  Serial.println("led bar begin");
  //led.setMode(LED_REVERSE);
  ledBar.setMode(LED_FORWARD);
  //led.setLedNum(7);
  Serial.println("led bar set mode");
#endif /* GROVE_LED_BAR */
#ifdef GROVE_LED_CIRCULAR
  ledCircle.begin();
  Serial.println("led circle begin");
  //ledCircle.setMode(LED_REVERSE);
  ledCircle.setMode(LED_FORWARD);
  //ledCircle.setLedNum(7);
  Serial.println("led circle set mode");
#endif /* GROVE_LED_CIRCULAR */
#endif /* LED_HAL_USE_MY9221 */
#ifdef LED_HAL_USE_P98X3
  ledChain.begin();
  Serial.println("full color led chain begin");
  for (int i=0; i< NUM_CHAIN_LEDS; i++) {
    ledChain.setLed(i,0,0,0);
  }
  Serial.println("full color led setup done");
#endif /* LED_HAL_USE_P98X3 */
#ifdef GROVE_NEO_PIXEL
  neoPixel.begin();
  Serial.println("neoPixel begin");
  for (int i=0; i< NUM_NEO_PIXEL; i++) {
    neoPixel.setLed(i,0,0,0);
  }
  Serial.println("neoPixel setup done");
#endif /* GROVE_NEO_PIXEL */
#ifdef USE_SIMPLE_COLOR_LED
  Serial.println("cathod/anode common led setup start");
  cathodeCommon.begin();
  Serial.println("cathod/anode common led setup end");
#endif /* USE_SIMPLE_COLOR_LED */
#ifdef GROVE_MONO_LED
  Serial.println("mono led setup start");
  mono_led.begin();
  Serial.println("mono led setup end");
#endif /* GROVE_MONO_LED */
  Serial.println("All setup done.");
}

void loop() {
  Serial.println("loop start");
#ifdef LED_HAL_USE_MY9221
#ifdef GROVE_LED_BAR
  Serial.println("LED bar setlevel");
  for (int i = 0; i < 10; i++) {
    ledBar.setLevel(i);
    delay(100);
  }
  delay(1000);
  Serial.println("LED bar change bright level");
  for (int i = 0; i < 10; i++) {
    ledBar.setLed(i,0.8);
    delay(1000);
    ledBar.setLed(i,0.6);
    delay(1000);
    ledBar.setLed(i,0.4);
    delay(1000);
    ledBar.setLed(i,0.2);
    delay(1000);
  }
#endif /* GROVE_LED_BAR */

#ifdef GROVE_LED_CIRCULAR
  Serial.println("LED circle setlevel");
  for (int i = 0; i < 24; i++) {
    ledCircle.setLevel(i);
    delay(100);
  }
  delay(1000);

  Serial.println("LED circle change bright level");
  for (int i = 0; i < 24; i++) {
    ledCircle.setLed(i,0.8);
    delay(1000);
    ledCircle.setLed(i,0.6);
    delay(1000);
    ledCircle.setLed(i,0.4);
    delay(1000);
    ledCircle.setLed(i,0.2);
    delay(1000);
  }
#endif /* GROVE_LED_CIRCULAR */
#endif /* LED_HAL_USE_MY9221 */

#ifdef LED_HAL_USE_P98X3
  Serial.println("Full color led chain set color");
  for (int i=0 ; i<NUM_CHAIN_LEDS ; i++ ) {
    ledChain.setLed(i,80,0,0);
    delay(300);
    ledChain.setLed(i,160,0,0);
    delay(300);
    ledChain.setLed(i,255,0,0);
    delay(300);
    ledChain.setLed(i,0,80,0);
    delay(300);
    ledChain.setLed(i,0,160,0);
    delay(300);
    ledChain.setLed(i,0,255,0);
    delay(300);
    ledChain.setLed(i,0,0,80);
    delay(300);
    ledChain.setLed(i,0,0,160);
    delay(300);
    ledChain.setLed(i,0,0,255);
    delay(300);
    ledChain.setLed(i,0,0,0);
  }
#endif /* LED_HAL_USE_P98X3 */

#ifdef GROVE_NEO_PIXEL
  Serial.println("neoPixel set color");
  for (int i=0 ; i<NUM_NEO_PIXEL ; i++ ) {
    neoPixel.setLed(i,80,0,0);
    delay(300);
    neoPixel.setLed(i,160,0,0);
    delay(300);
    neoPixel.setLed(i,255,0,0);
    delay(300);
    neoPixel.setLed(i,0,80,0);
    delay(300);
    neoPixel.setLed(i,0,160,0);
    delay(300);
    neoPixel.setLed(i,0,255,0);
    delay(300);
    neoPixel.setLed(i,0,0,80);
    delay(300);
    neoPixel.setLed(i,0,0,160);
    delay(300);
    neoPixel.setLed(i,0,0,255);
    delay(300);
    neoPixel.setLed(i,0,0,0);
  }
#endif /* GROVE_NEO_PIXEL */

#ifdef USE_SIMPLE_COLOR_LED
  Serial.println("cathod/anode common led set color");
  cathodeCommon.setLed(80,0,0);
  delay(300);
  cathodeCommon.setLed(160,0,0);
  delay(300);
  cathodeCommon.setLed(255,0,0);
  delay(300);
  cathodeCommon.setLed(0,80,0);
  delay(300);
  cathodeCommon.setLed(0,160,0);
  delay(300);
  cathodeCommon.setLed(0,255,0);
  delay(300);
  cathodeCommon.setLed(0,0,80);
  delay(300);
  cathodeCommon.setLed(0,0,160);
  delay(300);
  cathodeCommon.setLed(0,0,255);
  delay(300);
  cathodeCommon.setLed(0,0,0);
#endif /* USE_SIMPLE_COLOR_LED */

#ifdef GROVE_MONO_LED
  Serial.println("mono led test start");
  for (int i=0; i < 11 ; i++) {
    float val = 0.1*i;
    Serial.println(val);
    //mono_led.setLed(0,val);
    mono_led.setLed(val);
    delay(300);
  }
  Serial.println("mono led test done");
#endif /* GROVE_MONO_LED */
}


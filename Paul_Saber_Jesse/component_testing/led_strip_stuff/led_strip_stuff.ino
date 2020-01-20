//Notes:
//1.  The ground for the LED strip must be connected to the ground for the Arduino Nano/Uno.

#include "FastLED.h"

// How many leds in your strip?
#define NUM_LEDS 144

// For led chips like Neopixels, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806 define both DATA_PIN and CLOCK_PIN
#define DATA_PIN 4
#define CLOCK_PIN 13
#define BUCK_CONVERTER_PIN_LEDS 5
#define BUCK_CONVERTER_PIN_SOUND 6

// Define the array of leds
CRGB leds[NUM_LEDS];

void setup() { 

    pinMode(BUCK_CONVERTER_PIN_SOUND, OUTPUT);
  digitalWrite(BUCK_CONVERTER_PIN_SOUND, 1);
  pinMode(BUCK_CONVERTER_PIN_LEDS, OUTPUT);
  digitalWrite(BUCK_CONVERTER_PIN_LEDS, 1);

  
      // Uncomment/edit one of the following lines for your leds arrangement.
      // FastLED.addLeds<TM1803, DATA_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<TM1804, DATA_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<TM1809, DATA_PIN, RGB>(leds, NUM_LEDS);
       //FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<WS2812, DATA_PIN, RGB>(leds, NUM_LEDS);
      
      FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS); // for GRB LEDs
      //FastLED.addLeds<WS2812B, DATA_PIN, RGB>(leds, NUM_LEDS); // for RGB LEDs  
      
      //FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
      // FastLED.addLeds<APA104, DATA_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<UCS1903, DATA_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<UCS1903B, DATA_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<GW6205, DATA_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<GW6205_400, DATA_PIN, RGB>(leds, NUM_LEDS);
      
      // FastLED.addLeds<WS2801, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<SM16716, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<LPD8806, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<P9813, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<APA102, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<DOTSTAR, RGB>(leds, NUM_LEDS);

      // FastLED.addLeds<WS2801, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<SM16716, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<LPD8806, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<P9813, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<APA102, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<DOTSTAR, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
        FastLED.setBrightness(40);

}

void loop() { 
  // Turn the LED on, then pause
  leds[0] = CRGB::Red;
  leds[1] = CRGB::Green;
  leds[2] = CRGB::Blue;
  leds[3] = CRGB::Aquamarine;
  leds[4] = CRGB::DarkMagenta;
  leds[5] = CRGB::DeepPink;
  leds[6] = CRGB::OrangeRed;
  leds[7] = CRGB::Brown;
  leds[8] = CRGB::DarkOrchid;
  leds[9] = CRGB::LightCoral;
  leds[10] = CRGB::Plum;
  leds[11] = CRGB::Yellow;
  leds[12] = CRGB::Purple;
  leds[13] = CRGB::FairyLight;
  //For more colors, see http://fastled.io/docs/3.1/struct_c_r_g_b.html
  
  FastLED.show();
  
  delay(500);

  fill_solid(leds, NUM_LEDS, CRGB::Red);
  FastLED.show();

  delay(500);
  
  // Now turn the LED off, then pause
  leds[0] = CRGB::Black;
  FastLED.show();
  
  delay(100);

  fill_solid(leds, NUM_LEDS, CRGB::Black);
  FastLED.show();

  delay(100);
}

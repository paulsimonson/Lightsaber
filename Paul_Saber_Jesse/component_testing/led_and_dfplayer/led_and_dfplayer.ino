//Notes:
//1.  The ground for the LED strip must be connected to the ground for the Arduino Nano/Uno.

#include "FastLED.h"
#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

// How many leds in your strip?
#define NUM_LEDS 144

// For led chips like Neopixels, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806 define both DATA_PIN and CLOCK_PIN
#define DATA_PIN 4
#define CLOCK_PIN 13
#define BUCK_CONVERTER_PIN_LEDS 5
#define BUCK_CONVERTER_PIN_SOUND 6
#define RX_PIN 11
#define TX_PIN 10

//#define LED_PIN 4
#define BTN_PIN 9
#define VOLT_PIN A6
#define BTN_LED 2

// ---------------------------- SETTINGS -------------------------------
#define BTN_TIMEOUT 800     // button hold delay, ms
#define BRIGHTNESS 40 //106      // max LED brightness (0 - 255).  
//106 is basically the max brightness for 2 strings of 60 lights (0.06 A per LED = 7.4 amps at full white light, but buck converter only allows 3 amps).
#define SPEAKER_VOLUME 30    //Depending on power source/amps, too high a volume causes the system to have errors.
#define THRESHOLD_MODIFIER 0.9

#define SWING_TIMEOUT 500   // timeout between swings
#define SWING_L_THR 175 * THRESHOLD_MODIFIER     // swing angle speed threshold
#define SWING_THR 225 * THRESHOLD_MODIFIER      // fast swing angle speed threshold
#define STRIKE_THR 75 * THRESHOLD_MODIFIER     // hit acceleration threshold
#define STRIKE_S_THR 150 * THRESHOLD_MODIFIER   // hard hit acceleration threshold
#define FLASH_DELAY 90      // flash time while hit

#define PULSE_ALLOW 1       // blade pulsation (1 - allow, 0 - disallow)
#define PULSE_AMPL 35       // pulse amplitude
#define PULSE_DELAY 30      // delay between pulses

#define R1 100000.0           // voltage divider real resistance
#define R2 51000.0            // voltage divider real resistance
#define VOLTAGE_CALIBRATION 1.0
float voltage_sensor_factor = VOLTAGE_CALIBRATION * 5.0 / 1023.0 * (R1 + R2) / R2;
#define BATTERY_SAFE 0      // battery monitoring (1 - allow, 0 - disallow)

#define DEBUG 1             // debug information in Serial (1 - allow, 0 - disallow)
// ---------------------------- END SETTINGS -------------------------------


// Define the array of leds
CRGB leds[NUM_LEDS];

SoftwareSerial mySoftwareSerial(RX_PIN, TX_PIN); // RX, TX
//SoftwareSerial mySoftwareSerial(10, 9); // RX, TX
DFRobotDFPlayerMini myDFPlayer;
void printDetail(uint8_t type, int value);

void setup() { 
    mySoftwareSerial.begin(9600);
    Serial.begin(9600);

    pinMode(BUCK_CONVERTER_PIN_SOUND, OUTPUT);
    digitalWrite(BUCK_CONVERTER_PIN_SOUND, 1);
    pinMode(BUCK_CONVERTER_PIN_LEDS, OUTPUT);
    digitalWrite(BUCK_CONVERTER_PIN_LEDS, 1);

      //Turn on button LED.
  pinMode(BTN_PIN, INPUT_PULLUP);
  pinMode(BTN_LED, OUTPUT);
  digitalWrite(BTN_LED, 1);

      // Uncomment/edit one of the following lines for your leds arrangement.
    
      FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS); // for GRB LEDs
      //FastLED.addLeds<WS2812B, DATA_PIN, RGB>(leds, NUM_LEDS); // for RGB LEDs  
      
  FastLED.setBrightness(BRIGHTNESS);

     Serial.println();
  Serial.println(F("DFRobot DFPlayer Mini Demo"));
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));

  if (!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while(true);
  }
  Serial.println(F("DFPlayer Mini online."));

  myDFPlayer.volume(SPEAKER_VOLUME);  //Set volume value. From 0 to 30
  myDFPlayer.play(1);  //Play the first mp3
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
  
  delay(1000);

  fill_solid(leds, NUM_LEDS, CRGB::White);
  FastLED.show();
  delay(5);


//Play sounds
  static unsigned long timer = millis();

  if (millis() - timer > 1500) {
    timer = millis();
    myDFPlayer.next();  //Play next mp3/wav every 2.5 seconds.
  }

  if (myDFPlayer.available()) {
    printDetail(myDFPlayer.readType(), myDFPlayer.read()); //Print the detail message from DFPlayer to handle different errors and states.
  }
  
  delay(1000);
  
  // Now turn the LED off, then pause
  //leds[0] = CRGB::Black;
  //FastLED.show();
  //delay(250);

  fill_solid(leds, NUM_LEDS, CRGB::Black);
  FastLED.show();

  delay(250);
}

void printDetail(uint8_t type, int value){
  switch (type) {
    case TimeOut:
      Serial.println(F("Time Out!"));
      break;
    case WrongStack:
      Serial.println(F("Stack Wrong!"));
      break;
    case DFPlayerCardInserted:
      Serial.println(F("Card Inserted!"));
      break;
    case DFPlayerCardRemoved:
      Serial.println(F("Card Removed!"));
      break;
    case DFPlayerCardOnline:
      Serial.println(F("Card Online!"));
      break;
    case DFPlayerPlayFinished:
      Serial.print(F("Number:"));
      Serial.print(value);
      Serial.println(F(" Play Finished!"));
      break;
    case DFPlayerError:
      Serial.print(F("DFPlayerError:"));
      switch (value) {
        case Busy:
          Serial.println(F("Card not found"));
          break;
        case Sleeping:
          Serial.println(F("Sleeping"));
          break;
        case SerialWrongStack:
          Serial.println(F("Get Wrong Stack"));
          break;
        case CheckSumNotMatch:
          Serial.println(F("Check Sum Not Match"));
          break;
        case FileIndexOut:
          Serial.println(F("File Index Out of Bound"));
          break;
        case FileMismatch:
          Serial.println(F("Cannot Find File"));
          break;
        case Advertise:
          Serial.println(F("In Advertise"));
          break;
        default:
          break;
      }
      break;
    default:
      break;
  }
}

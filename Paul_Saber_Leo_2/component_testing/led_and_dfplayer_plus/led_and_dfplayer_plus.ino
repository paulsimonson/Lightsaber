//Notes:
//1.  The ground for the LED strip must be connected to the ground for the Arduino Nano/Uno.

#include "FastLED.h"
#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

#include "MPU6050_6Axis_MotionApps20.h"

// How many leds in your strip?
#define NUM_LEDS 60
#define LIGHT_UP_TIME 2 //ms per LED on strip


// For led chips like Neopixels, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806 define both DATA_PIN and CLOCK_PIN
#define DATA_PIN 4
#define CLOCK_PIN 13
#define BUCK_CONVERTER_PIN_LEDS 5
#define BUCK_CONVERTER_PIN_SOUND 6
#define RX_PIN 10
#define TX_PIN 11

//#define LED_PIN 4
#define BTN_PIN 9
#define VOLT_PIN A6
#define BTN_LED 3

// ---------------------------- SETTINGS -------------------------------
#define BTN_TIMEOUT 800     // button hold delay, ms
#define BRIGHTNESS 20 //106      // max LED brightness (0 - 255).  
//106 is basically the max brightness for 2 strings of 60 lights (0.06 A per LED = 7.4 amps at full white light, but buck converter only allows 3 amps).
#define SPEAKER_VOLUME 15    //Depending on power source/amps, too high a volume causes the system to have errors.
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
#define USING_3_18650_BATTERIES 0

#define DEBUG 0             // debug information in Serial (1 - allow, 0 - disallow)

//For sound on DFPlayer Mini:
#define RX_PIN 10
#define TX_PIN 11
//Specific sound effects files:
#define HUM_WAV 1
#define OFF_WAV 2
#define ON_WAV 3

// ---------------------------- END SETTINGS -------------------------------

// ------------------------------ VARIABLES/FUNCTIONS ---------------------------------

// Define the array of leds
CRGB leds[NUM_LEDS];

float k = 0.2;
unsigned long humTimer = -9000, mpuTimer, nowTimer;
int stopTimer;
boolean bzzz_flag, ls_chg_state, lightsaber_on;

MPU6050 accelgyro;
int16_t ax, ay, az;
int16_t gx, gy, gz;
unsigned long ACC, GYR, COMPL;
int gyroX, gyroY, gyroZ, accelX, accelY, accelZ, freq, freq_f = 20;

boolean btnState, btn_flag, hold_flag;
byte btn_counter;
unsigned long btn_timer, PULSE_timer, swing_timer, swing_timeout, battery_timer, bzzTimer;
byte nowNumber;
byte LEDcolor;  // 0 - red, 1 - green, 2 - blue, 3 - pink, 4 - yellow, 5 - ice blue
byte nowColor, red, green, blue, redOffset, greenOffset, blueOffset;
boolean eeprom_flag, swing_flag, swing_allow, strike_flag, HUMmode;
int PULSEOffset;

SoftwareSerial mySoftwareSerial(RX_PIN, TX_PIN); // RX, TX
DFRobotDFPlayerMini myDFPlayer;
void printDetail(uint8_t type, int value);
// ------------------------------ END VARIABLES ---------------------------------

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
  
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS); // for GRB LEDs
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

  myDFPlayer.volume(10);  //Set volume value. From 0 to 30
  myDFPlayer.play(1);  //Play the first mp3

   randomSeed(analogRead(2));    // starting point for random generator

  //Accelerometer initialization
  accelgyro.initialize();
  accelgyro.setFullScaleAccelRange(MPU6050_ACCEL_FS_16);
  accelgyro.setFullScaleGyroRange(MPU6050_GYRO_FS_250);
  if (DEBUG) {
    Serial.println();
    Serial.println(F("Initializing..."));
    if (accelgyro.testConnection()) 
      Serial.println(F("MPU6050 OK"));
    else 
      Serial.println(F("MPU6050 fail"));
  }
}



void loop() { 
  // Turn the LED on, then pause

  {//LEDs
    FastLED.setBrightness(10);
    fill_solid(leds, NUM_LEDS, CRGB::White);
    FastLED.show();
    delay(100);
    setPixel(0, 255, 0, 0);
    setPixel(1, 0, 255, 0);
    setPixel(2, 0, 0, 255);
    FastLED.show();
    delay(500);
    setAll(0, 0, 0);
    FastLED.show();
      delay(1000);

  }
  
  myDFPlayer.next();  //Play next mp3/wav every 2.5 seconds.
  
  Serial.println(F("Light up!"));
  for (int i = 0; i < NUM_LEDS; i++) {
    Serial.println(i);
    Serial.println(NUM_LEDS);

    setPixel(i, 255, 0, 0);
    delay(2);
    FastLED.show();

  }
  Serial.println(F("Done lighting up!"));


    //myDFPlayer.play(ON_WAV);
  delay(100);
  //light_up();
  delay(100);
        
  
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

void setPixel(int Pixel, byte red, byte green, byte blue) {
  if(Pixel < 0)
    Pixel = 0;
  if(Pixel > NUM_LEDS)
    Pixel = NUM_LEDS-1;
    
  leds[Pixel].r = red;
  leds[Pixel].g = green;
  leds[Pixel].b = blue;
}

void setAll(byte red, byte green, byte blue) {
  for (int i = 0; i < NUM_LEDS; i++ ) {
    setPixel(i, red, green, blue);
  }
  FastLED.show();
}

void light_up() {
  Serial.println(F("Light up!"));
  for (char i = 0; i < NUM_LEDS; i++) {        
    setPixel(i, red, green, blue);
    FastLED.show();
    delay(LIGHT_UP_TIME);
  }
}

void light_down() {
  for (char i = NUM_LEDS - 1; i >= 0; i--) {      
    setPixel(i, 0, 0, 0);
    FastLED.show();
    delay(LIGHT_UP_TIME);
  }
}

void hit_flash() {
  setAll(225, 225, 225);            
  delay(FLASH_DELAY);                
  setAll(red, blue, green);        
}

void setColor(byte color) {
  switch (color) {
    // 0 - red, 1 - green, 2 - blue, 3 - pink, 4 - yellow, 5 - ice blue
    case 0:
      red = 255;
      green = 0;
      blue = 0;
      break;
    case 1:
      red = 0;
      green = 0;
      blue = 255;
      break;
    case 2:
      red = 0;
      green = 255;
      blue = 0;
      break;
    case 3:
      red = 255;
      green = 0;
      blue = 255;
      break;
    case 4:
      red = 255;
      green = 255;
      blue = 0;
      break;
    case 5:
      red = 0;
      green = 255;
      blue = 255;
      break;
  }
}

void batteryTick() {
  if (millis() - battery_timer > 30000 && lightsaber_on && BATTERY_SAFE) {
    if (voltage_measure() < 15) {
      ls_chg_state = 1;
    }
    battery_timer = millis();
  }
}

long voltage_measure() {
  float voltage = 0;
  for (int i = 0; i < 10; i++) {    
    voltage += (float)analogRead(VOLT_PIN) * voltage_sensor_factor;
  }
  voltage = voltage * 0.1;

  if (DEBUG) {
    Serial.print(F("Voltage: "));
    Serial.println(voltage);
  }

  //For three 18650 batteries in series:
  if(USING_3_18650_BATTERIES)
  {
  int volts = voltage * 100.0/3.0;    // 3 cells!!!
  if (volts > 387)
    return map(volts, 420, 387, 100, 77);
  else if ((volts <= 387) && (volts > 375) )
    return map(volts, 387, 375, 77, 54);
  else if ((volts <= 375) && (volts > 368) )
    return map(volts, 375, 368, 54, 31);
  else if ((volts <= 368) && (volts > 340) )
    return map(volts, 368, 340, 31, 8);
  else if (volts <= 340)
    return map(volts, 340, 260, 8, 0);
  }
  else //assume 4 AA/AAA rechargeables
  {
      int volts = voltage * 100.0/4.0;    // 4 cells!!!
      return map(volts, 100, 150, 0, 100);
  }
}

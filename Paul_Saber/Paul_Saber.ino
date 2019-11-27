///Majory modifications I made to the original GyverSaber code to produce this program file:
///- Using actual ground instead of ports set to low state.
///- Use of DFPlayer Mini to play sounds.
///- Initializing resistor constants as floats, not ints.
///- General code clean-up, simplification, and clarification...
///- Small bug corrections.
///- Elimination of tone based sounds.

/*
     SUPER-DUPER COOL ARDUINO BASED MULTICOLOR SOUND PLAYING LIGHTSABER!
   HARDWARE:
     Addressable LED strip (WS2811) to get any blade color and smooth turn on effect
     MicroSD card module to play some sounds
     IMU MPU6050 (accel + gyro) to generate hum. Frequency depends on angle velocity of blade
     OR measure angle speed and play some hum sounds from SD
   CAPABILITIES:
     Smooth turning on/off with lightsaber-like sound effect
     Randomly pulsing color (you can turn it off)
     Sounds:
       MODE 1: generated hum. Frequency depends on angle velocity of blade
       MODE 2: hum sound from SD card
         Slow swing - long hum sound (randomly from 4 sounds)
         Fast swing - short hum sound (randomly from 5 sounds)
     Bright white flash when hitting
     Play one of 16 hit sounds, when hit
       Weak hit - short sound
       Hard hit - long "bzzzghghhdh" sound
     After power on blade shows current battery level from 0 to 100 percent
     Battery safe mode:
       Battery is drain BEFORE TURNING ON: GyverSaber will not turn on, button LED will PULSE a couple of times
       Battery is drain AFTER TURNING ON: GyverSaber will be turned off automatically
   CONTROL BUTTON:
     HOLD - turn on / turn off GyverSaber
     TRIPLE CLICK - change color (red - green - blue - yellow - pink - ice blue)
     //QUINARY CLICK - change sound mode (hum generation - hum playing)
     Selected color and sound mode stored in EEPROM (non-volatile memory)
     
   Project GitHub repository: https://github.com/AlexGyver/EnglishProjects/tree/master/GyverSaber
   YouTube channel: https://www.youtube.com/channel/UCNEOyqhGzutj-YS-d5ckYdg?sub_confirmation=1
   Author: MadGyver, forked and modified by Paul Simonson
*/

// ---------------------------- SETTINGS -------------------------------
#define NUM_LEDS 54         // number of microcircuits WS2811 on LED strip (note: one WS2811 controls 3 LEDs!)
#define BTN_TIMEOUT 800     // button hold delay, ms
#define BRIGHTNESS 150      // max LED brightness (0 - 255)
#define SPEAKER_VOLUME 20    //Depending on power source/amps, too high a volume causes the system to have errors.
#define THRESHOLD_MODIFIER 0.9

#define SWING_TIMEOUT 500   // timeout between swings
#define SWING_L_THR 100 * THRESHOLD_MODIFIER     // swing angle speed threshold
#define SWING_THR 200 * THRESHOLD_MODIFIER      // fast swing angle speed threshold
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
#define BATTERY_SAFE 1      // battery monitoring (1 - allow, 0 - disallow)

#define DEBUG 0             // debug information in Serial (1 - allow, 0 - disallow)
// ---------------------------- SETTINGS -------------------------------

#define LED_PIN 6
#define BTN_PIN 3
//#define IMU_GND A1
//#define SD_GND A0
#define VOLT_PIN A6
#define BTN_LED 4
//For sound on DFPlayer Mini:
#define RX_PIN 10
#define TX_PIN 11

#define HUM_WAV 1
#define OFF_WAV 2
#define ON_WAV 3


// -------------------------- LIBS ---------------------------
#include <avr/pgmspace.h>   // PROGMEM library
//#include <SD.h>
//#include <TMRpcm.h>         // audio from SD library
//#include "Wire.h"

// I2Cdev and MPU6050 must be installed as libraries, or else the .cpp/.h files
// for both classes must be in the include path of your project
#include "I2Cdev.h"

#include "MPU6050_6Axis_MotionApps20.h"
//#include "MPU6050.h" // not necessary if using MotionApps include file

// Arduino Wire library is required if I2Cdev I2CDEV_ARDUINO_WIRE implementation
// is used in I2Cdev.h
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
    #include "Wire.h"
#endif

//#include "I2Cdev.h"
//#include "MPU6050.h"
//#include <toneAC.h>         // hum generation library
#include "FastLED.h"        // addressable LED library
#include <EEPROM.h>
//For playing sounds from DFPlayer Mini
#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

CRGB leds[NUM_LEDS];
//#define SD_ChipSelectPin 10
//TMRpcm tmrpcm;
MPU6050 accelgyro;
// -------------------------- END LIBS ---------------------------


// ------------------------------ VARIABLES ---------------------------------
int16_t ax, ay, az;
int16_t gx, gy, gz;
unsigned long ACC, GYR, COMPL;
int gyroX, gyroY, gyroZ, accelX, accelY, accelZ, freq, freq_f = 20;
float k = 0.2;
unsigned long humTimer = -9000, mpuTimer, nowTimer;
int stopTimer;
boolean bzzz_flag, ls_chg_state, ls_state;
boolean btnState, btn_flag, hold_flag;
byte btn_counter;
unsigned long btn_timer, PULSE_timer, swing_timer, swing_timeout, battery_timer, bzzTimer;
byte nowNumber;
byte LEDcolor;  // 0 - red, 1 - green, 2 - blue, 3 - pink, 4 - yellow, 5 - ice blue
byte nowColor, red, green, blue, redOffset, greenOffset, blueOffset;
boolean eeprom_flag, swing_flag, swing_allow, strike_flag, HUMmode;
float voltage;
int PULSEOffset;
//For playing sounds from DFPlayer Mini:
SoftwareSerial mySoftwareSerial(RX_PIN, TX_PIN); // RX, TX
//SoftwareSerial mySoftwareSerial(10, 9); // RX, TX
DFRobotDFPlayerMini myDFPlayer;
void printDetail(uint8_t type, int value);

// ------------------------------ END VARIABLES ---------------------------------

// --------------------------------- SOUNDS ----------------------------------

//Corresponding sound file numbers:
//Strike sounds
int strikes[8] = {3, 4, 5, 6, 7, 8, 9, 10};
//Corresponding sound durations:
int strike_time[8] = {779, 563, 687, 702, 673, 661, 666, 635};

//Short strike sounds
int strikes_short[8] = {11, 12, 13, 14, 15, 16, 17, 18};
int strike_s_time[8] = {270, 167, 186, 250, 252, 255, 250, 238};

//Swing sounds
int swings[5] = {23, 24, 25, 26, 27};
int swing_time[5] = {389, 372, 360, 366, 337};

//Long swing sounds
int swings_L[4] = {19, 20, 21, 22};
int swing_time_L[4] = {636, 441, 772, 702};

// --------------------------------- END SOUNDS ---------------------------------

void setup() {
  FastLED.addLeds<WS2811, LED_PIN, GRB>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(100);  // ~40% of LED strip brightness
  setAll(0, 0, 0);             // and turn it off

  //Wire.begin();
  Serial.begin(115200);

  pinMode(BTN_PIN, INPUT_PULLUP);
  //pinMode(IMU_GND, OUTPUT);
  //pinMode(SD_GND, OUTPUT);
  pinMode(BTN_LED, OUTPUT);
  //digitalWrite(IMU_GND, 0);
  //digitalWrite(SD_GND, 0);
  digitalWrite(BTN_LED, 1);

  randomSeed(analogRead(2));    // starting point for random generator

  // IMU initialization
  accelgyro.initialize();
  accelgyro.setFullScaleAccelRange(MPU6050_ACCEL_FS_16);
  accelgyro.setFullScaleGyroRange(MPU6050_GYRO_FS_250);
  if (DEBUG) {
    Serial.println();
    Serial.println(F("Initializing..."));
    if (accelgyro.testConnection()) Serial.println(F("MPU6050 OK"));
    else Serial.println(F("MPU6050 fail"));
  }

  // DFPlayer Mini:
  mySoftwareSerial.begin(9600);

  Serial.println();
  Serial.println(F("Initializing DFPlayer Mini for sound output from SD card... (May take 3~5 seconds)"));

  if (!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please check for inserted SD card!"));
    while(true);
  }
  Serial.println(F("DFPlayer Mini online."));

  myDFPlayer.volume(SPEAKER_VOLUME);  //Set volume value. From 0 to 30

  if (DEBUG) {
    Serial.println(F("DFPlayer Mini test."));
    myDFPlayer.volume(SPEAKER_VOLUME);  //Set volume value. From 0 to 30
    Serial.println(F("state, volume, EQ, File counts, current file number, file counts in folder")); //read mp3 state
    Serial.println(myDFPlayer.readState()); //read mp3 state
    Serial.println(myDFPlayer.readVolume()); //read current volume
    Serial.println(myDFPlayer.readEQ()); //read EQ setting
    Serial.println(myDFPlayer.readFileCounts()); //read all file counts in SD card
    Serial.println(myDFPlayer.readCurrentFileNumber()); //read current play file number
    Serial.println(myDFPlayer.readFileCountsInFolder(3)); //read fill counts in folder SD:/03
    myDFPlayer.play(1);  //Play the first mp3
    long delay_timer = millis();
    while(millis() - delay_timer < 2000)
      ;
    myDFPlayer.play(3);  //Play the third mp3
    delay_timer = millis();
    while(millis() - delay_timer < 1000)
      ;
    Serial.println(F("Done playing DFPlayer Mini test."));
    myDFPlayer.volume(SPEAKER_VOLUME);  //Set volume value. From 0 to 30

    //myDFPlayer.pause(); // pause the sound
    delay(10); // debounce
  }
  // end of DFPlayer Mini setup.

  if (DEBUG) {
    EEPROM.write(0, 0);          // set default
    EEPROM.write(1, 0);          // set default
    nowColor = 0;                // set default
  }


  if ((EEPROM.read(0) >= 0) && (EEPROM.read(0) <= 5)) {  // check first start
    nowColor = EEPROM.read(0);   // remember color
    HUMmode = 1;//EEPROM.read(1);    // remember mode
  } else {                       // first start
    EEPROM.write(0, 0);          // set default
    EEPROM.write(1, 0);          // set default
    nowColor = 0;                // set default
  }

  setColor(nowColor);
  byte capacity = voltage_measure();       // get battery level
  capacity = map(capacity, 100, 0, (NUM_LEDS / 2 - 1), 1);  // convert into blade length
  if (DEBUG) {
    Serial.print(F("Battery: "));
    Serial.println(capacity);
  }

  for (char i = 0; i <= capacity; i++) {   // show battery level
    setPixel(i, red, green, blue);
    setPixel((NUM_LEDS - 1 - i), red, green, blue);
    FastLED.show();
    delay(25);
  }
  delay(1000);                         // 1 second to show battery level
  setAll(0, 0, 0);
  FastLED.setBrightness(BRIGHTNESS);   // set bright

  if (DEBUG) {
    Serial.print(F("Done initializing."));
  }
}

// --- MAIN LOOP---
void loop() {
  randomPULSE();
  getFreq();
  on_off_sound();
  btnTick();
  strikeTick();
  swingTick();
  batteryTick();
}
// --- MAIN LOOP---

void btnTick() {
  btnState = !digitalRead(BTN_PIN);
  if (btnState && !btn_flag) {
    if (DEBUG) Serial.println(F("BTN PRESS"));
    btn_flag = 1;
    btn_counter++;
    btn_timer = millis();
  }
  if (!btnState && btn_flag) {
    btn_flag = 0;
    hold_flag = 0;
  }
  if (btn_flag && btnState && (millis() - btn_timer > BTN_TIMEOUT) && !hold_flag) {
    ls_chg_state = 1;                     // flag to change saber state (on/off)
    hold_flag = 1;
    btn_counter = 0;
  }
  if ((millis() - btn_timer > BTN_TIMEOUT) && (btn_counter != 0)) {
    if (ls_state) {
      if (btn_counter > 2) {               // 3 press count
        nowColor++;                         // change color
        if (nowColor >= 6) nowColor = 0;
        setColor(nowColor);
        setAll(red, green, blue);
        eeprom_flag = 1;
      }
      /*
      if (btn_counter == 5) {               // 5 press count
        HUMmode = 1;//!HUMmode;
        myDFPlayer.loop(HUM_WAV);
        eeprom_flag = 1;
      }*/
    }
    btn_counter = 0;
  }
}

void on_off_sound() {
  if (ls_chg_state) {                // if change flag
    if (!ls_state) {                 // if lightsaber is turned off
      if (voltage_measure() > 10 || !BATTERY_SAFE) {
        if (DEBUG) Serial.println(F("SABER ON"));
        myDFPlayer.play(ON_WAV);
        delay(200);
        light_up();
        delay(100);
        bzzz_flag = 1;
        ls_state = true;               // remember that turned on
        myDFPlayer.loop(HUM_WAV);

      } else {
        if (DEBUG) Serial.println(F("LOW VOLTAGE!"));
        for (int i = 0; i < 5; i++) {
          digitalWrite(BTN_LED, 0);
          delay(400);
          digitalWrite(BTN_LED, 1);
          delay(400);
        }
      }
    } 
    else {                         // if GyverSaber is turned on
      bzzz_flag = 0;
      myDFPlayer.play(OFF_WAV);
      delay(300);
      light_down();
      delay(300);
      if (DEBUG) Serial.println(F("SABER OFF"));
      ls_state = false;
      if (eeprom_flag) {
        eeprom_flag = 0;
        EEPROM.write(0, nowColor);   // write color in EEPROM
        EEPROM.write(1, HUMmode);    // write mode in EEPROM
      }
    }
    ls_chg_state = 0;
  }

  if (((millis() - humTimer) > 9000) && bzzz_flag && HUMmode) {
    myDFPlayer.loop
    (HUM_WAV);
    humTimer = millis();
    swing_flag = 1;
    strike_flag = 0;
  }
  long delta = millis() - bzzTimer;
  if ((delta > 3) && bzzz_flag && !HUMmode) {
    if (strike_flag) {
      //tmrpcm.disable();
      //myDFPlayer.pause();
      strike_flag = 0;
    }
    
    bzzTimer = millis();
  }
}

void randomPULSE() {
  if (PULSE_ALLOW && ls_state && (millis() - PULSE_timer > PULSE_DELAY)) {
    PULSE_timer = millis();
    PULSEOffset = PULSEOffset * k + random(-PULSE_AMPL, PULSE_AMPL) * (1 - k);
    if (nowColor == 0) PULSEOffset = constrain(PULSEOffset, -15, 5);
    redOffset = constrain(red + PULSEOffset, 0, 255);
    greenOffset = constrain(green + PULSEOffset, 0, 255);
    blueOffset = constrain(blue + PULSEOffset, 0, 255);
    setAll(redOffset, greenOffset, blueOffset);
  }
}

void strikeTick() {
  if ((ACC > STRIKE_THR) && (ACC < STRIKE_S_THR)) {
    //myDFPlayer.pause();
    nowNumber = random(8);
    myDFPlayer.play(strikes_short[nowNumber]);
    hit_flash();
    humTimer = millis() - 9000 + strike_s_time[nowNumber] - FLASH_DELAY;
    strike_flag = 1;
  }
  if (ACC >= STRIKE_S_THR) {
    //myDFPlayer.pause();
    nowNumber = random(8);
    myDFPlayer.play(strikes[nowNumber]);
    hit_flash();
    humTimer = millis() - 9000 + strike_time[nowNumber] - FLASH_DELAY;
    strike_flag = 1;
  }
}

void swingTick() {
  if (GYR > 80 && (millis() - swing_timeout > 100) && HUMmode) {
    swing_timeout = millis();
    if (((millis() - swing_timer) > SWING_TIMEOUT) && swing_flag && !strike_flag) {
      if (GYR >= SWING_THR) {      
        nowNumber = random(5);          
        //strcpy_P(BUFFER, (char*)pgm_read_word(&(swings[nowNumber])));
        myDFPlayer.play(swings[nowNumber]);               
        humTimer = millis() - 9000 + swing_time[nowNumber];
        swing_flag = 0;
        swing_timer = millis();
        swing_allow = 0;
      }
      if ((GYR > SWING_L_THR) && (GYR < SWING_THR)) {
        nowNumber = random(4);            
        //strcpy_P(BUFFER, (char*)pgm_read_word(&(swings_L[nowNumber])));
        myDFPlayer.play(swings_L[nowNumber]);              
        humTimer = millis() - 9000 + swing_time_L[nowNumber];
        swing_flag = 0;
        swing_timer = millis();
        swing_allow = 0;
      }
    }
  }
}

void getFreq() {
  if (ls_state) {                                               // if GyverSaber is on
    if (millis() - mpuTimer > 500) {                            
      accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);       

      // find absolute and divide on 100
      gyroX = abs(gx / 100);
      gyroY = abs(gy / 100);
      gyroZ = abs(gz / 100);
      accelX = abs(ax / 100);
      accelY = abs(ay / 100);
      accelZ = abs(az / 100);

      // vector sum
      ACC = sq((long)accelX) + sq((long)accelY) + sq((long)accelZ);
      ACC = sqrt(ACC);
      GYR = sq((long)gyroX) + sq((long)gyroY) + sq((long)gyroZ);
      GYR = sqrt((long)GYR);
      COMPL = ACC + GYR;
      /*
         // отладка работы IMU
         Serial.print("$");
         Serial.print(gyroX);
         Serial.print(" ");
         Serial.print(gyroY);
         Serial.print(" ");
         Serial.print(gyroZ);
         Serial.println(";");
      */
      freq = (long)COMPL * COMPL / 1500;                        // parabolic tone change
      freq = constrain(freq, 18, 300);                          
      freq_f = freq * k + freq_f * (1 - k);                     // smooth filter
      mpuTimer = micros();                                     
    }
  }
}

void setPixel(int Pixel, byte red, byte green, byte blue) {
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
  for (char i = 0; i <= (NUM_LEDS / 2 - 1); i++) {        
    setPixel(i, red, green, blue);
    setPixel((NUM_LEDS - 1 - i), red, green, blue);
    FastLED.show();
    delay(25);
  }
}

void light_down() {
  for (char i = (NUM_LEDS / 2 - 1); i >= 0; i--) {      
    setPixel(i, 0, 0, 0);
    setPixel((NUM_LEDS - 1 - i), 0, 0, 0);
    FastLED.show();
    delay(25);
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
  if (millis() - battery_timer > 30000 && ls_state && BATTERY_SAFE) {
    if (voltage_measure() < 15) {
      ls_chg_state = 1;
    }
    battery_timer = millis();
  }
}

byte voltage_measure() {
  voltage = 0;
  for (int i = 0; i < 10; i++) {    
    voltage += (float)analogRead(VOLT_PIN) * voltage_sensor_factor;
  }
  voltage = voltage * 0.1;           
  int volts = voltage / 300.0;    // 3 cells!!!
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

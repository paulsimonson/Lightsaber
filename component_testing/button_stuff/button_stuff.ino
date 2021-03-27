//Some of the following code is not necessary.  I am not spending a lot of time on this program...

// ---------------------------- SETTINGS -------------------------------
#define BTN_TIMEOUT 800     // button hold delay, ms

#define DEBUG 1             // debug information in Serial (1 - allow, 0 - disallow)
// ---------------------------- SETTINGS -------------------------------

#define BTN 3
#define IMU_GND A1
#define SD_GND A0
#define BTN_LED 4

// -------------------------- LIBS ---------------------------


// -------------------------- LIBS ---------------------------


// ------------------------------ VARIABLES ---------------------------------

float k = 0.2;
unsigned long humTimer = -9000, mpuTimer, nowTimer;
int stopTimer;
boolean bzzz_flag, ls_chg_state, ls_state;
boolean btnState, btn_flag, hold_flag;
byte btn_counter;
unsigned long btn_timer, PULSE_timer, swing_timer, swing_timeout, battery_timer, bzzTimer;
//byte nowNumber;
//boolean eeprom_flag, swing_flag, swing_allow, strike_flag, HUMmode;
int PULSEOffset;
// ------------------------------ VARIABLES ---------------------------------



void setup() {
  ls_state = 1;
  ls_chg_state = 0;

  Serial.begin(9600);

  pinMode(BTN, INPUT_PULLUP);
  pinMode(IMU_GND, OUTPUT);
  pinMode(SD_GND, OUTPUT);
  pinMode(BTN_LED, OUTPUT);
  digitalWrite(IMU_GND, 0);
  digitalWrite(SD_GND, 0);
  digitalWrite(BTN_LED, 1);
}

// --- MAIN LOOP---
void loop() {
   btnTick();

}
// --- MAIN LOOP---

void btnTick() {
  btnState = !digitalRead(BTN);
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
    Serial.println(F("BTN PRESS to change on/off state"));
  }

  if ((millis() - btn_timer > BTN_TIMEOUT) && (btn_counter != 0)) {
    if (ls_state) {
      if (btn_counter == 3) {               // 3 press count
        Serial.println(F("BTN PRESS to change colors"));
      }
      if (btn_counter == 5) {               // 5 press count
        Serial.println(F("BTN PRESS to change hum mode"));
      }
    }
    btn_counter = 0;
  }
}

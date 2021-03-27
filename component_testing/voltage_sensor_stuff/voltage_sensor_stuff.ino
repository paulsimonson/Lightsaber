//Voltage sensor:
//+ goes through 100 k ohm resistor
//ground goes through 51 k ohm resistor
//The two combine and go through the VOLT_PIN
//Connect the Arduino to the common ground.

#define VOLT_PIN A6

// ---------------------------- SETTINGS -------------------------------
#define NUM_LEDS 30         // number of microcircuits WS2811 on LED strip (note: one WS2811 controls 3 LEDs!)

#define R1 101250.0           // voltage divider real resistance
#define R2 51100.0            // voltage divider real resistance
//float calibration_factor = 1.0820399113082;
float calibration_factor = 1.0;

#define BATTERY_SAFE 1      // battery monitoring (1 - allow, 0 - disallow)

#define DEBUG 1             // debug information in Serial (1 - allow, 0 - disallow)
// ---------------------------- SETTINGS -------------------------------


// -------------------------- LIBS ---------------------------

// -------------------------- LIBS ---------------------------


// ------------------------------ VARIABLES ---------------------------------
boolean ls_chg_state;
unsigned long battery_timer;
float voltage;

// ------------------------------ VARIABLES ---------------------------------



void setup() {
  //Wire.begin();
  Serial.begin(9600);

  byte capacity = voltage_measure();       // get battery level
  capacity = map(capacity, 100, 0, (NUM_LEDS / 2 - 1), 1);  // convert into blade length

  if(DEBUG){
    Serial.print(F("Battery: "));
    Serial.println(capacity);
  }
}

// --- MAIN LOOP---
void loop() {
  batteryTick();
}
// --- MAIN LOOP---


void batteryTick() {
  if (millis() - battery_timer > 1000 && BATTERY_SAFE) {
    battery_timer = millis();
    voltage = (float)analogRead(VOLT_PIN) * (5.0 / 1023.0) * ((R1 + R2) / R2) * calibration_factor;
    if(DEBUG){
      Serial.print(F("Battery: "));
      Serial.println(voltage);
    }
  }
}

byte voltage_measure() {
  voltage = 0;
  for (int i = 0; i < 10; i++) {    
    //voltage += (float)analogRead(VOLT_PIN) * 5 / 1023 * (R1 + R2) / R2;
    voltage += (float)analogRead(VOLT_PIN) * (5.0 / 1023.0) * ((R1 + R2) / R2) * calibration_factor;

  }
  voltage = voltage / 10;           
  int volts = voltage / 3 * 100;    // 3 cells!!!
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

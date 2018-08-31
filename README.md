# Lightsaber

This is my fork from GyverSaber.


[![MadGyver YouTube](http://alexgyver.ru/git_madgyver.jpg)](https://www.youtube.com/channel/UCNEOyqhGzutj-YS-d5ckYdg?sub_confirmation=1)
# GyverSaber - Arduino based multicolor sound playing lightsaber
* [Project description](#chapter-0)
* [Folders](#chapter-1)
* [Schemes](#chapter-2)
* [Components](#chapter-3)
* [Assemply and set up](#chapter-7)

<a id="chapter-0"></a>
## Project description
SUPER-DUPER COOL ARDUINO BASED MULTICOLOR SOUND PLAYING LIGHTSABER!
https://youtu.be/__gp2RfTMnk

#### CAPABILITIES:
* Smooth turning on/off with lightsaber-like sound effect
* Randomly pulsing color (you can turn it off)
* Sounds:
  + MODE 1: generated hum. Frequency depends on angle velocity of blade
  + MODE 2: hum sound from SD card
    - Slow swing - long hum sound (randomly from 4 sounds)
    - Fast swing - short hum sound (randomly from 5 sounds)
* Bright white flash when hitting
* Play one of 16 hit sounds, when hit
  + Weak hit - short sound
  + Hard hit - long "bzzzghghhdh" sound
* After power on blade shows current battery level from 0 to 100 percent
* Battery safe mode:
  + Battery is drain BEFORE TURNING ON: GyverSaber will not turn on, button LED will PULSE a couple of times
  + Battery is drain AFTER TURNING ON: GyverSaber will be turned off automatically
#### CONTROL BUTTON:
* HOLD - turn on / turn off GyverSaber
* TRIPLE CLICK - change color (red - green - blue - yellow - pink - ice blue)
* QUINARY CLICK - change sound mode (hum generation - hum playing)
* Selected color and sound mode stored in EEPROM (non-volatile memory)

<a id="chapter-1"></a>
## Folders
- **libraries** - libraries
- **GyverSaber** - arduino sketch
- **SDsounds** - GyverSaber sound pack

<a id="chapter-2"></a>
## Schemes
![SCHEME](https://github.com/AlexGyver/EnglishProjects/blob/master/GyverSaber/schemes/draw.jpg)
![SCHEME](https://github.com/AlexGyver/EnglishProjects/blob/master/GyverSaber/schemes/scheme1.jpg)
![SCHEME](https://github.com/AlexGyver/EnglishProjects/blob/master/GyverSaber/schemes/scheme2.jpg)

<a id="chapter-3"></a>
## Components
* Arduino NANO http://ali.pub/20o35g  http://ali.pub/20o36t

https://www.aliexpress.com/item/GREATZT-Nano-Mini-USB-With-the-bootloader-compatible-for-arduino-Nano-3-0-controller-CH340-USB/32898269748.html?spm=2114.search0604.3.106.38862b20aP4OlF&ws_ab_test=searchweb0_0,searchweb201602_5_10065_10068_5910015_10130_5723115_10547_5723715_10546_5890015_10548_5724715_5723815_315_10545_10696_5723215_5724015_5723415_531_10084_5722215_10083_5970015_10618_5724315_10307_5724215_5724115_5723315_5723615_5722315_10059_5723015_5722115_5860016_100031_5723915_5725015_10103_5725115_5980015_5724915_5990015_5722415,searchweb201603_16,ppcSwitch_3&algo_expid=40c216dd-b9b7-4775-a82b-eef6f41ee7dc-18&algo_pvid=40c216dd-b9b7-4775-a82b-eef6f41ee7dc&transAbTest=ae803_2&priceBeautifyAB=0

* Addressable LED strip. WS2811, 12V. Take **white PCB, IP30, 60 LEDs per meter**
http://ali.pub/23csyd  http://ali.pub/23cszc  http://ali.pub/23cszq

https://www.aliexpress.com/item/5m-DC12V-Black-PCB-30-48-60-leds-m-10-16-20-ws2811-ic-meter-10/2000165819.html?spm=2114.search0604.3.13.138019d4wZqZcY&ws_ab_test=searchweb0_0,searchweb201602_5_10065_10068_5910015_10130_5723115_10547_5723715_10546_5890015_10548_5724715_5723815_315_10545_10696_5723215_5724015_5723415_531_10084_5722215_10083_5970015_10618_5724315_10307_5724215_5724115_5723315_5723615_5722315_10059_5723015_5722115_5860016_100031_5723915_5725015_10103_5725115_5980015_5724915_5990015_5722415-5990015,searchweb201603_16,ppcSwitch_3&algo_expid=436e9e80-1d03-49f7-9f12-27822623d2fc-2&algo_pvid=436e9e80-1d03-49f7-9f12-27822623d2fc&transAbTest=ae803_2&priceBeautifyAB=0

* Button with LED. **Take 5V version** http://ali.pub/23ct29

https://www.aliexpress.com/item/Angel-Eye-Metal-LED-illuminated-Momentary-16mm-Push-Button-Switch-Car-Dash-12V-red-blue-green/32697109472.html?spm=2114.search0604.3.15.68aa1301mLgvV4&ws_ab_test=searchweb0_0,searchweb201602_5_10065_10068_5910015_10130_5723115_10547_5723715_10546_5890015_10548_5724715_5723815_315_10545_10696_5723215_5724015_5723415_531_10084_5722215_10083_5970015_10618_5724315_10307_5724215_5724115_5723315_5723615_5722315_10059_5723015_5722115_5860016_100031_5723915_5725015_10103_5725115_5980015_5724915_5990015_5722415,searchweb201603_16,ppcSwitch_3&algo_expid=b536f2ea-426e-4139-8c63-9888377c0825-2&algo_pvid=b536f2ea-426e-4139-8c63-9888377c0825&transAbTest=ae803_2&priceBeautifyAB=0

* MPU6050 http://ali.pub/23mryw  http://ali.pub/23mst1

https://www.aliexpress.com/item/Free-shipping-GY-521-MPU-6050-MPU6050-Module-3-Axis-analog-gyro-sensors-3-Axis-Accelerometer/714775852.html?spm=2114.search0604.3.65.140b69caUbqMcB&ws_ab_test=searchweb0_0,searchweb201602_5_10065_10068_5910015_10130_5723115_10547_5723715_10546_5890015_10548_5724715_5723815_315_10545_10696_5723215_5724015_5723415_531_10084_5722215_10083_5970015_10618_5724315_10307_5724215_5724115_5723315_5723615_5722315_10059_5723015_5722115_5860016_100031_5723915_5725015_10103_5725115_5980015_5724915_5990015_5722415,searchweb201603_16,ppcSwitch_3&algo_expid=be1c55c5-ee0a-4137-ae3c-ce7d955c960d-9&algo_pvid=be1c55c5-ee0a-4137-ae3c-ce7d955c960d&transAbTest=ae803_2&priceBeautifyAB=0

* Cheap MicroSD http://ali.pub/23msne  http://ali.pub/23msqp

https://www.aliexpress.com/item/-/32883703410.html?spm=a2g0s.13010208.99999999.260.30453c004NdqnN

* MicroSD module mini http://ali.pub/23ms27  http://ali.pub/23ms5b
* Or this http://ali.pub/23ms11

https://www.aliexpress.com/item/GREATZT-1Pcs-Micro-SD-Storage-Expansion-Board-Mini-Micro-SD-TF-Card-Memory-Shield-Module-With/32865801075.html?spm=2114.search0604.3.15.61f919cbpz6zX9&ws_ab_test=searchweb0_0,searchweb201602_5_10065_10068_5910015_10130_5723115_10547_5723715_10546_5890015_10548_5724715_5723815_315_10545_10696_5723215_5724015_5723415_531_10084_5722215_10083_5970015_10618_5724315_10307_5724215_5724115_5723315_5723615_5722315_10059_5723015_5722115_5860016_100031_5723915_5725015_10103_5725115_5980015_5724915_5990015_5722415,searchweb201603_16,ppcSwitch_3&algo_expid=725ca928-9bc9-4214-9ce4-a4f44cedce10-2&algo_pvid=725ca928-9bc9-4214-9ce4-a4f44cedce10&transAbTest=ae803_2&priceBeautifyAB=0

* Batteries 18650 with protection http://ali.pub/23moiu  http://ali.pub/23moke  http://ali.pub/23mol6

https://www.aliexpress.com/item/3-PCS-lot-100-Brand-New-Original-NCR18650B-3-7-v-3400mah-18650-Li-ion-Rechargeable/32324926502.html?spm=2114.search0604.3.1.6cde6339vQ8T0I&ws_ab_test=searchweb0_0,searchweb201602_5_10065_10068_5910015_10130_5723115_10547_5723715_10546_5890015_10548_5724715_5723815_315_10545_10696_5723215_5724015_5723415_531_10084_5722215_10083_5970015_10618_5724315_10307_5724215_5724115_5723315_5723615_5722315_10059_5723015_5722115_5860016_100031_5723915_5725015_10103_5725115_5980015_5724915_5990015_5722415,searchweb201603_16,ppcSwitch_3&algo_expid=cf919a0c-aa36-4680-82eb-e14b3e971f25-0&algo_pvid=cf919a0c-aa36-4680-82eb-e14b3e971f25&transAbTest=ae803_2&priceBeautifyAB=0

* DCDC Step Down http://ali.pub/23mpex  http://ali.pub/23mpfi  http://ali.pub/23mph9
* Amplifier http://ali.pub/23mp6d  http://ali.pub/23mp75  http://ali.pub/23mp7q
* Speaker http://ali.pub/23mq8h  http://ali.pub/23mq9g  http://ali.pub/23mqc6
* Resistors KIT http://ali.pub/23mqei  http://ali.pub/23mqfo
* Power button http://ali.pub/23mtiw
* Charging port http://ali.pub/23mtf0  http://ali.pub/23mt69
* CC CV charger for 3 cells http://ali.pub/23mt8s  http://ali.pub/23mt9d  http://ali.pub/23mt9k
* Prototype board http://ali.pub/23mrwy  

<a id="chapter-7"></a>
## Assembly and set up
* [Quick start with Arduino](https://learn.sparkfun.com/tutorials/installing-arduino-ide)
* Open GyverSaber.ino and tune:
  - Number of microcircuits WS2811 on LED strip (note: one WS2811 controls 3 LEDs!)
  - Turn on or turn off blade pulsation
  - Hardly recommend measure real resistance of voltage divider resistors
    + System can work without battery monitoring, just deactivate BATTERY_SAFE. **BUT IT IS NOT RECOMMENDED**
* Flash arduino
* MicroSD info:
  - Size < 4G
  - Format to FAT
  - Copy audiofiles **in the root**
  - If you want add your own sounds, convert them to .WAV:
    + 8 bit
	+ 16-32 kHz
	+ Mono
	+ Use online converters or Total Audio Converter
* Assemble schmeme
  - **WARNING!** If you are flashing **assembled scheme**, you must power up it! Arduino will not work correct with connected DCDC converter!
* Enjoy!

## GyverSaber settings
    NUM_LEDS 30         // number of microcircuits WS2811 on LED strip (note: one WS2811 controls 3 LEDs!)
    BTN_TIMEOUT 800     // button hold delay, ms
    BRIGHTNESS 255      // max LED brightness (0 - 255)

    SWING_TIMEOUT 500   // timeout between swings
    SWING_L_THR 150     // swing angle speed threshold
    SWING_THR 300       // fast swing angle speed threshold
    STRIKE_THR 150      // hit acceleration threshold
    STRIKE_S_THR 320    // hard hit acceleration threshold
    FLASH_DELAY 80      // flash time while hit

    PULSE_ALLOW 1       // blade pulsation (1 - allow, 0 - disallow)
    PULSE_AMPL 20       // pulse amplitude
    PULSE_DELAY 30      // delay between pulses

    R1 100000           // voltage divider real resistance
    R2 51000            // voltage divider real resistance
    BATTERY_SAFE 1      // battery monitoring (1 - allow, 0 - disallow)

    DEBUG 0             // debug information in Serial (1 - allow, 0 - disallow)

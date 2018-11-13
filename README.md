# Lightsaber

This is my fork from GyverSaber.


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
  + MODE 1: generated hum. Frequency depends on anglular velocity of blade
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

* Button with LED. **Buy the 5V version** http://ali.pub/23ct29

https://www.aliexpress.com/item/Angel-Eye-Metal-LED-illuminated-Momentary-16mm-Push-Button-Switch-Car-Dash-12V-red-blue-green/32697109472.html?spm=2114.search0604.3.15.68aa1301mLgvV4&ws_ab_test=searchweb0_0,searchweb201602_5_10065_10068_5910015_10130_5723115_10547_5723715_10546_5890015_10548_5724715_5723815_315_10545_10696_5723215_5724015_5723415_531_10084_5722215_10083_5970015_10618_5724315_10307_5724215_5724115_5723315_5723615_5722315_10059_5723015_5722115_5860016_100031_5723915_5725015_10103_5725115_5980015_5724915_5990015_5722415,searchweb201603_16,ppcSwitch_3&algo_expid=b536f2ea-426e-4139-8c63-9888377c0825-2&algo_pvid=b536f2ea-426e-4139-8c63-9888377c0825&transAbTest=ae803_2&priceBeautifyAB=0

* MPU6050 http://ali.pub/23mryw  http://ali.pub/23mst1

https://www.aliexpress.com/item/Free-shipping-GY-521-MPU-6050-MPU6050-Module-3-Axis-analog-gyro-sensors-3-Axis-Accelerometer/714775852.html?spm=2114.search0604.3.65.140b69caUbqMcB&ws_ab_test=searchweb0_0,searchweb201602_5_10065_10068_5910015_10130_5723115_10547_5723715_10546_5890015_10548_5724715_5723815_315_10545_10696_5723215_5724015_5723415_531_10084_5722215_10083_5970015_10618_5724315_10307_5724215_5724115_5723315_5723615_5722315_10059_5723015_5722115_5860016_100031_5723915_5725015_10103_5725115_5980015_5724915_5990015_5722415,searchweb201603_16,ppcSwitch_3&algo_expid=be1c55c5-ee0a-4137-ae3c-ce7d955c960d-9&algo_pvid=be1c55c5-ee0a-4137-ae3c-ce7d955c960d&transAbTest=ae803_2&priceBeautifyAB=0

* Cheap MicroSD http://ali.pub/23msne  http://ali.pub/23msqp

https://www.aliexpress.com/item/-/32883703410.html?spm=a2g0s.13010208.99999999.260.30453c004NdqnN

* MicroSD module mini http://ali.pub/23ms27  http://ali.pub/23ms5b
* Or this http://ali.pub/23ms11

https://www.aliexpress.com/item/GREATZT-1Pcs-Micro-SD-Storage-Expansion-Board-Mini-Micro-SD-TF-Card-Memory-Shield-Module-With/32865801075.html?spm=2114.search0604.3.15.61f919cbpz6zX9&ws_ab_test=searchweb0_0,searchweb201602_5_10065_10068_5910015_10130_5723115_10547_5723715_10546_5890015_10548_5724715_5723815_315_10545_10696_5723215_5724015_5723415_531_10084_5722215_10083_5970015_10618_5724315_10307_5724215_5724115_5723315_5723615_5722315_10059_5723015_5722115_5860016_100031_5723915_5725015_10103_5725115_5980015_5724915_5990015_5722415,searchweb201603_16,ppcSwitch_3&algo_expid=725ca928-9bc9-4214-9ce4-a4f44cedce10-2&algo_pvid=725ca928-9bc9-4214-9ce4-a4f44cedce10&transAbTest=ae803_2&priceBeautifyAB=0

* Batteries 18650 with protection http://ali.pub/23moiu  http://ali.pub/23moke  http://ali.pub/23mol6

These are probably not a good idea if building a toy for kids...

https://www.aliexpress.com/item/3-PCS-lot-100-Brand-New-Original-NCR18650B-3-7-v-3400mah-18650-Li-ion-Rechargeable/32324926502.html?spm=2114.search0604.3.1.6cde6339vQ8T0I&ws_ab_test=searchweb0_0,searchweb201602_5_10065_10068_5910015_10130_5723115_10547_5723715_10546_5890015_10548_5724715_5723815_315_10545_10696_5723215_5724015_5723415_531_10084_5722215_10083_5970015_10618_5724315_10307_5724215_5724115_5723315_5723615_5722315_10059_5723015_5722115_5860016_100031_5723915_5725015_10103_5725115_5980015_5724915_5990015_5722415,searchweb201603_16,ppcSwitch_3&algo_expid=cf919a0c-aa36-4680-82eb-e14b3e971f25-0&algo_pvid=cf919a0c-aa36-4680-82eb-e14b3e971f25&transAbTest=ae803_2&priceBeautifyAB=0

* DCDC Step Down http://ali.pub/23mpex  http://ali.pub/23mpfi  http://ali.pub/23mph9

https://www.aliexpress.com/item/1PCS-Mini-DC-DC-12-24V-To-5V-3A-Step-Down-Power-Supply-Module-Voltage-Buck/32819071159.html?spm=2114.search0604.3.23.64535c88w1ppXe&ws_ab_test=searchweb0_0,searchweb201602_5_10065_10068_5910015_10130_5723115_10547_5723715_10546_5890015_10548_5724715_5723815_315_10545_10696_5723215_5724015_5723415_531_10084_5722215_10083_5970015_10618_5724315_10307_5724215_5724115_5723315_5723615_5722315_10059_5723015_5722115_5860016_100031_5723915_5725015_10103_5725115_5980015_5724915_5990015_5722415,searchweb201603_16,ppcSwitch_3&algo_expid=65fc3731-9ec1-4ced-9048-a8843342bcbf-3&algo_pvid=65fc3731-9ec1-4ced-9048-a8843342bcbf&transAbTest=ae803_2&priceBeautifyAB=0

https://www.aliexpress.com/item/Smart-Electronics-XM1584-Ultra-small-Size-DC-DC-Step-Down-Power-Supply-Module-3A-Adjustable-for/32608213464.html?spm=2114.search0604.3.9.53313925DNEXot&ws_ab_test=searchweb0_0,searchweb201602_5_10065_10130_10068_10547_10890_10546_5853215_10548_10545_10696_5851613_5853015_10924_10925_10926_10618_10920_10921_10307_5852915_10922_537_536_10059_100031_10103_5729220_5852211_5852513_319_317_5733420_5852411_453_10084_454_10083_5733620_5850015_5733120_5733220_5733320_5733520_5850913_10884_5730320_10887_10928_321_322_5852715_5852613-5733320_10890,searchweb201603_51,ppcSwitch_0&algo_expid=7314ab2d-1fc8-414c-8299-091e40c96a26-1&algo_pvid=7314ab2d-1fc8-414c-8299-091e40c96a26

* Amplifier http://ali.pub/23mp6d  http://ali.pub/23mp75  http://ali.pub/23mp7q

https://www.aliexpress.com/item/1pcs-lot-PAM8403-Super-mini-digital-amplifier-board-2-3W-Class-D-digital-amplifier-board-efficient/32477442965.html?spm=2114.search0604.3.153.54382cd8VWInPQ&ws_ab_test=searchweb0_0,searchweb201602_5_10065_10068_5910015_10130_5723115_10547_5723715_10546_5890015_10548_5724715_5723815_315_10545_10696_5723215_5724015_5723415_531_10084_5722215_10083_5970015_10618_5724315_10307_5724215_5724115_5723315_5723615_5722315_10059_5723015_5722115_5860016_100031_5723915_5725015_10103_5725115_5980015_5724915_5990015_5722415,searchweb201603_16,ppcSwitch_3&algo_expid=3e7b7b01-a0a0-4339-8c05-df39a941927d-25&algo_pvid=3e7b7b01-a0a0-4339-8c05-df39a941927d&transAbTest=ae803_2&priceBeautifyAB=0

* Speaker http://ali.pub/23mq8h  http://ali.pub/23mq9g  http://ali.pub/23mqc6

https://www.aliexpress.com/item/2pcs-45MM-4Ohm-3W-full-range-Speaker-Loudspeaker-For-DIY/32581228628.html?spm=2114.search0604.3.53.13ef648duBdBAC&ws_ab_test=searchweb0_0,searchweb201602_5_10065_10068_5910015_10130_5723115_10547_5723715_10546_5890015_10548_5724715_5723815_315_10545_10696_5723215_5724015_5723415_531_10084_5722215_10083_5970015_10618_5724315_10307_5724215_5724115_5723315_5723615_5722315_10059_5723015_5722115_5860016_100031_5723915_5725015_10103_5725115_5980015_5724915_5990015_5722415-5990015,searchweb201603_16,ppcSwitch_3&algo_expid=a7ca4372-7317-4349-8a64-36343530574b-8&algo_pvid=a7ca4372-7317-4349-8a64-36343530574b&transAbTest=ae803_2&priceBeautifyAB=0

* Resistors KIT http://ali.pub/23mqei  http://ali.pub/23mqfo
* Power button http://ali.pub/23mtiw

https://www.aliexpress.com/item/10Pcs-16mm-Diameter-Small-Round-Boat-Rocker-Switches-Black-Mini-Round-2-Pin-ON-OFF-Rocker/32861276029.html?spm=a2g0s.13010208.99999999.260.c3123c00P51IU8

* Charging port http://ali.pub/23mtf0  http://ali.pub/23mt69

https://www.aliexpress.com/item/Dropshipping-5-5-mm-x-2-1mm-DC-Power-Jack-Socket-Female-Panel-Mount-Connector-C1Hot/32824405805.html?spm=2114.search0604.3.2.66f96b5bphfruZ&ws_ab_test=searchweb0_0,searchweb201602_5_10065_10068_5910015_10130_5723115_10547_5723715_10546_5890015_10548_5724715_5723815_315_10545_10696_5723215_5724015_5723415_531_10084_5722215_10083_5970015_10618_5724315_10307_5724215_5724115_5723315_5723615_5722315_10059_5723015_5722115_5860016_100031_5723915_5725015_10103_5725115_5980015_5724915_5990015_5722415-5990015,searchweb201603_16,ppcSwitch_3&algo_expid=3422a132-2317-4a5e-bfbd-9fd73d352a4b-0&algo_pvid=3422a132-2317-4a5e-bfbd-9fd73d352a4b&transAbTest=ae803_2&priceBeautifyAB=0

* CC CV charger for 3 cells http://ali.pub/23mt8s  http://ali.pub/23mt9d  http://ali.pub/23mt9k

Get 12.6V 1 amp 2.1 mm x 5.5 mm adapter.  It has to be CC CV.



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
* Assembly scheme
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


## Hilt
If I had the time...
https://youtu.be/e-HF0BOmt70

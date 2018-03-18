// Code to control TEA6825T base tuners with 6810 or 6811 PLL
// Created by Ricardo Cruz 18/03/2018
// I'm not responsible for any damaged cause by this code.

#include <Wire.h>

// TEA6825 BYTE VARS
byte TEA6825ADDRESS = B1100001;
byte TEA6825Tb1;
byte TEA6825Tb2;
// END OF TEA6825 VARS

//Program VARS
int minfmfreq = 881;
int maxfmfreq = 1088;
char tunefreqchar[4];
int freqnum1;
int freqnum2;
int freqnum3;
int freqnum4;
int tunefreq;
int lasttunefreq;
int freq;
int serchar;

//TEA6810 BYTE VARS
byte TEA6810ADDRESS = B1100010;
byte TEA6810b3;
byte TEA6810b4 = B00000000;
byte freqh;
byte freql;
// END OF TEA6810 BYTE VARS

// TEA6825T BYTE 1 CONFIGURATION VARIABLES
boolean MONO_STEREO; // 1 = Mono 0 = Stereo
boolean LSB_REF_SYNTH; // 50Khz = 1
boolean REF_SYNTH; // 50 Khz = 0
boolean MSB_REF_SYNTH; // 50 Khz = 1
boolean TUNE_MUT; // OFF = 1 ON = 0
boolean SDS_SDR_HOLD; // OFF = 1 ON = 0
boolean RADIO_MUTE; // OFF = 1 ON = 0
boolean I2C_FRONT_END; // ENABLED = 1 DISABLED = 0
// End

// TEA6825T BYTE 2 CONFIGURATION VARIABLES
boolean AM_FM; // AM = 0 FM = 1
boolean DIVIDER_AM_MIXER; // DIV BY 2 = 0 DIV BY 6 = 1
boolean IF_COUNT_MEASURE_TIME; // 40ms = 0 4ms = 1
boolean SDR; // SDR OFF = 0 SDR ON = 1
boolean IF_PRESCALER_DIV_RATE; // DIV BY 200 = 0 DIV BY 25 = 1
boolean SENSITIVITY; // UNCHANGED = 0 MULTIPATH SWITH = 1
boolean TEMP_COMPENSATION; // OFF = 0 ON = 1
boolean NOISE_BLANKER; // DEACTIVATED BY HIGH MODULATION = 0 NOT DEACTIVATED = 1
// End

//TEA6810 BYTE 3 CONFIGURATION VARIABLES
boolean MSB_INLOCK_COUNTER;
boolean LSB_INLOCK_COUNTER;
boolean OSC_CURRENT;
boolean CHARGE_PUMP_CURRENT;
boolean LOCAL;
boolean MSB_DIVIDER_N2;
boolean LSB_DIVIDER_N2;
boolean MODE;
//END OF TEA6810 BYTE 3 CONFIGURATION VARIABLES

//TEA6810 BYTE 3 DEFINITIONS
#define MSB_INLOCK_COUNTER 0
#define LSB_INLOCK_COUNTER 0
#define OSC_CURRENT 1
#define CHARGE_PUMP_CURRENT 1
#define LOCAL 0
#define MSB_DIVIDER_N2 1
#define LSB_DIVIDER_N2 1
#define MODE 1
//END OF TEA6810 BYTE 3 DEFINITIONS

// TEA6825T BYTE2 DEFINITIONS
#define AM_FM 1
#define DIVIDER_AM_MIXER 0
#define IF_COUNT_MEASURE_TIME 0
#define SDR 0
#define IF_PRESCALER_DIV_RATE 0
#define SENSITIVITY 0
#define TEMP_COMPENSATION 0
#define NOISE_BLANKER 0
//End

// TEA6825T BYTE1 DEFINITIONS
#define MONO_STEREO 0
#define LSB_REF_SYNTH 1
#define REF_SYNTH 0
#define MSB_REF_SYNTH 1
#define TUNE_MUT 1
#define SDS_SDR_HOLD 1
#define RADIO_MUTE 1
#define I2C_FRONT_END 1
//End

void calculatefrequency() {
  freq = tunefreq * 2;
  freq = freq + 1442;
  freql = lowByte(freq);
  freqh = highByte(freq);
 }

void MAKETEA6810TBYTE3() { 
    if (MSB_INLOCK_COUNTER == true) {
    bitSet(TEA6810b3, 7);
  }
  else {
    bitClear(TEA6810b3, 7);
  }
  if (LSB_INLOCK_COUNTER == true) {
    bitSet(TEA6810b3, 6);
  }
  else {
    bitClear(TEA6810b3, 6);
  }
  if (OSC_CURRENT == true) {
    bitSet(TEA6810b3, 5);
  }
  else {
    bitClear(TEA6810b3, 5);
  }
  if (CHARGE_PUMP_CURRENT == true) {
    bitSet(TEA6810b3, 4);
  }
  else {
    bitClear(TEA6810b3, 4);
  }
  if (LOCAL == true) {
    bitSet(TEA6810b3, 3);
  }
  else
  { bitClear(TEA6810b3, 3);
  }
  if (MSB_DIVIDER_N2 == true) {
    bitSet(TEA6810b3, 2);
  }
  else {
    bitClear(TEA6810b3, 2);
  }
  if (LSB_DIVIDER_N2 == true) {
    bitSet(TEA6810b3, 1);
  }
  else {
    bitClear(TEA6810b3, 1);
  }
  if (MODE == true) {
    bitSet(TEA6810b3, 0);
  }
  else {
    bitClear(TEA6810b3, 0);
  }
  return;
}      


void MAKETEA6825TBYTE1() { // CONSTRUCT TEA6825 BYTE1
  if (MONO_STEREO == true) {
    bitSet(TEA6825Tb1, 0);
  }
  else {
    bitClear(TEA6825Tb1, 0);
  }
  if (LSB_REF_SYNTH == true) {
    bitSet(TEA6825Tb1, 1);
  }
  else {
    bitClear(TEA6825Tb1, 1);
  }
  if (REF_SYNTH == true) {
    bitSet(TEA6825Tb1, 2);
  }
  else {
    bitClear(TEA6825Tb1, 2);
  }
  if (MSB_REF_SYNTH == true) {
    bitSet(TEA6825Tb1, 3);
  }
  else {
    bitClear(TEA6825Tb1, 3);
  }
  if (TUNE_MUT == true) {
    bitSet(TEA6825Tb1, 4);
  }
  else
  { bitClear(TEA6825Tb1, 4);
  }
  if (SDS_SDR_HOLD == true) {
    bitSet(TEA6825Tb1, 5);
  }
  else {
    bitClear(TEA6825Tb1, 5);
  }
  if (RADIO_MUTE == true) {
    bitSet(TEA6825Tb1, 6);
  }
  else {
    bitClear(TEA6825Tb1, 6);
  }
  if (I2C_FRONT_END == true) {
    bitSet(TEA6825Tb1, 7);
  }
  else {
    bitClear(TEA6825Tb1, 7);
  }
  return;
}                                  // END OF TEA6825 BYTE 1 CONSTRUCTION

void MAKETEA6825TBYTE2() {        // CONSTRUCT TEA6825 BYTE 2
  if (AM_FM == true) {
    bitSet(TEA6825Tb2, 0);
  }
  else {
    bitClear(TEA6825Tb2, 0);
  }
  if (DIVIDER_AM_MIXER == true) {
    bitSet(TEA6825Tb2, 1);
  }
  else {
    bitClear(TEA6825Tb2, 1);
  }
  if (IF_COUNT_MEASURE_TIME == true) {
    bitSet(TEA6825Tb2, 2);
  }
  else {
    bitClear(TEA6825Tb2, 2);
  }
  if (SDR == true) {
    bitSet(TEA6825Tb2, 3);
  }
  else {
    bitClear(TEA6825Tb2, 3);
  }
  if (IF_PRESCALER_DIV_RATE == true) {
    bitSet(TEA6825Tb2, 4);
  }
  else
  { bitClear(TEA6825Tb2, 4);
  }
  if (SENSITIVITY == true) {
    bitSet(TEA6825Tb2, 5);
  }
  else {
    bitClear(TEA6825Tb2, 5);
  }
  if (TEMP_COMPENSATION == true) {
    bitSet(TEA6825Tb2, 6);
  }
  else {
    bitClear(TEA6825Tb2, 6);
  }
  if (NOISE_BLANKER == true) {
    bitSet(TEA6825Tb2, 7);
  }
  else {
    bitClear(TEA6825Tb2, 7);
  }
  return;
} // END of TEA6825T BYTE 2 CONSTRUCTION

void setup()
{ Serial.begin(9600);
  Wire.begin();
}

void senddata() {
  MAKETEA6825TBYTE1();
  MAKETEA6825TBYTE2();
  MAKETEA6810TBYTE3();
calculatefrequency();
  Wire.beginTransmission(TEA6825ADDRESS); // i2c start tea6825
  Wire.write(TEA6825Tb1); // send tea6825 byte1
  Wire.write(TEA6825Tb2); // send tea6825 byte2
  Wire.endTransmission(true); // i2c stop tea6825
  Wire.beginTransmission(TEA6810ADDRESS);
  Wire.write(freql);
  Wire.write(freqh);
  Wire.write(TEA6810b3);
  Wire.write(TEA6810b4);
  Wire.endTransmission(true);
  
}

void loop()
{ if (tunefreq < minfmfreq) {
  tunefreq = minfmfreq;
  }
  if (tunefreq > maxfmfreq)
  {tunefreq = maxfmfreq;
  }
  if (Serial.available() > 0) {
    serchar = Serial.read();
  }
  if (serchar == 97) {  // a
    tunefreq = tunefreq + 1;
    serchar = 0;
  }
  if (serchar == 122 ) { // z
   tunefreq = tunefreq - 1;
   serchar = 0;
}
if (tunefreq != lasttunefreq) { 
senddata();
Serial.print( " FREQUENCIA ");
freqnum4 = tunefreq % 10;
freqnum3 = tunefreq / 10 % 10;
freqnum2 = tunefreq / 100 % 10;
freqnum1 = tunefreq / 1000 % 10;
if (tunefreq < 1000) {
//Serial.print(freqnum1);
Serial.print(freqnum2);
Serial.print(freqnum3);
Serial.print(".");
Serial.print(freqnum4);
Serial.println("MHz");
}
if (tunefreq > 999) {
Serial.print(freqnum1);
Serial.print(freqnum2);
Serial.print(freqnum3);
Serial.print(".");
Serial.println(freqnum4);
Serial.println("MHz");
}
lasttunefreq = tunefreq;}
}

/* Example: nRF24L01 
 
   1 - GND 
   2 - VCC 3.3V  
   3 - CE - Arduino pin 9
   4 - CSN - Arduino pin 10
   5 - SCK - Arduino pin 13
   6 - MOSI - Arduino pin 11
   7 - MISO - Arduino pin 12
   8 - UNUSED 
 
  You can used an Analog Joystick or 2 10K potentiometers 
 
   GND - Arduino GND 
   VCC - Arduino +5V
   X Pot - Arduino A0
   Y Pot - Arduino A1
 
/*----- Import all required Libraries -----*/
 
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
 
/*----- Declare all constant pin to be used ----*/ 
#define CE_PIN   9  // Uno= 9     // Mega = 48
#define CSN_PIN 10  // Uno= 10    // Mega = 53

const uint64_t pipe = 0xE8E8F0F0E1LL; // This is the transmit pipe to communicate the two module
RF24 radio(CE_PIN, CSN_PIN); // Activate  the Radio 
int joystick[7];  // 7 element array holding the Joystick readings

#define JOYSTICK_X A0
#define JOYSTICK_Y A1
#define JOYSTICK_UP   2
#define JOYSTICK_RIGHT  3
#define JOYSTICK_DOWN   4
#define JOYSTICK_LEFT   5

void setup()   
{
  Serial.begin(9600); /* Opening the Serial Communication */
  radio.begin();
  radio.openWritingPipe(pipe);

}//--(end setup )---
 
void loop()   /* Runs Continuously */
{
  joystick[0] = map(analogRead(JOYSTICK_X), 0, 1023, 0, 179); // Reading Analog X
  joystick[1] = map(analogRead(JOYSTICK_Y), 0, 1023, 0, 179); // Reading Analog Y 
 
  joystick[2] = digitalRead(JOYSTICK_UP); 
  joystick[3] = digitalRead(JOYSTICK_RIGHT); 
  joystick[4] = digitalRead(JOYSTICK_DOWN); 
  joystick[5] = digitalRead(JOYSTICK_LEFT); 
 
  radio.write( joystick, sizeof(joystick) );



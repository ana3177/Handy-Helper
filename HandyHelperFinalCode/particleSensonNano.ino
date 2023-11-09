int RED = 9;
int GREEN = 10;
int BLUE = 11;
int IRsens = 2; /*OUT pin on PIR sensor connected to D5 on nano */
int IRstat = 0; /*Status of the PIR sensor, assume no initial motion */

#include <Wire.h>
#include "MAX30105.h"

MAX30105 particleSensor;

long unblockedValue; //Average IR at power up


void setup() {
  
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  Serial.begin(9600);

   if (particleSensor.begin(Wire, I2C_SPEED_FAST) == false) //Use default I2C port, 400kHz speed
  {
    Serial.println("MAX30105 was not found. Please check wiring/power. ");
    while (1);
  }

  byte ledBrightness = 0xFF; //Options: 0=Off to 255=50mA
  byte sampleAverage = 4; //Options: 1, 2, 4, 8, 16, 32
  byte ledMode = 2; //Options: 1 = Red only, 2 = Red + IR, 3 = Red + IR + Green
  int sampleRate = 400; //Options: 50, 100, 200, 400, 800, 1000, 1600, 3200
  int pulseWidth = 411; //Options: 69, 118, 215, 411
  int adcRange = 2048; //Options: 2048, 4096, 8192, 16384

  particleSensor.setup(ledBrightness, sampleAverage, ledMode, sampleRate, pulseWidth, adcRange); //Configure sensor with these settings


  //Take an average of IR readings at power up
  unblockedValue = 0;
  for (byte x = 0 ; x < 32 ; x++)
  {
    unblockedValue += particleSensor.getIR(); //Read the IR value
  }
  unblockedValue /= 32;

  delay(3000);
  
}

void loop() {
  long currentDelta = particleSensor.getIR() - unblockedValue;
  unsigned long timer =0;
  if(currentDelta >(long)10){
  timer = millis();
  Serial.println(timer);
  if (timer >= 3000){
    startSequence();
    timer = 0;
  }
  else{
    displayColor(0,0,0);
    Serial.println("bye bye");
  }
 }
 else{
  timer = 0;
  Serial.println("no mo");
 }
}

void displayColor(int r, int g, int b){
  analogWrite(RED,255-r);
  analogWrite(GREEN,255-g);
  analogWrite(BLUE,255-b);
}

void startSequence(){
  Serial.println("ster");
  /*blink yellow x3*/
  for(int i=0; i<2; i++){
    displayColor(255,255,0);
    delay(1000);
    displayColor(0,0,0);
    delay(1000);
  }

  /*fade yellow to green*/
  for(int i=0; i<255; i++){
    int r=255-i;
    displayColor(r, 255, 0);
    delay(35);
  }

  /*blink green 3x */
  for (int i=0; i<2; i++){
    displayColor(0,255,0);
    delay(1000);
    displayColor(0,0,0);
    delay(1000);
  }

  /* fade green to yellow */
  for (int i=0; i<255; i++){
    displayColor(i, 255, 0);
    delay(50);
  }

  /*fade yellow to red*/
  for(int i=0; i<255; i++){
    int g=255-i;
    displayColor(255,g,0);
    delay(25);
    
  }

 displayColor(0,0,0);
 delay(2000);
  
}


int BLUE=8;//pinD5 on nano 10 on lily
int GREEN=9;//pinD6 on nano 11 on lily
int RED=6;//pinD3 on nano 9on lily
const int IRsens =5; //Infared Sensor Connected to pin 2
int sensState = LOW; //no motion is default
int sensVal=0; //placeholder for reading the output
int handsCleaned=0;

void setup()
{
  
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  pinMode(IRsens, INPUT);
  //digitalWrite(RED, LOW);
  digitalWrite(GREEN,HIGH);
  analogWrite(RED, 255);
  //digitalWrite(BLUE,LOW);
  //digitalWrite(IRsens, LOW);
  //Wire.begin(2);
  attachInterrupt(digitalPinToInterrupt(5),pirResponse,CHANGE);
  Serial.begin(9600);
  

}
int redValue;
int greenValue;
int blueValue;
long Tolerance=1500; //motion has to be detected for 1.5s to trigger
unsigned long startTime;
long motionTime=0;

 
void loop()
{
  
    //Wire.beginTransmission(IRsens);
    sensVal=digitalRead(IRsens);
    Serial.println(sensVal);
    if(sensVal==HIGH){ //if it detects something
    analogWrite(RED, 255); //turn on LED red (can use any # 0-255)
      startTime = millis();
      Serial.println(startTime);
      if(startTime>=Tolerance){
        startSequence();
        Serial.println("sequenceStarted");
      }
      if(sensState==LOW){
      Serial.println("Motion detected");
      sensState=HIGH;
      }
    }
  else{
    Serial.println("else");
    analogWrite(BLUE ,255); 
    analogWrite(RED, 0);
    if (sensState==HIGH){
      Serial.println("No Motion Detected");
      sensState = LOW;
      }
  }  
}

void pirResponse(){
  if (sensVal == 1{
    sensVal=0;
    Serial.println("no mot");
  }
  else{
    sensVal=1;
    Serial.println("yeeee");
    startSequence();
  }
}

void startSequence(){
    redValue=255;
    greenValue=0;
    blueValue=0;
    for(int i=0; i<3; i+=1){//red LED blinks x3 to let you know its starting 
    analogWrite(RED, 255);
    delay(500);
    analogWrite(RED, 0);
      delay(500);
    }
    for (int i=0; i<255; i+=1){//fades from red to green
      redValue -=1;
      greenValue +=1;
      analogWrite(RED, redValue); 
      analogWrite(GREEN, greenValue);
      delay(20);//this number will change how long it takes to go from red to green. we will have to play with this to get it to be 5s (or avg soap time)
     // while(digitalRead(IRsens)==HIGH);
  }
    for(int i=0; i<=3; i+=1){//blink green 3X to start 20s wash
    analogWrite(GREEN, 255);
    delay(500);
    analogWrite(GREEN, 0);
      delay(500);
    }
    
    redValue=0;
    greenValue=255;
    blueValue=0;
    for (int i=0; i<255; i+=1){
      greenValue -=1;
      blueValue +=1;
      analogWrite(GREEN, greenValue);
      analogWrite(BLUE, blueValue);
      delay(85); //This one for green to blue = 20seconds
    }
   analogWrite(RED, 255);
    delay(5000);//tells you after 20 seconds is up (hold for 5)
    analogWrite(BLUE,0);

    handsCleaned++;
    Serial.println(handsCleaned);
  } 

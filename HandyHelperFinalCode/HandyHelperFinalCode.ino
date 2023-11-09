
 int BLUE=9;      //Blue lead connected to pin9 on microcontoller
 int GREEN=10;    //Green lead connected to pin9 on microcontoller
 int RED=11;      //Red lead connected to pin11 on microcontoller
const int SensPin=A0; //Sensor output lead connected to pinA0 on microcontroller
int handsCleaned =0; //counts the number of sequences
int sensVal=0;      
int initalADC;      //Sensor reading at startup
float initialV;     //startup sensor voltage reading
int proximityADC;   


void setup() {
Serial.begin(57600);
pinMode(RED, OUTPUT);     
pinMode(GREEN, OUTPUT);
pinMode(BLUE, OUTPUT); 
pinMode(SensPin, INPUT);
analogWrite(BLUE,LOW);     //set all pins to LOW for comm (-) and HIGH for comm (+)
analogWrite(GREEN, LOW);
analogWrite(RED, LOW);
initalADC=analogRead(SensPin);             //Get initial sensor reading (value between 0 and 1023)
initialV=(float)proximityADC*5.0/1024.0;   //Convert to voltage
Serial.println(initialV);                  
}

void loop() {
  proximityADC = analogRead(SensPin);           
  float proximityV=(float)proximityADC*5.0/1024.0;
  Serial.println(proximityV);  
  delay(1000);
  
 if(proximityV<4.99){               //Can change this value depending on initialV & IR sensitivity
  Serial.println("Starting");
  startSequence();
 }
 else{
  Serial.println("No motion detected");
 }

}

//sequence follows standard traffic light convention, lasts approximately 27 seconds  
void startSequence(){
  for(int i=0; i<3; i+=1){//blink red 3x for soaping
    analogWrite(RED, 255);
    delay(1000);
    analogWrite(RED, 0);
    delay(500);
  }
  analogWrite(RED, 255);   //Red stays on 
  delay(500);
  
  for(int i=1; i<=20; i+=1){//fade from dark orange to gold
    analogWrite(GREEN, i);
    delay(800);//lasts 20 seconds
  }
  
  analogWrite(RED, 0);   //turn off red
  analogWrite(GREEN, 0); //turn off all light for 1s
  delay(1000);
  
  analogWrite(GREEN, 255); //flash green for 3s
  analogWrite(BLUE, 10);   //makes it a prettier shade
  delay(3000);
  
  analogWrite(GREEN, 0);  //  turn off all colors
  analogWrite(BLUE, 0);
  delay(3000);          //3s delay for last minute rinsing (7s total including green light)
  
  handsCleaned++;
  Serial.println(handsCleaned);
}

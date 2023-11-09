int IRsens=5;
int IRstat=0;
int ledPin=13;

void setup() {
  // put your setup code here, to run once:
  pinMode(IRsens, INPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  IRstat = digitalRead(IRsens);
  unsigned long timer = 0;
  if(IRstat == HIGH){
    timer = millis();
    digitalWrite(ledPin, HIGH);
    Serial.println("motion");
    Serial.println(timer);
    
  }
  else{
    digitalWrite(ledPin, LOW);
    Serial.println("no mo");
  }
 

}

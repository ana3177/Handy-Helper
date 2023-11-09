//lilypad PWM pins are 3,9,10,11,and 13
const int RED = 9;
const int GREEN = 10;
const int BLUE = 11;
void setup() {
  pinMode(RED,OUTPUT);
  pinMode(GREEN,OUTPUT);
  pinMode(BLUE, OUTPUT);
}

void loop() {
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
}

void displayColor(int r, int g, int b){
  analogWrite(RED,255-r);
  analogWrite(GREEN, 255-g);
  analogWrite(BLUE,255-b); 
}

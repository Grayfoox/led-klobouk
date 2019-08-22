#include <Adafruit_NeoPixel.h>

#define PIN 5
#define INTPIN 2
#define ANAPIN A7 
Adafruit_NeoPixel strip = Adafruit_NeoPixel(47, PIN, NEO_GRB + NEO_KHZ800);

int state = 0;
int volState = 0;
int potProm = 0;    // proměnná pro analogovou hodnotu potenciometru
int sire = 0;

void setup() {
  
  pinMode(INTPIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(INTPIN), changeState, RISING);
    Serial.begin(9600);      // open the serial port at 9600 bps:    

  pinMode(ANAPIN, INPUT); //TODO ANALOG INPUT
  pinMode(19,OUTPUT);
  digitalWrite(19, HIGH);


  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void changeState(){
    state += 1;
      Serial.print("switched");       // prints a label

    if(state > 4){
      state=0;

      
    }
}

void getPotColor(){
    potProm = analogRead(ANAPIN);
    potProm = map(potProm, 0, 1023, 0, 255);
}

void loop() {
     getPotColor();

      switch(state){
      case 0:      
      runBack();

      break;

      case 1: utikej();
      break;
     
      case 2:  
      nblink();
      break;

       case 3:  
      strip.setPixelColor(random(0,47),Wheel(random(0,256)));
          strip.show();
          delay(30);
      break;

  case 4:  
      stred();
      break;

        /*case 5:  
    for(int i=0; i< strip.numPixels(); i++) {
       strip.setPixelColor(i, Wheel(((i*7 + potProm))));
    }
    strip.show();
    delay(30+potProm);
    for(int i=0; i< strip.numPixels(); i++) {
       strip.setPixelColor(i,0,0,0);
    }
       strip.show();
    delay(30+potProm);
    
      break;*/
      }

        volState = state;

  }


   void duha1(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
     if(volState != state){
      break;
    }
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}
  
  
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}


  void stred(){
  sire += random(-2,3);
  if(sire < 0){
    sire = 0;
  }

  if(sire > 22){
    sire = 22;
  }

  for(int i=0;i<strip.numPixels();i++){
  strip.setPixelColor(i,strip.Color(0,0,0));
  }
  
  for(int i=0; i<sire; i++) { // 5 cycles of all colors on wheel
       strip.setPixelColor(22 - i, Wheel(((i*7 + potProm))));      
       strip.setPixelColor(23 + i, Wheel(((i*7 + potProm))));
} 
strip.show();
delay(50);
} 
  

  void duha1(int wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
     if(volState != state){
      break;
    }
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

void nblink(){

    for(int j=0;j<strip.numPixels()/7;j++){
        if(volState != state){
      break;
    }
    for(int i=0;i<strip.numPixels();i+=7){
    int pos = i+j;
    if(pos > strip.numPixels()){
      pos = pos - strip.numPixels();
    }
      if(volState != state){
      break;
    }
        strip.setPixelColor(pos-1,  strip.Color(0,0,0));
     strip.show(); 
     delay(50);
     
          getPotColor();
          strip.setPixelColor(pos,  Wheel(potProm));


    
    
    }
    strip.show(); 
     delay(50);
    }
     
  }  


void runBack(){
    for(int i=0;i<strip.numPixels();i++){
      if(volState != state){
      break;
    }
    getPotColor();
    strip.setPixelColor(i,   Wheel(potProm)); 
    strip.setPixelColor(i+1, Wheel(potProm)); 
    strip.setPixelColor(i+2, Wheel(potProm)); 
    strip.setPixelColor(i+3, Wheel(potProm)); 
    strip.setPixelColor(i+4, Wheel(potProm)); 
    strip.setPixelColor(i+5, Wheel(potProm)); 
    strip.setPixelColor(i+6, Wheel(potProm)); 
    strip.show(); 
    delay(50); 
    strip.setPixelColor(i, strip.Color(0,0,0)); 
  }
    for(int i=47;i>0;i--){
        if(volState != state){
      break;
    }
      getPotColor();
    strip.setPixelColor(i,   Wheel(potProm)); 
    strip.setPixelColor(i-1, Wheel(potProm)); 
    strip.setPixelColor(i-2, Wheel(potProm)); 
    strip.setPixelColor(i-3, Wheel(potProm)); 
    strip.setPixelColor(i-4, Wheel(potProm)); 
    strip.setPixelColor(i-5, Wheel(potProm)); 
    strip.setPixelColor(i-6, Wheel(potProm));
    strip.show(); 
    delay(50); 
    strip.setPixelColor(i, strip.Color(0,0,0)); 
   } 
  }


  void utikej() {
  for (int j=0; j<10; j++) {  
     if(volState != state){
      break;
    }
    for (int q=0; q < 3; q++) {
      for (int i=0; i < strip.numPixels(); i=i+3) {
        getPotColor();
        strip.setPixelColor(i+q, Wheel(potProm));    
      }
      strip.show();
     
      delay(40);
     
      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        
      }
    }
  }
  }
  

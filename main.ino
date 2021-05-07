#include <Adafruit_NeoPixel.h>

Adafruit_NeoPixel strip(32,10, NEO_GRB + NEO_KHZ800);


int hours = 6;
int minutes = 33;
int seconds = 0;
int pixels = strip.numPixels();

bool start = true;

void setup() {
  strip.begin();
  strip.setBrightness(55);
  Serial.begin(9600);
}

void loop() {

  
  for(int i = 0; i < 60; i ++){
    seconds = i;
    
    if(seconds == 59){
      minutes ++;
    }
    if(minutes == 60){
      minutes = 0;
      hours ++;
    }
    if(hours == 24){
      hours = 0;
    }
    showPixels();
    delay(1000);
  }
  
}


uint32_t hourPos(float hour, float minute){
  hour = hour + minute/60;
  int pos = 0;
  if(hour <12){
    pos = pixels * hour/12;
  }else{
    hour = hour - 12;
    pos = pixels * hour/12;
  }
  return pos;
}


uint32_t minPos(float minute){
  int pos = pixels * minute/60;
  return pos;
}

uint32_t secPos(float second){
  int pos = pixels * second/60;
  return pos;
}

void showPixels(){
  strip.clear();
  if(start){
    splitStrip(255,255,255,30);
    findPositions(50);
  }

//  strip.setPixelColor(secPos(seconds)-1, 255,0,0);
//  if(secPos(seconds) == 0){
//    strip.setPixelColor(strip.numPixels()-1, 255,0,0);
//  }
  
  if(secPos(seconds) == minPos(minutes) && secPos(seconds) == hourPos(hours, minutes)){
    strip.setPixelColor(hourPos(hours, minutes), 85,85,85);
    
  }else if(secPos(seconds) == minPos(minutes)){
    strip.setPixelColor(hourPos(hours, minutes), 0,0,255);
    strip.setPixelColor(minPos(minutes), 128,128,0);
    
  }else if(secPos(seconds) == hourPos(hours, minutes)){
    strip.setPixelColor(minPos(minutes), 0,255,0);
    strip.setPixelColor(hourPos(hours, minutes), 128,0,128);
    
  }else if(minPos(minutes) == hourPos(hours, minutes)){
    strip.setPixelColor(secPos(seconds), 255,0,0);
    strip.setPixelColor(hourPos(hours, minutes), 0,128,128);
    
  }else {
    strip.setPixelColor(secPos(seconds), 255,0,0);
    strip.setPixelColor(minPos(minutes), 0,255,0);
    strip.setPixelColor(hourPos(hours, minutes), 0,0,255);
  }
  
  
  strip.show();
}




void fillStrip(byte red, byte green, byte blue, int SpeedDelay) {
  strip.clear();
  for(uint16_t i=0; i<=strip.numPixels(); i++) {
      strip.fill(strip.Color(i*red, i*green, i*blue), 0, i);
      strip.show();
      delay(SpeedDelay);
  }
  delay(20*SpeedDelay);
  for(uint16_t i=255; i>0; i--){
    strip.fill(strip.Color(i,i,i));
    strip.show();
    delay(3);
  }
  strip.clear();
  start = false;
}


void splitStrip(byte red, byte green, byte blue, int SpeedDelay){

  for(int i=(strip.numPixels()/2); i>=0; i--){
    strip.setPixelColor(i, strip.Color(red, green, blue));
    strip.setPixelColor(strip.numPixels()-i, strip.Color(red, green, blue));
    strip.show();
    delay(SpeedDelay);
  }
  for(int i=(strip.numPixels()/2); i>=0; i--){
    strip.setPixelColor(i, strip.Color(0,0,0));
    strip.setPixelColor(strip.numPixels()-i, strip.Color(0,0,0));
    strip.show();
    delay(SpeedDelay);
  }
  start = false;
  delay(SpeedDelay*10);
}

void findPos(int SpeedDelay){
  strip.clear();
  int hour = hourPos(hours, minutes);
  int minute = minPos(minutes);
  int second = secPos(seconds);

  
  for(int i = 0; i <= hour; i++){
    strip.setPixelColor(i-1, strip.Color(0,0,0));
    strip.setPixelColor(i, strip.Color(0,0,255));
    strip.show();
    delay(SpeedDelay);
  }

  for(int i = 0; i <= minute; i++){
    if(i == hour + 1){
      strip.setPixelColor(i-1, strip.Color(0,0,255));
      strip.setPixelColor(i, strip.Color(0,255,0)); 
    }else if(i == hour){
      strip.setPixelColor(i-1, strip.Color(0,0,0));
      strip.setPixelColor(i, strip.Color(0,255,255));
    }else{
      strip.setPixelColor(i-1, strip.Color(0,0,0));
      strip.setPixelColor(i, strip.Color(0,255,0));
    }
    strip.show();
    delay(SpeedDelay);
  }

  for(int i = 0; i < second; i++){
    if(i == hour + 1 == minute + 1){
      strip.setPixelColor(i-1, strip.Color(0,255,255));
      strip.setPixelColor(i, strip.Color(255,0,0));
    }else if(i == hour || i == minute){
      strip.setPixelColor(i-1, strip.Color(0,0,0));
    }else{
      strip.setPixelColor(i-1, strip.Color(0,0,0));
      strip.setPixelColor(i, strip.Color(255,0,0));
    }
    strip.show();
    delay(SpeedDelay);
  }
  strip.clear();
  start = false;
}

void findPositions(int SpeedDelay){
  strip.clear();
  int hour = hourPos(hours, minutes);
  int minute = minPos(minutes);
  int second = secPos(seconds);
  bool clockwiseHour;
  bool clockwiseMinute;
  bool clockwiseSecond;

  if(hour <= (pixels/2)){
    clockwiseHour = true;
  }else{
    clockwiseHour = false;
  }
  
  if(minute <= pixels/2){
    clockwiseMinute = true;
  }else{
    clockwiseMinute = false;
  }

  if(second <= pixels/2){
    clockwiseSecond = true;
  }else{
    clockwiseSecond = false;
  }

  if(clockwiseHour){
    for(int i = 0; i <= hour; i++){
      strip.setPixelColor(i-2, strip.Color(0,0,0));
      strip.setPixelColor(i-1, strip.Color(0,0,100));
      strip.setPixelColor(i, strip.Color(0,0,255));
      strip.show();
      delay(SpeedDelay);
    }
  }else{
    for(int i = pixels; i >= hour; i--){
      strip.setPixelColor(i+2, strip.Color(0,0,0));
      strip.setPixelColor(i+1, strip.Color(0,0,100));
      strip.setPixelColor(i, strip.Color(0,0,255));
      strip.show();
      delay(SpeedDelay);
    }
  }
  strip.clear();
  strip.setPixelColor(hour, strip.Color(0,0,255));
  
  if(clockwiseMinute){
    for(int i = 0; i <= minute; i++){
      strip.setPixelColor(i-2, strip.Color(0,0,0));
      strip.setPixelColor(i-1, strip.Color(0,100,0));
      strip.setPixelColor(i, strip.Color(0,255,0));
      strip.setPixelColor(hour, strip.Color(0,0,255));
      strip.show();
      delay(SpeedDelay);
    }
  }else{
    for(int i = pixels; i >= minute; i--){
      strip.setPixelColor(i+2, strip.Color(0,0,0));
      strip.setPixelColor(i+1, strip.Color(0,100,0));
      strip.setPixelColor(i, strip.Color(0,255,0));
      strip.setPixelColor(hour, strip.Color(0,0,255));
      strip.show();
      delay(SpeedDelay);
    }
  }
  strip.clear();
  strip.setPixelColor(hour, strip.Color(0,0,255));
  strip.setPixelColor(minute, strip.Color(0,255,0));

  if(clockwiseSecond){
    for(int i = 0; i <= second; i++){
      strip.setPixelColor(i-2, strip.Color(0,0,0));
      strip.setPixelColor(i-1, strip.Color(100,0,0));
      strip.setPixelColor(i, strip.Color(255,0,0));
      strip.setPixelColor(hour, strip.Color(0,0,255));
      strip.setPixelColor(minute, strip.Color(0,255,0));
      strip.show();
      delay(SpeedDelay);
    }
  }else{
    for(int i = pixels; i >= second; i--){
      strip.setPixelColor(i+2, strip.Color(0,0,0));
      strip.setPixelColor(i+1, strip.Color(100,0,0));
      strip.setPixelColor(i, strip.Color(255,0,0));
      strip.setPixelColor(hour, strip.Color(0,0,255));
      strip.setPixelColor(minute, strip.Color(0,255,0));
      strip.show();
      delay(SpeedDelay);
    }
  }
  
  strip.clear();
  strip.setPixelColor(hour, strip.Color(0,0,255));
  strip.setPixelColor(minute, strip.Color(0,255,0));
  strip.setPixelColor(second, strip.Color(255,0,0));
}

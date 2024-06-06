#include <Adafruit_CircuitPlayground.h>
#include <AsyncDelay.h>

AsyncDelay delay_2s;
AsyncDelay delay_1_5s;
AsyncDelay delay_1s;
AsyncDelay delay_0_5s;
AsyncDelay missileDelay;

int randSelect = 0;

bool switchFlag = false;
bool switchState = false;
bool leftButtonFlag = false;
bool rightButtonFlag = false;

int phase = 0;

int alien1 = -1;
int alien2 = -1;

int missile1 = -1;
int missile2 = -1;

void setup() {
  
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  CircuitPlayground.begin();
  
  delay_2s.start(2000, AsyncDelay::MILLIS);
  delay_1_5s.start(1500, AsyncDelay::MILLIS);
  delay_1s.start(1000, AsyncDelay::MILLIS);
  delay_0_5s.start(500, AsyncDelay::MILLIS);
  missileDelay.start(100, AsyncDelay::MILLIS);

  attachInterrupt(digitalPinToInterrupt(7), switchInterrupt, CHANGE);
  attachInterrupt(digitalPinToInterrupt(4), rightButtonInterrupt, CHANGE);
  attachInterrupt(digitalPinToInterrupt(5), leftButtonInterrupt, CHANGE);

}

void switchInterrupt() {
  switchFlag = true;
}

void rightButtonInterrupt() {
  rightButtonFlag = true;
}

void leftButtonInterrupt() {
  leftButtonFlag = true;
}

void spawnAlien(){

  
  randSelect = random(0,3);
  
  if(randSelect == 1){
    if(alien1 == -1){
      alien1 = 0;
      CircuitPlayground.setPixelColor(alien1, 0, 255, 0); 
    }
  }else if(randSelect == 2){
    if(alien2 == -1){
      alien2 = 9;
      CircuitPlayground.setPixelColor(alien2, 0, 255, 0); 
    }
  }
  
}

void endGame(){
  
}

void restartTimer(){
  if(phase == 0){
    delay_2s.restart();
  }else if(phase == 1){
    delay_1_5s.restart();
  }else if(phase == 2){
    delay_1s.restart();
  }else if(phase == 3){
    delay_0_5s.restart();
  }
}

void moveAliens(){
  if(alien1 != -1 && alien1 < 4){
    alien1++;
    CircuitPlayground.setPixelColor(alien1, 0, 255, 0); 
  }else if(alien1 == 4){
    endGame();
  }
  if(alien2 != -1 && alien2 > 5){
    alien2--;
    CircuitPlayground.setPixelColor(alien2, 0, 255, 0); 
  }else if(alien1 == 5){
    endGame();
  }

  hitCheck();
}

void moveMissiles(){
  if(missile1 != -1 && missile1 > 0){
    CircuitPlayground.setPixelColor(missile1, 0, 0, 0); 
    missile1--;
    CircuitPlayground.setPixelColor(missile1, 255, 255, 255); 
  }else if(missile1 == 0){
    CircuitPlayground.setPixelColor(missile1, 0, 0, 0); 
    missile1 = -1;
  }


  
  if(missile2 != -1 && missile2 < 9){
    CircuitPlayground.setPixelColor(missile2, 0, 0, 0); 
    missile2++;
    CircuitPlayground.setPixelColor(missile2, 255, 255, 255); 
  }else if(missile2 == 9){
    CircuitPlayground.setPixelColor(missile2, 0, 0, 0); 
    missile2 = -1;
  }

  hitCheck();
}

void hitCheck(){
  if(missile1 == alien1){
    missile1 = -1;
    alien1 = -1;
  }

  if(missile2 == alien2){
    missile2 = -1;
    alien2 = -1;
  }
}

void loop() {

  
  if(phase == 0){
    if(delay_2s.isExpired()){
      CircuitPlayground.clearPixels();
      digitalWrite(LED_BUILTIN, HIGH);  
      moveAliens();
      spawnAlien();
      delay_2s.restart();
      delay(25);
      digitalWrite(LED_BUILTIN, LOW);  
    }
  }else if(phase == 1){
    
  }else if(phase == 2){
    
  }else if(phase == 3){
    
  }
  
  if(switchFlag == true){
    if(digitalRead(7) == 0){
      switchState = false;
    }else if(digitalRead(7) == 1){
      switchState = true;
    }
    switchFlag = false;
  }

  if(rightButtonFlag == true){
    if(missile1 == -1){
      missile1 = 4;
      CircuitPlayground.setPixelColor(missile1, 255, 255, 255); 
    }
    rightButtonFlag = false;
  }

  if(leftButtonFlag == true){
    if(missile2 == -1){
      missile2 = 5;
      CircuitPlayground.setPixelColor(missile2, 255, 255, 255); 
    }
    leftButtonFlag = false;
  }


  if(missileDelay.isExpired()){
    moveMissiles();
    Serial.println(missile1);
    Serial.println(missile2);
    missileDelay.restart();
  }












}

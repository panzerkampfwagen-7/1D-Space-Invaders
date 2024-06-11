#include <Adafruit_CircuitPlayground.h>
#include <AsyncDelay.h>

AsyncDelay delay_2s;
AsyncDelay delay_1_5s;
AsyncDelay delay_1s;
AsyncDelay delay_0_5s;
AsyncDelay delay_0_25s;
AsyncDelay missileDelay;

int randSelect = 0;

bool switchFlag = false;
bool switchState = false;
bool leftButtonFlag = false;
bool rightButtonFlag = false;
bool gameOver = false;

int phase = 0;
int alien1 = -1;
int alien2 = -1;
int missile1 = -2;
int missile2 = -2;
int score = 0;
int aliensDestroyed = 0;

float midi[127];
int A_four = 440;

int song[25][2] = {
    {36+24, 200},
    {36+24, 100},
    {41+24, 400},
    {36+24, 100},
    {41+24, 100},
    {45+24, 100},
    {48+24, 100},
    {45+24, 200},
    {41+24, 100},
    {43+24, 200},
    {43+24, 300},
    {38+24, 300},
    {43+24, 100},
    {41+24, 200},
    {40+24, 100},
    {41+24, 400},
    {36+24, 100},
    {41+24, 100},
    {45+24, 100},
    {48+24, 100},
    {45+24, 200},
    {41+24, 100},
    {42+24, 200},
    {42+24, 300},
    {41+24, 1000},
  };

void setup() {
  
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  CircuitPlayground.begin();
  generateMIDI();
  
  delay_2s.start(2000, AsyncDelay::MILLIS);
  delay_1_5s.start(1500, AsyncDelay::MILLIS);
  delay_1s.start(1000, AsyncDelay::MILLIS);
  delay_0_5s.start(500, AsyncDelay::MILLIS);
  delay_0_25s.start(250, AsyncDelay::MILLIS);
  missileDelay.start(100, AsyncDelay::MILLIS);

  attachInterrupt(digitalPinToInterrupt(7), switchInterrupt, CHANGE);
  attachInterrupt(digitalPinToInterrupt(4), rightButtonInterrupt, CHANGE);
  attachInterrupt(digitalPinToInterrupt(5), leftButtonInterrupt, CHANGE);

  playXevious();

}

void generateMIDI() {
  for (int x = 0; x < 127; ++x)
  {
    midi[x] = (A_four / 32.0) * pow(2.0, ((x - 9.0) / 12.0));
  }
}

void playXevious() {
  for(int i = 0; i < sizeof(song) / sizeof(song[0]); i++)
    {
      CircuitPlayground.playTone(midi[song[i][0]], song[i][1]);
      delay(1);
    }
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
  gameOver = true;
  for(int i = 0; i < 10; i++){
    CircuitPlayground.setPixelColor(i, 255, 0, 0);
  }
}

void moveAliens(){
  if(alien1 != -1 && alien1 < 4 && missile1 != alien1 && gameOver == false){
    alien1++;
    CircuitPlayground.setPixelColor(alien1, 0, 255, 0); 
  }else if(alien1 == 4){
    endGame();
  }else if(missile1 == alien1){
    missile1 = -2;
    alien1 = -1;
    CircuitPlayground.setPixelColor(missile1, 0, 0, 0); 
    CircuitPlayground.setPixelColor(alien1, 255, 0, 0); 
    score = score + 5;
    aliensDestroyed++;
  }
  
  if(alien2 != -1 && alien2 > 5 && missile2 != alien2 && gameOver == false){
    alien2--;
    CircuitPlayground.setPixelColor(alien2, 0, 255, 0); 
  }else if(alien2 == 5){
    endGame();
  }else if(missile2 == alien2){
    missile2 = -2;
    alien2 = -1;
    CircuitPlayground.setPixelColor(missile2, 0, 0, 0); 
    CircuitPlayground.setPixelColor(alien2, 255, 0, 0); 
    score = score + 5;
    aliensDestroyed++;
  }

}

void shootMissile(){
  for(int i = 0; i < 5; i++){
    CircuitPlayground.playTone(500-50*i, 4);
    delay(1);
  }
}

void moveMissiles(){

  if(missile1 != -2 && missile1 > 0 && missile1 != alien1){
    CircuitPlayground.setPixelColor(missile1, 0, 0, 0); 
    missile1--;
    CircuitPlayground.setPixelColor(missile1, 255, 255, 255); 
  }else if(missile1 == 0 && missile1 != alien1){
    CircuitPlayground.setPixelColor(missile1, 0, 0, 0); 
    missile1 = -2;
  }else if(missile1 == alien1){
    missile1 = -2;
    alien1 = -1;
    CircuitPlayground.setPixelColor(missile1, 0, 0, 0); 
    CircuitPlayground.setPixelColor(alien1, 0, 0, 0); 
    score = score + 5;
    aliensDestroyed++;
  }

  if(missile2 != -2 && missile2 < 9 && missile2 != alien2){
    CircuitPlayground.setPixelColor(missile2, 0, 0, 0); 
    missile2++;
    CircuitPlayground.setPixelColor(missile2, 255, 255, 255); 
  }else if(missile2 == 9 && missile2 != alien2){
    CircuitPlayground.setPixelColor(missile2, 0, 0, 0); 
    missile2 = -2;
  }else if(missile2 == alien2){
    missile2 = -2;
    alien2 = -1;
    CircuitPlayground.setPixelColor(missile2, 0, 0, 0); 
    CircuitPlayground.setPixelColor(alien2, 0, 0, 0); 
    score = score + 5;
    aliensDestroyed++;
  }

}


void loop() {

  if(gameOver == false){

    if(missile1 == alien1){
      CircuitPlayground.setPixelColor(missile1, 0, 0, 0);
    }
    if(missile2 == alien2){
      CircuitPlayground.setPixelColor(missile2, 0, 0, 0);
    }
  
    
    if(phase == 0){
      if(delay_2s.isExpired()){
        CircuitPlayground.clearPixels();
        digitalWrite(LED_BUILTIN, HIGH);  
        moveAliens();
        spawnAlien();
        delay_2s.restart();
        delay(25);
        digitalWrite(LED_BUILTIN, LOW);  
        score++;
      }
    }else if(phase == 1){
      if(delay_1_5s.isExpired()){
        CircuitPlayground.clearPixels();
        digitalWrite(LED_BUILTIN, HIGH);  
        moveAliens();
        spawnAlien();
        delay_1_5s.restart();
        delay(25);
        digitalWrite(LED_BUILTIN, LOW);  
        score++;
      }  
    }else if(phase == 2){
      if(delay_1s.isExpired()){
        CircuitPlayground.clearPixels();
        digitalWrite(LED_BUILTIN, HIGH);  
        moveAliens();
        spawnAlien();
        delay_1s.restart();
        delay(25);
        digitalWrite(LED_BUILTIN, LOW);  
        score++;
      }    
    }else if(phase == 3){
      if(delay_0_5s.isExpired()){
        CircuitPlayground.clearPixels();
        digitalWrite(LED_BUILTIN, HIGH);  
        moveAliens();
        spawnAlien();
        delay_0_5s.restart();
        delay(25);
        digitalWrite(LED_BUILTIN, LOW);  
        score++;
      }
    }else if(phase == 4){
      if(delay_0_25s.isExpired()){
        CircuitPlayground.clearPixels();
        digitalWrite(LED_BUILTIN, HIGH);  
        moveAliens();
        spawnAlien();
        delay_0_25s.restart();
        delay(25);
        digitalWrite(LED_BUILTIN, LOW);  
        score++;
      }
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
      shootMissile();
      if(missile1 == -2){
        missile1 = 4;
        CircuitPlayground.setPixelColor(missile1, 255, 255, 255); 
      }
      rightButtonFlag = false;
    }
  
    if(leftButtonFlag == true){
      shootMissile();
      if(missile2 == -2){
        missile2 = 5;
        CircuitPlayground.setPixelColor(missile2, 255, 255, 255); 
      }
      leftButtonFlag = false;
    }
  
  
    if(missileDelay.isExpired()){
      moveMissiles();
      //Serial.println(missile1);
      //Serial.println(missile2);
      Serial.print("Score: ");
      Serial.print(score);
      Serial.print("  ||  Phase: ");
      Serial.print(phase);
      Serial.print("  || Aliens Destroyed: ");
      Serial.println(aliensDestroyed);
      missileDelay.restart();
    }

  }

  if(switchFlag){
    if(digitalRead(7) == 1 && gameOver == true){
      playXevious();
      switchFlag = false;
      switchState = false;
      leftButtonFlag = false;
      rightButtonFlag = false;
      
      phase = 0;
      alien1 = -1;
      alien2 = -1;
      missile1 = -2;
      missile2 = -2;
      score = 0;
      aliensDestroyed = 0;
    
      delay_2s.start(2000, AsyncDelay::MILLIS);
      delay_1_5s.start(1500, AsyncDelay::MILLIS);
      delay_1s.start(1000, AsyncDelay::MILLIS);
      delay_0_5s.start(500, AsyncDelay::MILLIS);
      delay_0_25s.start(250, AsyncDelay::MILLIS);
      missileDelay.start(100, AsyncDelay::MILLIS);
      gameOver = false;
    }
  }


  if(score < 25){
    phase = 0;
  }else if(score >= 25 && phase == 0){
    phase = 1;
  }else if(score >= 75 && phase == 1){
    phase = 2;
  }else if(score >= 150 && phase == 2){
    phase = 3;
  }else if(score >= 300 && phase == 3){
    phase = 4;
  }


}

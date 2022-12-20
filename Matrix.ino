
#include <ezButton.h>
#include "LedControl.h"





#define VRX_PIN  A0
#define VRY_PIN  A1 
#define SW_PIN   2  

ezButton button(SW_PIN);
LedControl lc=LedControl(12,10,11,1);

byte Field[8] = {

  B10000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000
};
int LastRow = 0;
int CurrentRow = 1;
int NextRow = 2;

int xValue = 0; 
int yValue = 0; 
int bValue = 0; 

void setup() {
  lc.shutdown(0, false);
  lc.setIntensity(0,0);
  lc.clearDisplay(0);
  Serial.begin(9600) ;
  Serial.print(Field[CurrentRow]);

//Spawn Player
  for (int s=0; s<8; s++){
    lc.setRow(0,s,Field[s]);
  }

  button.setDebounceTime(50); 



}

void shiftRight(){
   Serial.print(Field[0]);
    Serial.print("\t");
    if (Field[0] == 1){
      Field[0] = Field[0] << 6;
      lc.setRow(0,0,Field[0]);
      delay(500);
      
    }
    
    if (Field[0] > 1){
      Field[0] = Field[0] >> 1;
      lc.setRow(0,0,Field[0]);
      delay(500);
    }
}


void shiftLeft(){
    Serial.print(Field[0]);
    Serial.print("\t");
    if (Field[0] == 128){
      Field[0] = Field[0] >> 6;
      lc.setRow(0,0,Field[0]);
      delay(500);
      
    }
    
    if (Field[0] > 1){
      Field[0] = Field[0] << 1;
      lc.setRow(0,0,Field[0]);
      delay(500);
    }
}




void shiftTop() {
  if (0 == CurrentRow){
    Field[CurrentRow] = Field[CurrentRow];
  }

  if (0 < CurrentRow){
    Field[LastRow] = Field[CurrentRow];
    Field[CurrentRow] = 0;
    lc.setrow(0,Field[LastRow],Field[LastRow]);
    Serial.print(Field[CurrentRow && LastRow]);
    LastRow -= 1;
    CurrentRow -= 1;
    delay(500);
  }
}




void shiftBottom(){
  if(7 == CurrentRow){
    Field[CurrentRow] = Field[CurrentRow];

  }

  if (7 > CurrentRow){
    Field[NextRow] = Field[CurrentRow];
    Field[CurrentRow] = 0;

    lc.setRow(0, Field[NextRow] ,Field[CurrentRow]);
    Serial.print(Field[CurrentRow && NextRow]);
    delay(500);
    CurrentRow += 1;
    NextRow += 1;
  }

}



void loop() {
  button.loop(); 

  xValue = analogRead(VRX_PIN);
  yValue = analogRead(VRY_PIN);

  bValue = button.getState();

  if (button.isPressed()) {
    Serial.println("The button is pressed");
  }

  if (button.isReleased()) {
    Serial.println("The button is released");
  }

  //RIGHT
  if (1000 <= xValue && 500 <= yValue){
    shiftRight();

  }


  //LEFT
  if(40 >= xValue && 520 >= yValue){
    shiftLeft();
  }


  //TOP
  if(510 >= xValue && 15 >= yValue){
    shiftTop();
  }
  

  //BOTTOM
  if (510 <= xValue && 1005 <= yValue){
    shiftBottom();
  }


  // Serial.print("x = ");
  // Serial.print(xValue);
  // Serial.print(", y = ");
  // Serial.print(yValue);
  // Serial.print(" : button = ");
  // Serial.println(bValue);


}

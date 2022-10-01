#include <Adafruit_NeoPixel.h>
#include "Queue.h"
#include "Light.h"
#include "SectionController.h"

#define PIN 6
#define NUM_LEDS 130
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);
SectionController section_4_UP_P = SectionController(strip,0,4,true);
SectionController section_4_DOWN_P = SectionController(strip,4,8,true);

SectionController section_8_UP_P = SectionController(strip,8,16,true);
SectionController section_8_DOWN_P = SectionController(strip,16,24,true);


SectionController section_33_UP_B = SectionController(strip,96,130,false);
SectionController section_8_UP_T = SectionController(strip,89,96,false);
SectionController section_8_DOWN_T = SectionController(strip,81,89,true);
SectionController section_33_DOWN_B = SectionController(strip,48,81,true);


SectionController section_4_UP_L = SectionController(strip,24,28,true);
SectionController section_4_DOWN_L = SectionController(strip,28,32,true);

SectionController section_8_UP_L = SectionController(strip,32,40,true);
SectionController section_8_DOWN_L = SectionController(strip,40,48,true);
int indexs[5] = { random(41),random(41),random(41),random(41),random(41) };
int indexs_currsor[5] = { 3,1,5,2,4};
int index=0;

// [][][][] <= 4_UP_L
// [][][][][][][][] <= 8_UP_L
// [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][] <= 33_UP_B [][][][][][][][] <= 8_UP_T
// [][][][][][][][] <= 8_UP_P
// [][][][] <= 4_UP_P


// [][][][] <= 4_DOWN_L
// [][][][][][][][] <= 8_DOWN_L
// [][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][][] <= 33_DOWN_B [][][][][][][][] <= 8_DOWN_T
// [][][][][][][][] <= 8_DOWN_P
// [][][][] <= 4_DOWN_P

//#####################Switch Program############################

int buttonPin = 4;
int programState = 0;
int buttonState = 0;
int delayTime = 30;

queue<Light> Lights;
void setup() {  
  strip.begin();
  strip.show(); 
  for(int i = 0; i< 10; i++){
    Lights.push(Light(
  }
}

void loop() {  
  Animation();
  delay(delayTime);  
}

void Animation()
{
  
  SetAll(0,0,0);

  for(int i=0;i < 5; i++){
    if(indexs[i] >= 0 && indexs[i] <= 4){
      switch(indexs_currsor[i])
      {
        case 1:  
          section_4_UP_P.setPixel(indexs[i],0,0,255);
          break;
        case 2:  
          section_8_UP_P.setPixel(indexs[i],0,0,255);
          break;
        case 3:  
          section_33_UP_B.setPixel(indexs[i],0,0,255);
          break;
        case 4:
          section_8_UP_L.setPixel(indexs[i],0,0,255);
          break;
        case 5:
          section_4_UP_L.setPixel(indexs[i],0,0,255);
          break;
      }    
    }
    if(indexs[i] >= 4 && indexs[i] <= 8) { 
      switch(indexs_currsor[i])
      {
        case 1:
        case 2:
          section_8_UP_P.setPixel(indexs[i],0,0,255);
          break;
        case 3:
          section_33_UP_B.setPixel(indexs[i],0,0,255);
          break;
        case 4:
        case 5:
          section_8_UP_L.setPixel(indexs[i],0,0,255);
          break;
      }     
    }
    if(indexs[i] >= 8 && indexs[i] <= 33 )
    {
      section_33_UP_B.setPixel(indexs[i],0,0,255);  
    }
    if(indexs[i] >= 33){
      section_8_UP_T.setPixel(indexs[i],0,0,255);  
    }
    
    indexs[i] = indexs[i] + 1;
    if(indexs[i] > 41){
      indexs[i] = 0;
    }
  }  
  section_8_UP_T.showStrip();
  section_4_UP_P.showStrip();  
  delay(30);  
}

void SetAll(int r, int g,int b){
  section_4_UP_P.setAll(r,g,b);
  section_8_UP_P.setAll(r,g,b);
  section_33_UP_B.setAll(r,g,b);
  section_8_UP_T.setAll(r,g,b);
  section_8_UP_L.setAll(r,g,b);
  section_4_UP_L.setAll(r,g,b);
  
  section_4_DOWN_P.setAll(r,g,b);
  section_8_DOWN_P.setAll(r,g,b);
  section_33_DOWN_B.setAll(r,g,b);
  section_8_DOWN_T.setAll(r,g,b);
  section_8_DOWN_L.setAll(r,g,b);
  section_4_DOWN_L.setAll(r,g,b);  
}

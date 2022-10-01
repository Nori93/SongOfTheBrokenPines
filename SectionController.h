#include <Adafruit_NeoPixel.h>
class SectionController{
private:
  Adafruit_NeoPixel STRIP;
  int START_LED;
  int END_LED;
  bool ASCENFING_ORDER;
  int SEC_LED_NUM;
  void setPixelColdColor (int Pixel, byte temperature)  {
     // Scale 'heat' down from 0-255 to 0-191
    byte t192 = round((temperature/255.0)*191);
   
    // calculate ramp up from
    byte heatramp = t192 & 0x3F; // 0..63
    heatramp <<= 2; // scale up to 0..252
   
    // figure out which third of the spectrum we're in:
    if( t192 > 0x80) {                     // hottest
      setPixel(Pixel, heatramp, 255, 255 );
    } else if( t192 > 0x40 ) {             // middle
      setPixel(Pixel, 0, heatramp, 255);
    } else {                               // coolest
      setPixel(Pixel, 0, 0, heatramp);
    }
  }
  

public:
  SectionController(Adafruit_NeoPixel strip,int startLed,int endLed,bool ascendingOrder){
    this->STRIP = strip;
    this->START_LED = startLed;
    this->END_LED = endLed;
    this->ASCENFING_ORDER = ascendingOrder;
    this->SEC_LED_NUM = END_LED - START_LED;     
  }
  
  void RunFireAnimation(int cooling, int sparking){
    byte heat[SEC_LED_NUM];
    int cooldown;
   
    // Step 1.  Cool down every cell a little
    for( int i = 0; i < SEC_LED_NUM; i++) {
      cooldown = random(0, ((cooling * 10) / SEC_LED_NUM) + 2);
     
      if(cooldown>heat[i]) {
        heat[i]=0;
      } else {
        heat[i]=heat[i]-cooldown;
      }
    }
   
    // Step 2.  Heat from each cell drifts 'up' and diffuses a little
    for( int k= SEC_LED_NUM - 1; k >= 2; k--) {
      heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2]) / 3;
    }
     
    // Step 3.  Randomly ignite new 'sparks' near the bottom
    if( random(255) < sparking ) {
      int y = random(7);
      heat[y] = heat[y] + random(160,255);   
    }
  
    // Step 4.  Convert heat to LED colors
    for( int j = 0; j < SEC_LED_NUM; j++) {    
      setPixelColdColor( j, heat[j] );
    }
  }
  void showStrip() {
   #ifdef ADAFRUIT_NEOPIXEL_H
     // NeoPixel
     STRIP.show();
   #endif
   #ifndef ADAFRUIT_NEOPIXEL_H
     // FastLED
     FastLED.show();
   #endif
  }

  
  void setAll(byte red, byte green, byte blue) {
    for(int i = 0; i < SEC_LED_NUM; i++ ) {
      setPixel(i, red, green, blue);
    }   
  }

  void meteorRain(byte red, byte green, byte blue, byte meteorSize, byte meteorTrailDecay, boolean meteorRandomDecay) {  
    setAll(0,0,0);
   
    for(int i = 0; i < SEC_LED_NUM+SEC_LED_NUM; i++) {
      // fade brightness all LEDs one step
      for(int j=0; j<SEC_LED_NUM; j++) {
        if( (!meteorRandomDecay) || (random(10)>5) ) {
          fadeToBlack(j, meteorTrailDecay );        
        }
      }
     
      // draw meteor
      for(int j = 0; j < meteorSize; j++) {
        if( ( i-j <SEC_LED_NUM) && (i-j>=0) ) {
          setPixel(i-j, red, green, blue);
        }
      }   
    }
  }

  void fadeToBlack(int pixel, byte fadeValue) {
   int ledNo = getSectionPixel(pixel);
   #ifdef ADAFRUIT_NEOPIXEL_H
      // NeoPixel
      uint32_t oldColor;
      uint8_t r, g, b;
      int value;
     
      oldColor = STRIP.getPixelColor(ledNo);
      r = (oldColor & 0x00ff0000UL) >> 16;
      g = (oldColor & 0x0000ff00UL) >> 8;
      b = (oldColor & 0x000000ffUL);
  
      r=(r<=10)? 0 : (int) r-(r*fadeValue/256);
      g=(g<=10)? 0 : (int) g-(g*fadeValue/256);
      b=(b<=10)? 0 : (int) b-(b*fadeValue/256);
     
      STRIP.setPixelColor(ledNo, r,g,b);
   #endif
   #ifndef ADAFRUIT_NEOPIXEL_H
     // FastLED
     leds[ledNo].fadeToBlackBy( fadeValue );
   #endif  
  }

  void setPixel(int Pixel, byte red, byte green, byte blue){
   int strip_Pixel = getSectionPixel(Pixel);
  {
     #ifdef ADAFRUIT_NEOPIXEL_H
       // NeoPixel
       STRIP.setPixelColor(strip_Pixel, STRIP.Color(red, green, blue));
     #endif
     #ifndef ADAFRUIT_NEOPIXEL_H
       // FastLED
       leds[strip_Pixel].r = red;
       leds[strip_Pixel].g = green;
       leds[strip_Pixel].b = blue;
     #endif
   }
  }

  int getSectionPixel(int Pixel){
    if(ASCENFING_ORDER)
    {
      return Pixel + START_LED;
    }
    else
    {      
      return END_LED - Pixel;
    }
  }  
  
};

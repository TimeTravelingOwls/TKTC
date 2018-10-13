/**************************************************************************/
/*
  NeoPixel_Wand: displays fancy NeoPixel effects for wand props
  by TimeTravelingOwls/burkmurray for TKTC
  
  v1.2 1/10/17 - NeoPixel 15 strip, trigger button, 2-position spell-select switch
  
  This version is for Harry and Ron, who each have one specific spell to perform 
  (switch in up position, unconnected) and a bunch of random fight spells (switch
  in down position, connected)

  Based on Adafruit's strandtest and GemmaButtonCycler code.

    ----> https://www.adafruit.com/
    
    Adafruit invests time and resources providing this open source code,
    please support Adafruit and open-source hardware by purchasing
    products from Adafruit!

*/
/**************************************************************************/


#include <Adafruit_NeoPixel.h>

#define BUTTON_PIN   2    // Digital IO pin connected to the button.  This will be
                          // driven with a pull-up resistor so the switch should
                          // pull the pin to ground momentarily.  On a high -> low
                          // transition the button press logic will execute.

#define SWITCH_PIN   1    // Digital IO pin connected to the switch.  This will be
                          // driven with a pull-up resistor so the switch should
                          // pull the pin to ground.  Based on switch state, 
                          // different spells will execute.
#define NEOPIXEL_PIN 0
#define PIXEL_COUNT 25

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);

bool oldState = HIGH;
int showType = 0;
int defaultBright = 85; // 1/3 brightness

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(SWITCH_PIN, INPUT_PULLUP);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  strip.setBrightness(defaultBright); // defined above

}

void loop() {

  strip.setBrightness(defaultBright); // reset brightness to default
  // Get current button state.
  bool newState = digitalRead(BUTTON_PIN);
  
  // Check if state changed from high to low (button press).
  if (newState == LOW && oldState == HIGH) {
    // Short delay to debounce button.
    delay(20);
    // Check if button is still low after debounce.
    newState = digitalRead(BUTTON_PIN);
//    if (newState == LOW && digitalRead(SWITCH_PIN) == LOW) {
      if (newState == LOW) {    
    // Button pressed, switch is down  
    // So run random spells
      showType++;
      if (showType > 5)
        showType=0;
      startShow(showType);
//      colorWipe(strip.Color(0, 0, 0), 50);
      strip.setBrightness(defaultBright); // reset brightness to default
    }
  // Otherwise (switch is up), run main spell
//  else {
//  colorWipe(strip.Color(250, 250, 0), 25);  // Yellow
//  delay(250);
//  colorWipe(strip.Color(0, 0, 0), 0);
//    }
  }

  // Set the last button state to the old state.
  oldState = newState;
}

void startShow(int i) {
//  If you modify the number of cases, don't forget to mod the switch statement above!

  switch(i){
    case 0: colorWipe(strip.Color(0, 0, 0), 50);    // Black/off
            break;
    case 1: colorWipe(strip.Color(250, 0, 0), 50);  // Red - Full Bloom
            break;
    case 2: for(uint16_t j=7; j<14; j++) {
                strip.setPixelColor(j,0, 0, 0);  // Black/off
                strip.show();
            }
            break;
    case 3: for(uint16_t j=0; j<7; j++) {
                strip.setPixelColor(j,0, 0, 0);  // Black/off
                strip.show();
            }
            break;
    case 4: for(uint16_t j=14; j<19; j++) {
                strip.setPixelColor(j,0, 0, 0);  // Black/off
                strip.show();
            }
            break;
    case 5: colorWipe(strip.Color(250, 0, 0), 50);  // Red
            delay(250);            
            strip.setBrightness(255); 
            strip.show();
            delay(500);
            strip.setBrightness(128); 
            strip.show();
            delay(500);
            strip.setBrightness(255); 
            strip.show();
            delay(500);            
            break;
  }
}


//  Lumos! Fade lights up to maxBright, bounce back, dim to black
void lumos(uint8_t maxBright) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i,255, 255, 64);  // Yellowish white
//      strip.show();
//      delay(wait);
  }

  for(uint16_t b=1; b<maxBright; b++) {
    strip.setBrightness(b); 
    strip.show();
    delay(10);
  }

    strip.setBrightness(maxBright - 25); 
    strip.show();
    delay(1000);

    for(uint16_t d=maxBright; d>=1; d--) {
    strip.setBrightness(d); 
    strip.show();
    delay(10);
  }
    strip.setBrightness(0); 
    strip.show();
}

//  Petrificus Totalus! Fill the dots one after the other with a color, 
//  fading lights up to maxBright, wipe all but last 5 pixels, pause, blink out the rest. 

void spell(uint32_t c, uint8_t maxBright) {
    strip.setBrightness(32); 
    colorWipe(c, 25);
    delay(250);   //pause for effect
    strip.setBrightness(maxBright); 
    colorWipe(c, 25);
    
//colorWipe modified to darken all but last 5 pixels
  for(uint16_t i=0; i<(strip.numPixels() - 5); i++) { 
      strip.setPixelColor(i, strip.Color(0, 0, 0));
      strip.show();
      delay(10);
  }
  delay(200);   //pause for effect
  strip.setBrightness(32); 
  strip.show();
  delay(200);   //pause for effect
           
//colorWipe modified to darken only last 5 pixels
  for(uint16_t i=(strip.numPixels() - 5); i<strip.numPixels(); i++) { 
      strip.setPixelColor(i, strip.Color(0, 0, 0));
      strip.show();
      delay(10);
  }
}


// Update to specify # of sparks
// Single-Color Sparkles!
void oneColorSparks(uint32_t c, uint8_t wait) {

  for(uint16_t i=0; i< 5*(strip.numPixels()); i++) {
    
    uint8_t  p = random(strip.numPixels());
  
    strip.setPixelColor(p, c);
    strip.show();
    delay(10);
    strip.setPixelColor(p, 0);
    delay(wait);
  }
  strip.show(); // Initialize all pixels to 'off'

}


// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
}


//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip.show();
     
      delay(wait);
     
      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
  colorWipe(strip.Color(0, 0, 0), 0);
}

/* Some other colors
  colorWipe(strip.Color(219,112,147), 50); // pink
  colorWipe(strip.Color(135,206,255), 50); // skyBlue
  colorWipe(strip.Color(128,158,10), 50); // maize
  colorWipe(strip.Color(88,2,163), 50); // lavender
  colorWipe(strip.Color(32,178,170), 50); // seaFoam
  colorWipe(strip.Color(102,205,0), 50); // spring
  colorWipe(strip.Color(237,120,6), 50); // orange
*/

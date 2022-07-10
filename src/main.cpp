#include <Arduino.h>
#include <OctoWS2811.h>
#define USE_OCTOWS2811
#include <FastLED.h>


#define RED    0xFF0000
#define GREEN  0x00FF00
#define BLUE   0x0000FF
#define PURPLE 0xFF00FF
#define YELLOW 0xFFFF00
#define AQUA   0x00FFFF
#define PINK   0xFF1088
#define ORANGE 0xE05800
#define WHITE  0xFFFFFF

struct Point {
  float x;
  float y;
  float z;  
};

struct Pixel {
  float x;
  float y;
  float z;
  unsigned int u;
  unsigned int v;
  CRGB *led;
};


const int numLeds= 400; // leds total

const float phi  = 1.618; // golden ratio

const int ledsPerStrip = numLeds/8;
const int pixelsPerSegment = 45;
const int segments = 5;
const int surfacePixels = pixelsPerSegment*segments;
const int freq = 3; // subdivisions per side on each face

Pixel polyhedronFaces[20*(freq^2)];
float polyhedronPoints[12];

CRGB leds[numLeds]; // 
Pixel pixels[surfacePixels];

int trianglesPerFace(int freq){
 return freq * freq;
}

int pointsPerFace(int freq){
  return ((freq+1) * (freq + 2))/2; 
}


void setup() {
  Serial.begin(9600);
  Serial.println("Creating pixel map");
  LEDS.addLeds<OCTOWS2811,RGB>(leds,ledsPerStrip);
  LEDS.setBrightness(60);

  for(int i=0; i< 20*(freq^2);i++){
   }
  for(int segmentIdx=0; segmentIdx<segments; segmentIdx++){
    for(int pixelPositionInSegment=0; pixelPositionInSegment<pixelsPerSegment; pixelPositionInSegment++){
      pixels[(pixelsPerSegment * segmentIdx) + pixelPositionInSegment].led = &leds[(ledsPerStrip * segmentIdx) + pixelPositionInSegment];  
    }
  }
}

//int getRow(){}
//int getCol(){}

void loop() {
    int microsec = 6000000 / numLeds;
for (int offset = 0; offset < 255; offset++){
  for(float i=0; i< pixelsPerSegment; i++){
    float rowPos = ceil(sqrt(2*i+.25)-.5);
    int row = ceil(rowPos);
    Serial.println(row);
  }
}

  //colorWipe(RED, microsec);
  //colorWipe(GREEN, microsec);
  //colorWipe(BLUE, microsec);
  //colorWipe(PURPLE, microsec);
  //colorWipe(YELLOW, microsec);
  //colorWipe(AQUA, microsec);
  //colorWipe(PINK, microsec);
  //colorWipe(ORANGE, microsec);
  //colorWipe(WHITE, microsec);
}

void colorWipe(int color, int wait)
{
  for(int i=0; i<surfacePixels; i++){
    *pixels[i].led = color;
    FastLED.show();
    delayMicroseconds(wait);        
  }
 
}

void colorTest(){
  for(int i=0; i<400; i++){
    if(i<50){
      leds[i]=ORANGE;
    }
    else if(i<100){
      leds[i] = BLUE;
      }
    else if(i<150){
      leds[i] = GREEN;
    }
    else if(i<200){
      leds[i] = RED;
      }
    else if(i<250){
      leds[i] = PURPLE;
    }
    else if(i<300){
      leds[i] = YELLOW;
    }
    else if(i<350){
      leds[i] = AQUA;
    }
    else{
      leds[i] = PINK;
    }
    //*pixels[i].led = color;
    FastLED.show();
  }

}

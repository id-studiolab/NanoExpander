// NANO expander test program.
// for testing HV1.1
// 20200409MCH

#define RED 11
#define GRN 12
#define BLU 13

//#include "libs/Adafruit_NeoPixel/Adafruit_NeoPixel.h"
#include <Adafruit_NeoPixel.h>

#define LED_PIN    8

#define LED_COUNT 10

// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
// Argument 1 = Number of pixels in NeoPixel strip
// Argument 2 = Arduino pin number (most are valid)
// Argument 3 = Pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)

#include "libs/MAX17048/MAX17048.h" 

MAX17048 pwr_mgmt;

void setup() {

  pinMode( 11, OUTPUT );
  pinMode( 12, OUTPUT );
  pinMode( 13, OUTPUT );

  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);
  
  Serial.begin(9600);
  while(!Serial){}
  
  Serial.println("test program for NANO epander board");
  Serial.println("hardware version 1.1");
  Serial.println("...");
  delay(2000);
  
  Serial.println("status LED testing");
  Serial.println("...");
  delay(2000);
  
  Serial.print("RED (D11) blinking");
  blinkLED(RED);
  Serial.println("");
  Serial.print("GREEN (D12) blinking");
  blinkLED(GRN);
  Serial.println("");
  Serial.print("BLUE (D13) blinking");
  blinkLED(BLU);
  Serial.println("");

  Serial.println("...");

  delay(2000);
  Wire.begin();
  pwr_mgmt.attatch(Wire);
  Serial.println("fuel gauge testing");
  Serial.println("...");
  delay(2000);
  Serial.print("VCELL ADC : ");
  Serial.println(pwr_mgmt.adc());
  Serial.print("VCELL V   : ");
  Serial.println(pwr_mgmt.voltage());
  Serial.print("VCELL SOC : ");
  Serial.print(pwr_mgmt.percent());
  Serial.println(" \%");
  Serial.print("VCELL SOC : ");
  Serial.print(pwr_mgmt.accuratePercent());
  Serial.println(" \%");
 
  Serial.println("...");
  delay(2000);

  Serial1.begin(9600);
  Serial.println("printing \"Hello, world!\" to Serial1");
  delay(1000);
  Serial1.println("Hello, world!");
  delay(1000);
  Serial1.println("Hello, world!");
  delay(1000);
  Serial.println("...");
  delay(1000);  
  Serial.println("neopixel strandtest");
  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(50); // Set BRIGHTNESS to about 1/5 (max = 255)
  
  colorWipe(strip.Color(255,   0,   0), 50); // Red
  colorWipe(strip.Color(  0, 255,   0), 50); // Green
  colorWipe(strip.Color(  0,   0, 255), 50); // Blue

  Serial.println("...");
  delay(2000);
  
  Serial.println("input testing");
  Serial.println("digital inputs have pullup");
  Serial.println("D2 LOW to continue");
  Serial.println("[D2][D3][D4][D5][D6][D7] [A0] [A2] [A4] [A6]");
  delay(3000);
  Serial.println("...");
  readPorts();
  Serial.println("...");

  
  
  
  
}

void readPorts(){
 
  
  //while(! digitalRead(2) ){
    while(1){
    for(int i = 2; i < 8; i++){
      Serial.print(digitalRead(i));
    }
    Serial.print(" ");
    Serial.print(analogRead(A0));
    Serial.print(" ");
    Serial.print(analogRead(A2));
    Serial.print(" ");
    Serial.print(analogRead(A4));
    Serial.print(" ");
    Serial.print(analogRead(A6));
    
    Serial.println("");
    
    if(digitalRead(2) ==  0 ){
      break;
    }
    delay(200);
    
  }
   
}

void blinkLED( uint8_t LED ){
  for(int i = 2; i>0; i--){
    digitalWrite( LED, HIGH );
    Serial.print(".");
    delay(500);
    digitalWrite( LED, LOW );
    Serial.print(".");
    delay(500);
  }
}

void colorWipe(uint32_t color, int wait) {
  for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
    strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    strip.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
  }
}
    
void loop() {

  
  // put your main code here, to run repeatedly:

}

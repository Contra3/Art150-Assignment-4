// Bluetooth Settings
#include <PS4BT.h>
#include <usbhub.h>
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
#include <SPI.h>
USB Usb;
//USBHub Hub1(&Usb); // Some dongles have a hub inside
BTD Btd(&Usb); // You have to create the Bluetooth Dongle instance like so
PS4BT PS4(&Btd, PAIR);
//End Bluetooth Settings

// NeoPixels Settings
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#define PIN            6
#define NUMPIXELS      60
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
//End NeoPixels Settings

bool printAngle, printTouch;
uint8_t oldL2Value, oldR2Value;

int delayval = 5; // delay for half a second
int RedLight;
int BlueLight;
int GreenLight;
int brightVal = 100;

  volatile bool flag = true;
#define FREQ_MAX 400
#define RNGSEED 5

const double amplitude = 100.0;
uint32_t spot = 0;

int w_red,p_red,w_green,p_green,w_blue,p_blue;



void setup() {
  Serial.begin(115200);
#if !defined(__MIPSEL__)
  while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
#endif
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1); // Halt
  }
  Serial.print(F("\r\nPS4 Bluetooth Library Started"));
  
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  // End of trinket special code
  
   pixels.begin(); // This initializes the NeoPixel library.
   pixels.setBrightness(brightVal);
   randomSeed(RNGSEED);
   w_red = random(FREQ_MAX);
   p_red = random();
   w_green = random(FREQ_MAX);
   p_green = random();
   w_blue = random(FREQ_MAX);
   p_blue = random();
}

void beginLights(){

    for(int i=0;i<NUMPIXELS;i+=2){
      RedLight = random(0,255);
      BlueLight = random(0,255);
      GreenLight = random(0,255);
      pixels.setPixelColor(i, pixels.Color(RedLight,GreenLight,BlueLight)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      delay(10); // Delay for a period of time (in milliseconds).
    }
    
    for(int i=1;i<NUMPIXELS;i+=2){
        RedLight = random(0,255);
        BlueLight = random(0,255);
        GreenLight = random(0,255);
        // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
        pixels.setPixelColor(i, pixels.Color(RedLight,GreenLight,BlueLight)); // Moderately bright green color.
        pixels.show(); // This sends the updated pixel color to the hardware.
        delay(10); // Delay for a period of time (in milliseconds).
    }

  
}

void changeBrightness(int brightness){
  brightVal += brightness;

  if(brightVal > 250 || brightVal < 25){
    return;
  }
  else{
      pixels.setBrightness(brightVal);
      pixels.show();
  }
  
}

void colorCircle(){
  for(int i=0;i<NUMPIXELS;i++){
    pixels.setPixelColor(i, pixels.Color(255,0,0)); // Moderately bright green color.
    pixels.show(); // This sends the updated pixel color to the hardware.
   }
}

void colorTriangle(){
    for(int i=0;i<NUMPIXELS;i++){  
      pixels.setPixelColor(i, pixels.Color(0,255,0)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
    }
}

void colorSquare(){
    for(int i=0;i<NUMPIXELS;i++){
    pixels.setPixelColor(i, pixels.Color(244, 22, 170)); // Moderately bright green color.
    pixels.show(); // This sends the updated pixel color to the hardware.
    }
}

void colorX(){
    for(int i=0;i<NUMPIXELS;i++){
      pixels.setPixelColor(i, pixels.Color(0,0,255)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
    }
}

void flashRed(){
 
    for(int i = 0; i < NUMPIXELS; i++){
      pixels.setPixelColor(i, pixels.Color(255, 0, 0));
    }
      pixels.setBrightness(10);
      pixels.show();
      delay(500);
      pixels.setBrightness(100);
      pixels.show();
      delay(500);
  
}

void flashGreen(){ 
    for(int i = 0; i < NUMPIXELS; i++){
      pixels.setPixelColor(i, pixels.Color(0, 255, 0));
    }
      pixels.setBrightness(10);
      pixels.show();
      delay(500);
      pixels.setBrightness(100);
      pixels.show();
      delay(500);

   
}

void colorFlow(){
  
    for(int i=0;i<NUMPIXELS;i++){
        BlueLight = random(0,255);
        GreenLight = random(0,255);
      pixels.setPixelColor(i,
        pixels.Color(
          (amplitude - 1)*sin((double)w_red*(double)(spot+i)/1800.0 + (double)p_red) + amplitude, 145, 15)
        );    
    }
    pixels.show();
    spot++;
  
}

void colorFlowBluePurple(){
   const double amplitudeTwo = 75.0;
        for(int i=0;i<NUMPIXELS;i++){
          pixels.setPixelColor(i,
            pixels.Color(
              (amplitudeTwo - 1)*sin((double)w_red*(double)(spot+i)/900.0 + (double)p_red) + amplitudeTwo, 0, 200));
        }
        pixels.show();
        spot++;
  
}

void fadeInAndOut(byte red, byte green, byte blue){
  float r, g, b; 
    for(int k = 0; k < 256; k=k+1) { 
      r = (k/256.0)*red;
      g = (k/256.0)*green;
      b = (k/256.0)*blue;
      
      for(int i = 0; i < NUMPIXELS; i++ ) {
        pixels.setPixelColor(i, r, g, b); 
      }
      
      pixels.show();
    }
       
    for(int k = 255; k >= 0; k=k-2) {
      r = (k/256.0)*red;
      g = (k/256.0)*green;
      b = (k/256.0)*blue;;
      
      for(int i = 0; i < NUMPIXELS; i++ ) {
        pixels.setPixelColor(i, r, g, b); 
      }
      pixels.show();
    }
  
}


void loop() {
  
  Usb.Task();

  if (PS4.connected()) {
    
    if (PS4.getButtonClick(PS)) {
      PS4.disconnect();
    }
    else {
      if (PS4.getButtonClick(TRIANGLE)) {
        colorTriangle();
        PS4.setLed(Green);
      }
      if (PS4.getButtonClick(CIRCLE)) {     
        colorCircle();
        PS4.setLed(Red);
      }
      if (PS4.getButtonClick(CROSS)) {
        colorX();
        PS4.setLed(Blue);
      }
      if (PS4.getButtonClick(SQUARE)) {
        colorSquare();
        PS4.setLed(244, 22, 170);
      }

      if (PS4.getButtonClick(UP)) {changeBrightness(25);} 
      if (PS4.getButtonClick(DOWN)) {changeBrightness(-25);}    
      
      if (PS4.getButtonPress(L1)){colorFlow();}
      if (PS4.getButtonPress(L2)){colorFlowBluePurple();}
      if (PS4.getButtonPress(R1)){flashRed();}
      if (PS4.getButtonPress(R2)){flashGreen();}

      if (PS4.getButtonPress(SHARE)){beginLights();}
      if (PS4.getButtonPress(OPTIONS)) {fadeInAndOut(0xff, 0x77, 0x00);}

      
    }
  }
}

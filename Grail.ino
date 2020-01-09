#include "Arduino.h"
#include <Adafruit_NeoPixel.h>
#include <SoftwareSerial.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif


#define PIXEL_PIN    12    // Digital IO pin connected to the NeoPixels.

#define PIXEL_COUNT 144
#define ARDUINO_RX A3//should connect to TX of the Serial MP3 Player module
#define ARDUINO_TX A2//connect to RX of the module
SoftwareSerial mySerial(ARDUINO_RX, ARDUINO_TX);//init the serial protocol, tell to myserial wich pins are TX and RX
static int8_t Send_buf[8] = {0} ;//The MP3 player undestands orders in a 8 int string
                                 //0X7E FF 06 command 00 00 00 EF;(if command =01 next song order) 
#define NEXT_SONG 0X01 
#define PREV_SONG 0X02 

#define CMD_PLAY_W_INDEX 0X03 //DATA IS REQUIRED (number of song)

#define VOLUME_UP_ONE 0X04
#define VOLUME_DOWN_ONE 0X05
#define CMD_SET_VOLUME 0X1E //DATA IS REQUIRED (number of volume from 0 up to 30(0x1E))
#define SET_DAC 0X17
#define CMD_PLAY_WITHVOLUME 0X22 //data is needed  0x7E 06 22 00 xx yy EF;(xx volume)(yy number of song)

#define CMD_SEL_DEV 0X09 //SELECT STORAGE DEVICE, DATA IS REQUIRED
                #define DEV_TF 0X02 //HELLO,IM THE DATA REQUIRED
                
#define SLEEP_MODE_START 0X0A
#define SLEEP_MODE_WAKEUP 0X0B

#define CMD_RESET 0X0C//CHIP RESET
#define CMD_PLAY 0X0D //RESUME PLAYBACK
#define CMD_PAUSE 0X0E //PLAYBACK IS PAUSED

#define CMD_PLAY_WITHFOLDER 0X0F//DATA IS NEEDED, 0x7E 06 0F 00 01 02 EF;(play the song with the directory \01\002xxxxxx.mp3

#define STOP_PLAY 0X16

#define PLAY_FOLDER 0X17// data is needed 0x7E 06 17 00 01 XX EF;(play the 01 folder)(value xx we dont care)

#define SET_CYCLEPLAY 0X19//data is needed 00 start; 01 close

#define SET_DAC 0X17//data is needed 00 start DAC OUTPUT;01 DAC no output

void printDetail(uint8_t type, int value);

// Parameter 1 = number of pixels in strip,  neopixel stick has 8
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_RGB     Pixels are wired for RGB bitstream
//   NEO_GRB     Pixels are wired for GRB bitstream, correct for neopixel stick
//   NEO_KHZ400  400 KHz bitstream (e.g. FLORA pixels)
//   NEO_KHZ800  800 KHz bitstream (e.g. High Density LED strip), correct for neopixel stick

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)

Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, NEO_GRB + NEO_KHZ800);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

void setup() {
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
  #if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif
  // End of trinket special code
Serial.begin(9600);//Start our Serial coms for serial monitor in our pc
mySerial.begin(9600);//Start our Serial coms for THE MP3
Serial.begin(115200);

  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
      {
//digitalWrite(hitPin,HIGH);
sendCommand(CMD_PLAY_WITHVOLUME, 0X1E01);//play the first song with volume 15 class
}
  // Some example procedures showing how to display to the pixels:

  // Send a theater pixel chase in...
  

 
  
  theaterChaseRainbow(60);
  theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 50); // Red
 theaterChase(strip.Color(0, 0, 127), 50); // Blue
 theaterChaseRainbow(50);
 theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 50); // Red
 theaterChase(strip.Color(0, 0, 127), 50); // Blue
 theaterChaseRainbow(50);
 theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 60); // Red
 theaterChase(strip.Color(0, 0, 127), 60); // Blue
 theaterChaseRainbow(50);
   colorWipe(strip.Color(255, 0, 0), 60); // Red
  colorWipe(strip.Color(0, 255, 0), 60); // Green
  colorWipe(strip.Color(0, 0, 255), 60); // Blue
colorWipe(strip.Color(0, 0, 0, 255), 60); // White RGBW
 theaterChaseRainbow(50);
  theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 60); // Red
 theaterChase(strip.Color(0, 0, 127), 60); // Blue
 theaterChaseRainbow(50);
 theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 60); // Red
 theaterChase(strip.Color(0, 0, 127), 60); // Blue
 theaterChaseRainbow(50);
 theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 60); // Red
 theaterChase(strip.Color(0, 0, 127), 60); // Blue
 theaterChaseRainbow(50);
  rainbow(20);
  theaterChaseRainbow(60);
  theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 50); // Red
 theaterChase(strip.Color(0, 0, 127), 50); // Blue
 theaterChaseRainbow(50);
 theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 50); // Red
 theaterChase(strip.Color(0, 0, 127), 50); // Blue
 theaterChaseRainbow(50);
 theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 60); // Red
 theaterChase(strip.Color(0, 0, 127), 60); // Blue
 theaterChaseRainbow(50);
   colorWipe(strip.Color(255, 0, 0), 60); // Red
  colorWipe(strip.Color(0, 255, 0), 60); // Green
  colorWipe(strip.Color(0, 0, 255), 60); // Blue
colorWipe(strip.Color(0, 0, 0, 255), 60); // White RGBW
 theaterChaseRainbow(50);
  theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 60); // Red
 theaterChase(strip.Color(0, 0, 127), 60); // Blue
 theaterChaseRainbow(50);
 theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 60); // Red
 theaterChase(strip.Color(0, 0, 127), 60); // Blue
 theaterChaseRainbow(50);
 theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 60); // Red
 theaterChase(strip.Color(0, 0, 127), 60); // Blue
 theaterChaseRainbow(50);
  rainbow(20);
  theaterChaseRainbow(60);
  theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 50); // Red
 theaterChase(strip.Color(0, 0, 127), 50); // Blue
 theaterChaseRainbow(50);
 theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 50); // Red
 theaterChase(strip.Color(0, 0, 127), 50); // Blue
 theaterChaseRainbow(50);
 theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 60); // Red
 theaterChase(strip.Color(0, 0, 127), 60); // Blue
 theaterChaseRainbow(50);
   colorWipe(strip.Color(255, 0, 0), 60); // Red
  colorWipe(strip.Color(0, 255, 0), 60); // Green
  colorWipe(strip.Color(0, 0, 255), 60); // Blue
colorWipe(strip.Color(0, 0, 0, 255), 60); // White RGBW
 theaterChaseRainbow(50);
  theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 60); // Red
 theaterChase(strip.Color(0, 0, 127), 60); // Blue
 theaterChaseRainbow(50);
 theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 60); // Red
 theaterChase(strip.Color(0, 0, 127), 60); // Blue
 theaterChaseRainbow(50);
 theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 60); // Red
 theaterChase(strip.Color(0, 0, 127), 60); // Blue
 theaterChaseRainbow(50);
  rainbow(20);
  theaterChaseRainbow(60);
  theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 50); // Red
 theaterChase(strip.Color(0, 0, 127), 50); // Blue
 theaterChaseRainbow(50);
 theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 50); // Red
 theaterChase(strip.Color(0, 0, 127), 50); // Blue
 theaterChaseRainbow(50);
 theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 60); // Red
 theaterChase(strip.Color(0, 0, 127), 60); // Blue
 theaterChaseRainbow(50);
   colorWipe(strip.Color(255, 0, 0), 60); // Red
  colorWipe(strip.Color(0, 255, 0), 60); // Green
  colorWipe(strip.Color(0, 0, 255), 60); // Blue
colorWipe(strip.Color(0, 0, 0, 255), 60); // White RGBW
 theaterChaseRainbow(50);
  theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 60); // Red
 theaterChase(strip.Color(0, 0, 127), 60); // Blue
 theaterChaseRainbow(50);
 theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 60); // Red
 theaterChase(strip.Color(0, 0, 127), 60); // Blue
 theaterChaseRainbow(50);
 theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 60); // Red
 theaterChase(strip.Color(0, 0, 127), 60); // Blue
 theaterChaseRainbow(50);
  rainbow(20);
  theaterChaseRainbow(60);
  theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 50); // Red
 theaterChase(strip.Color(0, 0, 127), 50); // Blue
 theaterChaseRainbow(50);
 theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 50); // Red
 theaterChase(strip.Color(0, 0, 127), 50); // Blue
 theaterChaseRainbow(50);
 theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 60); // Red
 theaterChase(strip.Color(0, 0, 127), 60); // Blue
 theaterChaseRainbow(50);
   colorWipe(strip.Color(255, 0, 0), 60); // Red
  colorWipe(strip.Color(0, 255, 0), 60); // Green
  colorWipe(strip.Color(0, 0, 255), 60); // Blue
colorWipe(strip.Color(0, 0, 0, 255), 60); // White RGBW
 theaterChaseRainbow(50);
  theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 60); // Red
 theaterChase(strip.Color(0, 0, 127), 60); // Blue
 theaterChaseRainbow(50);
 theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 60); // Red
 theaterChase(strip.Color(0, 0, 127), 60); // Blue
 theaterChaseRainbow(50);
 theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 60); // Red
 theaterChase(strip.Color(0, 0, 127), 60); // Blue
 theaterChaseRainbow(50);
  rainbow(20);
  theaterChaseRainbow(60);
  theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 50); // Red
 theaterChase(strip.Color(0, 0, 127), 50); // Blue
 theaterChaseRainbow(50);
 theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 50); // Red
 theaterChase(strip.Color(0, 0, 127), 50); // Blue
 theaterChaseRainbow(50);
 theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 60); // Red
 theaterChase(strip.Color(0, 0, 127), 60); // Blue
 theaterChaseRainbow(50);
   colorWipe(strip.Color(255, 0, 0), 60); // Red
  colorWipe(strip.Color(0, 255, 0), 60); // Green
  colorWipe(strip.Color(0, 0, 255), 60); // Blue
colorWipe(strip.Color(0, 0, 0, 255), 60); // White RGBW
 theaterChaseRainbow(50);
  theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 60); // Red
 theaterChase(strip.Color(0, 0, 127), 60); // Blue
 theaterChaseRainbow(50);
 theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 60); // Red
 theaterChase(strip.Color(0, 0, 127), 60); // Blue
 theaterChaseRainbow(50);
 theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 60); // Red
 theaterChase(strip.Color(0, 0, 127), 60); // Blue
 theaterChaseRainbow(50);
  rainbow(20);
  theaterChaseRainbow(60);
  theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 50); // Red
 theaterChase(strip.Color(0, 0, 127), 50); // Blue
 theaterChaseRainbow(50);
 theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 50); // Red
 theaterChase(strip.Color(0, 0, 127), 50); // Blue
 theaterChaseRainbow(50);
 theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 60); // Red
 theaterChase(strip.Color(0, 0, 127), 60); // Blue
 theaterChaseRainbow(50);
   colorWipe(strip.Color(255, 0, 0), 60); // Red
  colorWipe(strip.Color(0, 255, 0), 60); // Green
  colorWipe(strip.Color(0, 0, 255), 60); // Blue
colorWipe(strip.Color(0, 0, 0, 255), 60); // White RGBW
 theaterChaseRainbow(50);
  theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 60); // Red
 theaterChase(strip.Color(0, 0, 127), 60); // Blue
 theaterChaseRainbow(50);
 theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 60); // Red
 theaterChase(strip.Color(0, 0, 127), 60); // Blue
 theaterChaseRainbow(50);
 theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 60); // Red
 theaterChase(strip.Color(0, 0, 127), 60); // Blue
 theaterChaseRainbow(50);
  rainbow(20);
  theaterChaseRainbow(60);
  theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 50); // Red
 theaterChase(strip.Color(0, 0, 127), 50); // Blue
 theaterChaseRainbow(50);
 theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 50); // Red
 theaterChase(strip.Color(0, 0, 127), 50); // Blue
 theaterChaseRainbow(50);
 theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 60); // Red
 theaterChase(strip.Color(0, 0, 127), 60); // Blue
 theaterChaseRainbow(50);
   colorWipe(strip.Color(255, 0, 0), 60); // Red
  colorWipe(strip.Color(0, 255, 0), 60); // Green
  colorWipe(strip.Color(0, 0, 255), 60); // Blue
colorWipe(strip.Color(0, 0, 0, 255), 60); // White RGBW
 theaterChaseRainbow(50);
  theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 60); // Red
 theaterChase(strip.Color(0, 0, 127), 60); // Blue
 theaterChaseRainbow(50);
 theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 60); // Red
 theaterChase(strip.Color(0, 0, 127), 60); // Blue
 theaterChaseRainbow(50);
 theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 60); // Red
 theaterChase(strip.Color(0, 0, 127), 60); // Blue
 theaterChaseRainbow(50);
  rainbow(20);
  theaterChaseRainbow(60);
  theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 50); // Red
 theaterChase(strip.Color(0, 0, 127), 50); // Blue
 theaterChaseRainbow(50);
 theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 50); // Red
 theaterChase(strip.Color(0, 0, 127), 50); // Blue
 theaterChaseRainbow(50);
 theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 60); // Red
 theaterChase(strip.Color(0, 0, 127), 60); // Blue
 theaterChaseRainbow(50);
   colorWipe(strip.Color(255, 0, 0), 60); // Red
  colorWipe(strip.Color(0, 255, 0), 60); // Green
  colorWipe(strip.Color(0, 0, 255), 60); // Blue
colorWipe(strip.Color(0, 0, 0, 255), 60); // White RGBW
 theaterChaseRainbow(50);
  theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 60); // Red
 theaterChase(strip.Color(0, 0, 127), 60); // Blue
 theaterChaseRainbow(50);
 theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 60); // Red
 theaterChase(strip.Color(0, 0, 127), 60); // Blue
 theaterChaseRainbow(50);
 theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 60); // Red
 theaterChase(strip.Color(0, 0, 127), 60); // Blue
 theaterChaseRainbow(50);
  rainbow(20);
  theaterChaseRainbow(60);
  theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 50); // Red
 theaterChase(strip.Color(0, 0, 127), 50); // Blue
 theaterChaseRainbow(50);
 theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 50); // Red
 theaterChase(strip.Color(0, 0, 127), 50); // Blue
 theaterChaseRainbow(50);
 theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 60); // Red
 theaterChase(strip.Color(0, 0, 127), 60); // Blue
 theaterChaseRainbow(50);
   colorWipe(strip.Color(255, 0, 0), 60); // Red
  colorWipe(strip.Color(0, 255, 0), 60); // Green
  colorWipe(strip.Color(0, 0, 255), 60); // Blue
colorWipe(strip.Color(0, 0, 0, 255), 60); // White RGBW
 theaterChaseRainbow(50);
  theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 60); // Red
 theaterChase(strip.Color(0, 0, 127), 60); // Blue
 theaterChaseRainbow(50);
 theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 60); // Red
 theaterChase(strip.Color(0, 0, 127), 60); // Blue
 theaterChaseRainbow(50);
 theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 60); // Red
 theaterChase(strip.Color(0, 0, 127), 60); // Blue
 theaterChaseRainbow(50);
  rainbow(20);
  theaterChaseRainbow(60);
  theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 50); // Red
 theaterChase(strip.Color(0, 0, 127), 50); // Blue
 theaterChaseRainbow(50);
 theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 50); // Red
 theaterChase(strip.Color(0, 0, 127), 50); // Blue
 theaterChaseRainbow(50);
 theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 60); // Red
 theaterChase(strip.Color(0, 0, 127), 60); // Blue
 theaterChaseRainbow(50);
   colorWipe(strip.Color(255, 0, 0), 60); // Red
  colorWipe(strip.Color(0, 255, 0), 60); // Green
  colorWipe(strip.Color(0, 0, 255), 60); // Blue
colorWipe(strip.Color(0, 0, 0, 255), 60); // White RGBW
 theaterChaseRainbow(50);
  theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 60); // Red
 theaterChase(strip.Color(0, 0, 127), 60); // Blue
 theaterChaseRainbow(50);
 theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 60); // Red
 theaterChase(strip.Color(0, 0, 127), 60); // Blue
 theaterChaseRainbow(50);
 theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 60); // Red
 theaterChase(strip.Color(0, 0, 127), 60); // Blue
 theaterChaseRainbow(50);
  rainbow(20);
  theaterChaseRainbow(60);
  theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 50); // Red
 theaterChase(strip.Color(0, 0, 127), 50); // Blue
 theaterChaseRainbow(50);
 theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 50); // Red
 theaterChase(strip.Color(0, 0, 127), 50); // Blue
 theaterChaseRainbow(50);
 theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 60); // Red
 theaterChase(strip.Color(0, 0, 127), 60); // Blue
 theaterChaseRainbow(50);
   colorWipe(strip.Color(255, 0, 0), 60); // Red
  colorWipe(strip.Color(0, 255, 0), 60); // Green
  colorWipe(strip.Color(0, 0, 255), 60); // Blue
colorWipe(strip.Color(0, 0, 0, 255), 60); // White RGBW
 theaterChaseRainbow(50);
  theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 60); // Red
 theaterChase(strip.Color(0, 0, 127), 60); // Blue
 theaterChaseRainbow(50);
 theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 60); // Red
 theaterChase(strip.Color(0, 0, 127), 60); // Blue
 theaterChaseRainbow(50);
 theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 60); // Red
 theaterChase(strip.Color(0, 0, 127), 60); // Blue
 theaterChaseRainbow(50);
  rainbow(20);
  theaterChaseRainbow(60);
  theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 50); // Red
 theaterChase(strip.Color(0, 0, 127), 50); // Blue
 theaterChaseRainbow(50);
 theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 50); // Red
 theaterChase(strip.Color(0, 0, 127), 50); // Blue
 theaterChaseRainbow(50);
 theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 60); // Red
 theaterChase(strip.Color(0, 0, 127), 60); // Blue
 theaterChaseRainbow(50);
   colorWipe(strip.Color(255, 0, 0), 60); // Red
  colorWipe(strip.Color(0, 255, 0), 60); // Green
  colorWipe(strip.Color(0, 0, 255), 60); // Blue
colorWipe(strip.Color(0, 0, 0, 255), 60); // White RGBW
 theaterChaseRainbow(50);
  theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 60); // Red
 theaterChase(strip.Color(0, 0, 127), 60); // Blue
 theaterChaseRainbow(50);
 theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 60); // Red
 theaterChase(strip.Color(0, 0, 127), 60); // Blue
 theaterChaseRainbow(50);
 theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 60); // Red
 theaterChase(strip.Color(0, 0, 127), 60); // Blue
 theaterChaseRainbow(50);
  rainbow(20);
  theaterChaseRainbow(60);
  theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 50); // Red
 theaterChase(strip.Color(0, 0, 127), 50); // Blue
 theaterChaseRainbow(50);
 theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 50); // Red
 theaterChase(strip.Color(0, 0, 127), 50); // Blue
 theaterChaseRainbow(50);
 theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 60); // Red
 theaterChase(strip.Color(0, 0, 127), 60); // Blue
 theaterChaseRainbow(50);
   colorWipe(strip.Color(255, 0, 0), 60); // Red
  colorWipe(strip.Color(0, 255, 0), 60); // Green
  colorWipe(strip.Color(0, 0, 255), 60); // Blue
colorWipe(strip.Color(0, 0, 0, 255), 60); // White RGBW
 theaterChaseRainbow(50);
  theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 60); // Red
 theaterChase(strip.Color(0, 0, 127), 60); // Blue
 theaterChaseRainbow(50);
 theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 60); // Red
 theaterChase(strip.Color(0, 0, 127), 60); // Blue
 theaterChaseRainbow(50);
 theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 60); // Red
 theaterChase(strip.Color(0, 0, 127), 60); // Blue
 theaterChaseRainbow(50);
  rainbow(20);
  theaterChaseRainbow(60);
  theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 50); // Red
 theaterChase(strip.Color(0, 0, 127), 50); // Blue
 theaterChaseRainbow(50);
 theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 50); // Red
 theaterChase(strip.Color(0, 0, 127), 50); // Blue
 theaterChaseRainbow(50);
 theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 60); // Red
 theaterChase(strip.Color(0, 0, 127), 60); // Blue
 theaterChaseRainbow(50);
   colorWipe(strip.Color(255, 0, 0), 60); // Red
  colorWipe(strip.Color(0, 255, 0), 60); // Green
  colorWipe(strip.Color(0, 0, 255), 60); // Blue
colorWipe(strip.Color(0, 0, 0, 255), 60); // White RGBW
 theaterChaseRainbow(50);
  theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 60); // Red
 theaterChase(strip.Color(0, 0, 127), 60); // Blue
 theaterChaseRainbow(50);
 theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 60); // Red
 theaterChase(strip.Color(0, 0, 127), 60); // Blue
 theaterChaseRainbow(50);
 theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 60); // Red
 theaterChase(strip.Color(0, 0, 127), 60); // Blue
 theaterChaseRainbow(50);
  rainbow(20);
  theaterChaseRainbow(60);
  theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 50); // Red
 theaterChase(strip.Color(0, 0, 127), 50); // Blue
 theaterChaseRainbow(50);
 theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 50); // Red
 theaterChase(strip.Color(0, 0, 127), 50); // Blue
 theaterChaseRainbow(50);
 theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 60); // Red
 theaterChase(strip.Color(0, 0, 127), 60); // Blue
 theaterChaseRainbow(50);
   colorWipe(strip.Color(255, 0, 0), 60); // Red
  colorWipe(strip.Color(0, 255, 0), 60); // Green
  colorWipe(strip.Color(0, 0, 255), 60); // Blue
colorWipe(strip.Color(0, 0, 0, 255), 60); // White RGBW
 theaterChaseRainbow(50);
  theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 60); // Red
 theaterChase(strip.Color(0, 0, 127), 60); // Blue
 theaterChaseRainbow(50);
 theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 60); // Red
 theaterChase(strip.Color(0, 0, 127), 60); // Blue
 theaterChaseRainbow(50);
 theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 60); // Red
 theaterChase(strip.Color(0, 0, 127), 60); // Blue
 theaterChaseRainbow(50);
  rainbow(20);
  theaterChaseRainbow(60);
  theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 50); // Red
 theaterChase(strip.Color(0, 0, 127), 50); // Blue
 theaterChaseRainbow(50);
 theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 50); // Red
 theaterChase(strip.Color(0, 0, 127), 50); // Blue
 theaterChaseRainbow(50);
 theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 60); // Red
 theaterChase(strip.Color(0, 0, 127), 60); // Blue
 theaterChaseRainbow(50);
   colorWipe(strip.Color(255, 0, 0), 60); // Red
  colorWipe(strip.Color(0, 255, 0), 60); // Green
  colorWipe(strip.Color(0, 0, 255), 60); // Blue
colorWipe(strip.Color(0, 0, 0, 255), 60); // White RGBW
 theaterChaseRainbow(50);
  theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 60); // Red
 theaterChase(strip.Color(0, 0, 127), 60); // Blue
 theaterChaseRainbow(50);
 theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 60); // Red
 theaterChase(strip.Color(0, 0, 127), 60); // Blue
 theaterChaseRainbow(50);
 theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 60); // Red
 theaterChase(strip.Color(0, 0, 127), 60); // Blue
 theaterChaseRainbow(50);
  rainbow(20);
  theaterChaseRainbow(60);
  theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 50); // Red
 theaterChase(strip.Color(0, 0, 127), 50); // Blue
 theaterChaseRainbow(50);
 theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 50); // Red
 theaterChase(strip.Color(0, 0, 127), 50); // Blue
 theaterChaseRainbow(50);
 theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 60); // Red
 theaterChase(strip.Color(0, 0, 127), 60); // Blue
 theaterChaseRainbow(50);
   colorWipe(strip.Color(255, 0, 0), 60); // Red
  colorWipe(strip.Color(0, 255, 0), 60); // Green
  colorWipe(strip.Color(0, 0, 255), 60); // Blue
colorWipe(strip.Color(0, 0, 0, 255), 60); // White RGBW
 theaterChaseRainbow(50);
  theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 60); // Red
 theaterChase(strip.Color(0, 0, 127), 60); // Blue
 theaterChaseRainbow(50);
 theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 60); // Red
 theaterChase(strip.Color(0, 0, 127), 60); // Blue
 theaterChaseRainbow(50);
 theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 60); // Red
 theaterChase(strip.Color(0, 0, 127), 60); // Blue
 theaterChaseRainbow(50);
  rainbow(20);
  theaterChaseRainbow(60);
  theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 50); // Red
 theaterChase(strip.Color(0, 0, 127), 50); // Blue
 theaterChaseRainbow(50);
 theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 50); // Red
 theaterChase(strip.Color(0, 0, 127), 50); // Blue
 theaterChaseRainbow(50);
 theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 60); // Red
 theaterChase(strip.Color(0, 0, 127), 60); // Blue
 theaterChaseRainbow(50);
   colorWipe(strip.Color(255, 0, 0), 60); // Red
  colorWipe(strip.Color(0, 255, 0), 60); // Green
  colorWipe(strip.Color(0, 0, 255), 60); // Blue
colorWipe(strip.Color(0, 0, 0, 255), 60); // White RGBW
 theaterChaseRainbow(50);
  theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 60); // Red
 theaterChase(strip.Color(0, 0, 127), 60); // Blue
 theaterChaseRainbow(50);
 theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 60); // Red
 theaterChase(strip.Color(0, 0, 127), 60); // Blue
 theaterChaseRainbow(50);
 theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 60); // Red
 theaterChase(strip.Color(0, 0, 127), 60); // Blue
 theaterChaseRainbow(50);
  rainbow(20);
  theaterChaseRainbow(60);
  theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 50); // Red
 theaterChase(strip.Color(0, 0, 127), 50); // Blue
 theaterChaseRainbow(50);
 theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 50); // Red
 theaterChase(strip.Color(0, 0, 127), 50); // Blue
 theaterChaseRainbow(50);
 theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 60); // Red
 theaterChase(strip.Color(0, 0, 127), 60); // Blue
 theaterChaseRainbow(50);
   colorWipe(strip.Color(255, 0, 0), 60); // Red
  colorWipe(strip.Color(0, 255, 0), 60); // Green
  colorWipe(strip.Color(0, 0, 255), 60); // Blue
colorWipe(strip.Color(0, 0, 0, 255), 60); // White RGBW
 theaterChaseRainbow(50);
  theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 60); // Red
 theaterChase(strip.Color(0, 0, 127), 60); // Blue
 theaterChaseRainbow(50);
 theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 60); // Red
 theaterChase(strip.Color(0, 0, 127), 60); // Blue
 theaterChaseRainbow(50);
 theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 60); // Red
 theaterChase(strip.Color(0, 0, 127), 60); // Blue
 theaterChaseRainbow(50);
  rainbow(20);
  theaterChaseRainbow(60);
  theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 50); // Red
 theaterChase(strip.Color(0, 0, 127), 50); // Blue
 theaterChaseRainbow(50);
 theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 50); // Red
 theaterChase(strip.Color(0, 0, 127), 50); // Blue
 theaterChaseRainbow(50);
 theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 60); // Red
 theaterChase(strip.Color(0, 0, 127), 60); // Blue
 theaterChaseRainbow(50);
   colorWipe(strip.Color(255, 0, 0), 60); // Red
  colorWipe(strip.Color(0, 255, 0), 60); // Green
  colorWipe(strip.Color(0, 0, 255), 60); // Blue
colorWipe(strip.Color(0, 0, 0, 255), 60); // White RGBW
 theaterChaseRainbow(50);
  theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 60); // Red
 theaterChase(strip.Color(0, 0, 127), 60); // Blue
 theaterChaseRainbow(50);
 theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 60); // Red
 theaterChase(strip.Color(0, 0, 127), 60); // Blue
 theaterChaseRainbow(50);
 theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 60); // Red
 theaterChase(strip.Color(0, 0, 127), 60); // Blue
 theaterChaseRainbow(50);
  rainbow(20);
  theaterChaseRainbow(60);
  theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 50); // Red
 theaterChase(strip.Color(0, 0, 127), 50); // Blue
 theaterChaseRainbow(50);
 theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 50); // Red
 theaterChase(strip.Color(0, 0, 127), 50); // Blue
 theaterChaseRainbow(50);
 theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 60); // Red
 theaterChase(strip.Color(0, 0, 127), 60); // Blue
 theaterChaseRainbow(50);
   colorWipe(strip.Color(255, 0, 0), 60); // Red
  colorWipe(strip.Color(0, 255, 0), 60); // Green
  colorWipe(strip.Color(0, 0, 255), 60); // Blue
colorWipe(strip.Color(0, 0, 0, 255), 60); // White RGBW
 theaterChaseRainbow(50);
  theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 60); // Red
 theaterChase(strip.Color(0, 0, 127), 60); // Blue
 theaterChaseRainbow(50);
 theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 60); // Red
 theaterChase(strip.Color(0, 0, 127), 60); // Blue
 theaterChaseRainbow(50);
 theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 60); // Red
 theaterChase(strip.Color(0, 0, 127), 60); // Blue
 theaterChaseRainbow(50);
  rainbow(20);
  theaterChaseRainbow(60);
  theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 50); // Red
 theaterChase(strip.Color(0, 0, 127), 50); // Blue
 theaterChaseRainbow(50);
 theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 50); // Red
 theaterChase(strip.Color(0, 0, 127), 50); // Blue
 theaterChaseRainbow(50);
 theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 60); // Red
 theaterChase(strip.Color(0, 0, 127), 60); // Blue
 theaterChaseRainbow(50);
   colorWipe(strip.Color(255, 0, 0), 60); // Red
  colorWipe(strip.Color(0, 255, 0), 60); // Green
  colorWipe(strip.Color(0, 0, 255), 60); // Blue
colorWipe(strip.Color(0, 0, 0, 255), 60); // White RGBW
 theaterChaseRainbow(50);
  theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 60); // Red
 theaterChase(strip.Color(0, 0, 127), 60); // Blue
 theaterChaseRainbow(50);
 theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 60); // Red
 theaterChase(strip.Color(0, 0, 127), 60); // Blue
 theaterChaseRainbow(50);
 theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 60); // Red
 theaterChase(strip.Color(0, 0, 127), 60); // Blue
 theaterChaseRainbow(50);
  rainbow(20);
  theaterChaseRainbow(60);
  theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 50); // Red
 theaterChase(strip.Color(0, 0, 127), 50); // Blue
 theaterChaseRainbow(50);
 theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 50); // Red
 theaterChase(strip.Color(0, 0, 127), 50); // Blue
 theaterChaseRainbow(50);
 theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 60); // Red
 theaterChase(strip.Color(0, 0, 127), 60); // Blue
 theaterChaseRainbow(50);
   colorWipe(strip.Color(255, 0, 0), 60); // Red
  colorWipe(strip.Color(0, 255, 0), 60); // Green
  colorWipe(strip.Color(0, 0, 255), 60); // Blue
colorWipe(strip.Color(0, 0, 0, 255), 60); // White RGBW
 theaterChaseRainbow(50);
  theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 60); // Red
 theaterChase(strip.Color(0, 0, 127), 60); // Blue
 theaterChaseRainbow(50);
 theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 60); // Red
 theaterChase(strip.Color(0, 0, 127), 60); // Blue
 theaterChaseRainbow(50);
 theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 60); // Red
 theaterChase(strip.Color(0, 0, 127), 60); // Blue
 theaterChaseRainbow(50);
  rainbow(20);
  theaterChaseRainbow(60);
  theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 50); // Red
 theaterChase(strip.Color(0, 0, 127), 50); // Blue
 theaterChaseRainbow(50);
 theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 50); // Red
 theaterChase(strip.Color(0, 0, 127), 50); // Blue
 theaterChaseRainbow(50);
 theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 60); // Red
 theaterChase(strip.Color(0, 0, 127), 60); // Blue
 theaterChaseRainbow(50);
   colorWipe(strip.Color(255, 0, 0), 60); // Red
  colorWipe(strip.Color(0, 255, 0), 60); // Green
  colorWipe(strip.Color(0, 0, 255), 60); // Blue
colorWipe(strip.Color(0, 0, 0, 255), 60); // White RGBW
 theaterChaseRainbow(50);
  theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 60); // Red
 theaterChase(strip.Color(0, 0, 127), 60); // Blue
 theaterChaseRainbow(50);
 theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 60); // Red
 theaterChase(strip.Color(0, 0, 127), 60); // Blue
 theaterChaseRainbow(50);
 theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 60); // Red
 theaterChase(strip.Color(0, 0, 127), 60); // Blue
 theaterChaseRainbow(50);
  rainbow(20);
  theaterChaseRainbow(60);
  theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 50); // Red
 theaterChase(strip.Color(0, 0, 127), 50); // Blue
 theaterChaseRainbow(50);
 theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 50); // Red
 theaterChase(strip.Color(0, 0, 127), 50); // Blue
 theaterChaseRainbow(50);
 theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 60); // Red
 theaterChase(strip.Color(0, 0, 127), 60); // Blue
 theaterChaseRainbow(50);
   colorWipe(strip.Color(255, 0, 0), 60); // Red
  colorWipe(strip.Color(0, 255, 0), 60); // Green
  colorWipe(strip.Color(0, 0, 255), 60); // Blue
colorWipe(strip.Color(0, 0, 0, 255), 60); // White RGBW
 theaterChaseRainbow(50);
  theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 60); // Red
 theaterChase(strip.Color(0, 0, 127), 60); // Blue
 theaterChaseRainbow(50);
 theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 60); // Red
 theaterChase(strip.Color(0, 0, 127), 60); // Blue
 theaterChaseRainbow(50);
 theaterChase(strip.Color(127, 127, 127), 60); // White
 theaterChase(strip.Color(127, 0, 0), 60); // Red
 theaterChase(strip.Color(0, 0, 127), 60); // Blue
 theaterChaseRainbow(50);
  rainbow(20);
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
void sendCommand(int8_t command, int16_t dat)
{
 delay(20);
 Send_buf[0] = 0x7e; //starting byte
 Send_buf[1] = 0xff; //version
 Send_buf[2] = 0x06; //the number of bytes of the command without starting byte and ending byte
 Send_buf[3] = command; //
 Send_buf[4] = 0x00;//0x00 = no feedback, 0x01 = feedback
 Send_buf[5] = (int8_t)(dat >> 8);//datah
 Send_buf[6] = (int8_t)(dat); //datal
 Send_buf[7] = 0xef; //ending byte
 for(uint8_t i=0; i<8; i++)//
 {
   mySerial.write(Send_buf[i]) ;//send bit to serial mp3
 }
 Serial.println();
}

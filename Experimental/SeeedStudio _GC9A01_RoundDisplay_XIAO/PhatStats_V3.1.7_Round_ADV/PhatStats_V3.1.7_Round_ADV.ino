
#define CODE_VERS  "3.1.7.RND.ADV"  // Code version number

/*
  uVolume, GNATSTATS OLED, PHATSTATS TFT PC Performance Monitor & HardwareSerialMonitor Windows Client
  Rupert Hirst © 2016 - 2023 http://tallmanlabs.com http://runawaybrainz.blogspot.com/
  https://github.com/koogar/Phat-Stats  https://hackaday.io/project/19018-phat-stats-pc-performance-tft-display

  Board Manager Links
  ------------------------------------
  Click on File > Preference, and fill Additional Boards Manager URLs with the url below:

  XIAO ATSAMD21 / WIO Terminal
  ----------------------------
  https://files.seeedstudio.com/arduino/package_seeeduino_boards_index.json

  XIAO NRF52840
  -------------
  https://files.seeedstudio.com/arduino/package_seeeduino_boards_index.json

  XIAO RP2040
  -----------
  https://github.com/earlephilhower/arduino-pico/releases/download/global/package_rp2040_index.json

  XIAO ESP32C3
  ------------
  https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_dev_index.json
  https://wiki.seeedstudio.com/XIAO_ESP32C3_Getting_Started/#q3-i-want-to-reflash-the-bootloader-with-factory-firmware

  QY-PY ATSAMD21
  --------------
  !!!Install Arduino ATSAMD then ADD !!!
  https://adafruit.github.io/arduino-board-index/package_adafruit_index.json

  WIO Terminal
  --------------------------
  https://files.seeedstudio.com/arduino/package_seeeduino_boards_index.json


  Libraries
  -------------

  Adafruit Neopixel
  https://github.com/adafruit/Adafruit_NeoPixel

  Adafruit GFX Library
  https://github.com/adafruit/Adafruit-GFX-Library

  Adafruit ILI9341
  https://github.com/adafruit/Adafruit_ILI9341

  ciniml/WioTerminal_BackLight  // no need to install this library
  https://github.com/Seeed-Studio/Seeed_Arduino_Sketchbook/tree/master/examples/WioTerminal_BackLight


  Hookup Guide
  https://runawaybrainz.blogspot.com/2021/03/phat-stats-ili9341-tft-display-hook-up.html

  Library Working Version Checker 18/04/2023
  (some libraries may not be used in this sketch)
  ------------------------------------------------
  Arduino IDE           v1.8.19
  espressif (ESP32)     v2.0.5 (v2.08 = ESP32_AnalogWrite compile error)
  ------------------------------------------------
  ESP32_AnalogWrite     v0.2    (Current 04/2023)
  Adafruit BusIO        v1.14.0 (Current 04/2023
  Adafruit_GFX          v1.11.5 (Current 04/2023)
  Adafruit_NeoPixel     v1.11.0 (Current 04/2023)
  Adafruit ILI9341      v1.5.12 (Current 04/2023)
  Adafruit_SH1106_BADZZ v1.1.0  (32u4 only Current 04/2023)
  Adafruit SH110X       v2.1.8  (Current 04/2023)
  Adafruit SD1306       v2.5.7  (Current 04/2023)
  HID-Project           v2.8.4  (Current 04/2023)
  IRremote              v4.1.2  (Current 04/2023)
  TML_ErriezRotaryFullStep      (Current 04/2023)

  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
               SEE CONFIGURATION TAB FIRST, FOR QUICK SETTINGS!!!!
  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
*/


#include <Wire.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Fonts/Org_01.h>

#include "Adafruit_GC9A01A.h"

#include "Configuration_Settings.h" // load settings
#include "Z_Bitmaps.h"



/* Declare Prototype voids to the compiler*/
void Display_LS      ();
void Display_Port    ();
void Display_LS_180  ();
void Display_Port_180();
void Display_CircleGauge    ();
void Display_CircleGauge_180();
void button_Modes    ();
void serialEvent     ();
void activityChecker ();
void splashScreen    ();
void backlightON     ();
void backlightOFF    ();


/*


  B.LIGHT             = 6
  Screen Mode Button  = 1


  Onboard LED's
  --------------
  XIAO  (NRF52840)         Built in LED      = 11     (*Not Required for Reference only!!!)
  XIAO  (RP2040)           Built in LED      = 25     (*Not Required for Reference only!!!)
  XIAO  (ATSAMD21)         Built in LED      = 13     (*Not Required for Reference only!!!)
  WIO Terminal (ATSAMD51)  Build in LED      = 13

  QT-PY (ATSAMD21) Built in Neopixel =  11 or (12 to turn it off) (*Not Required for Reference only!!!)

  ==========================================================================================================




  Seeed Studio Round XIAO Display
  -------------------------------
   TFT_SCLK D8
   TFT_MISO D9
   TFT_MOSI D10
   TFT_CS   D1  // Chip select control pin
   TFT_DC   D3  // Data Command control pin
   TFT_RST  -1  // Reset pin (could connect to RST pin)

   LCD_BACKLIGHT   D6  // slide dip switch slot 2 to (KE) on the back of the Seeed Round display for backlight control

  ==========================================================================================================*/


//----------------------------------------------------------------------------
/* GC9A01A TFT setup */
//----------------------------------------------------------------------------

#if defined(Seeeduino_XIAO_RP2040) ^ defined(Seeeduino_XIAO_ESP32C3)

#define TFT_CS     D1
#define TFT_DC     D3
#define TFT_RST    -1  // ESP32C3 & OLD PCB V0.93

//#define TFT_SCLK   D8
//#define TFT_MOSI   D10

Adafruit_GC9A01A tft(TFT_CS, TFT_DC, TFT_RST);
#endif

//--------------
#if defined(Seeeduino_XIAO_ATSAMD) ^ defined(Adafruit_QTPY_ATSAMD) ^ defined(Seeeduino_XIAO_NRF52840)

#define TFT_CS     1
#define TFT_DC     3
#define TFT_RST    -1  // ESP32C3 & OLD PCB V0.93

//#define TFT_SCLK   8
//#define TFT_MOSI   10

Adafruit_GC9A01A tft(TFT_CS, TFT_DC, TFT_RST);
#endif


//-----------------------------------------------------------------------------


#if defined(Seeeduino_XIAO_RP2040) ^ defined(Seeeduino_XIAO_ESP32C3)
/* Mode Button pin*/
int mode_Button       = -1;
/* Screen TFT backlight Pin */
int TFT_backlight_PIN = D6;  // slide dip switch slot 2 to (KE) on the back of the Seeed Round display for backlight control
#endif


#if defined(Seeeduino_XIAO_ATSAMD) ^ defined(Adafruit_QTPY_ATSAMD) ^ defined(Seeeduino_XIAO_NRF52840)
/* Mode Button pin*/
int mode_Button       = -1;  //Mode Button pin
/* Screen TFT backlight Pin */
int TFT_backlight_PIN = 6;
#endif


//-----------------------------------------------------------------------------

/* Button Counter */
int display_Button_counter = 0;

/*XIAO TFT Brightness*/
int brightness_countLast = 0;   // Store Last PWM Value

/* More Display stuff*/
int displayDraw = 0;

//-----------------------------------------------------------------------------

/* Timer for active connection to host*/
boolean activeConn = false;
long lastActiveConn = 0;
boolean bootMode = true;

/* Vars for serial input*/
String inputString = "";
boolean stringComplete = false;

//-----------------------------  TFT Colours  ---------------------------------


#define GC9A01A_TEST        0x6A4E
#define GC9A01A_BLACK       0x0000
#define GC9A01A_WHITE       0xFFFF
#define GC9A01A_GREY        0x7BEF
#define GC9A01A_LIGHT_GREY  0xC618
#define GC9A01A_GREEN       0x07E0
#define GC9A01A_LIME        0x87E0
#define GC9A01A_BLUE        0x001F
#define GC9A01A_RED         0xF800
#define GC9A01A_AQUA        0x5D1C
#define GC9A01A_YELLOW      0xFFE0
#define GC9A01A_MAGENTA     0xF81F
#define GC9A01A_CYAN        0x07FF
#define GC9A01A_DARK_CYAN   0x03EF
#define GC9A01A_ORANGE      0xFCA0
#define GC9A01A_PINK        0xF97F
#define GC9A01A_BROWN       0x8200
#define GC9A01A_VIOLET      0x9199
#define GC9A01A_SILVER      0xA510
#define GC9A01A_GOLD        0xA508
#define GC9A01A_NAVY        0x000F
#define GC9A01A_MAROON      0x7800
#define GC9A01A_PURPLE      0x780F
#define GC9A01A_OLIVE       0x7BE0


//------------------------- CRT Style Colour Profiles ----------------------

#ifdef  RETRO_MONO

#define GC9A01A_YELLOW      0xFFFF //GC9A01A_WHITE
#define GC9A01A_WHITE       0xFFFF //GC9A01A_WHITE
#define GC9A01A_BLUE        0xA510 //GC9A01A_SILVER 
#define GC9A01A_GREEN       0x7BEF //GC9A01A_GREY 
#define GC9A01A_RED         0xC618 //GC9A01A_LIGHT_GREY
//--
#define GC9A01A_SILVER      0xA510 //GC9A01A_SILVER
#define GC9A01A_GREY        0x7BEF //GC9A01A_GREY 
#define GC9A01A_LIGHT_GREY  0xC618 //GC9A01A_LIGHT_GREY

#endif


#ifdef  RETRO_AMBER

#define GC9A01A_YELLOW      0xFFE0 //GC9A01A_YELLOW
#define GC9A01A_WHITE       0xFFE0 //GC9A01A_YELLOW
#define GC9A01A_BLUE        0xA508 //GC9A01A_GOLD
#define GC9A01A_GREEN       0xA508 //GC9A01A_GOLD
#define GC9A01A_RED         0xA508 //GC9A01A_GOLD
//--
#define GC9A01A_SILVER      0xFFE0 //GC9A01A_YELLOW
#define GC9A01A_GREY        0xA508 //GC9A01A_GOLD
#define GC9A01A_LIGHT_GREY  0xA508 //GC9A01A_GOLD

#endif


#ifdef  RETRO_GREEN

#define GC9A01A_YELLOW      0x07E0 //GC9A01A_GREEN
#define GC9A01A_WHITE       0x07E0 //GC9A01A_GREEN
#define GC9A01A_BLUE        0x7BE0 //GC9A01A_OLIVE
#define GC9A01A_GREEN       0x7BE0 //GC9A01A_OLIVE
#define GC9A01A_RED         0x7BE0 //GC9A01A_OLIVE
//--------
#define GC9A01A_SILVER      0x07E0 //GC9A01A_GREEN
#define GC9A01A_GREY        0x7BE0 //GC9A01A_OLIVE
#define GC9A01A_LIGHT_GREY  0x7BE0 //GC9A01A_OLIVE

#endif



//--------------------------------

void setup() {

  Serial.begin(baudRate);
  /* String Buffer */
  inputString.reserve(220);

  /* Set up PINs */
  pinMode(mode_Button, INPUT_PULLUP);
  pinMode(TFT_backlight_PIN, OUTPUT); // declare backlight pin to be an output:


#if defined(Seeeduino_XIAO_ATSAMD) ^ defined(Seeeduino_WIO_ATSAMD51)
#ifdef enableTX_LED
  pinMode(TX_LEDPin, OUTPUT); //  Builtin LED /  HIGH(OFF) LOW (ON)
#endif
#endif

#ifdef Seeeduino_XIAO_RP2040
#ifdef enableTX_LED
  pinMode(TX_LEDPin, OUTPUT);
#endif
#endif

#ifdef Seeeduino_XIAO_NRF52840
#ifdef enableTX_LED
  pinMode(TX_LEDPin, OUTPUT);
#endif
#endif

  backlightOFF();


  /* TFT SETUP */

  /*Give the micro time to initiate the SPi bus*/
  delay(100);
  tft.begin();

  tft.setRotation(ASPECT);// Rotate the display :  0, 1, 2 or 3 = (0, 90, 180 or 270 degrees)

  /* stops text wrapping*/
  tft.setTextWrap(false); // Stop  "Loads/Temps" wrapping and corrupting static characters

  /* Clear Screen*/
  tft.fillScreen(GC9A01A_BLACK);
  tft.setTextColor(GC9A01A_WHITE);

  splashScreen();

}

//-----End of Set up -------

void loop() {

  /* Check for Serial Activity */
  serialEvent();

#ifdef  enableActivityChecker
  activityChecker();      // Turn off screen when no activity
#endif

  /* Mode Button, moved to its own tab*/
  button_Modes();

#if defined(Seeeduino_XIAO_ATSAMD) ^ defined(Seeeduino_WIO_ATSAMD51)
#ifdef enableTX_LED
  /*Serial Activity LED */
  digitalWrite(TX_LEDPin, HIGH);    // turn the LED off HIGH(OFF) LOW (ON)
#endif
#endif

#ifdef Seeeduino_XIAO_RP2040
#ifdef enableTX_LED
  /*Serial Activity LED */
  digitalWrite(TX_LEDPin, HIGH);    // turn the LED off HIGH(OFF) LOW (ON)
#endif
#endif


#ifdef Seeeduino_XIAO_NRF52840
  /*Serial Activity LED */
#ifdef enableTX_LED
  pinMode(TX_LEDPin, HIGH); //  Builtin LED /  HIGH(OFF) LOW (ON)
#endif
#endif

}

//-----End of Main Loop -------



//-----------------------------  Serial Events -------------------------------

/* SerialEvent occurs whenever a new data comes in the hardware serial RX. This
  routine is run between each time loop() runs, so using delay inside loop can
  delay response. Multiple bytes of data may be available.*/

void serialEvent() {

  while (Serial.available()) {
    //while (Serial.available() > 0) {

    /* get the new byte: */
    char inChar = (char)Serial.read();
    //Serial.print(inChar); // Debug Incoming Serial

    /* add it to the inputString: */
    inputString += inChar;

    /* if the incoming character has '|' in it, set a flag so the main loop can do something about it: */
    if (inChar == '|') {
      stringComplete = true;

      delay(Serial_eventDelay);   //delay screen event to stop screen data corruption

      /* Serial Activity LEDs */
#ifdef enableTX_LED

#if defined(Seeeduino_XIAO_ATSAMD) ^ defined(Seeeduino_WIO_ATSAMD51)
      digitalWrite(TX_LEDPin, LOW);   // turn the LED off HIGH(OFF) LOW (ON)
#endif
#endif

#ifdef Seeeduino_XIAO_RP2040
#ifdef enableTX_LED
      digitalWrite(TX_LEDPin, LOW);   // turn the LED off HIGH(OFF) LOW (ON)
#endif
#endif



#ifdef enableTX_LED
#ifdef Seeeduino_XIAO_NRF52840
      digitalWrite(TX_LEDPin, LOW);   // turn the LED off HIGH(OFF) LOW (ON)
#endif
#endif

      /* TX blink delay*/
      delay(TX_LED_Delay);

    }
  }
}

//----------------------------- ActivityChecker  -------------------------------
void activityChecker() {

  if (millis() - lastActiveConn > lastActiveDelay)
    activeConn = false;
  else
    activeConn = true;

  if (!activeConn) {

 
    tft.fillScreen(GC9A01A_BLACK);
    tft.drawCircle   (120,   120, 119, GC9A01A_RED);

    tft.setRotation(ASPECT);// Rotate the display at the start:  0, 1, 2 or 3 = (0, 90, 180 or 270 degrees)
    tft.setTextColor(GC9A01A_RED);

    tft.drawBitmap(82, 70, WaitingDataBMP2_90, 76, 154, GC9A01A_RED);

    tft.setCursor(50, 44);
    tft.setFont(&Org_01);
    tft.setTextSize(2);
    tft.println("NO COM DATA!!!");

    delay(1000);

    /* Clear Screen, Turn Off Backlight & Neopixels when there is no activity, */
    backlightOFF ();

    tft.fillScreen(GC9A01A_BLACK);
    tft.setFont(); // Set Default Adafruit GRFX Font
    displayDraw = 0;

  }
}

//----------------------------- TFT Backlight  -------------------------------

#ifdef fixedBacklight // PIN4

void backlightON () {
  digitalWrite(TFT_backlight_PIN, HIGH);
}
void backlightOFF () {
  digitalWrite(TFT_backlight_PIN, LOW);
}

#else // PWM

void backlightON () {

  analogWrite(TFT_backlight_PIN, brightness_count); // TFT turn on backlight

}
void backlightOFF () {
  analogWrite(TFT_backlight_PIN, 0);        // TFT turn off backlight,

}
#endif

//----------------------------- Splash Screens --------------------------------
void splashScreen() {

  /* Initial Boot Screen, */

  backlightOFF();

  tft.setRotation(ASPECT);// Rotate the display at the start:  0, 1, 2 or 3 = (0, 90, 180 or 270 degrees)

  tft.setFont(&Org_01);

  tft.fillScreen(GC9A01A_BLACK);
  tft.drawCircle   (120,   120, 119, GC9A01A_WHITE); // bottom left corner LS


  tft.drawBitmap(44, 20, HSM_BG_BMP,  142, 128, GC9A01A_WHITE);
  tft.drawBitmap(44, 20, HSM_BG2_BMP, 142, 128, GC9A01A_RED);
  tft.drawBitmap(44, 20, HSM_BMP,     142, 128, GC9A01A_GREY);

  tft.setTextSize(3);
  tft.setCursor(86, 140);
  tft.setTextColor(GC9A01A_WHITE);
  tft.println("PHAT ");
  tft.setTextSize(3);
  tft.setCursor(78, 160);
  tft.println("STATS");

  tft.setTextSize(2);
  tft.setCursor(24, 178);
  tft.setTextColor(GC9A01A_SILVER);
  tft.print("PC Hardware Monitor");

  tft.setTextSize(2);
  tft.setCursor(56, 200);
  tft.setTextColor(GC9A01A_RED);
  tft.print("tallmanlabs.com");

  //------------------------------------------------------------------



  /*  Baud Rate */
  tft.setFont(); // Set Default Adafruit GRFX Font
  tft.setTextColor(GC9A01A_WHITE);
  tft.setTextSize(1);
  tft.setCursor(82, 220);
  tft.print("Baud: ");
  tft.print (baudRate);
  tft.print(" bps ");

  /* Set version */
  tft.setFont(); // Set Default Adafruit GRFX Font
  tft.setTextColor(GC9A01A_WHITE);
  tft.setTextSize(1);
  tft.setCursor(68, 208);
  tft.print("TFT: v");
  tft.print (CODE_VERS);

  backlightON();
  delay(1000);

  //----------------------------------------------------------------

  backlightOFF();
  tft.setTextColor(GC9A01A_WHITE);

  FeatureSet_Indicator2(); // Display Icons for enabled features
  backlightON();
  delay(1000);

  backlightOFF();// Hide the Screen while drawing

  tft.setRotation(ASPECT);// Rotate the display at the start:  0, 1, 2 or 3 = (0, 90, 180 or 270 degrees)
  tft.fillScreen(GC9A01A_BLACK);
  tft.drawCircle   (120,   120, 119, GC9A01A_WHITE); // bottom left corner LS


  tft.setFont(&Org_01);
  tft.setTextSize(2);
  tft.setCursor(50, 54);
  //tft.println("  Initialising ");
  tft.println("INITIALISING ");
  tft.drawBitmap(82, 70, WaitingDataBMP2_90, 76, 154, GC9A01A_WHITE);

  backlightON();

  delay(2000);

  backlightOFF();// Hide the Screen while drawing
  tft.fillScreen(GC9A01A_BLACK);
  tft.setFont(); // Set Default Adafruit GRFX Font

}


void next_display() {

  tft.fillRoundRect  (16,  25, 82,  82, 3,    GC9A01A_BLACK);

  tft.drawBitmap(18, 34, nextscreen64_BMP, 79, 64, GC9A01A_RED);
  //tft.drawBitmap(18, 34, nextscreen2_64_BMP, 79, 64, GC9A01A_RED);
  delay(500);
  //tft.drawBitmap(18, 34, nextscreen64_BMP, 79, 64, GC9A01A_BLACK);
  //tft.drawBitmap(18, 34, nextscreen2_64_BMP, 79, 64, GC9A01A_BLACK);

}

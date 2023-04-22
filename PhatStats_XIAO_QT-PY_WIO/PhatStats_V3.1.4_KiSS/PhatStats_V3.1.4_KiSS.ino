#define CODE_VERS  "3.1.4.KiSS"  // Code version number

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
  ------------------------------------------------
  Adafruit BusIO            v1.14.0 (Current 04/2023
  Adafruit_GFX              v1.11.5 (Current 04/2023)
  Adafruit_NeoPixel         v1.11.0 (Current 04/2023)
  Adafruit ILI9341          v1.5.12 (Current 04/2023)
  

  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
               SEE CONFIGURATION TAB FIRST, FOR QUICK SETTINGS!!!!
  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
*/


#include <Wire.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Fonts/Org_01.h>
#include <Adafruit_ILI9341.h>  // v1.5.6 Adafruit Standard

#include "Configuration_Settings.h" // load settings
#include "Z_Bitmaps.h"

#ifdef Seeeduino_WIO_ATSAMD51
//Wio Terminal LCD back light brightness
#include "lcd_backlight.hpp"
#include <cstdint>
#endif

/* Declare Prototype voids to the compiler*/
void Display_LS      ();
void Display_Port    ();
void Display_LS_180  ();
void Display_Port_180();
void button_Modes    ();
void serialEvent     ();
void activityChecker ();
void splashScreen    ();
void backlightON ();
void backlightOFF();

/*
  eBay Special Red PCB pinouts VCC(3.3v), GND, CS, RST, D/C, MOSI, SCK, BL, (MISO, T_CLK, T_CS, T_DIN, T_DO, T_IRQ)

  ILI9341 SPI TFT Adafruit QT-PY / XIAO
  --------------------------------------

  CS     =  5  or D5
  RST    =  0  or D0 or D9 (Use D9 for XIAO_ESP32C3 or old PCB Version)
  DC     =  7  or D7
  SCLK   =  8  or D8
  MOSI   =  10 Or D10

  B.LIGHT             = 4
  Screen Mode Button  = 1


  Onboard LED's
  --------------
  XIAO  (NRF52840)         Built in LED      = 11     (*Not Required for Reference only!!!)
  XIAO  (RP2040)           Built in LED      = 25     (*Not Required for Reference only!!!)
  XIAO  (ATSAMD21)         Built in LED      = 13     (*Not Required for Reference only!!!)
  WIO Terminal (ATSAMD51)  Build in LED      = 13

  QT-PY (ATSAMD21) Built in Neopixel =  11 or (12 to turn it off) (*Not Required for Reference only!!!)

  ==========================================================================================================

  Seeed Studio WIO Terminal
  -------------------------
  (TFT)
  CS      = LCD_SS_PIN
  RST     = LCD_RESET
  DC      = LCD_DC
  SCLK    = LCD_SCK_PIN
  MOSI    = LCD_MOSI_PIN

  B.LIGHT = LCD_BACKLIGHT
  ---------------------

  Buttons
  -------
  Screen Mode Button = WIO_5S_PRESS (WIO JoyPad Button)

  LED's
  -----
  WIO TERMINAL  Built in LED =  13 or LED_BUILTIN

  ==========================================================================================================

*/
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ Hidden in Main Sketch for KiSS   $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$

//------------------------------- Display Activity Shutdown -----------------------------------

/* Uncomment below to turn off the screen on serial timeout, else keep last display info eg: incase of PC Crash*/
#define enableActivityChecker

/* How long the display takes to timeout due to inactive serial data from the windows application */
#define lastActiveDelay 8000


/* Debounce  Button, button mode is a bit flaky at present as it needs interrupts, Sometimes it gets caught during a screen refresh
  and does not change. WIO Terminal & ESP32 seem to like 1000ms and works just!!! ok */

int debounceButton = 150; //  Use a 0.1uf/100nf/(104) ceramic capacitor from button Pin to GND

/* Enable the built in LED blinking when transmitting data,*/
//#define enableTX_LED

int TX_LED_Delay = 0; // TX blink delay, lags button

int baudRate     = 9600; // set serial baud rate to match that of HardwareSerialMonitor 115200 will use more resources

/* Delay screen event, to stop screen data corruption ESP8622 use 25, most others 5 will do*/
int Serial_eventDelay = 5; //

//#define  splashScreenLS // quick splash screen landscape hack job, also in FeatureSet

/* CPU is overclocked with Turbo boost disabled, to stop "TURBO" indicator,*/
//#define CPU_OverClocked

#define noDegree      // lose the "o"
#define smallPercent  // Use small percent symbol

//----------------------------- Frequency Gains Indicator --------------------------------

/* Uncomment to enable the display of frequency gains */
#define enable_ShowFrequencyGain

/* Uncomment only one of the units to display below, MHz or Percent */
//#define ShowFrequencyGainMHz        // Show Overlock/Turbo & Boost Clock Frequency Gains in MHZ  eg: "+24MHz"
#define ShowFrequencyGainPerc       // Show Overlock/Turbo & Boost Clock Frequency Gains in Percent  eg: "+24%"

//----------------------------- Throttle/Boost Indicator --------------------------------

#define enable_ThrottleIndicator // Show TJMax Indicator 
#define enable_BoostIndicator    // Show CPU & GPU Turbo/Boost Indicator

//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$




#if defined(Seeeduino_XIAO_ATSAMD) ^ defined(Seeeduino_WIO_ATSAMD51)
/*onboard WIO/XIAO BUILD in LED for TX*/
#define TX_LEDPin   13
#endif

#ifdef Seeeduino_XIAO_RP2040
/*onboard XIAO BUILD in LED for TX*/
#define TX_LEDPin   25
#endif


#ifdef Seeeduino_XIAO_NRF52840
/*onboard XIAO BUILD in LED for TX*/
#define TX_LEDPin   11
#endif



//----------------------------------------------------------------------------
/* ILI9321 TFT setup */
//----------------------------------------------------------------------------


#if defined(Seeeduino_XIAO_RP2040) ^ defined(Seeeduino_XIAO_ESP32C3)

#define TFT_CS     D5
#define TFT_DC     D7

#ifdef  ALT_TFT_RST
#define TFT_RST    D9  // ESP32C3 & OLD PCB V0.93(Use D9 for XIAO_ESP32C3 or old PCB Version)
#else
#define TFT_RST    D0  // changed from previous(9) to allow for MISO connection for Touch
#endif

#define TFT_SCLK   D8
#define TFT_MOSI   D10


Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST); // Use hardware SPI
#endif

//--------------------------------------------------
#if defined(Seeeduino_XIAO_ATSAMD) ^ defined(Adafruit_QTPY_ATSAMD) ^ defined(Seeeduino_XIAO_NRF52840)

#define TFT_CS     5
#define TFT_DC     7

#ifdef  ALT_TFT_RST
#define TFT_RST    9  // ESP32C3 & OLD PCB V0.93
#else
#define TFT_RST    0  // changed from previous(9) to allow for MISO connection for Touch
#endif

#define TFT_SCLK   8
#define TFT_MOSI   10

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST); // Use hardware SPI
#endif

//--------------------------------------------------

#ifdef Seeeduino_WIO_ATSAMD51

#define LCD_SPI SPI3
#define TFT_CS       LCD_SS_PIN
#define TFT_DC       LCD_DC
#define TFT_MOSI     LCD_MOSI_PIN
#define TFT_CLK      LCD_SCK_PIN
#define TFT_RST      LCD_RESET
#define TFT_MISO     LCD_MISO_PIN

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST, TFT_MISO);

#endif
//-----------------------------------------------------------------------------



#if defined(Seeeduino_XIAO_RP2040) ^ defined(Seeeduino_XIAO_ESP32C3)
/* Mode Button pin*/
int mode_Button       = D1;
/* Screen TFT backlight Pin */
int TFT_backlight_PIN = D4;
#endif

#ifdef Seeeduino_WIO_ATSAMD51
/*Button pin*/
int mode_Button       = WIO_5S_PRESS; // (WIO JoyPad Button)
/* Screen TFT backlight Pin */
int TFT_backlight_PIN = LCD_BACKLIGHT;
#endif

#if defined(Seeeduino_XIAO_ATSAMD) ^ defined(Adafruit_QTPY_ATSAMD) ^ defined(Seeeduino_XIAO_NRF52840)
/* Mode Button pin*/
int mode_Button       = 1;
/* Screen TFT backlight Pin */
int TFT_backlight_PIN = 4;
#endif



//-----------------------------------------------------------------------------

/* Button Counter */
int display_Button_counter = 0;

/*XIAO TFT Brightness*/
int brightness_countLast = 0;   // Store Last PWM Value

#ifdef Seeeduino_WIO_ATSAMD51
/* WioTerminal_Backlight library */
static LCDBackLight backLight;
#endif

/* More Display stuff*/
int displayDraw = 0;

/* Display screen rotation  0, 1, 2 or 3 = (0, 90, 180 or 270 degrees)*/
int ASPECT = 0; //Do not adjust,


//-----------------------------------------------------------------------------

/* Timer for active connection to host*/
boolean activeConn = false;
long lastActiveConn = 0;
boolean bootMode = true;

/* Vars for serial input*/
String inputString = "";
boolean stringComplete = false;

//-----------------------------  TFT Colours  ---------------------------------

#define ILI9341_TEST        0x6A4E
#define ILI9341_BLACK       0x0000
#define ILI9341_WHITE       0xFFFF
#define ILI9341_GREY        0x7BEF
#define ILI9341_LIGHT_GREY  0xC618
#define ILI9341_GREEN       0x07E0
#define ILI9341_LIME        0x87E0
#define ILI9341_BLUE        0x001F
#define ILI9341_RED         0xF800
#define ILI9341_AQUA        0x5D1C
#define ILI9341_YELLOW      0xFFE0
#define ILI9341_MAGENTA     0xF81F
#define ILI9341_CYAN        0x07FF
#define ILI9341_DARK_CYAN   0x03EF
#define ILI9341_ORANGE      0xFCA0
#define ILI9341_PINK        0xF97F
#define ILI9341_BROWN       0x8200
#define ILI9341_VIOLET      0x9199
#define ILI9341_SILVER      0xA510
#define ILI9341_GOLD        0xA508
#define ILI9341_NAVY        0x000F
#define ILI9341_MAROON      0x7800
#define ILI9341_PURPLE      0x780F
#define ILI9341_OLIVE       0x7BE0


//------------------------- CRT Style Colour Profiles ----------------------

#ifdef  RETRO_MONO
#define ILI9341_YELLOW      0xFFFF //ILI9341_WHITE
#define ILI9341_WHITE       0xFFFF //ILI9341_WHITE
#define ILI9341_BLUE        0xA510 //ILI9341_SILVER 
#define ILI9341_GREEN       0x7BEF //ILI9341_GREY 
#define ILI9341_RED         0xC618 //ILI9341_LIGHT_GREY
//--
#define ILI9341_SILVER      0xA510 //ILI9341_SILVER
#define ILI9341_GREY        0x7BEF //ILI9341_GREY 
#define ILI9341_LIGHT_GREY  0xC618 //ILI9341_LIGHT_GREY
#endif


//--------------------------------

void setup() {

  Serial.begin(baudRate);
  /* String Buffer */
  inputString.reserve(220);

#ifdef Seeeduino_WIO_ATSAMD51
  /* WioTerminal_Backlight library */
  backLight.initialize();
#endif

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



  /* TFT SETUP */

  /*Give the micro time to initiate the SPi bus*/
  delay(100);
  tft.begin();

  tft.setRotation(ASPECT);// Rotate the display :  0, 1, 2 or 3 = (0, 90, 180 or 270 degrees)

  /* stops text wrapping*/
  tft.setTextWrap(false); // Stop  "Loads/Temps" wrapping and corrupting static characters

  /* Clear Screen*/
  tft.fillScreen(ILI9341_BLACK);
  tft.setTextColor(ILI9341_WHITE);

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

    /* Set Default Adafruit GRFX Font*/
    tft.setFont();

    tft.fillScreen(ILI9341_BLACK);

    tft.setRotation(0);// Rotate the display at the start:  0, 1, 2 or 3 = (0, 90, 180 or 270 degrees)
    //tft.drawRoundRect  (0, 0  , 240, 320, 8,    ILI9341_RED);
    tft.setTextColor(ILI9341_RED);

    tft.setRotation(2);// Rotate the display at the start:  0, 1, 2 or 3 = (0, 90, 180 or 270 degrees)
    tft.drawBitmap(82, 80, WaitingDataBMP2_90, 76, 154, ILI9341_RED);
    tft.setTextSize(2); tft.setCursor(40, 40); tft.println("NO COM DATA!!!");

    delay(1000);

    /* Clear Screen, Turn Off Backlight & Neopixels when there is no activity, */

    //tft.invertDisplay(0);
    backlightOFF ();
    tft.fillScreen(ILI9341_BLACK);

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

#ifdef Seeeduino_WIO_ATSAMD51
  /* WioTerminal_Backlight library */
  backLight.setBrightness(brightness_count); // TFT turn on backlight, WioTerminal_Backlight library
#endif
}
void backlightOFF () {
  analogWrite(TFT_backlight_PIN, 0);        // TFT turn off backlight,

#ifdef Seeeduino_WIO_ATSAMD51
  /* WioTerminal_Backlight library */
  backLight.setBrightness(0); // TFT turn off backlight,  WioTerminal_Backlight library
#endif

}
#endif

//----------------------------- Splash Screens --------------------------------
void splashScreen() {

  /* Initial Boot Screen, */

  tft.setRotation(2);// Rotate the display at the start:  0, 1, 2 or 3 = (0, 90, 180 or 270 degrees)

  tft.setFont(&Org_01);
  tft.fillScreen(ILI9341_BLACK);

  //tft.drawRoundRect  (0, 0  , 240, 320, 8,    ILI9341_RED);

#ifdef splashScreenLS // Quick landscape hack job, also in FeatureSet
  tft.setRotation(3);// Rotate the display at the start:  0, 1, 2 or 3 = (0, 90, 180 or 270 degrees)
#endif

  tft.drawBitmap(44, 20, HSM_BG_BMP,  142, 128, ILI9341_WHITE);
  tft.drawBitmap(44, 20, HSM_BG2_BMP, 142, 128, ILI9341_RED);
  tft.drawBitmap(44, 20, HSM_BMP,     142, 128, ILI9341_GREY);

  tft.setTextSize(3);
  tft.setCursor(86, 140);
  tft.setTextColor(ILI9341_WHITE);
  tft.println("PHAT ");
  tft.setTextSize(3);
  tft.setCursor(78, 160);
  tft.println("STATS");

  tft.setTextSize(2);
  tft.setCursor(22, 190);
  tft.setTextColor(ILI9341_SILVER);
  tft.print("PC Hardware Monitor");

  tft.setTextSize(3);
  tft.setCursor(22, 219);
  tft.setTextColor(ILI9341_RED);
  tft.print("tallmanlabs.com");

  //------------------------------------------------------------------

#ifdef splashScreenLS

  /*  Baud Rate */
  tft.setFont(); // Set Default Adafruit GRFX Font
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(1);
  tft.setCursor(140 - 130, 12);
  tft.print("Baud: ");
  tft.print (baudRate);
  tft.print(" bps ");

  /* Set version */
  tft.setFont(); // Set Default Adafruit GRFX Font
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(1);
  tft.setCursor(140 - 130, 3);
  tft.print("TFT: v");
  tft.print (CODE_VERS);

#else

  /*  Baud Rate */
  tft.setFont(); // Set Default Adafruit GRFX Font
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(1);
  tft.setCursor(110, 288);
  tft.print("Baud: ");
  tft.print (baudRate);
  tft.print(" bps ");

  /* Set version */
  tft.setFont(); // Set Default Adafruit GRFX Font
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(1);
  tft.setCursor(110, 300);
  tft.print("TFT: v");
  tft.print (CODE_VERS);

#endif

  //----------------------------------------------------------------
  tft.setTextColor(ILI9341_WHITE);
  tft.setFont(); // Set Default Adafruit GRFX Font

  backlightON();
  //FeatureSet_Indicator2(); // Display Icons for enabled features

  delay(1000);
backlightOFF();// Hide the Screen while drawing

  /**/

    #ifdef splashScreenLS // Quick landscape hack job, also in FeatureSet
    #ifdef Seeeduino_WIO_ATSAMD51
    tft.setRotation(3);// Rotate the display at the start:  0, 1, 2 or 3 = (0, 90, 180 or 270 degrees)
    tft.fillScreen(ILI9341_BLACK);
    //tft.drawRoundRect  (0, 0  , 240, 320, 8,    ILI9341_RED);
    tft.drawBitmap(120, 26, WaitingDataBMP_USB, 76, 190, ILI9341_RED);
    backlightON();

    #else

    tft.setRotation(0);// Rotate the display at the start:  0, 1, 2 or 3 = (0, 90, 180 or 270 degrees)
    tft.fillScreen(ILI9341_BLACK);
    //tft.drawRoundRect  (0, 0  , 240, 320, 8,    ILI9341_RED);
    tft.drawBitmap(82, 62, WaitingDataBMP_USB, 76, 190, ILI9341_RED);
    backlightON();
    #endif
    #endif

    delay(2000);
  
  
  backlightOFF();// Hide the Screen while drawing
  tft.fillScreen(ILI9341_BLACK);

}

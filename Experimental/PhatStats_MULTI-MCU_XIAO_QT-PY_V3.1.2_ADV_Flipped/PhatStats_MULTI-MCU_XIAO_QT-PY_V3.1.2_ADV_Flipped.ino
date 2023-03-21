#define CODE_VERS  "3.1.2.ADV"  // Code version number


/*
  uVolume, GNATSTATS OLED, PHATSTATS TFT PC Performance Monitor & HardwareSerialMonitor Windows Client
  Rupert Hirst & Colin Conway © 2016 - 2021
  http://tallmanlabs.com
  http://runawaybrainz.blogspot.com/

  Licence
  --------
  GPL v2

  This Sketch Requires HardwareSerialMonitor v1.3 or higher

  Board Manager QY-PY
  -------------------
  Click on File > Preference, and fill Additional Boards Manager URLs with the url below:
  Install Arduino ATSAMD then ADD
  https://adafruit.github.io/arduino-board-index/package_adafruit_index.json

  Drivers
  ------------
  https://github.com/adafruit/Adafruit_Windows_Drivers/releases/tag/2.5.0.0


  Board Manager XIAO
  -------------------
  https://wiki.seeedstudio.com/Seeeduino-XIAO/

  Click on File > Preference, and fill Additional Boards Manager URLs with the url below:

  XIAO ATSAMD21
  -------------
  https://files.seeedstudio.com/arduino/package_seeeduino_boards_index.json

  XIAO NRF52840
  -------------
  https://files.seeedstudio.com/arduino/package_seeeduino_boards_index.json

  XIAO RP2040
  -----------
  https://github.com/earlephilhower/arduino-pico/releases/download/global/package_rp2040_index.json

  XIAO ESP32C3
  -----------
  https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_dev_index.json


  Libraries
  ---------
  Adafruit Neopixel
  https://github.com/adafruit/Adafruit_NeoPixel

  Adafruit GFX Library
  https://github.com/adafruit/Adafruit-GFX-Library

  Adafruit ILI9341
  https://github.com/adafruit/Adafruit_ILI9341



  Hookup Guide
  https://runawaybrainz.blogspot.com/2021/03/phat-stats-ili9341-tft-display-hook-up.html

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


/*
  eBay Special Red PCB pinouts VCC(3.3v), GND, CS, RST, D/C, MOSI, SCK, BL, (MISO, T_CLK, T_CS, T_DIN, T_DO, T_IRQ)

  Adafruit QT-PY / XIAO
  ---------------------
  (TFT)
  CS     =  5
  RST    =  0
  DC     =  7
  SCLK   =  8
  MOSI   =  10

  B.LIGHT             = 4
  Screen Mode Button  = 1
  NeoPixel            = 6

  Onboard LED's
  --------------
  XIAO  (NRF52840) Built in LED      =  11     (*Not Required for Reference only!!!)
  XIAO  (RP2040)   Built in LED      =  25     (*Not Required for Reference only!!!)
  XIAO  (ATSAMD21) Built in LED      =  13     (*Not Required for Reference only!!!)
  QT-PY (ATSAMD21) Built in LED      =         (None on the QT-PY)
  
  QT-PY (ATSAMD21) Built in Neopixel =  11 or (12 to turn it off) (*Not Required for Reference only!!!)

  ==========================================================================================================
*/


//---------------------------------------------------------------------------------------


#include <Adafruit_NeoPixel.h>

#if defined(Seeeduino_XIAO_ATSAMD) ^ defined(Adafruit_QTPY_ATSAMD) ^ defined(Seeeduino_XIAO_NRF52840)
#define NEOPIN      6
#endif

#if defined(Seeeduino_XIAO_RP2040) ^ defined(Seeeduino_XIAO_ESP32C3)
#define NEOPIN      D6
#endif

#define NUM_PIXELS  16


#ifdef Seeeduino_XIAO_ATSAMD
/*onboard XIAO BUILD in LED for TX*/
#define TX_LEDPin   13
#endif


#ifdef Seeeduino_XIAO_RP2040
/*onboard XIAO BUILD in LED for TX*/
#define TX_LEDPin   25
#endif


#ifdef Adafruit_QTPY_ATSAMD
/*onboard QT-PY NeoPixel for TX*/
#define TX_NeoPin   11  //
#endif

#ifdef Seeeduino_XIAO_NRF52840
/*onboard XIAO BUILD in LED for TX*/
#define TX_LEDPin   11
#endif

#ifdef Adafruit_QTPY_ATSAMD
Adafruit_NeoPixel TX_pixel(1, TX_NeoPin, NEO_GRB + NEO_KHZ800);
#endif

Adafruit_NeoPixel pixels(NUM_PIXELS, NEOPIN, NEO_GRB + NEO_KHZ800);



/* Pre-define Hex NeoPixel colours,  eg. pixels.setPixelColor(0, BLUE); https://htmlcolorcodes.com/color-names/ */
#define BLUE       0x0000FF
#define GREEN      0x008000
#define RED        0xFF0000
#define ORANGE     0xFFA500
#define DARKORANGE 0xFF8C00
#define YELLOW     0xFFFF00
#define WHITE      0xFFFFFF
#define BLACK      0x000000 // OFF


//----------------------------------------------------------------------------

/* ILI9321 TFT setup */

//----------------------------------------------------------------------------


#if defined(Seeeduino_XIAO_RP2040) ^ defined(Seeeduino_XIAO_ESP32C3)
//----------------------------------------------------------------------------
/* RP2040 SPi Hardware only for speed*/
#define TFT_CS     D5
#define TFT_DC     D7
#define TFT_RST    D0  // changed from previous(9) to allow for MISO connection for Touch

#ifdef  OLDPCB_V0_93

#define TFT_RST    D9  // OLDPCB_V0_93
#else
#define TFT_RST    D0  // changed from previous(9) to allow for MISO connection for Touch
#endif

/* These pins do not have to be defined as they are hardware pins
  Connect TFT_SCLK to pin   D8
  Connect TFT_MOSI to pin   D10
*/
#endif


//--------------------------------------------------
#if defined(Seeeduino_XIAO_ATSAMD) ^ defined(Adafruit_QTPY_ATSAMD) ^ defined(Seeeduino_XIAO_NRF52840)
/* ATSAMD21 SPi Hardware only for speed*/
#define TFT_CS     5
#define TFT_DC     7
#define TFT_RST    0 // changed from previous(9) to allow for MISO connection for Touch

#ifdef  OLDPCB_V0_93

#define TFT_RST    9  // OLDPCB_V0_93
#else
#define TFT_RST    0  // changed from previous(9) to allow for MISO connection for Touch
#endif

/* These pins do not have to be defined as they are hardware pins
  Connect TFT_SCLK to pin   8
  Connect TFT_MOSI to pin   10
*/

#endif

//-----------------------------------------------------------------------------

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST); // Use hardware SPI

//-----------------------------------------------------------------------------

#if defined(Seeeduino_XIAO_ATSAMD) ^ defined(Adafruit_QTPY_ATSAMD) ^ defined(Seeeduino_XIAO_NRF52840)

/* Mode Button pin*/
int mode_Button       = 1;

/* Screen TFT backlight Pin */
int TFT_backlight_PIN = 4;
#endif

//----------------------------

#if defined(Seeeduino_XIAO_RP2040) ^ defined(Seeeduino_XIAO_ESP32C3)

/* Mode Button pin*/
int mode_Button       = D1;
/* Screen TFT backlight Pin */
int TFT_backlight_PIN = D4;

#endif


int display_Button_counter = 0;


//-----------------------------------------------------------------------------

/*TFT Brightness*/

int brightness_countLast    = 0;   // Store Last PWM Value

/* Display screen rotation  0, 1, 2 or 3 = (0, 90, 180 or 270 degrees)*/
int ASPECT = 0; //Do not adjust,

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
//--------------------------------

void setup() {



  Serial.begin(baudRate);  //  USB Serial Baud Rate
  //Serial.begin(9600);  //  USB Serial Baud Rate
  //Serial.begin(115200);  //  USB Serial Baud Rate

  inputString.reserve(200); // String Buffer

  /* Set up PINs*/
  pinMode(mode_Button, INPUT_PULLUP);
  pinMode(TFT_backlight_PIN, OUTPUT); // declare backlight pin to be an output:

  /* Set up the NeoPixel*/
  pixels.begin();    // This initializes the NeoPixel library.

#ifdef Seeeduino_XIAO_ATSAMD
#ifdef enableTX_LED
  pinMode(TX_LEDPin, OUTPUT); //  Builtin LED /  HIGH(OFF) LOW (ON)
#endif
#endif


#ifdef Adafruit_QTPY_ATSAMD
#ifdef enableTX_LED
  TX_pixel.begin();  // This initializes the library for the Built in NeoPixel.
#endif
#endif


#ifdef Seeeduino_XIAO_RP2040
#ifdef enableTX_LED
  pinMode(TX_LEDPin, OUTPUT); //  Builtin LED /  HIGH(OFF) LOW (ON)
#endif
#endif

#ifdef Seeeduino_XIAO_NRF52840
#ifdef enableTX_LED
  pinMode(TX_LEDPin, OUTPUT); //  Builtin LED /  HIGH(OFF) LOW (ON)
#endif
#endif


  pixels.setBrightness(NeoBrightness); // Atmel Global Brightness (does not work for STM32!!!!)
  pixels.show(); // Turn off all Pixels


  backlightOFF();

  /* TFT SETUP */

  delay(1000); // Give the micro time to initiate the SPi bus
  tft.begin(); //ILI9341


  tft.setRotation(ASPECT);// Rotate the display :  0, 1, 2 or 3 = (0, 90, 180 or 270 degrees)

  /* stops text wrapping*/
  tft.setTextWrap(false); // Stop  "Loads/Temps" wrapping and corrupting static characters

  /* Clear Screen*/
  tft.fillScreen(ILI9341_BLACK);
  tft.setTextColor(ILI9341_WHITE);

  splashScreen();


}

/* End of Set up */

void loop() {

  serialEvent();          // Check for Serial Activity

#ifdef  enableActivityChecker
  activityChecker();      // Turn off screen when no activity
#endif

#ifdef Seeeduino_XIAO_ATSAMD
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

#ifdef Adafruit_QTPY_ATSAMD
#ifdef enableTX_LED
  /* Serial Activity NeoPixel */
  TX_pixel.setPixelColor(0, 0, 0, 0 ); // turn built in NeoPixel Off
  TX_pixel.show();
#endif
#endif

#ifdef Seeeduino_XIAO_NRF52840
  /*Serial Activity LED */
#ifdef enableTX_LED
  pinMode(TX_LEDPin, HIGH); //  Builtin LED /  HIGH(OFF) LOW (ON)
#endif
#endif


  //-----------------------------

  /* Mode Button, moved to its own tab*/
  button_Modes();

}

/* END of Main Loop */


//-----------------------------  NeoPixels  -----------------------------------
void allNeoPixelsOff() {
  for ( int i = 0; i < NUM_PIXELS; i++ ) {
    pixels.setPixelColor(i, 0, 0, 0 );
  }
  pixels.show();
}

void allNeoPixelsRED() {
  for ( int i = 0; i < NUM_PIXELS; i++ ) {
    pixels.setPixelColor(i, 255, 0, 0 );
  }
  pixels.show();
}
//-----------------------------  Serial Events -------------------------------
/*
  SerialEvent occurs whenever a new data comes in the hardware serial RX. This
  routine is run between each time loop() runs, so using delay inside loop can
  delay response. Multiple bytes of data may be available.
*/
void serialEvent() {

  while (Serial.available()) {
    //while (Serial.available() > 0) {
    // get the new byte:
    char inChar = (char)Serial.read();
    //Serial.print(inChar); // Debug Incoming Serial

    // add it to the inputString:
    inputString += inChar;
    // if the incoming character has '|' in it, set a flag so the main loop can do something about it:
    if (inChar == '|') {
      stringComplete = true;

      delay(Serial_eventDelay);   //delay screen event to stop screen data corruption

#ifdef enableTX_LED

      /* Serial Activity LED */
#ifdef Seeeduino_XIAO_ATSAMD
      digitalWrite(TX_LEDPin, LOW);   // turn the LED off HIGH(OFF) LOW (ON)
#endif
#endif

#ifdef Seeeduino_XIAO_RP2040
#ifdef enableTX_LED
      //USER LED GREEN
      digitalWrite(TX_LEDPin, LOW);   // turn the LED off HIGH(OFF) LOW (ON)
#endif
#endif

#ifdef enableTX_LED
#ifdef Adafruit_QTPY_ATSAMD
      TX_pixel.setPixelColor(0, 10, 0, 0 ); // turn built in NeoPixel on
      TX_pixel.show();
#endif
#endif

#ifdef enableTX_LED
      /* Serial Activity LED */
#ifdef Seeeduino_XIAO_NRF52840
      digitalWrite(TX_LEDPin, LOW);   // turn the LED off HIGH(OFF) LOW (ON)
#endif
#endif

      delay(TX_LED_Delay); // TX blink delay

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

    /* Turn off display when there is no activity, */
    backlightOFF ();

    //if (invertedStatus)

    //Turn off NeoPixel when there is no activity
    allNeoPixelsOff();
    /* Set Default Adafruit GRFX Font*/
    tft.setFont();

    tft.fillScreen(ILI9341_BLACK);


    tft.setRotation(0);// Rotate the display at the start:  0, 1, 2 or 3 = (0, 90, 180 or 270 degrees)
    tft.drawRoundRect  (0, 0  , 240, 320, 8,    ILI9341_RED);
    tft.setTextColor(ILI9341_RED);
    tft.drawBitmap(82, 80, WaitingDataBMP2_90, 76, 154, ILI9341_RED);
    tft.setTextSize(2); tft.setCursor(40, 40); tft.println("NO COM DATA!!!");
    delay(2000);

    //Turn off display when there is no activity
    //tft.invertDisplay(0);
    displayDraw = 0;

    /* Clear Screen & Turn Off Backlight, */
    tft.fillScreen(ILI9341_BLACK);
    backlightOFF ();
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
#else
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

  allNeoPixelsOff();

  tft.setRotation(0);// Rotate the display at the start:  0, 1, 2 or 3 = (0, 90, 180 or 270 degrees)

  tft.setFont(&Org_01);
  tft.fillScreen(ILI9341_BLACK);
  tft.drawRoundRect  (0, 0  , 240, 320, 8,    ILI9341_RED);

#ifdef splashScreenLS // Quick landscape hack job, also in FeatureSet
  tft.setRotation(3);// Rotate the display at the start:  0, 1, 2 or 3 = (0, 90, 180 or 270 degrees)
#endif

  //tft.drawBitmap(84, 56, JustGnatBMP, 64, 64, ILI9341_YELLOW);

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

  tft.setTextColor(ILI9341_WHITE);
  tft.setFont(); // Set Default Adafruit GRFX Font

  backlightON();

  FeatureSet_Indicator2(); // Display Icons for enabled features

  delay(6000);

#ifdef enableNeopixelGauges

  allNeoPixelsRED();

#endif

#ifdef splashScreenLS // Quick landscape hack job, also in FeatureSet
  tft.setRotation(0);// Rotate the display at the start:  0, 1, 2 or 3 = (0, 90, 180 or 270 degrees)
#endif

  tft.fillScreen(ILI9341_BLACK);

  tft.drawRoundRect  (0, 0  , 240, 320, 8,    ILI9341_RED);
  tft.drawBitmap(82, 62, WaitingDataBMP_USB, 76, 190, ILI9341_RED);

  delay(3000);

}

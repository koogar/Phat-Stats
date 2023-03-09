#define CODE_VERS  "3.1.0.KiSS"  // Code version number


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
  https://files.seeedstudio.com/arduino/package_seeeduino_boards_index.json

  Libraries
  ---------

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


#include "Configuration_Settings.h" // load settings
#include "Z_Bitmaps.h"


/*
  eBay Special Red PCB pinouts VCC(3.3v), GND, CS, RST, D/C, MOSI, SCK, BL, (MISO, T_CLK, T_CS, T_DIN, T_DO, T_IRQ)

  Adafruit QT-PY / XIAO
  ---------------------
  ATSAMD21G18 @ 48MHz with 3.3V logic/power
  256KB of FLASH + 32KB of RAM
  ---------------------
  (TFT)
  CS     =  5
  RST    =  0
  DC     =  7
  SCLK   =  8
  MOSI   =  10


  B.LIGHT =  4
  ---------------------

  Screen Mode Button      = 1


  Neopixel / LED's
  ---------------------
  XIAO Built in LED       =  13  None on the QT-PY     (*Not Required for Reference only!!!)
  QT-PY Built in Neopixel =  11 or (12 to turn it off) (*Not Required for Reference only!!!)

  NeoPixel         =  6
  ==========================================================================================================
*/


//---------------------------------------------------------------------------------------


/*onboard XIAO BUILD in LED for TX*/
#ifdef Seeeduino_XIAO
#define TX_LEDPin 13
#endif


//----------------------------------------------------------------------------

/* ILI9321 TFT setup */
#include <Adafruit_ILI9341.h>  // v1.5.6 Adafruit Standard

/* ATSAMD21 SPi Hardware only for speed*/
#define TFT_CS     5
#define TFT_DC     7
#define TFT_RST    0 // changed from previous(9) to allow for MISO connection for Touch


/* These pins do not have to be defined as they are hardware pins
  Connect TFT_SCLK to pin   8
  Connect TFT_MOSI to pin   10
*/


Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST); // Use hardware SPI

//-----------------------------------------------------------------------------


/* Encoder Button pin*/
int mode_Button     = 1;
int display_Button_counter = 0;

/* Screen TFT backlight Pin */
int TFT_backlight_PIN =  4;

/*TFT Brightness*/

int brightness_countLast      = 0;   // Store Last PWM Value

//-----------------------------------------------------------------------------

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

  //Serial.begin(9600);  //  USB Serial Baud Rate
  Serial.begin(115200);  //  USB Serial Baud Rate
  inputString.reserve(200); // String Buffer


  /* Set up PINs*/
  pinMode(mode_Button, INPUT_PULLUP);
  pinMode(TFT_backlight_PIN, OUTPUT); // declare backlight pin to be an output:

#ifdef enableTX_LED

#ifdef Seeeduino_XIAO
#ifdef enableTX_LED
  pinMode(TX_LEDPin, OUTPUT); //  Builtin LED /  HIGH(OFF) LOW (ON)
#endif
#endif
#endif
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


#ifdef enableTX_LED
  /*Serial Activity LED */
#ifdef Seeeduino_XIAO
  digitalWrite(TX_LEDPin, HIGH);    // turn the LED off HIGH(OFF) LOW (ON)
#endif
#endif


  //-----------------------------

  /* Mode Button, moved to its own tab*/
  button_Modes();

}

/* END of Main Loop */




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
#ifdef Seeeduino_XIAO
      digitalWrite(TX_LEDPin, LOW);   // turn the LED off HIGH(OFF) LOW (ON)
#endif
#endif


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

  delay(6000);

#ifdef splashScreenLS // Quick landscape hack job, also in FeatureSet
  tft.setRotation(0);// Rotate the display at the start:  0, 1, 2 or 3 = (0, 90, 180 or 270 degrees)
#endif

  tft.fillScreen(ILI9341_BLACK);

  tft.drawRoundRect  (0, 0  , 240, 320, 8,    ILI9341_RED);
  tft.drawBitmap(82, 62, WaitingDataBMP_USB, 76, 190, ILI9341_RED);

  delay(3000);

}

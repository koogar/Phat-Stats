
#define CODE_VERS  "3.1.6.BT.ADV"  // Code version number

/*
  uVolume, GNATSTATS OLED, PHATSTATS TFT PC Performance Monitor & HardwareSerialMonitor Windows Client
  Rupert Hirst © 2016 - 2023 http://tallmanlabs.com http://runawaybrainz.blogspot.com/
  https://github.com/koogar/Phat-Stats  https://hackaday.io/project/19018-phat-stats-pc-performance-tft-display


  WARNING!!!last successful compile espressif v2.0.5
  if your compile fails (analogWriteResolution) uninstall in the IDE boards manager down to the above version
  https://github.com/espressif/arduino-esp32/blob/master/docs/arduino-ide/boards_manager.md

  Board Manager ESP32
  -------------------
  Click on File > Preference, and fill Additional Boards Manager URLs with the url below:
  https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json



  Libraries
  ---------
  Adafruit Neopixel
  https://github.com/adafruit/Adafruit_NeoPixel

  Adafruit GFX Library
  https://github.com/adafruit/Adafruit-GFX-Library

  Adafruit ILI9341
  https://github.com/adafruit/Adafruit_ILI9341

  Rotary encoder
  https://github.com/koogar/ErriezRotaryEncoderFullStep


  WARNING!!!last successful compile espressif v2.0.5
  if your compile fails (analogWriteResolution) uninstall in the IDE boards manager down to the above version

  ESP32 analogueWrite Function
  https://github.com/ERROPiX/ESP32_AnalogWrite

  Battery Monitor by Alberto Iriberri Andrés
  https://github.com/pangodream/18650CL

  Hookup Guide
  https://runawaybrainz.blogspot.com/2021/03/phat-stats-ili9341-tft-display-hook-up.html



  Library Working Version Checker 18/04/2023
  (some libraries may not be used in this sketch)
  ------------------------------------------------
  Arduino IDE          v1.8.19
  espressif (ESP32)    v2.0.5 (v2.08 = ESP32_AnalogWrite compile error)
  ------------------------------------------------
  ESP32_AnalogWrite    v0.2    (Current 04/2023)
  Adafruit BusIO       v1.14.0 (Current 04/2023
  Adafruit_GFX         v1.11.5 (Current 04/2023)
  Adafruit_NeoPixel    v1.11.0 (Current 04/2023)
  Adafruit ILI9341     v1.5.12 (Current 04/2023)
  Adafruit SH110X      v2.1.8  (Current 04/2023)
  Adafruit SD1306      v2.5.7  (Current 04/2023)
  HID-Project          v2.8.4  (Current 04/2023)
  IRremote             v4.1.2  (Current 04/2023)


  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
               SEE CONFIGURATION TAB FIRST, FOR QUICK SETTINGS!!!!
  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
*/



#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Fonts/Org_01.h>
#include <analogWrite.h>
#include <TML_ErriezRotaryFullStep.h>

#include "Configuration_Settings.h" // load settings
#include "Z_Bitmaps.h"

#include "BluetoothSerial.h" //https://www.electronicshub.org/esp32-bluetooth-tutorial/


#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled!
#endif

BluetoothSerial SerialBT;    // Bluetooth Classic, not BLE
/*
  eBay Special Red PCB pinouots VCC(3.3v), GND, CS, RST, D/C, MOSI, SCK, BL, (MISO, T_CLK, T_CS, T_DIN, T_DO, T_IRQ)

  Wemos ESP32 LoLin32 D32  (Compiles/Tested)
  https://www.wemos.cc/en/latest/d32/d32.html

  **Wemos ESP32 Lolin32 Lite** (Compiles/Tested)
  **Wemos ESP32 Lolin32 v1  **  (Compiles/Tested)
  **discontinued, Clones Available**

  --------------------------------------------
  CS     =  17             (15)
  RST    =  15             (-1)
  DC     =  16             (2)

  SCLK   =  18
  MOSI   =  23

  MISO   =  19   (*Touch, Not Required for Reference only!!!)

  B.LIGHT =  4             (0, 13)
  ---------------------


  Mode Button= 0            (0,17)
  ---------------------
  i2c
  ---------------------
  SCL = 22  (*Not Required for Reference only!!!)
  SDA = 21  (*Not Required for Reference only!!!)

  (Lolin32 Lite)
  SCL = 23  (*Not Required for Reference only!!!)
  SDA = 19  (*Not Required for Reference only!!!)
  ---------------------
  ---------------------

  Neopixel / LED's
  ---------------------
  Built in LED =  5 (*Not Required for Reference only!!!)
  Neopixel     =  2       (32)

  Battery Monitor   Voltage divider (GND ---[100K]--- (Pin34 ADC) ----[100k]--- BATT+) 3.2v to 4.2v Range
  --------------------
  Battery Monitor = 34
  ==========================================================================================================
*/

#ifdef batteryMonitor

/* Battery Monitor Settings*/
#include <Pangodream_18650_CL.h> // Copyright (c) 2019 Pangodream

#define ADC_PIN 34        //!< ADC pin used, default is GPIO34 - ADC1_6 Voltage divider (2* 100K)
#define CONV_FACTOR 1.8 //!< Convertion factor to translate analog units to volts
#define READS 20
Pangodream_18650_CL BL(ADC_PIN, CONV_FACTOR, READS);

#endif

//---------------------------------------------------------------------------------------
#include <Adafruit_NeoPixel.h>
#define NEOPIN      2
//#define NUM_PIXELS  16 // moved to CFG
Adafruit_NeoPixel pixels(NUM_PIXELS, NEOPIN, NEO_GRB + NEO_KHZ800);

/* Pre-define Hex NeoPixel colours,  eg. pixels.setPixelColor(0, BLUE); https://htmlcolorcodes.com/color-names/ */
#define neo_BLUE       0x0000FF
#define neo_GREEN      0x008000
#define neo_RED        0xFF0000
#define neo_ORANGE     0xFFA500
#define neo_DARKORANGE 0xFF8C00
#define neo_YELLOW     0xFFFF00
#define neo_WHITE      0xFFFFFF
#define neo_BLACK      0x000000 // OFF

/*onboard BUILD in LED for RX*/
#define TX_LEDPin 5

//----------------------------------------------------------------------------

/* ILI9321 TFT setup */
#include <Adafruit_ILI9341.h>  // v1.5.6 Adafruit Standard

/* ESP32 SPi Hardware only for speed*/
#define TFT_CS     17
#define TFT_DC     16
#define TFT_RST    15

/* These pins do not have to be defined as they are hardware pins */
//Connect TFT_SCLK to pin   18
//Connect TFT_MOSI to pin   23

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST); // Use hardware SPI

//-----------------------------------------------------------------------------


/* Encoder Button pin*/
int mode_Button     = 0;
int display_Button_counter = 0;

/* Screen TFT backlight Pin */
int TFT_backlight_PIN = 4;


/* Encoder TFT Brightness*/ //Reserved!!! not supported on ESP32 Reserved
//volatile int brightness_count = 150; // Start Up PWM Brightness, moved to CFG!!!
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


#ifdef  RETRO_AMBER
#define ILI9341_YELLOW      0xFFE0 //ILI9341_YELLOW
#define ILI9341_WHITE       0xFFE0 //ILI9341_YELLOW
#define ILI9341_BLUE        0xA508 //ILI9341_GOLD
#define ILI9341_GREEN       0xA508 //ILI9341_GOLD
#define ILI9341_RED         0xA508 //ILI9341_GOLD
//--
#define ILI9341_SILVER      0xFFE0 //ILI9341_YELLOW
#define ILI9341_GREY        0xA508 //ILI9341_GOLD
#define ILI9341_LIGHT_GREY  0xA508 //ILI9341_GOLD
#endif


#ifdef  RETRO_GREEN
#define ILI9341_YELLOW      0x07E0 //ILI9341_GREEN
#define ILI9341_WHITE       0x07E0 //ILI9341_GREEN
#define ILI9341_BLUE        0x7BE0 //ILI9341_OLIVE
#define ILI9341_GREEN       0x7BE0 //ILI9341_OLIVE
#define ILI9341_RED         0x7BE0 //ILI9341_OLIVE
//--
#define ILI9341_SILVER      0x07E0 //ILI9341_GREEN
#define ILI9341_GREY        0x7BE0 //ILI9341_OLIVE
#define ILI9341_LIGHT_GREY  0x7BE0 //ILI9341_OLIVE
#endif


//--------------------------------


void setup() {


#ifdef enable_BT
  //btStart();
  SerialBT.begin(device_BT); //Bluetooth device name
#else //USB

  Serial.begin(baudRate);  //  USB Serial Baud Rate
#endif

  inputString.reserve(220); // String Buffer



  /* Set up the NeoPixel*/
  pixels.begin();    // This initializes the NeoPixel library.
  pixels.setBrightness(NeoBrightness); // Atmel Global Brightness
  pixels.show(); // Turn off all Pixels

  /* Set up PINs*/

  pinMode(mode_Button, INPUT_PULLUP);

#ifdef fixedBacklight
  pinMode(TFT_backlight_PIN, OUTPUT); // declare backlight pin to be an output:
#else
  // Set resolution for a specific pin
  analogWriteResolution(TFT_backlight_PIN, 12); //ESP32 only
#endif

#ifdef enableTX_LED
  pinMode(TX_LEDPin, OUTPUT); //  Builtin LED /  HIGH(OFF) LOW (ON)
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




#ifdef enableTX_LED
  /*ESP Activity LED */
  digitalWrite(TX_LEDPin, HIGH);    // turn the LED off HIGH(OFF) LOW (ON)
#endif
  //-----------------------------

  /*Mode Button, moved to its own tab*/
  button_Modes();

}

/* END of Main Loop */


//-----------------------------  NeoPixels RGB  -----------------------------------
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

void allNeoPixelsGREEN() {
  for ( int i = 0; i < NUM_PIXELS; i++ ) {
    pixels.setPixelColor(i, 0, 255, 0 );
  }
  pixels.show();
}

void allNeoPixelsBLUE() {
  for ( int i = 0; i < NUM_PIXELS; i++ ) {
    pixels.setPixelColor(i, 0, 0, 255 );
  }
  pixels.show();
}
//-----------------------------  Serial Events -------------------------------
/*
  SerialEvent occurs whenever a new data comes in the hardware serial RX. This
  routine is run between each time loop() runs, so using delay inside loop can
  delay response. Multiple bytes of data may be available.
*/

/* BlueTooth */
void serialBTEvent() {
  while (SerialBT.available()) {

    char inChar = (char)SerialBT.read();
    //Serial.print(inChar); // Debug Incoming Serial

    // add it to the inputString:
    inputString += inChar;
    // if the incoming character has '|' in it, set a flag so the main loop can do something about it:
    if (inChar == '|') {
      stringComplete = true;

      delay(Serial_eventDelay);   //delay screen event to stop screen data corruption

#ifdef enableTX_LED
      /* Serial Activity LED */
      digitalWrite(TX_LEDPin, LOW);   // turn the LED off HIGH(OFF) LOW (ON)
#endif

    }
  }
}


/* USB Serial*/
void serialEvent() {
  while (Serial.available()) {

    char inChar = (char)Serial.read();
    //Serial.print(inChar); // Debug Incoming Serial

    // add it to the inputString:
    inputString += inChar;
    // if the incoming character has '|' in it, set a flag so the main loop can do something about it:
    if (inChar == '|') {
      stringComplete = true;

      delay(Serial_eventDelay);   //delay screen event to stop screen data corruption

#ifdef enableTX_LED
      /* Serial Activity LED*/
      digitalWrite(TX_LEDPin, LOW);   // turn the LED off HIGH(OFF) LOW (ON)
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


    /* Set Default Adafruit GRFX Font*/
    tft.setFont();

    tft.fillScreen(ILI9341_BLACK);

    tft.setRotation(2);// Rotate the display at the start:  0, 1, 2 or 3 = (0, 90, 180 or 270 degrees)
    tft.drawRoundRect  (0, 0  , 240, 320, 8,    ILI9341_RED);
    tft.setTextColor(ILI9341_RED);
    tft.drawBitmap(82, 80, WaitingDataBMP2_90, 76, 154, ILI9341_RED);
    tft.setTextSize(2); tft.setCursor(40, 40); tft.println("NO COM DATA!!!");


    delay(2000);

    /* Clear Screen, Turn Off Backlight & Neopixels when there is no activity, */

    //tft.invertDisplay(0);
    backlightOFF ();
    allNeoPixelsOff();
    tft.fillScreen(ILI9341_BLACK);

    displayDraw = 0;

  }

}



//----------------------------- TFT Backlight  -------------------------------
#ifdef fixedBacklight //
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
  tft.setRotation(1);// Rotate the display at the start:  0, 1, 2 or 3 = (0, 90, 180 or 270 degrees)
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


#ifdef batteryMonitor
  // Battery Level Indicator on Boot Screen
  //-------------------------------------------------------------
  if (BL.getBatteryVolts() <= 3.4 ) {

    tft.drawBitmap(170, 10, BATTERY_BMP, 60, 20, ILI9341_RED);
    tft.setTextSize(2);
    tft.setCursor(178, 23);
    tft.setTextColor(ILI9341_BLACK);
    tft.print(BL.getBatteryVolts()); tft.print("v");

  } else {

    //-------------------------------------------------------------

    tft.drawBitmap(170, 10, BATTERY_BMP, 60, 20, ILI9341_GREEN);
    tft.setTextSize(2);
    tft.setCursor(178, 23);
    tft.setTextColor(ILI9341_BLACK);
    tft.print(BL.getBatteryVolts()); tft.print("v");
  }

#endif

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

  //-------------------------------------------------------------------
  //tft.setTextColor(ILI9341_WHITE);
  tft.setFont(); // Set Default Adafruit GRFX Font

  //tft.setTextSize(1);

  //tft.setCursor(10, 305);
  //tft.setTextColor(ILI9341_WHITE);
  //tft.print("If using USB Serial? Disconnect BT!!!");

  backlightON();

  FeatureSet_Indicator2(); // Display Icons for enabled features

  delay(2000);

#ifdef enable_NeopixelGauges

#ifdef enable_BT
  allNeoPixelsBLUE();
#else
  allNeoPixelsRED();
#endif

#endif

  tft.fillScreen(ILI9341_BLACK);
  backlightOFF();// Hide the Screen while drawing

#ifdef enable_BT
  tft.drawRoundRect  (0, 0  , 240, 320, 8,    ILI9341_RED);
  tft.drawBitmap(82, 62, WaitingDataBMP_BT, 76, 190, ILI9341_BLUE);

#ifdef batteryMonitor
  // Show Battery Level Indicator on waiting for data screen

  if (BL.getBatteryVolts() <= 3.4 ) {
    tft.drawBitmap(33 + 40, 280, BATTERY_BMP, 60, 20, ILI9341_RED);

    tft.setCursor(46 + 40, 286 ); // (Left/Right, UP/Down)
    tft.setTextSize(1);
    tft.setTextColor(ILI9341_BLACK);
    tft.print(BL.getBatteryVolts()); tft.print("v");
    tft.setTextColor(ILI9341_WHITE);
    tft.setTextSize(2);
    tft.setCursor(100 + 40, 283 ); // (Left/Right, UP/Down)
    tft.print(BL.getBatteryChargeLevel());
    tft.print("% ");

  } else {

    tft.drawBitmap(33 + 40, 280, BATTERY_BMP, 60, 20, ILI9341_GREEN);

    tft.setCursor(46 + 40, 286 ); // (Left/Right, UP/Down)
    tft.setTextSize(1);
    tft.setTextColor(ILI9341_BLACK);
    tft.print(BL.getBatteryVolts()); tft.print("v");
    tft.setTextColor(ILI9341_WHITE);
    tft.setTextSize(2);
    tft.setCursor(100 + 40, 283 ); // (Left/Right, UP/Down)
    tft.print(BL.getBatteryChargeLevel());
    tft.print("% ");
  }
#endif

#ifdef splashScreenLS // Quick landscape hack job, also in FeatureSet
  tft.setRotation(0);// Rotate the display at the start:  0, 1, 2 or 3 = (0, 90, 180 or 270 degrees)
#endif

#else // USB
  tft.drawRoundRect  (0, 0  , 240, 320, 8,    ILI9341_RED);
  tft.drawBitmap(82, 62, WaitingDataBMP_USB, 76, 190, ILI9341_RED);
#endif

#ifdef enable_BT
  tft.drawRoundRect  (0, 0  , 240, 320, 8,    ILI9341_RED);
  tft.drawBitmap(82, 62, WaitingDataBMP_BT,  76, 190, ILI9341_BLUE);
#endif

  backlightON();
  delay(2000);
  backlightOFF();// Hide the Screen while drawing
  tft.fillScreen(ILI9341_BLACK);

}

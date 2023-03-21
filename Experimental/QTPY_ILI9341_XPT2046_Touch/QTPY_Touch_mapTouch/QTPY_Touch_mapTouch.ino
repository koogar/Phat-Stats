/* Map XPT2046 input to ILI9341 320x240 raster */

//https://gist.github.com/CelliesProjects/99a56121e7c8a7cb00d5b46270e74b75#file-maptouch-ino

#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include <XPT2046_Touchscreen.h> /* https://github.com/PaulStoffregen/XPT2046_Touchscreen */

#define TFT_DC             7 //27 // 16
#define _sclk              8 //25 // 18
#define _mosi              10 //32 // 23 /* 10K pull-up */
#define _miso              9 //39 // 19// vn?
#define TFT_CS             5 // 4 // 17 /* 10K pull-up */
#define TFT_RST            0 //12 // 19
#define TFT_BACKLIGHT_PIN  4 // 2 // 4  /* -via transistor- */
#define TOUCH_CS_PIN       2 //33 // 15     /* 10K pull-up */
#define TOUCH_IRQ_PIN      3 //35 // 14

#define TFT_NORMAL         1
#define TFT_UPSIDEDOWN     3

const uint8_t TFT_ORIENTATION = TFT_NORMAL;

Adafruit_ILI9341 tft = Adafruit_ILI9341( TFT_CS, TFT_DC, TFT_RST );

XPT2046_Touchscreen touch( TOUCH_CS_PIN, TOUCH_IRQ_PIN );

void setup() {
  Serial.begin( 115200 );
  SPI.begin(  );
  //SPI.setFrequency( 60000000 );

  //tft.begin( 10000000, SPI );
  tft.begin();

  tft.setRotation( TFT_ORIENTATION );
  tft.fillScreen( ILI9341_BLACK );
  tft.setTextColor( ILI9341_GREEN, ILI9341_BLACK );

  pinMode( TFT_BACKLIGHT_PIN, OUTPUT );
  digitalWrite( TFT_BACKLIGHT_PIN, HIGH );

  touch.begin();
  Serial.println( "Touch screen ready." );
}


TS_Point rawLocation;

void loop() {

  tft.println("TEST!!!");
  //if ( touch.touched() )
    while ( touch.touched() )
    {
      rawLocation = touch.getPoint();
      /*
        tft.setCursor( 100, 150 );
        tft.print( "X = " );
        tft.print( rawLocation.x );
        tft.setCursor(100, 180);
        tft.print( "Y = " );
        tft.print( rawLocation.y );

        Serial.print("x = ");
        Serial.print(rawLocation.x);
        Serial.print(", y = ");
        Serial.print(rawLocation.y);
        Serial.print(", z = ");
        Serial.println(rawLocation.z);
      */
      if ( TFT_ORIENTATION == TFT_UPSIDEDOWN )
      {
        tft.drawPixel( mapFloat( rawLocation.x, 340, 3900, 0, 320 ),
                       mapFloat( rawLocation.y, 200, 3850, 0, 240 ),
                       ILI9341_GREEN );
      }
      if ( TFT_ORIENTATION == TFT_NORMAL )
      {
        tft.drawPixel( mapFloat( rawLocation.x, 340, 3900, 320, 0 ),
                       mapFloat( rawLocation.y, 200, 3850, 240, 0 ),
                       ILI9341_GREEN );
      }
    }
  //tft.fillScreen(ILI9341_BLACK);
}

static inline __attribute__((always_inline)) float mapFloat( float x, const float in_min, const float in_max, const float out_min, const float out_max)
{
  return ( x - in_min ) * ( out_max - out_min ) / ( in_max - in_min ) + out_min;
}

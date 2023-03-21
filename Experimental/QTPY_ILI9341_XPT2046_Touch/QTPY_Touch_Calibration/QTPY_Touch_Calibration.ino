// -----------------------------------------------------------------------------
//
// the process of calibrating a touchscreen, at a high-level, consists of:
//
// (ONE-TIME)
//   1. pick three random points a,b,c (not co-linear) in -screen- coordinates.
//   2. for each point p, obtain the corresponding -touchscreen- coorindate p_t.
// (ALWAYS/RUNTIME)
//   3. with all six points (a, b, c, a_t, b_t, c_t), along with the screen
//      height and width for the current orientation (per setRotation()), pass
//      a calibration object to the touchscreen via calibrate().
//
// any subsequent calls to get touch position (getPoint() or readData()) after
// calling calibrate() will return (x,y)-points in -screen- coordinates instead
// of -touchscreen- coordinates -- also corrected for screen orientation!
//
// --
//
// how to use this library:
//
//   1. usage of this library is identical to XPT2046_Touchscreen. however, to
//      enable calibration, after calling begin() and setRotation(), you must
//      then call calibrate() with an appropriate TS_Calibration object as
//      parameter. afterwards, all calls to obtain touch position (getPoint()
//      and readData()) will return (x,y) points in screen coordinates rather
//      than touchscreen coordinates. this sketch simply assists with obtaining
//      the parameters required to construct a TS_Calibration object. these
//      parameters are fixed, hardware descriptors that should never change for
//      a given touchscreen. so once the parameters are obtained one time, you
//      should never have to calculate them again unless your screen is moved
//      or removed for some reason.
//
// --
//
// how to use this sketch:
//
//   1. the sketch below assists performing steps 1-2 above. simply update the
//      GPIO pin defines below per your configuration, ensure the
//      VERIFY_CALIBRATION macro is commented out, and then compile and flash.
//
//   2. once running, touch the center of each crosshair. you will see the
//      needed point-translation mapping drawn to screen (and also printed to
//      serial console if open). the point on the left-hand side of each line is
//      the -screen- coordinate of the crosshair, and on the right-hand side is
//      the -touchscreen- coordinate of the last touch.
//
//   3. once all three lines have been drawn, substitute your -touchscreen-
//      coordinates into the _touchPoint[] array below, uncomment the
//      VERIFY_CALIBRATION macro below, and then compile and flash.
//
//   4. now when you touch the crosshairs, both points listed on each line will
//      be in -screen- coordinates -- one for the crosshair and one for the
//      touch! verify that the distance between crosshair and touch coordinate
//      approaches zero as you approach closer to the center of the crosshair.
//
// be sure to use something pokey, fine-tipped to touch the crosshair center.
//
// *** NOTE *** IMPORTANT ***
//   I seem to get best calibration results by performing steps 1-2 in landscape
//   orientation (rotation=1) with screen width,height=320,240. then for step
//   3, I can re-use those same 6 points obtained while in landscape even if I
//   flip or change the orientation/screen dimensions to portrait when calling
//   calibrate() in my actual project. this is the default configuration of
//   this sketch below.
//
// -----------------------------------------------------------------------------


//https://github.com/ardnew/XPT2046_Calibrated

#include <XPT2046_Calibrated.h>
#include <Adafruit_ILI9341.h> // or Adafruit_ILI9341.h
#include <SPI.h>

// -- CONFIGURATION --
#define TFT_BACKLIGHT_PIN   4 // 2 // 4  /* -via transistor- */

#define TS_CS_PIN   2
#define TS_IRQ_PIN  3

#define TFT_CS_PIN 5
#define TFT_DC_PIN 7
#define TFT_RST_PIN 0
//SCLK   =  8
//MOSI   =  10

static uint16_t const SCREEN_WIDTH    = 320;
static uint16_t const SCREEN_HEIGHT   = 240;
static uint8_t  const SCREEN_ROTATION = 1U;

enum class PointID { NONE = -1, A, B, C, COUNT };

// source points used for calibration
static TS_Point _screenPoint[] = {
  TS_Point( 13,  11), // point A
  TS_Point(312, 113), // point B
  TS_Point(167, 214)  // point C
};

#define VERIFY_CALIBRATION
#ifdef VERIFY_CALIBRATION

// touchscreen points used for calibration verification
static TS_Point _touchPoint[] = {
  TS_Point(3795, 3735), // point A
  TS_Point( 482, 2200), // point B
  TS_Point(2084,  583), // point C
};

static TS_Calibration cal(
    _screenPoint[(int)PointID::A], _touchPoint[(int)PointID::A],
    _screenPoint[(int)PointID::B], _touchPoint[(int)PointID::B],
    _screenPoint[(int)PointID::C], _touchPoint[(int)PointID::C],
    SCREEN_WIDTH,
    SCREEN_HEIGHT
);

#endif // VERIFY_CALIBRATION

// -- LOCAL VARIABLES --

#ifdef TIRQ_PIN
XPT2046_Calibrated ts(TS_CS_PIN, TS_IRQ_PIN);
#else
XPT2046_Calibrated ts(TS_CS_PIN);
#endif // TIRQ_PIN

Adafruit_ILI9341 tft = Adafruit_ILI9341( TFT_CS_PIN, TFT_DC_PIN, TFT_RST_PIN );

// -----------------------------------------------------------------------------

// -- UTILITY ROUTINES (DECLARATION) --

inline bool touched();
void crosshair(TS_Point p);
uint16_t distance(TS_Point a, TS_Point b);
void drawMapping(PointID n, TS_Point p);
void updateScreenEdges(TS_Point p);
PointID nearestScreenPoint(TS_Point touch);

// -- ARDUINO MAIN --

void setup() {

  Serial.begin(115200);
  
  pinMode( TFT_BACKLIGHT_PIN, OUTPUT );
  digitalWrite( TFT_BACKLIGHT_PIN, HIGH );
  
  while (!Serial && (millis() <= 1000U))
    { continue; }

  tft.begin();
  tft.setRotation(SCREEN_ROTATION);
  tft.fillScreen(ILI9341_BLACK);
  tft.setTextSize(1);
  tft.setTextColor(ILI9341_WHITE);

  ts.begin();
  ts.setRotation(SCREEN_ROTATION);
#ifdef VERIFY_CALIBRATION
  ts.calibrate(cal);
#endif

  // draw the crosshairs on screen only once
  for (int i = (int)PointID::NONE + 1; i < (int)PointID::COUNT; ++i)
    { crosshair(_screenPoint[i]); }
}

void loop() {

  if (touched()) {

    TS_Point p = ts.getPoint();

    //updateScreenEdges(p);

    // determine which screen point is closest to this touch event
    PointID n = nearestScreenPoint(p);

    // update the corresponding line mapping
    drawMapping(n, p);

    delay(30);
  }
}

// -- UTILITY ROUTINES (DEFINITION) --

inline bool touched() {
#ifdef TIRQ_PIN
  if (ts.tirqTouched()) {
    return ts.touched();
  }
  return false;
#else
  return ts.touched();
#endif
}

void crosshair(TS_Point p) {
  tft.drawCircle   (p.x,     p.y,     6, ILI9341_WHITE);
  tft.drawFastHLine(p.x - 4, p.y,     9, ILI9341_WHITE);
  tft.drawFastVLine(p.x,     p.y - 4, 9, ILI9341_WHITE);
}

uint16_t distance(TS_Point a, TS_Point b) {
  // calculate the distance between points a and b in whatever 2D coordinate
  // system they both exist. returns an integer distance with naive rounding.
  static uint16_t const MAX = ~((uint16_t)0U);
  int32_t dx = b.x - a.x;
  int32_t dy = b.y - a.y;
  uint32_t dsq = (uint32_t)sq(dx) + (uint32_t)sq(dy);
  double d = sqrt(dsq); // add 1/2 for rounding
  if (d > ((double)MAX - 0.5))
    { return MAX; }
  else
    { return (uint16_t)(d + 0.5); } // poor-man's rounding
}

void drawMapping(PointID n, TS_Point tp) {

  static uint8_t const BUF_LEN = 64;
  static char buf[BUF_LEN] = { '\0' };

  static uint16_t lineHeight = (uint16_t)(1.5F * 8.0F + 0.5F);
  static uint16_t lineSpace  = 1U;

  int16_t posX, posY;
  uint16_t sizeW, sizeH;
  uint16_t posLeft = 6U;
  uint16_t posTop =
    SCREEN_HEIGHT - (3U - (uint16_t)n) * (lineHeight + lineSpace);

  TS_Point sp = _screenPoint[(int)n];

  // construct the line buffer
  snprintf(buf, BUF_LEN, "%c (%u,%u) = (%u,%u)",
    (uint8_t)n + 'A', sp.x, sp.y, tp.x, tp.y);

  // print the current line to serial port for debugging
  Serial.printf("%s\n", buf);

  // erase the previous line
  tft.getTextBounds(buf, posLeft, posTop, &posX, &posY, &sizeW, &sizeH);
  tft.fillRect(posX, posY, sizeW, sizeH, ILI9341_BLACK);

  // draw the current line
  tft.setCursor(posLeft, posTop);
  tft.printf("%s", buf);
}

// -- NOT FOR GENERAL USAGE -- IGNORE THESE --------------------------- BEGIN --
// approximate calibration only used for determining distance from touch to
// crosshair while calibrating. you can determine these values by using the
// updateScreenEdges() routine below -- just call it with the position of every
// touch event while scrubbing all 4 edges of the screen with a stylus.
#define XPT2046_X_LO 3963
#define XPT2046_X_HI 338
#define XPT2046_Y_LO 4031
#define XPT2046_Y_HI 211
#define MAP_2D_PORTRAIT(x, y)                                        \
  TS_Point(                                                          \
    (int16_t)map((x), XPT2046_X_LO, XPT2046_X_HI, 0,  SCREEN_WIDTH), \
    (int16_t)map((y), XPT2046_Y_LO, XPT2046_Y_HI, 0, SCREEN_HEIGHT)  \
  )
#define MAP_2D_LANDSCAPE(x, y)                                       \
  TS_Point(                                                          \
    (int16_t)map((x), XPT2046_Y_LO, XPT2046_Y_HI, 0,  SCREEN_WIDTH), \
    (int16_t)map((y), XPT2046_X_LO, XPT2046_X_HI, 0, SCREEN_HEIGHT)  \
  )
void updateScreenEdges(TS_Point p) {
  static uint16_t xHi = 0xFFFF;
  static uint16_t yHi = 0xFFFF;
  static uint16_t xLo = 0x0;
  static uint16_t yLo = 0x0;
  if (p.x < xHi) { xHi = p.x; }
  if (p.x > xLo) { xLo = p.x; }
  if (p.y < yHi) { yHi = p.y; }
  if (p.y > yLo) { yLo = p.y; }
  Serial.printf("[X_LO, X_HI] = [%u, %u], [Y_LO, Y_HI] = [%u, %u]\n",
      xLo, xHi, yLo, yHi);
}
// -- NOT FOR GENERAL USAGE -- IGNORE THESE ----------------------------- END --

PointID nearestScreenPoint(TS_Point touch) {

#ifdef VERIFY_CALIBRATION
  // the input point is already in screen coordinates because the touchscreen
  // has been calibrated. no need to perform translation.
  TS_Point tp = touch;
#else
  // translate the input point (in touch coordinates) to screen coordinates
  // using the hardcoded ranges defined in these macros. not particularly
  // accurate, but it doesn't need to be.
  TS_Point tp = (SCREEN_ROTATION & 1U)
    ? MAP_2D_LANDSCAPE(touch.x, touch.y)
    : MAP_2D_PORTRAIT(touch.x, touch.y);
  Serial.printf(
      "Touch{%u, %u} => Screen{%u, %u}\n", touch.x, touch.y, tp.x, tp.y);
#endif

  PointID  near = PointID::NONE;
  uint16_t dist = 0U;

  for (int id = (int)PointID::NONE + 1; id < (int)PointID::COUNT; ++id) {
    // compute the distance from our (translated) input touch point to each
    // screen point to determine minimum distance.
    uint16_t d = distance(tp, _screenPoint[id]);
    if ((near == PointID::NONE) || (d < dist)) {
      // new minimum distance, this is the nearest point to our touch (so far)
      near = (PointID)id;
      dist = d;
    }
  }

  return near;
}

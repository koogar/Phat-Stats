

#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_GC9A01A.h"

/**/  

//QT PY ATSAMD21,Seeeduino_XIAO_ATSAMD, Seeeduino_XIAO_NRF52840
#define TFT_SCLK  8
#define TFT_MISO  9
#define TFT_MOSI  10
#define TFT_CS    1  // Chip select control pin
#define TFT_DC    3  // Data Command control pin
#define TFT_BL    6
#define TFT_RST  -1  // Reset pin (could connect to RST pin)


/*
//Seeeduino_XIAO_RP2040, Seeeduino_XIAO_ESP32C3/S3
#define TFT_SCLK D8
#define TFT_MISO D9
#define TFT_MOSI D10
#define TFT_CS   D1  // Chip select control pin
#define TFT_DC   D3  // Data Command control pin
#define TFT_BL   D6
#define TFT_RST  -1  // Reset pin (could connect to RST pin)
*/

Adafruit_GC9A01A tft(TFT_CS, TFT_DC, TFT_RST); //XIAO & QT PY


// Hardware SPI on Feather or other boards
//Adafruit_GC9A01A tft(TFT_CS, TFT_DC);



void setup() {

  pinMode(TFT_BL, OUTPUT); // declare backlight pin to be an output:
  digitalWrite(TFT_BL, HIGH);
  
  Serial.begin(9600);
  Serial.println("GC9A01A Test!");

  tft.begin();

  Serial.println(F("Benchmark                Time (microseconds)"));
  delay(10);
  Serial.print(F("Screen fill              "));
  Serial.println(testFillScreen());
  delay(500);

  Serial.print(F("Text                     "));
  Serial.println(testText());
  delay(3000);

  Serial.print(F("Lines                    "));
  Serial.println(testLines(GC9A01A_CYAN));
  delay(500);

  Serial.print(F("Horiz/Vert Lines         "));
  Serial.println(testFastLines(GC9A01A_RED, GC9A01A_BLUE));
  delay(500);

  Serial.print(F("Rectangles (outline)     "));
  Serial.println(testRects(GC9A01A_GREEN));
  delay(500);

  Serial.print(F("Rectangles (filled)      "));
  Serial.println(testFilledRects(GC9A01A_YELLOW, GC9A01A_MAGENTA));
  delay(500);

  Serial.print(F("Circles (filled)         "));
  Serial.println(testFilledCircles(10, GC9A01A_MAGENTA));

  Serial.print(F("Circles (outline)        "));
  Serial.println(testCircles(10, GC9A01A_WHITE));
  delay(500);

  Serial.print(F("Triangles (outline)      "));
  Serial.println(testTriangles());
  delay(500);

  Serial.print(F("Triangles (filled)       "));
  Serial.println(testFilledTriangles());
  delay(500);

  Serial.print(F("Rounded rects (outline)  "));
  Serial.println(testRoundRects());
  delay(500);

  Serial.print(F("Rounded rects (filled)   "));
  Serial.println(testFilledRoundRects());
  delay(500);

  Serial.println(F("Done!"));
}

void loop(void) {
  for (uint8_t rotation = 0; rotation < 4; rotation++) {
    tft.setRotation(rotation);
    testText();
    delay(1000);

  }
}

unsigned long testFillScreen() {
  unsigned long start = micros();
  tft.fillScreen(GC9A01A_BLACK);
  yield();
  tft.fillScreen(GC9A01A_RED);
  yield();
  tft.fillScreen(GC9A01A_GREEN);
  yield();
  tft.fillScreen(GC9A01A_BLUE);
  yield();
  tft.fillScreen(GC9A01A_BLACK);
  yield();
  return micros() - start;
}

unsigned long testText() {
  tft.fillScreen(GC9A01A_BLACK);
  unsigned long start = micros();

  tft.setTextColor(GC9A01A_WHITE);  tft.setTextSize(1);
  tft.setCursor(85, 20);
  tft.print("Hello World!");

  tft.setTextColor(GC9A01A_YELLOW); tft.setTextSize(2);
  tft.setCursor(50, 40);
  tft.print(1234.56);

  tft.setTextColor(GC9A01A_RED);    tft.setTextSize(3);
  tft.setCursor(25, 65);
  tft.print(0xDEADBEEF, HEX);

  tft.println();
  tft.setTextColor(GC9A01A_GREEN);
  tft.setCursor(10, 100);
  tft.setTextSize(5);
  tft.print("Groop");

  tft.setCursor(10, 140);
  tft.setTextSize(2);
  tft.println("I implore thee,");
  tft.setTextSize(1);
  tft.setCursor(20, 160);
  tft.print("my foonting turlingdromes.");
  tft.setCursor(30, 170);
  tft.print("And hooptiously drangle me");
  tft.setCursor(40, 180);
  tft.print("with crinkly bindlewurdles,");
  tft.setCursor(50, 190);
  tft.print("Or I will rend thee");
  tft.setCursor(60, 200);
  tft.print("in the gobberwarts");
  tft.setCursor(70, 210);
  tft.print("with my blurglecruncheon,");
  tft.setCursor(80, 220);
  tft.print("see if I don't!");
  return micros() - start;
}

unsigned long testLines(uint16_t color) {
  unsigned long start, t;
  int           x1, y1, x2, y2,
                w = tft.width(),
                h = tft.height();

  tft.fillScreen(GC9A01A_BLACK);
  yield();

  x1 = y1 = 0;
  y2    = h - 1;
  start = micros();
  for (x2 = 0; x2 < w; x2 += 6) tft.drawLine(x1, y1, x2, y2, color);
  x2    = w - 1;
  for (y2 = 0; y2 < h; y2 += 6) tft.drawLine(x1, y1, x2, y2, color);
  t     = micros() - start; // fillScreen doesn't count against timing

  yield();
  tft.fillScreen(GC9A01A_BLACK);
  yield();

  x1    = w - 1;
  y1    = 0;
  y2    = h - 1;
  start = micros();
  for (x2 = 0; x2 < w; x2 += 6) tft.drawLine(x1, y1, x2, y2, color);
  x2    = 0;
  for (y2 = 0; y2 < h; y2 += 6) tft.drawLine(x1, y1, x2, y2, color);
  t    += micros() - start;

  yield();
  tft.fillScreen(GC9A01A_BLACK);
  yield();

  x1    = 0;
  y1    = h - 1;
  y2    = 0;
  start = micros();
  for (x2 = 0; x2 < w; x2 += 6) tft.drawLine(x1, y1, x2, y2, color);
  x2    = w - 1;
  for (y2 = 0; y2 < h; y2 += 6) tft.drawLine(x1, y1, x2, y2, color);
  t    += micros() - start;

  yield();
  tft.fillScreen(GC9A01A_BLACK);
  yield();

  x1    = w - 1;
  y1    = h - 1;
  y2    = 0;
  start = micros();
  for (x2 = 0; x2 < w; x2 += 6) tft.drawLine(x1, y1, x2, y2, color);
  x2    = 0;
  for (y2 = 0; y2 < h; y2 += 6) tft.drawLine(x1, y1, x2, y2, color);

  yield();
  return micros() - start;
}

unsigned long testFastLines(uint16_t color1, uint16_t color2) {
  unsigned long start;
  int           x, y, w = tft.width(), h = tft.height();

  tft.fillScreen(GC9A01A_BLACK);
  start = micros();
  for (y = 0; y < h; y += 5) tft.drawFastHLine(0, y, w, color1);
  for (x = 0; x < w; x += 5) tft.drawFastVLine(x, 0, h, color2);

  return micros() - start;
}

unsigned long testRects(uint16_t color) {
  unsigned long start;
  int           n, i, i2,
                cx = tft.width()  / 2,
                cy = tft.height() / 2;

  tft.fillScreen(GC9A01A_BLACK);
  n     = min(tft.width(), tft.height());
  start = micros();
  for (i = 2; i < n; i += 6) {
    i2 = i / 2;
    tft.drawRect(cx - i2, cy - i2, i, i, color);
  }

  return micros() - start;
}

unsigned long testFilledRects(uint16_t color1, uint16_t color2) {
  unsigned long start, t = 0;
  int           n, i, i2,
                cx = tft.width()  / 2 - 1,
                cy = tft.height() / 2 - 1;

  tft.fillScreen(GC9A01A_BLACK);
  n = min(tft.width(), tft.height());
  for (i = n; i > 0; i -= 6) {
    i2    = i / 2;
    start = micros();
    tft.fillRect(cx - i2, cy - i2, i, i, color1);
    t    += micros() - start;
    // Outlines are not included in timing results
    tft.drawRect(cx - i2, cy - i2, i, i, color2);
    yield();
  }

  return t;
}

unsigned long testFilledCircles(uint8_t radius, uint16_t color) {
  unsigned long start;
  int x, y, w = tft.width(), h = tft.height(), r2 = radius * 2;

  tft.fillScreen(GC9A01A_BLACK);
  start = micros();
  for (x = radius; x < w; x += r2) {
    for (y = radius; y < h; y += r2) {
      tft.fillCircle(x, y, radius, color);
    }
  }

  return micros() - start;
}

unsigned long testCircles(uint8_t radius, uint16_t color) {
  unsigned long start;
  int           x, y, r2 = radius * 2,
                      w = tft.width()  + radius,
                      h = tft.height() + radius;

  // Screen is not cleared for this one -- this is
  // intentional and does not affect the reported time.
  start = micros();
  for (x = 0; x < w; x += r2) {
    for (y = 0; y < h; y += r2) {
      tft.drawCircle(x, y, radius, color);
    }
  }

  return micros() - start;
}

unsigned long testTriangles() {
  unsigned long start;
  int           n, i, cx = tft.width()  / 2 - 1,
                      cy = tft.height() / 2 - 1;

  tft.fillScreen(GC9A01A_BLACK);
  n     = min(cx, cy);
  start = micros();
  for (i = 0; i < n; i += 5) {
    tft.drawTriangle(
      cx    , cy - i, // peak
      cx - i, cy + i, // bottom left
      cx + i, cy + i, // bottom right
      tft.color565(i, i, i));
  }

  return micros() - start;
}

unsigned long testFilledTriangles() {
  unsigned long start, t = 0;
  int           i, cx = tft.width()  / 2 - 1,
                   cy = tft.height() / 2 - 1;

  tft.fillScreen(GC9A01A_BLACK);
  start = micros();
  for (i = min(cx, cy); i > 10; i -= 5) {
    start = micros();
    tft.fillTriangle(cx, cy - i, cx - i, cy + i, cx + i, cy + i,
                     tft.color565(0, i * 10, i * 10));
    t += micros() - start;
    tft.drawTriangle(cx, cy - i, cx - i, cy + i, cx + i, cy + i,
                     tft.color565(i * 10, i * 10, 0));
    yield();
  }

  return t;
}

unsigned long testRoundRects() {
  unsigned long start;
  int           w, i, i2,
                cx = tft.width()  / 2 - 1,
                cy = tft.height() / 2 - 1;

  tft.fillScreen(GC9A01A_BLACK);
  w     = min(tft.width(), tft.height());
  start = micros();
  for (i = 0; i < w; i += 6) {
    i2 = i / 2;
    tft.drawRoundRect(cx - i2, cy - i2, i, i, i / 8, tft.color565(i, 0, 0));
  }

  return micros() - start;
}

unsigned long testFilledRoundRects() {
  unsigned long start;
  int           i, i2,
                cx = tft.width()  / 2 - 1,
                cy = tft.height() / 2 - 1;

  tft.fillScreen(GC9A01A_BLACK);
  start = micros();
  for (i = min(tft.width(), tft.height()); i > 20; i -= 6) {
    i2 = i / 2;
    tft.fillRoundRect(cx - i2, cy - i2, i, i, i / 8, tft.color565(0, i, 0));
    yield();
  }

  return micros() - start;
}

// Matrix Display
// 320 pixel wide display / 12 pixel character spacing = 26 columns.
// The final column starts at x=304 and uses an 8 pixel character cell.

#define CHAR_WIDTH  12
#define MAX_COLS    (320 / CHAR_WIDTH)

// --- Aesthetics ---
#define NEON_GREEN  0x07E0  // Brightest
#define DIM_GREEN   0x0320  // Mid-tone
#define DARK_GREEN  0x0100  // Fading tail
// ------------------

int yPositions[MAX_COLS];
int speeds[MAX_COLS];
int streamLengths[MAX_COLS];

unsigned long lastUpdate = 0;
const int updateInterval = 50; // Higher = Slower rain

bool matrixActive = false;


// Start a new Matrix screensaver session.
// The display is cleared once here, not on every animation frame.
void matrix_display_start() {

  tft.fillScreen(0x0000);

  for (int i = 0; i < MAX_COLS; i++) {
    yPositions[i] = random(-300, 0);
    speeds[i] = random(1, 4);
    streamLengths[i] = random(8, 20);
  }

  lastUpdate = millis();
  matrixActive = true;
}


// Tell Matrix that the screensaver session has ended.
// The next call to matrix_display() will start a fresh session.
void matrix_display_stop() {

  // Only clear once when leaving the Matrix screensaver.
  // activityChecker() calls this repeatedly while activity is present,
  // so the clear only happens when a Matrix session is active.
  if (matrixActive) {
    matrixActive = false;
    tft.fillScreen(0x0000);
  }
}


// Matrix screensaver
void matrix_display() {

  // First frame after entering screensaver mode.
  if (!matrixActive) {
    matrix_display_start();
  }

  tft.setTextSize(1);

  if (millis() - lastUpdate > updateInterval) {

    lastUpdate = millis();

    for (int i = 0; i < MAX_COLS; i++) {

      int x = i * CHAR_WIDTH + 4;

      // 1. Erase the very end of the tail
      int tailPos = yPositions[i] - (streamLengths[i] * 12);
      tft.fillRect(x, tailPos, 8, 12, 0x0000);

      // 2. Draw the trailing tail
      tft.setTextColor(DARK_GREEN);
      tft.setCursor(x, yPositions[i] - 24);
      tft.print((char)random(33, 126));

      // 3. Draw the main body
      tft.setTextColor(DIM_GREEN);
      tft.setCursor(x, yPositions[i] - 12);
      tft.print((char)random(33, 126));

      // 4. Draw the leading head
      tft.setTextColor(NEON_GREEN);
      tft.setCursor(x, yPositions[i]);
      tft.print((char)random(33, 126));

      // 5. Update Y based on individual column speed
      yPositions[i] += (speeds[i] * 4);

      // 6. Reset logic
      if (tailPos > 240) {
        yPositions[i] = 0;
        speeds[i] = random(1, 4);
        streamLengths[i] = random(8, 22);
      }
    }
  }
}

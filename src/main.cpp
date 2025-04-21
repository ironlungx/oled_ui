#include "freertos/projdefs.h"
#include <Arduino.h>
#include <U8g2lib.h>

#include <oled_ui.h> // Should be included before U8g2lib if it uses types from it

// Use the UILib namespace
using namespace UILib;

U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);

// Define the UI context globally or where appropriate
Context uiContext(&u8g2, u8g2_font_helvB08_tr, u8g2_font_haxrcorp4089_tr);

// Example Label instance with a buffer size of 20 characters
Label<20> statusLabel(5, 15, "Initializing...");
ProgressBar progressBar(5, 30, 0, 118, 10); // x, y, initial, w, h

void setup() {
  Serial.begin(115200); // Start serial for debugging
  u8g2.begin();
  u8g2.setFontRefHeightExtendedText();
  u8g2.setDrawColor(1);
  u8g2.setFontPosTop();
  u8g2.setFontDirection(0);

  // Example: Update label text after setup
  statusLabel.setText("Ready");
  progressBar.setProgress(10);
}

void switch_ui(int x, int y, bool selected) {
  // Get screen dimensions
  int screenWidth = u8g2.getWidth();
  int screenHeight = u8g2.getHeight();

  int h =
      screenHeight *
      0.172; // 15% of the screenHeight (TODO: replace with something better)

  if (h < 8)
    h = 8;
  if (h > 16)
    h = 16;

  int w = 1.73 * h;

  int r = h / 2; // Radius for the rounded ends

  u8g2.drawRFrame(x, y, w, h, r);

  int circleX;
  if (selected) {
    circleX = x + w - r - 1; // Right position when selected
  } else {
    circleX = x + r; // Left position when not selected
  }

  int circleY = y + r;
  int circleR = r - 2; // Slightly smaller than the corner radius

  // Draw the filled circle indicator
  if (selected)
    u8g2.drawDisc(circleX, circleY, circleR);
  else
    u8g2.drawCircle(circleX, circleY, circleR);
}

// Removed global Context config, using uiContext now

void loop() {
  u8g2.clearBuffer();

  // Render UI elements
  statusLabel.render(&uiContext);
  progressBar.render(&uiContext);

  // Example: Update progress bar over time
  progressBar += 1; // Use overloaded operator
  if (progressBar.getProgress() > 100) {
    progressBar.setProgress(0);
    statusLabel.setText("Looping...");
  }

  // Example usage of the old switch_ui function (if still needed)
  // switch_ui(90, 50, (millis() / 1000) % 2 == 0);

  u8g2.sendBuffer();
  vTaskDelay(pdMS_TO_TICKS(100)); // ~10 FPS
}

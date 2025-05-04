#include "elements/bitmap.hpp"
#include "elements/label.hpp"
#include "elements/progressBar.h"

#include <Arduino.h>
#include <U8g2lib.h>
#include <cstdlib>

#define DEBUG
#define FPS

#define BTN 2

static const unsigned char cursorBMP[] = {0x01, 0x00, 0x03, 0x00, 0x07, 0x00, 0x0d, 0x00, 0x1d, 0x00, 0x39,
                                          0x00, 0x79, 0x00, 0xf1, 0x00, 0xf1, 0x01, 0xe1, 0x03, 0xf1, 0x07,
                                          0x09, 0x00, 0x05, 0x00, 0x03, 0x00, 0x01, 0x00, 0x00, 0x00};

using namespace UILib;

U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);
Grid grid(u8g2.getDisplayWidth(), u8g2.getDisplayHeight(), 8, 11);

Context uiContext(&u8g2, &grid);

Label<20> statusLabel({5, 1, AnchorPoint::CENTER}, new LabelSpec{u8g2_font_haxrcorp4089_tr}, "Initializing...");
Label<20> fpsLabel({5, 3, AnchorPoint::TOP_CENTER}, new LabelSpec{u8g2_font_5x7_tr}, "FPS: 0.0");

ProgressBar bar({5, 5, AnchorPoint::CENTER}, 20, 6, 1);

Bitmap cursor({8, 3, AnchorPoint::TOP_LEFT}, 11, 16, cursorBMP, true);

Appearance visuals;
Appearance visualsFPS;

unsigned long previousTime = 0;
int frameCount = 0;
float fps = 0.0;
bool showGrid = true;

#ifdef DEBUG
void renderGrid() {
  for (unsigned int i = 0; i < grid.getHorizontalLines(); ++i) {
    unsigned int y = grid.getHorizontalLinePosition(i);
    u8g2.drawLine(0, y, u8g2.getDisplayWidth() - 1, y);
  }

  // Draw vertical lines
  for (int i = 0; i < grid.getVerticalLines(); ++i) {
    unsigned int x = grid.getVerticalLinePosition(i);
    u8g2.drawLine(x, 0, x, u8g2.getDisplayHeight() - 1);
  }
}
#else
void renderGrid() {}
#endif

void displayTask(void *p) {
  while (true) {
#ifdef FPS
    static int delta = 1;
    unsigned long currentTime = millis();
    frameCount++;

    if (currentTime - previousTime >= 1000) {
      fps = (float)frameCount / (currentTime - previousTime) * 1000;
      previousTime = currentTime;
      frameCount = 0;

      char fpsString[20];
      sprintf(fpsString, "FPS: %.2f", fps);
      fpsLabel.setText(fpsString);
    }

#endif

    u8g2.clearBuffer();

    if (showGrid)
      renderGrid(); // Draw the grid lines

#ifdef FPS
    fpsLabel.render(&uiContext);
#endif

    statusLabel.render(&uiContext);
    bar.render(&uiContext);
    cursor.render(&uiContext);
    u8g2.sendBuffer();
  }
}

void setup() {
  pinMode(BTN, INPUT);
  pinMode(3, INPUT);

  Serial.begin(115200);

  u8g2.begin();

  u8g2.setFontRefHeightExtendedText();
  u8g2.setDrawColor(1);
  u8g2.setFontPosTop();
  u8g2.setFontDirection(0);
  u8g2.setFontPosTop();

  visuals
      .setMargin(1)                                 // Margin  (optional, doesn't do anything right now)
      .setPadding(3)                                // Padding
      .setBorderType(Appearance::BorderType::SOLID) // (i hate clang-format for not having fluent support)
      .setBorderSize(3);                            //

  visualsFPS = visuals;
  visualsFPS.borderSize = 0;

  statusLabel.setAppearance(visuals);
  fpsLabel.setAppearance(visualsFPS);
  cursor.setAppearance(visuals);

  xTaskCreate(displayTask, "Display Task", 4096, NULL, 1, NULL);
}

void loop() {
  if (digitalRead(BTN) == LOW) {
    statusLabel.setText("Pressed!");
    cursor.setGridPos({8, 3, UILib::AnchorPoint::CENTER});
    return;
  } else {
    statusLabel.setText("Released!");
  }

  showGrid = !digitalRead(3);
  int cursorX = static_cast<int>(sin(millis() / 1000.0) * 50 + 64); // Center around x = 64
  int cursorY = static_cast<int>(cos(millis() / 1000.0) * 20 + 32); // Center around y = 32

  cursor.setCoords(cursorX, cursorY);
}

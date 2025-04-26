#include <Arduino.h>
#include <U8g2lib.h>
#include <cstdint>
#include <cstdlib>
#include <oled_ui.h>

#include "esp32-hal-gpio.h"
#include "grid.h"

#define BTN 2

using namespace UILib;

U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);
Grid grid(u8g2.getDisplayWidth(), u8g2.getDisplayHeight(), 8, 6);
// Grid grid(100, 50, 8, 6);

Context uiContext(&u8g2, &grid);

Label<20> statusLabel(2, 3, GridAlignment::LEFT, GridAlignment::RIGHT, new LabelSpec(u8g2_font_haxrcorp4089_tr),
                      "Initializing...");
Label<20> fpsLabel(0, 0, GridAlignment::LEFT, GridAlignment::TOP, new LabelSpec(u8g2_font_5x7_tr), "");
Label<20> memoryLabel(0, 6, GridAlignment::LEFT, GridAlignment::TOP, new LabelSpec(u8g2_font_5x7_tr), "");

ProgressBar bar(60, 5, 0, 50, 10, 100);

Appearance visuals;
Appearance visualsFPS;

unsigned long previousTime = 0;
int frameCount = 0;
float fps = 0.0;

void displayTask(void *p) {
  while (true) {
    uint32_t mem = xPortGetFreeHeapSize();

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

    char buf[20];
    itoa(mem, buf, 10);
    memoryLabel.setText(buf);

    u8g2.clearBuffer();

    fpsLabel.render(&uiContext, &visualsFPS);
    memoryLabel.render(&uiContext, &visualsFPS);

    if (bar.getProgress() >= 100) {
      delta = -1;
    } else if (bar.getProgress() <= 0) {
      delta = 1;
    }

    bar += delta;

    statusLabel.render(&uiContext, &visuals);
    bar.render(&uiContext, nullptr);

    u8g2.sendBuffer();
  }
}

void setup() {
  pinMode(BTN, INPUT);

  Serial.begin(115200);

  u8g2.begin();

  u8g2.setFontRefHeightExtendedText();
  u8g2.setDrawColor(1);
  u8g2.setFontPosTop();
  u8g2.setFontDirection(0);
  u8g2.setFontPosTop();

  visuals.setMargin(1);
  visuals.setPadding(6);

  visuals.borderType = Appearance::BorderType::SOLID;
  visuals.borderSize = 3;

  visualsFPS = visuals;
  visualsFPS.borderSize = 0;

  xTaskCreate(displayTask, "Display Task", 4096, NULL, 1, NULL);
}

void loop() {
  if (digitalRead(BTN) == LOW)
    statusLabel.setText("Pressed!");
  else
    statusLabel.setText("Released!");
}

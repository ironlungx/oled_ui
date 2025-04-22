#include <Arduino.h>
#include <U8g2lib.h>
#include <oled_ui.h>

using namespace UILib;

U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);
Context uiContext(&u8g2);

Label<50> statusLabel(40, 25, new LabelSpec(u8g2_font_haxrcorp4089_tr), "Initializing...");
Label<50> fpsLabel(5, 5, new LabelSpec(u8g2_font_5x7_tr), ""); // Label to display FPS
ProgressBar bar(60, 5, 0, 50, 10);

Appearance visuals;
Appearance visualsFPS;

unsigned long previousTime = 0;
int frameCount = 0;
float fps = 0.0;

void setup() {
  u8g2.begin();
  setCpuFrequencyMhz(240);

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
}

void loop() {
  static int delta = 1;
  unsigned long currentTime = millis();
  frameCount++;

  if (currentTime - previousTime >= 1000) {
    fps = (float)frameCount / (currentTime - previousTime) * 1000;
    previousTime = currentTime;
    frameCount = 0;

    char fpsString[50];
    sprintf(fpsString, "FPS: %.2f", fps);
    fpsLabel.setText(fpsString);
  }

  u8g2.clearBuffer();

  fpsLabel.render(&uiContext, &visualsFPS); // Render the FPS label

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

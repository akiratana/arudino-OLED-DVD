#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
 #include "bitmap.h"
 
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// SPI用の定義（CS, DC, RESET）
#define OLED_MOSI   11  // ハードウェアSPI（固定）
#define OLED_CLK    13  // ハードウェアSPI（固定）
#define OLED_DC     9
#define OLED_CS     10
#define OLED_RESET  8//未使用

const int bmpWidth =32;
const int bmpHeight = 15;

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &SPI, OLED_DC, OLED_RESET, OLED_CS);

// テキスト位置と速度
int x = 0;
int y = 0;
int dx = 1;
int dy = 1;

void setup() {
  // 初期化
  if (!display.begin(SSD1306_SWITCHCAPVCC)) {
    for (;;); // エラー時は停止
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.display();
}

void loop() {
  display.clearDisplay();
  display.setCursor(x, y);
  //display.print("Hello!");
  display.drawBitmap(x, y, epd_bitmap_dvd_logo_black_and_white, bmpWidth, bmpHeight, SSD1306_WHITE);
  display.display();

 
  x += dx;
  y += dy;

  // 画面の端で跳ね返る処理
  if (x <= 0 || x + bmpWidth >= SCREEN_WIDTH) dx = -dx;
  if (y <= 0 || y + bmpHeight >= SCREEN_HEIGHT) dy = -dy;

  delay(50); // 移動スピード調整
}

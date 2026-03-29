#include <MD_MAX72xx.h>
#include <SPI.h>

#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 1
#define CS_PIN 5

MD_MAX72XX mx(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

byte heart[8] = {
  B00000000,
  B01100110,
  B11111111,
  B11111111,
  B01111110,
  B00111100,
  B00011000,
  B00000000
};

byte current[8] = {0};

void setup() {
  mx.begin();
  mx.control(MD_MAX72XX::INTENSITY, 8);
  mx.clear();
}

// Drop ONE pixel with gravity in a column
void dropPixel(int col, int targetRow) {
  for (int row = 0; row <= targetRow; row++) {
    mx.clear();

    // draw existing pixels
    for (int i = 0; i < 8; i++) {
      mx.setRow(i, current[i]);
    }

    // draw falling pixel
    mx.setPoint(row, col, true);
    delay(80);

    // stop at target row or on another pixel
    if (row == targetRow || (current[row + 1] & (1 << col))) {
      current[row] |= (1 << col);
      break;
    }
  }
}

void loop() {
  memset(current, 0, sizeof(current));
  mx.clear();

  // Build from bottom to top
  for (int row = 7; row >= 0; row--) {
    for (int col = 0; col < 8; col++) {

      // If this pixel belongs to the heart
      if (heart[row] & (1 << col)) {
        dropPixel(col, row);
      }
    }
  }

  delay(2500);
  mx.clear();
  delay(1200);
}

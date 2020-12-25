/*
  Author: Aleksi Jarva, Arttu Terhokoski
  Mikrokontrollerit 5S00DE75-3002
  Project: Ulkovalojen ohjaus
  File: keyboard.ino
  Description: Function definitions for 4x4 keybad module.
*/

void readKeyboard() {
  // Start condition for row scan in 2x4 keyboard
  byte xMask = B11111011;

  // Nested loop to scan keyboard row by row
  // and column by column
  for (int i = 0; i < 4; i++) {
    PORTB = xMask & B11111111;

    byte yMask = B00000010;

    for (int k = 0; k < 2; k++) {
      delay(1);
      byte rowPressed = PINC & B00000011;

      if (rowPressed == (yMask & B00000011)) {
        kB.row = k;
        kB.column = i;
        break;
      }
      yMask <<= 1;
      yMask++;
    }
    xMask <<= 1;
    xMask++;
  }
}

/*
  Author: Aleksi Jarva, Arttu Terhokoski
  Mikrokontrollerit 5S00DE75-3002
  Project: Ulkovalojen ohjaus
  File: keyboard.h
  Description: This module controls 4x4 keypad. This file
  includes datastruct and function declarations.
  declarations.
*/

#ifndef KEYBOARD_H
#define KEYBOARD_H

// Correction table for keyboard to print
// correct ASCII character
const char correctionTable[4][4] =
{
  {49, 50, 51, 65},
  {52, 53, 54, 66},
  {55, 56, 57, 67},
  {42, 48, 35, 68}
};

// Datastruct to store data of key presed
struct keyBoard {
  volatile int row;
  volatile int column;
};

// Description: Scan algorithm to detect which key is pressed
void readKeyboard();

#endif

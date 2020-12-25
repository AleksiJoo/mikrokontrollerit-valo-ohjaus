/*
  Author: Aleksi Jarva, Arttu Terhokoski
  Mikrokontrollerit 5S00DE75-3002
  Project: Ulkovalojen ohjaus
  File: display.h
  Description: This module controls printouts to LCD display.
  This file includes function declarations.
*/

#ifndef DISPLAY_H
#define DISPLAY_H

// Description: Print version and date to LCD screen
void printVersionAndDate();

// Description: Prints measured outside light intensity to LCD display
void printMeasured();

//Description: Prints control output to LEDS to LCD display
void printControl();

/* Description: Prints selected control mode to LCD display
   Parameter 1: control mode 'A' or 'M'
*/
void printMode(char mode);

// Description: Prints welcome screen to LCD display
void printWelcomeScreen();

// Description: Prints screen on manual mode if level not selected to LCD display
void printLevelNotSelected();

#endif

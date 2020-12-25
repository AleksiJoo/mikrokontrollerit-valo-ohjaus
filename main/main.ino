/*
  Author: Aleksi Jarva, Arttu Terhokoski
  Mikrokontrollerit 5S00DE75-3002
  Project: Ulkovalojen ohjaus
  File: main.ino
  Description: This is the main module for program
*/

#include "keyboard.h"
#include "display.h"
#include <LiquidCrystal.h>

// GLOBAL CONSTANTS
const int PWM_OUTPUT_PIN = 9;

// GLOBAL DATA STRUCTURES
struct TagTable {
  int outsideLevel;
  int ledOutput;
  int controlValue;
  char mode;

  // Constructor
  TagTable():
    outsideLevel(0), ledOutput(0), controlValue(0), mode('X')
  {
  }
};

// GLOBAL VARIABLES
keyBoard kB;
TagTable tags;
TagTable* tagPtr = &tags;
LiquidCrystal lcd(1, 0, 4, 5, 6, 7);
// RS,E,DB4,DB5,DB6,DB7

// GENERAL FUNCTIONS

/* Description: Reads outside luminosity and makes A/D conversion
   Parameter 1: Pointer to struct to store data
*/
void readOutsideLevel() {

  // Configuring ADC control and status register A
  // and starting single conversion
  ADCSRA = B11000111;

  // Waiting for conversion to be ready
  while ((ADCSRA & B01000000) != 0) {
  }

  // Scaling converted values with map library function
  // Reducting photoresistors forward voltage from 1023
  tags.outsideLevel = map(ADC, 0, 950, 0, 100);
  tags.ledOutput = map(ADC, 0, 950, 0, 255);
  tags.controlValue = 100 - map(tags.ledOutput, 0, 255, 0, 100);
}

// Description: Reads from PINC registry if key is pressed
bool isKeyPressed() {
  // returns TRUE if key is pressed
  return ((PINC & B00000011) != 3);
}

void setup() {

  // SETUP REGISTERS
 
  // All C port pins as input and pullup resistor on for C0 and C1
  DDRC = B00000000;
  PORTC = B00000011;

  // All B port pins to output mode and B2...B5 LOW
  // This is for keyboard HW interrupt sensing
  DDRB = B11111111;
  PORTB = B11000011;

  // A/D converter reference voltage selected to 5v and channel A7
  ADMUX = B01000111;

  // Configuring external interrupt registers
  // INT0 and INT1 will sense falling edge (10, 10)
  EICRA = B00001010;
  // Enable interrupt service
  EIMSK = B00000011;
  
  // END OF REGISTERS SETUP
  analogWrite(PWM_OUTPUT_PIN,0);
  
  lcd.begin(16, 2);
  printVersionAndDate();
}

// Interrupt service for INT0 (D2)
ISR(INT0_vect) {
  // Clear global interrupt
  cli();
  // Read keyboard
  readKeyboard();
  // Disable external interrupts (INT0, INT1)
  EIMSK = B00000000;
  // Set B2...5 to back to LOW before return
  PORTB = B11000011;
  // enable global interrupt
  sei();
}
// Interrupt service for INT1 (D3)
ISR(INT1_vect) {
  cli();
  readKeyboard();
  EIMSK = B00000000;
  PORTB = B11000011;
  sei();
}


void loop() {

  readOutsideLevel();
  char selectedKey = correctionTable[kB.row][kB.column];
  int manualControlLevel = 0;
  lcd.clear();

  if (!isKeyPressed()) {
    EIMSK = B00000011;
  }

  // Configuring control mode from keyboard input
  if (selectedKey == 'A') {
    tags.mode = 'A';
  }
  else if (selectedKey == 'B') {
    tags.mode = 'M';
  }

  // AUTO control mode
  if (tags.mode == 'A') {
    printMeasured();
    printMode(tags.mode);

    if (tags.outsideLevel < 70) {
      analogWrite(PWM_OUTPUT_PIN, 255 - tags.ledOutput);
      printControl();
    }
    else {
      analogWrite(PWM_OUTPUT_PIN, 0);
      lcd.setCursor(0, 1);
      lcd.print("Lights off");
    }
  }

  // MANUAL mode control
  else if (tags.mode == 'M') {

    if (selectedKey == '1') {
      manualControlLevel = 13;
      tags.controlValue = 5;
    }
    else if (selectedKey == '2') {
      manualControlLevel = 63;
      tags.controlValue = 25;
    }
    else if (selectedKey == '3') {
      manualControlLevel = 128;
      tags.controlValue = 50;
    }
    else if (selectedKey == '4') {
      manualControlLevel = 191;
      tags.controlValue = 75;
    }
    else if (selectedKey == '5') {
      manualControlLevel = 255;
      tags.controlValue = 100;
    }
    //Led off when number 6 is pressed
    else if (selectedKey == '6') {
      manualControlLevel = 0;
      tags.controlValue = 0;
      printLevelNotSelected();
    }
    //If manual control level is not chosen or it is 0, program asks for it
    else {
      printLevelNotSelected();
    }

    // Printing default view to LCD display
    if (manualControlLevel > 0) {
      printMeasured();
      printControl();
      printMode(tags.mode);
    }
    analogWrite(PWM_OUTPUT_PIN, manualControlLevel);

  }
  else {
    printWelcomeScreen();
  }
  delay(150);
}

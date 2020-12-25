/*
  Author: Aleksi Jarva, Arttu Terhokoski
  Mikrokontrollerit 5S00DE75-3002
  Project: Ulkovalojen ohjaus
  File: display.h
  Description: Function definitions for display module
*/

void printVersionAndDate() { 
  lcd.setCursor(0,0);
  lcd.print("Version: 1.0");
  lcd.setCursor(0,1);
  lcd.print("Date:");
  lcd.setCursor(9,1);
  lcd.print("DEC/2020");
  delay(5000);
}

void printMeasured() {
  lcd.setCursor(0, 0);
  lcd.print("M:");
  lcd.setCursor(3, 0);
  lcd.print(tags.outsideLevel);
  lcd.setCursor(6, 0);
  lcd.print("%");
}

void printControl() {
  lcd.setCursor(0, 1);
  lcd.print("C:");
  lcd.setCursor(3, 1);
  lcd.print(tags.controlValue);
  lcd.setCursor(6, 1);
  lcd.print("%");
}

void printMode(char mode) {
  lcd.setCursor(11, 0);
  if (mode == 'A') {
    lcd.print("mode: AUT");
  }
  else if (mode == 'M') {
    lcd.print("mode: MAN");
  }
}

void printWelcomeScreen() {
  lcd.setCursor(0, 0);
  lcd.print("Welcome");
  lcd.setCursor(0, 1);
  lcd.print("Select AUTO / MANUAL");
}

void printLevelNotSelected() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Lights off");
  lcd.setCursor(0, 1);
  lcd.print("Select level 1-5");
}

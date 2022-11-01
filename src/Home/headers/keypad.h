//
// Created by Jan Andreasen on 31/10/2022.
//

#ifndef H5_EMBEDDED_PROJECT_KEYPAD_H
#define H5_EMBEDDED_PROJECT_KEYPAD_H

#include "../../../.pio/libdeps/mkrwifi1010/Keypad/src/Keypad.h"

#define ROWS 4												// Number of rows in keypad
#define COLS 4												// Number of columns in keypad

byte rowPins[ROWS] = {12, 11, 10, 9};	// Pin numbering for rows in keypad
byte colPins[COLS] = {8, 7, 6, 5};	// Pin numbering for columns in keypad

char text[4];												// Creates an array of chars for the sevseg
char pwd[4] = {'1', '3', '3', '7'};		// The "correct" password for the keypad
char pwdTest[4];											// Empty array for testing the PW
char keys[COLS][ROWS] = {
        {'1', '2', '3', 'A'},
        {'4', '5', '6', 'B'},
        {'7', '8', '9', 'C'},
        {'*', '0', '#', 'D'}
};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

int pwdCount = 0;

void checkPassword(char key);
void keyIn();
bool comparePassword(char pw[]);

#endif //H5_EMBEDDED_PROJECT_KEYPAD_H

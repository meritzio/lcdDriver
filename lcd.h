#ifndef LCD_H
#define LCD_H
#include<stdbool.h>
#include "lcdPort.h"

///Create an lcd screen reference
typedef struct LcdHandle
{
    ///Register Select Pin
    LcdPort rs;
    ///Read/Write
    LcdPort rw;
    ///Enable
    LcdPort en;
    ///Digital out 0
    LcdPort db4;
    ///Digital out 1
    LcdPort db5;
    ///Digital out 2
    LcdPort db6;
    ///Digital out 3
    LcdPort db7;
    ///Row Length
    unsigned int rowLength;
    ///Number of Rows
    unsigned int rowCount;
    ///Position
    unsigned int position;
} LcdHandle;

///Construct the LcdHandle specifying which digital out pins are referenced
LcdHandle lcdConstruct(LcdPort rs, LcdPort rw, LcdPort en, LcdPort db4, LcdPort db5, LcdPort db6, LcdPort db7,
                        unsigned int rowLength, unsigned int rowCount);
///Run the start procedure to initialise the screen and start 4 bit mode
void lcdInitialize(LcdHandle* lcd);
///Clear all characters on the display
void lcdClearDisplay(LcdHandle* lcd);
///Specify how the lcd should appear
void lcdSetAppearance(LcdHandle* lcd, bool displayOn, bool cursorOn, bool cursorBlinking);
///Shift all characters left
void lcdShiftLeft(LcdHandle* lcd);
///Shift all characters right
void lcdShiftRight(LcdHandle* lcd);
///Move the cursor left (loops around at position 0)
void lcdCursorLeft(LcdHandle* lcd);
///Move the cursor right (loops back to position 0)
void lcdCursorRight(LcdHandle* lcd);
///Move the cursor to the start of row 1
void lcdCursorRow1(LcdHandle* lcd);
///Move the cursor to the start of row 2
void lcdCursorRow2(LcdHandle* lcd);
///Send the registers state rising the enable line
void lcdSend(LcdHandle* lcd);
///Send command (bits RS, R/W, DB7, DB6, DB5, DB4)
void lcdCommand(LcdHandle* lcd, int command);
///Send a character to the LCD
void lcdChar(LcdHandle* lcd, char value);
///Send an array of characters to the LCD
void lcdMessage(LcdHandle* lcd, char* message);
///(Internal use) track the cursor motion by a quantity
void lcdMotion(LcdHandle* lcd, int amount);

#endif


#include "lcd.h"

LcdHandle lcdConstruct(
    LcdPort rs, LcdPort rw, LcdPort en,
    LcdPort db4, LcdPort db5, LcdPort db6, LcdPort db7,
    unsigned int rowLength, unsigned int rowCount)
{
    LcdHandle lcd;
    lcd.rs = rs;
    lcd.rw = rw;
    lcd.en = en;
    lcd.db4 = db4;
    lcd.db5 = db5;
    lcd.db6 = db6;
    lcd.db7 = db7;
    lcd.rowLength = rowLength;
    lcd.rowCount = rowCount;
    lcd.position = 0;
    return lcd;
}

void lcdInitialize(LcdHandle* lcd)
{
    //delay(30); //Wait for Vcc to rise
    for(int i = 0; i < 2000000; i++); 
    lcdCommand(lcd, 0x3U);
    for(int i = 0; i < 2000000; i++); 
    lcdCommand(lcd, 0x3U);
    for(int i = 0; i < 2000000; i++); 
    lcdCommand(lcd, 0x3U);
    for(int i = 0; i < 2000000; i++); 
    lcdCommand(lcd, 0x2U);
}

void lcdClearDisplay(LcdHandle* lcd)
{
    lcdCommand(lcd, 0x0U);
    lcdCommand(lcd, 0x1U);
    lcd->position = 0;
}

void lcdSetAppearance(LcdHandle* lcd, bool displayOn, bool cursorOn, bool cursorBlinking)
{
    lcdCommand(lcd, 0x0U);
    if(displayOn && cursorOn)
    {
        lcdCommand(lcd, cursorBlinking ? 0xFU : 0xEU);
    }
    else if (displayOn)
    {
        lcdCommand(lcd, 0xCU);
    }
    else
    {
        lcdCommand(lcd, 0x8U);
    }
}

void lcdShiftLeft(LcdHandle* lcd)
{
    lcdCommand(lcd, 0x1U);
    lcdCommand(lcd, 0x8U);
    lcdMotion(lcd, -1);
}

void lcdShiftRight(LcdHandle* lcd)
{
    lcdCommand(lcd, 0x1U);
    lcdCommand(lcd, 0xCU);
    lcdMotion(lcd, 1);
}

void lcdCursorLeft(LcdHandle* lcd)
{
    lcdCommand(lcd, 0x1U);
    lcdCommand(lcd, 0x0U);
    lcdMotion(lcd, -1);
}

void lcdCursorRight(LcdHandle* lcd)
{
    lcdCommand(lcd, 0x1U);
    lcdCommand(lcd, 0x4U);
    lcdMotion(lcd, 1);
}

void lcdCursorRow1(LcdHandle* lcd)
{
    lcdCommand(lcd, 0x8U);
    lcdCommand(lcd, 0x0U);
    lcd->position = 0x0U;
}

void lcdCursorRow2(LcdHandle* lcd)
{
    lcdCommand(lcd, 0xCU);
    lcdCommand(lcd, 0x0U);
    lcd->position = lcd->rowLength;
}

void lcdSend(LcdHandle* lcd)
{
    int i = 0; //Check bits hi or lo by bitmask
    LcdPort* enable = &(lcd->en);
    lcdPortState(enable, false); //Send enable signal
    for(i = 0; i < 8000; i++);   //Pause
    lcdPortState(enable,  true); //Send enable signal
    for(i = 0; i < 8000; i++);   //Pause
    lcdPortState(enable, false); //Send enable signal
}

void lcdCommand(LcdHandle* lcd, int command)
{
    lcdPortState(&(lcd->db4), (command & (1U << 0)) > 0);
    lcdPortState(&(lcd->db5), (command & (1U << 1)) > 0);
    lcdPortState(&(lcd->db6), (command & (1U << 2)) > 0);
    lcdPortState(&(lcd->db7), (command & (1U << 3)) > 0);
    lcdPortState(&(lcd->rw), (command & (1U << 4)) > 0);
    lcdPortState(&(lcd->rs), (command & (1U << 5)) > 0);
    lcdSend(lcd);
}

void lcdChar(LcdHandle* lcd, char value)
{
    int command0 = value >> 4, //RS HI
    command1 = value & 0xF;
    command0 |= 1U << 5;
    command1 |= 1U << 5;
    lcdCommand(lcd, command0);
    lcdCommand(lcd, command1);
    lcdMotion(lcd, 1);
}

void lcdMessage(LcdHandle* lcd, char* message)
{
    while(*message)
    {
        lcdChar(lcd, *message);
        message++;
    }
}

void lcdMotion(LcdHandle* lcd, int amount)
{
    unsigned int position = lcd->position,
    newPosition = position + amount;
    if(((int)position + amount) > -1)
    {
        if (newPosition % lcd->rowLength == 0) //If changing row
        {
            switch (newPosition / lcd->rowLength)
            {
                case 0:
                    lcdCursorRow1(lcd);
                    break;
                case 1:
                    lcdCursorRow2(lcd);
                    break;
                default: //If above max rows then loop back
                    lcdCursorRow1(lcd);
                    break;
            }
        }
        else //If on a row simply update position
        {
            lcd->position = newPosition;
        }
    }
    else //Looping back to end of last row
    {
        int iL = lcd->rowLength * lcd->rowCount;
        //Since row count not known, safer to move right rowLength*rowCount from 0
        for(int i = 0; i < iL; i++)
        {
            lcdCursorRight(lcd);
        }
    }
}

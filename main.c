#include "TM4C123.h"                    // Device header
#include<stdbool.h>
#include "lcd.h"

int main(void)
{
    LcdHandle lcd = lcdConstruct(
        lcdPortConstruct('F',2), //RS PF2
        lcdPortConstruct('F',3), //RW PF3
        lcdPortConstruct('B',3), //EN PB3
        lcdPortConstruct('C',7), //DB4 PC7
        lcdPortConstruct('C',6), //DB5 PC6
        lcdPortConstruct('C',5), //DB6 PC5
        lcdPortConstruct('C',4)  //DB7 PC4
    );
	  LcdHandle* lcdPtr = &lcd;
    
    lcdInitialize(lcdPtr);
    lcdClearDisplay(lcdPtr);
    lcdCommand(lcdPtr, 0x0U);
    lcdCommand(lcdPtr, 0xFU);
    lcdSetAppearance(&lcd, true, true, true);
    lcdMessage(lcdPtr, "Hello World");
    //lcdCursorRight(&lcd);
    while(true){};
}

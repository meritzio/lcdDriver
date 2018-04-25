#include "TM4C123.h"                    // Device header
#include<stdbool.h>
#include "lcd.h"

int main(void)
{
    //Port wiring specification of LED
    LcdHandle lcdScreen = lcdConstruct(
        lcdPortConstruct('F', 2),
        lcdPortConstruct('F', 3),
        lcdPortConstruct('B', 3),
        lcdPortConstruct('C', 7),
        lcdPortConstruct('C', 6),
        lcdPortConstruct('C', 5),
        lcdPortConstruct('C', 4),
        16,
        2
    );
    
    LcdHandle* lcd = &lcdScreen; //ptr Convenience
    lcdInitialize(lcd);
    lcdClearDisplay(lcd);
    lcdSetAppearance(lcd, true, true, true);
    lcdMessage(lcd, "Hello World");
    
    while(true)
    {
        for(int i = 0; i < 640000; i++);
        lcdShiftLeft(lcd);    
    };
}

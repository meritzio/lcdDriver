#ifndef LCDPORT_H
#define LCDPORT_H

#include<stdbool.h>
#include<stdlib.h>
#include "TM4C123.h"

typedef struct LcdPort
{
    ///The Digital Output Port to send data to
    GPIOA_Type* gpio;
    ///The port pin to set hi or lo
    int pin;
} LcdPort;

///Make a new lcdPort
LcdPort lcdPortConstruct(char port, int pin);
///Set port state hi or lo
void lcdPortState(LcdPort* port, bool hi);

#endif


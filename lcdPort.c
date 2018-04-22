#include "lcdPort.h"

LcdPort lcdPortConstruct(char port, int pin)
{
    GPIOA_Type* gpio;
    int rcgcBit;
    LcdPort lPort;
    
    switch(port)
    {
        case 'A':
        gpio = GPIOA;
        rcgcBit = 0;
        break;
        case 'B':
        gpio = GPIOB;
        rcgcBit = 1;
        break;
        case 'C':
        gpio = GPIOC;
        rcgcBit = 2;
        break;
        case 'D':
        gpio = GPIOD;
        rcgcBit = 3;
        break;
        case 'E':
        gpio = GPIOE;
        rcgcBit = 4;
        break;
        case 'F':
        gpio = GPIOF;
        rcgcBit = 5;
        break;
        default: break;
    }
    
    SYSCTL->RCGCGPIO |= 1U << rcgcBit;
    gpio->LOCK = 0x4C4F434B;
    gpio->CR   |= 1U << pin;
    gpio->DIR  |= 1U << pin;
    gpio->DEN  |= 1U << pin;
    
    lPort.gpio = gpio;
    lPort.pin  = pin;
    return lPort;
}

void lcdPortState(LcdPort* port, bool hi)
{
    if (hi) {
        port->gpio->DATA |= 1U << (port->pin);
    }
    else {
        port->gpio->DATA &= ~(1U << (port->pin));
    }
}


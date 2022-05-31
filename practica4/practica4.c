#pragma config FOSC = INTOSCIO
#pragma WDTE = OFF
#pragma PWRTE = ON
#pragma MCLRE = OFF
#pragma BOREN = OFF
#pragma LVP = OFF
#pragma CPD = OFF
#pragma CP = OFF

#include <xc.h>
#include <pic16f628.h>

#define _XTAL_FREQ 4000000
#define ENT PORTAbits.RA2
#define SAL PORTBbits.RB4

void_interrupt() Vectorinterupcion(void){
    if (EEIF==1)
    {
        EEIF=0;
    }
}

void ConfigPIC(){

    TRISA = 0B11111111;
    TRISB = 0X00;
    CMCON = 0X07;
    PORTA = 0;
    PORTB = 0;
}

void main(void){
    ConfigPIC();
    while (1)
    {
        if (ENT == 0)
        {
            SAL = 0;
        }
        if (ENT == 1)
        {
            SAL = 1; 
        }
    }

    return 0;
    
}
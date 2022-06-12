/*
 * File:   LecturaPuertos.c
 * Author: Ismael Cervantes de Anda
 * Código para configurar los puertos de un PIC16F628A
 * Created on 20 de mayo de 2022, 09:27 AM
 */
// PIC16F628A Configuration Bit Settings

// 'C' source line config statements

// CONFIG
#pragma config FOSC = INTOSCIO  // Oscillator Selection bits (INTOSC oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config MCLRE = OFF      // RA5/MCLR/VPP Pin Function Select bit (RA5/MCLR/VPP pin function is digital input, MCLR internally tied to VDD)
#pragma config BOREN = OFF      // Brown-out Detect Enable bit (BOD disabled)
#pragma config LVP = OFF        // Low-Voltage Programming Enable bit (RB4/PGM pin has digital I/O function, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EE Memory Code Protection bit (Data memory code protection off)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#include <pic16f628a.h>

#define _XTAL_FREQ 4000000

#define Ent0 PORTAbits.RA0
#define Ent1 PORTAbits.RA1
#define Ent2 PORTAbits.RA2
#define Ent3 PORTAbits.RA3
#define Ent4 PORTAbits.RA4
#define Ent5 PORTAbits.RA5
#define Ent6 PORTAbits.RA6
#define Ent7 PORTAbits.RA7

#define Sal0 PORTBbits.RB0
#define Sal1 PORTBbits.RB1
#define Sal2 PORTBbits.RB2
#define Sal3 PORTBbits.RB3
#define Sal4 PORTBbits.RB4
#define Sal5 PORTBbits.RB5
#define Sal6 PORTBbits.RB6
#define Sal7 PORTBbits.RB7

#define GIE INTCONbits.GIE
#define TOIE INTCONbits.T0IE
#define TOIF INTCONbits.T0IF
#define PEIE INTCONbits.PEIE


char    var7seg;
char    continter;

void __interrupt() VectorInterrupcion(void)              // Funciones de interrupción.
{
    if (EEIF == 1) {EEIF = 0;}                          //interrupción por fin de escritura en EEPROM
}

void ConfigPIC(void)
{
    TRISA = 0B11111111;         //Puerto A como entradas
    TRISB = 0x00;               //Puerto B como salidas
    CMCON = 0x07;               //Terminales del puerto A como entradas digitales
    PORTA = 0;
    PORTB = 0;
}

void main(void)
{
    ConfigPIC();
    
    while (1)
    {   if (Ent3 == 0)  {   Sal2 = 0;}
        if (Ent3 == 1)  {   Sal2 = 1;}
    }
    return;
}
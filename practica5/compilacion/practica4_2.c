// CONFIG
#pragma config FOSC = INTOSCIO  // Oscillator Selection bits (INTOSC oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)#pragma config PWRTE = ON     // Power-up Timer Enable bit (PWRT enabled)
#pragma config MCLRE = OFF      // RA5/MCLR/VPP Pin Function Select bit (RA5/MCLR/VPP pin function is digital input, MCLR internally tied to VDD)
#pragma config BOREN = OFF      // Brown-out Detect Enable bit (BOD disabled)
#pragma config LVP = OFF        // Low-Voltage Programming Enable bit (RB4/PGM pin has digital I/O function, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EE Memory Code Protection bit (Data memory code protection off)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

//#pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#include <pic16f628a.h>
#define _XTAL_FREQ 4000000
#define Bit7 PORTAbits.RA7
#define Bit6 PORTAbits.RA6
#define Bit5 PORTAbits.RA5
#define Bit4 PORTAbits.RA4
#define Bit3 PORTAbits.RA3
#define Bit2 PORTAbits.RA2
#define Bit1 PORTAbits.RA1
#define Bit0 PORTAbits.RA0

#define RxUART PORTBbits.RB1
#define TxUART PORTBbits.RB2
#define Led_Tx PORTBbits.RB6
#define Led_Rx PORTBbits.RB7

#define GIE INTCONbits.GIE
#define TOIE INTCONbits.T0IE
#define TOIF INTCONbits.T0IF
#define PEIE INTCONbits.PEIE

#define SPEN RCSTAbits.SPEN
#define CREN RCSTAbits.CREN

#define TRMT TXSTAbits.TRMT

#define RCIE PIE1bits.RCIE
#define TXIE PIE1bits.TXIE

#define TXIF PIR1bits.TXIF
#define RCIF PIR1bits.RCIF

char ByteRx;
char TxUSART;
void __interrupt() VectorInterrupcion(void)         // Funciones de interrupción.
{
    if (RCIF == 1)                                  //Interrupción por uso de UART (RS-232)
    {   
        GIE = 0;                    //Desactivación general de interrupciones
        ByteRx = RCREG;RCIF = 0;                   //Limpia la bandera de interrupción por recepción
        GIE = 1;                    //Activa las interrupciones
    }
}

void ConfigPIC(void)
{
    
    TRISA = 0B11111111;         //Puerto A como entradas
    TRISB = 0B00000010;         //Puerto B como salidas solo bit 1 como entrada
    CMCON = 0X07;               //Terminales del puerto A como I/O digitales
    PORTA = 0;
    PORTB = 0;
}

void ConfigUSART(void)          //Configuracion_USART  9600 BPS, sin bit de paridad, 1 bit stop
{
    TXIE = 0;                   //Desactiva interrupción por fin de transmisiónpor usart.
    TXSTA = 0B00100110;
    SPBRG = 25;
    RCSTA =0B10010000;
    //Este bit es parte del registro RCSTA    SPEN =1;                      //Habilitación del puerto de comunicaciónserial
    //Este bit es parte del registro RCSTA    CREN = 1;                     //Activa la recepcióncontinua    
    RCIE = 1;                                                               //Activar interrupción por fin de recepción por usart.
    TXIF = 0;
    RCIF = 0;
    GIE = 1;                    //Activar habilitador general de interrupciones.
    PEIE = 1;  //Activar habilitador general de interrupciones por periféricos.
    RCREG = 0;
}

void Transmite(void)            //Transmite por RS-232 9600 BPS, sin bit de paridad, 1 bit stop
{
    TXSTA = 0B00100110;
    SPBRG = 25;
    TXREG = TxUSART;
    while(!TXIF);
    while(!TRMT);               //Esta bandera es la que funciona para detectar cuando se vacíael buffer de transmisión
}
void main(void)
{
    ConfigPIC();
    ConfigUSART();
    while (1){   
        TxUSART = PORTA;
        Led_Tx = 1;
        Transmite();
        __delay_us(100);
        Led_Tx = 0;
        __delay_ms(1000);
        }
    return;
}
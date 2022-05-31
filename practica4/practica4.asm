#include <p16f628a.inc>

__CONFIG_INTOSC_OSC_NOCLKOUT&_WDT_OFF&_PWRTE_ON&_MCLRE_OFF&_BOREN_OFF&_BODEN_OFF&_LVP_OFF&_CPD_OFF&_CP_ON

w equ 0x00
status equ 0x03
porta equ 0x05
protb equ 0x06
trisa equ 0x85
trisb equ 0x86
cmcon equ 0x07
ro0 equ 0x05
rp1 equ 0x06
    org 0x00
    goto inicio
    org 0x04
    retfie
inicio
    bcf status, rp1
    bsf status, rp0
    movlw 0xff
    movwf trisa
    movlw b'00000000'
    mowf trisb
    bcf status,rp1
    movlow b'00000111'
    movwf cmcon
ciclo
    btfsc porta,2
    goto enciende
    goto apaga
enciende
    bsf portb, 4
    goto ciclo
apaga
    bcf portb,4
    goto ciclo
    end
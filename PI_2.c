/* 
 * File:   main.c
 * Author: dafne
 *
 * Created on 12 de octubre de 2021, 10:53 PM
 */

// PIC18F4550 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1L
#pragma config PLLDIV = 1       // PLL Prescaler Selection bits (No prescale (4 MHz oscillator input drives PLL directly))
#pragma config CPUDIV = OSC1_PLL2// System Clock Postscaler Selection bits ([Primary Oscillator Src: /1][96 MHz PLL Src: /2])
#pragma config USBDIV = 1       // USB Clock Selection bit (used in Full-Speed USB mode only; UCFG:FSEN = 1) (USB clock source comes directly from the primary oscillator block with no postscale)

// CONFIG1H
#pragma config FOSC = INTOSCIO_EC// Oscillator Selection bits (Internal oscillator, port function on RA6, EC used by USB (INTIO))
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
#pragma config IESO = OFF       // Internal/External Oscillator Switchover bit (Oscillator Switchover mode disabled)

// CONFIG2L
#pragma config PWRT = OFF       // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOR = ON         // Brown-out Reset Enable bits (Brown-out Reset enabled in hardware only (SBOREN is disabled))
#pragma config BORV = 3         // Brown-out Reset Voltage bits (Minimum setting 2.05V)
#pragma config VREGEN = OFF     // USB Voltage Regulator Enable bit (USB voltage regulator disabled)

// CONFIG2H
#pragma config WDT = ON         // Watchdog Timer Enable bit (WDT enabled)
#pragma config WDTPS = 32768    // Watchdog Timer Postscale Select bits (1:32768)

// CONFIG3H
#pragma config CCP2MX = ON      // CCP2 MUX bit (CCP2 input/output is multiplexed with RC1)
#pragma config PBADEN = ON      // PORTB A/D Enable bit (PORTB<4:0> pins are configured as analog input channels on Reset)
#pragma config LPT1OSC = OFF    // Low-Power Timer 1 Oscillator Enable bit (Timer1 configured for higher power operation)
#pragma config MCLRE = ON       // MCLR Pin Enable bit (MCLR pin enabled; RE3 input pin disabled)

// CONFIG4L
#pragma config STVREN = ON      // Stack Full/Underflow Reset Enable bit (Stack full/underflow will cause Reset)
#pragma config LVP = ON         // Single-Supply ICSP Enable bit (Single-Supply ICSP enabled)
#pragma config ICPRT = OFF      // Dedicated In-Circuit Debug/Programming Port (ICPORT) Enable bit (ICPORT disabled)
#pragma config XINST = OFF      // Extended Instruction Set Enable bit (Instruction set extension and Indexed Addressing mode disabled (Legacy mode))

// CONFIG5L
#pragma config CP0 = OFF        // Code Protection bit (Block 0 (000800-001FFFh) is not code-protected)
#pragma config CP1 = OFF        // Code Protection bit (Block 1 (002000-003FFFh) is not code-protected)
#pragma config CP2 = OFF        // Code Protection bit (Block 2 (004000-005FFFh) is not code-protected)
#pragma config CP3 = OFF        // Code Protection bit (Block 3 (006000-007FFFh) is not code-protected)

// CONFIG5H
#pragma config CPB = OFF        // Boot Block Code Protection bit (Boot block (000000-0007FFh) is not code-protected)
#pragma config CPD = OFF        // Data EEPROM Code Protection bit (Data EEPROM is not code-protected)

// CONFIG6L
#pragma config WRT0 = OFF       // Write Protection bit (Block 0 (000800-001FFFh) is not write-protected)
#pragma config WRT1 = OFF       // Write Protection bit (Block 1 (002000-003FFFh) is not write-protected)
#pragma config WRT2 = OFF       // Write Protection bit (Block 2 (004000-005FFFh) is not write-protected)
#pragma config WRT3 = OFF       // Write Protection bit (Block 3 (006000-007FFFh) is not write-protected)

// CONFIG6H
#pragma config WRTC = OFF       // Configuration Register Write Protection bit (Configuration registers (300000-3000FFh) are not write-protected)
#pragma config WRTB = OFF       // Boot Block Write Protection bit (Boot block (000000-0007FFh) is not write-protected)
#pragma config WRTD = OFF       // Data EEPROM Write Protection bit (Data EEPROM is not write-protected)

// CONFIG7L
#pragma config EBTR0 = OFF      // Table Read Protection bit (Block 0 (000800-001FFFh) is not protected from table reads executed in other blocks)
#pragma config EBTR1 = OFF      // Table Read Protection bit (Block 1 (002000-003FFFh) is not protected from table reads executed in other blocks)
#pragma config EBTR2 = OFF      // Table Read Protection bit (Block 2 (004000-005FFFh) is not protected from table reads executed in other blocks)
#pragma config EBTR3 = OFF      // Table Read Protection bit (Block 3 (006000-007FFFh) is not protected from table reads executed in other blocks)

// CONFIG7H
#pragma config EBTRB = OFF      // Boot Block Table Read Protection bit (Boot block (000000-0007FFh) is not protected from table reads executed in other blocks)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h>
#include <stdbool.h>

#include "stdio.h"
#include "stdlib.h"
//#include <p18f4550.h>

/*
 * 
 */
int v, ready;

void TMR0_WriteTimer(uint16_t timerVal){
    // Write to the Timer0 registers
    TMR0H = (timerVal >> 8);
    TMR0L = (uint8_t) timerVal;
}

void parseNote(unsigned char n){
    int f = 0;
    uint16_t init = 0;
    switch(n){
        case 'c': //261.63 Hz
            f = 65;
            //f = 131;
            init = 63624; // T = 3822 us -> T/2 = 1911 us
            break;
        case 'd': //293.67 Hz
            f = 73;
            //f = 147;
            init = 63832; // T = 3405 us -> T/2 = 1703 us
            break;
        case 'e': //329.63 Hz
            f = 82;
            //f = 165;
            init = 64018; // T = 3034 us -> T/2 = 1517 us
            break;
        case 'f': //349.23 Hz
            f = 87;
            //f = 175;
            init = 64103; // T = 2864 us -> T/2 = 1432 us
            break;
        case 'g': //392 Hz
            f = 98;
            //f = 196;
            init = 64259; // T = 2551 us -> T/2 = 1276 us
            break;
        case 'a': //440 Hz
            f = 110;
            //f = 220;
            init = 64398; // T = 2273 us -> T/2 = 1137 us
            break;
        case 'b': //493.88 Hz
            f = 123;
            //f = 247;
            init = 64523; // T = 2025 us -> T/2 = 1012 us
            break;
        case 'C': //277.18 Hz
            f = 70;
            //f = 139;
            init = 63731; // T = 3608 us -> T/2 = 1804 us
            break;
        case 'D': //311.13 Hz
            f = 78;
            //f = 156;
            init = 63928; // T = 3214 us -> T/2 = 1607 us
            break;
        case 'F': //369.99 Hz
            f = 92;
            //f = 185;
            init = 64183; // T = 2703 us -> T/2 = 1352 us
            break;
        case 'G': //415.3 Hz
            f = 104;
            //f = 208;
            init = 64331; // T = 2408 us -> T/2 = 1204 us
            break;
        case 'A': //466.16 Hz
            f = 116;
            //f = 233;
            init = 64462; // T = 2145 us -> T/2 = 1073 us
            break;
        // ...
        case 's': //0 Hz
            f = 0;
            init = 0;
            break;
        default: // case 'c' -> 261.63 Hz
            f = 65;
            //f = 131;
            init = 63624; // T = 3822 us -> T/2 = 1911 us          
            break;
    }
    T0CONbits.TMR0ON = 0;
    INTCONbits.TMR0IF = 0;
    if(f == 0){
        PORTDbits.RD4 = 0;
        for(int i=0; i<=65*v; i++){
            TMR0_WriteTimer(63624);
            ready = 0;
            T0CONbits.TMR0ON = 1;
            //while(INTCONbits.TMR0IF == 0);
            while(ready == 0);
            T0CONbits.TMR0ON = 0;
            ready = 0;
            //INTCONbits.TMR0IF = 0;
        } 
    }else{
        for(int i=0; i<=f*v; i++){
            if(PORTDbits.RD4 == 0){
                PORTDbits.RD4 = 1;
            }else if(PORTDbits.RD4 == 1){
                PORTDbits.RD4 = 0;
            }
            TMR0_WriteTimer(init);
            ready = 0;
            T0CONbits.TMR0ON = 1;
            //while(INTCONbits.TMR0IF == 0);
            while(ready == 0);
            T0CONbits.TMR0ON = 0;
            ready = 0;
            //INTCONbits.TMR0IF = 0;
        } 
    }
}

void song(){ // DEMON SLAYER OP
    unsigned char notas[] = {/*'C','b','C',
                             'C','b','C',
                             'e','s','C','b','a','s','g','g',
                             'e','g','a',
                             'a','C','D',
                             'C','D','E',
                             'g','a','g','s','g','a','a','a','s','g','a','s','g','a','a','a',
                             'g','a','s','g','a','a','a','s','g','a','s','g','a','a','a',*/
                             'a','C','b',
                             'g','a','g',
                             'D','D','D',
                             'F','E','a',
                             'g','a','s','C','D','s','G','A','G','A','s','C','s','B','g','a','g',
                             'D','D','D','s','F','E','C','s','C','b','b','s','C','D',
                             'C','D','s','C','a','s','C','E','D','s','C','D','C','a','C','g',
                             'C','D','s','C','a','s','C','E','D','s','D','D','D','s','E','G','s','E','D','C',
                             'C','b','b','s','C','D',
                             'C','b','C','C','b','C','s','e','s','C','b','a','g','g',
                             'e','g','a','s','a','C','D','s','C','D','E',
                             'g','g','s','E','s','D','E','G','s','E','D','E','E',
                             'C','C','s','D','E','G','s','E','D','E','E',
                             'g','g','C','C','s','g','g','C','D','s','C','G','s','F','E','s','D','C','C',
                             'C','D','E','s','D','s','E','G','E',
                             'g','g','s','E','D','E','G','s','E','D','E','E',
                             'C','C','s','D','E','G','s','E','D','E','C',
                             'C','C','s','D','E','s','E','C','B','G','s','E','D','C','C',
                             'C','D','E','D','s','g','g','s','a',
                             'g','a','g','s','g','a','a','a','s','g','a','s','g','a','a','a',
                             'g','a','s','g','a','a','a','s','g','a','s','g','a','a','a',
                             'g','a','s','g','a','a','a','s','g','a','s','g','a','a','a'};
    for(int i=0; i<255; i++){
        parseNote(notas[i]); //tocar nota a la frecuencia determinada
    }
}

void interrupt INTERRUPT_InterruptManager (void)
{
    if(INTCONbits.INT0IE == 1 && INTCONbits.INT0IF == 1){
        v = 1;
        INTCONbits.INT0IF = 0;
    }else if(INTCON3bits.INT1IE == 1 && INTCON3bits.INT1IF == 1){
        v = 4;
        INTCON3bits.INT1IF = 0;
    }else if(INTCON3bits.INT2IE == 1 && INTCON3bits.INT2IF == 1){
        v = 8;
        INTCON3bits.INT2IF = 0;
    }else if(INTCONbits.TMR0IE == 1 && INTCONbits.TMR0IF == 1){
        //Nop();
        //__nop()
        //T0CONbits.TMR0ON = 0;
        INTCONbits.TMR0IF = 0;
        ready = 1;
        
    }
}

void main(void) {
       
    TRISBbits.TRISB0 = 1;
    TRISBbits.TRISB1 = 1;
    TRISBbits.TRISB2 = 1;
    
    TRISDbits.TRISD4 = 0;
    
    //INT0, INT1 and INT2 are sensitive to positive edges
    INTCON2bits.INTEDG0 = 1;
    INTCON2bits.INTEDG1 = 1;
    INTCON2bits.INTEDG2 = 1;
    
    //clear flags and enable interrupts
    INTCONbits.INT0F = 0;
    INTCONbits.INT0IE = 1;
    INTCON3bits.INT1IF= 0;
    INTCON3bits.INT1IE = 1;
    INTCON3bits.INT2IF = 0;
    INTCON3bits.INT2IE = 1;
    
    //PORTA, PORTB and PORTE are digital
    ADCON1bits.PCFG = 0xF; 
    
    // SCS INTOSC; IDLEN disabled; IRCF 4MHz; 
    OSCCON = 0x60;
    // INTSRC 31kHz derived from INTRC internal oscillator; TUN = 0
    OSCTUNE = 0x00;
    
    INTCONbits.GIE = 1;
    INTCONbits.PEIE = 1;
    INTCONbits.TMR0IF = 0;
    INTCONbits.TMR0IE = 1;
    T0CONbits.T0CS = 0;
    T0CONbits.T0SE = 0;
    T0CONbits.T08BIT = 0;
    T0CONbits.PSA = 1;
    
    v = 2;
    PORTDbits.RD4 = 0;
    while(1){
        song();
    }
}

//#include <p24FJ256GB110.h>
#include "ee308.h"
#include <xc.h>
//#include <libpic30.h>

void init_IO(void)
{
    LATCbits.LATC4 = 1; // TTP229 SCLK HIGH
    LATAbits.LATA9 = 0;
    LATAbits.LATA10 = 0;
    TRISCbits.TRISC4 = 0;
    TRISAbits.TRISA9 = 0;
    TRISAbits.TRISA10 = 0;
}

void init_timer(void)
{
	//_T1IP = 4;	// set Timer1 priority, (4 is the default value)
  	T1CONbits.TCKPS0 = 1;
	T1CONbits.TCKPS1 = 1;	// prescaler set to 256 
    T1CONbits.TCS = 0;
    
	TMR1	= 0x0000;
	PR1	= 3905;		// set timer1 period to 3906 -> f = 2e6/256/3096 = 2Hz
//	_T1IF = 0;      // clear timer1 IF
//	_T1IE = 1;      // enable timer1 interrupt
    IFS0bits.T1IF = 0;
    IEC0bits.T1IE = 1;
    
	T1CONbits.TON = 1;
}

void init_i2c(void)
{
    ANSBbits.ANSB2 = 0;
    ANSBbits.ANSB3 = 0;
    I2C2BRG = 0x27;     // set BAUD rate
    I2C2CONLbits.A10M = 0;
    I2C2CONLbits.I2CEN = 1;
}

void init_CNInt(void)
{
    CNEN2bits.CN22IE = 1;
    IFS1bits.CNIF = 0;
    IEC1bits.CNIE = 1;
}
#include "ee308.h"
#include "lcd.h"
#include "keypad.h"

//#include <stdint.h>
//#include <stddef.h>
#include <xc.h> //

#pragma config JTAGEN=OFF, FWDTEN = 0

const unsigned char LookUp[16] = "0123456789ABCDEF";
//volatile unsigned char LCD_data[2][16] = {"PIC24 Board v2.2", "Keyboard  -->   "};

unsigned char kbdflag = 0;

void __attribute__ ( ( __interrupt__ , auto_psv ) ) _T1Interrupt ( void )
{
    //LATAbits.LATA10 = ~LATAbits.LATA10;
    //LATA ^= 0x0200;     // bit 9 toggle
    IFS0bits.T1IF = 0 ;
}
void __attribute__ ( ( __interrupt__ , auto_psv ) ) _CNInterrupt ( void )
{
    if(PORTBbits.RB8==0)
    {
        kbdflag = 1;
        CNEN2bits.CN22IE = 0;
        
    }
    IFS1bits.CNIF = 0;
}


main() {
    unsigned char kbd;
    
    init_IO();
    init_timer();
    init_i2c();
    init_CNInt();
    init_lcd();
    
   
    
    RPOR10bits.RP20R=8 ;   //SPI1 clock output
    RPINR20bits.SDI1R=  8 ;//SPI1 data input

    SPI1CON1Lbits.SSEN=0;
    SPI1CON1Lbits.MSTEN=1;
    SPI1CON1Lbits.CKP=1;
    SPI1CON1Lbits.MODE32=0;
    SPI1CON1Lbits.MODE16=1;
    SPI1CON1Lbits.MCLKEN=0;
    SPI1CON1Lbits.SMP=0; 
    SPI1BRGLbits.BRG = 499;
    SPI1CON1Lbits.CKE = 0; //SPIx Clock Edge Select bit
    SPI1CON1Lbits.DISSDI = 0; //input controlled by the module
    SPI1CON1Lbits.DISSCK = 0; //output controlled by the module
    SPI1STATLbits.SPIROV=0;
    SPI1CON1Lbits.SPIEN=1;
     while(1)
    {
        if(kbdflag)
        {
            kbdflag = 0;
            kbd = read_keypad();
            if (kbd!=16)
            {
                send_LCD_CMD(0xCF);
                send_LCD_DATA(LookUp[kbd]);
            }
        }
    }
}

#include "ee308.h"
#include "lcd.h"
#include "keypad.h"

//#include <stdint.h>
//#include <stddef.h>
#include <xc.h>

#pragma config JTAGEN=OFF, FWDTEN = 0

const unsigned char LookUp[16] = "0123456789ABCDEF";
//volatile unsigned char LCD_data[2][16] = {"PIC24 Board v2.2", "Keyboard  -->   "};

unsigned char kbdflag = 0;

void __attribute__ ( ( __interrupt__ , auto_psv ) ) _T1Interrupt ( void )
{
    LATAbits.LATA10 = ~LATAbits.LATA10;
    //LATA ^= 0x0200;     // bit 9 toggle
    IFS0bits.T1IF = 0 ;
}
void __attribute__ ( ( __interrupt__ , auto_psv ) ) _CNInterrupt ( void )
{
    if(PORTBbits.RB8==1)
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

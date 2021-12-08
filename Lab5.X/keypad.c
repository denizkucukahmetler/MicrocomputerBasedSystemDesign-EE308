#include <xc.h>

unsigned char read_keypad(void)
{
        
    unsigned int i,j;
    unsigned int buff;
    unsigned char result;
    result=16;
    
    SPI1BUFL=0x0000;
    
    while(!SPI1STATLbits.SPIRBF);
    if(SPI1STATLbits.SPIRBF)
    {  
        
        buff = SPI1BUFL;
    }
    
    buff = buff ^ 0b1111111111111111 ;
    
    for (i = 0; i<16;i++)
        {
            if ((buff << i) ==0x8000)
            {
                result = i;
            }
        }
    
    
    IFS1bits.CNIF = 0;
    CNEN2bits.CN22IE = 1;   // re-enable CNint
    return(result);
}
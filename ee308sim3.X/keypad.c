#include <xc.h>

unsigned char read_keypad(void)
{
    int i;
    unsigned char j, result;
    
    result = 16;
    
    for (i = 0 ; i < 1000 ; i++);
    /*
    for (j=0; j<16; j++)
    {
        LATCbits.LATC4 = 0;
        for (i = 0 ; i < 100 ; i++);
        if (PORTBbits.RB8==0) result = j;
        LATCbits.LATC4 = 1;
    }
    */
    
    SPI1CON1Lbits.SMP = 0;
    for (i = 0 ; i < 100 ; i++); //wait to receive data
    
    SPI1CON1Lbits.MODE16 = 1;
    SPI1CON1Lbits.MODE32 = 0;
    result = 0;//SPI1BUFL;
    /*
    result = SPI1BUF;
    SPI1CON1bits.DISSCK		= 0;	// Internal SPIx clock is enabled
	SPI1CON1bits.MSTEN 		= 1; 	// 1 =  Master mode; 0 =  Slave mode
	SPI1CON1bits. 		= 4; 	// Secondary Prescaler = 4:1
	SPI1CON1bits.PPRE 		= 2; 	// Primary Prescaler = 4:1
          */  
    for (i = 0 ; i < 10000 ; i++);

    IFS1bits.CNIF = 0;
    CNEN2bits.CN22IE = 1;   // re-enable CNint
    return(result);
}
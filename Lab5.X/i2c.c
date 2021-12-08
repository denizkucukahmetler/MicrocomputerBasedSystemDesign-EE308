#include <xc.h>
#include "i2c.h"


void I2Cstart(void)
{
	I2C2CONLbits.SEN = 1;		// start condition
	while(I2C2CONLbits.SEN){}	// wait while start condition in progress
}

void I2Cstop(void)
{
	I2C2CONLbits.PEN = 1;		// stop condition
	while(I2C2CONLbits.PEN){}	// wait while stop condition in progress
}

void I2Crestart(void)
{
	I2C2CONLbits.RSEN = 1;		// restart condition
	while(I2C2CONLbits.RSEN){}	// wait while restart condition in progress
}

unsigned char I2Cwrite(unsigned int c)
{
	I2C2TRN = c;
	while(I2C2STATbits.TBF){}	// wait write
	while(I2C2STATbits.TRSTAT){}	// wait slave ack	
	return(I2C2STATbits.ACKSTAT ? 0 : 1);	// not acknowledge = 0, acknowledge = 1
}

unsigned char I2Cread(void)
{
	//unsigned int c;
	I2C2CONLbits.RCEN = 1;		// master receive enable
	while(I2C2CONLbits.RCEN){}	// wait read
	return(I2C2RCV);
	//c = I2C1RCV;
	//return(c);
}

void I2Cack(void)
{
	I2C2CONLbits.ACKDT = 0;		// ACK bit 0
	I2C2CONLbits.ACKEN = 1;		// send ACK
	while(I2C2CONLbits.ACKEN){}	// wait_ack
}

void I2Cnack(void)
{
	I2C2CONLbits.ACKDT = 1;		// ACK bit 1
	I2C2CONLbits.ACKEN = 1;		// send ACK
	while(I2C2CONLbits.ACKEN){}	// wait_ack
}


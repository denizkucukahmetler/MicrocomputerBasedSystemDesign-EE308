void initI2C(void);
void I2Cstart();
void I2Cstop(void);
void I2Crestart(void);
unsigned char I2Cwrite(unsigned int c);
unsigned char I2Cread(void);
void I2Cack(void);
void I2Cnack(void);

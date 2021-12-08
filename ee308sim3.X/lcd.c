#include "i2c.h"
#include "lcd.h"

void init_lcd(void)
{
    unsigned int i;
    volatile unsigned char LCD_data[2][16] = {"PIC24 Board v2.3", "Keyboard  -->   "};
    
    send_1_LCD(0x08);
    for (i = 0 ; i < 16000 ; i++);
    send_1_LCD(0x3C);
    for (i = 0 ; i < 16000 ; i++);
    send_1_LCD(0x3C);
    for (i = 0 ; i < 16000 ; i++);
    send_1_LCD(0x3C);
    for (i = 0 ; i < 16000 ; i++);
    send_1_LCD(0x3C);
    for (i = 0 ; i < 16000 ; i++);
    send_1_LCD(0x2C);
    for (i = 0 ; i < 16000 ; i++);
    
    send_LCD_CMD(0x28);
    for (i = 0 ; i < 16000 ; i++);
    send_LCD_CMD(0x0E);
    for (i = 0 ; i < 16000 ; i++);
    send_LCD_CMD(0x01);
    for (i = 0 ; i < 16000 ; i++);
    
    for (i = 0 ; i < 16 ; i++)
        send_LCD_DATA(LCD_data[0][i]);
    send_LCD_CMD(0xC0);
    for (i = 0 ; i < 16 ; i++)
        send_LCD_DATA(LCD_data[1][i]);
    
    //send_LCD_CMD(0x80);
    //send_LCD_DATA('A');
}

void send_LCD_CMD(unsigned char c)
{
    send_2_LCD(c, 0x0C);
}

void send_LCD_DATA(unsigned char c)
{
    send_2_LCD(c, 0x0D);
}

void send_1_LCD(unsigned char c)
{
    I2Cstart();
    I2Cwrite(0x4E);
    I2Cwrite(c);
    c&=0xFB;    // clear bit #2
    I2Cwrite(c);
    I2Cstop();
}

void send_2_LCD(unsigned char c, unsigned char cd)
{
    unsigned char tmp;
    
    I2Cstart();
    I2Cwrite(0x4E);
    tmp = c;
    tmp &= 0xF0;
    tmp |= cd;
    I2Cwrite(tmp);
    tmp &= 0xFB;
    I2Cwrite(tmp);
    tmp = c<<4;
    tmp |= cd;
    I2Cwrite(tmp);
    tmp &= 0xFB;
    I2Cwrite(tmp);
    I2Cstop();
}

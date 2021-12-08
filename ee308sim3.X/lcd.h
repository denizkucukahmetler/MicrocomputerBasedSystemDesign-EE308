#define FOSC    (8000000ULL)
#define FCY     (FOSC/2)

void init_lcd(void);
void send_LCD_CMD(unsigned char);
void send_LCD_DATA(unsigned char);
void send_1_LCD(unsigned char);
void send_2_LCD(unsigned char, unsigned char);

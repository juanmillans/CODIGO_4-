#include <xc.h>
#define _XTAL_FREQ 8000000UL  // This constant needs to be defined so we can use the delay function with corrrect delays.

#define USE_CGRAM_LCD

#define RS LATAbits.LA4
#define EN LATAbits.LA5

#define D4 LATDbits.LD4
#define D5 LATDbits.LD5
#define D6 LATDbits.LD6
#define D7 LATDbits.LD7

#define RS_DIR TRISAbits.TRISA4
#define EN_DIR TRISAbits.TRISA5


#define D4_DIR TRISDbits.TRISD4
#define D5_DIR TRISDbits.TRISD5
#define D6_DIR TRISDbits.TRISD6
#define D7_DIR TRISDbits.TRISD7

void Lcd_Port(char a);
void Lcd_Cmd(char a);
void Lcd_Clear(void);
void Lcd_Set_Cursor(char a, char b);
void Lcd_Init(void);
void Lcd_Write_Char(char a);
void Lcd_Write_String(const char *a);
void Lcd_Shift_Right(void);
void Lcd_Shift_Left(void);
void Lcd_Blink(void);
void Lcd_NoBlink(void);

#ifdef USE_CGRAM_LCD
void Lcd_CGRAM_CreateChar(char add, const char* chardata);
void Lcd_CGRAM_Init(void);
void Lcd_CGRAM_Close(void);
#endif
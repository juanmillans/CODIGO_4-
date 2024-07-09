// External oscillator with postcaling of 0.5 .
// primera seccion (Librerias)
#include <xc.h>
#include <stdio.h>
#include <stdlib.h>

#include "lcd.h"
#include "Welcome.h"
#include "blinky.h"
#include "RGB_BCD.h"

#include <string.h>// para manejar las strings 
#define _XTAL_FREQ 8000000UL  // This constant needs to be defined so we can use the delay function with corrrect delays.


const char figura_1[8] = {0x3, 0xe, 0xc, 0x18, 0xc, 0xe, 0x3, 0x00}; //boca muy abierta derecha
const char figura_2[8] = {0x0, 0x7, 0xc, 0x18, 0xc, 0x7, 0x0, 0x00};//boca semiabierta derecha
const char figura_3[8] = {0x0, 0x6, 0xf, 0x1c, 0xf, 0x6, 0x0, 0x00};//boca semicerrada derecha 
const char figura_4[8] = {0x0, 0x4, 0xe, 0x1f, 0xe, 0x4, 0x0, 0x00};// boca cerrada (derecha/izquierda)
const char figura_5[8] = {0x18, 0xe, 0x6, 0x1, 0x6, 0xe, 0x18, 0x00};//boca muy abierta izquierda
const char figura_6[8] = {0x0, 0xc, 0x1e, 0x7, 0x1e, 0xc, 0x0, 0x00};//boca semiabierta izquierda
const char figura_7[8] = {0x0, 0x1c, 0x6, 0x3, 0x6, 0x1c, 0x0,0x00};//boca semicerrada izquierda 
const char figura_8[8] = {0x4, 0xe, 0x1f, 0x15, 0x1f, 0x1f, 0x15,0x00};// Fantasma 
const char figura_9[8] = {0x0, 0x0, 0x0, 0x1e, 0x18, 0x10, 0x0,0x00};// El trabuco
void Welcome()
{
    //OSCCONbits.IRCF=0b111;// Escogemos el reloj de 8 Mhz
    //OSCCONbits.SCS=0b10; // escogemos el oscilador interno 
    
    Lcd_Init();                         // Inicializa la pantalla LCD
    
    Lcd_CGRAM_Init();                   // Accede a la CRGAM
    Lcd_CGRAM_CreateChar(0, figura_1);  // Almacena el caracter 1 en la posicion 0 de la  CGRAM
    Lcd_CGRAM_CreateChar(1, figura_2);  // Almacena el caracter 2 en la posicion 1 de la  CGRAM
    Lcd_CGRAM_CreateChar(2, figura_3);  // Almacena el caracter 3 en la posicion 2 de la  CGRAM
    Lcd_CGRAM_CreateChar(3, figura_4);  // Almacena el caracter 4 en la posicion 3 de la  CGRAM
    Lcd_CGRAM_CreateChar(4, figura_5);  // Almacena el caracter 5 en la posicion 4 de la  CGRAM
    Lcd_CGRAM_CreateChar(5, figura_6);  // Almacena el caracter 6 en la posicion 5 de la  CGRAM
    Lcd_CGRAM_CreateChar(6, figura_7);  // Almacena el caracter 7 en la posicion 6 de la  CGRAM
    Lcd_CGRAM_CreateChar(7, figura_8);  // Almacena el caracter 8 en la posicion 7 de la  CGRAM
    
    Lcd_CGRAM_Close();                  // Sale de la CGRAM
    Lcd_Clear();                        // Limpia la pantalla
    
   
    Lcd_Set_Cursor(1,1); // fila 1 colimna 1 
    Lcd_Write_String("   Bienvenidos  ");
    __delay_ms(3000);

    for(char i=0; i<16; i++)
      {
        Lcd_Shift_Left();
        __delay_ms(300);
      }

    for(char i=0; i<16; i++)
      {
        Lcd_Shift_Right();
        __delay_ms(300);
      }

    Lcd_Clear();
    Lcd_Set_Cursor(1,1); // fila 1 colimna 1 
    Lcd_Write_String("    Contador    ");
    Lcd_Set_Cursor(2,1);// fila 2 colimna 1
    Lcd_Write_String("    De Piezas   ");
    __delay_ms(3000);


    for(char i=1; i<17; i++)
      {
        Lcd_Set_Cursor(2,i);
         Lcd_Write_Char(0);
         __delay_ms(100);

         Lcd_Set_Cursor(2,i); 
         Lcd_Write_Char(1);
         __delay_ms(100);


         Lcd_Set_Cursor(2,i); 
         Lcd_Write_String(" ");


         Lcd_Set_Cursor(2,i); 
         Lcd_Write_Char(2);
         __delay_ms(100);

         Lcd_Set_Cursor(2,i); 
         Lcd_Write_Char(3);
         __delay_ms(100); 


         Lcd_Set_Cursor(2,i); 
         Lcd_Write_String(" ");
      }
    for(char i=16; i>4; i--)
      {
        Lcd_Set_Cursor(1,i);
         Lcd_Write_Char(4);
         __delay_ms(100);

         Lcd_Set_Cursor(1,i); 
         Lcd_Write_Char(5);
         __delay_ms(100);

         Lcd_Set_Cursor(1,i); 
         Lcd_Write_Char(6);
         __delay_ms(100);

         Lcd_Set_Cursor(1,i); 
         Lcd_Write_Char(3);
         __delay_ms(100); 

         Lcd_Set_Cursor(1,i); 
         Lcd_Write_String(" ");
      }     

    //Lcd_CGRAM_CreateChar(6, figura_9);  // Almacena el caracter 9 en la posicion 6 de la  CGRAM // el trabuco 
    for(char i=3; i<20; i++)
      {
        Lcd_Set_Cursor(1,i);
         Lcd_Write_Char(0);             
        Lcd_Set_Cursor(1,i-2);
         Lcd_Write_Char(7);
         __delay_ms(100);

         Lcd_Set_Cursor(1,i); 
         Lcd_Write_Char(1);
         Lcd_Set_Cursor(1,i-2);
         Lcd_Write_Char(7);
         __delay_ms(100);


         Lcd_Set_Cursor(1,i); 
         Lcd_Write_String(" ");
         Lcd_Set_Cursor(1,i-2); 
         Lcd_Write_String(" ");


         Lcd_Set_Cursor(1,i); 
         Lcd_Write_Char(2);
         __delay_ms(100);
         Lcd_Set_Cursor(1,i-2);
         Lcd_Write_Char(7);

         Lcd_Set_Cursor(1,i); 
         Lcd_Write_Char(3);
         Lcd_Set_Cursor(1,i-2);
         Lcd_Write_Char(7);

         __delay_ms(100); 


         Lcd_Set_Cursor(1,i); 
         Lcd_Write_String(" ");
         Lcd_Set_Cursor(1,i-2); 
         Lcd_Write_String(" ");           
      }        


    Lcd_Clear();
    

}

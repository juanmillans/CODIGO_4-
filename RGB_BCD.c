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

char Negro =0b111;
//hgfghhfhgfhgfh
char magenta = 0b010;
char azul = 0b011;
char cyan = 0b001;
char verde = 0b101;
char amarillo = 0b100;
char blanco = 0b000;
char rojo = 0b110;



void RGB_BCD(int count_En,int *contador, int *contador_dec, int*re_pcs ) 
{            
   // OSCCONbits.IRCF=0b111;// Escogemos el reloj de 8 Mhz
   // OSCCONbits.SCS=0b10; // escogemos el oscilador interno 
    LATD = (*contador);

    if(PORTCbits.RC1 == 1 && count_En==1 )              // Incrementa el contador
        {
            while(PORTCbits.RC1 == 1)
              {
                __delay_ms(10);
              }
            (*contador)++;
            (*re_pcs)--;
           
            if((*contador) > 9)
              {
                (*contador) = 0;
                (*contador_dec)++;
                switch(*contador_dec)
                {
                  case 0:
                    LATE=Negro;
                  break;

                  case 1:
                    LATE=magenta;
                  break;

                  case 2:
                    LATE=azul;
                  break;

                  case 3:
                    LATE=cyan;
                  break;

                  case 4:
                    LATE=verde;
                  break;    

                  case 5:
                    LATE=amarillo;
                  break;    

                  case 6:
                    LATE=blanco;
                  break;    

                  default:
                    LATE=Negro;
                    break;
                 }
                }
      
      
         }
    
}


                
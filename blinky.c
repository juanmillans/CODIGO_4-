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

void blinky (void)
{
  INTCONbits.GIE=1; // activamos las interruptiones en general. 
  INTCONbits.PEIE=1;// Activando las interrupciones de perifericos. 
  RCONbits.IPEN=1; // activando los niveles de prioridad de las interrupciones. 
  //interrupcion Timer0 
  T0CONbits.TMR0ON=0;// Contador detenido
  INTCONbits.TMR0IE=1;// Actvando la interrupcion timer 0
  INTCON2bits.TMR0IP=1; //prioridad alta
  T0CONbits.T08BIT=0;//16 bit counter
  T0CONbits.T0CS=0;// se configura como temporizador en lugar de contador
  T0CONbits.PSA=0;// Seleccionamos el reloj que venga del prescalador
  T0CONbits.T0PS=0b100;// Asignamos que el el prescalador divida al reloj en 1/32
  INTCONbits.TMR0IF=0;//Bajando la bandera en un inicio. 
  
  T0CONbits.TMR0ON=1;// Contador iniciado 
  return;
}
void __interrupt(high_priority)HIGH_PRIORITY_i()
  {    
    if(INTCONbits.TMR0IF==1)
    {
      LATAbits.LATA1=~LATAbits.LATA1;
      // 34285 = 0b10000101 0b11101101
      TMR0H=0b10000101;
      TMR0L=0b11101101;
      INTCONbits.TMR0IF=0;// taking down the int1 flag. 
    }
  }

// External oscillator with postcaling of 0.5 .
// primera seccion (Librerias)
#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include "kbd4x4.h"
// segunda seccion (configuracion)
#pragma FOSC=HS // 
#define _XTAL_FREQ 4000000UL  // This constant needs to be defined so we can use the delay function with corrrect delays.


void main()
{
  Keypad_Init();
  
  Keypad_Get_Char();
}

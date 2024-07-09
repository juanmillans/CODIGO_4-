/* #include "kbd4x4.h"
*
* Creada por: Ing. Abiezer Hernandez O.
* Fecha de creacion: 02/12/2019
* Electronica y Circuitos
*
*/

#include <xc.h>
#define _XTAL_FREQ 4000000UL

#define COL0_PIN PORTBbits.RB7
#define COL1_PIN PORTBbits.RB6
#define COL2_PIN PORTBbits.RB5
#define COL3_PIN PORTBbits.RB4

#define ROW0_PIN PORTBbits.RB3
#define ROW1_PIN PORTBbits.RB2
#define ROW2_PIN PORTBbits.RB1
#define ROW3_PIN PORTBbits.RB0



#define COL0_DIR TRISBbits.TRISB7
#define COL1_DIR TRISBbits.TRISB6
#define COL2_DIR TRISBbits.TRISB5
#define COL3_DIR TRISBbits.TRISB4

#define ROW0_DIR TRISBbits.TRISB3
#define ROW1_DIR TRISBbits.TRISB2
#define ROW2_DIR TRISBbits.TRISB1
#define ROW3_DIR TRISBbits.TRISB0



void Keypad_Init(void);
char Keypad_Get_Char(void);
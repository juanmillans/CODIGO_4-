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

#pragma config LVP = OFF 
#pragma config WDT = OFF
#define _XTAL_FREQ 8000000UL  // This constant needs to be defined so we can use the delay function with corrrect delays.


int contador=0; 
int contador_dec=0;
// codigo 
int state=0;
char Tecla;
int num;

int Enter_en=0;
int Numpad_en=0; // los numeros del keypad estan desabilitados hasta no ser requeridos
int Keypad_en=0;// las funciones como reset, parada de emergencia, finalizacion, se encuentran deshabilitados.
int Borrado=0;
int Borrado_En=0;

int back_l_En=0;
int reset_En=0;
int E_stop_En=0;



int count_En=0;

int result=0;
int digito=0;
int times=0;
int times_1=0;

char num_str[10]; 
char re_pcs_str[20];
char counted_pcs_str[20];
int check =0;
int ok_flag=0;

int re_pcs;
int ok_en=0;




void main()
{   
   
   
   Lcd_Init();                         // Inicializa la pantalla LCD
   TRISB=0b11110000;                   // 
   LATB=0b11110000;
   TRISD=0b00000000;                   // Configurar todo el uerto D como salida.
   TRISE=0b000;                        // configura todo el puerto E como salida. 
   TRISCbits.RC1=1;                    // Configura el pin 16 como entrada. 
   TRISA=0b000000000;                  // Configura todo el puerto A como salida. 
   ADCON1bits.PCFG = 0x0F;             // Coloca los pines AN1 hasta AN12 como digitales. 
  
   INTCONbits.GIE=1; 
   INTCONbits.PEIE=1;
   RCONbits.IPEN=1;
   
   OSCCONbits.IRCF=0b111;// Escogemos el reloj de 8 Mhz
   OSCCONbits.SCS=0b10; // escogemos el oscilador interno 
   
   INTCONbits.RBIE=1;                            
   INTCON2bits.RBIP=0;
   INTCONbits.RBIF=0;
   
   
   
   //INTCON2bits.nRBPU=0;
    LATE=0b111;
    LATDbits.LATD0=0;
    LATDbits.LATD1=0;
    LATDbits.LATD2=0;
    LATDbits.LATD3=0;
    while(1)
    
    {
      blinky ();
      switch (state)
              
        {
          case 0: // inicio de programa
              LATAbits.LA3=1;
              Welcome();
              state++;
              Numpad_en=0;
              break;
          case 1: // pregunta cuantas piezas hay a contar. 
            
            if (times<1)
              {
                Lcd_Set_Cursor(1,1); // fila 1 colimna 1 
                Lcd_Write_String("cuantas piezas");
                Lcd_Set_Cursor(2,1);// fila 2 colimna 1
                Lcd_Write_String("desea contar?  ");
                __delay_ms(2000);
                Lcd_Clear();
                Lcd_Set_Cursor(1,1);
                __delay_ms(100);
                Lcd_Set_Cursor(1,1); // fila 1 colimna 1 
                Lcd_Write_String("ingrese numero");
                Lcd_Set_Cursor(2,1);// fila 2 colimna 1
                Lcd_Write_String("de 0 a 59  ");
                Lcd_Blink();
                Numpad_en=1;
                Borrado_En=1;
               
                
                times++;
              }
            
            if (Numpad_en && Enter_en &&(digito<2))
            {
              switch(digito)
                {
                  case 0:
                    if(Borrado==0)
                    {
                  Lcd_Set_Cursor(2,12);
                  Lcd_Write_String(num_str);
                  result=10*num;
                  digito++;
                  
                    }

                  break;


                  case 1:
                  Lcd_Set_Cursor(2,13);
                  Lcd_Write_String(num_str);
                  Lcd_NoBlink();
                  result=result+num;
                  Numpad_en=0;
                  ok_en=1;
                  digito++;
                  
                  break;                
              }
              
                Enter_en=0;
                
              }
              break;
              
              
          case 2: //Contar piezas 
            Borrado_En=0;
            ok_en=0;
            
            if (times_1<1)
              {
                Lcd_Clear();
                char countdown[20];
                for (int i = 3; i >= 0; i--) 
                  {
                    sprintf(countdown,"empezamos en %d", i);
                    Lcd_Clear();
                    Lcd_Set_Cursor(1,1); // fila 1 colimna 1 
                    Lcd_Write_String(countdown); 
                    __delay_ms(1000);
                  }
                Lcd_Clear();
                times_1++;
              }

             
              
              RGB_BCD(count_En,&contador, &contador_dec,&re_pcs ) ;
              if (re_pcs !=check)
              {

                
                Lcd_Clear();
                sprintf(counted_pcs_str,"contadas %d", 10*contador_dec+contador);
                sprintf(re_pcs_str,"faltantes %d",re_pcs);    
                Lcd_Set_Cursor(1,1);  
                Lcd_Write_String(counted_pcs_str);
                Lcd_Set_Cursor(2,1);  
                Lcd_Write_String(re_pcs_str);
                if (re_pcs==0)
                {
                  Lcd_Clear();
                  times_1=0;
                  state++;
                }

                 check=re_pcs;
              }
                

            break;
          case 3:
              
              if (times_1<1)
              {
                Lcd_Set_Cursor(1,1);  
                Lcd_Write_String("conteo");
                Lcd_Set_Cursor(2,1);  
                Lcd_Write_String("terminado");
                __delay_ms(2000);
                Lcd_Clear();
                __delay_ms(100);
                Lcd_Set_Cursor(1,1);  
                Lcd_Write_String("pulsa ok para");
                Lcd_Set_Cursor(2,1);  
                Lcd_Write_String("Volver al menu");  
                ok_en=1;
                times_1++;
              }
  
            
            break;
            
          default:
            break;
        } 
    } 
}


//  ONLY LOW PRIORITY INTERRUPTIONS 


void __interrupt(low_priority)LOW_PRIORITY()
  {

 
  if(INTCONbits.RBIF==1)
    {
      if(PORTB != 0b11110000)
        {
        if(Borrado==1)
        {
          Numpad_en=1;
          Borrado=0;
        }
        ok_flag=0;
        Enter_en=0;
        Tecla=0;
        LATB=0b11111110;
        if(PORTBbits.RB4==0) Tecla=1;
        else if(PORTBbits.RB5==0) Tecla=2;
        else if(PORTBbits.RB6==0) Tecla=3;
        else if(PORTBbits.RB7==0) Tecla=4;
        else
          {
          LATB=0b11111101;
          if(PORTBbits.RB4==0) Tecla=5;
          else if(PORTBbits.RB5==0)Tecla=6;
          else if(PORTBbits.RB6==0)Tecla=7;
          else if(PORTBbits.RB7==0)Tecla=8;
          else
            {
            LATB=0b11111011;  
            if(PORTBbits.RB4==0) Tecla=9;
            else if (PORTBbits.RB5==0) Tecla=10;
            else if (PORTBbits.RB6==0) Tecla=11;
            else if (PORTBbits.RB7==0) Tecla=12;
            else
              {
                LATB=0b11110111;
                if(PORTBbits.RB4==0) Tecla=13;
                else if (PORTBbits.RB5==0) Tecla=14;
                else if (PORTBbits.RB6==0) Tecla=15;
                else if (PORTBbits.RB7==0) Tecla=16;           
              }
            }
          }
        
        if (E_stop_En==0)
        {
          switch (Tecla) 
          {
            case 1:

                  if (Numpad_en==1)
                    {
                    num=1;
                    Borrado=0;
                    back_l_En=0;
                    reset_En=0;
                    E_stop_En=0;
                    }
                  break;
              case 2:
                  if (Numpad_en==1)
                    {
                     num=2;
                     Borrado=0;
                     reset_En=0;
                     E_stop_En=0;
                    }


                  break;
              case 3:
                  if (Numpad_en==1)
                    {
                      num=3;
                      Borrado=0;
                      back_l_En=0;
                      reset_En=0;
                      E_stop_En=0;
                    }              

                  break;
             case 5:
                  if (Numpad_en==1)
                    {
                      num=4;
                      Borrado=0;
                      back_l_En=0;
                      reset_En=0;
                      E_stop_En=0;
                    }              

                  break;
              case 6:
                   if (Numpad_en==1)
                    {
                      num=5;
                      Borrado=0;
                      back_l_En=0;
                      reset_En=0;
                      E_stop_En=0;
                    }             

                  break;
              case 7:
                   if (Numpad_en==1)
                    {
                      num=6;
                      Borrado=0;
                      back_l_En=0;
                      reset_En=0;
                      E_stop_En=0;
                    }             
                  break;
              case 9:
                  if (Numpad_en==1)
                    {
                      num=7;
                      Borrado=0;
                      back_l_En=0;
                      reset_En=0;
                      E_stop_En=0;
                    }              

                  break; 
              case 10:
                  if (Numpad_en==1)
                    {
                      num=8;
                      Borrado=0;
                      back_l_En=0;
                      reset_En=0;
                      E_stop_En=0;
                    }              

                  break;
              case 11:
                  if (Numpad_en==1)
                    {
                      num=9;
                      Borrado=0;
                      back_l_En=0;
                      reset_En=0;
                      E_stop_En=0;
                      
                    }              

                  break;
              case 14:
                  if (Numpad_en==1)
                    {
                      num=0;
                      Borrado=0;
                      back_l_En=0;
                      reset_En=0;
                      E_stop_En=0;
                    }              

                  break;

              case 8:// tecla de borrado
                if(Borrado_En==1)
                {
                  Lcd_Set_Cursor(2,12);
                  Lcd_Write_String(" ");
                  Lcd_Set_Cursor(2,13);
                  Lcd_Write_String(" ");
                  Lcd_Set_Cursor(2,12);
                  Lcd_Blink();
                  result=0;
                  digito=0;
                  Borrado=1;        
                  back_l_En=0;
                  reset_En=0;
                  E_stop_En=0;
                }
                  break;
                  
              case 4://boton de ok 
                
                if(ok_en==1)
                  {
                  if(state==1)
                  {
                    if (result>0 && result<=59 )
                      {
                        re_pcs=result; // la variable piezas faltantes es igual que result. 
                        Numpad_en=0;
                        //times_1=0;
                        count_En=1;
                        ok_en=0;
                        state++;
                      }
                    else 
                      {
                        Lcd_Clear();
                        Lcd_Set_Cursor(1,1);  
                        Lcd_Write_String("numero");
                        Lcd_Set_Cursor(2,1);  
                        Lcd_Write_String("invalido");
                        __delay_ms(2000);
                
                        Enter_en=0;
                        Numpad_en=0; // los numeros del keypad estan desabilitados hasta no ser requeridos
                        Keypad_en=0;// las funciones como reset, parada de emergencia, finalizacion, se encuentran deshabilitados.
                        Borrado=0;
                        Borrado_En=0;
                        count_En=0;
                        result=0;
                        digito=0;
                        times=0;
                        times_1=0;
                        check =0;
                        ok_en=0;
                        state=1;

                      }                  
                  }
                  else if(state==3)
                  {
                    
                    ok_en=0;
                    Enter_en=0;
                    Numpad_en=0; // los numeros del keypad estan desabilitados hasta no ser requeridos
                    Keypad_en=0;// las funciones como reset, parada de emergencia, finalizacion, se encuentran deshabilitados.
                    Borrado=0;
                    Borrado_En=0;
                    count_En=0;
                    result=0;
                    digito=0;
                    times=0;
                    times_1=0;
                    check =0;
                    state=1;
                    contador=0; 
                    contador_dec=0;
                    LATE=0b111;
                    LATDbits.LATD0=0;
                    LATDbits.LATD1=0;
                    LATDbits.LATD2=0;
                    LATDbits.LATD3=0;                    
                  }
                  back_l_En=0;
                  reset_En=0;
                  E_stop_En=0;
                  
                  }
                  ok_flag=1;
                  break;

              case 12:// boton de reset 
                    contador=0; 
                    contador_dec=0;
                    LATE=0b111;
                    LATDbits.LATD0=0;
                    LATDbits.LATD1=0;
                    LATDbits.LATD2=0;
                    LATDbits.LATD3=0; 
                    re_pcs=result;
                    reset_En=1;
                    E_stop_En=0;
                  break;
              case 13: // parada de emergencia
                if(state==2)
                {
                  
                  Lcd_Clear();   
                  Lcd_Set_Cursor(1,1);  
                  Lcd_Write_String("Parada De");
                  Lcd_Set_Cursor(2,1);  
                  Lcd_Write_String("Emrgencia");
                  
                  E_stop_En=1;
                }
                
                  

                  break;

              case 15: // finalizar conteo. volver a menu.
                    Enter_en=0;
                    Numpad_en=0; // los numeros del keypad estan desabilitados hasta no ser requeridos
                    Keypad_en=0;// las funciones como reset, parada de emergencia, finalizacion, se encuentran deshabilitados.
                    Borrado=0;
                    Borrado_En=0;
                    count_En=0;
                    result=0;
                    digito=0;
                    times=0;
                    times_1=0;
                    check =0;
                    state=1;
                    contador=0; 
                    contador_dec=0;
                    LATE=0b111;
                    LATDbits.LATD0=0;
                    LATDbits.LATD1=0;
                    LATDbits.LATD2=0;
                    LATDbits.LATD3=0;  
                
                  break;
              case 16:// encender pantalla LCD 
                  back_l_En=1;
                  LATAbits.LA3=~LATAbits.LA3;
                                    
                  break;
              default:
                return;
           }   

        }
        
          if(Numpad_en==1 && Borrado==0 && back_l_En==0 && reset_En==0 && ok_flag==0)
          {
            sprintf(num_str, "%d", num);
            Enter_en=1;
          }

        LATB=0b11110000;
        __delay_ms(100);
        
        
        
        
        }
        
      
  if (E_stop_En==1)
  {
     INTCONbits.RBIF=1;

     Numpad_en=0; // los numeros del keypad estan desabilitados hasta no ser requeridos
     Borrado=0;
     back_l_En=0;
     reset_En=0;
     LATE=0b110;//rojo de emergencia.
     LATAbits.LA3=1;
     count_En=0;
  }
  else
  {
  INTCONbits.RBIF=0;
  
  }
      

      
    }

  }



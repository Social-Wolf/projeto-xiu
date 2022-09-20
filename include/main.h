#include <stdio.h>            //Bilioteca do C
#include <stdbool.h>          //Biblioteca que permite utilizar variavel booleana
#include <stdint.h>  
#include <util/delay.h>

#include <avr/io.h>
#include <avr/interrupt.h>

#include "ad_conversion.h"
#include "hardware_config.h"
#include "uart.h"
#include "contador.h"
#include "sinalizacao_visual.h"
#include "menu_control.h"

#define set_bit(y,bit)      (y|=(1<<bit)) //coloca em 1 o bit x da variável Y 
#define clr_bit(y,bit)      (y&=~(1<<bit)) //coloca em 0 o bit x da variável Y 
#define cpl_bit(y,bit)      (y^=(1<<bit)) //troca o estado lógico do bit x da variável Y 
#define tst_bit(y,bit)      (y&(1<<bit)) //retorna 0 ou 1 conforme leitura do bit

uint8_t ch;
uint8_t buffer[];
uint8_t  menu_flag = 0, confirm_flag = 0;

ISR(TIMER0_OVF_vect) 
{
    TCNT0 = 252; // recarrega o Timer 0 para contagem de 250us
    f_timers();
}

ISR(PCINT0_vect)
{
    if(!tst_bit(PINB, B_MENU))
    {
        menu_flag++;
        _delay_ms(10);
    }
    else if(!tst_bit(PINB, B_CONFIRM))
    {
        //guard_function();
        _delay_ms(70);
    }
    if(menu_flag == 4)
    {
        menu_flag = 0;
    }
}

ISR(USART_RX_vect) 
{
    ch = UDR0;    // Faz a leitura do buffer da serial 
    UDR0 = ch;    // envia pela serial o valor lido  
}

ISR(ADC_vect)
{
    read_ad_chanel();
}

void setup();
void setup_software();
void setup_hardware();
void f_timers();
void f_timer0();
void f_timer1();
void f_timer2();
void f_timer3();
void f_timer4();
void f_timer5();
void loop();
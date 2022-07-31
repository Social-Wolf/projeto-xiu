#include <stdio.h>            //Bilioteca do C
#include <stdbool.h>          //Biblioteca que permite utilizar variavel booleana
#include <stdint.h>  
#include <util/delay.h>

#include <avr/io.h>
#include <avr/interrupt.h>

#include "hardware_config.h"
#include "contador.h"

#define set_bit(y,bit)      (y|=(1<<bit)) //coloca em 1 o bit x da variável Y 
#define clear_bit(y,bit)    (y&=~(1<<bit)) //coloca em 0 o bit x da variável Y 
#define cpl_bit(y,bit)      (y^=(1<<bit)) //troca o estado lógico do bit x da variável Y 
#define tst_bit(y,bit)      (y&(1<<bit)) //retorna 0 ou 1 conforme leitura do bit

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
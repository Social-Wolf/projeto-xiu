#include <stdio.h>            //Bilioteca do C
#include <stdbool.h>          //Biblioteca que permite utilizar variavel booleana
#include <stdint.h>  
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

void io_config();
void timer_config();
void interrupt_config();
void adc_config();


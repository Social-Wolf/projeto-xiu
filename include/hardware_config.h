#include <stdio.h>            //Bilioteca do C
#include <stdbool.h>          //Biblioteca que permite utilizar variavel booleana
#include <stdint.h>  
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define LED_ON_OFF    PB0
#define BUZZER        PB1
#define BOTAO_0       PB2
#define BOTAO_1       PB3 
#define BOTAO_2       PB4 
#define BOTAO_3       PB5 
#define DISP_1        PB6 
#define DISP_2        PB7 

#define DECOD_0       PC0 
#define DECOD_1       PC1 
#define DECOD_2       PC2 
#define DECOD_3       PC3 
#define SENSOR        PC4 
#define CALIBRADOR    PC5

#define RX            PD0 
#define TX            PD1 
#define DMX_0         PD2 
#define DMX_1         PD3 
#define DMX_2         PD4 
#define LED_8         PD5 
#define LED_VISUAL    PD6 
#define LED_SOM       PD7 

void io_config();
void timer_config();
void uart_config(uint16_t size);
void interrupt_config();
void adc_config();


#include <avr/io.h>

#define SWITCH_OFF    PB0
#define BUZZER        PB1
#define DISP_2        PB2
#define DISP_1        PB3 
#define B_MENU        PB4 
#define B_CONFIRM     PB5 

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
#define LED_ALARM     PD7 

void io_config();
void timer_config();
void uart_config(uint16_t size);
void extern_interrupt_config();
void adc_config();


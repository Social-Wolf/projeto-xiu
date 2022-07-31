#include "hardware_config.h"

void io_config()
{
    // 0 = entrada 1 = saida 
    DDRB  = 0b11000011; //cont_disp como saída 
    DDRC  = 0b00001111; 
    DDRD  = 0b11011110;

    // entrada: 0 = sem pull-up 1 = com pull-up 
    // saida:   0 = low         1 = high
    PORTB = 0b00111100;
    PORTC = 0b00110000; //inicio as saídas apagadas
    PORTD = 0b00000000; //inicio o led apagado
}

void timer_config()
{
  /*tempo =65536 * Prescaler/Fosc = 65536 * 1024/16000000 = 4, 19s
    tempo = X_bit_timer * Prescaler/Fosc
    Valor inicial de contagem = 256 - tempo_desejado*Fosc/Prescaler = 256 - 0,001*16000000/1024 = 240
    Valor inicial de contagem = X_bit_timer - tempo_desejado*Fosc/Prescaler */

    TCCR0B = 0b00000101;    //prescaler de 1024
    TCNT0 =  240;           //contagem para gerar 1ms
    TIMSK0 = 0b00000001;    //habilito interrupcao do timer0

}

void interrupt_config()
{

}

void adc_config()
{
  
}

  
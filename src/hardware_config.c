#include "hardware_config.h"
//#include "adc_conversion.h"

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

void uart_config(uint16_t size)
{
  UBRR0H = (uint8_t)(size>>8);  //2 bits mais significativos de ubrr
  UBRR0L = (uint8_t)size;       //8 bits menos significativos de ubrr
  
  //Habilita a interrupcao de recepcao e os pinos TX e RX
  UCSR0B =  (1<<RXEN0) | (1<<TXEN0) | (1<<RXCIE0);

  //Configura a UART com 8 bits de dados
  UCSR0C =  (1<<UCSZ01) | (1<<UCSZ00); 
}

void interrupt_config()
{

}

void adc_config()
{
  /* Tadc = 1/1MHz = 1us
   * Primeira Conversao = 25*1 = 25us
   * Demais conversoes = 14*1 = 14us
   * Tempo total do prieiro ciclo = (25*1) + (14*1*5) = 95us
   * Tempo das demais conversoes = 14*1*6 = 84us
   * Utilizando teoria de amostragem -> 168->190us
   * FADC = 1MHz
   */
    
  ADMUX  = 0x60; // 0110-0000   // Referencia no AVCC, deslocado a direita
  ADCSRA = 0x8c; // 1000-1100   // ADC habilitado, interrupcao do AD habilitado e prescaler de 16 - 1MHz
  ADCSRB = 0x00; // 0000-0000   // Modo livre
  //DIDR0 = 0x3f;// 0011-1111   // Desabilita a entrada digital desses terminais

  // Atencao! Segundo o datasheet quanto maior a velocidade,
  // menor a precisao do AD, logo, utilizar 8bits em freq. elevadas
}

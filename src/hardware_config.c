#include "hardware_config.h"
//#include "adc_conversion.h"

void io_config()
{
    // 0 = entrada 1 = saida 
    DDRB  = 0b11001111; //cont_disp como saída 
    DDRC  = 0b00001111; 
    DDRD  = 0b11111110;

    // entrada: 0 = sem pull-up 1 = com pull-up 
    // saida:   0 = low         1 = high
    PORTB = 0b00110000;
    PORTC = 0b00000000; //inicio as saídas apagadas
    PORTD = 0b00000000; //inicio o led apagado
}

void timer_config()
{
  /*tempo =65536 * Prescaler/Fosc = 65536 * 1024/16000000 = 4, 19s
    tempo = X_bit_timer * Prescaler/Fosc
    Valor inicial de contagem = 256 - tempo_desejado*Fosc/Prescaler = 256 - 0,00025*16000000/1024 = 252
    Valor inicial de contagem = X_bit_timer - tempo_desejado*Fosc/Prescaler */

    TCCR0B = 0b00000101;    //prescaler de 1024
    TCNT0 =  252;           //contagem para gerar 250us
    TIMSK0 = 0b00000001;    //habilito interrupcao do timer0
}

void uart_config(uint16_t size)
{
  UBRR0H = (uint8_t)(size>>8);  // 2 bits mais significativos de ubrr
  UBRR0L = (uint8_t)size;       // 8 bits menos significativos de ubrr
  
  //Habilita a interrupcao de recepcao e os pinos TX e RX
  UCSR0B =  (1<<RXEN0) | (1<<TXEN0) | (1<<RXCIE0);

  //Configura a UART com 8 bits de dados
  UCSR0C =  (1<<UCSZ01) | (1<<UCSZ00); 
}

void extern_interrupt_config()
{
  PCICR  = (1<<PCIE0);      // habilita a chave geral do PORTB
  PCMSK0 = 0b00111100;      // habilita: PB2, PB3, PB4 e PB5 
  PCIFR  = (1<<PCIF0);      // habilita as flags
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
    
  ADMUX  = 0x20; // 0010-0000   // Referencia no ARef, deslocado a esquerda
  ADCSRA = 0x8c; // 1000-1100   // ADC habilitado, interrupcao do AD habilitado e prescaler de 16 - 1MHz
  ADCSRB = 0x00; // 0000-0000   // Modo livre
  //DIDR0 = 0x3f;// 0011-1111   // Desabilita a entrada digital desses terminais

  // Atencao! Segundo o datasheet quanto maior a velocidade,
  // menor a precisao do AD, logo, utilizar 8bits em freq. elevadas
}

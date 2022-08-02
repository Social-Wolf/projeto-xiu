#include "uart.h"

void uart_send_char(uint8_t ch) 
{
  UDR0 = ch;
  //Aguarda o buffer ser desocupado
  while (!(UCSR0A & (1<<UDRE0)));
}

void uart_caractere_sending_service(uint8_t ch) 
{
  uart_send_char(ch);
}

void uart_decimal_sending_service(int16_t data)
{
  static uint8_t cenmil = 0, dezmil = 0, mil = 0, cen = 0, dez = 0, uni = 0;

  if(data < 0)
  {
    uart_caractere_sending_service('-');
    data *= (-1);
  }

  cenmil = data / 100000;
  dezmil = (data%100000) / 10000;
  mil = (data % 10000) / 1000;
  cen = (data%1000) / 100;
  dez = (data%100)/10;
  uni = (data%10);
  
  uart_send_char(cenmil + 48);
  uart_send_char(dezmil + 48);
  uart_send_char(mil + 48);
  uart_send_char(cen + 48);
  uart_send_char(dez + 48);
  uart_send_char(uni + 48);
} 

void uart_string_sending_service(int8_t *s)
{
  uint16_t i=0;
  while (s[i] != '\x0') 
  {
      uart_send_char(s[i++]);
  };
}

void uart_hex_sending_service(uint8_t ch)
{   
  uint8_t i,temp;
  for (i=0; i<2; i++)
  {
      temp = (ch & 0xF0)>>4;
      if ( temp <= 9)
          uart_send_char('0' + temp);
      else
          uart_send_char('A' + temp - 10);
      ch = ch << 4;    
    }
}
#include <stdint.h>
#include <avr/interrupt.h>

void uart_send_char(uint8_t ch);

void uart_caractere_sending_service(uint8_t ch);

void uart_decimal_sending_service(int16_t data);

void uart_string_sending_service(int8_t *s);

void uart_hex_sending_service(uint8_t ch);

int8_t get_uart_data(void);
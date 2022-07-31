#ifndef ADC_H
#define ADC_H

#include <stdint.h>
#include <avr/interrupt.h>

uint8_t leitura_adc[5];
void tratar_leitura_do_ADC(void);
void adc_conversion_ch_service(unsigned char channel);

#endif


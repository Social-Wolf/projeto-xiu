#ifndef ADC_H
#define ADC_H

#include <stdint.h>
#include <avr/interrupt.h>

uint8_t ad_read[7];

void set_ad_chanel_service(unsigned char channel);
uint8_t ad_read_service(void);
void read_ad_chanel(void);

#endif
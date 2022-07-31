#include "adc_conversion.h"

void adc_conversion_ch_service(unsigned char channel)
{
  ADMUX &= 0xf0;
  ADMUX |= (channel & 0x0f);
  
  ADCSRA |= 0x40;
}

uint8_t adc_read_service(void)
{
  unsigned char dado = ADCH;
  return dado;
}

void tratar_leitura_do_ADC(void)
{
    /* inicializo no setup na funcao calibration e em seguida toda
     * vez que ocorre uma conversao a interrupcao do AD ocorre
     * e entao esta funcao e chamada pelo vetor de interrupcao
     * do AD, obtendo os dados da conversao em "paralelo" a rotina */
    
    /* Leio primeiro o default que seria o primeiro canal
     * e em seguida faco uma logica circular de leitura dos canais */
    
  static uint8_t estado = 10;
  
  switch (estado) {
      
    case 0:
      estado = 1;
      leitura_adc[0] = adc_read_service();
      adc_conversion_ch_service(1);
      break;
        
    case 1:
      estado = 2;
      leitura_adc[1] = adc_read_service();
      adc_conversion_ch_service(2);
      break;

    case 2:
      estado = 3;
      leitura_adc[2] = adc_read_service();
      adc_conversion_ch_service(3);
      break;

    case 3:
      estado = 4;
      leitura_adc[3] = adc_read_service();
      adc_conversion_ch_service(5);
      break;

    case 4:
      estado = 0;
      leitura_adc[4] = adc_read_service();
      adc_conversion_ch_service(0);
      break;

    default:
      estado = 0;
      adc_conversion_ch_service(0);
      leitura_adc[0] = adc_read_service();
      break; 
  }    
}

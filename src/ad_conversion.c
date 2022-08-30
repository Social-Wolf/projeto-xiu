#include "ad_conversion.h"

void set_ad_chanel_service(uint8_t channel)
{
  ADMUX &= 0xf0;
  ADMUX |= (channel & 0x0f);
  
  ADCSRA |= 0x40;
}

uint8_t ad_read_service(void)
{
  uint8_t dado = ADCH;
  return dado;
}

void read_ad_chanel(void)
{/* inicializo no setup na funcaoo calibration e em seguida toda
     * vez que ocorre uma conversao a interrupcao do AD ocorre
     * e entao esta funcao e chamada pelo vetor de interrupcao
     * do AD, obtendo os dados da conversao em "paralelo" a rotina */
    
    /* Leio primeiro o default que seria o primeiro canal
     * e em seguida faco uma logica circular de leitura dos canais */
    
  static uint8_t estado = 10;

  switch (estado) 
  {
    case 4:
      estado = 5;
      set_ad_chanel_service(5);
      ad_read[4] = ad_read_service();
      break;

    case 5:
      estado = 4;
      set_ad_chanel_service(4);
      ad_read[5] = ad_read_service();
      break;

    default:
      estado = 5;
      set_ad_chanel_service(5);
      ad_read[4] = ad_read_service();
      break; 
  }    
}
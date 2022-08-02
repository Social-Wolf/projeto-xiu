#include "ad_conversion.h"

void set_ad_chanel_service(unsigned char channel)
{
  ADMUX &= 0xf0;
  ADMUX |= (channel & 0x0f);
  
  ADCSRA |= 0x40;
}

uint8_t ad_read_service(void)
{
  unsigned char dado = ADCH;
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
  
  switch (estado) {
      
    case 0:
      estado = 1;
      ad_read[0] = ad_read_service();
      set_ad_chanel_service(1);
      break;
        
    case 1:
      estado = 2;
      ad_read[1] = ad_read_service();
      set_ad_chanel_service(2);
      break;

    case 2:
      estado = 3;
      ad_read[2] = ad_read_service();
      set_ad_chanel_service(3);
      break;

    case 3:
      estado = 4;
      ad_read[3] = ad_read_service();
      set_ad_chanel_service(4);
      break;

    case 4:
      estado = 5;
      ad_read[4] = ad_read_service();
      set_ad_chanel_service(5);
      break;

    case 5:
      estado = 0;
      ad_read[5] = ad_read_service();
      set_ad_chanel_service(0);
      break;

    default:
      estado = 0;
      set_ad_chanel_service(0);
      ad_read[0] = ad_read_service();
      break; 
  }    
}
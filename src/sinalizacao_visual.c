#include "sinalizacao_visual.h"

#define set_bit(y,bit)      (y|=(1<<bit)) //coloca em 1 o bit x da variável Y 
#define clr_bit(y,bit)      (y&=~(1<<bit)) //coloca em 0 o bit x da variável Y 
#define cpl_bit(y,bit)      (y^=(1<<bit)) //troca o estado lógico do bit x da variável Y 
#define tst_bit(y,bit)      (y&(1<<bit)) //retorna 0 ou 1 conforme leitura do bit

/* Tabela verdade - demultiplex*/
/*  E   S2  S1  S0      Y
 *  0   0   0   0       1
 *  0   0   0   1       2
 *  0   0   1   0       3
 *  0   0   1   1       4
 *  0   1   0   0       5
 *  0   1   0   1       6
 *  0   1   1   0       7
 *  0   1   1   1       8       */

uint8_t read_ad_to_level(uint8_t leitura)
{
    uint8_t level;

    if(leitura <= 28)
    {
        level = 1;
     }
    else if(leitura <= 56)
    {
        level = 2; 
    }
    else if(leitura <= 84)
    {
        level = 3;
    }
    else if(leitura <= 112)
    {
        level = 4;
    }
    else if(leitura <= 140)
    {
        level = 5;
    }
    else if(leitura <= 168)
    {
        level = 6;
    }
    else if(leitura <= 196)
    {
        level = 7;
    }
    else if(leitura <= 224)
    {
        level = 8;
    }
    else if(leitura <= 255)
    {
        set_bit(PORTD, LED_8);
    }
    return level;
}

void visual_signal(uint8_t level)
{
    switch  (level)
    {
    case 1:
        clr_bit(PORTD, DMX_0);
        clr_bit(PORTD, DMX_1);
        clr_bit(PORTD, DMX_2);
        break;
    case 2:
        set_bit(PORTD, DMX_0);
        clr_bit(PORTD, DMX_1);
        clr_bit(PORTD, DMX_2);
        break;
    case 3:
        clr_bit(PORTD, DMX_0);
        set_bit(PORTD, DMX_1);
        clr_bit(PORTD, DMX_2);
        break;
    case 4:
        set_bit(PORTD, DMX_0);
        set_bit(PORTD, DMX_1);
        clr_bit(PORTD, DMX_2);
        break;
    case 5:
        clr_bit(PORTD, DMX_0);
        clr_bit(PORTD, DMX_1);
        set_bit(PORTD, DMX_2);
        break;
    case 6:
        set_bit(PORTD, DMX_0);
        clr_bit(PORTD, DMX_1);
        set_bit(PORTD, DMX_2);
        break;
    case 7:
        clr_bit(PORTD, DMX_0);
        set_bit(PORTD, DMX_1);
        set_bit(PORTD, DMX_2);
        break;
    case 8:
        set_bit(PORTD, DMX_0);
        set_bit(PORTD, DMX_1);
        set_bit(PORTD, DMX_2);
        break;
    default:
        break;
    }
}
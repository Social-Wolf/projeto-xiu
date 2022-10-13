#include "sinalizacao_visual.h"

#define set_bit(y,bit)      (y|=(1<<bit)) //coloca em 1 o bit x da variável Y 
#define clr_bit(y,bit)      (y&=~(1<<bit)) //coloca em 0 o bit x da variável Y 
#define cpl_bit(y,bit)      (y^=(1<<bit)) //troca o estado lógico do bit x da variável Y 
#define tst_bit(y,bit)      (y&(1<<bit)) //retorna 0 ou 1 conforme leitura do bit

/* Tabela verdade - demultiplex*/
/*  E   S2  S1  S0      Y
 *  0   0   0   0       0
 *  0   0   0   1       1
 *  0   0   1   0       2
 *  0   0   1   1       3
 *  0   1   0   0       4
 *  0   1   0   1       5
 *  0   1   1   0       6
 *  0   1   1   1       7       */

uint8_t read_ad_to_limit_level(uint8_t leitura, uint8_t limit_abs)
{
    uint8_t limit_level = 0;
    uint8_t passo = 0;
    uint8_t resolucao[9];

    passo = limit_abs/9; 

    resolucao[0] = passo;

    for(char i = 1; i<9; i++)
    {
        resolucao[i] = resolucao[i-1] + passo;        
    }

    if(leitura <= resolucao[0])
    {
        limit_level = 0;
    }
    else if(leitura <= resolucao[1])
    {
        limit_level = 1; 
    }
    else if(leitura <= resolucao[2])
    {
        limit_level = 2; 
    }
    else if(leitura <= resolucao[3])
    {
        limit_level = 3;
    }
    else if(leitura <= resolucao[4])
    {
        limit_level = 4;
    }
    else if(leitura <= resolucao[5])
    {
        limit_level = 5;
    }
    else if(leitura <= resolucao[6])
    {
        limit_level = 6;
    }
    else if(leitura <= resolucao[7])
    {
        limit_level = 7;
    }
    else
    {
        limit_level = 8;
        set_bit(PORTD, LED_8);
    }

    /*
    if(leitura <= 29)
    {
        limit_level = 0;
    }
    else if(leitura <= 56)
    {
        limit_level = 1; 
    }
    else if(leitura <= 84)
    {
        limit_level = 2; 
    }
    else if(leitura <= 112)
    {
        limit_level = 3;
    }
    else if(leitura <= 140)
    {
        limit_level = 4;
    }
    else if(leitura <= 168)
    {
        limit_level = 5;
    }
    else if(leitura <= 196)
    {
        limit_level = 6;
    }
    else if(leitura <= 224)
    {
        limit_level = 7;
    }
    else if(leitura <= 255)
    {
        limit_level = 8;
        set_bit(PORTD, LED_8);
    }
    */

    return limit_level;
}

uint8_t level_analisys(uint8_t limit_level)
{
    static uint8_t level = 0;

    if(limit_level == 0)
        set_bit(PORTB, SWITCH_OFF);
    else
        clr_bit(PORTB, SWITCH_OFF);

    if(limit_level != 8)
        clr_bit(PORTD, LED_8);

    if(level >= limit_level)
        level = 0;
    level++;

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
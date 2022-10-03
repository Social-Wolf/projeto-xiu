#include "hardware_config.h"
#include "contador.h"
#include "sinalizacao_visual.h"
#include "menu_control.h"
#include "ad_conversion.h"

#define set_bit(y,bit)      (y|=(1<<bit)) //coloca em 1 o bit x da variável Y 
#define clr_bit(y,bit)      (y&=~(1<<bit)) //coloca em 0 o bit x da variável Y 
#define cpl_bit(y,bit)      (y^=(1<<bit)) //troca o estado lógico do bit x da variável Y 
#define tst_bit(y,bit)      (y&(1<<bit)) //retorna 0 ou 1 conforme leitura do bit

// int8_t menu_flag = 0, confirm_flag = 0;

void select_function(uint8_t menu_flag)
{        
    switch(menu_flag)
    {
        case 0:
            exit_menu();
            break;
        case 1:
            init_menu();
            break;
        case 2:
            function_visual();
            break;
        case 3:
            function_alarm();
            break;
        // case 4:
        //     function_alarm();
        //     break;    
    }
}

void init_menu()
{
    set_bit(PORTD, LED_VISUAL);
    set_bit(PORTD, LED_ALARM);
    visual_signal(level_analisys(0)); //?
}

void exit_menu()
{
    clr_bit(PORTD, LED_VISUAL);
    clr_bit(PORTD, LED_ALARM);
}

void function_visual()
{
    cpl_bit(PORTD, LED_VISUAL);
    set_bit(PORTD, LED_ALARM);
}

void function_alarm()
{
    set_bit(PORTD, LED_VISUAL);
    cpl_bit(PORTD, LED_ALARM);
    OCR1A = (uint16_t) (1023*(ad_read[5]/255.0));
}
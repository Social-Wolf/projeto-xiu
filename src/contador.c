#include <avr/io.h>
#include "contador.h"
#include <stdbool.h>          //Biblioteca que permite utilizar variavel booleana

#define set_bit(y,bit)      (y|=(1<<bit)) //coloca em 1 o bit x da variável Y 
#define clear_bit(y,bit)    (y&=~(1<<bit)) //coloca em 0 o bit x da variável Y 
#define cpl_bit(y,bit)      (y^=(1<<bit)) //troca o estado lógico do bit x da variável Y 
#define tst_bit(y,bit)      (y&(1<<bit)) //retorna 0 ou 1 conforme leitura do bit

/*Funcionamento do mux*/

//bits:3 2 1 0
       //0000   -> 0    PD0 = 0
       //0001   -> 1    PD0 = 1
       //0010   -> 2    PD1 = 1
       //0011   -> 3    PD1 e PD0 = 1
       //0100   -> 4    PD2 = 1
       //0101   -> 5    PD2 e PD0 = 1
       //0110   -> 6    PD2 e PD1 = 1
       //0111   -> 7    PD2 -> PD0 = 1
       //1000   -> 8    PD3 = 1
       //1001   -> 9    PD3 e PD0 = 1

void show_display(unsigned char number)
{
    switch (number)
    {
        case 0:
        clear_bit(PORTC, PC0);
        clear_bit(PORTC, PC1);
        clear_bit(PORTC, PC2);
        clear_bit(PORTC, PC3);
        break;

        case 1:
        set_bit(PORTC, PC0);
        clear_bit(PORTC, PC1);
        clear_bit(PORTC, PC2);
        clear_bit(PORTC, PC3);
        break;

        case 2:
        clear_bit(PORTC, PC0);
        set_bit(PORTC, PC1);
        clear_bit(PORTC, PC2);
        clear_bit(PORTC, PC3);
        break;

        case 3:
        set_bit(PORTC, PC0);
        set_bit(PORTC, PC1);
        clear_bit(PORTC, PC2);
        clear_bit(PORTC, PC3);
        break;

        case 4:
        clear_bit(PORTC, PC0);
        clear_bit(PORTC, PC1);
        set_bit(PORTC, PC2);
        clear_bit(PORTC, PC3);
        break;

        case 5:
        set_bit(PORTC, PC0);
        clear_bit(PORTC, PC1);
        set_bit(PORTC, PC2);
        clear_bit(PORTC, PC3);
        break;

        case 6:
        clear_bit(PORTC, PC0);
        set_bit(PORTC, PC1);
        set_bit(PORTC, PC2);
        clear_bit(PORTC, PC3);
        break;

        case 7:
        set_bit(PORTC, PC0);
        set_bit(PORTC, PC1);
        set_bit(PORTC, PC2);
        clear_bit(PORTC, PC3);
        break;

        case 8:
        clear_bit(PORTC, PC0);
        clear_bit(PORTC, PC1);
        clear_bit(PORTC, PC2);
        set_bit(PORTC, PC3);
        break;

        case 9:
        set_bit(PORTC, PC0);
        clear_bit(PORTC, PC1);
        clear_bit(PORTC, PC2);
        set_bit(PORTC, PC3);
        break;
    }
}

void display_7seg(unsigned char dezena, unsigned char unidade)
{
    static bool estado = 0;

    switch (estado)
    {
        case 0:
            set_bit(PORTB, PB6);
            clear_bit(PORTB, PB7);
            show_display(unidade);
            //estado = 1;
            break;

        case 1:
            clear_bit(PORTB, PB6);
            set_bit(PORTB, PB7);
            show_display(dezena);
            estado = 0;
            break;
    }
}
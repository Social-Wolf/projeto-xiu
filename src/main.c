#include "main.h"

uint16_t max_timer0, max_timer1, max_timer2, max_timer3, max_timer4, max_timer5;
uint8_t  unidade = 0, dezena = 0;
uint8_t  limit, level;
uint8_t  memoria;

int8_t main()
{
    setup();
    while(1)  loop();

    return 0;
}

void setup(void)
{
    setup_hardware();
    setup_software();
}

void setup_hardware(void)
{
    cli();  // desalibita todas as  interrupcoes
  
    io_config();
    timer_config();
    uart_config(16);
    adc_config();
    extern_interrupt_config();

    sei();  // habilita todas as interrupcoes
}

void setup_software(void)
{
    max_timer0 =    1;  // tempo: 250us
    max_timer1 =    2;  // tempo: 500us 
    max_timer2 =    3;  // tempo: 750us
    max_timer3 =    4;  // tempo:   1ms
    max_timer4 =    8;  // tempo:   2ms
    max_timer5 = 4000;  // tempo: 1segundo

    read_ad_chanel();
}

void loop(void)
{

}

void f_timers() // chamada a cada 1ms
{
    static uint16_t cont1 = 0, cont2 = 0, cont3 = 0, cont4 = 0, cont5 = 0;

    f_timer0(); 

    if(cont1 < max_timer1) cont1++; 
    
    else // base de tempo de 200ms
    {
        cont1 = 0;
        f_timer1(); 
    }

    if(cont2 < max_timer2) cont2++;

    else // base de tempo de 400ms
    {
        cont2 = 0;
        f_timer2();
    }

    if(cont3 < max_timer3) cont3++;

    else // base de tempo de 600ms
    {
        cont3 = 0;
        f_timer3();
    }

    if(cont4 < max_timer4) cont4++;

    else // base de tempo de 800ms
    {
        cont4 = 0;
        f_timer4();
    }

    if(cont5 < max_timer5) cont5++;

    else // base de tempo de 1segundo
    {
        cont5 = 0;
        f_timer5();
    }

}

void f_timer0(void) // 250us
{   
    if(menu_flag == 0)
    {
        limit = read_ad_to_level(ad_read[4]);
        visual_signal(level_analisys(limit));
        DDRC  = 0b00011111;
        PORTC &= (0<<5);
        PORTC &= (1<<6);
    }
    else if(menu_flag == 1)
    {        
        DDRC  = 0b00111111;
        PORTC &= (0<<5);
        PORTC &= (0<<6);
    }
    else if(menu_flag == 2)
    {
        limit = read_ad_to_level(ad_read[5]);
        visual_signal(level_analisys(limit));
        DDRC  = 0b00101111;
        PORTC &= (1<<5);
        PORTC &= (0<<6);
    }
    else if(menu_flag == 3)
    {
        limit = read_ad_to_level(ad_read[5]);
        visual_signal(level_analisys(limit));
        DDRC  = 0b00101111;
        PORTC &= (1<<5);
        PORTC &= (0<<6);
    }
    else level = 0;
}

void f_timer1(void) // 500us
{
    
}

void f_timer2(void) // 750us
{
    //uart_string_sending_service("ola");
    //uart_string_sending_service("\n");
    memoria = ad_read[4];
    sprintf(buffer, "%d\t%d\t%d\t%d\n", menu_flag, ad_read[4], ad_read[5], limit);
    uart_string_sending_service(buffer); 
    // sprintf(buffer, "%d\t%d\t%d\t%d\n", menu_flag, ad_read[4], ad_read[5], level);
    // uart_string_sending_service(buffer);    
}

void f_timer3(void) // 1ms
{
    display_7seg(dezena, unidade);
}

void f_timer4(void) // 2ms
{
    
}

void f_timer5(void) // 1segundo
{   
    select_function(menu_flag);
    unidade++;   
    if(unidade > 9)
    {
        unidade = 0;
        dezena++;
    }
    if(dezena > 9)
        dezena = 0;
}

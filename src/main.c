#include "main.h"

unsigned int  max_timer0, max_timer1, max_timer2, max_timer3, max_timer4, max_timer5;
unsigned int unidade = 0, dezena = 0;
unsigned int  millis; 

ISR(TIMER0_OVF_vect) 
{
  TCNT0 = 240; // recarrega o Timer 0 para contagem de 1ms
  millis++;
  f_timers();
}

int main()
{
    setup_hardware();
    setup_software();  
    while(1)  loop();

    return 0;
}

void setup_hardware(void)
{
    cli();  //desalibita todas as  interrupcoes
  
    io_config();
    timer_config();

    sei();  //habilita todas as interrupcoes
}

void setup_software(void)
{
    max_timer0 =    1;  // tempo:   1ms
    max_timer1 =  200;  // tempo: 200ms 
    max_timer2 =  400;  // tempo: 400ms
    max_timer3 =  600;  // tempo: 600ms
    max_timer4 =  800;  // tempo: 800ms
    max_timer5 = 1000;  // tempo: 1segundo
}

void loop(void)
{
}

void f_timers() // chamada a cada 1ms
{
    static unsigned int cont0 = 0, cont1 = 0, cont2 = 0, cont3 = 0, cont4 = 0, cont5 = 0;

    if(cont0 < max_timer0) cont0++; 
    
    else // base de tempo de  10ms
    {
        cont0 = 0;
        f_timer0(); 
    }

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

void f_timer0(void) //   1ms
{   
}

void f_timer1(void) // 200ms
{

}

void f_timer2(void) // 400ms
{
  
}

void f_timer3(void) // 600ms
{
    cpl_bit(PORTD, PD6);
}

void f_timer4(void) // 800ms
{
    display_7seg(dezena, unidade);
    cpl_bit(PORTD, PD7);
}

void f_timer5(void) // 1segundo
{   
    unidade++;   
    if(unidade > 9)
    {
        unidade = 0;
        dezena++;
    }
    if(dezena > 9) dezena = 0;
    cpl_bit(PORTB, PB0);
}

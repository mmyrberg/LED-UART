#include "UART.h" //Inkludera headerfiler.
#include "LED.h"

//Deklarera variabler av typen Led_Type för att hantera LED-lampor (led1, led2).
Led_Type led1;
Led_Type led2;

//Huvudfunktion konstruerar och hanterar LED-lamporna, programmets startpunkt. 
int main(void) {
    USART2_Init(); //Upprätta kommunikationen genom att anropa USART2_Init. 
    
    //Konstruera led1 och led2 med rött resp. blått ljus samt avstängd resp. påslagen status.
    Led_ctor(&led1,RED,OFF);
    Led_ctor(&led2,BLUE,ON);
    
    Led_getState(&led1); //Hämta och skriv ut statusen för led1.

    Led_setState(&led2,OFF); //Ställ in led2 till avstängd status.
    
    while(1){} //Evig loop som håller igång programmet. 

    return 0;
}
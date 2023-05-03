// Denna fil knyter samman UART.c och Main.c 
ifndef  __UART_H
#define  __UART_H // Initierar att vår headerfil börjar

#include "stm32f4xx.h" // Hämtar källkoden och hänvisningar för arbete på STM-hårdvara. 
#include <stdio.h> //  Inkluderar standard I/O för C

void USART2_Init(void); // Kallar på och refererar till deklarationen av vår UART-funktion
void test_setup(void); //Kallar på och refererar till vår testfunktion ur UART.c

#endif // förtydligar avslutningen av vår headerfil
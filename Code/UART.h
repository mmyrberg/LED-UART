//Denna fil knyter samman UART.c och Main.c 
#ifndef UART_H //Kolla om __UART_H är definierat.
#define UART_H //Om inte så definieras det och all kod som följer inkluderas.

#include "stm32f4xx.h" //Inkludera biblioteket för denna mikrokontroller så att vi får tillgång till den källkod och hänvisningar vi behöver för arbete på STM-hårdvara.
#include <stdio.h> //Inkluderar standard I/O för C. Möjliggör användning av standardin- och utdatafunktioner som printf() och scanf().

void USART2_Init(void); //Deklarera UART-funktionen i UART.c
void test_setup(void); //Deklarera testfunktionen i UART.c

#endif //Markerar avslutningen av denna headerfil.
#include "UART.h"
#include "LED.h"

Led_Type led1;
Led_Type led2;

int main(void){ //huvudfunktion konstruerar och hanterar LED-lamporna
  USART2_Init();
  
  Led_ctor(&led1,RED,OFF);
  Led_ctor(&led2,BLUE,ON);
  
  Led_getState(&led1);
  Led_setState(&led2,OFF);
  
  while(1){}
  
}
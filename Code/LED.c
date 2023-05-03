include "LED.h" //Inkluderar headerfilen för att även denna fil skall känna till de olika LED-beteckningarna och funktioner

//Konstruktorn för LED-lamporna med typ, färg och status
void Led_ctor(Led_Type * const me, LedColor_Type _color, LedState_Type _state){
  
	me->color  = _color;
	me->state  = _state; 

	//Enablea klockan för LED-porten (GPIOB)
	RCC->AHB1ENR |= LED_PORT_CLOCK;  
	
	//Konfiguera LED-pinsen baserad på deras färg och status
	switch(_color){
		 
		case RED: //Sätta portläget för LED-konfigurationen till output
			LED_PORT->MODER |=LED_RED_MODE_BIT;
		  if(me->state  == ON){ //Sätter på LED
			   LED_PORT->ODR |= LED_RED_PIN;
				printf("The RED Led is set ON \n\r");
			}
			else{ //Stänger av LED
			  LED_PORT->ODR &= ~LED_RED_PIN;
        printf("The RED Led is set OFF \n\r");

			}
		break;
		
		case YELLOW: //Sätta portläget för LED-konfigurationen till output
			LED_PORT->MODER |=LED_YELLOW_MODE_BIT;
		  if(me->state  == ON){//Sätter på LED
			   LED_PORT->ODR |= LED_YELLOW_PIN;
				printf("The YELLOW Led is set ON \n\r");
			}
			else{//Stänger av LED
			  LED_PORT->ODR &= ~LED_YELLOW_PIN;
        printf("The YELLOW Led is set OFF \n\r");

			}
		break;
		
		case BLUE: //Sätta portläget för LED-konfigurationen till output
			LED_PORT->MODER |=LED_BLUE_MODE_BIT;
		  if(me->state  == ON){//Sätter på LED
			   LED_PORT->ODR |= LED_BLUE_PIN;
				printf("The BLUE Led is set ON \n\r");
			}
			else{//Stänger av LED
			  LED_PORT->ODR &= ~LED_BLUE_PIN;
        printf("The BLUE Led is set OFF \n\r");

			}
		break;
		
		case GREEN://Sätta portläget för LED-konfigurationen till output
			LED_PORT->MODER |=LED_GREEN_MODE_BIT;
		  if(me->state  == ON){//Sätter på LED
			   LED_PORT->ODR |= LED_GREEN_PIN;
				printf("The GREEN Led is set ON \n\r");
			}
			else{//Stänger av LED
			  LED_PORT->ODR &= ~LED_GREEN_PIN;
        printf("The GREEN Led is set OFF \n\r");

			}
		break;
	}
}

void Led_setState(Led_Type * const me,LedState_Type _state){
	//Sätta statusen av LED:n
	 me->state =  _state;

	//Kolla fären på LED för att veta att korrekt LED manipuleras
	switch(me->color){
		 //om LED Röd
		case RED:
			LED_PORT->MODER |=LED_RED_MODE_BIT; //Sätta pin till outputläge
		  if(me->state  == ON){ //Om önskad status är ON
			   LED_PORT->ODR |= LED_RED_PIN; //Definiera pinsens output till aktiv
				printf("The RED Led is set ON \n\r");
			}
			else{
			  LED_PORT->ODR &= ~LED_RED_PIN; //Definiera pin output till inaktiv
        printf("The RED Led is set OFF \n\r");

			}
		break;
		
		case YELLOW:
			LED_PORT->MODER |=LED_YELLOW_MODE_BIT;//Sätta pin till outputläge
		  if(me->state  == ON){//Om önskad status är ON
			   LED_PORT->ODR |= LED_YELLOW_PIN;//Definiera pinsens output till aktiv
				printf("The YELLOW Led is set ON \n\r");
			}
			else{
			  LED_PORT->ODR &= ~LED_YELLOW_PIN;//Definiera pin output till inaktiv
        printf("The YELLOW Led is set OFF \n\r");

			}
		break;
		
		case BLUE:
			LED_PORT->MODER |=LED_BLUE_MODE_BIT;//Sätta pin till outputläge
		  if(me->state  == ON){//Om önskad status är ON
			   LED_PORT->ODR |= LED_BLUE_PIN;//Definiera pinsens output till aktiv
				printf("The BLUE Led is set ON \n\r");
			}
			else{
			  LED_PORT->ODR &= ~LED_BLUE_PIN;//Definiera pin output till inaktiv
        printf("The BLUE Led is set OFF \n\r");

			}
		break;
		
		case GREEN:
			LED_PORT->MODER |=LED_GREEN_MODE_BIT;//Sätta pin till outputläge
		  if(me->state  == ON){//Om önskad status är ON
			   LED_PORT->ODR |= LED_GREEN_PIN;//Definiera pinsens output till aktiv
				printf("The GREEN Led is set ON \n\r");
			}
			else{
			  LED_PORT->ODR &= ~LED_GREEN_PIN;//Definiera pin output till inaktiv
        printf("The GREEN Led is set OFF \n\r");

			}
		break;
	
	}
}

LedState_Type Led_getState(Led_Type * const me){

	//Kontollera färgen av den LED som efterfrågas, printa sedan statusen
	switch(me->color){
		
		case RED:
			   printf("The RED Led is cureently %d \n\r",me->state);
				 break;
	  	case GREEN:
			   printf("The GREEN Led is cureently %d \n\r",me->state);
				 break;
		case BLUE:
			   printf("The BLUE Led is cureently %d\n\r",me->state);
				 break;
		case YELLOW:
			   printf("The YELLOW Led is cureently  %d \n\r",me->state);
				 break;
	 }
  
	return me->state; //Returnerar LED-lampas status av vald färg
}
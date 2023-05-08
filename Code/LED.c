#include "LED.h" //Inkludera headerfilen för att denna fil skall känna till dem olika LED-beteckningarna och funktionerna.

//Konstruktorn för LED-lamporna. Sätter lampornas initiala värden för färg och status.
void Led_ctor(Led_Type *const me, LedColor_Type _color, LedState_Type _state) {

    //Sätter färg och status för LED-lampan som me pekar på till de värden som skickas med som argument i _color och _state.
    me->color  = _color;
    me->state  = _state; 

    //Aktiverar klockan för GPIO-porten som LED-lampan är ansluten till
    RCC->AHB1ENR |= LED_PORT_CLOCK;  

    //Switch-sats för att konfiguera LED-pinsen beroende på deras färg och status
    switch(_color){
        case RED: //Om färgen är röd...
            LED_PORT->MODER |= LED_RED_MODE_BIT; //...ställ in moder-registret med LED_RED_MODE_BIT för att enbart den bit som representerar den röda LED-pinsen blir konfiguerad som en utgångsport (output). 
            if(me->state == ON){ //Om state är ON (1)...
                LED_PORT->ODR |= LED_RED_PIN; //...slå på LED-lampan genom att ändra status i ODR-registret till aktiv för den röda LED-pinsen...
                printf("The RED Led is set ON \n\r"); //...och skriv ut att den röda LED:n är påslagen.
            }
            else{ //Annars, state är OFF (0)...
                LED_PORT->ODR &= ~LED_RED_PIN; //...stäng av LED-lampan genom att ändra status på ODR-registret till att inaktivera den röda LED-pinsen...
                printf("The RED Led is set OFF \n\r"); //...och skriv ut att den röda LED är OFF.
            }
        break;
        //Upprepa samma princip för övriga färger.
        case YELLOW:
            LED_PORT->MODER |= LED_YELLOW_MODE_BIT;
            if(me->state == ON){
                LED_PORT->ODR |= LED_YELLOW_PIN;
                printf("The YELLOW Led is set ON \n\r");
            }
            else{
                LED_PORT->ODR &= ~LED_YELLOW_PIN;
                printf("The YELLOW Led is set OFF \n\r");
            }
        break;

        case BLUE:
            LED_PORT->MODER |= LED_BLUE_MODE_BIT;
            if(me->state == ON){
                LED_PORT->ODR |= LED_BLUE_PIN;
                printf("The BLUE Led is set ON \n\r");
            }
            else{
                LED_PORT->ODR &= ~LED_BLUE_PIN;
                printf("The BLUE Led is set OFF \n\r");
            }
        break;

        case GREEN:
            LED_PORT->MODER |= LED_GREEN_MODE_BIT;
            if(me->state == ON){
                LED_PORT->ODR |= LED_GREEN_PIN;
                printf("The GREEN Led is set ON \n\r");
            }
            else{
                LED_PORT->ODR &= ~LED_GREEN_PIN;
                printf("The GREEN Led is set OFF \n\r");
            }
        break;
    }
}
//Funktion för att ställa in statusen för en LED-lampa.
void Led_setState(Led_Type *const me,LedState_Type _state) {
    
    //Sätter önskad status på LED.
    me->state =  _state;

    //Switch-sats med färgen som en villkor för att avgöra vilken LED-lampa som ska manipuleras.
    switch(me->color){
        case RED: //Om LED har färgen röd...
            LED_PORT->MODER |= LED_RED_MODE_BIT; //...ställ in moder-registret så att den pin som är kopplad till den röda LED-lampan sätts till utgångsläge (output).
            if(me->state == ON){ //Om önskad status är ON...
                LED_PORT->ODR |= LED_RED_PIN; //...ställ in pin output till aktiv för att tända den röda LED-lampan...
                printf("The RED Led is set ON\n\r"); //...och skriv ut att den röda LED:n är påslagen.
            }
            else{ //Annars, om önskad status är OFF...
                LED_PORT->ODR &= ~LED_RED_PIN; //...ställ in pin output till inaktiv för att släcka den röda LED-lampan...
                printf("The RED Led is set OFF\n\r"); //...och skriv ut att den röda LED:n är OFF.
            }
        break;
        //Upprepa samma princip för övriga färger.
        case YELLOW:
            LED_PORT->MODER |= LED_YELLOW_MODE_BIT;
            if(me->state == ON){
                LED_PORT->ODR |= LED_YELLOW_PIN;
                printf("The YELLOW Led is set ON\n\r");
            }
            else{
                LED_PORT->ODR &= ~LED_YELLOW_PIN;
                printf("The YELLOW Led is set OFF\n\r");
            }
        break;

        case BLUE:
                LED_PORT->MODER |= LED_BLUE_MODE_BIT;
            if(me->state == ON){
                LED_PORT->ODR |= LED_BLUE_PIN;
                printf("The BLUE Led is set ON\n\r");
            }
            else{
                LED_PORT->ODR &= ~LED_BLUE_PIN;
                printf("The BLUE Led is set OFF\n\r");
            }
        break;

        case GREEN:
            LED_PORT->MODER |= LED_GREEN_MODE_BIT;
            if(me->state == ON){
                LED_PORT->ODR |= LED_GREEN_PIN;
                printf("The GREEN Led is set ON\n\r");
            }
            else{
                LED_PORT->ODR &= ~LED_GREEN_PIN;
                printf("The GREEN Led is set OFF\n\r");
            }
        break;
    }
}
//Funktion för att kontrollera vilken status (av/på) en LED-lampa har. 
LedState_Type Led_getState(Led_Type *const me) {

    //Switch-sats som kontollerar färgen på den LED-lampa som efterfrågas och printar sedan ut statusen.
    switch(me->color){
        case RED:
            printf("The RED Led is currently %d\n\r", me->state);
        break;

        case GREEN:
            printf("The GREEN Led is currently %d\n\r", me->state);
        break;

        case BLUE:
            printf("The BLUE Led is currently %d\n\r", me->state);
        break;

        case YELLOW:
            printf("The YELLOW Led is currently %d\n\r", me->state);
        break;
    }

    //Returnerar LED-lampas status av vald färg.
    return me->state; 
}
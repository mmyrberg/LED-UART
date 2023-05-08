#ifndef LED_H //Denna headerfil knyter samman LED.c och Main.c
#define LED_H //Initierar att vår headerfil börjar.

#include <stdint.h> //Inkludera standardbibliotek för C. Ger oss heltalstyper med exakt storlek oberoende av underliggande hårdvara (int8_t, uint8_t, int16_t, uint16_t, int32_t, uint32_t, int64_t, uint64_t).
#include "UART.h" //Inkluderar vår uart headerfil, vår drivrutin.
#include "stm32f4xx.h" //Device Header för enhetsspecifika angivelser om hårdvaran.

//Definiera vilken GPIO som skall vara ansvarig för LED-funktionen. Alla gånger headern inkluderas och LED_PORT skrivs så är detta synonymt med GPIOB.
#define LED_PORT GPIOB

//Definiera klocksignalen för porten. vänsterskiftar LED_PORT_CLOCK från 1 (00000001) till 2 (00000010). Detta motsvarar den bit som styr klocksignalen.
#define LED_PORT_CLOCK (1U<<1)

//Definiera bitpositionerna för de GPIO-pins som är kopplade till LED-lamporna på mikrokontrollern.
#define LED_RED_PIN (1U<<14) //Definiera den 14:e biten i registeradressen för att styra röda LED-lampan (dvs. den 14:e biten är satt till 1 och alla andra bitar är satta till 0). Samma princip på övriga nedan. 
#define LED_GREEN_PIN (1U<<12)
#define	LED_BLUE_PIN (1U<<15)
#define LED_YELLOW_PIN (1U<<13)

//Definiera mode bits för varje LED-färg.
#define LED_RED_MODE_BIT (1U<<28) //Definierar bitpositionen 28 som motsvarar en röd LED-lampa. Samma princip för övriga nedan.
#define LED_GREEN_MODE_BIT (1U<<24)
#define LED_YELLOW_MODE_BIT (1U<<26)
#define LED_BLUE_MODE_BIT (1U<<30)

//Definiera de olika LED-färgerna som finns.
typedef enum { //Skapar en ny datatyp som kallas LedColor_Type och kan innehålla fyra olika värden som representerar färgerna för de olika LED-lamporna.
    RED = 0, //Röd börjar på 0, grön är 1 osv. 
    GREEN,
    YELLOW,
    BLUE
}LedColor_Type; //Denna nya datatyp kan användas för att skapa variabler som representerar en av dessa fyra färger.

//Definierar LED-lampans status, om den är av eller på.
typedef enum {
    OFF = 0,
    ON = 1
}LedState_Type;  //Denna datatyp kallar vi för LedState_Type. Samma princip gäller som i ovan enum.

//Struct som definierar de attribut som en LED-lampa består utav.
typedef struct { //Innehåller två medlemmar som representerar färgen och statusen för en LED-lampa.
    LedColor_Type color; 
    LedState_Type state;  
}Led_Type; //Ges namnet Led_Type som blir en egen datatyp för variabler som kan lagra info om färg och status för en LED-lampa.

//Deklarera funktionerna för LED-konstruktorn, statusangivelse och statuskontroll. 
void Led_ctor(Led_Type *const me, LedColor_Type _color, LedState_Type _state); //Konstruktorn. Skapar en ny instans av structen Led_Type och sätter dess initiala värden, t.ex. att den ska vara röd och påslagen.
void Led_setState(Led_Type *const me, LedState_Type _state); //Uppdaterar LED-lampans status.
LedState_Type Led_getState(Led_Type *const me); //Hämtar LED-lampans nuvarande status.

#endif //Anger att headerfilen avslutas.
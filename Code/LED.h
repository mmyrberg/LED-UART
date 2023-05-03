#ifndef LED_H
#define LED_H // Initierar att vår headerfil börjar

#include <stdint.h> // ger oss heltalstyper med exakt bredd oberoende av underliggande hårdvara (int8_t, uint8_t, int16_t, uint16_t, int32_t, uint32_t, int64_t, uint64_t)
#include "UART.h" // inkluderar vår uartHeader
#include "stm32f4xx.h" //Device Header för enhetsspecifika angivelser om hårdvaran

//Definiera vilken GPIO som skall vara ansvarig för LED-funktionen
#define	LED_PORT GPIOB

//Definiera klocksignalen för porten
#define	LED_PORT_CLOCK (1U<<1)

//Definiera de olika pinsen för de olika LED-färgerna
#define LED_RED_PIN	(1U<<14)
#define LED_GREEN_PIN (1U<<12)
#define	LED_BLUE_PIN (1U<<15)
#define LED_YELLOW_PIN (1U<<13)

//Definiera mode bits för varje LED-färg
#define LED_RED_MODE_BIT (1U<<28)
#define LED_GREEN_MODE_BIT (1U<<24)
#define LED_YELLOW_MODE_BIT (1U<<26)
#define LED_BLUE_MODE_BIT (1U<<30)

//Definiera de olika LED-färgerna som finns
typedef  enum {
	RED	= 0,
	GREEN,
	YELLOW,
	BLUE
}LedColor_Type;

//Definierar/numrerar de olika lägena som LED kan befinna sig i
typedef enum {
	OFF =0,
	ON = 1
}LedState_Type;

//Definierar de attribut som LED bestå utav
typedef struct {
	LedColor_Type color; 
	LedState_Type state;  
}Led_Type;

//Deklarerar funktionerna för LED-konstruktion och statuskontrollen
void Led_ctor(Led_Type * const me, LedColor_Type _color, LedState_Type _state);
void Led_setState(Led_Type * const me,LedState_Type _state);
LedState_Type Led_getState(Led_Type * const me);

#endif // förtydligar avslutningen av vår headerfil
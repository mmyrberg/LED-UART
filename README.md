# Hantera en LED med UART-protokollet
Slutuppgift i kursen *Inbyggda System: Arkitektur och Design*

> Länk till projekt: https://github.com/mmyrberg/LED-UART

## Innehållsförteckning
* **Beskrivning**
* **Krav**
* **Installation**
* **Användning**

### Beskrivning 
Detta projekt innehåller en drivrutin i programspråket C för att aktivera UART-protokollet för kommunikation mellan en mikrokontroller (stm32F411x) och en LED-lampa. Drivrutinen aktiverar sändning och mottagning av data och underlättar kommunikationen genom ett antal funktioner för att initiera och hantera dataöverförning och eventuella avbrott som genereras. Även om kommunikation med en LED-lampa etableras i detta projekt går det även bra att nyttja denna drivrutin för kommunikation med andra enheter som använder UART-protkollet.

### Krav
För att använda denna UART-drivrutin krävs följande:
*   STM32F411x mikrokontrollerplattform
*   STM32CubeIDE eller liknande IDE
*   STM32F411x Hardware Abstraction Layer (stm32f4xx.h) 
*   UART-kabel eller en USB-till-UART-converter

### Installation
1. Ladda ner källkoden som en ZIP-fil eller klona projektet från github
2. Importera projektet i din IDE och lägg till nödvändiga Hardware Abstraction Layer (HAL)
3. Inkludera headerfilen uart.h till din programvara
4. Gå till filen UART.c och anpassa UART-inställningarna för att passa dina behov genom att ändra önskade konfigurationsparametrar i funktionen USART2_Init()
5. Anropa funktionerna från din applikation

### Användning
De funktioner som är tillgängliga för att använda UART-drivrutinen inkluderar:
* `USART2_Init`: Använd för att initiera USART-protokollet och dess beståndsdelar (se exempel nedan) 
* `USART2_write`: Använd för att skriva och sända data med hjälp av UART-gränssnittet
* `USART2_read`: Använd för att läsa och ta emot data med hjälp av UART-gränssnittet

#### Exempelkod (C):
```
#include "UART.h"

void USART2_Init(void) { 
    //Aktivera klocktillgång för USART2.  
    RCC->APB1ENR |= 0x20000;
    //Aktivera klocktillgång för GPIO-port A.
    RCC->AHB1ENR |= 0x01;
    //Konfiguera pinsen PA2 och PA3 som ut- respektive ingång för alternativa funktioner.
    GPIOA->MODER &= ~0x00F0; 
    GPIOA->MODER |= 0x00A0; 
    //Konfiguera typen av alternativ funktion för PA2 och PA3.
    GPIOA->AFR[0] &= ~0xFF00;
    GPIOA->AFR[0] |= 0x7700; 

    /*Konfiguration av UART.*/
    USART2->BRR = 0x0683; //Sätt standard baud-rate till 9600bps
    USART2->CR1 = 0x000C; //Sätt transmit (tx) och receive (rx) till att arbeta i 8 bitars data (8 bitars data, 1 stop bit, ingen paritet).
    USART2->CR2 = 0x000; //Nollställ USART2:s CR2-register.
    USART2->CR3 = 0x000; //Nollställ USART2:s CR3-register.
    USART2->CR1 |= 0x2000; //Ställ om bit 13 i CR1-registret till 1 för att aktivera UART.
}
```
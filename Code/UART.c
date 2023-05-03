#include "UART.h" // Hämtar vår samlingsfil för headers och funktioner. inkludera headerfilen UART, källkoden från STM för deras plattform f4xx

// Definiera funktion för att initiera Usart-protokollet och dess beståndsdelar. Denna funktion är en drivrutin.
void USART2_Init(void){ 
    // konfiguera systemklockan (RCC) för mikrokontrollern. 
    // Pilen "->" referear till headern "stm32f4xx.h", pekar på den, som pionters(*) fast för headerfiler.
    // APB1ENR är ett register inom RCC som används för att aktivera eller inaktivera klockan. 
    // När man bara sätter "=" finns risk att förkonfiguarade bitar skrivs över, därför använder man "|=", vilket gör att inget manupilueras längs vägen.
    // Värdet 0x20000 är en hexadecimal representation av det binära värdet 0010 0000 0000 0000 0000, som har en 1 i den 17:e bitpositionen(index) och nollor i alla andra bitpositioner. 
    // Tillsammans med "|=" innebär detta att man sätter bit 17 i APB1ENR-registret till 1 utan att påverka värdena för de andra bitarna i registret.
    // Genom att sätta bit 17 till 1 aktiverar koden klockan för en enhet som är ansluten till APB1-bussen.
    // 1. Enablea klocktillgång för uart2
    RCC->APB1ENR  |=  0x20000; // Aktiverar UART2 genom att sätta bit 17 i APB1ENR till 1.
    // 2. Enablea klocktillgång för port A
    RCC->AHB1ENR   |=0x01; // Aktiverar GPIO genom att sätta bit 0 i AHB1ENR till 1.
    // 3. Enablea pins relaterade till vald port, för alternativ funktion= betyder att den konverteras till att den används till. Vanliga funktionen är I/O, men när det gäller UART protokkollet är det inte längre en vanlig utan klassas. Är det vanlig I/O är inte alternativt, är det  
    GPIOA->MODER &=~0x00F0; // Rensar bitarna 4-7 för att förbereda pins PA2 och PA3.
     //"& samt ~ forcerar en invertering som leder till att bitarna som via hex betecknas med 1, i realvärde ersätts med 0".
    GPIOA->MODER |= 0x00A0; // Sätter bitarna 5 och 7 till 1 fö att aktivera alternativ funtionalitet på pins PA2 och PA3
    // 4. Välja typen av alternativ funktion för de valda pinsen, hakperenteserna syftar till att välja början av AFR-LOW/HIGH
    GPIOA->AFR[0] &= ~0xFF00; // Rensar bitarna 8-15 för att förbereda pins PA2 och PA3.
    GPIOA->AFR[0] |= 0x7700; // Sätter bitarna 8-11 samt 12-14 till formatet 0111
    // Nu är pin 2 och 3 redo för att skicka och ta emot UART-kommunikation
    /*Konstruktion av enhetens kommunikation avslutas*/

    // Konfiguration av UART
    USART2->BRR  =  0x0683; // Sätter en standard baud-rate med hjälp av hexadecimalen 0x0683 (9600bps)
    USART2->CR1  =  0x000C; // Sätter tx och rx till att arbeta i 8 bitars data. (8 bitars data, 1 stop bit, ingen paritet)
    USART2->CR2  =  0x000; // Nollställer CR2
    USART2->CR3  =  0x000; // Nollställer CR3
    USART2->CR1  |=  0x2000; // Omställer bit 13 (Uart-aktiveringen) till 1
}
    // UART Read och Write-regler
int USART2_write(int ch){ // Deklarerar skrivfunktionen (Överföringen av data till terminalen)
    //En loop för att skicka byte för byte
	while(!(USART2->SR & 0x0080)){} // Sätter ett krav som kontrollerar att statusen på överföringen är tom och kan ta emot nästa karaktär(byte)
	USART2->DR = (ch & 0xFF); // Sätter överföringen av byten till dataregistret
	
  return ch;
}
    //Uart read
int USART2_read(void){ // Deklarerar läsfunktionen (mottagning av information)
  while(!(USART2->SR & 0x0020)){} // Sätter ett krav som kontrollerar om det finns mer data att hämta
	return USART2->DR; // Läser ut datan
}
// Interface för standard I/O i C
// En omdiregering till att utge datan i terminalen
struct __FILE { int handle; }; // Strukturerar våra huvudsakliga överföringsströmmar
FILE __stdin  = {0};
FILE __stdout = {1};
FILE __stderr = {2};


int fgetc(FILE *f) { // fget hämtar en byte från standardströmmen och behandlar även teckenreturer
    int c;

    c = USART2_read();     

    if (c == '\r') {        
        USART2_write(c);    
        c = '\n';
    }

    USART2_write(c);       

    return c;
}

int fputc(int c, FILE *f) { // fput skriver en byte till standardströmmen
    return USART2_write(c);
}


int n; // Deklarerar en byte för användning i testfunktionen
char str[80]; // Sätter en limitering i överföringen av karaktärer
		
void test_setup(void){ // Testar vår läs- och skrivfunktion
	
	printf("please enter a number: ");
	scanf("%d", &n);
	printf("the number entered is: %d\r\n", n);
	printf("please type a character string: ");
	gets(str);
	printf("the character string entered is: ");
	puts(str);
	printf("\r\n");
	
}
#include "UART.h" //Inkludera vår headerfil UART.

//Definiera funktion för att initiera USART-protokollet och dess beståndsdelar. Denna funktion utgör en drivrutin.
void USART2_Init(void) { 
    // 1. Aktivera klocktillgång för USART2. APB1ENR är ett register inom RCC (systemklockan) som används för att aktivera eller inaktivera klockan. 
    RCC->APB1ENR |= 0x20000; //Aktiverar klockan för USART2 genom att sätta bit 17 i APB1ENR till 1. Om man bara sätter "=" finns risk att förkonfiguarade bitar skrivs över, därför använder vi "|=".
    // 2. Aktivera klocktillgång för port A.
    RCC->AHB1ENR |= 0x01; //Aktiverar klockan för GPIO-port A genom att sätta bit 0 i RCC's AHB1ENR-register till 1.
    // 3. Aktivera pins relaterade till vald port, för alternativ funktion, vilket ger GPIO-pinsen möjlighet att användas för andra syften än enkel in- och utdata (I/O), som t.ex. kommunikation med UART-protokollet.
    GPIOA->MODER &= ~0x00F0; //Rensar bitarna 4-7 i GPIO-port A:s MODER-register för att förbereda pins PA2 och PA3 ifall dessa är i andra lägen. "&" samt "~" forcerar en invertering som leder till att bitarna som via hex betecknas med 1, ersätts med 0.
    GPIOA->MODER |= 0x00A0; //Sätter bitarna 5 och 7 i GPIO-port A:s MODER-register till 1 för att aktivera alternativ funtionalitet på pins PA2 och PA3.
    // 4. Välj typen av alternativ funktion för de valda pinsen. Hakperenteserna syftar till att välja början av AFR-registret LOW/HIGH.
    GPIOA->AFR[0] &= ~0xFF00; //Rensar bitarna 8-15 för att förbereda pins PA2 och PA3 för alternativ funktion.
    GPIOA->AFR[0] |= 0x7700; //Sätter bitarna 8-11 samt 12-14 till formatet 0111 för att välja alternativ funktion till UART på pins PA2 och PA3.
    /*Nu är pin 2 och 3 redo för att skicka och ta emot UART-kommunikation*/

    //Konfiguration av UART.
    USART2->BRR = 0x0683; //Sätter en standard baud-rate till 9600bps genom att skriva hexavärdet 0x0683 till BRR-registret.
    USART2->CR1 = 0x000C; //Sätter transmit (tx) och receive (rx) till att arbeta i 8 bitars data (8 bitars data, 1 stop bit, ingen paritet).
    USART2->CR2 = 0x000; //Nollställer USART2:s CR2-register.
    USART2->CR3 = 0x000; //Nollställer USART2:s CR3-register.
    USART2->CR1 |= 0x2000; //Omställer bit 13 i CR1-registret till 1 för att aktivera UART.
}

//UART write-regler.
int USART2_write(int ch) { //Deklarerar skrivfunktionen (överföring av data till terminalen).
    
    //En loop för att skicka byte för byte...
    while(!(USART2->SR & 0x0080)){} //...sätter ett krav som kontrollerar att statusen på överföringsdataregistret (bit 7) är tomt och redo för att ta emot nästa karaktär(byte).
    
    USART2->DR = (ch & 0xFF); //Sätter överföringen av byten till dataregistret.
    
    return ch; //Returnera det överförda värdet. 
}

//UART read-regler.
int USART2_read(void) { //Deklarerar läsfunktionen (mottagning av information).
    while(!(USART2->SR & 0x0020)){} //Sätter ett krav som kontrollerar om det finns data att läsa/hämta.
    
    return USART2->DR; //Returnera läst datavärde.
}

//Interface för standard I/O i C.
//En omdiregering till att utge datan i terminalen. 
struct __FILE { int handle; }; //Strukturerar våra huvudsakliga överföringsströmmar.
FILE __stdin  = {0};
FILE __stdout = {1};
FILE __stderr = {2};

//Funktion för att läsa en byte från standardinmatningen. 
int fgetc(FILE *f) { //fgetc hämtar en byte från standardströmmen och behandlar även teckenreturer.
    int c;

    c = USART2_read();     

    if(c == '\r'){        
        USART2_write(c);    
        c = '\n';
    }

    USART2_write(c);       

    return c;
}

//Funktion för att skriva ut till terminalen.
int fputc(int c, FILE *f) { //fputc skriver en byte till standardströmmen.
    return USART2_write(c);
}

int n; //Deklarerar en byte för användning i testfunktionen.
char str[80]; //Sätter en begränsning av antal karaktärer i överföringen.

//Funktion som testar läs- och skrivfunktionen. Obs, används för närvarande inte i main men finns tillgänglig vid behov för att testa kommunikationen.
void test_setup(void) {
    printf("please enter a number: ");
    scanf("%d", &n);
    printf("the number entered is: %d\r\n", n);
    printf("please type a character string: ");
    gets(str);
    printf("the character string entered is: ");
    puts(str);
    printf("\r\n");
}
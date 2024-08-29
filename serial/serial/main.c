#include "serialConfig.h"

static FILE mysdtout = FDEV_SETUP_STREAM(USART0_Transmit_IO, NULL, _FDEV_SETUP_WRITE);

int main(void){
	USART0_Init(MYUBRR);   
	sei();
	stdout = &mysdtout;
	printf("Hello, word\r\n");
	while(1){
		for (size_t a = 0; a < 21; a++){
			printf("Contagem: %d\r\n", a);
			_delay_ms(1000);
		}
		//USART0_Transmit(USART0_Receive());
	}
}
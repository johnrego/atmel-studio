#include <avr/io.h>
#include <avr/interrupt.h>
#include "serialConfig.h"


/* Static Variables */
static unsigned char USART_RxBuf[USART_RX_BUFFER_SIZE];
static volatile unsigned char USART_RxHead;
static volatile unsigned char USART_RxTail;
static unsigned char USART_TxBuf[USART_TX_BUFFER_SIZE];
static volatile unsigned char USART_TxHead;
static volatile unsigned char USART_TxTail;

/* Initialize USART */
void USART0_Init(unsigned int baudrate)
{
 unsigned char x;

 /* Set the baud rate */
 UBRR0H = (unsigned char) (baudrate>>8);                  
 UBRR0L = (unsigned char) baudrate;
 
 /* Enable USART receiver and transmitter */
 UCSR0B = ((1 << RXCIE0) | (1 << RXEN0) | (1 << TXEN0)); 
 
 /* For devices in which UBRRH/UCSRC shares the same location
 * eg; ATmega16, URSEL should be written to 1 when writing UCSRC
 * 
 */
 /* Set frame format: 8 data 2stop */
 UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); //CHANGED ADDRESS and 1 stop bit
 
 /* Flush receive buffer */
 x = 0;        

 USART_RxTail = x;
 USART_RxHead = x;
 USART_TxTail = x;
 USART_TxHead = x;
}


ISR(USART0_RX_vect)  //CHANGE ISR
{
 unsigned char data;
 unsigned char tmphead;

 /* Read the received data */
 data = UDR0;                 
 /* Calculate buffer index */
 tmphead = (USART_RxHead + 1) & USART_RX_BUFFER_MASK;
 /* Store new index */
 USART_RxHead = tmphead;

 if (tmphead == USART_RxTail) {
  /* ERROR! Receive buffer overflow */
 }
 /* Store received data in buffer */
 USART_RxBuf[tmphead] = data; 
}


ISR(USART0_UDRE_vect)
{
 unsigned char tmptail;

 /* Check if all data is transmitted */
 if (USART_TxHead != USART_TxTail) {
  /* Calculate buffer index */
  tmptail = (USART_TxTail + 1) & USART_TX_BUFFER_MASK;
  /* Store new index */
  USART_TxTail = tmptail;      
  /* Start transmission */
  UDR0 = USART_TxBuf[tmptail];  
 } else {       
  /* Disable UDRE interrupt */
  UCSR0B &= ~(1<<UDRIE0);         
 }
}

unsigned char USART0_Receive(void)
{
 unsigned char tmptail;
 
 /* Wait for incoming data */
 while (USART_RxHead == USART_RxTail);
 /* Calculate buffer index */
 tmptail = (USART_RxTail + 1) & USART_RX_BUFFER_MASK;
 /* Store new index */
 USART_RxTail = tmptail;                
 /* Return data */
 return USART_RxBuf[tmptail];          
}

void USART0_Transmit(unsigned char data)
{
 unsigned char tmphead;
 
 /* Calculate buffer index */
 tmphead = (USART_TxHead + 1) & USART_TX_BUFFER_MASK;
 /* Wait for free space in buffer */
 while (tmphead == USART_TxTail);
 /* Store data in buffer */
 USART_TxBuf[tmphead] = data;
 /* Store new index */
 USART_TxHead = tmphead;               
 /* Enable UDRE interrupt */
 UCSR0B |= (1<<UDRIE0);                    
}

int USART0_Transmit_IO(char data, FILE *steam)
{
	unsigned char tmphead;
	
	/* Calculate buffer index */
	tmphead = (USART_TxHead + 1) & USART_TX_BUFFER_MASK;
	/* Wait for free space in buffer */
	while (tmphead == USART_TxTail);
	/* Store data in buffer */
	USART_TxBuf[tmphead] = data;
	/* Store new index */
	USART_TxHead = tmphead;
	/* Enable UDRE interrupt */
	UCSR0B |= (1<<UDRIE0);
}
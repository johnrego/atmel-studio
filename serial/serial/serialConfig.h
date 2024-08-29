#ifndef SERIALCONFIG_H_
#define SERIALCONFIG_H_
/*
#ifndef XC_HEADER_TEMPLATE_H
#define XC_HEADER_TEMPLATE_H

#include <xc.h> // include processor files - each processor file is guarded.

#define F_CPU 16000000
#define BAUD 9600
#define MYUBRR ((F_CPU/16/BAUD)-1)
*/
#define F_CPU 16000000 // Clock Speed
#define BAUD 9600
#define MYUBRR ((F_CPU / (BAUD * 16UL)) - 1)

/* USART Buffer Defines */
#define USART_RX_BUFFER_SIZE 128     /* 2,4,8,16,32,64,128 or 256 bytes */
#define USART_TX_BUFFER_SIZE 128     /* 2,4,8,16,32,64,128 or 256 bytes */
#define USART_RX_BUFFER_MASK (USART_RX_BUFFER_SIZE - 1)
#define USART_TX_BUFFER_MASK (USART_TX_BUFFER_SIZE - 1)

#include <stdio.h>
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>

/* Prototypes */
void USART0_Init(unsigned int baudrate);
unsigned char USART0_Receive(void);
void USART0_Transmit(unsigned char data);
int USART0_Transmit_IO(char data, FILE *steam);

#endif /* SERIALCONFIG_H_ */
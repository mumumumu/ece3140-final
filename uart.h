/******************************************************************************
	Cornell University
	Computer Systems Lab
	ECE 3140 UART header file
******************************************************************************/
#include "msp430x22x4.h"

#ifndef UART_H_
#define UART_H_

void uartTx(char c);
void uartTxString(char *p);
void uart_default_init(void);

#endif /*UART_H_*/

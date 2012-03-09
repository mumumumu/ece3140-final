#include "uart.h"
/******************************************************************************
	Cornell University
	Computer Systems Lab
	ECE 3140 UART common functions
******************************************************************************/

/*
 * Initializes the UART interface, it assumes that the clock is set to 8Mhz and it uses this data to set the correct baud rate
 */
void uart_default_init() {
  //UART init
  P3SEL |= 0x30;
  UCA0CTL1 |= UCSSEL_2;                     // CLK = ACLK
  UCA0BR0 = 0x41;                           // 32kHz/9600 = 3.41
  UCA0BR1 = 0x03;                           //
  UCA0MCTL = UCBRS1 + UCBRS0;               // Modulation UCBRSx = 3
  UCA0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
  IE2 |= UCA0RXIE;                          // Enable USCI_A0 (UART) RX interrupt
}

/*
 * Transmit a string through the UART interface
 * 
 */ 
void uartTx(char c) {
    while(!(IFG2 & UCA0TXIFG)); // wait for tx buf empty	
    UCA0TXBUF = c;
}
/*
 * Transmits a null-terminated string throught the UART interface
 */
void uartTxString(char *p) {
	while (*p) {
		if(*p == '\n') uartTx('\r');
		uartTx(*p++);
	}
}


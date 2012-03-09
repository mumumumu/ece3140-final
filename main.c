#include "msp430x22x4.h"
#include "stdlib.h"
#include "uart.h"

volatile unsigned int time = 0;
volatile unsigned int pause = 0;
volatile unsigned int note=0;
volatile unsigned int bpm=1;
volatile unsigned int duration=200;
//char *song = "L4C4,L4D4,L4E4,L4F4,L4G4,L4A4,L4B4!";
//char *song ="L16C4,L4E4,L4F4,L4G4,L4C5,L4B4,L8E4,L16A4,L16B4,L8A4,L8E4,L8D4,L4F4,L8F4,L8G4,L8A4,L8D5,L8C5,L8B4,L16A4,L16B4,L4C5,L8A4,L4G4,L4AS4,L8F4,L8C5,L8B4,L8C5,L8A4,L8F4,L8E4,L8F4,L8G4,L8C5,L8B4,L8C5,L8G4,L8E4,L8D4,L8E4,L8F4,L4C5,L8E5,L8D5,L8C5,L8B4,L8C5,L4D5,L8A4,L16D5,L16C5,L4B4,L8G4,L4F4,L8E4,L8D4,L8F4,L4C4,L8F4,L8G4,L8F4,L8E4,L8D4,L2E4,L8F4,L8E4,L8D4,L8C4,L8F4,L8E4,L8D4,L8F4,L8G4,L8D4,L8A4,L8F4,L8E4,L4G4,L8F4,L4E4,L16G4,L16A4,L16B4,L8C5,L8B4,L8A4,L8C5,L8B4,L16F4,L16G4,L4A4,L8G4,L4AS4,L8A4,L4G4,L8F4,L8E4,L4A4,L4G4,L4F4,L444,L4A4,L4G4,L4C5,L4B4,L4A4,L4D5,L4E5,L4C5,L2D5!"; //1D5,L4C5,L1B4!";//pokeman bike ride
char *song = "L4E4,L8B3,L8C4,L8D4,L16E4,L16D4,L8C4,L8B3,L4A3,L8A3,L8C4,L4E4,L8D4,L8C4,L4B3,L8C4,L4D4,L4E4,L4C4,L4A3,L2A3,L4D4,L4F4,L4A4,L8G4,L8F4,L4E4,L8C4,L4E4,L8D4,L8C4,L4B3,L8B3,L8C4,L4D4,L4E4,L4C4,L4A3,L4A3!";
char global_read;
int mode = 0; //0=keyboard mode, 1=playback mode

//8000 cycles = 1 ms
void delay(unsigned int ms){
  	volatile unsigned int i;
  	i = time;
  	while ((time-i) < (ms/1.3)) {
    	__no_operation();
  	}
}

void stop(){
	TACTL = TASSEL_2 + MC_3; 
 	CCR0 = 0;
}

void play(unsigned int hz){
	CCR0 = (8000000/hz)-1;
	CCTL1 = OUTMOD_7;
	CCR1 = (CCR0/2)-1; //50% duty cycle for max volume	
	TACTL = TASSEL_2 | MC_1;
}

char* playSong(char *p){
	switch(*p){
		case 'L':
			p++;
			switch(*p){
				case '1':
					duration=800;
					p++;
					switch(*p){
						case '6': duration=50; break;
					}
					break;
				case '2': duration=400; break;
				case '4': duration=200; break;
				case '8': duration=100; break;
			}
			break;
		case 'C':
			p++;
			switch(*p){
				case '1': note=33; break;
				case '2': note=65; break;
				case '3': note=131; break;
				case '4': note=262;  break;
				case '5': note=523;  break;
				case '6': note=1047; break;
				case '7': note=2093; break;
				case '8': note=4186; break;
				case 'S':
					p++;
					switch(*p){
						case '1': note=35; break;
						case '2': note=69; break;
						case '3': note=139; break;
						case '4': note=277;  break;
						case '5': note=554;  break;
						case '6': note=1109; break;
						case '7': note=2217; break;
						case '8': note=4435; break;
					}
					break;
				}
			break;
		case 'D':
			p++;
			switch(*p){
				case '1': note=37; break;
				case '2': note=73; break;
				case '3': note=147; break;
				case '4': note=294;  break;
				case '5': note=587;  break;
				case '6': note=1175; break;
				case '7': note=2349; break;
				case '8': note=4699; break;
				case 'S':
					p++;
					switch(*p){
						case '1': note=39; break;
						case '2': note=78; break;
						case '3': note=156; break;
						case '4': note=311;  break;
						case '5': note=622;  break;
						case '6': note=1245; break;
						case '7': note=2489; break;
						case '8': note=4978; break;
					}
					break;
			}
			break;
		case 'E':
			p++;
			switch(*p){
				case '1': note=41; break;
				case '2': note=82; break;
				case '3': note=165; break;
				case '4': note=330;  break;
				case '5': note=659;  break;
				case '6': note=1319; break;
				case '7': note=2637; break;
			}
			break;
		case 'F':
			p++;
			switch(*p){
				case '1': note=44; break;
				case '2': note=87; break;
				case '3': note=175; break;
				case '4': note=349;  break;
				case '5': note=698;  break;
				case '6': note=1397; break;
				case '7': note=2794; break;
				case 'S':
					p++;
					switch(*p){
						case '1': note=46; break;
						case '2': note=93; break;
						case '3': note=185; break;
						case '4': note=370;  break;
						case '5': note=740;  break;
						case '6': note=1480; break;
						case '7': note=2960; break;
					}
				break;
			}
			break;
		case 'G':
			p++;
			switch(*p){
				case '1': note=49; break;
				case '2': note=98; break;
				case '3': note=196; break;
				case '4': note=392;  break;
				case '5': note=784;  break;
				case '6': note=1568; break;
				case '7': note=3136; break;
				case 'S':
					p++;
					switch(*p){
						case '1': note=52; break;
						case '2': note=104; break;
						case '3': note=208; break;
						case '4': note=415;  break;
						case '5': note=831;  break;
						case '6': note=1661; break;
						case '7': note=3322; break;
					}
				break;
			}
			break;
		case 'A':
			p++;
			switch(*p){
				case '1': note=55; break;
				case '2': note=110; break;
				case '3': note=220; break;
				case '4': note=440;  break;
				case '5': note=880;  break;
				case '6': note=1760; break;
				case '7': note=3520; break;
				case 'S':
					p++;
					switch(*p){
						case '1': note=58; break;
						case '2': note=117; break;
						case '3': note=233; break;
						case '4': note=466;  break;
						case '5': note=932;  break;
						case '6': note=1865; break;
						case '7': note=3729; break;
					}
					break;
			}
			break;	
		case 'B':
			p++;
			switch(*p){
				case '0': note=31; break;
				case '1': note=62; break;
				case '2': note=123; break;
				case '3': note=247; break;
				case '4': note=494;  break;
				case '5': note=988;  break;
				case '6': note=1976; break;
				case '7': note=3951; break;
			}
			break;
		case '!': stop(); p=song; break;
	}
	p++;
	play(note);
	delay(duration);
	return p;
}	

void main(){
	char *p=song;
	WDTCTL = WDTPW+WDTHOLD; //stop WDT
	DCOCTL = CALDCO_8MHZ;  	//DCO control register
	BCSCTL1 = CALBC1_8MHZ;	//Basic clock system control

	uart_default_init();
	
	P1IE = 0x04; 	 //enable switch as an interrupt
  	P1IES = 0x04;    //enable interrupt on neg edge
  	P1REN = 0x04;	 //set resistor for P1.2
  	P1OUT = 0x04;	 //sets mux to DVCC (i.e. use the resistor)
	
	P1DIR |= 0x03;
	TBCCTL0=CCIE;
	TBCCR0 = 8000;		   
	TBCTL = TBSSEL_2 | MC_1; 
	P2DIR |= 0x08; 	//set p2.4 to output
	P2SEL |= 0x08;	
	
	__enable_interrupt();
	while(1){
		switch(mode){
			case 0:
				P1OUT=0x05;
			  	switch(global_read){
			  		case 'z': note = 131; break;	//C3
					case 'x': note = 147; break;	//D3
					case 'c': note = 165; break;	//E3
					case 'v': note = 175; break;	//F3
					case 'b': note = 196; break;	//G3
					case 'n': note = 220; break;	//A3
					case 'm': note = 247; break;	//B3
					case 'a': note = 262; break;	//C4
					case 's': note = 294; break;	//D4
					case 'd': note = 330; break;	//E4
					case 'f': note = 349; break;	//F4
					case 'g': note = 392; break;	//G4
					case 'h': note = 440; break;	//A4
					case 'j': note = 494; break;	//B4
					case 'q': note = 523; break;	//C5
					case 'w': note = 587; break;	//D5
					case 'e': note = 659; break;	//E5
					case 'r': note = 698; break;	//F5
					case 't': note = 784; break;	//G5
					case 'y': note = 880; break;	//A5
					case 'u': note = 988; break;	//B5
					case '.': note = 0; break;		//END NOTE
				}
				if(note){
					play(note);
					delay(200);
					stop();
					global_read='.';
				}
				break;
			case 1:
				P1OUT=0x06;
				p=playSong(p);
				break;
		}
	}
}

#pragma vector=TIMERB0_VECTOR
__interrupt void timerB_handler (void) {
  	time++;
}

#pragma vector=PORT1_VECTOR
__interrupt void port1_handler (void) {
	unsigned int intrCounter = 0;
  	for (intrCounter=1; intrCounter<=600; intrCounter++){
	    if ((P1IN & 0x04) != 0){ 	//checks if button is not pressed
	        intrCounter = 0; 		//reset the counter back to 0
		}
	    if (intrCounter == 600){	//600 cycles is equivalent to approximately 3ms for the debouncing
	       mode ^= 0x01; 			//toggle between keyboard and song mode
	       global_read = '!';			//turn off whatever note was plaing
	    }
  	}
	P1IFG = 0x00;  			//reset flags
}

#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCI0RX_ISR(void) {
	char n[] = "\n";
	global_read = UCA0RXBUF;
	switch(global_read){
		case 'z': uartTx('C'); break;	//C3
		case 'x': uartTx('D'); break;	//D3
		case 'c': uartTx('E'); break;	//E3
		case 'v': uartTx('F'); break;	//F3
		case 'b': uartTx('G'); break;	//G3
		case 'n': uartTx('A'); break;	//A3
		case 'm': uartTx('B'); break;	//B3
		case 'a': uartTx('C'); break;	//C4
		case 's': uartTx('D'); break;	//D4
		case 'd': uartTx('E'); break;	//E4
		case 'f': uartTx('F'); break;	//F4
		case 'g': uartTx('G'); break;	//G4
		case 'h': uartTx('A'); break;	//A4
		case 'j': uartTx('B'); break;	//B4
		case 'q': uartTx('C'); break;	//C5
		case 'w': uartTx('D'); break;	//D5
		case 'e': uartTx('E'); break;	//E5
		case 'r': uartTx('F'); break;	//F5
		case 't': uartTx('G'); break;	//G5
		case 'y': uartTx('A'); break;	//A5
		case 'u': uartTx('B'); break;	//B5
		case '.': uartTx('!'); break;	
	}
	uartTxString(n);
}



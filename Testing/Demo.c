#include <stdio.h>

int demo();
unsigned char mkeyscan();

int main()
{
	demo();
	return 0;	
}

int demo()
{
	
	unsigned char *adctl, *adr1, *porta, *ddra; 
	unsigned char offset, exit = '\0'; 
	unsigned int delay, i=0;
	
	/* Assign pointers and values to ports and direction registers */
	adctl=(unsigned char*)0x30;
	adr1=(unsigned char*)0x31;
	porta=(unsigned char *)0x00;
	ddra=(unsigned char *)0x01;
	*adctl=0x20;
	*ddra=0xff;
	offset = 0xff;
	
	printf("Press any key to stop demo.\n\r");
	
	/* Run until key press */
	while(exit == '\0')
	{
		exit = mkeyscan();
		while(((*adctl)&0x80)==0x00);
		delay = *adr1 + offset;
		
		for(i = 0; i < delay; i++);
		/*printf("Data from channel E0 is %02x, delay = %04x\n\r", *adr1, delay);*/ /*Debug line*/
		*porta = 0x01; /*Write value to port A*/

		for(i = 0; i < delay; i++);
		*porta = 0x03;
		
		for(i = 0; i < delay; i++);
		*porta = 0x02;
		
		for(i = 0; i < delay; i++);
		*porta = 0x06;
		
		for(i = 0; i < delay; i++);
		*porta = 0x04;

		for(i = 0; i < delay; i++);
		*porta = 0x0c;
		
		for(i = 0; i < delay; i++);
		*porta = 0x08;

		for(i = 0; i < delay; i++);
		*porta = 0x09;
	}
	*porta = 0x00; /*Clear data on quit*/
	return(1);
}

unsigned char mkeyscan()
{
	unsigned char *scsr, *scdr, data;
	/* Note no config needed for baud rate since already defined in monitor program*/
	scsr = (unsigned char *)0x2e;
	scdr = (unsigned char *)0x2f;
	data = '\0';
	/* if key has been pressed read key code else return NULL */
	if (((*scsr) & 0x20) != 0x0)
	{
		data = *scdr;
	}
	return(data);
}

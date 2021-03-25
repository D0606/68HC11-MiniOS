#include <stdio.h>

int demo();

int main()
{
	demo();
	return 0;	
}

int demo()
{
	unsigned char *adctl, *adr1, data, *porta,*ddra, offset;
	unsigned int delay, i=0;
	adctl=(unsigned char*)0x30;
	adr1=(unsigned char*)0x31;
	porta=(unsigned char *)0x00;
	ddra=(unsigned char *)0x01;
	*adctl=0x20;
	*ddra=0xff;
	offset = 0x0ff;

	for(;;)
	{
		while(((*adctl)&0x80)==0x00);
		delay = *adr1 + offset;
		for(i = 0; i < delay; i++);
		/*printf("Data from channel E0 is %02x, delay = %04x\n\r", *adr1, delay);*/ /*Debug line*/
		*porta = 0x01;

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

	return 1;
}

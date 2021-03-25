#include <stdio.h>
void main(void)
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
		delay = *adr1 * offset;
		for(i = 0; i < delay; i++);
		printf("Data from channel E0 is %02x, delay = %04x\n\r", *adr1, delay);
		*porta = 0x01;

		while(((*adctl)&0x80)==0x00);
		delay = *adr1 * offset;
		for(i = 0; i < delay; i++);
		printf("Data from channel E0 is %02x, delay = %04x\n\r", *adr1, delay);
		*porta = 0x03;
		
		while(((*adctl)&0x80)==0x00);
		delay = *adr1 * offset;		
		for(i = 0; i < delay; i++);
		printf("Data from channel E0 is %02x, delay = %04x\n\r", *adr1, delay);
		*porta = 0x02;
		
		while(((*adctl)&0x80)==0x00);
		delay = *adr1 * offset;
		for(i = 0; i < delay; i++);
		printf("Data from channel E0 is %02x, delay = %04x\n\r", *adr1, delay);
		*porta = 0x06;
		
		while(((*adctl)&0x80)==0x00);
		delay = *adr1 * offset;
		for(i = 0; i < delay; i++);
		printf("Data from channel E0 is %02x, delay = %04x\n\r", *adr1, delay);
		*porta = 0x04;
		
		while(((*adctl)&0x80)==0x00);
		delay = *adr1 * offset;
		for(i = 0; i < delay; i++);
		printf("Data from channel E0 is %02x, delay = %04x\n\r", *adr1, delay);
		*porta = 0x0c;
		
		while(((*adctl)&0x80)==0x00);
		delay = *adr1 * offset;
		for(i = 0; i < delay; i++);
		printf("Data from channel E0 is %02x, delay = %04x\n\r", *adr1, delay);
		*porta = 0x08;

		while(((*adctl)&0x80)==0x00);
		delay = *adr1 * offset;
		for(i = 0; i < delay; i++);
		printf("Data from channel E0 is %02x, delay = %04x\n\r", *adr1, delay);
		*porta = 0x09;
	}
}

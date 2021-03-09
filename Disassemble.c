#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

typedef struct opAssembler
{
	char instruction[8];
	int bytes;
} opAssembler;

int main()
{
	
	struct opAssembler command[255];
	unsigned char address[5];
	unsigned char data, data1;
	char temp1[10],temp2[10];
	unsigned int *addValue;

	/*Initialse data*/	
	strcpy(command[0x89].instruction,"ADCA #$");
	command[0x89].bytes = 2;
	
	printf("Please enter an address: ");
	gets(address); /*Obtain user entered address - 3000 and after seems clear*/
	sscanf(address, "%x", &addValue); /*assign input to addvalue*/
	printf("\n\rAddress obtained: %x", addValue);
	
	/*get opcode*/
	data = *addValue;
	printf("\n\rData obtained: %x,", data);
	
	/*look up string*/
	strcpy(temp1, command[data].instruction);
	
	/*look up number of bytes next*/
	if (command[data].bytes == 2)
	{
		data1 = *(addValue+1);
		sprintf(temp2, "%x", data1);
	}
	strcat(temp1,temp2);
	printf("%x %02x %02x %s \n\r",addValue, *addValue, *(addValue+1), temp1);
}









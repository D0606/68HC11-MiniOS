#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

int dm(unsigned int);

int main()
{
	unsigned int add = 0x7000, i;
	unsigned char /*strAdd[10],*/ *asciiPtr;
	
/*	printf("Enter address: ");
	gets(strAdd);
	sscanf(strAdd, "%04x", &add);
	printf("Address: %04x", add);*/
	
	asciiPtr = (unsigned char *)add;
	
	for(i = 0; i < 256; i++)
	{
		*asciiPtr = i;
		asciiPtr++;
	}

	dm(add);
	dm(add + 0x00a0);
	
	return 0;
}

int dm(unsigned int addTemp)
{

	unsigned char *address;
	unsigned char i = 0, j = 0, data;
	char ascii[2], fillAscii[2] = {'.','\0'}, strAscii[15];

	/* Assign pointer to address*/
	address = (unsigned char *)addTemp;

	/*Print header*/
	printf("\n\rAddress\t\tHex Data\t\t  ASCII\n\n\r");

	/* Process through memory and display block */
	for(j = 0; j < 16; j++)
	{
		/*Clear the strings*/
		strAscii[0] = '\0';
		ascii[0] = '\0';
		
		printf(" %04x\t", address);

		for(i = 0; i < 10; i++)
		{
			data = *(address+i);
			printf("%02x ", data);
			/*Not recognised hex, so output '.' */
			if (data <= 0x20 || data >= 0x7F)
			{
				strcat(strAscii, fillAscii);
			}
			/* Output hex char */
			else
			{
				sprintf(ascii, "%c", data);
				strcat(strAscii, ascii);
			}
		}
		printf("\t%s\n\r", strAscii);
		address+= 10; /* Increment to next set on line */
	}
	return(1);	
}

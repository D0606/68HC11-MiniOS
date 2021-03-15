#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

int main()
{
	
	unsigned char getAddress[5];
	unsigned char i = 0, j = 0, data;
	char ascii[2], fillAscii[2] = {'.','\0'}, strAscii[15];
	unsigned char *address;
	unsigned int addTemp;

	/*Get the address parameters*/
	printf("Please enter a start address: ");
	gets(getAddress); /*Obtain user entered address*/
	printf("\n\rString obtained: %s\n\r", getAddress);
	sscanf(getAddress, "%x", &addTemp); /*assign input to addvalue*/
	printf("\n\rAddress obtained: %x\n\r", addTemp);
	address = (unsigned char *)addTemp;
	
	/*Print header*/
	printf("\n\rAddress\t\tHex Data\t\t  ASCII\n\n\r");
	
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
			if (data <= 0x20 || data >= 0x7F)
			{
				strcat(strAscii, fillAscii);
			}
			else
			{
				sprintf(ascii, "%c", data);
				strcat(strAscii, ascii);
			}
		}
		printf("\t%s\n\r", strAscii);
		address+= 10;
	}		
}

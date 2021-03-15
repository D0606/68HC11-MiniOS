#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

int main()
{
	
	unsigned char getAddress[5];
	unsigned char data, isBreak;
	char newData[3];
	unsigned char *address;
	unsigned int addTemp, data1;

	/*Get the address parameters*/
	printf("Please enter an address to modify: ");
	gets(getAddress); /*Obtain user entered address*/
	printf("\n\rString obtained: %s", getAddress);
	sscanf(getAddress, "%04x", &addTemp); /*assign input to addvalue*/
	printf("\n\rAddress obtained: %x\n\r\n", addTemp);
	address = (unsigned char *)addTemp;
	
	printf("Please enter your new values. Use '.' to exit.\n\r");
	printf("Address\tHex Data\n\n\r");
	while(1){
		/*Acquire data and print with address*/
		data = *address;
		printf("%04x:\t%02x <- ", address, data);
		
		/*Acquire new value and check for break*/
		gets(newData);
		sscanf(newData, "%c", &isBreak);
		if (isBreak == '.')
		{
			break;
		}
		else
		{
			/*Write new value to address and increment until break*/
			sscanf(newData, "%02x", &data1);
			*address = data1;
		}
		address+= 1;
	}
}

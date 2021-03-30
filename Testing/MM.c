#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdio.h>

int mm();

int main()
{
	
	unsigned int add;
	unsigned char strAdd[10];

	printf("Enter address: ");
	gets(strAdd);
	sscanf(strAdd, "%04x", &add);
	mm(add);
	return 0;
}

int mm(unsigned int addTemp)
{
	
	unsigned char *address;
	unsigned char data, isBreak;
	char newData[10];
	unsigned int data1;
	
	/* Assign pointer to incoming parameter value */
	address = (unsigned char *)addTemp;
	
	printf("Please enter your new values. Use '.' to exit.\n\r");
	printf("Address\tHex Data\n\n\r");

	/* Continue until quit */
	while(1) {
		
		/*Acquire data and print with address*/
		data = *address;
		printf("%04x:\t%02x <- ", address, data);
		
		/*Acquire new value and check for break*/
		newData[0] = '\n'; /*Set default input to return line skip*/
		newData[1] = '\0'; /*Suppose null unless overwritten*/
		newData[2] = '\0'; /*Re-write null in case of overwrite later*/
		gets(newData);
		sscanf(newData, "%c", &isBreak);
		
		/* Check for quit */
		if (isBreak == '.')
		{
			break;
		}
		/* Skip line */
		if (isBreak == '\n')
		{
			address+= 1;
		}
		else
		{
			/* Check if only one character input and validate */
			if (newData[1] == '\0')
			{
				/* If not valid or is whitespace */
				if (isxdigit(newData[0]) == 0 || newData[0] == ' ')
				{
					printf("Please enter a valid 8 bit hexadecimal value.\n\r");
				}
				/*Accept, format and increment pointer*/
				else
				{
					sscanf(newData, "%02x", &data1);
					*address = data1;
					address+= 1;
				}
			}
			/*Two digits or more entered, validate and process */
			else
			{
				/* If not valid, whitespace or overwritten the null check */
				if (isxdigit(newData[0]) == 0 || isxdigit(newData[1]) == 0 || newData[0] == ' ' || newData[1] == ' ' || newData[2] != '\0')
				{
					printf("Please enter a correct 8 bit hexadecimal value.\n\r");
				}
				else
				{
					/*Write new value to address and increment until break*/
					sscanf(newData, "%02x", &data1);
					*address = data1;
					address+= 1;
				}
			}
		}
	}
	return(1);
}

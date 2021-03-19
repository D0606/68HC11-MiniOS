#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

/**********************************************************
Author: Daniel Truman
Company: Staffordshire University
Date: 19/03/21
Version:		0.1
Purpose:		Error checks instruction requests and ranges to ensure that values will be acceptably formatted and within correct ranges
Modifications:	0.1 - Switch case implementation for five instruction types plus default for unit testing with appropriate debug outputs
Functions:		None
Variables:		unsigned char testInput[20] - Holds user entered test string
				unsigned char code - Holds the code value extracted from the testInput string to select the switch case
				unsigned char errorCode - Holds the return value from the switch case output which will be return at the end of the function
				unsigned int startRange, endRange - Holds the integer values extracted from the testInput string in hex to select address range values to test
**********************************************************/
int main()
{
	unsigned char code=5, errorCode=0;
	unsigned char testInput[20];
	unsigned int startRange=0, endRange=0;
	
	testInput[0] = '\0';

	printf("Codes:\n\r------\n\r0: LF\t- No Params\n\r1: DM\t- 1 Param\n\r2: MM\t- 1 Param\n\r3: DI\t- 2 Params\n\r4: Demo\t- No Prarams\n\n\r");
	printf("Enter a test code and desired values <x y z>: ");
	gets(testInput);
	sscanf(testInput, "%u %04x %04x", &code, &startRange, &endRange);
	printf("Code: %u, Start: %04x, End: %04x\n\r", code, startRange, endRange);
	
	switch(code)
		{
			case 0:
				printf("Load File error checking...No accepted extra values.\n\r");
				if(startRange != 0 || endRange != 0)
				{
					errorCode = 1;
					printf("This instruction requires no parameters, please follow syntax example.\n\r");
				}
				else
				{
					errorCode = 0;
				}
				break;
			case 1:
				printf("Display Memory error checking...Accepts start range only.\n\n");
				/*Check for clear second parameter*/
				if(endRange != 0)
				{
					errorCode = 1;
					printf("This instruction requires only one parameter, please follow syntax example.\n\r");
				}
				/*Check for overall acceptable range*/
				if(startRange < 0x0400 || startRange > 0x7DFF)
				{
					errorCode = 1;
					printf("This instruction only accepts address values between 0400 and 7DFF.\n\r");
				}
				else
				{
					errorCode = 0;
				}
				break;
			case 2:
				printf("Modify Memory error checking...Accepts start range only.\n\r");
				/*Check for clear second parameter*/
				if(endRange != 0)
				{
					errorCode = 1;
					printf("This instruction requires only one parameter, please follow syntax example.\n\r");
				}
				/*Check for overall acceptable range*/
				if(startRange < 0x0400 || startRange > 0x7DFF)
				{
					errorCode = 1;
					printf("This instruction only accepts address values between 0400 and 7DFF.\n\r");
				}
				else
				{
					errorCode = 0;
				}
				break;
			case 3:
				printf("Disassemble Memory error checking...Accepts start range and end range.\n\r");
				/*Check for overlap on range*/
				if(endRange <= startRange || startRange >= endRange)
				{
					errorCode = 1;
					printf("End range cannot be equal to or lower than start range.\n\r");
					break;
				}
				/*Check for overall acceptable start range*/
				if(startRange < 0x0400 || startRange >= 0x7DFF)
				{
					errorCode = 1;
					printf("This instruction only accepts start address ranges between 0400 and 7DFE.\n\r");
					break;
				}
				/*Check for overall acceptable end range*/
				if(endRange <= 0x400 || endRange > 0x7DFF)
				{
					errorCode = 1;
					printf("This instruction only accepts end address ranges between 0401 and 7DFF.\n\r");
					break;
				}
				else
				{
					errorCode = 0;
				}
				break;
			case 4:
				printf("Demo error checking...No accepted extra values.\n\r");
				if(startRange != 0 || endRange != 0)
				{
					errorCode = 1;
					printf("This instruction requires no parameters, please follow syntax example.\n\r");
				}
				else
				{
					errorCode = 0;
				}
				break;
			default:
				printf("An error has occured, no recognised command was selected.\n\r");
				errorCode = 1;
				break;
		}
		printf("Error: %u.", errorCode);
		return(errorCode);
}

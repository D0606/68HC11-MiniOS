#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int ec(unsigned int code, unsigned int valOne, unsigned int valTwo);

int main()
{
	
	unsigned int add1, add2, mode;
	unsigned char strAdd[20];

	printf("Enter code and addresses: ");
	gets(strAdd);
	sscanf(strAdd, "%d %04x %04x", &mode, &add1, &add2);
	printf("You entered mode: %d, Start: %04x, End: %04x\n\r", mode, add1, add2);
	ec(mode, add1, add2);
	return 0;
}

/**********************************************************
Author: Daniel Truman
Company: Staffordshire University
Date: 19/03/21
Version:		0.2
Purpose:		Error checks instruction requests and ranges to ensure that values will be acceptably formatted and within correct ranges
Modifications:	0.1 - Switch case implementation for five instruction types plus default for unit testing with appropriate debug outputs
				0.2 - Added more boolean checks and fixed checking error in existing, reordered some checks and added breaks to each check
Functions:		None
Variables:		unsigned char testInput[20] - Holds user entered test string
				unsigned char code - Holds the code value extracted from the testInput string to select the switch case
				unsigned char errorCode - Holds the return value from the switch case output which will be return at the end of the function
				unsigned int valOne, valTwo - Holds the integer values extracted from the testInput string in hex to select address range values to test
**********************************************************/
int ec(unsigned int code, unsigned int valOne, unsigned int valTwo)
{
	unsigned char errorCode = 0;

	/*printf("Code: %d, Start: %04x, End: %04x\n\r", code, valOne, valTwo);*/ /* Debug line */
	
	/* Match incoming value and validate for request */
	switch(code)
	{
		case 0:
			/*printf("Load File error checking...No accepted extra values.\n\r");*/ /* Debug line */
			/* Check for 0 values on both parameters */
			if(valOne != 0 || valTwo != 0)
			{
				errorCode = 1;
				printf("This instruction requires no parameters, please follow syntax example.\n\r");
			}
			else
			{
				errorCode = 0; /* Return as valid */
			}
			break;
		case 1:
			/*printf("Display Memory error checking...Accepts start range only.\n\n");*/ /* Debug line */
			/* Check for 0 values on both parameters */
			if(valOne == 0)
			{
				errorCode = 1;
				printf("This instruction requires a valid hexadecimal parameter, please follow syntax example.\n\r");
				break;
			}
			/* Check for 0 value on second parameter */
			if(valTwo != 0)
			{
				errorCode = 1;
				printf("This instruction requires only one parameter, please follow syntax example.\n\r");
				break;
			}
			/* Check for overall acceptable range */
			if(valOne < 0x0400 || valOne > 0x7DFF)
			{
				errorCode = 1;
				printf("This instruction only accepts address values between 0400 and 7DFF.\n\r");
				break;
			}
			else
			{
				errorCode = 0;
			}
			break;
		case 2:
			/*printf("Modify Memory error checking...Accepts start range only.\n\r");*/ /* Debug line */
			/* Check for 0 value */
			if(valOne == 0)
			{
				errorCode = 1;
				printf("This instruction requires a valid hexadecimal parameter, please follow syntax example.\n\r");
				break;
			}
			/* Check for clear second parameter */
			if(valTwo != 0)
			{
				errorCode = 1;
				printf("This instruction requires only one parameter, please follow syntax example.\n\r");
				break;
			}
			/* Check for overall acceptable range */
			if(valOne < 0x0400 || valOne > 0x7DFF)
			{
				errorCode = 1;
				printf("This instruction only accepts address values between 0400 and 7DFF.\n\r");
				break;
			}
			else
			{
				errorCode = 0;
			}
			break;
		case 3:
			/* Check for 0 values */
			/*printf("Disassemble Memory error checking...Accepts start range and end range.\n\r");*/ /* Debug line */
			if(valOne == 0 || valTwo == 0)
			{
				errorCode = 1;
				printf("This instruction requires two parameters, please follow syntax example.\n\r");
				break;
			}
			/* Check for overlap on range */
			if(valTwo <= valOne || valOne >= valTwo)
			{
				errorCode = 1;
				printf("End range cannot be equal to or lower than start range.\n\r");
				break;
			}
			/* Check for overall acceptable start range */
			if(valOne < 0x0400 || valOne >= 0x7DFF)
			{
				errorCode = 1;
				printf("This instruction only accepts start address ranges between 0400 and 7DFE.\n\r");
				break;
			}
			/* Check for overall acceptable end range */
			if(valTwo <= 0x400 || valTwo > 0x7DFF)
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
			/*printf("Demo error checking...No accepted extra values.\n\r");*/ /* Debug line */
			/* Check for 0 values on both parameters */
			if(valOne != 0 || valTwo != 0)
			{
				errorCode = 1;
				printf("This instruction requires no parameters, please follow syntax example.\n\r");
			}
			else
			{
				errorCode = 0;
			}
			break;
			/* Handle other possible cases */
		default:
			printf("An error has occured, no recognised command was selected.\n\r");
			errorCode = 1;
			break;
	}
	/*printf("\n\rerrorCheck function return: %u.\n\r", errorCode);*/ /* Debug line */
	return(errorCode);
}

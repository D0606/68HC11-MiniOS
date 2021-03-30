#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/************ Function Prototypes ************/
int loadFile();
int displayMem(unsigned int);
int modifyMem(unsigned int);
int disassembleMem(unsigned int, unsigned int);
int demo();
int errorCheck(unsigned int, unsigned int, unsigned int);
unsigned char mkeyscan();

/************ Structure Definition ************/
typedef struct opAssembler
{
	char instruction[10]; /* Contains the assembly instruction */
	char bytes; /* Length of data */
	char type; /* Standard or extended code type */
	char isValid[6]; /* Validation string to check against to ensure simple data won't validate the entry */
} opAssembler;

/**********************************************************
Author:			Daniel Truman
Company:		Staffordshire University
Date:			03/03/21
Version:		1.0
Purpose:		Displays available functions, allows input and string matches input to an error checking function.
				Uses return value to call specified matched function if valid.
Modifications:	0.1 - Initial menu design with rudimentary function call stubs
				0.2 - Implemented string matching with toupper and confirmed matches
				0.3 - Swictch case implemented to set flags and call function stub printf outputs
				0.4 - Changed to interface with separate error checking function to validate user inputs; now uses return value from function for validation and function calls
				0.5 - Changed loops to allow for returns from functions to inform actions
				1.0 - Tested and implemented in programme, debug lines commented out			
Functions:		loadFile()
				displayMem()
				modifyMem()
				disassembleMem()
				demo()
				errorCheck()
Variables:		unsigned char	- strChoice[20]	- Holds user input for processing
								- cmdChoice[5]	- Holds the first portion of user input, used for string matching to functions
								- launchCode	- Holds a value for selection on switch case, derived from the cmdChoice[] string match
								- invalidChoice - Holds a value that is used to secure a loop until a valid command is given
								- matched		- Holds a value that indicates that a command has string matched for validation purposes
				unsigned int	- startRange	- Holds a starting memory address value in hexadecimal
								- endRange		- Holds an ending memory address value in hexadecimal to determine range
**********************************************************/
int main()
{
	unsigned char strChoice[20], cmdChoice[5];
	unsigned char launchCode, invalidChoice = 1, i = 0, matched = 0;
	unsigned int startRange = 0, endRange = 0;

	for(;;)
	{

		while(invalidChoice == 1)
		{
			/*Clear variables*/
			startRange = 0;
			endRange = 0;
			matched = 0;
			cmdChoice[0] = '\0';
			strChoice[0] = '\0';

			/*Print out main menu and display choices*/
			printf("\n\n\r*#*#*#*#*#*#*#*#*#*#*#* 04908117 - Assignment Main Menu *#*#*#*#*#*#*#*#*#*#*#*\n\n\r");
			printf("Please select from the following options:\n\n\r");
			printf("LF\tLoad File. Syntax: LF\n\r");
			printf("DM\tDisplay Memory. Syntax: DM <Start Range> e.g.DM 400\n\r");
			printf("MM\tModify Memory. Syntax: MM <Start Range> e.g.MM 400\n\r");
			printf("DI\tDisassemble Memory. Syntax: DI <Start Range> <End Range> e.g.DI 400 800\n\r");
			printf("DEMO\tLaunch the onboard demo. Syntax: DEMO\n\r");
			printf("\n\r*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*\n\n\r");
			printf("Please enter your command: ");
			gets(strChoice); /*Receive user input*/
			/*printf("\n\rString is: %s\n\r", strChoice);*/ /*Debug Line*/
			sscanf(strChoice, "%s %04x %04x", &cmdChoice, &startRange, &endRange); /*Assign inputs to variables to check for validity*/
			/*printf("Command: %s, length: %d, Start Range:  %04x, End Range: %04x\n\r", cmdChoice, strlen(cmdChoice), startRange, endRange);*/ /*Debug line*/

			/*Process command string for accurate matching*/
			for(i = 0; i < strlen(cmdChoice); i++)
			{
				cmdChoice[i] = toupper(cmdChoice[i]);
			}
			/*printf("Command entered was: %s\n\r", cmdChoice);*/ /*Debug line*/

			/*Check if command was valid and process*/
			if(strcmp(cmdChoice, "LF") == 0)
			{
				matched = 1;
				invalidChoice = errorCheck(0, startRange, endRange);
				launchCode = 0;
			}
			if(strcmp(cmdChoice, "DM") == 0)
			{
				matched = 1;
				invalidChoice = errorCheck(1, startRange, endRange);
				launchCode = 1;
			}
			if(strcmp(cmdChoice, "MM") == 0)
			{
				matched = 1;
				invalidChoice = errorCheck(2, startRange, endRange);
				launchCode = 2;
			}
			if(strcmp(cmdChoice, "DI") == 0)
			{
				matched = 1;
				invalidChoice = errorCheck(3, startRange, endRange);
				launchCode = 3;
			}
			if(strcmp(cmdChoice, "DEMO") == 0)
			{
				matched = 1;
				invalidChoice = errorCheck(4, startRange, endRange);
				launchCode = 4;
			}
			if(matched != 1)
			{
				invalidChoice = errorCheck(5, startRange, endRange);
			}

			/*If validated, call specified function with validated and applicable ranges*/
			if(invalidChoice == 0)
			{
				switch(launchCode)
				{
					case 0:
						invalidChoice = loadFile();
						break;
					case 1:
						invalidChoice = displayMem(startRange);
						break;
					case 2:
						invalidChoice = modifyMem(startRange);
						break;
					case 3:
						invalidChoice = disassembleMem(startRange, endRange);
						break;
					case 4:
						invalidChoice = demo();
						break;
					default:
						printf("An error has occured -- Error: %u.\n\r", launchCode); /*Debug line, should not be seen unless something has gone wrong.*/
						invalidChoice = 1;
						break;
				}
			}
		}
	}
	printf("Exceptional error occured! Codes: %d %d %d\n\r", matched, invalidChoice, launchCode); /*Debug line, should not be seen unless something has gone wrong.*/
	return(0);
}

/**********************************************************
Author:			Daniel Truman
Company:		Staffordshire University
Date:			19/03/21
Version:		1.0
Purpose:		Uploads S19 programmes in text file formats and writes to memory one byte at a time, validates data
Modifications:	0.1 - Initial version
				0.2 - Replaced arrays with direct memory accessing
				0.3 - Added multiple line scanning
				0.4 - Added checksum validation
				0.5 - Changed how checksum is done on retrieved addressed
				0.6 - Printf changes to end of file read and error announcement with failed checksum
				1.0 - Tested and implemented in programme, debug lines commented out
Functions:		None
Variables:		unsigned char	- *scsr			- Pointer to the address for the Serial Communication Status Register
								- *scdr			- Pointer to the address for the Serial Communications Data Register
								- fileData		- Holds a hex value for a nibble or calculated byte of read data
								- fileData1 	- Holds a hex value for a nibble of read data, used to calculate final byte held in fileData
								- lineLength	- Holds a hex value for a nibble or calculated byte of read file length data
								- lineLength1	- Holds a hex value for a nibble of read file length data, used to calculate final byte held in lineLength
								- address1		- Holds a hex value for a nibble of read address data, used to calculate final bytes held in address
								- addChk		- Holds a hex value for the checksum of the address, added to myChkSum when calculated
								- myChkSum		- Holds a hex value for the checksum calculation
								- fileChkSum	- Holds a hex value for a nibble or calculated byte of read checksum data
								- fileChkSum1	- Holds a hex value for a nibble of checksum data, used to calculate final byte held in fileChkSum
								- data			- Holds a value retrived from Serial Communications Data Register
								- status		- Holds a value used as a flag for data loop to indicate more lines awaiting read
								- charCount		- Holds a value used to interate data gathering over the length of a line
								- flag			- Holds a value used to activate the data gathering loop
								- addFlag		- Holds a value used to capture a one-time address held in addLog on first read line only
								- chkFail		- Holds a value used as a flag to activate a condition upon checksum failing
								- failLine		- Holds a value showing the read line in which the checksum failed
								- lastLine		- Holds a value used as a flag indicating the last line of a file, skipping the data gathering loop
								- lineCount		- Holds a value indicating the number of lines read in
				unsigned int	- address		- Holds a hex value for nibbles or calculated 2 bytes of read address data
								- addLog		- Holds a hex value for a complete calculated address value from the first read line
**********************************************************/
int loadFile()
{
	
	unsigned char *scsr, *scdr, *origin;
	unsigned char fileData = 0x00, fileData1 = 0x00, lineLength = 0x00, lineLength1 = 0x00,
					address1 = 0x00, addChk = 0x00, myChkSum = 0x00, fileChkSum = 0x00, fileChkSum1 = 0x00,
					data, status = 0, charCount = 0, flag = 0, addFlag = 0, chkFail = 0, failLine = 0, lastLine = 0, lineCount = 0;
	unsigned int address = 0x0000, addLog;
	
	/* Assign pointers to serial data and comms registers. Baud rate defined in monitor programme */
	scsr = (unsigned char *)0x2e;
	scdr = (unsigned char *)0x2f;
	
	printf("Select a text file to upload.\n\r");
	do
	{
		/* Check for valid S19, first character and following character */
		while(((*scsr) & 0x20) == 0x0);
		data = *scdr;
		
		if (data == 'S')
		{
			flag = 0; /* reset flag */
			while(((*scsr) & 0x20) == 0x0);
			data = *scdr;
			if (data == '1')
			{
				charCount = 0; /*Reset char count*/
				myChkSum = 0x00; /*Clear checksum*/
				putchar('/');/* Output for each line */
				flag = 1;  /* Mark ready for reading line */
			}
			if ( data == '9') 
			{
				status = 1; /* Last line, stop operation */
				lastLine = 1;
				charCount = 0;
				myChkSum = 0x00;
				putchar('/');
				flag = 1;
			}
		}
		
		if ( flag == 1)	
		{
			/* Get first line length nibble and bitshift*/
			while(((*scsr) & 0x20) == 0x00);
			lineLength = *scdr;
			if(lineLength >= '0' && lineLength <= '9') /* Check for numeric and offset */
			{
				lineLength = lineLength - 0x30;
			}
			if(lineLength >= 'A' && lineLength <= 'F') /* Check for alpha and offset */
			{
				lineLength = lineLength - 0x37;
			}
			lineLength = lineLength << 4;
			
			/*Get second length nibble and bitshift*/
			while(((*scsr) & 0x20) == 0x00);
			lineLength1 = *scdr;
			if(lineLength1 >= '0' && lineLength1 <= '9')
			{
				lineLength1 = lineLength1 - 0x30;
			}
			if(lineLength1 >= 'A' && lineLength1 <= 'F')
			{
				lineLength1 = lineLength1 - 0x37;
			}
			lineLength = lineLength + lineLength1; /* Add nibbles to calculate full byte */
			myChkSum = myChkSum + lineLength; /* Full address retrieved, process checksum */
			
			/*Get first address nibble and bitshift*/
			while(((*scsr) & 0x20) == 0x00);
			address = *scdr;
			if(address >= '0' && address <= '9')
			{
				address = address - 0x30;
			}
			if(address >= 'A' && address <= 'F')
			{
				address = address - 0x37;
			}
			address = address << 4;
			
			/*Get second address nibble and bitshift*/
			while(((*scsr) & 0x20) == 0x00);
			address1 = *scdr;
			if(address1 >= '0' && address1 <= '9')
			{
				address1 = address1 - 0x30;
			}
			if(address1 >= 'A' && address1 <= 'F')
			{
				address1 = address1 - 0x37;
			}
			address = address + address1;
			myChkSum = myChkSum + address; /* Process checksum for byte */
			address = address << 4;
			charCount+=1; /* Begin counting characters on full bytes*/
			
			/*Get third address nibble and bitshift*/
			while(((*scsr) & 0x20) == 0x00);
			address1 = *scdr;
			if(address1 >= '0' && address1 <= '9')
			{
				address1 = address1 - 0x30;
			}
			if(address1 >= 'A' && address1 <= 'F')
			{
				address1 = address1 - 0x37;
			}
			address = address + address1;			
			address = address << 4;
			addChk = addChk + address1;
			addChk = addChk << 4;
			
			/*Get last address nibble and bitshift*/
			while(((*scsr) & 0x20) == 0x00);
			address1 = *scdr;
			if(address1 >= '0' && address1 <= '9')
			{
				address1 = address1 - 0x30;
			}
			if(address1 >= 'A' && address1 <= 'F')
			{
				address1 = address1 - 0x37;
			}
			address = address + address1;
			addChk = addChk + address1;
			myChkSum = myChkSum + addChk;
			charCount+=1;
			/* Set start address once retrieved on first line only */
			if (addFlag == 0)
			{
				addLog = address;
				addFlag = 1;
			}
			
			if (lastLine == 0)
			{
				/* Assign retrived address to pointer */
				origin = (unsigned char *)address;
				/* Retrieve line data */
				do
				{
					/*Get first nibble and bitshift*/
					while(((*scsr) & 0x20) == 0x00);
					fileData = *scdr;
					if(fileData >= '0' && fileData <= '9')
					{
						fileData = fileData - 0x30;
					}
					if(fileData >= 'A' && fileData <= 'F')
					{
						fileData = fileData - 0x37;
					}
					fileData = fileData << 4;
					
					/*Get second address nibble and bitshift*/
					while(((*scsr) & 0x20) == 0x00);
					fileData1 = *scdr;
					if(fileData1 >= '0' && fileData1 <= '9')
					{
						fileData1 = fileData1 - 0x30;
					}
					if(fileData1 >= 'A' && fileData1 <= 'F')
					{
						fileData1 = fileData1 - 0x37;
					}
					fileData = fileData + fileData1; /*Calculate byte */
					myChkSum = myChkSum + fileData; /*Checksum addition*/
					charCount+=1;
					*origin = fileData; /* Assign pointer and increment */
					origin+=1;
				}while(charCount <= lineLength-2);
			}

			/* Retrive checksum and calculate for validation */
			while(((*scsr) & 0x20) == 0x00);
			fileChkSum = *scdr;
			if(fileChkSum >= '0' && fileChkSum <= '9')
			{
				fileChkSum = fileChkSum - 0x30;
			}
			if(fileChkSum >= 'A' && fileChkSum <= 'F')
			{
				fileChkSum = fileChkSum - 0x37;
			}
			fileChkSum = fileChkSum << 4;
			
			/* Get second checksum nibble and bitshift */
			while(((*scsr) & 0x20) == 0x00);
			fileChkSum1 = *scdr;
			if(fileChkSum1 >= '0' && fileChkSum1 <= '9')
			{
				fileChkSum1 = fileChkSum1 - 0x30;
			}
			if(fileChkSum1 >= 'A' && fileChkSum1 <= 'F')
			{
				fileChkSum1 = fileChkSum1 - 0x37;
			}
			fileChkSum = fileChkSum + fileChkSum1;
			myChkSum = ~myChkSum; /*1s complement for correct checksum value*/
			
			/* Validate line with checksum */
			if(myChkSum != fileChkSum)
			{
				chkFail = 1;
				failLine = lineCount+1;
				status = 1;
				break;
			}
			lineCount+=1; /*increment line count as done and flag ready for next line */
			flag = 0;
		}
			
	}while(status == 0);
		
	/* Process once file has finished or failed */
	if(chkFail == 0)
	{
		printf("\n\n\rDownload completed with %d lines successfully read.\n\r",lineCount);
	}
	else
	{
		printf("\n\n\rError! File read failed on line %d!\n\r", failLine);
	}
	printf("Data origin at: %04x, last received checksum: %02x, validated checksum: %02x\n\r", addLog, fileChkSum, myChkSum);

	return(1);
}

/**********************************************************
Author:			Daniel Truman
Company:		Staffordshire University
Date:			12/03/21
Version:		1.0
Purpose:		Prints out a block of memory to display that shows hexadecimal values and the recognised ascii equivalents in a set specified range of memory
Modifications:	0.1 - Initial implementation with no data filtering
				0.2 - ASCII data ranges add for filtering and replacement '.' character used
				0.3 - Formatting changed to match monitor programme's DM
				1.0 - Tested and implemented in programme, debug lines commented out
Functions:		None
Variables:		unsigned char	- *address		- Pointer to the address range taken from incoming validated paramter addTemp
								- i				- Holds a value used to iterate through a printing loop to display a line of characters
								- j				- Holds a value used to iterate through a printing loop to display a line of characters
								- data			- Holds a value received from pointer *address
				char			- ascii[2]		- Holds an array of validated values taken from data for use in string construction in strAscii[]
								- fillAscii[2]	- Holds an array of pre-initialised values use to display invalidated ASCII character as '.' in strAscii[]
								- strAscii[15]	- Holds an array of character values concatenated from ascii[] and fillAscii[] to display
				unsigned int	- addTemp			- Incoming parameter holds a hexadecimal value representing a memory address
**********************************************************/
int displayMem(unsigned int addTemp)
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

/**********************************************************
Author:			Daniel Truman
Company:		Staffordshire University
Date:			14/03/21
Version:		1.0
Purpose:		Allows the user to modify memory from a specified address one byte at a time
Modifications:	0.1 - Initial implementation allows for iteration over memory with unchecked data entry
				0.2 - Added address skipping and quitting on '.'
				0.3 - Added data validation to ensure hexadecimal and no whitespacing
				1.0 - Tested and implemented in programme, debug lines commented out
Functions:		None
Variables:		unsigned char	- *address		- Pointer to the address range taken from incoming validated paramter addTemp
								- data			- Holds a value received from the pointer *address
								- isBreak		- Holds a value used as a flag to determine an action during user input
				char			- newData[10]	- Holds an array of values from user input sized to ensure no buffer overrun and then validated
				unsigned int	- addTemp			- Incoming parameter holds a hexadecimal value representing a memory address
								- data1			- Holds a value extracted from validated user input used to change data at pointer *address
**********************************************************/
int modifyMem(unsigned int addTemp)
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

/**********************************************************
Author:			Daniel Truman
Company:		Staffordshire University
Date:			10/03/21
Version:		1.0
Purpose:		Displays recognised assembly codes in a user specified range of addresses
Modifications:	0.1 - Initial structure design and implementation of array of commands
				0.2 - Implemented detection of standard codes on memory
				0.3 - Modofied flag clearing
				0.4 - Implement detection of extended commands
				0.5 - Changed detection of extended commands to scan forwards
				0.6 - Implemented new array for extended commands
				1.0 - Tested and implemented in programme, debug lines commented out
Functions:		mykeyscan()
Structure:		opAssembler
Variables:		struct			- command[255]		- Holds and array of value relating to the hexadecimal operation codes for assembler commands used as lookup table
								- extraCommand[255]	- Holds and array of value relating to the hexadecimal operation codes for extended assembler commands used as lookup table
				unsigned char	- *addStart			- Pointer to the starting address range taken from validated incoming parameter addTemp1
								- *addEnd			- Pointer to the last address range taken from validated incoming parameter addTemp1
								- n					- Holds a value used to activate a condition to pause the display until user prompts to leave or continue
								- data				- Holds a value received from pointer *addStart
								- data1				- Holds a value from the next address received from pointer *addStart
								- data2				- Holds a value from the next address but one received from pointer *addStart
								- flagData			- Holds a value used as a flag to indicate the use of the extended commands array
								- wait				- Holds a value from mkeyscan() function to hold until user inputs a key
				char			- temp[10]			- Holds an array of values used to create a string to output to display
								- temp1[10]			- Holds an array of values used to create a string to concatenate to temp[10]
								- temp2[10]			- Holds an array of values used to create a string to concatenate to temp1[10]
				unsigned int	- addTemp1			- Incoming parameter holds a hexadecimal value representing a memory address
								- addTemp2			- Incoming parameter holds a hexadecimal value representing a memory address
								- addRange			- Holds a value calculated from addTemp1 and addTemp2 to use a limit in for loop
				long int		- i					- Holds a value used to iterate through for loop with potentially very large ranges
**********************************************************/
int disassembleMem(unsigned int addTemp1, unsigned int addTemp2)
{
	
	struct opAssembler command[255], extraCommand[255];
	unsigned char *addStart, *addEnd;
	unsigned char n, data, data1, data2, flagData, wait;
	char temp[10], temp1[10], temp2[10];
	unsigned int addRange;
	long int i;

	/*Initialse data for all assembly commands to be recognised*/
	strcpy(command[0x1B].instruction,"ABA ");
	command[0x1B].bytes = 0;
	strcpy(command[0x1B].isValid, "Valid");
	
	strcpy(command[0x3A].instruction,"ABX ");
	command[0x3A].bytes = 0;
	command[0x3A].type = 18;
	strcpy(command[0x3A].isValid, "Valid");
		
	strcpy(extraCommand[0x3A].instruction,"ABY "); /*18 Type*/
	extraCommand[0x3A].bytes = 0;
	strcpy(extraCommand[0x3A].isValid, "Valid");
		
	strcpy(command[0x89].instruction,"ADCA #$");
	command[0x89].bytes = 1; /*Usually*/
	strcpy(command[0x89].isValid, "Valid");
		
	strcpy(command[0x99].instruction,"ADCA $");
	command[0x99].bytes = 1; /*Ignores top 8 bits*/
	strcpy(command[0x99].isValid, "Valid");
		
	strcpy(command[0xB9].instruction,"ADCA $");
	command[0xB9].bytes = 2;
	strcpy(command[0xB9].isValid, "Valid");

	strcpy(command[0xA9].instruction,"ADCA X,$");
	command[0xA9].bytes = 1;
	command[0xA9].type = 18;
	strcpy(command[0xA9].isValid, "Valid");

	strcpy(extraCommand[0xA9].instruction,"ADCA Y,$"); /*18 Type*/
	extraCommand[0xA9].bytes = 1;
	strcpy(extraCommand[0xA9].isValid, "Valid");

	strcpy(command[0xC9].instruction,"ADCB #$");
	command[0xC9].bytes = 1; /*Usually*/
	strcpy(command[0xC9].isValid, "Valid");

	strcpy(command[0xD9].instruction,"ADCB $");
	command[0xD9].bytes = 1; /*Ignores top 8 bits*/
	strcpy(command[0xD9].isValid, "Valid");

	strcpy(command[0xF9].instruction,"ADCB $");
	command[0xF9].bytes = 2;
	strcpy(command[0xF9].isValid, "Valid");

	strcpy(command[0xE9].instruction,"ADCB X,$");
	command[0xE9].bytes = 1;
	command[0xE9].type = 18;
	strcpy(command[0xE9].isValid, "Valid");

	strcpy(extraCommand[0xE9].instruction,"ADCB Y,$"); /*18 Type*/
	extraCommand[0xE9].bytes = 1;
	strcpy(extraCommand[0xE9].isValid, "Valid");
		
	strcpy(command[0x8B].instruction,"ADDA #$");
	command[0x8B].bytes = 1; /*Usually*/
	strcpy(command[0x8B].isValid, "Valid");
		
	strcpy(command[0x9B].instruction,"ADDA $");
	command[0x9B].bytes = 1; /*Ignores top 8 bits*/
	strcpy(command[0x9B].isValid, "Valid");
		
	strcpy(command[0xBB].instruction,"ADDA $");
	command[0xBB].bytes = 2;
	strcpy(command[0xBB].isValid, "Valid");
		
	strcpy(command[0xAB].instruction,"ADDA X,$");
	command[0xAB].bytes = 1;
	command[0xAB].type = 18;
	strcpy(command[0xAB].isValid, "Valid");
		
	strcpy(extraCommand[0xAB].instruction,"ADDA Y,$"); /*18 Type*/
	extraCommand[0xAB].bytes = 1;
	strcpy(extraCommand[0xAB].isValid, "Valid");
		
	strcpy(command[0xCB].instruction,"ADDB #$");
	command[0xCB].bytes = 1; /*Usually*/
	strcpy(command[0xCB].isValid, "Valid");
		
	strcpy(command[0xDB].instruction,"ADDB $");
	command[0xDB].bytes = 1; /*Ignores top 8 bits*/
	strcpy(command[0xDB].isValid, "Valid");
		
	strcpy(command[0xFB].instruction,"ADDB $");
	command[0xFB].bytes = 2;
	strcpy(command[0xFB].isValid, "Valid");
		
	strcpy(command[0xEB].instruction,"ADDB X,$");
	command[0xEB].bytes = 1;
	command[0xEB].type = 18;
	strcpy(command[0xEB].isValid, "Valid");
		
	strcpy(extraCommand[0xEB].instruction,"ADDB Y,$"); /*18 Type*/
	extraCommand[0xEB].bytes = 1;
	strcpy(extraCommand[0xEB].isValid, "Valid");
		
	strcpy(command[0xC3].instruction,"ADDD #$");
	command[0xC3].bytes = 2;
	strcpy(command[0xC3].isValid, "Valid");
		
	strcpy(command[0xD3].instruction,"ADDD $");
	command[0xD3].bytes = 1;
	strcpy(command[0xD3].isValid, "Valid");
	
	strcpy(command[0xF3].instruction,"ADDD $");
	command[0xF3].bytes = 2;
	strcpy(command[0xF3].isValid, "Valid");
	
	strcpy(command[0xE3].instruction,"ADDD X,$");
	command[0xE3].bytes = 1;
	command[0xE3].type = 18;
	strcpy(command[0xE3].isValid, "Valid");
	
	strcpy(extraCommand[0xE3].instruction,"ADDD Y,$"); /*18 Type*/
	extraCommand[0xE3].bytes = 1;
	strcpy(extraCommand[0xE3].isValid, "Valid");
	
	strcpy(command[0x80].instruction,"SUBA #$");
	command[0x80].bytes = 1; /*Usually*/
	strcpy(command[0x80].isValid, "Valid");
	
	strcpy(command[0x90].instruction,"SUBA $");
	command[0x90].bytes = 1; /*Ignores top 8 bits*/
	strcpy(command[0x90].isValid, "Valid");
	
	strcpy(command[0xB0].instruction,"SUBA $");
	command[0xB0].bytes = 2;
	strcpy(command[0xB0].isValid, "Valid");
	
	strcpy(command[0xA0].instruction,"SUBA X,$");
	command[0xA0].bytes = 1;
	command[0xA0].type = 18;
	strcpy(command[0xA0].isValid, "Valid");
	
	strcpy(extraCommand[0xA0].instruction,"SUBA Y,$"); /*18 Type*/
	extraCommand[0xA0].bytes = 1;
	strcpy(extraCommand[0xA0].isValid, "Valid");
	
	strcpy(command[0xC0].instruction,"SUBB #$");
	command[0xC0].bytes = 1; /*Usually*/
	strcpy(command[0xC0].isValid, "Valid");
	
	strcpy(command[0xD0].instruction,"SUBB $");
	command[0xD0].bytes = 1; /*Ignores top 8 bits*/
	strcpy(command[0xD0].isValid, "Valid");
	
	strcpy(command[0xF0].instruction,"SUBB $");
	command[0xF0].bytes = 2;
	strcpy(command[0xF0].isValid, "Valid");
	
	strcpy(command[0xE0].instruction,"SUBB X,$");
	command[0xE0].bytes = 1;
	command[0xE0].type = 18;
	strcpy(command[0xE0].isValid, "Valid");
	
	strcpy(extraCommand[0xE0].instruction,"SUBB Y,$"); /*18 Type*/
	extraCommand[0xE0].bytes = 1;
	strcpy(extraCommand[0xE0].isValid, "Valid");
	
	strcpy(command[0x83].instruction,"SUBD #$");
	command[0x83].bytes = 2;
	strcpy(command[0x83].isValid, "Valid");
	
	strcpy(command[0x93].instruction,"SUBD $");
	command[0x93].bytes = 1;
	strcpy(command[0x93].isValid, "Valid");
	
	strcpy(command[0xB3].instruction,"SUBD $");
	command[0xB3].bytes = 2;
	strcpy(command[0xB3].isValid, "Valid");
	
	strcpy(command[0xA3].instruction,"SUBD X,$");
	command[0xA3].bytes = 1;
	command[0xA3].type = 18;
	strcpy(command[0xA3].isValid, "Valid");
	
	strcpy(extraCommand[0xA3].instruction,"SUBD Y,$"); /*18 Type*/
	extraCommand[0xA3].bytes = 1;
	strcpy(extraCommand[0xA3].isValid, "Valid");
	
	strcpy(command[0x86].instruction,"LDAA #$");
	command[0x86].bytes = 1; /*Usually*/
	strcpy(command[0x86].isValid, "Valid");
	
	strcpy(command[0x96].instruction,"LDAA $");
	command[0x96].bytes = 1; /*Ignores top 8 bits*/
	strcpy(command[0x96].isValid, "Valid");
	
	strcpy(command[0xB6].instruction,"LDAA $");
	command[0xB6].bytes = 2;
	strcpy(command[0xB6].isValid, "Valid");
	
	strcpy(command[0xA6].instruction,"LDAA X,$");
	command[0xA6].bytes = 1;
	command[0xA6].type = 18;
	strcpy(command[0xA6].isValid, "Valid");
	
	strcpy(extraCommand[0xA6].instruction,"LDAA Y,$"); /*18 Type*/
	extraCommand[0xA6].bytes = 1;
	strcpy(extraCommand[0xA6].isValid, "Valid");
	
	strcpy(command[0xC6].instruction,"LDAB #$");
	command[0xC6].bytes = 1; /*Usually*/
	strcpy(command[0xC6].isValid, "Valid");
	
	strcpy(command[0xD6].instruction,"LDAB $");
	command[0xD6].bytes = 1; /*Ignores top 8 bits*/
	strcpy(command[0xD6].isValid, "Valid");
	
	strcpy(command[0xF6].instruction,"LDAB $");
	command[0xF6].bytes = 2;
	strcpy(command[0xF6].isValid, "Valid");
	
	strcpy(command[0xE6].instruction,"LDAB X,$");
	command[0xE6].bytes = 1;
	command[0xE6].type = 18;
	strcpy(command[0xE6].isValid, "Valid");
	
	strcpy(extraCommand[0xE6].instruction,"LDAB Y,$"); /*18 Type*/
	extraCommand[0xE6].bytes = 1;
	strcpy(extraCommand[0xE6].isValid, "Valid");
	
	strcpy(command[0xCC].instruction,"LDD #$");
	command[0xCC].bytes = 2;
	strcpy(command[0xCC].isValid, "Valid");
	
	strcpy(command[0xDC].instruction,"LDD $");
	command[0xDC].bytes = 1;
	strcpy(command[0xDC].isValid, "Valid");
	
	strcpy(command[0xFC].instruction,"LDD $");
	command[0xFC].bytes = 2;
	strcpy(command[0xFC].isValid, "Valid");
	
	strcpy(command[0xEC].instruction,"LDD X,$");
	command[0xEC].bytes = 1;
	command[0xEC].type = 18;
	strcpy(command[0xEC].isValid, "Valid");
	
	strcpy(extraCommand[0xEC].instruction,"LDD Y,$"); /*18 Type*/
	extraCommand[0xEC].bytes = 1;
	strcpy(extraCommand[0xEC].isValid, "Valid");
	
	strcpy(command[0x97].instruction,"STAA $");
	command[0x97].bytes = 1; /*Ignores top 8 bits*/
	strcpy(command[0x97].isValid, "Valid");
	
	strcpy(command[0xB7].instruction,"STAA $");
	command[0xB7].bytes = 2;
	strcpy(command[0xB7].isValid, "Valid");
	
	strcpy(command[0xA7].instruction,"STAA X,$");
	command[0xA7].bytes = 1;
	command[0xA7].type = 18;
	strcpy(command[0xA7].isValid, "Valid");
	
	strcpy(extraCommand[0xA7].instruction,"STAA Y,$"); /*18 Type*/
	extraCommand[0xA7].bytes = 1;
	strcpy(extraCommand[0xA7].isValid, "Valid");
	
	strcpy(command[0xD7].instruction,"STAB $");
	command[0xD7].bytes = 1; /*Ignores top 8 bits*/
	strcpy(command[0xD7].isValid, "Valid");
	
	strcpy(command[0xF7].instruction,"STAB $");
	command[0xF7].bytes = 2;
	strcpy(command[0xF7].isValid, "Valid");
	
	strcpy(command[0xE7].instruction,"STAB X,$");
	command[0xE7].bytes = 1;
	command[0xE7].type = 18;
	strcpy(command[0xE7].isValid, "Valid");
	
	strcpy(extraCommand[0xE7].instruction,"STAB Y,$"); /*18 Type*/
	extraCommand[0xE7].bytes = 1;
	strcpy(extraCommand[0xE7].isValid, "Valid");
	
	strcpy(command[0xDD].instruction,"STD $");
	command[0xDD].bytes = 1;
	strcpy(command[0xDD].isValid, "Valid");
	
	strcpy(command[0xFD].instruction,"STD $");
	command[0xFD].bytes = 2;
	strcpy(command[0xFD].isValid, "Valid");
	
	strcpy(command[0xED].instruction,"STD X,$");
	command[0xED].bytes = 1;
	command[0xED].type = 18;
	strcpy(command[0xED].isValid, "Valid");
	
	strcpy(extraCommand[0xED].instruction,"STD Y,$"); /*18 Type*/
	extraCommand[0xED].bytes = 1;
	strcpy(extraCommand[0xED].isValid, "Valid");
	
	/* Assign pointers to addresses */
	addStart = (unsigned char *)addTemp1;
	addEnd = (unsigned char *)addTemp2;
	
	/*Set the max range and prep for the loop*/
	addRange = addEnd - addStart;
	/*printf("Range Hex: %x, Dec: %d\n\r", addRange, addRange);*/ /* Debug line */
	n = 0;
	printf("\n\rAddress\tHex Data\tAssembly\n\r");
	
	for(i = 0; i < addRange+1; i++)
	{
		/*Clear the strings and flags*/
		temp[0] = '\0';
		temp1[0] = '\0';
		temp2[0] = '\0';

		data = *addStart;

		printf("\n\r%x\t%02x", addStart, data);
		flagData = *(addStart+1); /* Look at next address value - used for validating 0x18 type commands */
	
		if (data == 0x18 && command[flagData].type == 18)
		{
			strcpy(temp, extraCommand[flagData].instruction); /* Write 0x18 data to temp */
			data1 = *(addStart+1); /* Get opcode */
			sprintf(temp1, "%02x", data1); /* Write opcode to temp1 */
			
			if(command[flagData].bytes == 1) /* Get extra data if a byte should be attached */
			{
				data2 = *(addStart+2); /* Get attached byte - all 0x18 codes are 1 byte */
				sprintf(temp2, "%02x", data2); /* Byte written to temp2 */
				strcat(temp1, temp2); /* Data concatenated */
				i+= 1; /* Iterate past retrieved addresses */
				addStart+= 1;
			}
			
			i+= 1; /* Iterate past remaining addresses */
			addStart+= 1;
			printf("%s\t\t%s%s", temp1, temp, temp2);
		}
	
		/* Look up string */
		if (strcmp(command[data].isValid, "Valid") == 0) /* Check valid tab */
		{
			strcpy(temp, command[data].instruction);
				
			/* Look up number of bytes next */
			if (command[data].bytes == 2)
			{
				data1 = *(addStart+1);
				sprintf(temp1, "%02x", data1);
				data2 = *(addStart+2);
				sprintf(temp2, "%02x", data2);
				strcat(temp1, temp2);
				i+= 2;
				addStart+= 2;
			}
			
			if (command[data].bytes == 1)
			{
				data1 = *(addStart+1);
				sprintf(temp1, "%02x", data1);
				i+= 1;
				addStart+= 1;
			}
		
			printf("%s\t\t%s%s", temp1, temp, temp1);
			
		}
		
		addStart+= 1;
		
		/*Page break here*/
		n++;
		if (n == 15)
		{
			printf("\n\n\r%ld/%u addresses displayed. Press any key to continue or 'q' to stop.\n\r", (i + 1), addRange);
			wait = '\0';
			while (wait == '\0')
			{
				wait = mkeyscan(); /* Wait for continue */
				
			}
			n = 0;
			
			/* Don't print header if quitting */
			if (wait != 'q')
			{
				printf("\n\rAddress\tHex Data\tAssembly\n\r");
			}
		}
		
		/* Quit on 'q' */
		if (wait == 'q')
		{
			break;
		}
	}
	return(1);
}

/**********************************************************
Author:			Daniel Truman
Company:		Staffordshire University
Date:			25/03/21
Version:		1.0
Purpose:		Runs a demo outputting to a stepper motor on port A in order to move it. Speed is regulated by values from a potentiometer on port E
Modifications:	0.1 - Initial menu design with rudimentary function calls
				0.2 - Added a keyscan to allow break from function
				1.0 - Tested and implemented in programme, debug lines commented out
Functions:		mkeyscan()
Variables:		unsigned char	- *adctl	- Pointer to the address of the A/D Control/Status register
								- *adr1		- Pointer to the address of the A/D result register 1 
								- *porta	- Pointer to the address of the hardware port A
								- *ddra		- Pointer to the address of the port A Data Direction Register
								- offset	- Holds a value used to increase the delay to allow for a more visible change in speed
								- exit		- Holds a value intialised to null and used to indicate a user quitting the demo via function mykeyscan()
				unsigned int	- delay		- Holds a value calculated from offset and value obtained from port E A/D.
								- i			- Holds a value used to delay the programme in a for loop whilst i is less than delay
**********************************************************/
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

/**********************************************************
Author:			Daniel Truman
Company:		Staffordshire University
Date:			06/03/21
Version:		1.0
Purpose:		To validate any use input from main() to ensure no incorrect inputs are fed on function calls from main
Modifications:	0.1 - Initial structure with basic error status returns
				0.2 - Validation of incoming parameters implemented
				0.3 - Modified parameters and added more debugging code
				1.0 - Tested and implemented in programme, debug lines commented out			
Functions:		mkeyscan()
Variables:		unsigned int	- code		- Incoming parameter holds a value used in function switch case
								- valOne	- Incoming parameter holds a hexadecimal value representing an address range for validation
								- valTwo	- Incoming parameter holds a hexadecimal value representing an address range for validation
				unsigned char	- errorCode	- Holds a value to return to main indicating status of error found during validation
**********************************************************/
int errorCheck(unsigned int code, unsigned int valOne, unsigned int valTwo)
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

/**********************************************************
Author:			Mr James Mccarren
Company:		Staffordshire University
Version:		1.0
Purpose:		Simple keyscan with no handshaking using 68hc11 microcontroller
Modifications:	None to function. Changes made to variable names in calling process only.
Functions:		None
Variables:
**********************************************************/
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

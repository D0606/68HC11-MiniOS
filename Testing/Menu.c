#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/************ Function Prototypes ************/
int mainMenu();
int loadFile();
int displayMem(int mem);
int modifyMem(int mem);
int disassembleMem(int startMem, int endMem);
int demo();
int errorCheck(unsigned char code, unsigned int valOne, unsigned int valTwo);

/**********************************************************
Author: Daniel Truman
Company: Staffordshire University
Date: 03/03/21
Version:		0.1
Purpose:		
Modifications:	0.1 - Initial menu design with rudimentary function calls
Functions:		None
Variables:		
**********************************************************/
int main()
{
	unsigned char strChoice[20], cmdChoice[5];
	unsigned char launchCode, invalidChoice = 1, i = 0, strLength = 0, matched = 0;
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
			printf("Command: %s, length: %d, Start Range:  %04x, End Range: %04x\n\r", cmdChoice, strlen(cmdChoice), startRange, endRange);
			
			/*Process command string for accurate matching*/
			for(i = 0; i < strlen(cmdChoice); i++)
			{
				cmdChoice[i] = toupper(cmdChoice[i]);
			}
			printf("Command entered was: %s\n\r", cmdChoice);

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
						printf("An error has occured -- Error: %u.\n\r", launchCode);
						invalidChoice = 1;
						break;
				}
			}
		}
	}
	return 0;
}

/**********************************************************
Author: Daniel Truman
Company: Staffordshire University
Date: 03/03/21
Version:		0.1
Purpose:		
Modifications:	0.1 - Initial menu design with rudimentary function calls
Functions:		None
Variables:		
**********************************************************/
int loadFile()
{
	printf("This should call function for Loading File, accepts no parameters.\n\r");
	return 0;
}

/**********************************************************
Author: Daniel Truman
Company: Staffordshire University
Date: 03/03/21
Version:		0.1
Purpose:		
Modifications:	0.1 - Initial menu design with rudimentary function calls
Functions:		None
Variables:		
**********************************************************/
int displayMem(int mem)
{
	printf("This should call function for Displaying Memory, accepts one Memory parameter and displays a range from there. Current: %x\n\r", mem);
	return 0;
}

/**********************************************************
Author: Daniel Truman
Company: Staffordshire University
Date: 03/03/21
Version:		0.1
Purpose:		
Modifications:	0.1 - Initial menu design with rudimentary function calls
Functions:		None
Variables:		
**********************************************************/
int modifyMem(int mem)
{
	printf("This should call function for Modifying Memory, accepts one Memory parameter and allows changes one address at a time. Current: %x\n\r", mem);
	return 0;
}

/**********************************************************
Author: Daniel Truman
Company: Staffordshire University
Date: 03/03/21
Version:		0.1
Purpose:		
Modifications:	0.1 - Initial menu design with rudimentary function calls
Functions:		None
Variables:		
**********************************************************/
int disassembleMem(int startMem, int endMem)
{
	printf("This should call function for Disassembling Memory, accepts two parameters that will show the disassembled code in that memory range. Current: %x-%x\n\r", startMem, endMem);
	return 0;
}

/**********************************************************
Author: Daniel Truman
Company: Staffordshire University
Date: 03/03/21
Version:		0.1
Purpose:		
Modifications:	0.1 - Initial menu design with rudimentary function calls
Functions:		None
Variables:		
**********************************************************/
int demo()
{
	printf("This should call function for the Demo, accepts no parameters.\n\r");
	return 0;
}

/**********************************************************
Author: Daniel Truman
Company: Staffordshire University
Date: 03/03/21
Version:		0.1
Purpose:		
Modifications:	0.1 - Initial menu design with rudimentary function calls
Functions:		None
Variables:		
**********************************************************/
int errorCheck(int code, int valOne, int valTwo)
{
	printf("Command code: %u | Value one: %x | Value two: %x\n\r", code, valOne, valTwo);
	return 0;
}

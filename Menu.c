#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/************ Function Prototypes ************/
int mainMenu();
int isWhitespace(char a);
char *mgets(char *is);
int loadFile();
int displayMem(int mem);
int modifyMem(int mem);
int disassembleMem(int startMem, int endMem);
int demo();
int errorCheck(int code, int valOne, int valTwo);

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
	unsigned char strChoice[13], cmdChoice[5];
	unsigned int i = 0, invalidChoice = 1, startRange = 0, endRange = 0, caseSelect = 9, strLength = 0, errorCode = 0;
	
	for(;;)
	{
		
		while(invalidChoice == 1)
		{
			/*Print out main menu and display choices*/
			printf("\n\n\r*#*#*#*#*#*#*#*#*#*#*#* 04908117 - Assignment Main Menu *#*#*#*#*#*#*#*#*#*#*#*\n\n\r");
			printf("Please select from the following options:\n\n\r");
			printf("LF\tLoad File. Syntax: LF\n\r");
			printf("DM\tDisplay Memory. Syntax: DM <Start Range> e.g.DM 400\n\r");
			printf("MM\tModify Memory. Syntax: MM <Start Range> e.g.MM 400\n\r");
			printf("DS\tDisassemble Memory. Syntax: DS <Start Range> <End Range> e.g.DS 400 800\n\r");
			printf("DEMO\tLaunch the onboard demo. Syntax: DEMO\n\r");
			printf("\n\r*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*\n\n\r");
			printf("Please enter your command: ");
			gets(strChoice); /*Receive user input*/
			/*printf("\n\rString is: %s\n\r", strChoice);*/ /*Debug Line*/
			sscanf(strChoice, "%s %u %u", &cmdChoice, &startRange, &endRange); /*Assign inputs to variables to check for validity*/
			printf("Command: %s, length: %d, Start Range:  %u, End Range: %u\n\r", cmdChoice, strlen(cmdChoice), startRange, endRange);
			
			/*Process command string for accurate matching*/
			for(i = 0; i < strlen(cmdChoice); i++)
			{
				cmdChoice[i] = toupper(cmdChoice[i]);
			}
			printf("Command entered was: %s\n\r", cmdChoice);
			
			/*Check if command was valid and process*/
			if(strcmp(cmdChoice, "LF") == 0)
			{
				caseSelect = 0;
				errorCode = errorCheck(caseSelect, startRange, endRange);
				if (errorCode == 0)
				{
					invalidChoice = 0;
				}
			}
			else if(strcmp(cmdChoice, "DM") == 0)
			{
				caseSelect = 1;
				errorCode = errorCheck(caseSelect, startRange, endRange);
				if (errorCode == 0)
				{
					invalidChoice = 0;
				}
			}
			else if(strcmp(cmdChoice, "MM") == 0)
			{
				caseSelect = 2;
				errorCode = errorCheck(caseSelect, startRange, endRange);
				if (errorCode == 0)
				{
					invalidChoice = 0;
				}
			}
			else if(strcmp(cmdChoice, "DS") == 0)
			{
				caseSelect = 3;
				errorCode = errorCheck(caseSelect, startRange, endRange);
				if (errorCode == 0)
				{
					invalidChoice = 0;
				}
			}
			else if(strcmp(cmdChoice, "DEMO") == 0)
			{
				caseSelect = 4;
				errorCode = errorCheck(caseSelect, startRange, endRange);
				if (errorCode == 0)
				{
					invalidChoice = 0;
				}
			}
			else
			{
				printf("Invalid entry, please ensure you enter the command following the example syntax.\n\r");
				invalidChoice = 1; /*Ensure variable keeps the loop*/
				startRange = 0;
				endRange = 0;				
			}			
		}
		
		switch(caseSelect)
		{
			case 0:
				loadFile();
				startRange = 0;
				endRange = 0;
				break;
			case 1:
				displayMem(startRange);
				startRange = 0;
				endRange = 0;
				break;
			case 2:
				modifyMem(startRange);
				startRange = 0;
				endRange = 0;
				break;
			case 3:
				disassembleMem(startRange, endRange);
				startRange = 0;
				endRange = 0;
				break;
			case 4:
				demo();
				startRange = 0;
				endRange = 0;
				break;
			default:
				printf("An error has occured, no command was selected.\n\r");
				startRange = 0;
				endRange = 0;
				break;
		}
		
		invalidChoice = 1;	
	}
	return 0;
}

int loadFile()
{
	printf("This should call function for Loading File, accepts no parameters.\n\r");
	return 0;
}

int displayMem(int mem)
{
	printf("This should call function for Displaying Memory, accepts one Memory parameter and displays a range from there. Current: %u\n\r", mem);
	return 0;
}

int modifyMem(int mem)
{
	printf("This should call function for Modifying Memory, accepts one Memory parameter and allows changes one address at a time. Current: %u\n\r", mem);
	return 0;
}

int disassembleMem(int startMem, int endMem)
{
	printf("This should call function for Disassembling Memory, accepts two parameters that will show the disassembled code in that memory range. Current: %u-%u\n\r", startMem, endMem);
	return 0;
}

int demo()
{
	printf("This should call function for the Demo, accepts no parameters.\n\r");
	return 0;
}

int errorCheck(int code, int valOne, int valTwo)
{
	printf("Error code: %u | Value one: %u | Value two: %u\n\r", code, valOne, valTwo);
	return 0;
}


















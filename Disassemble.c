#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

unsigned char mkeyscan();

typedef struct opAssembler
{
	char instruction[10];
	char bytes;
	char type;
	char isValid[6];
} opAssembler;

int main()
{
	
	struct opAssembler command[255], extraCommand[255];
	unsigned char getStart[5], getEnd[5];
	unsigned char n, data, data1, data2, flagData, wait;
	char temp[10], temp1[10], temp2[10];
	unsigned char *addStart, *addEnd;
	unsigned int addRange, addTemp;
	long int i;
	/*unsigned char testData[100];*/ /*for example*/

	/*Initialse data*/
	strcpy(command[0x1B].instruction,"ABA ");
	command[0x1B].bytes = 0;
	strcpy(command[0x1B].isValid, "Valid");
	
	strcpy(command[0x3A].instruction,"ABX ");
	command[0x3A].bytes = 0;
	command[0x3A].type = 18;
	strcpy(command[0x3A].isValid, "Valid");
		
	strcpy(extraCommand[/*0xFF+*/0x3A].instruction,"ABY "); /*18 Type*/
	extraCommand[0x3A].bytes = 0;
	strcpy(extraCommand[0x3A].isValid, "Valid");
		
	strcpy(command[0x89].instruction,"ADCA #$");
	command[0x89].bytes = 1; /*Usually*/
	strcpy(command[0x89].isValid, "Valid");
		
	strcpy(command[0x99].instruction,"ADCA $");
	command[0x99].bytes = 2;
	strcpy(command[0x99].isValid, "Valid");
		
	strcpy(command[0xB9].instruction,"ADCA $");
	command[0xB9].bytes = 2;
	strcpy(command[0xB9].isValid, "Valid");
		
	strcpy(command[0xA9].instruction,"ADCA,X $");
	command[0xA9].bytes = 1;
	command[0xA9].type = 18;
	strcpy(command[0xA9].isValid, "Valid");
		
	strcpy(extraCommand[0xA9].instruction,"ADCA,Y $"); /*18 Type*/
	extraCommand[0xA9].bytes = 1;
	strcpy(extraCommand[0xA9].isValid, "Valid");
		
	strcpy(command[0xC9].instruction,"ADCB #$");
	command[0xC9].bytes = 1; /*Usually*/
	strcpy(command[0xC9].isValid, "Valid");
		
	strcpy(command[0xD9].instruction,"ADCB $");
	command[0xD9].bytes = 2;
	strcpy(command[0xD9].isValid, "Valid");
		
	strcpy(command[0xF9].instruction,"ADCB $");
	command[0xF9].bytes = 2;
	strcpy(command[0xF9].isValid, "Valid");
		
	strcpy(command[0xE9].instruction,"ADCB,X $");
	command[0xE9].bytes = 1;
	command[0xE9].type = 18;
	strcpy(command[0xE9].isValid, "Valid");
		
	strcpy(extraCommand[0xE9].instruction,"ADCB,Y $"); /*18 Type*/
	extraCommand[0xE9].bytes = 1;
	strcpy(extraCommand[0xE9].isValid, "Valid");
		
	strcpy(command[0x8B].instruction,"ADDA #$");
	command[0x8B].bytes = 1; /*Usually*/
	strcpy(command[0x8B].isValid, "Valid");
		
	strcpy(command[0x9B].instruction,"ADDA $");
	command[0x9B].bytes = 2;
	strcpy(command[0x9B].isValid, "Valid");
		
	strcpy(command[0xBB].instruction,"ADDA $");
	command[0xBB].bytes = 2;
	strcpy(command[0xBB].isValid, "Valid");
		
	strcpy(command[0xAB].instruction,"ADDA,X $");
	command[0xAB].bytes = 1;
	command[0xAB].type = 18;
	strcpy(command[0xAB].isValid, "Valid");
		
	strcpy(extraCommand[0xAB].instruction,"ADDA,Y $"); /*18 Type*/
	extraCommand[0xAB].bytes = 1;
	strcpy(extraCommand[0xAB].isValid, "Valid");
		
	strcpy(command[0xCB].instruction,"ADDB #$");
	command[0xCB].bytes = 1; /*Usually*/
	strcpy(command[0xCB].isValid, "Valid");
		
	strcpy(command[0xDB].instruction,"ADDB $");
	command[0xDB].bytes = 2;
	strcpy(command[0xDB].isValid, "Valid");
		
	strcpy(command[0xFB].instruction,"ADDB $");
	command[0xFB].bytes = 2;
	strcpy(command[0xFB].isValid, "Valid");
		
	strcpy(command[0xEB].instruction,"ADDB,X $");
	command[0xEB].bytes = 1;
	command[0xEB].type = 18;
	strcpy(command[0xEB].isValid, "Valid");
		
	strcpy(extraCommand[0xEB].instruction,"ADDB,Y $"); /*18 Type*/
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
	
	strcpy(command[0xE3].instruction,"ADDD,X $");
	command[0xE3].bytes = 1;
	command[0xE3].type = 18;
	strcpy(command[0xE3].isValid, "Valid");
	
	strcpy(extraCommand[0xE3].instruction,"ADDD,Y $"); /*18 Type*/
	extraCommand[0xE3].bytes = 1;
	strcpy(extraCommand[0xE3].isValid, "Valid");
	
	strcpy(command[0x80].instruction,"SUBA #$");
	command[0x80].bytes = 1; /*Usually*/
	strcpy(command[0x80].isValid, "Valid");
	
	strcpy(command[0x90].instruction,"SUBA $");
	command[0x90].bytes = 2;
	strcpy(command[0x90].isValid, "Valid");
	
	strcpy(command[0xB0].instruction,"SUBA $");
	command[0xB0].bytes = 2;
	strcpy(command[0xB0].isValid, "Valid");
	
	strcpy(command[0xA0].instruction,"SUBA,X $");
	command[0xA0].bytes = 1;
	command[0xA0].type = 18;
	strcpy(command[0xA0].isValid, "Valid");
	
	strcpy(extraCommand[0xA0].instruction,"SUBA,Y $"); /*18 Type*/
	extraCommand[0xA0].bytes = 1;
	strcpy(extraCommand[0xA0].isValid, "Valid");
	
	strcpy(command[0xC0].instruction,"SUBB #$");
	command[0xC0].bytes = 1; /*Usually*/
	strcpy(command[0xC0].isValid, "Valid");
	
	strcpy(command[0xD0].instruction,"SUBB $");
	command[0xD0].bytes = 2;
	strcpy(command[0xD0].isValid, "Valid");
	
	strcpy(command[0xF0].instruction,"SUBB $");
	command[0xF0].bytes = 2;
	strcpy(command[0xF0].isValid, "Valid");
	
	strcpy(command[0xE0].instruction,"SUBB,X $");
	command[0xE0].bytes = 1;
	command[0xE0].type = 18;
	strcpy(command[0xE0].isValid, "Valid");
	
	strcpy(extraCommand[0xE0].instruction,"SUBB,Y $"); /*18 Type*/
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
	
	strcpy(command[0xA3].instruction,"SUBD,X $");
	command[0xA3].bytes = 1;
	command[0xA3].type = 18;
	strcpy(command[0xA3].isValid, "Valid");
	
	strcpy(extraCommand[0xA3].instruction,"SUBD,Y $"); /*18 Type*/
	extraCommand[0xA3].bytes = 1;
	strcpy(extraCommand[0xA3].isValid, "Valid");
	
	strcpy(command[0x86].instruction,"LDAA #$");
	command[0x86].bytes = 1; /*Usually*/
	strcpy(command[0x86].isValid, "Valid");
	
	strcpy(command[0x96].instruction,"LDAA $");
	command[0x96].bytes = 2;
	strcpy(command[0x96].isValid, "Valid");
	
	strcpy(command[0xB6].instruction,"LDAA $");
	command[0xB6].bytes = 2;
	strcpy(command[0xB6].isValid, "Valid");
	
	strcpy(command[0xA6].instruction,"LDAA,X $");
	command[0xA6].bytes = 1;
	command[0xA6].type = 18;
	strcpy(command[0xA6].isValid, "Valid");
	
	strcpy(extraCommand[0xA6].instruction,"LDAA,Y $"); /*18 Type*/
	extraCommand[0xA6].bytes = 1;
	strcpy(extraCommand[0xA6].isValid, "Valid");
	
	strcpy(command[0xC6].instruction,"LDAB #$");
	command[0xC6].bytes = 2; /*Usually*/
	strcpy(command[0xC6].isValid, "Valid");
	
	strcpy(command[0xD6].instruction,"LDAB $");
	command[0xD6].bytes = 2;
	strcpy(command[0xD6].isValid, "Valid");
	
	strcpy(command[0xF6].instruction,"LDAB $");
	command[0xF6].bytes = 2;
	strcpy(command[0xF6].isValid, "Valid");
	
	strcpy(command[0xE6].instruction,"LDAB,X $");
	command[0xE6].bytes = 1;
	command[0xE6].type = 18;
	strcpy(command[0xE6].isValid, "Valid");
	
	strcpy(extraCommand[0xE6].instruction,"LDAB,Y $"); /*18 Type*/
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
	
	strcpy(command[0xEC].instruction,"LDD,X $");
	command[0xEC].bytes = 1;
	command[0xEC].type = 18;
	strcpy(command[0xEC].isValid, "Valid");
	
	strcpy(extraCommand[0xEC].instruction,"LDD,Y $"); /*18 Type*/
	extraCommand[0xEC].bytes = 1;
	strcpy(extraCommand[0xEC].isValid, "Valid");
	
	strcpy(command[0x97].instruction,"STAA $");
	command[0x97].bytes = 2; /*Top 8 bits assumed 00*/
	strcpy(command[0x97].isValid, "Valid");
	
	strcpy(command[0xB7].instruction,"STAA $");
	command[0xB7].bytes = 2;
	strcpy(command[0xB7].isValid, "Valid");
	
	strcpy(command[0xA7].instruction,"STAA,X $");
	command[0xA7].bytes = 1;
	command[0xA7].type = 18;
	strcpy(command[0xA7].isValid, "Valid");
	
	strcpy(extraCommand[0xA7].instruction,"STAA,Y $"); /*18 Type*/
	extraCommand[0xA7].bytes = 1;
	strcpy(extraCommand[0xA7].isValid, "Valid");
	
	strcpy(command[0xD7].instruction,"STAB $");
	command[0xD7].bytes = 2; /*Top 8 bits assumed 00*/
	strcpy(command[0xD7].isValid, "Valid");
	
	strcpy(command[0xF7].instruction,"STAB $");
	command[0xF7].bytes = 2;
	strcpy(command[0xF7].isValid, "Valid");
	
	strcpy(command[0xE7].instruction,"STAB,X $");
	command[0xE7].bytes = 1;
	command[0xE7].type = 18;
	strcpy(command[0xE7].isValid, "Valid");
	
	strcpy(extraCommand[0xE7].instruction,"STAB,Y $"); /*18 Type*/
	extraCommand[0xE7].bytes = 1;
	strcpy(extraCommand[0xE7].isValid, "Valid");
	
	strcpy(command[0xDD].instruction,"STD $");
	command[0xDD].bytes = 1;
	strcpy(command[0xDD].isValid, "Valid");
	
	strcpy(command[0xFD].instruction,"STD $");
	command[0xFD].bytes = 2;
	strcpy(command[0xFD].isValid, "Valid");
	
	strcpy(command[0xED].instruction,"STD,X $");
	command[0xED].bytes = 1;
	command[0xED].type = 18;
	strcpy(command[0xED].isValid, "Valid");
	
	strcpy(extraCommand[0xED].instruction,"STD,Y $"); /*18 Type*/
	extraCommand[0xED].bytes = 1;
	strcpy(extraCommand[0xED].isValid, "Valid");
	

	/*Get the disassembler paramters*/
	printf("Please enter a start address: ");
	gets(getStart); /*Obtain user entered address*/
	printf("\n\rString obtained: %s\n\r", getStart);
	sscanf(getStart, "%x", &addTemp); /*assign input to addvalue*/
	printf("\n\rAddress obtained: %x, %d\n\r", addTemp, addTemp);
	addStart = (unsigned char *)addTemp;
	
	printf("Please enter an end address: ");
	gets(getEnd); /*Obtain user entered address*/
	printf("\n\rString obtained: %s\n\r", getEnd);
	sscanf(getEnd, "%x", &addTemp); /*assign input to addvalue*/
	printf("\n\rAddress obtained: %x, %d\n\r", addTemp, addTemp);
	addEnd = (unsigned char *)addTemp;
	
	/*get opcode*/
	addRange = addEnd - addStart;
	printf("Range =Hex: %x, Dec: %d\n\r", addRange, addRange);
	n = 0;
	
	for(i = 0; i < addRange+1; i++)
	{
		/*Clear the strings and flags*/
		temp[0] = '\0';
		temp1[0] = '\0';
		temp2[0] = '\0';
		
		data = *addStart;
		printf("\n\rAddress: %x, Data: %02x,", addStart, data);
		flagData = *(addStart+1);
	
		/*look up string*/
		if (strcmp(command[data].isValid, "Valid") == 0) /*Check valid tab*/
		{
			if (command[data].type == 18 && flagData == 0x18)
			{
				strcpy(temp, extraCommand[data].instruction);
			}
			else
			{
				strcpy(temp, command[data].instruction);
			}
				
			/*look up number of bytes next*/
			if (command[data].bytes == 2)
			{
				data1 = *(addStart+1);
				sprintf(temp1, "%02x", data1);
				data2 = *(addStart+2);
				sprintf(temp2, "%02x", data2);
				strcat(temp1, temp2);
				i++;
				i++;
				addStart++;
				addStart++;
			}
			
			if (command[data].bytes == 1)
			{
				data1 = *(addStart+1);
				sprintf(temp1, "%02x", data1);
				i++;
				addStart++;
			}
		
			strcat(temp,temp1);
			printf("\tCommand: %s", temp);
			
		}
		addStart++;
		
		/*Page break here*/
		n++;
		if (n == 15)
		{
			printf("\n\n\r%ld/%u addresses displayed. Press any key to continue.\n\r", (i), (addRange));
			wait = '\0';
			while (wait == '\0')
			{
				wait = mkeyscan();
			}
			n = 0;
		}
	}
}

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



